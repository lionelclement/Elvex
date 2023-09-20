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
 * LaBRI - Université Bordeaux 
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
#include "parser.hpp"
#include "generator.hpp"
#include "vartable.hpp"
#include "node.hpp"
#include "forest.hpp"
#include "messages.hpp"
#include "config.hpp"
#include "fatal_exception.hpp"
#include "usage_exception.hpp"
#include "parser_exception.hpp"

Parser parser = Parser();
Generator generator = Generator();

time_t before, after;
#ifdef OUTPUT_XML
xmlNodePtr xmlNodeRoot;
xmlDocPtr document;
#endif

/* **************************************************
 *
 ************************************************** */
void usage()
{
    std::cerr << "Usage: " << PROJECT_NAME << " [options] [<input>]*\n";
    std::cerr << "\
options\n\
\t--help|-h                                   print this\n\
\t--version|-v                                print version\n\
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
\t-rulesFile <file>                           the rules\n\
\t-lexiconFile <file>                         the lexicon\n\
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
    do
    {
        generator.clear();
        if (parser.getStartTerm())
        {
            generator.generate(parser);
        }
        if (trace)
        {
            std::cout << "<ul>" << std::endl;
        }
        if (generator.getNodeRoot() && !generator.getNodeRoot()->empty())
        {
            std::vector<forestPtr>::const_iterator forestIt = generator.getNodeRoot()->cbegin();
            forestPtr forest;
            if (generator.getRandomResult())
            {
                unsigned int rv = std::rand() / ((RAND_MAX + 1u) / generator.getNodeRoot()->size());
                forest = generator.getNodeRoot()->at(rv);
            }
            while (forestIt != generator.getNodeRoot()->cend())
            {
                if (!generator.getRandomResult())
                    forest = *forestIt;
                for (auto i = forest->output_cbegin(); i != forest->output_cend(); ++i)
                {
                    if (trace)
                    {
                        std::cout << "<li>" << std::endl;
                    }
                    std::cout << (*i) << std::endl;
                    if (trace)
                    {
                        std::cout << "</li>" << std::endl;
                    }
                }
                if (generator.getRandomResult() || generator.getFirstResult())
                    break;
                ++forestIt;
            }
        }
        if (trace)
        {
            std::cout << "</ul>" << std::endl;
        }
    } while (generator.getRandomResult() && generator.getNodeRoot()->empty() &&
             randomTry++ < MAXATTEMPTS);
}

/* **************************************************
 *
 ************************************************** */
