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

#define MAXSTRING 100000
#define SEP_PREF ""
#define SEP_UW "UNKNOWN"
#define SEP_SUFF "\n"
#define SEP_OR "|"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "compact-lexicon-tree.hh"
#include "lexicon.hh"

extern bool isLexString;
extern char *lexString;
extern char *currentLexString;
extern class Entry *localEntry;

class CompactLexicon {

private:

   std::string directoryName;
   std::string fileName;
   FILE *fsaFile;
   std::string fsaFileName;
   FILE *dataFile;
   std::string dataFileName;
   std::istream *inputStream = &std::cin;
   CompactLexiconTree *compactLexicon;

public:
   char *buffer;
   struct CompactLexiconFsa *fsa;
   struct CompactLexiconBuffer *info;
   unsigned long int init;
   class CompactLexiconTree *lexiconInit;

public:
   CompactLexicon(std::string directoryName, std::string fileName);
   void printResults(std::ostream &, unsigned long int index, bool sep) const;
   unsigned long int searchStatic(unsigned long int index, std::string) const;
   void saveFsa();
   void loadFsa();
   void openFiles(std::string mode);
   void closeFiles();
   std::string unif(std::string fs1, std::string fs2);
   void addToData(std::string entry, std::string form, std::string features);
   void addPattern(Lexicon &pattern, Lexicon &morpho, std::string input, std::string fs, std::string lemma, std::string pos);
   void addForms(std::string input, std::string inputSearch, std::string features, Lexicon &pattern, Lexicon &morpho);
   void buildEntries(class Lexicon &pattern, class Lexicon &morpho);
   void loadData(void);
   void consult(void);
};
#endif // COMPACTLEXICON_H
