/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2023 LABRI,
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI -- Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
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
<<<<<<< HEAD
#include "generator.hpp"
#include "application.hpp"
=======
#include "parser.hpp"
#include "generator.hpp"
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
#include "vartable.hpp"
#include "node.hpp"
#include "forest.hpp"
#include "messages.hpp"
#include "config.hpp"
<<<<<<< HEAD
#include "usage_exception.hpp"
=======
#include "fatal_exception.hpp"
#include "usage_exception.hpp"
#include "parser_exception.hpp"
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723

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
<<<<<<< HEAD
void showUsage() {
    std::cerr << "Usage: " << PROJECT_NAME << " parameters [options] [<input>]*\n";
=======
void usage()
{
    std::cerr << "Usage: " << PROJECT_NAME << " [options] [<input>]*\n";
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    std::cerr << "\
parameters\n\
\t--help|-h                                   print this\n\
\t--version|-v                                print version\n\
\t-rulesFile <file>                           the rules\n\
\t-lexiconFile <file>                         the lexicon\n\
options\n\
\t--verbose|-V                                verbose mode\n\
\t--reduceAll|-a                              reduce all rules\n\
\t--random|-r                                 outputs first sentence randomly selected\n\
\t--first|-f                                  outputs the first sentence\n\
\t--trace|-t                                  trace the @trace rules\n\
\t--traceAll\n\
\t--traceInit\n\
\t--traceStage\n\
\t--traceClose\n\
\t--traceShift\n\
\t--traceReduce\n\
\t--traceAction\n\
\t-maxLength <number>                         max sentence length\n\
\t-maxUsages <number>                         max number of rule usage\n\
\t-maxItems <number>                          max number of items per set\n\
\t-maxTime <seconds>                          max time in seconds\n\
<<<<<<< HEAD
=======
\t-rulesFile <file>                           the rules\n\
\t-lexiconFile <file>                         the lexicon\n\
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
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
void sig_handler(int signum)
{
    throw fatal_exception("ALARM SIGNAL" + std::to_string(signum) + " OUT OF TIME");
}

/* **************************************************
 *
 ************************************************** */
void generate(bool trace)
{
    int randomTry = 0;
<<<<<<< HEAD
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
=======
    do
    {
        synthesizer.clear();
        if (parser.getStartTerm())
        {
            synthesizer.generate(parser);
        }
        if (trace){
            std::cout << "<ul>" << std::endl;
        }
        if (synthesizer.getNodeRoot() && !synthesizer.getNodeRoot()->empty())
        {
            std::vector<forestPtr>::const_iterator forestIt = synthesizer.getNodeRoot()->cbegin();
            forestPtr forest;
            if (synthesizer.getRandom())
            {
                unsigned int rv = std::rand() / ((RAND_MAX + 1u) / synthesizer.getNodeRoot()->size());
                forest = synthesizer.getNodeRoot()->at(rv);
            }
            while (forestIt != synthesizer.getNodeRoot()->cend())
            {
                if (!synthesizer.getRandom())
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
                    forest = *forestIt;
                for (auto i = forest->getOutput_cbegin(); i != forest->getOutput_cend(); ++i)
                {
                    if (trace){
                        std::cout << "<li>" << std::endl;
                    }
                    std::cout << (*i) << std::endl;
                    if (trace){
                        std::cout << "</li>" << std::endl;
                    }
                }
<<<<<<< HEAD
                if (application.getRandom())
=======
                if (synthesizer.getRandom() || synthesizer.getFirst())
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
                    break;
                ++forestIt;
            }
        }
<<<<<<< HEAD
#ifdef TRACE_OPTION
        std::cout << "</ul>" << std::endl;
#endif
    } while (application.getRandom() && application.getNodeRoot()->getForests().empty() &&
=======
        if (trace){
            std::cout << "</ul>" << std::endl;
        }
    } while (synthesizer.getRandom() && synthesizer.getNodeRoot()->empty() &&
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
             randomTry++ < MAXATTEMPTS);
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
int main(int argn, char **argv) {
  application = Application();

#ifdef TRACE_OPTION
    std::cout << "<html><head><title>Elvex</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"></head><body>" << std::endl;
#endif
    try {
=======
int main(int argn, char **argv)
{
    bool trace = false;
    try
    {
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
#ifdef OUTPUT_XML
        application.setOutXML(nullptr);
#endif
<<<<<<< HEAD
        if (argn <= 1) {
	  throw usage_exception();
        } else {
            for (unsigned int arg = 1; argv[arg]; ++arg) {
                if (argv[arg][0] == '-') {
                    if (!strcmp(argv[arg] + 1, "v") || !strcmp(argv[arg] + 1, "-version")) {
=======
        if (argn <= 1)
        {
            throw usage_exception("not enough arguments");
        }
        else
        {
            for (unsigned int arg = 1; argv[arg]; ++arg)
            {
                if (argv[arg][0] == '-')
                {
                    if (!strcmp(argv[arg] + 1, "v") || !strcmp(argv[arg] + 1, "-version"))
                    {
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
                        std::cout << ELVEX_VERSION << std::endl;
                        return EXIT_SUCCESS;
                    }

<<<<<<< HEAD
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
=======
                    if (!strcmp(argv[arg] + 1, "V") || !strcmp(argv[arg] + 1, "-verbose"))
                    {
                        synthesizer.setVerbose(true);
                        parser.setVerbose(true);
                    }
                    else if (!strcmp(argv[arg] + 1, "h") || !strcmp(argv[arg] + 1, "-help"))
                    {
                        usage();
                        return EXIT_SUCCESS;
                    }
                    else if (!strcmp(argv[arg] + 1, "a") || !strcmp(argv[arg] + 1, "-reduceAll"))
                    {
                        synthesizer.setReduceAll(true);
                    }
                    else if (!strcmp(argv[arg] + 1, "r") || !strcmp(argv[arg] + 1, "-random"))
                    {
                        std::srand(time(nullptr));
                        synthesizer.setRandom(true);
                    }
                    else if (!strcmp(argv[arg] + 1, "f") || !strcmp(argv[arg] + 1, "-first"))
                    {
                        synthesizer.setFirst(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "t") || !strcmp(argv[arg] + 1, "-trace"))
                    {
                        trace = true;
                        synthesizer.setTrace(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceAll"))
                    {
                        trace = true;
                        synthesizer.setTraceInit(true);
                        synthesizer.setTraceStage(true);
                        synthesizer.setTraceClose(true);
                        synthesizer.setTraceShift(true);
                        synthesizer.setTraceReduce(true);
                        synthesizer.setTraceAction(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceInit"))
                    {
                        trace = true;
                        synthesizer.setTraceInit(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceStage"))
                    {
                        trace = true;
                        synthesizer.setTraceStage(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceClose"))
                    {
                        trace = true;
                        synthesizer.setTraceClose(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceShift"))
                    {
                        trace = true;
                        synthesizer.setTraceShift(true);
                    }
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723

                    else if (!strcmp(argv[arg] + 1, "-traceReduce"))
                    {
                        trace = true;
                        synthesizer.setTraceReduce(true);
                    }

<<<<<<< HEAD
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
=======
                    else if (!strcmp(argv[arg] + 1, "-traceAction"))
                    {
                        trace = true;
                        synthesizer.setTraceAction(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "lexiconFile"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            synthesizer.setLexiconFileName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad lexiconFile argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "rulesFile"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            synthesizer.setRulesFileName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad rulesFile argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "inputFile"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            synthesizer.setInputFileName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad inputFile argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "maxLength"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            synthesizer.setMaxLength(atoi(argv[++arg]));
                        else
                        {
                            throw usage_exception("bad maxLength argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "maxUsages"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            synthesizer.setMaxUsages(atoi(argv[++arg]));
                        else
                        {
                            throw usage_exception("bad maxUsages argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "maxItems"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            synthesizer.setMaxItems(atoi(argv[++arg]));
                        else
                        {
                            throw usage_exception("bad maxItems argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "maxTime"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                        {
                            signal(SIGALRM, sig_handler);
                            alarm(atoi(argv[++arg]));
                            time(&before);
                        }
                        else
                        {
                            throw usage_exception("bad maxTime argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "compactedLexiconDirectory"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            synthesizer.setCompactedDirectoryName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad compactedLexiconDirectory argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "cld"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            synthesizer.setCompactedDirectoryName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad cld argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "compactedLexiconFile"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            synthesizer.setCompactedLexiconFileName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad compactedLexiconFile argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "clf"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            synthesizer.setCompactedLexiconFileName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad clf argument");
                        }
                    }

#ifdef OUTPUT_XML
                    else if (!strcmp(argv[arg] + 1, "xml"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                        {
                            synthesizer.setOutXML(strdup(argv[++arg]));
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
                        }
                        else
                        {
                            throw usage_exception("bad xml argument");
                        }
                    }
#endif
<<<<<<< HEAD
		    
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
=======

                    else
                    {
                        std::ostringstream oss;
                        oss << "Unknown argument: " << argv[arg] + 1 << std::endl;
                        throw usage_exception(oss);
                    }
                }
                else
                {
                    synthesizer.addInput(argv[arg]);
                }
            }

            if (synthesizer.getLexiconFileName().length() > 0)
            {
                parser.parseFile("@lexicon (", ")", synthesizer.getLexiconFileName());
            }

            if (synthesizer.getRulesFileName().length() > 0)
            {
                parser.parseFile("@rules (", ")", synthesizer.getRulesFileName());
                parser.getRules().analyseTerms(parser);
            }

            if (synthesizer.getCompactedLexiconFileName().length() > 0)
            {
                char *dir = strdup((synthesizer.getCompactedDirectoryName().length() > 0)
                                       ? synthesizer.getCompactedDirectoryName().c_str()
                                       : ".");
                char *file = strdup(synthesizer.getCompactedLexiconFileName().c_str());
                auto *lex = new CompactedLexicon(std::string(dir), std::string(file));
                lex->openFiles("r");
                lex->loadFsa();
                lex->loadData();
                lex->closeFiles();
                synthesizer.setCompactedLexicon(lex);
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
            }
	    
#ifdef OUTPUT_XML
<<<<<<< HEAD
            if (application.getOutXML()) {
	      document = xmlNewDoc ((xmlChar*)"1.0");
	      xmlDocSetRootElement(document, xmlNewNode(nullptr, (xmlChar*)"ROOT"));
	      xmlNodeRoot = xmlDocGetRootElement(document);
            }
#endif
	    
=======
            if (synthesizer.getOutXML())
            {
                document = xmlNewDoc((xmlChar *)"1.0");
                xmlDocSetRootElement(document, xmlNewNode(nullptr, (xmlChar *)"ROOT"));
                xmlNodeRoot = xmlDocGetRootElement(document);
            }
#endif
        }

    //COUT_LINE;
    //parser.printCacheLexicon(std::cout);


        if (trace){
            std::cout << "<html><head><title>Elvex</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"></head><body>" << std::endl;
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
        }
	
        srand(time(nullptr));
<<<<<<< HEAD

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
=======
        if (synthesizer.getInputFileName().length() > 0)
        {
            parser.parseFile("@input (", ")", synthesizer.getInputFileName());
            generate(trace);
        }

        for (std::list<std::string>::const_iterator i = synthesizer.getInputs().begin();
             i != synthesizer.getInputs().end(); ++i)
        {
            parser.parseBuffer("@input (", ")", *i, "input");
            generate(trace);
        }

#ifdef OUTPUT_XML
        if (synthesizer.getOutXML())
        {
            std::string encoding = "UTF-8";
            xmlSaveFormatFileEnc(synthesizer.getOutXML(), document, encoding.c_str(), 1);
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
        }
#endif
    }
<<<<<<< HEAD
    catch (fatal_exception &e) {
      return EXIT_FAILURE;
    }
    catch (usage_exception &e) {
      showUsage();
=======
    catch (fatal_exception &e)
    {
        std::cerr << "*** fatal error: " << e.getMessage() << std::endl;
        std::flush(std::cerr);
    }
    catch (usage_exception &e)
    {
        std::cerr << "*** usage error: " << e.getMessage() << std::endl;
        usage();
        std::flush(std::cerr);
        return EXIT_FAILURE;
    }
    catch (parser_exception &e)
    {
        std::cerr << "*** parser error: " << e.getMessage() << std::endl;
        std::flush(std::cerr);
        return EXIT_FAILURE;
    }
    catch (std::string s)
    {
        std::cerr << "*** error" << s << std::endl;
        return EXIT_FAILURE;
    }
    if (trace){
        std::cout << "</body></html>" << std::endl;
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    }
    return EXIT_SUCCESS;
}
