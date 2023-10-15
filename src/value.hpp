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
        //LIST_FEATURES_VALUE,
        PAIRP_VALUE,
        NUMBER_VALUE,
        FORM_VALUE
    };

private:
    bitsetPtr bitset;    // pour encoder les constantes
    uint32_t code; // pour encoder les identifiers et les variables
    pairpPtr pairp;
    std::string string;
    double number;
    VariableFlag variableFlag;
    featuresPtr features; // pour encoder les SF
    //listFeaturesPtr listFeatures; // pour encoder les listes de SF

public:
    static valuePtr STATIC_NIL;
    static valuePtr STATIC_TRUE;
    static valuePtr STATIC_FALSE;
    static valuePtr STATIC_ANONYMOUS;

    Type type;

private:
    Value(const enum Type, const std::string &);

    Value(const enum Type, uint32_t = 0, double = 0.0, bitsetPtr = bitsetPtr(), featuresPtr = featuresPtr(),
          pairpPtr = pairpPtr()/*, listFeaturesPtr = listFeaturesPtr()*/);

    void makeSerialString(void);

public:
    ~Value();

    static valuePtr createEmpty(const enum Type type);
    static valuePtr createNumber(double number);
    static valuePtr createVariable(uint32_t code);
    static valuePtr createIdentifier(uint32_t code);
    static valuePtr createIdentifier(const std::string &name);
    static valuePtr createForm(const std::string &str);
    static valuePtr createConstant(bitsetPtr bitset);
    static valuePtr createFeatures(featuresPtr features);
    static valuePtr createPairp(pairpPtr pairp);

    enum Type getType(void) const;

    bitsetPtr getBitset(void) const;

    uint32_t getCode(void) const;

    featuresPtr getFeatures(void) const;

    //listFeaturesPtr getListFeatures(void) const;

    double getNumber(void) const;

    std::string &getString(void) ;

    pairpPtr getPairp(void) const;

    void print(std::ostream &) const;

    void flatPrint(std::ostream &) const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr) const;
#endif

    bool buildEnvironment(statementPtr statementRoot, const environmentPtr &environment, const valuePtr &value, bool acceptToFilterNULLVariables, bool root, bool verbose);

    bool subsumes(statementPtr statementRoot, const valuePtr &, const environmentPtr &, bool verbose);

    valuePtr clone(void);

    void deleteAnonymousVariables(void);

    void deleteVariables(void);

    bool renameVariables(uint32_t);

    bool isNil(void) const;

    bool isFalse(void) const;

    bool isTrue(void) const;

    bool isAnonymous(void) const;

    bool isNumber(void) const;

    bool isString(void) const;

    bool isVariable(void) const;

    bool isIdentifier(void) const;

    bool isFeatures(void) const;

    bool isConstant(void) const;

    bool isPairp(void) const;

    // bool isListFeatures(void) const;

    void enable(const statementPtr &root, class Item *item, class Generator *synthesizer, bool &effect, bool on);

    bool eq(valuePtr) const;

    bool lessThan(const valuePtr &) const;

    bool findVariable(uint32_t key) const;

    void apply(statementPtr statementRoot, class Item *item, class Parser &parser, class Generator *synthesizer, uint32_t variable, const statementPtr &body,
          bool &effect, bool verbose);

    bool containsVariable(void);

    void setVariableFlag(enum VariableFlag::flagValues flag);
};

#endif // ELVEX_VALUE_H
