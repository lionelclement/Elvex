/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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

#include <algorithm>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

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

Parser parser;
Generator generator;

#ifdef OUTPUT_XML
xmlNodePtr xmlNodeRoot;
xmlDocPtr document;
#endif

namespace
{

    time_t before;
    // time_t after;

    bool isOption(const char *arg, std::initializer_list<const char *> names)
    {
        for (const char *name : names)
        {
            if (std::strcmp(arg, name) == 0)
            {
                return true;
            }
        }

        return false;
    }

    char *readOptionValue(int &arg, char **argv, const std::string &optionName)
    {
        if (argv[arg + 1] != nullptr && argv[arg + 1][0] != '-')
        {
            return argv[++arg];
        }

        throw usage_exception("bad " + optionName + " argument");
    }

    void usage()
    {
        std::cerr << "Usage: " << PROJECT_NAME << " [options] [<input>]*\n";
        std::cerr << "\
Options:\n\
\t-h, --help                                       print this help message\n\
\t-v, --version                                    print version\n\
\t-V, --verbose                                    enable verbose mode\n\
\t-a, --reduce-all                                 reduce all rules\n\
\t-r, --random                                     output one randomly selected sentence\n\
\t--seed <number>                                  random seed for reproducible generation\n\
\t-f, --first                                      output the first sentence\n\
\t--strategy <exhaustive|sample|beam>              derivation strategy; default: exhaustive\n\
\t--max-rule-choices <number>                      maximum rule/disjunction choices opened in sample mode\n\
\t--beam-width <number>                            maximum items kept per state in beam mode\n\
\t--max-length <number>                            maximum sentence length\n\
\t--max-usages <number>                            maximum number of rule usages\n\
\t--max-items <number>                             maximum number of items per set\n\
\t--max-time <seconds>                             maximum time in seconds\n\
\t--max-attempts <number>                          maximum attempts for a random choice\n\
\t--macros-file <file>                             macros file\n\
\t--rules-file <file>                              rules file\n\
\t--lexicon-file <file>                            lexicon file\n\
\t--input-file <file>                              input file\n\
\t--compacted-lexicon-file, --clf <path/file>      compacted lexicon file prefix\n\
\t-t, --trace                                      trace the @trace rules\n\
\t--trace-all                                      trace everything\n\
\t--trace-init                                     trace initialization\n\
\t--trace-stage                                    trace stage steps\n\
\t--trace-close                                    trace close steps\n\
\t--trace-shift                                    trace shift steps\n\
\t--trace-reduce                                   trace reduce steps\n\
\t--trace-action                                   trace actions\n\
";
#ifdef OUTPUT_XML
        std::cerr << "\
\t--xml <file>                                     XML output file\n";
#endif
    }

