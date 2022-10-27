/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI, 
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

#include <unordered_set>
#include <vector>
#include <climits>
#include "flags.hpp"
#include "uniq_id.hpp"
#include "shared_ptr.hpp"
#include "serializable.hpp"

class Item :
        public UniqId, 
        public Flags, 
        public Serializable, 
        public std::enable_shared_from_this<class Item> {

public:
    typedef std::unordered_set<unsigned int> set_of_unsigned_int;
    typedef set_of_unsigned_int::const_iterator set_of_unsigned_int_const_iterator ;


private:
    rulePtr rule; // the grammar rule
    unsigned int index; // the actual terms (UINT_MAX when not positionned)
    std::vector<unsigned int> indexTerms; // the actual term in disjunction for each terms (UINT_MAX when not positionned)
    statementsPtr statements; // the semantics
    set_of_unsigned_int refs;  // set of items from which this one is derived
    std::vector<bool> seen; // seen flags
    std::vector<unsigned int> ranges; // ranges
    featuresPtr inheritedFeatures; // ↑
    listFeaturesPtr inheritedSonFeatures; // ↓
    featuresPtr synthesizedFeatures; // ⇑
    listFeaturesPtr synthesizedSonFeatures; // ⇓
    std::vector<forestIdentifierPtr> forestIdentifiers; // forest identifiers
    environmentPtr environment; // variable environment

    // trace flags:
    bool s_id = true, s_ruleId = false, s_rule = false, s_flags = false, s_refs = false, 
        s_seen = false, s_item = true, s_index = true, s_indexTerms = true, s_currentTerm = false,
        s_ranges = true, s_forestIdentifiers = true, 
        s_inheritedFeatures = false, s_inheritedSonFeatures = true, 
        s_synthesizedFeatures = false,  s_synthesizedSonFeatures = false, 
        s_statements = false, s_environment = false;

    Item(const rulePtr& rule, statementsPtr statements);

    void makeSerialString(void);

public:
    ~Item();

    // static constructors
    
    static itemPtr _create(const rulePtr& rule, statementsPtr statements = statementsPtr());

    // terms[index][0] if terms[index].size()==1 and !terms[index].optionnal(), exception otherwise
    unsigned int currentTerm(void) ;

    // terms[index]
    termsPtr currentTerms() const;

    // getters
    
    rulePtr getRule(void) const;

    unsigned int getIndex(void) const;

    std::vector<unsigned int>& _getIndexTerms(void);

    unsigned int getRuleLhs(void) const;

    std::vector<termsPtr>& _getRuleRhs(void);

    statementsPtr getStatements(void) const;

    set_of_unsigned_int getRefs(void) ;

    listFeaturesPtr getSynthesizedSonFeatures(void) ;

    listFeaturesPtr getInheritedSonFeatures(void) ;

    featuresPtr getSynthesizedFeatures();

    featuresPtr getInheritedFeatures(void) const;

    environmentPtr getEnvironment() const;

    unsigned int getRuleId(void) const;
    
    unsigned int getRuleLineno() const;

    bool getRuleTrace(void) const;

    std::vector<bool>& getSeen(void);

    termsPtr getTerms(unsigned int) const;

    std::vector<unsigned int>& _getRanges(void);

    // setters
    
    void _setCurrentTerms(termsPtr);

    void _setRule(rulePtr);

    void _setRefs(set_of_unsigned_int);

    void _setSynthesizedSonFeatures(listFeaturesPtr);

    void _setInheritedSonFeatures(listFeaturesPtr);

    void _setSynthesizedFeatures(featuresPtr);

    void _setInheritedFeatures(featuresPtr);

    void _setEnvironment(environmentPtr);

    void _setSeen(std::vector<bool>&);

    void _setSeen(unsigned int, bool);

    void _setRanges(std::vector<unsigned int>&);

    void _setForestIdentifiers(std::vector<forestIdentifierPtr>&);

    void _setStatements(const statementsPtr&);

    // rule methods
    
    void rulePrint(std::ostream &, unsigned int index = UINT_MAX, bool withSemantic = false, bool html = true) const;
    
    void ruleResetUsages(void) ;

    const std::string& getRuleFilename() const;

    void _addRef(unsigned int);

    void _putIndexTerms(unsigned int, unsigned int);

    bool isSeen(unsigned int) const;

    void _addRanges(unsigned int) ;

    std::vector<forestIdentifierPtr> _getForestIdentifiers(void) const;

    void _addForestIdentifiers(unsigned int i, forestIdentifierPtr);

    void buildSynthesizedFeatures(class Synthesizer *) const;

    void buildInheritedSonFeatures(class Synthesizer *) const;

    void _addEnvironment(environmentPtr);

    void print(std::ostream&);

    void _renameVariables(size_t);

    bool isCompleted(void);

    bool isStarted(void);

    void _setIndex(unsigned int);
    
    void _next(bool&);

    void defaultInheritedSonFeatures(void);

    void apply(class Parser& parser, class Synthesizer* synthesizer);

    itemPtr _clone(const std::bitset<FLAGS>& savedFlags = Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
   
    struct hash {
        size_t operator()(itemPtr const&) const;
    };

    struct equal_to {
        bool operator()(itemPtr const&, itemPtr const&) const;
    };
};

#endif // ELVEX_ITEM_H
