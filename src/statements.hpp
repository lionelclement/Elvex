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
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef ELVEX_STATEMENTS_H
#define ELVEX_STATEMENTS_H

#include <list>
#include <vector>
#include "flags.hpp"
#include "uniq_id.hpp"
#include "serializable.hpp"
#include "shared_ptr.hpp"

class Statements :
        public UniqId, public Flags, public Serializable, public std::enable_shared_from_this<class Statements> {

public:
    typedef std::list<statementPtr> list;

private:
    statementPtr guard;
    list statements;

    Statements(const statementPtr&);

    void makeSerialString(void);

public:
    ~Statements();

    static statementsPtr create(const statementPtr& = statementPtr());

    size_t size(void);

    list::const_iterator begin(void) const;

    list::const_iterator end(void) const;

    void addStatement(const statementPtr&);

    void renameVariables(size_t);

    void print(std::ostream &, unsigned int tabulation = 0, unsigned int yetColored = 0) const;

    statementsPtr clone(const std::bitset<FLAGS> &savedFlags);

    void apply(itemPtr item, class Parser &parser, class Synthesizer *synthesizer, bool &effect);

    void enable(itemPtr item, class Synthesizer *synthesizer, bool &effect, bool on);

};

#endif // ELVEX_STATEMENTS_H
