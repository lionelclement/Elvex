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
 * LaBRI -- Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#include <iostream>
#include <iomanip>
#include "statements.hpp"
#include "environment.hpp"
#include "messages.hpp"
#include "item.hpp"
#include "statement.hpp"
<<<<<<< HEAD
#include "application.hpp"
=======
#include "generator.hpp"
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
#include "listfeatures.hpp"

/* **************************************************
 *
 ************************************************** */
Statements::Statements(const statementPtr &statement)
{
    NEW;
    if (statement)
        statements.push_front(statement);
}

/* **************************************************
 *
 ************************************************** */
Statements::~Statements()
{
    DELETE;
    for (auto &statement : statements)
        statement.reset();
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Statements::create(const statementPtr &statement)
{
    return statementsPtr(new Statements(statement));
}

/* **************************************************
 *
 ************************************************** */
size_t Statements::size()
{
    return this->statements.size();
}

/* **************************************************
 *
 ************************************************** */
Statements::list::const_iterator Statements::begin()
{
    return this->statements.begin();
}

/* **************************************************
 *
 ************************************************** */
Statements::list::const_iterator Statements::end()
{
    return this->statements.end();
}

/* **************************************************
 *
 ************************************************** */
Statements::list::const_iterator Statements::cbegin() const
{
    return this->statements.cbegin();
}

/* **************************************************
 *
 ************************************************** */
Statements::list::const_iterator Statements::cend() const
{
    return this->statements.cend();
}

/* **************************************************
 *
 ************************************************** */
void Statements::addStatement(const statementPtr &statement)
{
    if (statement->isGuard())
        this->guard = statement;
    else
        this->statements.push_back(statement);
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
void Statements::print(std::ostream& outStream, unsigned int tabulation, unsigned int yetColored) const {
    unsigned int color = yetColored;
    if (isSetFlags(Flags::SEEN)) {
        color |= 0x0000FFu;
=======
void Statements::print(std::ostream &out, unsigned int tabulation, unsigned int color, bool ln,
                       std::string leftSep, std::string rightSep, std::string sep) const
{
    if (ln)
    {
        out << "<div>";
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    }
    if (ln)
    {
        for (unsigned int j = 1; j <= tabulation; ++j)
            out << "&nbsp;";
    }
    out << leftSep;
    if (ln)
    {
        out << "<div>";
    }
    tabulation += 5;
    if (guard)
    {
        if (ln)
        {
            for (unsigned int j = 1; j <= tabulation; ++j)
                out << "&nbsp;";
        }
        guard->print(out, tabulation, color);
    }
    bool first = true;
    for (list::const_iterator i = statements.cbegin(); i != statements.cend(); ++i)
    {
        if (first)
            first = false;
        else
            out << sep;
        if (ln)
        {
            for (unsigned int j = 1; j <= tabulation; ++j)
                out << "&nbsp;";
        }
        (*i)->print(out, tabulation, color);
    }
    tabulation -= 5;
    if (ln)
    {
        out << "</div>";
        for (unsigned int j = 1; j <= tabulation; ++j)
            out << "&nbsp;";
    }
    out << rightSep;
    if (ln)
    {
        out << "</div>";
    }
}

/* **************************************************
 *
 ************************************************** */
void Statements::makeSerialString()
{
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
<<<<<<< HEAD
statementsPtr Statements::clone(const std::bitset<FLAGS>& protectedFlags) {
=======
statementsPtr Statements::clone(const std::bitset<FLAGS> &protectedFlags)
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    statementsPtr _statements = Statements::create();
    _statements->guard = (guard) ? guard->clone(protectedFlags) : statementPtr();
    for (list::const_iterator i = this->statements.cbegin(); i != this->statements.cend(); ++i)
        _statements->addStatement((*i)->clone(protectedFlags));
    _statements->addFlags(protectedFlags & this->getFlags());
    return _statements;
}

/* **************************************************
 *
 ************************************************** */
void Statements::renameVariables(size_t i)
{
    if (guard)
        guard->renameVariables(i);
    for (list::const_iterator j = this->statements.cbegin(); j != this->statements.cend(); ++j)
        (*j)->renameVariables(i);
}

/* **************************************************
<<<<<<< HEAD
 * Applique l'ensemble des instructions
 ************************************************** */
void Statements::apply(itemPtr item, Application *application, bool& effect) {
    if (item->isSetFlags(Flags::BOTTOM))
        return;
    if (item->isSetFlags(Flags::SEEN)) {
        FATAL_ERROR_UNEXPECTED
    }

    if (guard) {
        if (guard->isUnsetFlags(Flags::SEEN)) {
            guard->apply(item, application, effect);
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
            (*statement)->enable(*statement, item, application, enable_effect, false);
            if (enable_effect)
                (*statement)->enable(*statement, item, application, enable_effect, true);
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
            (*statement)->apply(item, application, effect);
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
void Statements::enable(itemPtr item, Application *application, bool& effect, bool on) {
    if (guard)
        guard->enable(guard, item, application, effect, on);
    for (list::const_iterator i = statements.begin(); i != statements.end(); ++i) {
        (*i)->enable(*i, item, application, effect, on);
=======
 *
 ************************************************** */
bool Statements::findVariable(const bitsetPtr &variable)
{
    if (guard && guard->findVariable(variable))
        return true;
    for (list::const_iterator j = this->statements.cbegin(); j != this->statements.cend(); ++j)
        if ((*j)->findVariable(variable))
            return true;
    return false;
}

/* **************************************************
 * Applique l'ensemble des instructions
 ************************************************** */
void Statements::apply(class Item *item, Parser &parser, Synthesizer *synthesizer, bool &effect)
{
    bool allSeen = true;
    if (item->isSetFlags(Flags::BOTTOM | Flags::SEEN))
    {
        FATAL_ERROR_UNEXPECTED
    }

    bool localEffect;
    if (guard && guard->isUnsetFlags(Flags::SEEN))
    {
        if (synthesizer->getTraceAction() || ((synthesizer->getVerbose() && synthesizer->getTrace() && item->getRuleTrace())))
        {
            std::cout << "<H3>####################### APPLY (before gard) #######################</H3>" << std::endl;
            item->print(std::cout);
            std::cout << std::endl;
        }
        guard->apply(item, parser, synthesizer, effect);
        guard->addFlags(Flags::SEEN);
        if (synthesizer->getTraceAction() || ((synthesizer->getVerbose() && synthesizer->getTrace() && item->getRuleTrace())))
        {
            std::cout << "<H3>####################### APPLY CON'T (after gard) #######################</H3>" << std::endl;
            item->print(std::cout);
            std::cout << std::endl;
        }
        if (guard->isSetFlags(Flags::BOTTOM))
        {
            addFlags(Flags::BOTTOM);
            goto exitApply;
        }
    }

    localEffect = true;
    while (localEffect && item->isUnsetFlags(Flags::BOTTOM))
    {
        localEffect = false;

        if (synthesizer->getTraceAction() || (synthesizer->getVerbose() && synthesizer->getTrace() && item->getRuleTrace()))
        {
            std::cout << "<H3>####################### APPLY CON'T (before toggle enable) #######################</H3>" << std::endl;
            item->print(std::cout);
            std::cout << std::endl;
        }
        for (list::const_iterator statement = statements.cbegin();
             statement != statements.cend();
             ++statement)
        {
            if ((*statement)->isUnsetFlags(Flags::SEEN))
            {
                bool enableResult = false;
                (*statement)->toggleEnable(*statement, item, synthesizer, enableResult, false);
                if (enableResult)
                {
                    (*statement)->toggleEnable(*statement, item, synthesizer, enableResult, true);
                }
            }
        }

        if (synthesizer->getTraceAction() || (synthesizer->getVerbose() && synthesizer->getTrace() && item->getRuleTrace()))
        {
            std::cout << "<H3>####################### APPLY CON'T (after toggle enable and before apply) #######################</H3>" << std::endl;
            item->print(std::cout);
            std::cout << std::endl;
        }

        for (list::const_iterator statement = statements.cbegin();
             statement != statements.cend();
             ++statement)
        {
            if ((*statement)->isSetFlags(Flags::SEEN))
            {
                continue;
            }
            if ((*statement)->isSetFlags(Flags::DISABLED))
            {
                continue;
            }
            if (!item->getEnvironment() || item->getEnvironment()->size() == 0)
            {
                item->setEnvironment(environmentPtr());
            }
            effect = false;
            (*statement)->apply(item, parser, synthesizer, effect);
            if ((*statement)->isSetFlags(Flags::BOTTOM))
            {
                addFlags(Flags::BOTTOM);
                goto exitApply;
                break;
            }
            if (effect)
            {
                localEffect = true;
            }
        }
    }
    for (list::const_iterator statement = statements.cbegin();
             statement != statements.cend();
             ++statement)
        {
            if ((*statement)->isSetFlags(Flags::SEEN))
            {
                continue;
            }
            if ((*statement)->isSetFlags(Flags::DISABLED))
            {
                allSeen = false;
            }
        }

    if (allSeen)
        this->addFlags(Flags::SEEN);
    
    exitApply:
    {
    }
    if (synthesizer->getTraceAction() || (synthesizer->getVerbose() && synthesizer->getTrace() && item->getRuleTrace()))
    {
        std::cout << "<H3>####################### APPLY CON'T #######################</H3>" << std::endl;
        item->print(std::cout);
        std::cout << std::endl;
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    }
}

/* **************************************************
 *
 ************************************************** */
void Statements::toggleEnable(class Item *item, Synthesizer *synthesizer, bool &effect, bool on)
{
    if (guard)
        guard->toggleEnable(guard, item, synthesizer, effect, on);
    for (auto statement = statements.cbegin(); statement != statements.cend(); ++statement)
    {
        (*statement)->toggleEnable(*statement, item, synthesizer, effect, on);
    }
}
