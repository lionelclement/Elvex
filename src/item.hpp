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

#ifndef ELVEX_ITEM_H
#define ELVEX_ITEM_H

#include <climits>
#include <set>
#include <vector>
#include <unordered_map>
#include "flags.hpp"
#include "uniq-id.hpp"
#include "shared_ptr.hpp"
#include "serializable.hpp"

class Item :
        public UniqId, public Flags, public Serializable, public std::enable_shared_from_this<class Item> {

private:
    rulePtr rule;
    unsigned int index; // the \bullet position
    std::vector<unsigned int> indexTerms; // which term in a disjunction
    statementsPtr statements;
    std::set<unsigned int> refs; // item from which this one is derived
    std::vector<bool> seen;
    std::vector<unsigned int> ranges;
    featuresPtr inheritedFeatures; //↑
    listFeaturesPtr inheritedSonFeatures; //↓
    featuresPtr synthesizedFeatures; //⇑
    listFeaturesPtr synthesizedSonFeatures; //⇓
    std::vector<forestIdentifierPtr> forestIdentifiers;
    environmentPtr environment;
    bool trace;
    bool s_id = true, s_ruleId = false, s_rule = false, s_flags = false, s_refs = false, s_seen = false, s_item = true, s_index = false, s_indexTerms = false, s_terms = false,
            s_ranges = false, s_forestIdentifiers = false, s_inheritedFeatures = true, s_inheritedSonFeatures = true, s_synthesizedFeatures = true, s_synthesizedSonFeatures = true,
            s_statements = true, s_environment = true;

    Item(rulePtr rule, unsigned int index, statementsPtr statements);

    Item(const rulePtr& rule, unsigned int index, unsigned int indexTerm, statementsPtr statements);

    Item(const rulePtr& rule, unsigned int index, std::vector<unsigned int> &indexTerms, statementsPtr statements);

    void makeSerialString(void);

public:
    ~Item();

    static itemPtr create(const rulePtr&, unsigned int = UINT_MAX, unsigned int = 0, statementsPtr = statementsPtr());

    static itemPtr create(const rulePtr&, unsigned int, std::vector<unsigned int> &, statementsPtr);

    unsigned int getLineno() const;

    const std::string &getFilename() const;

    unsigned int getCurrentTerm(void) const;

    termsPtr getCurrentTerms() const;

    termsPtr getTerms(unsigned int) const;

    void setCurrentTerms(termsPtr);

    rulePtr getRule(void) const;

    void setRule(rulePtr);

    unsigned int getIndex(void) const;

    void setIndex(unsigned int);

    std::vector<unsigned int> &getIndexTerms(void);

    unsigned int getLhs(void) const;

    std::vector<termsPtr> &getRhs(void) const;

    statementsPtr getStatements(void);

    std::set<unsigned int> &getRefs(void);

    void setRefs(std::set<unsigned int> &);

    void addRef(unsigned int);

    void addRefs(std::set<unsigned int> &);

    std::vector<bool> &getSeen(void);

    void setSeen(std::vector<bool> &);

    bool isSeen(unsigned int) const;

    void setSeen(unsigned int, bool);

    void addItem(std::unordered_map<unsigned int, itemPtr> &, unsigned int, itemPtr);

    std::vector<unsigned int> &getRanges(void);

    void addRanges(unsigned int);

    void addRanges(std::vector<unsigned int> &);

    std::vector<forestIdentifierPtr> &getForestIdentifiers(void);

    void addForestIdentifiers(unsigned int i, forestIdentifierPtr);

    void addForestIdentifiers(std::vector<forestIdentifierPtr> &);

    listFeaturesPtr getSynthesizedSonFeatures(void);

    void setSynthesizedSonFeatures(listFeaturesPtr);

    listFeaturesPtr getInheritedSonFeatures(void);

    void setInheritedSonFeatures(listFeaturesPtr);

    featuresPtr getSynthesizedFeatures(void) const;

    void setSynthesizedFeatures(featuresPtr);

    featuresPtr getInheritedFeatures(void) const;

    void setInheritedFeatures(featuresPtr);

    void buildSynthesizedFeatures(class Synthesizer *);

    void buildInheritedSonFeatures(class Synthesizer *);

    environmentPtr getEnvironment(void) const;

    void setEnvironment(environmentPtr);

    void addEnvironment(environmentPtr);

    void addEnvironment(environmentPtr, environmentPtr);

    bool getTrace(void) const;

    void setTrace(bool trace);

    void addStatements(const statementsPtr&);

    void print(std::ostream &) const;

    itemPtr clone(const std::bitset<FLAGS> &savedFlags);

    void renameVariables(size_t);

    bool isCompleted(void);

    bool isStarted(void);

    void successor(/*itemSetPtr, *//*class Synthesizer *, */bool &);

    void defaultInheritedSonFeatures(void);

    void apply(/*itemSetPtr state, */class Parser &parser, class Synthesizer *synthesizer);

    struct hash {
        size_t operator()(itemPtr const&) const;
    };

    struct equal_to {
        bool operator()(itemPtr const&, itemPtr const&) const;
    };
};

#endif // ELVEX_ITEM_H
