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

#ifndef ELVEX_FEATURE_H
#define ELVEX_FEATURE_H

#include "flags.h"
#include "id.h"
#include "shared_ptr.h"
#include "serializable.h"
#include "variableflag.h"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Feature :
        public Id, public Flags, public Serializable, public std::enable_shared_from_this<class Feature> {

public:
    enum Type {
        PRED = 0,
        CONSTANT,
        FORM,
        VARIABLE,
    };

    static const Type first_type = PRED;
    static const Type last_type = VARIABLE;

private:
    enum Type type;
    bitsetPtr attribute;
    valuePtr value;

    Feature(Type, bitsetPtr, valuePtr);

    void makeSerialString(void);

    VariableFlag variableFlag;

public:
    ~Feature();

    static featurePtr create(enum Type type = CONSTANT, bitsetPtr attribute = bitsetPtr(), valuePtr value = valuePtr());

    const bitsetPtr getAttribute(void) const;

    void setAttribute(const bitsetPtr);

    const valuePtr getValue(void) const;

    void setValue(const valuePtr);

    enum Type getType(void) const;

    void setType(const enum Type);

    std::string attributeToString(void) const;

    featurePtr clone(void) const;

    void print(std::ostream &) const;

    void flatPrint(std::ostream &) const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr nodeRoot);
#endif

    bool renameVariables(size_t);

    void enable(statementPtr, itemPtr, class Synthesizer *synthesizer, bool &, bool);

    bool findVariable(const bitsetPtr) const;

    bool containsVariable(void);

    bool findVariable(bitsetPtr);

    void setVariableFlag(enum VariableFlag::flagValues flag);

};

#endif // ELVEX_FEATURE_H
