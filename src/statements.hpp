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

#ifndef ELVEX_STATEMENTS_H
#define ELVEX_STATEMENTS_H

#include <list>
#include <vector>
#include "facade.hpp"
#include "serializable.hpp"
#include "shared_ptr.hpp"

class Statements : public Facade,
                   public Serializable,
                   public std::enable_shared_from_this<class Statements>
{

public:
    typedef std::list<statementPtr> list;

private:
    statementPtr guard;
    list statements;

    Statements(const statementPtr &);

    void makeSerialString(void);

public:
    ~Statements();

    static statementsPtr create(const statementPtr & = statementPtr());

    size_t size(void);

    list::const_iterator begin(void);

    list::const_iterator end(void);

    list::const_iterator cbegin(void) const;

    list::const_iterator cend(void) const;

    void addStatement(const statementPtr &);

    void renameVariables(size_t);

    bool findVariable(const bitsetPtr &variable);

    void print(std::ostream &outStream, unsigned int tabulationLenght, unsigned int tabulation, unsigned int color, unsigned int bgcolor, bool ln, std::string leftSep, std::string rightSep, std::string sep) const;

    statementsPtr clone(const std::bitset<FLAGS> &savedFlags);

    void toggleEnable(class Item *item, class Generator *synthesizer, bool &effect, bool on);

    void apply(class Item *item, class Parser &parser, class Generator *synthesizer, bool &effect);

};

#endif // ELVEX_STATEMENTS_H
