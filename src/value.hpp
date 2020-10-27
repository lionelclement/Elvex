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

#ifndef ELVEX_VALUE_H
#define ELVEX_VALUE_H

#include "flags.hpp"
#include "uniq-id.hpp"
#include "shared_ptr.hpp"
#include "serializable.hpp"
#include "variableflag.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Value :
        public UniqId, public Flags, public Serializable, public std::enable_shared_from_this<class Value> {

public:
    enum Type {
        NIL,
        TRUE,
        CONSTANT,
        VARIABLE,
        ANONYMOUS,
        CODE,
        FEATURES,
        LIST,
        NUMBER,
        STR
    };

private:
    bitsetPtr bits; // pour encoder les constantes et les variables
    unsigned int code; // pour encoder les identifiers
    listPtr list;
    std::string str;
    double number;
    VariableFlag variableFlag;

public:
    static valuePtr TRUE_VALUE;
    static valuePtr NIL_VALUE;
    static valuePtr ANONYMOUS_VALUE;

    Type type;
    featuresPtr features; // pour encoder les SF

private:
    Value(const enum Type, const std::string&);

    Value(const enum Type, unsigned int = 0, double = 0.0, bitsetPtr bitset = bitsetPtr(), featuresPtr = featuresPtr(),
          listPtr lst = listPtr());

    void makeSerialString(void);

public:
    ~Value();

    static valuePtr create(const enum Type);

    static valuePtr create(const enum Type, double);

    static valuePtr create(const enum Type, unsigned int);

    static valuePtr create(const enum Type, const std::string&);

    static valuePtr create(const enum Type, bitsetPtr);

    static valuePtr create(const enum Type, featuresPtr);

    static valuePtr create(const enum Type, class Set *);

    static valuePtr create(const enum Type, listPtr);

    Type getType(void) const;

    bitsetPtr getBits(void) const;

    unsigned int getCode(void) const;

    featuresPtr getFeatures(void) const;

    double getNumber(void) const;

    std::string getStr(void) const;

    listPtr getList(void) const;

    void print(std::ostream &) const;

    void flatPrint(std::ostream &) const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr) const;
#endif

    bool buildEnvironment(const environmentPtr&, const valuePtr&, bool, bool);

    bool subsumes(const valuePtr&, const environmentPtr&);

    valuePtr clone(void);

    void deleteAnonymousVariables(void) const;

    bool renameVariables(size_t);

    bool isNil(void) const;

    //bool isFalse(void) const;

    bool isTrue(void) const;

    bool isAnonymous(void) const;

    bool isNumber(void) const;

    bool isStr(void) const;

    bool isVariable(void) const;

    bool isIdentifier(void) const;

    bool isFeatures(void) const;

    bool isConstant(void) const;

    bool isList(void) const;

    void enable(const statementPtr& root, const itemPtr& item, class Synthesizer *synthesizer, bool &effect, bool on);

    bool eq(valuePtr) const;

    bool lt(const valuePtr&) const;

    bool findVariable(const bitsetPtr&) const;

    void
    apply(const itemPtr& item, class Parser &parser, class Synthesizer *synthesizer, const statementPtr& variable, statementPtr body,
          bool &effect);

    bool containsVariable(void);

    void setVariableFlag(enum VariableFlag::flagValues flag);
};

#endif // ELVEX_VALUE_H
