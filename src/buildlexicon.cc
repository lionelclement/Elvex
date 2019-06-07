/* **************************************************
*
* ELVEX
*
* Copyright 2019 LABRI,
* CNRS (UMR 5800), the University of Bordeaux,
* and the Bordeaux INP
*
* Author: Lionel Clément,
* Labri -- 351, cours de la Libération
* 33405 Talence Cedex - France
* lionel.clement@labri.fr
*
* This file is part of ELVEX.
*
************************************************** */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cmath>
#include <sys/stat.h>
#include <string.h>

#include "buildlexicon.hh"
#include "info.hh"
#include "lex.hh"

/* **************************************************
*
************************************************** */
void
usage() {
  std::cerr <<
  "Usage: buildlexiconmain [global-option] <build|consult|test> <input>\n"
  "Global options:\n"
  "-h|--help                              print this\n"
  "-v|--version                           print version\n"
  "-f <filePrefix>\n"
  "-d <directory>" << std::endl;
  exit (EXIT_SUCCESS);
}

/* **************************************************
*
************************************************** */
int main(int argn,
  char** argv) {
    try {
      class Lex lex;

      int mode=0;
      std::string inputFileName="-";
      char prefix[MAXSTRING];
      char directory[MAXSTRING];
      if (argn > 1) {
        // generic options
        for (int i = 1; argv[i]; i++) {
          if (argv[i][0] == '-') {
            if (!strcmp(argv[i]+1, "f")) {
              if ((i+1 >= argn) || argv[i+1][0] == '-')
                usage();
              else
                strcpy (prefix, argv[++i]);
            }
            else if (!strcmp(argv[i]+1, "d")) {
              if ((i+1 >= argn) || argv[i+1][0] == '-')
                usage();
              else
                strcpy (directory, argv[++i]);
            }
            else if (!strcmp(argv[i]+1, "v") || !strcmp(argv[i]+1, "-version")) {
              std::cerr << PACKAGE_NAME << PACKAGE_VERSION << std::endl;
              return EXIT_SUCCESS;

            }
            else if (!strcmp(argv[i]+1, "h") || !strcmp(argv[i]+1, "-help"))
              usage();
            else
              usage();
          }
          else {
            if (!strcmp(argv[i], "build"))
              mode=1;
            else if (!strcmp(argv[i], "consult"))
              mode=2;
            else if (!strcmp(argv[i], "test"))
              mode=3;
            else
              inputFileName=argv[i];
          }
        }
      }
      switch (mode){
        case 1:{
          std::ifstream inputFile;
          if (inputFileName!=""){
            inputFile.open(inputFileName.c_str());
            if (inputFile.is_open()) {
              if (!lex.build(directory, prefix, &inputFile))
                return EXIT_FAILURE;
              inputFile.close();

            }
            else {
              std::cerr << "Unable to open file";
              return EXIT_FAILURE;
            }
          }
          else {
            if (!lex.build(directory, prefix, &std::cin))
              return EXIT_FAILURE;
          }
          return EXIT_SUCCESS;
        }
        break;
        case 2:
          if (!lex.load(directory, prefix))
            return EXIT_FAILURE;
          if (!lex.consult(inputFileName))
            return EXIT_FAILURE;
          return EXIT_SUCCESS;
          break;
        case 3:
          if (!lex.load(directory, prefix))
            return EXIT_FAILURE;
          return EXIT_SUCCESS;
          break;
      }
      usage();
    }
    catch (std::string& message){
      std::cout << message << std::endl;
    }
    return EXIT_SUCCESS;
  }
