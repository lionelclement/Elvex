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

#ifndef ELVEX_PAIRP_H
#define ELVEX_PAIRP_H

#include "facade.hpp"
#include "serializable.hpp"
#include "variableflag.hpp"
#include "shared_ptr.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Pairp : public Facade,
              public Serializable,
              public std::enable_shared_from_this<Pairp>
{

public:
    enum Type
    {
        _ATOM_,
        _PAIRP_,
        _NIL_
    };
    static pairpPtr NIL;

private:
    enum Type type;
    valuePtr value;
    struct
    {
        pairpPtr car;
        pairpPtr cdr;
    } pairp;

    void makeSerialString(void);

    VariableFlag variableFlag;

    static pairpPtr create(void);

public:
    Pairp(enum Type, valuePtr = valuePtr(), pairpPtr = pairpPtr(), pairpPtr = pairpPtr());

    ~Pairp();

    static pairpPtr create(valuePtr);

    static pairpPtr create(pairpPtr, pairpPtr);

    Type getType(void) const;

    void setType(Type);

    valuePtr getValue(void) const;

    void setValue(valuePtr);

    pairpPtr getCar(void) const;

    pairpPtr getCdr(void) const;

    bool isNil(void) const;

    bool isAtom(void) const;

    bool isVariable(void) const;

    bool isPairp(void) const;

    void print(std::ostream &) const;

    void flatPrint(std::ostream &, bool) const;

    bool buildEnvironment(statementPtr statement, const environmentPtr &environment, const pairpPtr &otherPairp, bool acceptToFilterNULLVariables, bool root, bool verbose);

    void deleteVariables(void);

    void deleteAnonymousVariables(void);

    bool renameVariables(uint32_t);

    void apply(statementPtr from, class Item *item, class Parser &parser, class Generator *generator, uint32_t code, statementPtr statement,
                  bool &effect, bool verbose);

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    pairpPtr clone(void) const;

    void enable(const statementPtr &, class Item *, class Generator *generator, bool &, bool);

    bool subsumes(statementPtr from, const pairpPtr &, const environmentPtr &, bool verbose);

    pairpPtr pushFront(valuePtr);

    pairpPtr pushBack(valuePtr);

    bool containsVariable(void);

    bool findVariable(uint32_t key) const;

    void setVariableFlag(enum VariableFlag::flagValues);
};

#endif // ELVEX_PAIRP_H
