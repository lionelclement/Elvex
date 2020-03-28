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

#ifndef COMPACTLEXICON_H
#define COMPACTLEXICON_H

#define MAXSTRING 10000
#define SEP_PREF ""
#define SEP_UW "UNKNOWN"
#define SEP_SUFF "\n"
#define SEP_OR "|"

#include <string>
#include <iostream>     // std::cout
#include <fstream>
#include <sstream>

#include "compact-lexicon-tree.hh"
#include "lexicon.hh"

extern bool isLexString;
extern char *lexString;
extern char *currentLexString;
extern class Entry *localEntry;

class CompactLexicon {

   friend CompactLexiconTree;

private:

   std::string directoryName;
   std::string fileName;
   FILE *fsaFile;
   std::string fsaFileName;
   FILE *dataFile;
   std::string dataFileName;
   std::ifstream inputFile = std::ifstream();
   std::istream *inputStream = &std::cin;
   size_t InputFileStreamSize;
   CompactLexiconTree *compactLexicon;

public:
   char *buffer;
   struct CompactLexiconFsa *fsa;
   struct CompactLexiconBuffer *info;
   unsigned long int init;
   class CompactLexiconTree *lexiconInit;

private:
  void addForms(Lexicon &lexicon, std::string line, std::string form, std::string input, std::string pos, std::string predicate , std::string fs);

public:
   CompactLexicon(std::string directoryName, std::string fileName, const std::string inputFileName);
   CompactLexicon(std::string directoryName, std::string fileName);
   unsigned long int _getInit(void) const {
      return init;
   }
   ;
   char *_getBuffer(void) const {
      return buffer;
   }
   ;
   struct CompactLexiconBuffer *_getInfo(void) {
      return info;
   }
   ;
   void printResults(std::ostream &, unsigned long int index, bool sep) const;
   unsigned long int searchStatic(unsigned long int index, std::string) const;
   void saveFsa();
   void loadFsa();
   void openFiles(std::string mode);
   void closeFiles();
   void buildPredEntries(class Lexicon &pattern);
   void buildFormEntries(class Lexicon &pattern);
   void loadData(void);
   void consult(void);
};
#endif // COMPACTLEXICON_H
