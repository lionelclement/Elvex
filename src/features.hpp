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

#ifndef ELVEX_FEATURES_H
#define ELVEX_FEATURES_H

#include <vector>

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "facade.hpp"
#include "serializable.hpp"
#include "shared_ptr.hpp"
#include "variableflag.hpp"

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
    VariableFlag variableFlag;

    Features(const featurePtr &);

    static featuresPtr createBottom();

    static featuresPtr createNil();

    void makeSerialString();

public:
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

    void print(std::ostream &) const;

    void flatPrint(std::ostream &, bool par = true) const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    featuresPtr clone() const;

    valuePtr find(const bitsetPtr &) const;

    bool buildEnvironment(statementPtr statementRoot, const environmentPtr &, const featuresPtr &, bool
#ifdef TRACE_BUILD_ENVIRONMENT
                          ,
                          bool
#endif
                            , bool verbose);

    void subFlags(const std::bitset<MAX_FLAGS> &);

    uint32_t assignHead();

    std::string *assignForm();

    bool renameVariables(uint32_t);

    bool isNil() const;

    bool isBottom() const;

    void enable(statementPtr statementRoot, class Item *, class Generator *synthesizer, bool &, bool);

    bool subsumes(statementPtr statementRoot, const featuresPtr &, const environmentPtr &, bool verbose);

    void deleteAnonymousVariables();

    void deleteVariables();

    bool containsVariable();

    bool findVariable(uint32_t key) const;

    void setVariableFlag(enum VariableFlag::flagValues flag);

    void apply(statementPtr statementRoot, class Item *item, class Parser &parser, Generator *synthesizer, const statementPtr &variable,
               const statementPtr &body,
               bool &effect, bool verbose);
};

#endif // ELVEX_FEATURES_H
