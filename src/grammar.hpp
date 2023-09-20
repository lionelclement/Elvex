/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2020 LABRI,
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI - Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef ELVEX_GRAMMAR_H
#define ELVEX_GRAMMAR_H

#include <set>
#include <list>
#include "shared_ptr.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Grammar
{
public:
    typedef std::list<rulePtr> ruleList;

private:
    std::set<unsigned int> terminals;
    std::set<unsigned int> nonTerminals;
    ruleList rules;
    unsigned int startTerm;
    rulePtr firstRule;
    unsigned int idMax;

public:
    Grammar(void);

    ~Grammar(void);

    std::set<unsigned int> &getTerminals(void);

    std::set<unsigned int> &getNonTerminals(void);

    const ruleList &getRules(void) const;

    unsigned int getStartTerm(void) const;

    rulePtr getFirstRule(void) const;

    const unsigned int *getRefIdMax(void) const;

    void setStartTerm(unsigned int startTerm);

    ruleList::const_iterator rulesBegin(void) const;

    ruleList::const_iterator rulesEnd(void) const;

    void addRule(rulePtr);

    void addNewStartTerm(bool);

    void addNonTerminal(unsigned int);

    void addTerminal(unsigned int);

    void print(std::ostream &) const;

    bool isTerminal(unsigned int) const;

    bool isNonTerminal(unsigned int) const;

    void analyseTerms(class Parser &);

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    std::list<rulePtr> *findRules(unsigned int lhs);
};

#endif // ELVEX_GRAMMAR_H
