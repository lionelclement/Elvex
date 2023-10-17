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

#ifndef ELVEX_ITEM_H
#define ELVEX_ITEM_H

#include <climits>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include "facade.hpp"
#include "shared_ptr.hpp"
#include "serializable.hpp"
#include "parser.hpp"
#include "generator.hpp"

class Item : public Facade,
             public Serializable
{

public:
    typedef std::unordered_set<uint32_t> set_of_uint32_t;
    static uint32_t TERM_NA;
    static uint8_t INDEX_NA;

private:
    rulePtr rule;                                            // the grammar rule
    uint8_t index;                                           // the \bullet position
    std::vector<uint8_t> indexTerms;                         // term in a disjunction
    statementsPtr statements;                                // the semantics
    set_of_uint32_t refs;                                    // set of items from which this one is derived
    std::vector<bool> seen;                                  // seen flags
    std::vector<uint8_t> ranges;                             // ranges
    featuresPtr inheritedFeatures;                           // ↑
    listFeaturesPtr inheritedSonFeatures;                    // ↓
    featuresPtr synthesizedFeatures;                         // ⇑
    listFeaturesPtr synthesizedSonFeatures;                  // ⇓
    std::vector<class ForestIdentifier *> forestIdentifiers; // forest identifiers
    environmentPtr environment;                              // variable environment

    bool s_id = false, s_ruleId = false, s_rule = false, s_flags = false, s_refs = false,
         s_seen = false, s_item = true, s_index = false, s_indexTerms = false, s_terms = false,
         s_ranges = false, s_forestIdentifiers = false, s_inheritedFeatures = true,
         s_inheritedSonFeatures = true, s_synthesizedFeatures = true,
         s_synthesizedSonFeatures = true, s_statements = true, s_environment = true;

    void makeSerialString(void);

public:
    Item(rulePtr rule, uint8_t index, statementsPtr statements);

    Item(const rulePtr &rule, uint8_t index, uint8_t indexTerm, statementsPtr statements);

    Item(const rulePtr &rule, uint8_t index, std::vector<uint8_t> &indexTerms, statementsPtr statements);

    ~Item();

    // static constructors

    static class Item *create(const rulePtr &, uint8_t index = INDEX_NA, uint8_t indexTerm = INDEX_NA, statementsPtr = statementsPtr());

    static class Item *create(const rulePtr &, uint8_t index, std::vector<uint8_t> &indexTerms, statementsPtr);

    uint32_t getCurrentTerm(void) const;

    // getters

    termsPtr getCurrentTerms() const;

    rulePtr getRule(void) const;

    uint8_t getIndex(void) const;

    std::vector<uint8_t> &getIndexTerms(void);

    uint32_t getRuleLhs(void) const;

    std::vector<termsPtr> &getRuleRhs(void) const;

    statementsPtr getStatements(void);

    set_of_uint32_t &getRefs(void);

    listFeaturesPtr getSynthesizedSonFeatures(void);

    listFeaturesPtr getInheritedSonFeatures(void);

    featuresPtr getSynthesizedFeatures() const;

    featuresPtr getInheritedFeatures(void) const;

    environmentPtr getEnvironment() const;

    uint32_t getRuleId(void) const;

    std::string getRuleIdStr(void) const;

    uint32_t getRuleLineno() const;

    bool getRuleTrace(void) const;

    std::vector<bool> &getSeen(void);

    // setters

    void setCurrentTerms(termsPtr);

    void setRule(rulePtr);

    void setIndex(uint8_t);

    void setRefs(set_of_uint32_t &);

    void setSynthesizedSonFeatures(listFeaturesPtr);

    void setInheritedSonFeatures(listFeaturesPtr);

    void setSynthesizedFeatures(featuresPtr);

    void setInheritedFeatures(featuresPtr);

    void setEnvironment(environmentPtr);

    void setSeen(std::vector<bool> &);

    void setSeen(uint8_t, bool);

    // rule methods

    void rulePrint(std::ostream &, uint8_t index = UINT8_MAX, bool withSemantic = false, bool html = true) const;

    void ruleResetUsages(void);

    const std::string &getRuleFilename() const;

    bool getWithSpaces() const;

    bool getBidirectional() const;

    bool getPermutable() const;

    termsPtr getTerms(uint32_t) const;

    void addRef(uint32_t);

    void addRefs(set_of_uint32_t &);

    bool isSeen(uint8_t) const;

    void addItem(std::unordered_map<uint32_t, class Item *> &, unsigned int, class Item *);

    std::vector<uint8_t> &getRanges(void);

    void addRange(uint8_t);

    void addRanges(std::vector<uint8_t> &);

    std::vector<class ForestIdentifier *> &getForestIdentifiers(void);

    void addForestIdentifiers(unsigned int i, class ForestIdentifier *);

    void addForestIdentifiers(std::vector<class ForestIdentifier *> &);

    void buildSynthesizedFeatures(statementPtr from, class Generator *);

    void buildInheritedSonFeatures(statementPtr from, class Generator *);

    bool addEnvironment(statementPtr from, environmentPtr, bool verbose);

    bool addEnvironment(statementPtr from, environmentPtr, environmentPtr, bool verbose);

    void addStatements(const statementsPtr &);

    void print(std::ostream &) const;

    void renameVariables(uint32_t);

    bool isCompleted(void);

    bool isStarted(void);

    void step(bool &);

    void defaultInheritedSonFeatures(void);

    void apply(Parser &parser, Generator *generator, bool verbose);

    class Item *clone(const std::bitset<MAX_FLAGS> &savedFlags, bool verbose);

    struct Hash
    {
        size_t operator()(class Item *) const;
    };

    struct KeyEqual
    {
        bool operator()(class Item *, class Item *) const;
    };
};

#endif // ELVEX_ITEM_H
