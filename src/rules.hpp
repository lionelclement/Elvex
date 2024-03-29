/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2023 LABRI,
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI - Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
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

class Rules
{
public:
    typedef std::list<rulePtr> list_of_rule;
    typedef std::unordered_set<uint32_t> set_of_uint32_t;

private:
    set_of_uint32_t terminals;
    set_of_uint32_t nonTerminals;
    list_of_rule rules;
    uint32_t startTerm;
    rulePtr firstRule;
    uint32_t idMax;

public:
    Rules(void);

    ~Rules(void);

    set_of_uint32_t &getTerminals(void);

    set_of_uint32_t &getNonTerminals(void);

    const list_of_rule &getRules(void) const;

    uint32_t getStartTerm(void) const;

    rulePtr getFirstRule(void) const;

    const uint32_t *getRefIdMax(void) const;

    void setStartTerm(uint32_t startTerm);

    list_of_rule::const_iterator cbegin(void) const;

    list_of_rule::const_iterator cend(void) const;

    void addRule(rulePtr);

    void addNonTerminal(uint32_t);

    void addTerminal(uint32_t);

    void print(std::ostream &) const;

    bool isTerminal(uint32_t) const;

    bool isNonTerminal(uint32_t) const;

    void analyseTerms(class Parser &);

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    list_of_rule *findRules(uint32_t lhs);
};

#endif // ELVEX_RULES_H
