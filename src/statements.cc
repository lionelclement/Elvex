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

#include <iostream>
#include <iomanip>
#include "statements.hpp"
#include "environment.hpp"
#include "messages.hpp"
#include "item.hpp"
#include "statement.hpp"
#include "generator.hpp"
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
Statements::list_statement::const_iterator Statements::begin()
{
    return this->statements.begin();
}

/* **************************************************
 *
 ************************************************** */
Statements::list_statement::const_iterator Statements::end()
{
    return this->statements.end();
}

/* **************************************************
 *
 ************************************************** */
Statements::list_statement::const_iterator Statements::cbegin() const
{
    return this->statements.cbegin();
}

/* **************************************************
 *
 ************************************************** */
Statements::list_statement::const_iterator Statements::cend() const
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
void Statements::print(std::ostream &out, uint8_t tabulationLenght, uint8_t tabulation, uint32_t color, uint32_t bgcolor, bool ln,
                       std::string leftSep, std::string rightSep, std::string sep) const
{
    if (ln)
    {
        out << "<div>";
    }
    if (ln)
    {
        for (uint8_t j = 1; j <= tabulation; ++j)
            out << "&nbsp;";
    }
    out << leftSep;
    if (ln)
    {
        out << "<div>";
    }
    tabulation += tabulationLenght;
    if (guard)
    {
        if (ln)
        {
            for (uint8_t j = 1; j <= tabulation; ++j)
                out << "&nbsp;";
        }
        guard->print(out, tabulationLenght, tabulation, color, bgcolor);
    }
    bool first = true;
    for (list_statement::const_iterator statement = statements.cbegin(); statement != statements.cend(); ++statement)
    {
        if (first)
            first = false;
        else
            out << sep;
        if (ln)
        {
            for (uint8_t j = 1; j <= tabulation; ++j)
                out << "&nbsp;";
        }
        (*statement)->print(out, tabulationLenght, tabulation, color, bgcolor);
    }
    tabulation -= tabulationLenght;
    if (ln)
    {
        out << "</div>";
        for (uint8_t j = 1; j <= tabulation; ++j)
            out << "&nbsp;";
    }
    out << rightSep;
    if (ln)
    {
        out << "</div>";
    }
}

// /* **************************************************
//  *
//  ************************************************** */
// void Statements::makeSerialString()
// {
//     std::ostringstream stream;
    
//     stream << '#';
//     if (guard)
//         stream << '-' + guard->peekSerialString() + '/';
//     if (!statements.empty()){
//         for (auto statement : statements){
//             //stream << '_' + (statement ? statement->peekSerialString() : "0") + '_';
//             //stream << '_' + (statement ? statement->peekSerialString() : "0") + '_';
//         }
//     } else {
//         stream << '0';
//     }
//     stream << '#';

//     stream.flush();
//     serialString = stream.str();
// }

/* **************************************************
 *
 ************************************************** */
statementsPtr Statements::clone(const std::bitset<MAX_FLAGS> &protectedFlags)
{
    statementsPtr _statements = Statements::create();
    _statements->guard = (guard) ? guard->clone(protectedFlags) : statementPtr();
    for (list_statement::const_iterator statement = this->statements.cbegin(); statement != this->statements.cend(); ++statement)
        _statements->addStatement((*statement)->clone(protectedFlags));
    _statements->addFlags(protectedFlags & this->getFlags());
    return _statements;
}

/* **************************************************
 *
 ************************************************** */
void Statements::renameVariables(uint32_t code)
{
    if (guard)
        guard->renameVariables(code);
    for (list_statement::const_iterator statement = this->statements.cbegin(); statement != this->statements.cend(); ++statement)
        (*statement)->renameVariables(code);
}

/* **************************************************
 *
 ************************************************** */
bool Statements::findVariable(uint32_t code)
{
    if (guard && guard->findVariable(code))
        return true;
    for (list_statement::const_iterator statement = this->statements.cbegin(); statement != this->statements.cend(); ++statement)
        if ((*statement)->findVariable(code))
            return true;
    return false;
}

/* **************************************************
 * Applique l'ensemble des instructions
 ************************************************** */
void Statements::apply(class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool verbose)
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
        guard->apply(guard, item, parser, synthesizer, effect, verbose);
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
        for (list_statement::const_iterator statement = statements.cbegin();
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

        for (list_statement::const_iterator statement = statements.cbegin();
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
            if (!item->getEnvironment() || item->getEnvironment()->empty())
            {
                item->setEnvironment(environmentPtr());
            }
            effect = false;
            (*statement)->apply((*statement), item, parser, synthesizer, effect, verbose);
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
    for (list_statement::const_iterator statement = statements.cbegin();
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
    }
}

/* **************************************************
 *
 ************************************************** */
void Statements::toggleEnable(class Item *item, Generator *synthesizer, bool &effect, bool on)
{
    if (guard)
        guard->toggleEnable(guard, item, synthesizer, effect, on);
    for (auto statement = statements.cbegin(); statement != statements.cend(); ++statement)
    {
        (*statement)->toggleEnable(*statement, item, synthesizer, effect, on);
    }
}
