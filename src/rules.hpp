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
 * LaBRI -- Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef ELVEX_RULES_H
#define ELVEX_RULES_H

#include <unordered_set>
#include <list>
#include "shared_ptr.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Rules {
public:
    typedef std::list<rulePtr> list_of_rule;
    typedef std::unordered_set<unsigned int> set_of_unsigned_int;

private:
    set_of_unsigned_int terminals;
    set_of_unsigned_int nonTerminals;
    list_of_rule rules;
    unsigned int startTerm;
    rulePtr firstRule;
    unsigned int idMax;

public:
    Rules(void);

    ~Rules(void);

    set_of_unsigned_int& getTerminals(void);

    set_of_unsigned_int& getNonTerminals(void);

    const list_of_rule& getRules(void) const;

    unsigned int getStartTerm(void) const;

    rulePtr getFirstRule(void) const;

    const unsigned int* getRefIdMax(void) const;

    void setStartTerm(unsigned int startTerm);

    list_of_rule::const_iterator cbegin(void) const;

    list_of_rule::const_iterator cend(void) const;

    void addRule(rulePtr);

    void addNewStartTerm(bool);

    void addNonTerminal(unsigned int);

    void addTerminal(unsigned int);

    void print(std::ostream& ) const;

    bool isTerminal(unsigned int) const;

    bool isNonTerminal(unsigned int) const;

    void analyseTerms(class Parser&);

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    list_of_rule* findRules(unsigned int lhs);
};

#endif // ELVEX_RULES_H
