/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI,
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
#include "parser.hpp"
#include "synthesizer.hpp"
#include "vartable.hpp"
#include "node.hpp"
#include "forest.hpp"
#include "messages.hpp"
#include "config.hpp"
#include "fatal_exception.hpp"
#include "usage_exception.hpp"
#include "parser_exception.hpp"

Parser parser = Parser();
Synthesizer synthesizer = Synthesizer();

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
\t--random|-r                                 outputs one sentence randomly selected\n\
\t--one|-o                                    outputs the first sentence\n";
#ifdef TRACE_OPTION
    std::cerr << "\
 \t--trace|-t                                  trace the @trace rules\n\
 \t--traceAll\n\
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
        synthesizer.clear();
        if (parser.getStartTerm())
        {
            synthesizer.generate(parser);
        }
#ifdef TRACE_OPTION
        if (trace){
            std::cout << "<ul>" << std::endl;
        }
#endif
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
                    forest = *forestIt;
                for (auto i = forest->getOutput_cbegin(); i != forest->getOutput_cend(); ++i)
                {
#ifdef TRACE_OPTION
        if (trace){
                    std::cout << "<li>" << std::endl;
        }
#endif
                    std::cout << (*i) << std::endl;
#ifdef TRACE_OPTION
        if (trace){
                    std::cout << "</li>" << std::endl;
        }
#endif
                }
                if (synthesizer.getRandom())
                    break;
                ++forestIt;
            }
        }
#ifdef TRACE_OPTION
        if (trace){
            std::cout << "</ul>" << std::endl;
        }
#endif
    } while (synthesizer.getRandom() && synthesizer.getNodeRoot()->empty() &&
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
        synthesizer.setOutXML(nullptr);
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
                    else if (!strcmp(argv[arg] + 1, "o") || !strcmp(argv[arg] + 1, "-one"))
                    {
                        synthesizer.setOne(true);
                    }

#ifdef TRACE_OPTION
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

                    else if (!strcmp(argv[arg] + 1, "-traceReduce"))
                    {
                        trace = true;
                        synthesizer.setTraceReduce(true);
                    }

                    else if (!strcmp(argv[arg] + 1, "-traceAction"))
                    {
                        trace = true;
                        synthesizer.setTraceAction(true);
                    }

#endif

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
                    else if (!strcmp(argv[arg] + 1, "maxLength"))
                    {
                        if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
                            synthesizer.setMaxUsages(atoi(argv[++arg]));
                        else
                        {
                            throw usage_exception("bad maxLength argument");
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
                    synthesizer.addInput(argv[arg]);
                }
            }

            if (synthesizer.getLexiconFileName().length() > 0)
            {
                parser.parseFile("@lexicon", synthesizer.getLexiconFileName());
            }

            if (synthesizer.getRulesFileName().length() > 0)
            {
                parser.parseFile("@rules", synthesizer.getRulesFileName());
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
            }

#ifdef OUTPUT_XML
            if (synthesizer.getOutXML())
            {
                document = xmlNewDoc((xmlChar *)"1.0");
                xmlDocSetRootElement(document, xmlNewNode(nullptr, (xmlChar *)"ROOT"));
                xmlNodeRoot = xmlDocGetRootElement(document);
            }
#endif
        }

#ifdef TRACE_OPTION
        if (trace){
            std::cout << "<html><head><title>Elvex</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"></head><body>" << std::endl;
        }
#endif

        srand(time(nullptr));
        if (synthesizer.getInputFileName().length() > 0)
        {
            parser.parseFile("@input", synthesizer.getInputFileName());
            generate(trace);
        }

        for (std::list<std::string>::const_iterator i = synthesizer.getInputs().begin();
             i != synthesizer.getInputs().end(); ++i)
        {
            parser.parseBuffer("@input", *i, "input");
            generate(trace);
        }

#ifdef OUTPUT_XML
        if (synthesizer.getOutXML())
        {
            std::string encoding = "UTF-8";
            xmlSaveFormatFileEnc(synthesizer.getOutXML(), document, encoding.c_str(), 1);
        }
#endif
    }
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
#ifdef TRACE_OPTION
    if (trace){
        std::cout << "</body></html>" << std::endl;
    }
#endif
    return EXIT_SUCCESS;
}
