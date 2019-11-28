/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cmath>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "buildlexicon.hh"
#include "compact-lexicon.hh"
#include "compact-lexicon-info.hh"
#include "lexicon.hh"
#include "messages.hh"
#include "synthesizer.hh"

#ifndef PACKAGE_NAME
#define PACKAGE_NAME "elvex"
#endif

#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION "?.?.?"
#endif

Parser parser;

/* **************************************************
 *
 ************************************************** */
void usage() {
   std::cerr
         << "Usage: buildlexiconmain [global-option] <build|consult> <input>\n\
\tGlobal options:\n\
\t-h|--help                              print this\n\
\t-v|--version                           print version\n\
\t-compactLexiconDirectory <directory>\n\
\t-compactLexiconFile <file>\n\
\t-patternFile <file>"
         << std::endl;
   exit(EXIT_SUCCESS);
}

/* **************************************************
 *
 ************************************************** */
int main(int argn, char** argv) {
   try {
      CompactLexicon *lex;
      Buildlexicon::Choice mode = Buildlexicon::NONE;
      std::string inputFileName = std::string();
      std::string prefix;
      std::string directory;
      std::string patternFile = std::string();
      class Lexicon posPredLexicon = Lexicon();
      class Lexicon predLexicon = Lexicon();

      if (argn > 1) {
         // generic options
         for (unsigned int arg = 1; argv[arg]; ++arg) {
            if (argv[arg][0] == '-') {

               if (!strcmp(argv[arg] + 1, "v") || !strcmp(argv[arg] + 1, "-version")) {
                  std::cout << PACKAGE_VERSION << std::endl;
                  return EXIT_SUCCESS;
               }

               else if (!strcmp(argv[arg] + 1, "h") || !strcmp(argv[arg] + 1, "-help")) {
                  usage();
                  return EXIT_SUCCESS;
               }

               else if (!strcmp(argv[arg] + 1, "compactLexiconFile")) {
                  prefix = std::string(argv[++arg]);
               }

               else if (!strcmp(argv[arg] + 1, "compactLexiconDirectory")) {
                  directory = std::string(argv[++arg]);
               }

               else if (!strcmp(argv[arg] + 1, "patternFile")) {
                  patternFile = std::string(argv[++arg]);
               }
            }
            else {
               if (!strcmp(argv[arg], "build"))
                  mode = Buildlexicon::BUILD;
               else if (!strcmp(argv[arg], "consult"))
                  mode = Buildlexicon::CONSULT;
               else
                  inputFileName = argv[arg];
            }
         }
      }

      if (patternFile.size()) {
         std::ifstream inputFile;
         inputFile.open(patternFile.c_str());
         char line[MAXSTRING];
         while (inputFile.getline(line, MAXSTRING)) {
            if (strchr(line, '\t') && !strchr(line, '#')) {
               char pos[MAXSTRING];
               strcpy(pos, line);
               char *rhs = strchr(pos, '\t');
               *rhs = 0;

               char line2[MAXSTRING];
               strcpy(line2, line);
               char *lemma = strchr(line2, '\t') + 1;
               rhs = strchr(lemma, '\t');
               *rhs = 0;

               char line3[MAXSTRING];
               strcpy(line3, line);
               char *predicate = strchr(line3, '\t') + 1;
               predicate = strchr(predicate, '\t') + 1;
               rhs = strchr(predicate, '\t');
               *rhs = 0;

               char line4[MAXSTRING];
               strcpy(line4, line);
               char *fs = strchr(line4, '\t') + 1;
               fs = strchr(fs, '\t') + 1;
               fs = strchr(fs, '\t') + 1;

               //std::cerr << "/pos:/" << pos << '/' << std::endl;
               //std::cerr << "/predicate:/" << predicate << '/' << std::endl;
               //std::cerr << "/lemma:/" << lemma << '/' << std::endl;
               //std::cerr << "/fs:/" << fs << '/' << std::endl;

               std::stringstream stream;
               stream << pos << "#_" << predicate;
               std::string input = stream.str();

               stream.str("");
               stream << lemma << '#' << fs;
               std::string output = stream.str();

               //std::cerr << "/input:/" << input << '/' << std::endl;
               //std::cerr << "/output:/" << output << '/' << std::endl;

               posPredLexicon.add(input, output);

               stream.str("");
               stream << "_" << predicate;
               std::string input2 = stream.str();

               stream.str("");
               stream << fs;
               std::string output2 = stream.str();

               predLexicon.add(input2, output2);

            }
         }
      }

      switch (mode) {

         case Buildlexicon::BUILD: {
            if (inputFileName != "") {
               std::ifstream inputFile = std::ifstream();
               inputFile.open(inputFileName.c_str());
               if (inputFile.is_open()) {
                  lex = new CompactLexicon(directory, prefix, inputFileName);
                  lex->openFiles("w");
                  lex->buildPredEntries(predLexicon);
                  lex->buildFormEntries(posPredLexicon);
                  lex->saveFsa();
                  lex->closeFiles();
                  inputFile.close();
               }
               else {
                  std::cerr << "Unable to open file";
                  return EXIT_FAILURE;
               }
            }
            else {
               UNEXPECTED
            }
            return EXIT_SUCCESS;
         }
            break;

         case Buildlexicon::CONSULT: {
            lex = new CompactLexicon(directory, prefix, inputFileName);
            lex->openFiles("r");
            lex->loadFsa();
            lex->loadData();
            lex->consult();
            lex->closeFiles();
            return EXIT_SUCCESS;
         }
            break;

         default:
            break;
      }
      usage();
   }
   catch (std::string &message) {
      std::cout << message << std::endl;
   }
   return EXIT_SUCCESS;
}
