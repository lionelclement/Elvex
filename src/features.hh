/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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

#include <list>

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "flags.hh"
#include "serializable.hh"
#include "id.hh"
#include "shared_ptr.hh"
#include "variableflag.hh"

class Features :
        public Id, public Flags, public Serializable, public std::enable_shared_from_this<class Features> {

public:
    typedef std::list<featurePtr> list;
    static featuresPtr NIL;
    static featuresPtr BOTTOM;

private:
    list features;
    unsigned int pred;
    std::string form;
    VariableFlag variableFlag;

    Features(featurePtr);

    static featuresPtr createBottom(void);

    static featuresPtr createNil(void);

    void makeSerialString(void);

public:
    ~Features();

    static featuresPtr create(featurePtr = featurePtr());

    void putId(unsigned int id);

    void add(featurePtr, bool = false);

    void add(featuresPtr, bool = false);

    list::iterator erase(list::iterator i);

    const size_t size(void) const;

    list::iterator begin(void);

    list::iterator end(void);

    featurePtr front(void) const;

    void print(std::ostream &) const;

    void flatPrint(std::ostream &, bool par = true) const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    featuresPtr clone(void) const;

    valuePtr find(bitsetPtr) const;

    bool buildEnvironment(environmentPtr, featuresPtr, bool, bool);

    void subFlags(const std::bitset<FLAGS> &);

    unsigned int assignPred(void);

    std::string assignForm(void);

    bool renameVariables(size_t);

    bool isNil(void) const;

    bool isBottom(void) const;

    void enable(statementPtr, itemPtr, class Synthesizer *synthesizer, bool &, bool);

    bool subsumes(featuresPtr, environmentPtr);

    void deleteAnonymousVariables(void);

    bool containsVariable(void);

    bool findVariable(bitsetPtr);

    void setVariableFlag(enum VariableFlag::flagValues flag);
};

#endif // ELVEX_FEATURES_H

