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

#include <stack>
#include <fstream>
#include <string>

#include "forestidentifier.hh"
#include "forestmap.hh"
#include "grammar.hh"
#include "ipointer.hh"
#include "memoizationmap.hh"

#ifndef MAXLENGTH
#define MAXLENGTH 1000
#endif

#ifndef MAXUSAGES
#define MAXUSAGES 1000
#endif

#ifndef MAXCARDINAL
#define MAXCARDINAL 1000
#endif

class Synthesizer {

private:
  class Grammar grammar;
  std::map<unsigned int, itemSetPtr > states;

  // pos => (PRED => entries)
  // verb => (manger => (mangions, mange|mange))
  typedef std::map<unsigned int, std::map<unsigned int, entriesPtr, std::less<unsigned int> >*, std::less<unsigned int> > lexiconType;
  typedef std::map<unsigned int, itemPtr > itemMapType;

  lexiconType lexicon;
  
  // Associe un identifieur de foret à une foret
  class ForestMap forestMap;
  itemMapType itemMap;
  nodePtr nodeRoot;
  featuresPtr startFeatures;
  class Term *startTerm;
  class Lex *compactLexicon;
  entryPtr localEntry; //flying lexical entry
  std::map<std::string, entryPtr > mapLocalEntry;
  unsigned int maxLength;
  unsigned int maxUsages;
  unsigned int maxCardinal;
  std::string lexiconFileName;
  std::string grammarFileName;
  std::string inputFileName;
  std::stack< std::string > bufferNames;
  std::stack< int > linenos;
  
  std::string lexiconString;
  std::string grammarString;
  std::string inputString;
  std::string compactLexiconFileName;
  std::string compactDirectoryName;

  bool reduceAll;
  bool trace;
  bool warning;
  bool random;
  
#ifdef TRACE
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

  Synthesizer(void);
  ~Synthesizer(void);

  class Grammar &getGrammar(void);
  void setGrammar(class Grammar &grammar);
  std::map<unsigned int, itemSetPtr >::const_iterator begin(void) const;
  std::map<unsigned int, itemSetPtr >::const_iterator end(void) const;
  int size(void) const;

  void pushBufferName(std::string);
  std::string popBufferName(void);
  std::string getTopBufferName(void);
  void pushLineno(int);
  int popLineno(void);
  int getTopLineno(void);
  class ForestMap getForestMap(void);
  
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

  void setInputString(std::string);
  void setLexiconString(std::string);
  void setGrammarString(std::string);
  std::string getInputString(void) const;
  std::string getLexiconString(void) const;
  std::string getGrammarString(void) const;

  void setMaxLength(unsigned int);
  void setMaxUsages(unsigned int);
  unsigned int getMaxUsages(void);
  void setMaxCardinal(unsigned int);
  unsigned int getMaxCardinal(void);
  
  class Lex *getCompactLexicon(void) const;
  void setCompactLexicon(class Lex *);

  void setStartFeatures(featuresPtr);
  featuresPtr getStartFeatures(void) const;

  class Term *getStartTerm(void) const;
  void setStartTerm(class Term *);

  
#ifdef OUTPUT_XML
  void setOutXML(char *);
  char *getOutXML(void) const;
#endif

#ifdef TRACE
  void setTraceStage(bool);
  void setTraceClose(bool);
  void setTraceShift(bool);
  void setTraceReduce(bool);
  void setTraceAction(bool);
  bool getTraceStage(void);
  bool getTraceClose(void);
  bool getTraceShift(void);
  bool getTraceReduce(void);
  bool getTraceAction(void);

#endif

  nodePtr getNodeRoot(void);
  lexiconType &getLexicon(void);
  void setLexicon(lexiconType &);
  lexiconType::const_iterator findLexicon(const unsigned int i) const;
  lexiconType::const_iterator beginLexicon(void) const;
  lexiconType::const_iterator endLexicon(void) const;

  entryPtr getLocalEntry(void) const;
  void setLocalEntry(entryPtr);

  void printLexicon(std::ostream &) const;

  const bool insertItemMap(const itemPtr);
  void eraseItemMap(const unsigned int);
  itemPtr getItemMap(const unsigned int);

  const bool getTrace(void) const;
  void setTrace(const bool);
  const bool getVerbose(void) const;
  void setVerbose(const bool);
  const bool getReduceAll(void) const;
  void setReduceAll(bool);
  void setRandom(bool);
  bool getRandom(void) const;

private:
  void printState(std::ostream &, itemSetPtr);
  void close(itemSetPtr, unsigned int);
  bool shift(itemSetPtr, unsigned int);
  
 public:  
  itemPtr createItem(itemPtr, unsigned int);
  void parseFile(std::string);
  int parseString(std::string, std::string);
  void generate(void);
  const entriesPtr findCompactLexicon(const unsigned int code, const unsigned int pred);
#ifdef MEMOIZATION
#ifdef MEMOIZATION_SHIFT
  std::string keyMemoization(itemPtr);
#endif
#ifdef MEMOIZATION_REDUCE
  std::string keyMemoization(itemPtr, itemPtr);
#endif
#endif
  
};


#endif // SYNTHESIZER_H
