/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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

/**
 * Grammar rule collection with terminal/nonterminal classification.
 * Provides rule lookup and term analysis for the chart generator.
 */
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

    /** Collect all symbols occurring on the left-hand side of a rule. */
    void collectNonTerminals();

    /** Register terminal symbols and prime the parser's lexical cache. */
    void collectTerminals(class Parser &);
    void prepareTerminalCache(class Parser &, uint32_t code);

    /** Emit the existing HTML diagnostics without changing their order. */
    void printSymbols(std::ostream &, const set_of_uint32_t &) const;
    void printRuleRows(std::ostream &) const;

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

    /** Classify grammar symbols and prepare terminal/nonterminal lookups. */
    void analyseTerms(class Parser &);

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    /** Find productions whose left-hand side matches a nonterminal. */
    list_of_rule *findRules(uint32_t lhs);
};

#endif // ELVEX_RULES_H
