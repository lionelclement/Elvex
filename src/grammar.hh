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

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <set>
#include <list>
#include "rule.hh"

typedef std::list<rulePtr> ruleList;

class Grammar {
private:
	std::set<unsigned int> terminals;
	std::set<unsigned int> nonTerminals;
	ruleList rules;
	termPtr startTerm;
	rulePtr firstRule;
	unsigned int idMax;

public:
	Grammar(void);
	~Grammar(void);

	std::set<unsigned int> &getTerminals(void);
	std::set<unsigned int> &getNonTerminals(void);
	const ruleList &getRules(void) const;
	termPtr getStartTerm(void) const;
	rulePtr getFirstRule(void) const;
	const unsigned int *getRefIdMax(void) const;
	void setStartTerm(termPtr startTerm);

	ruleList::const_iterator rulesBegin(void) const;
	ruleList::const_iterator rulesEnd(void) const;
	void addRule(rulePtr);
	void addNewStartTerm(bool);
	void addNonTerminal(unsigned int);
	void addTerminal(unsigned int);
	void print(std::ostream &, class Gitem *) const;
	bool isTerminal(termPtr) const;
	bool isNonTerminal(termPtr) const;
	void analyseTerms(class Synthesizer&);
#ifdef OUTPUT_XML
	void toXML(xmlNodePtr);
#endif
	std::list<rulePtr> *findRules(termPtr lhs);
};

#endif // GRAMMAR_H
