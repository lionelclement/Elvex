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

#include <cstring>

#include "buildlexicon.hpp"
#include "compacted-lexicon.hpp"
#include "compacted-lexicon-info.hpp"
#include "lexicon.hpp"
#include "messages.hpp"
#include "synthesizer.hpp"
#include "config.hpp"

Parser parser = Parser();

/* **************************************************
 *
 ************************************************** */
void usage() {
    std::cerr << "Usage: " << PROJECT_NAME << "buildlexicon [global-option] <build|consult|list> <input>\n\
\tGlobal options:\n\
\t-h|--help                              print this\n\
\t-v|--version                           print version\n\
\t-compactedLexiconDirectory <directory> the directory which contains the compacted lexicon\n\
\t-compactedLexiconFile <file>           the compacted lexicon prefix name\n\
\t-patternFile <file>                    the pattern file\n\
\t-morphoFile <file>                     the morpho file"
            << std::endl;
    exit(EXIT_SUCCESS);
}

/* **************************************************
 *
 ************************************************** */
int main(int argn, char **argv) {
    try {
        CompactedLexicon* lex;
        Buildlexicon::Choice mode = Buildlexicon::NONE;
        std::string inputFileName = std::string();
        std::string prefix;
        std::string directory;
        std::string patternFile = std::string();
        std::string morphoFile = std::string();
        class Lexicon morpho = Lexicon();
        class Lexicon pattern = Lexicon();

        if (argn > 1) {
            // generic options
            for (unsigned int arg = 1; argv[arg]; ++arg) {
                if (argv[arg][0] == '-') {

                    if (!strcmp(argv[arg] + 1, "v") || !strcmp(argv[arg] + 1, "-version")) {
                        std::cout << ELVEX_VERSION << std::endl;
                        return EXIT_SUCCESS;
                    } else if (!strcmp(argv[arg] + 1, "h") || !strcmp(argv[arg] + 1, "-help")) {
                        usage();
                        return EXIT_SUCCESS;
                    } else if (!strcmp(argv[arg] + 1, "compactedLexiconFile")) {
                        prefix = std::string(argv[++arg]);
                    } else if (!strcmp(argv[arg] + 1, "compactedLexiconDirectory")) {
                        directory = std::string(argv[++arg]);
                    } else if (!strcmp(argv[arg] + 1, "patternFile")) {
                        patternFile = std::string(argv[++arg]);
                    } else if (!strcmp(argv[arg] + 1, "morphoFile")) {
                        morphoFile = std::string(argv[++arg]);
                    }
                } else {
                    if (!strcmp(argv[arg], "build"))
                        mode = Buildlexicon::BUILD;
                    else if (!strcmp(argv[arg], "consult"))
                        mode = Buildlexicon::CONSULT;
                    else if (!strcmp(argv[arg], "list"))
                        mode = Buildlexicon::LIST;
                    else
                        inputFileName = argv[arg];
                }
            }
        }

        if (!morphoFile.empty()) {
            std::ifstream inputFile;
            inputFile.open(morphoFile.c_str());
            char line[MAXSTRING];
            while (inputFile.getline(line, MAXSTRING)) {
                if ((line[0] != '#') && strchr(line, '\t')) {
                    //std::cerr << line << std::endl;
                    std::string input;
                    std::string output;

                    if (line[0] == '@') {
                        featuresPtr features;

                        char line2[MAXSTRING];
                        strcpy(line2, line);
                        char *form = strchr(line2, '@') + 1;
                        char *rhs = strchr(form, '\t');
                        *rhs = 0;

                        char line4[MAXSTRING];
                        strcpy(line4, line);
                        char *f = strchr(line4, '\t') + 1;

                        std::stringstream stream;
                        stream << form;
                        std::string _input = stream.str();

                        stream.str("");
                        stream << form;
                        std::string _output = stream.str();

                        stream.str("");
                        stream << '[' << f << ']';
                        std::string fsString = stream.str();
                        if (parser.parseBuffer("#", fsString, "morphology")) {
                            stream.str("");
                            stream << "error in lexicon: " << f << std::endl;
                            FATAL_ERROR(stream.str())
                        }
                        features = parser.getLocalFeatures();
                        //features->flatPrint(std::cerr);
                        parser.addMacros(_input, features);
                    } else {
                        char form[MAXSTRING];
                        strcpy(form, line);
                        char *rhs = strchr(form, '\t');
                        *rhs = 0;

                        char line2[MAXSTRING];
                        strcpy(line2, line);
                        char *pos = strchr(line2, '\t') + 1;
                        rhs = strchr(pos, '\t');
                        *rhs = 0;

                        char line3[MAXSTRING];
                        strcpy(line3, line);
                        char *lemma = strchr(line3, '\t') + 1;
                        lemma = strchr(lemma, '\t') + 1;
                        rhs = strchr(lemma, '\t');
                        *rhs = 0;

                        char line4[MAXSTRING];
                        strcpy(line4, line);
                        char *features = strchr(line4, '\t') + 1;
                        features = strchr(features, '\t') + 1;
                        features = strchr(features, '\t') + 1;

                        //std::cerr << "/form:/" << form << '/' << std::endl;
                        //std::cerr << "/pos:/" << pos << '/' << std::endl;
                        //std::cerr << "/lemma:/" << lemma << '/' << std::endl;
                        //std::cerr << "/features:/" << features << '/' << std::endl;

                        std::stringstream stream;
                        stream << lemma << '#' << pos;
                        std::string _input = stream.str();

                        stream.str("");
                        stream << form << '#' << features;
                        std::string _output = stream.str();
                        //std::cerr << "morpho/input:/" << _input << '/' << std::endl;
                        //std::cerr << "morpho/output:/" << _output << '/' << std::endl;
                        morpho.add(_input, _output);
                    }

                }
            }
            inputFile.close();
        }

        //parser.listMacros();

        if (!patternFile.empty()) {
            std::ifstream inputFile;
            inputFile.open(patternFile.c_str());
            char line[MAXSTRING];
            while (inputFile.getline(line, MAXSTRING)) {
                if ((line[0] != '#') && strchr(line, '\t')) {

                    //std::cerr << line << std::endl;

                    char lexeme[MAXSTRING];
                    strcpy(lexeme, line);
                    char *rhs = strchr(lexeme, '\t');
                    *rhs = 0;

                    char line2[MAXSTRING];
                    strcpy(line2, line);
                    char *pos = strchr(line2, '\t') + 1;
                    rhs = strchr(pos, '\t');
                    *rhs = 0;

                    char line3[MAXSTRING];
                    strcpy(line3, line);
                    char *lemma = strchr(line3, '\t') + 1;
                    lemma = strchr(lemma, '\t') + 1;
                    rhs = strchr(lemma, '\t');
                    *rhs = 0;

                    char line4[MAXSTRING];
                    strcpy(line4, line);
                    char *features = strchr(line4, '\t') + 1;
                    features = strchr(features, '\t') + 1;
                    features = strchr(features, '\t') + 1;

                    //std::cerr << "/lexeme:/" << lexeme << '/' << std::endl;
                    //std::cerr << "/pos:/" << pos << '/' << std::endl;
                    //std::cerr << "/lemma:/" << lemma << '/' << std::endl;
                    //std::cerr << "/features:/" << features << '/' << std::endl;

                    std::stringstream stream;
                    stream << lexeme << '#' << pos;
                    std::string input = stream.str();

                    stream.str("");
                    stream << lemma << '#' << features;
                    std::string output = stream.str();

                    //std::cerr << "pattern/input:/" << input << '/' << std::endl;
                    //std::cerr << "pattern/output:/" << output << '/' << std::endl;

                    pattern.add(input, output);

                }
            }
            inputFile.close();
        }

        //CERR_LINE

        switch (mode) {

            case Buildlexicon::BUILD: {
                lex = new CompactedLexicon(directory, prefix);
                lex->openFiles("w");
                lex->buildEntries(pattern, morpho);
                lex->saveFsa();
                lex->closeFiles();
                return EXIT_SUCCESS;
            }

            case Buildlexicon::CONSULT: {
                lex = new CompactedLexicon(directory, prefix);
                lex->openFiles("r");
                lex->loadFsa();
                lex->loadData();
                lex->consult();
                lex->closeFiles();
                return EXIT_SUCCESS;
            }

            case Buildlexicon::LIST: {
                lex = new CompactedLexicon(directory, prefix);
                lex->openFiles("r");
                lex->loadFsa();
                lex->loadData();
                lex->list();
                lex->closeFiles();
                return EXIT_SUCCESS;
            }

            default:
                break;
        }
        usage();
    }
    catch (fatal_exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
