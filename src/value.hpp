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

#ifndef ELVEX_VALUE_H
#define ELVEX_VALUE_H

#include "facade.hpp"
#include "shared_ptr.hpp"
#include "serializable.hpp"
#include "variableflag.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Value : public Facade,
              public Serializable,
              public std::enable_shared_from_this<class Value>
{

public:
    enum Type
    {
        NIL_VALUE,
        TRUE_VALUE,
        FALSE_VALUE,
        CONSTANT_VALUE,
        VARIABLE_VALUE,
        ANONYMOUS_VALUE,
        IDENTIFIER_VALUE,
        FEATURES_VALUE,
        LIST_FEATURES_VALUE,
        PAIRP_VALUE,
        NUMBER_VALUE,
        FORM_VALUE
    };

private:
    bitsetPtr bits;    // pour encoder les constantes et les variables
    uint16_t code; // pour encoder les identifiers
    pairpPtr pairp;
    std::string str;
    double number;
    VariableFlag variableFlag;
    featuresPtr features; // pour encoder les SF
    listFeaturesPtr listFeatures; // pour encoder les listes de SF

public:
    static valuePtr STATIC_NIL;
    static valuePtr STATIC_TRUE;
    static valuePtr STATIC_FALSE;
    static valuePtr STATIC_ANONYMOUS;

    Type type;

private:
    Value(const enum Type, const std::string &);

    Value(const enum Type, uint16_t = 0, double = 0.0, bitsetPtr = bitsetPtr(), featuresPtr = featuresPtr(),
          pairpPtr = pairpPtr(), listFeaturesPtr = listFeaturesPtr());

    void makeSerialString(void);

public:
    ~Value();

    static valuePtr create(const enum Type);

    static valuePtr create(const enum Type, double);

    static valuePtr create(const enum Type, uint16_t);

    static valuePtr create(const enum Type, const std::string &);

    static valuePtr create(const enum Type, bitsetPtr);

    static valuePtr create(featuresPtr);

    static valuePtr create(listFeaturesPtr);

    static valuePtr create(class Set *);

    static valuePtr create(pairpPtr);

    enum Type getType(void) const;

    bitsetPtr getBits(void) const;

    uint16_t getCode(void) const;

    featuresPtr getFeatures(void) const;

    listFeaturesPtr getListFeatures(void) const;

    double getNumber(void) const;

    std::string getStr(void) const;

    pairpPtr getPairp(void) const;

    void print(std::ostream &) const;

    void flatPrint(std::ostream &) const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr) const;
#endif

    bool buildEnvironment(statementPtr from, const environmentPtr &, const valuePtr &, bool, bool);

    bool subsumes(statementPtr from, const valuePtr &, const environmentPtr &);

    valuePtr clone(void);

    void deleteAnonymousVariables(void);

    void deleteVariables(void);

    bool renameVariables(u_int32_t);

    bool isNil(void) const;

    bool isFalse(void) const;

    bool isTrue(void) const;

    bool isAnonymous(void) const;

    bool isNumber(void) const;

    bool isForm(void) const;

    bool isVariable(void) const;

    bool isIdentifier(void) const;

    bool isFeatures(void) const;

    bool isConstant(void) const;

    bool isPairp(void) const;

    bool isListFeatures(void) const;

    void enable(const statementPtr &root, class Item *item, class Generator *synthesizer, bool &effect, bool on);

    bool eq(valuePtr) const;

    bool lt(const valuePtr &) const;

    bool findVariable(const bitsetPtr &) const;

    void apply(statementPtr from, class Item *item, class Parser &parser, class Generator *synthesizer, const statementPtr &variable, const statementPtr &body,
          bool &effect);

    bool containsVariable(void);

    void setVariableFlag(enum VariableFlag::flagValues flag);
};

#endif // ELVEX_VALUE_H
