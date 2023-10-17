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

#ifndef ELVEX_FEATURE_H
#define ELVEX_FEATURE_H

#include "facade.hpp"
#include "shared_ptr.hpp"
#include "serializable.hpp"
#include "variableflag.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Feature : public Facade,
                public Serializable,
                public std::enable_shared_from_this<class Feature>
{

public:
    enum Type
    {
        _HEAD_ = 0,
        _LEMMA_,
        _CONSTANT_,
        _FORM_,
        _VARIABLE_,
    };

    static const Type first_type = _HEAD_;
    static const Type last_type = _VARIABLE_;

private:
    enum Type type;

    bitsetPtr attribute;

    uint32_t code;

    valuePtr value;

    void makeSerialString(void);

    VariableFlag variableFlag;

public:
    Feature(Type, bitsetPtr, valuePtr);

    Feature(Type, uint32_t, valuePtr);

    ~Feature();

    static featurePtr createConstant(bitsetPtr attribute = bitsetPtr(), valuePtr value = valuePtr());

    static featurePtr createHead(valuePtr value);

    static featurePtr createForm(valuePtr value);

    static featurePtr createLemma(valuePtr value);

    static featurePtr createVariable(uint32_t code, valuePtr value = valuePtr());

    bitsetPtr getAttribute(void) const;

    uint32_t getCode(void) const;

    void setAttribute(const bitsetPtr);

    valuePtr getValue(void) const;

    void setValue(const valuePtr);

    enum Type getType(void) const;

    void setType(const enum Type);

    bool isForm() const;

    bool isHead() const;

    bool isLemma() const;

    bool isConstant() const;

    bool isVariable() const;

    std::string attributeToString(void) const;

    featurePtr clone(void) const;

    void print(std::ostream &) const;

    void flatPrint(std::ostream &) const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr nodeRoot);
#endif

    bool renameVariables(uint32_t);

    void enable(const statementPtr &, class Item *, class Generator *synthesizer, bool &, bool);

    bool findVariable(uint32_t key) const;

    bool containsVariable(void);

};

#endif // ELVEX_FEATURE_H
