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

#ifndef ELVEX_FEATURES_H
#define ELVEX_FEATURES_H

#include <vector>

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "facade.hpp"
#include "serializable.hpp"
#include "shared_ptr.hpp"

/**
 * Feature structure supporting variable binding and subsumption.
 * The NIL and BOTTOM special instances represent distinct logical states.
 */
class Features : public Facade,
                 public Serializable,
                 public std::enable_shared_from_this<class Features>
{

public:
    static featuresPtr NIL;

    static featuresPtr BOTTOM;

    typedef std::vector<featurePtr> list_of_feature;

private:
    list_of_feature features;

    uint32_t head;

    std::string form;

    /** Create the distinguished inconsistent/bottom feature structure. */
    static featuresPtr createBottom();

    /** Create the distinguished NIL feature structure. */
    static featuresPtr createNil();

    void makeCoreSerialString();

    /** Check whether two features denote the same attribute or special slot. */
    static bool hasMatchingAttribute(const featurePtr &left, const featurePtr &right);

    /** Bind unmatched fields to variable attributes, then clear temporary SEEN flags. */
    void bindRemainingStructureVariables(statementPtr statementRoot,
                                         const environmentPtr &environment,
                                         const featuresPtr &otherFeatures,
                                         bool verbose, bool override);

public:
    Features(const featurePtr &);

    ~Features();

    static featuresPtr create(const featurePtr & = featurePtr());

    void putId(unsigned int id);

    void add(const featurePtr &);

    void add(const featuresPtr &);

    size_t size() const;

    list_of_feature::const_iterator cbegin() const;

    list_of_feature::const_iterator cend() const;

    list_of_feature::iterator begin();

    list_of_feature::iterator end();

    list_of_feature::iterator erase(list_of_feature::iterator);

    featurePtr front() const;

    void toHTML(std::ostream &) const;

    void flatPrint(std::ostream &, bool par = true) const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    featuresPtr clone() const;

    valuePtr findSpecialFeature(const bitsetPtr &code) const;

    valuePtr find(const bitsetPtr &) const;

    /**
     * Unify this feature structure with another and update variable bindings.
     * The supplied environment is mutable despite being passed as a shared pointer.
     */
    bool buildEnvironment(statementPtr statementRoot, const environmentPtr &, const featuresPtr &, bool
#ifdef TRACE_BUILD_ENVIRONMENT
                          ,
                          bool
#endif
                            , bool verbose, bool override);

    void subFlags(const std::bitset<MAX_FLAGS> &);

    uint32_t assignHead();

    std::string *assignForm();

    bool renameVariables(uint32_t);

    bool isNil() const;

    bool isBottom() const;

    void testEnable(statementPtr statementRoot, class Item *, class Generator *synthesizer, bool &, bool);

    /**
     * Check feature compatibility while binding variables in the environment.
     * Callers must clone the environment before speculative alternatives.
     */
    bool subsumes(statementPtr statementRoot, const featuresPtr &, const environmentPtr &, bool verbose);

    bool containsVariable();

    bool containsSynthesizedChildFeatures();

    void apply(statementPtr statementRoot, class Item *item, class Parser &parser, Generator *synthesizer, const statementPtr &variable,
               const statementPtr &body,
               bool &effect, bool verbose);

};

#endif // ELVEX_FEATURES_H
