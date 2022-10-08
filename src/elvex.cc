/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2020 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: 
 * Lionel Clément
 * LaBRI -- Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#include <csignal>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "compacted-lexicon.hpp"
#include "generator.hpp"
#include "application.hpp"
#include "vartable.hpp"
#include "node.hpp"
#include "forest.hpp"
#include "messages.hpp"
#include "config.hpp"
#include "usage_exception.hpp"

Application application;
//Rules rules = application.getRules();

time_t before, after;
#ifdef OUTPUT_XML
xmlNodePtr xmlNodeRoot;
xmlDocPtr document;
#endif

/* **************************************************
 *
 ************************************************** */
void showUsage() {
    std::cerr << "Usage: " << PROJECT_NAME << " parameters [options] [<input>]*\n";
    std::cerr << "\
parameters\n\
\t--help|-h                                   print this\n\
\t--version|-v                                print version\n\
\t-rulesFile <file>                           the rules\n\
\t-lexiconFile <file>                         the lexicon\n\
options\n\
\t--verbose|-V                                verbose mode\n\
\t--reduceAll|-a                              reduce all rules\n\
\t--trace|-t                                  trace the generation process\n\
\t--random|-r                                 outputs one sentence randomly selected\n\
\t--one|-o                                    outputs the first sentence\n";
#ifdef TRACE_OPTION
    std::cerr << "\
 \t--traceInit\n\
 \t--traceStage\n\
 \t--traceClose\n\
 \t--traceShift\n\
 \t--traceReduce\n\
 \t--traceAction\n";
#endif
    std::cerr << "\
\t-maxLength <number>                         max number of length\n\
\t-maxUsages <number>                         max number of rule usage\n\
\t-maxCardinal <number>                       max number of items per set\n\
\t-maxTime <seconds>                          max time in seconds\n\
\t-inputFile <file>                           the input\n\
\t-compactedLexiconDirectory/-cld <directory> the directory which contains the compacted lexicon\n\
\t-compactedLexiconFile/-clf <file>           the compacted lexicon prefix name\n\
";
#ifdef OUTPUT_XML
    std::cerr << "\
\t-xml <file>                                 the XML file\n";
#endif
}

/* **************************************************
 *
 ************************************************** */
void sig_handler(int signum) {
    FATAL_ERROR("ALARM SIGNAL" + std::to_string(signum) + " OUT OF TIME")
}

/* **************************************************
 *
 ************************************************** */
void generate() {
    int randomTry = 0;
    do {
        if (application.generator.getStartTerm()) {
	  application.generate(application.generator);
        }
#ifdef TRACE_OPTION
        std::cout << "<ul>" << std::endl;
#endif
        if (application.getNodeRoot() && !application.getNodeRoot()->getForests().empty()) {
            std::vector<forestPtr>::const_iterator forestIt = application.getNodeRoot()->getForests().begin();
            forestPtr forest;
            if (application.getRandom()) {
                int rv = std::rand() / ((RAND_MAX + 1u) / application.getNodeRoot()->getForests().size());
                forest = application.getNodeRoot()->getForests().at(rv);
            }
            while (forestIt != application.getNodeRoot()->getForests().end()) {
                if (!application.getRandom())
                    forest = *forestIt;
                for (const auto & i : forest->getOutput()) {
#ifdef TRACE_OPTION
                    std::cout << "<li>" << std::endl;
#endif
                    std::cout << i << std::endl;
#ifdef TRACE_OPTION
                    std::cout << "</li>" << std::endl;
#endif
                }
                if (application.getRandom())
                    break;
                ++forestIt;
            }
        }
#ifdef TRACE_OPTION
        std::cout << "</ul>" << std::endl;
#endif
    } while (application.getRandom() && application.getNodeRoot()->getForests().empty() &&
             randomTry++ < MAXATTEMPTS);
}

/* **************************************************
 *
 ************************************************** */
