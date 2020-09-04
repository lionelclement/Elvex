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

#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <map>
#include "shared_ptr.hh"
#include "forestmap.hh"
#include "memoization-map.hh"
#include "parser.hh"

#ifndef MAXLENGTH
#define MAXLENGTH 1000
#endif

#ifndef MAXUSAGES
#define MAXUSAGES 1000
#endif

#ifndef MAXCARDINAL
#define MAXCARDINAL 1000
#endif

#ifndef MAXATTEMPTS
#define MAXATTEMPTS 3000
#endif

class Synthesizer {

public:
   typedef std::map<unsigned int, itemPtr> Item_map;
   typedef std::map<unsigned int, itemSetPtr> ItemSet_map;

private:
   ItemSet_map states;
   ForestMap forestMap;
   Item_map itemMap;
   nodePtr nodeRoot;
   class CompactLexicon *compactLexicon;
   unsigned int maxLength;
   unsigned int maxUsages;
   unsigned int maxCardinal;
   std::string lexiconFileName;
   std::string grammarFileName;
   std::string inputFileName;

   std::list<std::string> inputs;

   std::string compactLexiconFileName;
   std::string compactDirectoryName;

   bool reduceAll;
   bool trace;
   bool warning;
   bool random;
   bool one;
   int attempsRandom;

#ifdef TRACE_OPTION
   bool traceInit;
   bool traceStage;
   bool traceClose;
   bool traceShift;
   bool traceReduce;
   bool traceAction;
#endif

#ifdef OUTPUT_XML
   char *outXML;
#endif

#ifdef MEMOIZATION
   MemoizationMap memoizedMap;
#endif

public:

   Synthesizer();
   ~Synthesizer(void);

   ItemSet_map::const_iterator begin(void) const;
   ItemSet_map::const_iterator end(void) const;
   size_t size(void) const;

   class ForestMap getForestMap(void);
   std::list<std::string> &getInputs(void);

   void setInputFileName(char *);
   void setLexiconFileName(char *);
   void setGrammarFileName(char *);
   void setCompactLexiconFileName(char *);
   void setCompactDirectoryName(char *);
   std::string getInputFileName(void) const;
   std::string getLexiconFileName(void) const;
   std::string getCompactLexiconFileName(void) const;
   std::string getCompactDirectoryName(void) const;
   std::string getGrammarFileName(void) const;

   void setMaxLength(unsigned int);
   void setMaxUsages(unsigned int);
   unsigned int getMaxUsages(void);
   void setMaxCardinal(unsigned int);
   unsigned int getMaxCardinal(void);

   class CompactLexicon *getCompactLexicon(void) const;
   void setCompactLexicon(class CompactLexicon *);

   void addInput(std::string);

#ifdef OUTPUT_XML
   void setOutXML(char *);
   char *getOutXML(void) const;
#endif

#ifdef TRACE_OPTION
   void setTraceInit(bool);
   void setTraceStage(bool);
   void setTraceClose(bool);
   void setTraceShift(bool);
   void setTraceReduce(bool);
   void setTraceAction(bool);
   bool getTraceInit(void);
   bool getTraceStage(void);
   bool getTraceClose(void);
   bool getTraceShift(void);
   bool getTraceReduce(void);
   bool getTraceAction(void);
#endif

   nodePtr getNodeRoot(void);
   const bool insertItemMap(const itemPtr);
   void eraseItemMap(const unsigned int);
   itemPtr getItemMap(const unsigned int);

   bool getTrace(void) const;
   void setTrace(const bool);
   const bool getReduceAll(void) const;
   void setReduceAll(bool);
   void setRandom(bool);
   bool getRandom(void) const;
   void setOne(bool);
   bool getOne(void) const;

   void printState(std::ostream &, itemSetPtr);
   void close(class Parser &, itemSetPtr, unsigned int);
   bool shift(class Parser &, itemSetPtr, unsigned int);
   void clear(void);

   itemPtr createItem(itemPtr, unsigned int);
   void generate(class Parser &);
   const entriesPtr findCompactLexicon(class Parser &, unsigned int code, const std::string str, const unsigned int pred);
#ifdef MEMOIZATION
   std::string keyMemoization(itemPtr const, itemPtr const);
#endif
};

#endif // SYNTHESIZER_H
