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
 * LaBRI -- Université Bordeaux
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

class Item : public Facade,
             public Serializable
{

public:
    typedef std::unordered_set<unsigned int> set_of_unsigned_int;
    typedef set_of_unsigned_int::const_iterator set_of_unsigned_int_const_iterator;
    static  unsigned char NA;
    
private:

    rulePtr rule;                                            // the grammar rule
    unsigned char index;                                      // the \bullet position
    std::vector<unsigned char> indexTerms;                    // term in a disjunction
    statementsPtr statements;                                // the semantics
    set_of_unsigned_int refs;                                // set of items from which this one is derived
    std::vector<bool> seen;                                  // seen flags
    std::vector<unsigned char> ranges;                        // ranges
    featuresPtr inheritedFeatures;                           // ↑
    listFeaturesPtr inheritedSonFeatures;                    // ↓
    featuresPtr synthesizedFeatures;                         // ⇑
    listFeaturesPtr synthesizedSonFeatures;                  // ⇓
    std::vector<class ForestIdentifier *> forestIdentifiers; // forest identifiers
    environmentPtr environment;                              // variable environment

    bool s_id = true, s_ruleId = false, s_rule = false, s_flags = false, s_refs = false,
         s_seen = false, s_item = true, s_index = false, s_indexTerms = false, s_terms = false,
         s_ranges = false, s_forestIdentifiers = false, s_inheritedFeatures = true,
         s_inheritedSonFeatures = true, s_synthesizedFeatures = true,
         s_synthesizedSonFeatures = true, s_statements = true, s_environment = true;

    Item(rulePtr rule, unsigned char index, statementsPtr statements);

    Item(const rulePtr &rule, unsigned char index, unsigned int indexTerm, statementsPtr statements);

    Item(const rulePtr &rule, unsigned char index, std::vector<unsigned char> &indexTerms, statementsPtr statements);

    void makeSerialString(void);

public:
    ~Item();

    // static constructors

    static class Item *create(const rulePtr &, unsigned char index = NA, unsigned char indexTerm = 0, statementsPtr = statementsPtr());

    static class Item *create(const rulePtr &, unsigned char index, std::vector<unsigned char> &indexTerms, statementsPtr);

    unsigned int getCurrentTerm(void) const;

    // getters

    termsPtr getCurrentTerms() const;

    rulePtr getRule(void) const;

    unsigned char getIndex(void) const;

    std::vector<unsigned char> &getIndexTerms(void);

    unsigned int getRuleLhs(void) const;

    std::vector<termsPtr> &getRuleRhs(void) const;

    statementsPtr getStatements(void);

    set_of_unsigned_int &getRefs(void);

    listFeaturesPtr getSynthesizedSonFeatures(void);

    listFeaturesPtr getInheritedSonFeatures(void);

    featuresPtr getSynthesizedFeatures() const;

    featuresPtr getInheritedFeatures(void) const;

    environmentPtr getEnvironment() const;

    unsigned int getRuleId(void) const;

    unsigned int getRuleLineno() const;

    bool getRuleTrace(void) const;

    std::vector<bool> &getSeen(void);

    // setters

    void setCurrentTerms(termsPtr);

    void setRule(rulePtr);

    void setIndex(unsigned char);

    void setRefs(set_of_unsigned_int &);

    void setSynthesizedSonFeatures(listFeaturesPtr);

    void setInheritedSonFeatures(listFeaturesPtr);

    void setSynthesizedFeatures(featuresPtr);

    void setInheritedFeatures(featuresPtr);

    void setEnvironment(environmentPtr);

    void setSeen(std::vector<bool> &);

    void setSeen(unsigned int, bool);

    // rule methods

    void rulePrint(std::ostream &, unsigned int index = UINT_MAX, bool withSemantic = false, bool html = true) const;

    void ruleResetUsages(void);

    const std::string &getRuleFilename() const;

    bool getWithSpaces() const;

    bool getBidirectional() const;

    bool getPermutable() const;

    termsPtr getTerms(unsigned int) const;

    void addRef(unsigned int);

    void addRefs(set_of_unsigned_int &);

    bool isSeen(unsigned int) const;

    void addItem(std::unordered_map<unsigned int, class Item *> &, unsigned int, class Item *);

    std::vector<unsigned char> &getRanges(void);

    void addRange(unsigned char);

    void addRanges(std::vector<unsigned char> &);

    std::vector<class ForestIdentifier *> &getForestIdentifiers(void);

    void addForestIdentifiers(unsigned int i, class ForestIdentifier *);

    void addForestIdentifiers(std::vector<class ForestIdentifier *> &);

    void buildSynthesizedFeatures(statementPtr from, class Generator *);

    void buildInheritedSonFeatures(statementPtr from, class Generator *);

    bool addEnvironment(statementPtr from, environmentPtr);

    bool addEnvironment(statementPtr from, environmentPtr, environmentPtr);

    void addStatements(const statementsPtr &);

    void print(std::ostream &) const;

    void renameVariables(size_t);

    bool isCompleted(void);

    bool isStarted(void);

    void step(bool &);

    void defaultInheritedSonFeatures(void);

    void apply(class Parser& parser, class Generator* synthesizer);

    class Item* clone(const std::bitset<FLAGS>& savedFlags);

    struct hash
    {
        size_t operator()(class Item *) const;
    };

    struct equal_to
    {
        bool operator()(class Item *, class Item *) const;
    };
};

#endif // ELVEX_ITEM_H