int main(int argn, char **argv) {
  application = Application();

#ifdef TRACE_OPTION
    std::cout << "<html><head><title>Elvex</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"></head><body>" << std::endl;
#endif
    try {
#ifdef OUTPUT_XML
        application.setOutXML(nullptr);
#endif
        if (argn <= 1) {
	  throw usage_exception();
        } else {
            for (unsigned int arg = 1; argv[arg]; ++arg) {
                if (argv[arg][0] == '-') {
                    if (!strcmp(argv[arg] + 1, "v") || !strcmp(argv[arg] + 1, "-version")) {
                        std::cout << ELVEX_VERSION << std::endl;
                        return EXIT_SUCCESS;
                    }

		    if (!strcmp(argv[arg] + 1, "h") || !strcmp(argv[arg] + 1, "-help")) {
		      showUsage();
		      return EXIT_SUCCESS;
		    }
		    
                    if (!strcmp(argv[arg] + 1, "V") || !strcmp(argv[arg] + 1, "-verbose")) {
                        application.setVerbose(true);
                        application.setVerbose(true);

                    } else if (!strcmp(argv[arg] + 1, "t") || !strcmp(argv[arg] + 1, "-trace")) {
                        application.setTrace(true);

                    } else if (!strcmp(argv[arg] + 1, "a") || !strcmp(argv[arg] + 1, "-reduceAll")) {
                        application.setReduceAll(true);

                    } else if (!strcmp(argv[arg] + 1, "r") || !strcmp(argv[arg] + 1, "-random")) {
                        std::srand(time(nullptr));
                        application.setRandom(true);

                    } else if (!strcmp(argv[arg] + 1, "o") || !strcmp(argv[arg] + 1, "-one")) {
                        application.setOne(true);
                    }

#ifdef TRACE_OPTION
                        else if (!strcmp(argv[arg] + 1, "-traceInit")) {
                           application.setTraceInit(true);
                        }

                        else if (!strcmp(argv[arg] + 1, "-traceStage")) {
                           application.setTraceStage(true);
                        }

                        else if (!strcmp(argv[arg] + 1, "-traceClose")) {
                           application.setTraceClose(true);
                        }

                        else if (!strcmp(argv[arg] + 1, "-traceShift")) {
                           application.setTraceShift(true);
                        }

                        else if (!strcmp(argv[arg] + 1, "-traceReduce")) {
                           application.setTraceReduce(true);
                        }

                        else if (!strcmp(argv[arg] + 1, "-traceAction")) {
                           application.setTraceAction(true);
                        }

#endif

                    else if (!strcmp(argv[arg] + 1, "lexiconFile")) {
		      if ((argn != arg) && (argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-')) {
			application.setLexiconFileName(argv[++arg]);
		      }
		      else {
			throw usage_exception("lexiconFile value");
		      }
                    } else if (!strcmp(argv[arg] + 1, "rulesFile")) {
		      if ((argn != arg) && (argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-')) {
                            application.setRulesFileName(argv[++arg]);
		      }
		      else {
			throw usage_exception("rulesFile value");
                        }
                    } else if (!strcmp(argv[arg] + 1, "inputFile")) {
		      if ((argn != arg) && (argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-')){
			application.setInputFileName(argv[++arg]);
		      }
		      else {
			throw usage_exception("inputFile value");
		      }
                    } else if (!strcmp(argv[arg] + 1, "maxLength")) {
		      if ((argn != arg) && (argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-')){
			application.setMaxLength(atoi(argv[++arg]));
		      }
		      else {
			throw usage_exception("maxLength value");
		      }
                    } else if (!strcmp(argv[arg] + 1, "maxUsages")) {
		      if ((argn != arg) && (argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-')){
			application.setMaxUsages(atoi(argv[++arg]));
		      }
		      else {
			throw usage_exception("maxUsages value");
		      }
                    } else if (!strcmp(argv[arg] + 1, "maxCardinal")) {
		      if ((argn != arg) && (argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-')) {
			application.setMaxCardinal(atoi(argv[++arg]));
		      }
		      else {
			throw usage_exception("maxCardinal value");
		      }
                    } else if (!strcmp(argv[arg] + 1, "maxTime")) {
		      if ((argn != arg) && (argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-')) {
			signal(SIGALRM, sig_handler);
			alarm(atoi(argv[++arg]));
			time(&before);
		      } else {
			throw usage_exception("maxTime value");
		      }
                    } else if (!strcmp(argv[arg] + 1, "compactedLexiconDirectory")) {
		      if ((argn != arg) && (argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-')){
			application.setCompactedDirectoryName(argv[++arg]);
		      }
		      else {
			throw usage_exception("compactedLexiconDirectory value");
		      }
                    } else if (!strcmp(argv[arg] + 1, "cld")) {
		      if ((argn != arg) && (argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-')){
			application.setCompactedDirectoryName(argv[++arg]);
		      }
		      else {
			throw usage_exception("cld value");
		      }
                    } else if (!strcmp(argv[arg] + 1, "compactedLexiconFile")) {
		      if ((argn != arg) && (argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-')){
			application.setCompactedLexiconFileName(argv[++arg]);
		      }
		      else {
			throw usage_exception("compactedLexiconFile value");
		      }
                    } else if (!strcmp(argv[arg] + 1, "clf")) {
		      if ((argn != arg) && (argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-')){
			application.setCompactedLexiconFileName(argv[++arg]);
		      }
		      else {
			throw usage_exception("clf value");
		      }
                    }

#ifdef OUTPUT_XML
                        else if (!strcmp (argv[arg]+1, "xml")) {
                           if ((argn != arg) && (argv[arg + 1] != nullptr) && (argv[arg + 1][0]!='-')) {
			     application.setOutXML(strdup(argv[++arg]));
                           }
                           else {
                              throw usage_exception("xml value");
                           }
                        }
#endif
		    
			else {
			  std::ostringstream oss;
			  oss << "Unknown argument: " << argv[arg] + 1;
			  throw usage_exception(oss.str());
			}
                } else {
		  application.addInput(argv[arg]);
                }
            }
	    
            if (application.getRulesFileName().length() > 0) {
	      application.generator.parseFile("@rules", application.getRulesFileName());
	      application.generator.getRules().analyseTerms(application);
            }
	    
            if (application.getLexiconFileName().length() > 0) {
	      application.generator.parseFile("@lexicon", application.getLexiconFileName());
            }
	    
            if (application.getCompactedLexiconFileName().length() > 0) {
	      char *dir = strdup((application.getCompactedDirectoryName().length() > 0)
				 ? application.getCompactedDirectoryName().c_str() : ".");
	      char *file = strdup(application.getCompactedLexiconFileName().c_str());
	      auto *lex = new CompactedLexicon(std::string(dir), std::string(file));
	      application.setCompactedLexicon(lex);
	      lex->openFiles("r");
	      lex->loadFsa();
	      lex->loadData();
	      lex->closeFiles();
            }
	    
#ifdef OUTPUT_XML
            if (application.getOutXML()) {
	      document = xmlNewDoc ((xmlChar*)"1.0");
	      xmlDocSetRootElement(document, xmlNewNode(nullptr, (xmlChar*)"ROOT"));
	      xmlNodeRoot = xmlDocGetRootElement(document);
            }
#endif
	    
        }
	
        srand(time(nullptr));

	if (application.getInputFileName().length() > 0) {
	  application.generator.parseFile("@input", application.getInputFileName());
          generate();
        }

        for (std::list<std::string>::const_iterator i = application.getInputs().begin();
             i != application.getInputs().end(); ++i) {
	  CERR_LINE;
	  application.generator.parseBuffer("@input", *i, "input");
	  generate();
        }

#ifdef OUTPUT_XML
        if (application.getOutXML()) {
           std::string encoding="UTF-8";
           xmlSaveFormatFileEnc(application.getOutXML(), document, encoding.c_str(), 1);
        }
#endif

    }
    catch (fatal_exception &e) {
      return EXIT_FAILURE;
    }
    catch (usage_exception &e) {
      showUsage();
    }
#ifdef TRACE_OPTION
    std::cout << "</body></html>" << std::endl;
#endif
    return EXIT_SUCCESS;
}