    void sig_handler(int signum)
    {
        throw fatal_exception("alarm signal " + std::to_string(signum) + ": out of time");
    }

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
                    size_t rv = generator.randomIndex(generator.getNodeRoot()->size());
                    forest = generator.getNodeRoot()->at(rv);
                }

                while (forestIt != generator.getNodeRoot()->cend())
                {
                    if (!generator.getRandomResult())
                    {
                        forest = *forestIt;
                    }

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
                    {
                        break;
                    }

                    ++forestIt;
                }
            }

            if (trace)
            {
                std::cout << "</ul>" << std::endl;
            }
        } while (generator.getRandomResult() &&
                 generator.getNodeRoot()->empty() &&
                 randomTry++ < MAXATTEMPTS);
    }
}

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

        for (int arg = 1; argv[arg] != nullptr; ++arg)
        {
            if (argv[arg][0] != '-')
            {
                generator.addInput(argv[arg]);
                continue;
            }

            const char *option = argv[arg];

            if (isOption(option, {"-v", "--version"}))
            {
                std::cout << ELVEX_VERSION << std::endl;
                return EXIT_SUCCESS;
            }
            else if (isOption(option, {"-V", "--verbose"}))
            {
                generator.setVerbose(true);
                parser.setVerbose(true);
            }
            else if (isOption(option, {"-h", "--help"}))
            {
                usage();
                return EXIT_SUCCESS;
            }
            else if (isOption(option, {"-a", "--reduce-all"}))
            {
                generator.setReduceAll(true);
            }
            else if (isOption(option, {"-r", "--random"}))
            {
                generator.setRandomResult(true);
            }
            else if (isOption(option, {"-f", "--first"}))
            {
                generator.setFirstResult(true);
            }
            else if (isOption(option, {"-t", "--trace"}))
            {
                trace = true;
                generator.setTrace(true);
            }
            else if (isOption(option, {"--trace-all"}))
            {
                trace = true;
                generator.setTraceInit(true);
                generator.setTraceStage(true);
                generator.setTraceClose(true);
                generator.setTraceShift(true);
                generator.setTraceReduce(true);
                generator.setTraceAction(true);
            }
            else if (isOption(option, {"--trace-init"}))
            {
                trace = true;
                generator.setTraceInit(true);
            }
            else if (isOption(option, {"--trace-stage"}))
            {
                trace = true;
                generator.setTraceStage(true);
            }
            else if (isOption(option, {"--trace-close"}))
            {
                trace = true;
                generator.setTraceClose(true);
            }
            else if (isOption(option, {"--trace-shift"}))
            {
                trace = true;
                generator.setTraceShift(true);
            }
            else if (isOption(option, {"--trace-reduce"}))
            {
                trace = true;
                generator.setTraceReduce(true);
            }
            else if (isOption(option, {"--trace-action"}))
            {
                trace = true;
                generator.setTraceAction(true);
            }
            else if (isOption(option, {"--macros-file"}))
            {
                generator.setMacrosFileName(readOptionValue(arg, argv, "macros-file"));
            }
            else if (isOption(option, {"--lexicon-file"}))
            {
                generator.setLexiconFileName(readOptionValue(arg, argv, "lexicon-file"));
            }
            else if (isOption(option, {"--rules-file"}))
            {
                generator.setRulesFileName(readOptionValue(arg, argv, "rules-file"));
            }
            else if (isOption(option, {"--input-file"}))
            {
                generator.setInputFileName(readOptionValue(arg, argv, "input-file"));
            }
            else if (isOption(option, {"--max-length"}))
            {
                generator.setMaxLength(std::atoi(readOptionValue(arg, argv, "max-length")));
            }
            else if (isOption(option, {"--max-usages"}))
            {
                generator.setMaxUsages(std::atoi(readOptionValue(arg, argv, "max-usages")));
            }
            else if (isOption(option, {"--max-items"}))
            {
                generator.setMaxItems(std::atoi(readOptionValue(arg, argv, "max-items")));
            }
            else if (isOption(option, {"--max-time"}))
            {
                signal(SIGALRM, sig_handler);
                alarm(std::atoi(readOptionValue(arg, argv, "max-time")));
                time(&before);
            }
            else if (isOption(option, {"--max-attempts"}))
            {
                generator.setMaxAttemps(std::atoi(readOptionValue(arg, argv, "max-attempts")));
            }
            else if (isOption(option, {"--seed"}))
            {
                generator.seedRandom(
                    static_cast<uint32_t>(
                        std::strtoul(readOptionValue(arg, argv, "seed"), nullptr, 10)));
            }
            else if (isOption(option, {"--strategy"}))
            {
                std::string strategyName(readOptionValue(arg, argv, "strategy"));

                if (!generator.setStrategy(strategyName))
                {
                    throw usage_exception("bad strategy argument: expected exhaustive, sample, or beam");
                }
            }
            else if (isOption(option, {"--max-rule-choices"}))
            {
                generator.setMaxRuleChoices(
                    std::atoi(readOptionValue(arg, argv, "max-rule-choices")));
            }
            else if (isOption(option, {"--beam-width"}))
            {
                generator.setBeamWidth(
                    std::atoi(readOptionValue(arg, argv, "beam-width")));
            }
            else if (isOption(option, {"--compacted-lexicon-file",
                                       "--clf"}))
            {
                generator.setCompactedLexiconFileName(
                    readOptionValue(arg, argv, "compacted-lexicon-file"));
            }

#ifdef OUTPUT_XML
            else if (isOption(option, {"--xml"}))
            {
                generator.setOutXML(strdup(readOptionValue(arg, argv, "xml")));
            }
#endif

            else
            {
                std::ostringstream oss;
                oss << "Unknown argument: " << option;
                throw usage_exception(oss);
            }
        }

        if (generator.getMacrosFileName().length() > 0)
        {
            parser.parseFile("@macros (", ")", generator.getMacrosFileName());
            parser.getRules().analyseTerms(parser);
        }

        if (generator.getRulesFileName().length() > 0)
        {
            parser.parseFile("@rules (", ")", generator.getRulesFileName());
            parser.getRules().analyseTerms(parser);
        }
        else
        {
            throw usage_exception("Rules file not found");
        }

        if ((generator.getLexiconFileName().length() == 0) &&
            (generator.getCompactedLexiconFileName().length() == 0))
        {
            throw usage_exception("Lexicon not found");
        }

        if (generator.getLexiconFileName().length() > 0)
        {
            parser.parseFile("@lexicon (", ")", generator.getLexiconFileName());
        }

        if (generator.getCompactedLexiconFileName().length() > 0)
        {
            std::string filePrefix = generator.getCompactedLexiconFileName();

            auto *lex = new CompactedLexicon(filePrefix);
            lex->openFiles("r");
            lex->loadFsa(generator.getVerbose());
            lex->loadData(generator.getVerbose());
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

        if (trace)
        {
            std::cout <<
                R"(
<!DOCTYPE html>
<html>
<head>
    <title>Elvex</title>
    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">  
    <style>
        .hidden {
            display: none;
        }
    </style>
</head>
<body>
    <script>
        function toggleVisibility(id) {
            var element = document.getElementById(id);
            if (element.classList.contains('hidden')) {
                element.classList.remove('hidden');
            } else {
                element.classList.add('hidden');
            }
        }
    </script>
)";
        }

        if (generator.getInputFileName().length() > 0)
        {
            parser.parseFile("@input (", ")", generator.getInputFileName());
            generate(trace);
        }
        else
        {
            std::string line;

            while (std::getline(std::cin, line))
            {
                generator.addInput(line);
            }
        }

        if (!generator.emptyInputs())
        {
            for (auto it = generator.cbeginInputs(); it != generator.cendInputs(); ++it)
            {
                const std::string &s = *it;

                auto first = std::find_if_not(
                    s.begin(),
                    s.end(),
                    [](unsigned char c)
                    {
                        return std::isspace(c);
                    });

                if (first == s.end() ||
                    (first != s.end() &&
                     *first == '/' &&
                     (first + 1) != s.end() &&
                     *(first + 1) == '/'))
                {
                    continue;
                }

                parser.parseBuffer("@input (", ")", s, "input");
                generate(trace);
            }
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
        std::cout <<
            R"(

</body>
</html>
)";
    }

    return EXIT_SUCCESS;
}