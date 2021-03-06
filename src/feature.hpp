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

#ifndef ELVEX_FEATURE_H
#define ELVEX_FEATURE_H

#include "flags.hpp"
#include "uniq-id.hpp"
#include "shared_ptr.hpp"
#include "serializable.hpp"
#include "variableflag.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Feature :
        public UniqId, public Flags, public Serializable, public std::enable_shared_from_this<class Feature> {

public:
    enum Type {
        PRED = 0,
        LEMMA,
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

    bitsetPtr getAttribute(void) const;

    void setAttribute(const bitsetPtr);

    valuePtr getValue(void) const;

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

    void enable(const statementPtr&, const itemPtr&, class Synthesizer *synthesizer, bool &, bool);

    bool findVariable(const bitsetPtr) const;

    bool containsVariable(void);

    bool findVariable(const bitsetPtr&);

};

#endif // ELVEX_FEATURE_H
