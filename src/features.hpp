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

#ifndef ELVEX_FEATURES_H
#define ELVEX_FEATURES_H

#include <vector>

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "flags.hpp"
#include "serializable.hpp"
#include "uniq-id.hpp"
#include "shared_ptr.hpp"
#include "variableflag.hpp"

class Features :
        public UniqId, 
        public Flags, 
        public Serializable, 
        public std::enable_shared_from_this<class Features> {

public:
    static featuresPtr NIL;
    static featuresPtr BOTTOM;

    typedef std::vector<featurePtr> list_of_feature;

private:
    list_of_feature features;
    unsigned int pred;
    std::string form;
    VariableFlag variableFlag;

    Features(const featurePtr&);

    static featuresPtr createBottom();

    static featuresPtr createNil();

    void makeSerialString();

public:
    ~Features();

    static featuresPtr create(const featurePtr& = featurePtr());

    void putId(unsigned int id);

    void add(const featurePtr&);

    void add(const featuresPtr&);

    size_t size() const;

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

    valuePtr find(const bitsetPtr&) const;

    bool buildEnvironment(const environmentPtr&, const featuresPtr&, bool/*, bool*/);

    void subFlags(const std::bitset<FLAGS> &);

    unsigned int assignPred();

    std::string *assignForm();

    bool renameVariables(size_t);

    bool isNil() const;

    bool isBottom() const;

    void enable(const statementPtr&, const itemPtr&, class Synthesizer *synthesizer, bool &, bool);

    bool subsumes(const featuresPtr&, const environmentPtr&);

    void deleteAnonymousVariables();

    bool containsVariable();

    bool findVariable(const bitsetPtr&);

    void setVariableFlag(enum VariableFlag::flagValues flag);
};

#endif // ELVEX_FEATURES_H