int main(int argn, char **argv)
{
    bool trace = false;
    try
    {
#ifdef OUTPUT_XML
        generator.setOutXML(nullptr);
#endif
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
                        std::cout << ELVEX_VERSION << std::endl;
                        return EXIT_SUCCESS;
                    }

                    if (!strcmp(argv[arg] + 1, "V") || !strcmp(argv[arg] + 1, "-verbose"))
                    {
                        generator.setVerbose(true);
                        parser.setVerbose(true);
                    }
                    else if (!strcmp(argv[arg] + 1, "h") || !strcmp(argv[arg] + 1, "-help"))
                    {
                        usage();
                        return EXIT_SUCCESS;
                    }
                    else if (!strcmp(argv[arg] + 1, "a") || !strcmp(argv[arg] + 1, "-reduceAll"))
                    {
                        generator.setReduceAll(true);
                    }
                    else if (!strcmp(argv[arg] + 1, "r") || !strcmp(argv[arg] + 1, "-random"))
                    {
                        std::srand(time(nullptr));
                        generator.setRandomResult(true);
                    }
                    else if (!strcmp(argv[arg] + 1, "f") || !strcmp(argv[arg] + 1, "-first"))
                    {
                        generator.setFirstResult(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "t") || !strcmp(argv[arg] + 1, "-trace"))
                    {
                        trace = true;
                        generator.setTrace(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceAll"))
                    {
                        trace = true;
                        generator.setTraceInit(true);
                        generator.setTraceStage(true);
                        generator.setTraceClose(true);
                        generator.setTraceShift(true);
                        generator.setTraceReduce(true);
                        generator.setTraceAction(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceInit"))
                    {
                        trace = true;
                        generator.setTraceInit(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceStage"))
                    {
                        trace = true;
                        generator.setTraceStage(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceClose"))
                    {
                        trace = true;
                        generator.setTraceClose(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceShift"))
                    {
                        trace = true;
                        generator.setTraceShift(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceReduce"))
                    {
                        trace = true;
                        generator.setTraceReduce(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceAction"))
                    {
                        trace = true;
                        generator.setTraceAction(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "lexiconFile"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            generator.setLexiconFileName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad lexiconFile argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "rulesFile"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            generator.setRulesFileName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad rulesFile argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "inputFile"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            generator.setInputFileName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad inputFile argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "maxLength"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            generator.setMaxLength(atoi(argv[++arg]));
                        else
                        {
                            throw usage_exception("bad maxLength argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "maxUsages"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            generator.setMaxUsages(atoi(argv[++arg]));
                        else
                        {
                            throw usage_exception("bad maxUsages argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "maxItems"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            generator.setMaxItems(atoi(argv[++arg]));
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
                            generator.setCompactedDirectoryName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad compactedLexiconDirectory argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "cld"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            generator.setCompactedDirectoryName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad cld argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "compactedLexiconFile"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            generator.setCompactedLexiconFileName(argv[++arg]);
                        else
                        {
                            throw usage_exception("bad compactedLexiconFile argument");
                        }
                    }
                    else if (!strcmp(argv[arg] + 1, "clf"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            generator.setCompactedLexiconFileName(argv[++arg]);
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
                            generator.setOutXML(strdup(argv[++arg]));
                        }
                        else
                        {
                            throw usage_exception("bad xml argument");
                        }
                    }
#endif

                    else
                    {
                        std::ostringstream oss;
                        oss << "Unknown argument: " << argv[arg] + 1 << std::endl;
                        throw usage_exception(oss);
                    }
                }
                else
                {
                    generator.addInput(argv[arg]);
                }
            }

            if (generator.getLexiconFileName().length() > 0)
            {
                parser.parseFile("@lexicon (", ")", generator.getLexiconFileName());
            }

            if (generator.getRulesFileName().length() > 0)
            {
                parser.parseFile("@rules (", ")", generator.getRulesFileName());
                parser.getRules().analyseTerms(parser);
            }

            if (generator.getCompactedLexiconFileName().length() > 0)
            {
                char *dir = strdup((generator.getCompactedDirectoryName().length() > 0)
                                       ? generator.getCompactedDirectoryName().c_str()
                                       : ".");
                char *file = strdup(generator.getCompactedLexiconFileName().c_str());
                auto *lex = new CompactedLexicon(std::string(dir), std::string(file));
                lex->openFiles("r");
                lex->loadFsa();
                lex->loadData();
                lex->closeFiles();
                generator.setCompactedLexicon(lex);
            }

#ifdef OUTPUT_XML
            if (generator.getOutXML())
            {
                document = xmlNewDoc((xmlChar *)"1.0");
                xmlDocSetRootElement(document, xmlNewNode(nullptr, (xmlChar *)"ROOT"));
                xmlNodeRoot = xmlDocGetRootElement(document);
            }
#endif
        }

        // COUT_LINE;
        // parser.printCacheLexicon(std::cout);

        if (trace)
        {
            std::cout << "<html><head><title>Elvex</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"></head><body>" << std::endl;
        }
        srand(time(nullptr));

        if (generator.getInputFileName().length() > 0)
        {
            parser.parseFile("@input (", ")", generator.getInputFileName());
            generate(trace);
        }

        for (std::list<std::string>::const_iterator i = generator.getInputs().begin();
             i != generator.getInputs().end(); ++i)
        {
            parser.parseBuffer("@input (", ")", *i, "input");
            generate(trace);
        }

#ifdef OUTPUT_XML
        if (generator.getOutXML())
        {
            std::string encoding = "UTF-8";
            xmlSaveFormatFileEnc(generator.getOutXML(), document, encoding.c_str(), 1);
        }
#endif
    }
    catch (usage_exception &e)
    {
        std::cerr << "*** usage error: " << e.what() << std::endl;
        usage();
        std::flush(std::cerr);
        return EXIT_FAILURE;
    }
    catch (parser_exception &e)
    {
        std::cerr << "*** " << e.what() << std::endl;
        std::flush(std::cerr);
        return EXIT_FAILURE;
    }
    catch (fatal_exception &e)
    {
        std::cerr << "*** fatal error: " << e.what() << std::endl;
        std::flush(std::cerr);
        return EXIT_FAILURE;
    }
    if (trace)
    {
        std::cout << "</body></html>" << std::endl;
    }
    return EXIT_SUCCESS;
}
