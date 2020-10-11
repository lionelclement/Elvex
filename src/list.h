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

#ifndef ELVEX_LIST_H
#define ELVEX_LIST_H

#include "flags.h"
#include "id.h"
#include "serializable.h"
#include "variableflag.h"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class List :
        public Serializable, public Flags, public Id, public std::enable_shared_from_this<List> {

public:
    enum Type {
        ATOM,
        PAIRP,
        NIL
    };
    static listPtr NIL_LIST;

private:
    enum Type type;
    valuePtr value;
    struct {
        listPtr car;
        listPtr cdr;
    } pairp;

    List(enum Type type, valuePtr _value = valuePtr(), listPtr _car = listPtr(), listPtr _cdr = listPtr());

    static listPtr create(void);

    void makeSerialString(void);

    VariableFlag variableFlag;

public:
    ~List();

    static listPtr create(valuePtr value);

    static listPtr create(listPtr car, listPtr cdr);

    Type getType(void) const;

    void setType(Type _type);

    valuePtr getValue(void) const;

    void setValue(valuePtr _value);

    listPtr getCar(void) const;

    void setCar(listPtr car);

    listPtr getCdr(void) const;

    void setCdr(listPtr cdr);

    listPtr getCadr(void) const;

    listPtr getCddr(void) const;

    listPtr getCaar(void) const;

    listPtr getCdar(void) const;

    bool isNil(void) const;

    bool isAtomic(void) const;

    bool isVariable(void) const;

    bool isPairp(void) const;

    void print(std::ostream &) const;

    void flatPrint(std::ostream &, bool par) const;

    bool buildEnvironment(const environmentPtr& environment, const listPtr& otherList, bool acceptToFilterNULLVariables, bool root);

    void deleteAnonymousVariables(void);

    bool renameVariables(size_t);

    void
    apply(const itemPtr& item, class Parser &parser, class Synthesizer *synthesizer, const statementPtr& variable, statementPtr body,
          bool &effect);

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    listPtr clone(void) const;

    void enable(const statementPtr&, const itemPtr&, class Synthesizer *synthesizer, bool &, bool);

    bool subsumes(const listPtr&, const environmentPtr&);

    listPtr pushFront(valuePtr _value);

    listPtr pushBack(valuePtr _value);

    bool containsVariable(void);

    bool findVariable(const bitsetPtr&);

    void setVariableFlag(enum VariableFlag::flagValues flag);
};

#endif // ELVEX_LIST_H
