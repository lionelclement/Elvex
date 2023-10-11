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

    Pairp(enum Type, valuePtr = valuePtr(), pairpPtr = pairpPtr(), pairpPtr = pairpPtr());

    void makeSerialString(void);

    VariableFlag variableFlag;

    static pairpPtr create(void);

public:
    ~Pairp();

    static pairpPtr create(valuePtr);

    static pairpPtr create(pairpPtr, pairpPtr);

    Type getType(void) const;

    void setType(Type);

    valuePtr getValue(void) const;

    void setValue(valuePtr);

    pairpPtr getCar(void) const;

    void setCar(pairpPtr);

    pairpPtr getCdr(void) const;

    void setCdr(pairpPtr);

    pairpPtr getCadr(void) const;

    pairpPtr getCddr(void) const;

    pairpPtr getCaar(void) const;

    pairpPtr getCdar(void) const;

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

    void apply(statementPtr from, class Item *, class Parser &, class Generator *, const statementPtr &, statementPtr,
               bool &, bool verbose);

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    pairpPtr clone(void) const;

    void enable(const statementPtr &, class Item *, class Generator *synthesizer, bool &, bool);

    bool subsumes(statementPtr from, const pairpPtr &, const environmentPtr &, bool verbose);

    pairpPtr pushFront(valuePtr);

    pairpPtr pushBack(valuePtr);

    bool containsVariable(void);

    bool findVariable(const bitsetPtr &);

    void setVariableFlag(enum VariableFlag::flagValues);
};

#endif // ELVEX_PAIRP_H
