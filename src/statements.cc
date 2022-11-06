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

#include <iostream>     // std::cout, std::endl
#include <iomanip>

#include "statements.hpp"
#include "environment.hpp"
#include "messages.hpp"
#include "item.hpp"
#include "statement.hpp"
#include "synthesizer.hpp"
#include "listfeatures.hpp"

/* **************************************************
 *
 ************************************************** */
Statements::Statements(const statementPtr& statement) {
    NEW
    if (statement)
        statements.push_front(statement);
}

/* **************************************************
 *
 ************************************************** */
Statements::~Statements() {
    DELETE
    for (auto & statement : statements)
        statement.reset();
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Statements::create(const statementPtr& statement) {
    return statementsPtr(new Statements(statement));
}

/* **************************************************
 *
 ************************************************** */
size_t Statements::size() {
    return this->statements.size();
}

/* **************************************************
 *
 ************************************************** */
Statements::list::const_iterator Statements::begin() const {
    return this->statements.begin();
}

/* **************************************************
 *
 ************************************************** */
Statements::list::const_iterator Statements::end() const {
    return this->statements.end();
}

/* **************************************************
 *
 ************************************************** */
void Statements::addStatement(const statementPtr& statement) {
    if (statement->isGuard())
        this->guard = statement;
    else
        this->statements.push_back(statement);
}

/* **************************************************
 *
 ************************************************** */
void Statements::print(std::ostream &outStream, unsigned int tabulation, unsigned int yetColored) const {
    unsigned int color = yetColored;
    if (isSetFlags(Flags::SEEN)) {
        color |= 0x0000FFu;
    }
    if (isSetFlags(Flags::DISABLED)) {
        color |= 0xC0C0C0u;
    }
    if (isSetFlags(Flags::BOTTOM)) {
        color |= 0xFF0000u;
    }
    if (color != 0)
        outStream << "<div style=\"color:#" << std::setfill('0') << std::setw(6) << std::hex << color << ";\">";
    else
        outStream << "<div>";
    tabulation += 3;
    for (unsigned int j = 1; j <= tabulation; ++j)
        outStream << "&nbsp;";
    outStream << "{<BR>";
    if (guard)
        guard->print(outStream, tabulation, yetColored | color);
    for (list::const_iterator i = statements.begin(); i != statements.end(); ++i)
        (*i)->print(outStream, tabulation, yetColored | color);
    for (unsigned int j = 1; j <= tabulation; ++j)
        outStream << "&nbsp;";
    outStream << "}";
    outStream << "</div>";
}

/* **************************************************
 *
 ************************************************** */
void Statements::makeSerialString() {
    serialString = '{';
    if (guard)
        serialString += guard->peekSerialString() + ';';
    for (auto i : statements)
        serialString += i->peekSerialString() + ';';
    serialString += '}';
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Statements::clone(const std::bitset<FLAGS> &protectedFlags) {
    statementsPtr _statements = Statements::create();
    _statements->guard = (guard) ? guard->clone(protectedFlags) : statementPtr();
    for (list::const_iterator i = this->statements.begin(); i != this->statements.end(); ++i)
        _statements->addStatement((*i)->clone(protectedFlags));
    _statements->addFlags(protectedFlags & this->getFlags());
    return _statements;
}

/* **************************************************
 *
 ************************************************** */
void Statements::renameVariables(size_t i) {
    if (guard)
        guard->renameVariables(i);
    for (list::const_iterator j = this->statements.begin(); j != this->statements.end(); ++j)
        (*j)->renameVariables(i);
}

/* **************************************************
 * Applique l'ensemble des instructions
 ************************************************** */
void Statements::apply(itemPtr item, Parser &parser, Synthesizer *synthesizer, bool &effect) {
    if (item->isSetFlags(Flags::BOTTOM))
        return;
    if (item->isSetFlags(Flags::SEEN)) {
        FATAL_ERROR_UNEXPECTED
    }

    if (guard) {
        if (guard->isUnsetFlags(Flags::SEEN)) {
            guard->apply(item, parser, synthesizer, effect);
            guard->addFlags(Flags::SEEN);
            if (guard->isSetFlags(Flags::BOTTOM)) {
                item->addFlags(Flags::BOTTOM);
                return;
            }
        }
    }

    loopStatements:
    bool allDone = true;
    for (list::iterator statement = statements.begin(); statement != statements.end(); ++statement) {
        if ((*statement)->isUnsetFlags(Flags::SEEN)) {
            bool enable_effect = false;
            (*statement)->enable(*statement, item, synthesizer, enable_effect, false);
            if (enable_effect)
                (*statement)->enable(*statement, item, synthesizer, enable_effect, true);
            if (enable_effect)
                allDone = false;
            if ((*statement)->isSetFlags(Flags::DISABLED)) {
                allDone = false;
                continue;
            }
            if (!item->getEnvironment() || item->getEnvironment()->size() == 0) {
                item->setEnvironment(environmentPtr());
            }
            effect = false;
            (*statement)->apply(item, parser, synthesizer, effect);
            if ((*statement)->isSetFlags(Flags::BOTTOM)) {
                item->addFlags(Flags::BOTTOM);
                break;
            }
            if (effect) {
                goto loopStatements;
                //break;
            }
        }
    }
    if (allDone)
        this->addFlags(Flags::SEEN);

}

/* **************************************************
 *
 ************************************************** */
void Statements::enable(itemPtr item, Synthesizer *synthesizer, bool &effect, bool on) {
    if (guard)
        guard->enable(guard, item, synthesizer, effect, on);
    for (list::const_iterator i = statements.begin(); i != statements.end(); ++i) {
        (*i)->enable(*i, item, synthesizer, effect, on);
    }
}

