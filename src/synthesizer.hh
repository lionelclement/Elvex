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
#include <unordered_map>

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

#ifndef MAXATTEMPTS
#define MAXATTEMPTS 1000
#endif

class Synthesizer {

public:
  typedef std::unordered_map<std::string const, entryPtr, std::hash<std::string>, std::equal_to<std::string> > entry_map;
  // pos => (PRED => entries)
  // verb => (manger => (mangions, mange|mange))
  typedef std::map< unsigned int, entriesPtr > entries_map;
  typedef std::map< unsigned int, entries_map * > entries_map_map;
  typedef std::map< unsigned int, itemPtr > item_map;
  typedef std::map< unsigned int, itemSetPtr > itemSet_map;
  typedef std::unordered_map<std::string, featuresPtr > features_map;
  
private:
  class Grammar grammar;
  itemSet_map states;

  entries_map_map lexicon;
  
  // Associe un identifieur de foret à une foret
  class ForestMap forestMap;
  item_map itemMap;
  nodePtr nodeRoot;
  featuresPtr startFeatures;
  termPtr startTerm;
  class Lex *compactLexicon;
  entryPtr localEntry; //flying lexical entry
  entry_map mapLocalEntry;
  unsigned int maxLength;
  unsigned int maxUsages;
  unsigned int maxCardinal;
  std::string lexiconFileName;
  std::string grammarFileName;
  std::string inputFileName;
  std::stack< std::string > bufferNames;
  std::stack< unsigned int > linenos;

  std::list<std::string> inputs;

  features_map macros;

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
  itemSet_map::const_iterator begin(void) const;
  itemSet_map::const_iterator end(void) const;
  size_t size(void) const;

  void pushBufferName(std::string);
  std::string popBufferName(void);
  std::string getTopBufferName(void);
  void pushLineno(unsigned int);
  unsigned int popLineno(void);
  unsigned int getTopLineno(void);
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

  termPtr getStartTerm(void) const;
  void setStartTerm(termPtr );

  
  void addInput(std::string);

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
  entries_map_map &getLexicon(void);
  void setLexicon(entries_map_map &);
  entries_map_map::const_iterator findLexicon(const unsigned int i) const;
  entries_map_map::const_iterator beginLexicon(void) const;
  entries_map_map::const_iterator endLexicon(void) const;

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

  void printState(std::ostream &, itemSetPtr);
  void close(itemSetPtr, unsigned int);
  bool shift(itemSetPtr, unsigned int);
  
  itemPtr createItem(itemPtr, unsigned int);
  void parseFile(std::string);
  unsigned int parseString(std::string, std::string);
  void generate(void);
  const entriesPtr findCompactLexicon(const unsigned int code, const unsigned int pred);
#ifdef MEMOIZATION
#ifdef MEMOIZATION_SHIFT
  std::string keyMemoization(itemPtr const);
#endif
#ifdef MEMOIZATION_REDUCE
  std::string keyMemoization(itemPtr const, itemPtr const);
#endif
#endif
  void addMacros(std::string, featuresPtr);
  featuresPtr findMacros(std::string);

};


#endif // SYNTHESIZER_H
