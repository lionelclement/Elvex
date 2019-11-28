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

#ifndef PARSER_H
#define PARSER_H

#include <functional>
#include <string>
#include <map>
#include <unordered_map>
#include <deque>
#include "ipointer.hh"
#include "grammar.hh"
#include "entry.hh"
#include "entries.hh"
#include "features.hh"

class Parser {

public:
   typedef std::unordered_map<std::string, entryPtr, std::hash<std::string>, std::equal_to<std::string> > entry_map;
   // pos => (PRED => entries)
   // verb => (manger => (mangions, mange|mange))
   typedef std::map<unsigned int, entriesPtr> entries_map;
   typedef std::map<unsigned int, entries_map *> entries_map_map;
   typedef std::unordered_map<std::string, featuresPtr> features_map;

private:
   Grammar grammar;
   entries_map_map lexicon;
   entry_map mapLocalEntry;
   features_map macros;
   featuresPtr startFeatures;
   termPtr startTerm;
   bool verbose;
   featuresPtr localFeatures;
   std::deque<std::string> bufferNames;
   std::deque<unsigned int> linenos;

public:
   Parser(void);
   ~Parser(void);

   void pushBufferName(std::string);
   std::string popBufferName(void);

   void pushLineno(unsigned int);
   unsigned int popLineno(void);
   unsigned int getTopLineno(void);

   class Grammar &getGrammar(void);

   std::string getTopBufferName(void);

   termPtr getStartTerm(void) const;
   void setStartTerm(termPtr);

   void setStartFeatures(featuresPtr);
   featuresPtr getStartFeatures(void) const;

   featuresPtr getLocalFeatures(void) const;
   void setLocalFeatures(featuresPtr);

   entries_map_map &getLexicon(void);
   void setLexicon(entries_map_map &);
   entries_map_map::const_iterator findLexicon(unsigned int i) const;
   entries_map_map::const_iterator beginLexicon(void) const;
   entries_map_map::const_iterator endLexicon(void) const;

   void setVerbose(bool);
   bool getVerbose(void) const;

   entry_map &getMapLocalEntry(void);

   void printLexicon(std::ostream &) const;

   void addMacros(std::string, featuresPtr);
   featuresPtr findMacros(std::string);

public:
   unsigned int parseFile(std::string prefix, std::string fileName);
public:
   unsigned int _parseBuffer(std::string prefix, std::string buffer, std::string bufferName);
private:
   unsigned int parseString(std::string buffer);
};

#endif // PARSER_H
