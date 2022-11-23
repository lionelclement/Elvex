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
        _NIL_,
        _TRUE_,
        _CONSTANT_,
        _VARIABLE_,
        _ANONYMOUS_,
        _CODE_,
        _FEATURES_,
        _LISTFEATURES_,
        _PAIRP_,
        _NUMBER_,
        _FORM_
    };

private:
    bitsetPtr bits;    // pour encoder les constantes et les variables
    unsigned int code; // pour encoder les identifiers
    pairpPtr pairp;
    std::string str;
    double number;
    VariableFlag variableFlag;
    featuresPtr features; // pour encoder les SF
    listFeaturesPtr listFeatures; // pour encoder les listes de SF

public:
    static valuePtr NIL_VALUE;
    static valuePtr TRUE_VALUE;
    static valuePtr ANONYMOUS_VALUE;

    Type type;

private:
    Value(const enum Type, const std::string &);

    Value(const enum Type, unsigned int = 0, double = 0.0, bitsetPtr = bitsetPtr(), featuresPtr = featuresPtr(),
          pairpPtr = pairpPtr(), listFeaturesPtr = listFeaturesPtr());

    void makeSerialString(void);

public:
    ~Value();

    static valuePtr create(const enum Type);

    static valuePtr create(const enum Type, double);

    static valuePtr create(const enum Type, unsigned int);

    static valuePtr create(const enum Type, const std::string &);

    static valuePtr create(const enum Type, bitsetPtr);

    static valuePtr create(featuresPtr);

    static valuePtr create(listFeaturesPtr);

    static valuePtr create(class Set *);

    static valuePtr create(pairpPtr);

    enum Type _getType(void) const;

    bitsetPtr getBits(void) const;

    unsigned int getCode(void) const;

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

    bool buildEnvironment(const environmentPtr &, const valuePtr &, bool, bool);

    bool subsumes(const valuePtr &, const environmentPtr &);

    valuePtr clone(void);

    void deleteAnonymousVariables(void) const;

    bool renameVariables(size_t);

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

    void enable(const statementPtr &root, class Item *item, class Synthesizer *synthesizer, bool &effect, bool on);

    bool eq(valuePtr) const;

    bool lt(const valuePtr &) const;

    bool findVariable(const bitsetPtr &) const;

    void
    apply(class Item *item, class Parser &parser, class Synthesizer *synthesizer, const statementPtr &variable, const statementPtr &body,
          bool &effect);

    bool containsVariable(void);

    void setVariableFlag(enum VariableFlag::flagValues flag);
};

#endif // ELVEX_VALUE_H
