/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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
    // resetSerial();
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
        guard->toHTML(out, tabulationLenght, tabulation, color, bgcolor);
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
        (*statement)->toHTML(out, tabulationLenght, tabulation, color, bgcolor);
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
    //bool effect = false;

    if (guard)
    {
        guard->renameVariable(code);
        //effect = true;
    }

    for (auto statement = this->statements.cbegin(); statement != this->statements.cend(); ++statement)
    {
        (*statement)->renameVariable(code);
        //effect = true;
    }

    //if (effect)
    //    resetSerial();
}

/* **************************************************
 *
 ************************************************** */
bool Statements::findVariable(uint32_t code)
{
    if (guard && guard->containsVariable(code))
        return true;
    for (list_statement::const_iterator statement = this->statements.cbegin(); statement != this->statements.cend(); ++statement)
        if ((*statement)->containsVariable(code))
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
            item->toHTML(std::cout);
            std::cout << std::endl;
        }
        guard->apply(guard, item, parser, synthesizer, effect, true, verbose);
        guard->addFlags(Flags::SEEN);
        if (synthesizer->getTraceAction() || ((synthesizer->getVerbose() && synthesizer->getTrace() && item->getRuleTrace())))
        {
            std::cout << "<H3>####################### APPLY CON'T (after gard) #######################</H3>" << std::endl;
            item->toHTML(std::cout);
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

        for (list_statement::const_iterator statement = statements.cbegin();
             statement != statements.cend();
             ++statement)
        {
            if ((*statement)->isUnsetFlags(Flags::SEEN))
            {
                bool enableResult = false;
                (*statement)->testEnable(*statement, item, synthesizer, enableResult, false);
                if (enableResult)
                {
                    (*statement)->testEnable(*statement, item, synthesizer, enableResult, true);
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
                continue;
            }
            effect = false;
            (*statement)->apply((*statement), item, parser, synthesizer, effect, true, verbose);
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
        item->toHTML(std::cout);
        std::cout << std::endl;
    }
}

/* **************************************************
 *
 ************************************************** */
void Statements::testEnable(class Item *item, Generator *synthesizer, bool &effect, bool on)
{
    if (guard)
        guard->testEnable(guard, item, synthesizer, effect, on);
    for (auto statement = statements.cbegin(); statement != statements.cend(); ++statement)
    {
        (*statement)->testEnable(*statement, item, synthesizer, effect, on);
    }
}

/* **************************************************
 *
 ************************************************** */
/*
void Statements::makeSerialString()
{
    std::ostringstream stream;

    stream << '{';

    if (guard)
    {
        stream << "G:";
        stream << guard->peekSerialString();
        stream << ';';
    }
    else
    {
        stream << "G:0;";
    }

    stream << "S:";
    if (statements.empty())
    {
        stream << '0';
    }
    else
    {
        bool first = true;
        for (const auto &statement : statements)
        {
            if (!first)
                stream << '|';
            first = false;

            if (statement)
                stream << statement->peekSerialString();
            else
                stream << '0';
        }
    }

    stream << '}';

    serialString = stream.str();
}
*/
