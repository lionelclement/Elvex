/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2018 LABRI, 
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

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <set>
#include <list>
#include "rule.hh"

typedef std::set<class Rule *, Rule::Less> ruleSet;

class Grammar {
private:
  std::set<unsigned int> terminals;
  std::set<unsigned int> nonTerminals;
  ruleSet rules;
  class Term *startTerm;
  class Rule *firstRule;
  unsigned int idMax;
  
 public:
  Grammar(void);
  ~Grammar(void);
  
  std::set<unsigned int> &getTerminals(void);
  std::set<unsigned int> &getNonTerminals(void);
  const ruleSet &getRules(void) const;
  class Term *getStartTerm(void) const;
  class Rule *getFirstRule(void) const;
  const unsigned int *getRefIdMax(void) const;
  void setStartTerm(class Term* startTerm);
  
  ruleSet::const_iterator rulesBegin(void) const;
  ruleSet::const_iterator rulesEnd(void) const;
  bool addRule(class Rule *rule);
  void addNewStartTerm(bool);
  void addNonTerminal(unsigned int);
  void addTerminal(unsigned int);
  void print(std::ostream &, class Gitem *) const;
  bool isTerminal(class Term *) const;
  bool isNonTerminal(class Term *) const;
  void analyseTerms(class Synthesizer&);
#ifdef OUTPUT_XML
  void toXML(const xmlNodePtr);
#endif
  std::list<class Rule *> *findRules(class Term *lhs);
};

#endif // GRAMMAR_H
