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

#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <utility>

#include "statement.hpp"
#include "environment.hpp"
#include "statements.hpp"
#include "feature.hpp"
#include "features.hpp"
#include "value.hpp"
#include "terms.hpp"
#include "pairp.hpp"
#include "messages.hpp"
#include "item.hpp"
#include "shared_ptr.hpp"
#include "listfeatures.hpp"
#include "rule.hpp"
#include "generator.hpp"
#include "parser.hpp"
#include "bitset.hpp"
#include "vartable.hpp"
#include "flags.hpp"

/* **************************************************
 *
 ************************************************** */
Statement::Statement(uint32_t lineno, std::string bufferName, type op, bool rootOp)
{
    NEW;
    this->lineno = lineno;
    this->bufferName = bufferName;
    this->op = op;
    this->rootOp = rootOp;
}

/* **************************************************
 *
 ************************************************** */
Statement::~Statement()
{
    DELETE;
}

/* **************************************************
 * NIL UP UP2
 ************************************************** */
statementPtr Statement::createEmpty(uint32_t lineno, std::string bufferName, type op, bool rootOp)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    return statementPtr(statement);
}

/* **************************************************
 * DOWN DOWN2 DASH
 ************************************************** */
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp, uint8_t first, uint8_t second)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->code = (static_cast<uint32_t>(second) << 8) | static_cast<uint32_t>(first);
    return statementPtr(statement);
}

/* **************************************************
 * STMS PRINT PRINTLN PRINTSTDERR PRINTSTDERRLN
 ************************************************** */
statementPtr Statement::createStatements(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementsPtr statements)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->statements = statements;
    return statementPtr(statement);
}

/* **************************************************
 * GUARD FEATURES
 ************************************************** */
statementPtr Statement::createFeatures(uint32_t lineno, std::string bufferName, type op, bool rootOp, featuresPtr features)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->features = features;
    return statementPtr(statement);
}

/* **************************************************
 * ATTEST
 ************************************************** */
statementPtr Statement::createFirst(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementPtr first)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->first = first;
    return statementPtr(statement);
}

/* **************************************************
 * AFF SUBSUME IF IF_CON_T DEFERRED FOREACH_CON_T UNIF
 ************************************************** */
statementPtr Statement::createFirstSecond(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementPtr first, statementPtr second)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->first = first;
    statement->second = second;
    return statementPtr(statement);
}

/* **************************************************
 * FOREACH
 ************************************************** */
statementPtr Statement::createForeach(uint32_t lineno, std::string bufferName, bool rootOp, uint32_t code, statementPtr first)
{
    Statement *statement = new Statement(lineno, bufferName, FOREACH_STATEMENT, rootOp);
    statement->code = code;
    statement->first = first;
    return statementPtr(statement);
}

/* **************************************************
 * SEARCH
 ************************************************** */
statementPtr Statement::createSearch(uint32_t lineno, std::string bufferName, bool rootOp, uint32_t code, statementPtr first)
{
    Statement *statement = new Statement(lineno, bufferName, SEARCH_STATEMENT, rootOp);
    statement->code = code;
    statement->first = first;
    return statementPtr(statement);
}

/* **************************************************
 * CONSTANT
 ************************************************** */
statementPtr Statement::createConstant(uint32_t lineno, std::string bufferName, bool rootOp, bitsetPtr bitset)
{
    Statement *statement = new Statement(lineno, bufferName, CONSTANT_STATEMENT, rootOp);
    statement->bitset = bitset;
    return statementPtr(statement);
}

/* **************************************************
 * VARIABLE
 ************************************************** */
statementPtr Statement::createVariable(uint32_t lineno, std::string bufferName, bool rootOp, uint32_t code)
{
    Statement *statement = new Statement(lineno, bufferName, VARIABLE_STATEMENT, rootOp);
    statement->code = code;
    return statementPtr(statement);
}

/* **************************************************
 * PAIRP
 ************************************************** */
statementPtr Statement::createPairp(uint32_t lineno, std::string bufferName, bool rootOp, pairpPtr pairp)
{
    Statement *statement = new Statement(lineno, bufferName, PAIRP_STATEMENT, rootOp);
    statement->pairp = pairp;
    return statementPtr(statement);
}

/* **************************************************
 * FCT
 ************************************************** */
statementPtr Statement::createFunction(uint32_t lineno, std::string bufferName, bool rootOp,
                                       function_type function, statementPtr first, statementPtr second)
{
    Statement *statement = new Statement(lineno, bufferName, FUNCTION_STATEMENT, rootOp);
    statement->function = function;
    statement->first = first ? first : statementPtr();
    statement->second = second ? second : statementPtr();
    return statementPtr(statement);
}

/* **************************************************
 * NUMBER
 ************************************************** */
statementPtr Statement::createNumber(uint32_t lineno, std::string bufferName, bool rootOp, double number)
{
    Statement *statement = new Statement(lineno, bufferName, NUMBER_STATEMENT, rootOp);
    statement->number = number;
    return statementPtr(statement);
}

/* **************************************************
 * STRING
 ************************************************** */
statementPtr Statement::createString(uint32_t lineno, std::string bufferName, bool rootOp, std::string string)
{
    Statement *statement = new Statement(lineno, bufferName, STRING_STATEMENT, rootOp);
    statement->string = string;
    return statementPtr(statement);
}

/* **************************************************
 * ANONYMOUS
 ************************************************** */
statementPtr Statement::createAnonymous(uint32_t lineno, std::string bufferName, bool rootOp)
{
    Statement *statement = new Statement(lineno, bufferName, ANONYMOUS_STATEMENT, rootOp);
    statement->value = Value::STATIC_ANONYMOUS;
    return statementPtr(statement);
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isAssignment() const
{
    return op == ASSIGNMENT_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isSubsume() const
{
    return op == SUBSUME_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isUp() const
{
    return op == INHERITED_FEATURES_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isUp2() const
{
    return op == SYNTHESIZED_FEATURES_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isDown() const
{
    return op == INHERITED_CHILDREN_FEATURES_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isSearch() const
{
    return op == SEARCH_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isDown2() const
{
    return op == SYNTHESIZED_CHILDREN_FEATURES_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isFeatures() const
{
    return op == FEATURES_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isVariable() const
{
    return op == VARIABLE_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isConstant() const
{
    return op == CONSTANT_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isUnif() const
{
    return op == UNIF_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isGuard() const
{
    return op == GUARD_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isPrint() const
{
    return op == PRINT_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isPrintln() const
{
    return op == PRINTLN_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isEprint() const
{
    return op == EPRINT_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isEprintln() const
{
    return op == EPRINTLN_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isAttest() const
{
    return op == ATTEST_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isIf() const
{
    return op == IF_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isForeach() const
{
    return op == FOREACH_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isDeferred() const
{
    return op == DEFERRED_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isStms() const
{
    return op == STMS_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isString() const
{
    return op == STRING_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isPairp() const
{
    return op == PAIRP_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isNumber() const
{
    return op == NUMBER_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isFct() const
{
    return op == FUNCTION_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::containsDash() const
{
    bool result = (op == DASH_STATEMENT);
    if (first)
        result = result || first->containsDash();
    if (second)
        result = result || second->containsDash();
    return result;
}

/* **************************************************
 *
 ************************************************** */
Statement::function_type Statement::_getFct() const
{
    return function;
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::_getFirst() const
{
    return first;
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::_getSecond() const
{
    return second;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Statement::_getFeatures() const
{
    return features;
}

/* **************************************************
 *
 ************************************************** */
bitsetPtr Statement::_getBitset() const
{
    return bitset;
}

/* **************************************************
 *
 ************************************************** */
uint8_t Statement::getFirst() const
{
    uint8_t lowByte = code & 0xFF;
    return lowByte;
}

/* **************************************************
 *
 ************************************************** */
uint32_t Statement::getCode() const
{
    return code;
}

/* **************************************************
 *
 ************************************************** */
uint8_t Statement::getSecond() const
{
    uint8_t highByte = (code >> 8) & 0xFF;
    return highByte;
}

/* **************************************************
 *
 ************************************************** */
std::string &Statement::_getString()
{
    return string;
}

/* **************************************************
 *
 ************************************************** */
pairpPtr Statement::_getPairp() const
{
    return pairp;
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Statement::_getStatements() const
{
    return statements;
}

/* **************************************************
 *
 ************************************************** */
double Statement::_getNumber() const
{
    return number;
}

/* **************************************************
 *
 ************************************************** */
uint32_t Statement::_getLineno() const
{
    return lineno;
}

/* **************************************************
 *
 ************************************************** */
std::string Statement::_getBufferName() const
{
    return bufferName;
}

/* **************************************************
 *
 ************************************************** */
void Statement::brln(std::ostream &out, int tabulation) const
{
    out << "<BR>";
    for (uint8_t j = 1; j <= tabulation; ++j)
        out << "&nbsp;";
}

/* **************************************************
 *
 ************************************************** */
void Statement::toHTML(std::ostream &out, uint8_t tabulationLenght, uint8_t tabulation, uint32_t color, uint32_t bgcolor) const
{
#define BLACK 0x000000u
#define RED 0xFF0000u
#define PINK 0xFFC0CBu
#define GREEN 0x90EE90u
#define BLUE 0x0000FFu
#define GRAY 0xB7B7B7u
#define OPENSPAN \
    if (color)   \
        out << "<SPAN style=\"color:#" << std::setfill('0') << std::setw(6) << std::hex << color << ";background-color:#" << std::setw(6) << std::hex << bgcolor << ";\">";
#define CLOSESPAN \
    if (color)    \
        out << "</SPAN>";
#define BR out << "<BR>";

    if (isSetFlags(Flags::SEEN))
        color |= BLUE;
    if (isSetFlags(Flags::DISABLED))
        color |= GRAY;
    if (isSetFlags(Flags::BOTTOM))
        color |= RED;

    switch (this->op)
    {

    case GUARD_STATEMENT:
        OPENSPAN;
        features->flatPrint(out);
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case ATTEST_STATEMENT:
        OPENSPAN;
        out << "<B>attest</B>&nbsp;";
        first->toHTML(out);
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case ASSIGNMENT_STATEMENT:
        OPENSPAN;
        first->toHTML(out);
        out << "&nbsp;=&nbsp;";
        second->toHTML(out);
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case SUBSUME_STATEMENT:
        OPENSPAN;
        first->toHTML(out);
        out << "&nbsp;⊂&nbsp;";
        second->toHTML(out);
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case PRINT_STATEMENT:
        OPENSPAN;
        out << "<B>print</B>&nbsp;";
        statements->print(out, tabulationLenght, tabulation, color, bgcolor, false, "(", ")", ",&nbsp;");
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case PRINTLN_STATEMENT:
        OPENSPAN;
        out << "<B>println</B>&nbsp;";
        statements->print(out, tabulationLenght, tabulation, color, bgcolor, false, "(", ")", ",&nbsp;");
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case EPRINT_STATEMENT:
        OPENSPAN;
        out << "<B>eprint</B>&nbsp;";
        statements->print(out, tabulationLenght, tabulation, color, bgcolor, false, "(", ")", ",&nbsp;");
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case EPRINTLN_STATEMENT:
        OPENSPAN;
        out << "<B>eprintln</B>&nbsp;";
        statements->print(out, tabulationLenght, tabulation, color, bgcolor, false, "(", ")", ",&nbsp;");
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case SEARCH_STATEMENT:
        out << "<B>search</B>&nbsp;";
        first->toHTML(out);
        out << "&nbsp;<B>on</B>&nbsp;";
        out << Vartable::codeToName(code);
        break;

    case STMS_STATEMENT:
        statements->print(out, tabulationLenght, tabulation, color, bgcolor, true, "{", "}", "");
        break;

    case IF_STATEMENT:
        OPENSPAN;
        out << "<B>if</B>&nbsp;(";
        first->toHTML(out);
        out << ')';
        CLOSESPAN;
        second->toHTML(out, tabulationLenght, tabulation, color, bgcolor);
        break;

    case THEN_STATEMENT:
        if (first->isSetFlags(Flags::REJECTED))
            bgcolor = PINK;
        if (first->isSetFlags(Flags::CHOOSEN))
            bgcolor = GREEN;
        if (first->isStms())
            first->toHTML(out, tabulationLenght, tabulation, color, bgcolor);
        else
        {
            brln(out, tabulation + tabulationLenght);
            first->toHTML(out, tabulationLenght, tabulation + tabulationLenght, color, bgcolor);
        }

        break;

    case THEN_ELSE_STATEMENT:
        if (first->isSetFlags(Flags::REJECTED))
            bgcolor = PINK;
        if (first->isSetFlags(Flags::CHOOSEN))
            bgcolor = GREEN;
        if (first->isStms())
            first->toHTML(out, tabulationLenght, tabulation, color, bgcolor);
        else
        {
            brln(out, tabulation + tabulationLenght);
            first->toHTML(out, tabulationLenght, tabulation + tabulationLenght, color, bgcolor);
        }

        if (second)
        {
            for (uint8_t j = 1; j <= tabulation; j++)
                out << "&nbsp;";

            if (second->isSetFlags(Flags::REJECTED))
                bgcolor = PINK;
            if (second->isSetFlags(Flags::CHOOSEN))
                bgcolor = GREEN;
            if (second->isStms())
            {
                OPENSPAN;
                out << "<B>else</B>";
                CLOSESPAN;
                second->toHTML(out, tabulationLenght, tabulation, color, bgcolor);
            }
            else if (second->isIf())
            {
                OPENSPAN;
                out << "<B>elseif</B>&nbsp;(";
                second->first->toHTML(out);
                out << ')';
                CLOSESPAN;
                second->second->toHTML(out, tabulationLenght, tabulation, color, bgcolor);
            }
            else
            {
                OPENSPAN;
                out << "<B>else</B>";
                CLOSESPAN;
                brln(out, tabulation + tabulationLenght);
                second->toHTML(out, tabulationLenght, tabulation + tabulationLenght, color, bgcolor);
            }
        }
        break;

    case DEFERRED_STATEMENT:
        OPENSPAN;
        out << "<B>deferred</B>&nbsp;(";
        first->toHTML(out);
        out << ')';
        CLOSESPAN;
        if (second->isStms())
        {
            second->toHTML(out, tabulationLenght, tabulation, color);
        }
        else
        {
            brln(out, tabulation + tabulationLenght);
            second->toHTML(out, tabulationLenght, tabulation + tabulationLenght, color);
        }
        break;

    case FOREACH_STATEMENT:
        OPENSPAN;
        out << "<B>foreach</B>&nbsp;";
        out << Vartable::codeToName(code);
        out << "&nbsp;";
        CLOSESPAN;
        first->toHTML(out, tabulationLenght, tabulation, color);
        break;

    case FOREACH_CON_T_STATEMENT:
        OPENSPAN;
        out << "<B>in</B>&nbsp;";
        first->toHTML(out);
        CLOSESPAN;
        if (second->isStms())
            second->toHTML(out, tabulationLenght, tabulation, color);
        else
        {
            brln(out, tabulation + tabulationLenght);
            second->toHTML(out, tabulationLenght, tabulation + tabulationLenght, color);
        }
        break;

    case NIL_STATEMENT:
        out << "<B>NIL</B>";
        break;

    case CONSTANT_STATEMENT:
        out << bitset->toString();
        break;

    case VARIABLE_STATEMENT:
        out << '$' << Vartable::codeToName(code);
        break;

    case ANONYMOUS_STATEMENT:
        out << '_';
        break;

    case FEATURES_STATEMENT:
        features->flatPrint(out);
        break;

    case PAIRP_STATEMENT:
        pairp->flatPrint(out, true);
        break;

    case UNIF_STATEMENT:
        out << "&nbsp;(";
        first->toHTML(out);
        out << "&nbsp;∪&nbsp;";
        second->toHTML(out);
        out << ")&nbsp;";
        break;

    case INHERITED_FEATURES_STATEMENT:
        out << "↑";
        break;

    case SYNTHESIZED_FEATURES_STATEMENT:
        out << "⇑";
        break;

    case DASH_STATEMENT:
        out << '#' << std::to_string(getFirst() + 1);
        if (getSecond() != UINT8_MAX)
            out << "." << std::to_string(getSecond() + 1);
        break;

    case INHERITED_CHILDREN_FEATURES_STATEMENT:
        out << "↓" << std::to_string(getFirst() + 1);
        break;

    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
        out << "⇓";
        out << std::to_string(getFirst() + 1);
        break;

    case STRING_STATEMENT:
        out << "&quot;" << string << "&quot;";
        break;

    case NUMBER_STATEMENT:
        out << number;
        break;

    case FUNCTION_STATEMENT:
        switch (function)
        {
        case NOP:
            out << "<B>nop</B>&nbsp;";
            break;
        case NOT:
            out << "¬";
            out << "&nbsp;(";
            first->toHTML(out);
            out << ")&nbsp;";
            break;
        case AND:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;∧&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case OR:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;∨&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case PLUS:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;+&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case MINUS:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;-&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case TIMES:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;*&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case DIVIDE:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;/&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case MODULO:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;%&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case FLOOR:
            out << "&nbsp;floor(";
            first->toHTML(out);
            out << ")&nbsp;";
            break;
        case EQUAL:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;==&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case DIFF:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;≠&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case LT:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;<&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case LE:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;≤&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case GT:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;>&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case GE:
            out << "&nbsp;(";
            first->toHTML(out);
            out << "&nbsp;≥&nbsp;";
            second->toHTML(out);
            out << ")&nbsp;";
            break;
        case MINUS_U:
            out << "-&nbsp;";
            first->toHTML(out);
            break;
        case RANDOM:
            out << "rand()";
            break;
        }
    }
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::clone(const std::bitset<MAX_FLAGS> &protectedFlags)
{
    statementPtr statement = shared_from_this();
    switch (op)
    {
    case INHERITED_FEATURES_STATEMENT:
    case SYNTHESIZED_FEATURES_STATEMENT:
    case NIL_STATEMENT:
    case DASH_STATEMENT:
    case INHERITED_CHILDREN_FEATURES_STATEMENT:
    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
    case STRING_STATEMENT:
    case NUMBER_STATEMENT:
    case ANONYMOUS_STATEMENT:
        statement = shared_from_this();
        break;
    case FEATURES_STATEMENT:
    case GUARD_STATEMENT:
        statement = Statement::createFeatures(this->lineno, this->bufferName, op, this->rootOp, features->clone());
        break;
    case PAIRP_STATEMENT:
        statement = Statement::createPairp(this->lineno, this->bufferName, this->rootOp, pairp->clone());
        break;
    case CONSTANT_STATEMENT:
        statement = Statement::createConstant(this->lineno, this->bufferName, this->rootOp, bitset->clone());
        break;
    case VARIABLE_STATEMENT:
        statement = Statement::createVariable(this->lineno, this->bufferName, this->rootOp, code);
        break;
    case ATTEST_STATEMENT:
        statement = Statement::createFirst(this->lineno, this->bufferName, op, this->rootOp, first ? first->clone(protectedFlags) : statementPtr());
        break;
    case IF_STATEMENT:
    case THEN_STATEMENT:
    case THEN_ELSE_STATEMENT:
    case FOREACH_CON_T_STATEMENT:
    case DEFERRED_STATEMENT:
    case UNIF_STATEMENT:
    case ASSIGNMENT_STATEMENT:
    case SUBSUME_STATEMENT:
        statement = Statement::createFirstSecond(this->lineno, this->bufferName, op, this->rootOp,
                                                 first ? first->clone(protectedFlags) : statementPtr(),
                                                 second ? second->clone(protectedFlags) : statementPtr());
        break;
    case FOREACH_STATEMENT:
        statement = Statement::createForeach(this->lineno, this->bufferName, this->rootOp,
                                             code,
                                             first ? first->clone(protectedFlags) : statementPtr());
        break;
    case FUNCTION_STATEMENT:
        statement = Statement::createFunction(this->lineno, this->bufferName, this->rootOp, function,
                                              first ? first->clone(protectedFlags) : statementPtr(),
                                              second ? second->clone(protectedFlags) : statementPtr());
        break;
    case STMS_STATEMENT:
    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:
    case EPRINT_STATEMENT:
    case EPRINTLN_STATEMENT:
        statement = Statement::createStatements(this->lineno, this->bufferName, op, this->rootOp,
                                                statements->clone(protectedFlags));
        break;
    case SEARCH_STATEMENT:
        statement = Statement::createSearch(this->lineno, this->bufferName, this->rootOp,
                                            code, first ? first->clone(protectedFlags) : statementPtr());
        break;
    }
    statement->addFlags(protectedFlags & this->getFlags());
    return statement;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr
Statement::evalFeatures(class Item *item, Parser &parser, Generator *synthesizer, bool replaceVariables, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::evalFeatures #######################" << std::endl;
    std::cout << "<div>evalFeatures: " << std::endl;
    this->toHTML(std::cout);
    std::cout << std::endl;
    item->toHTML(std::cout);
    std::cout << "</div>" << std::endl;
#endif

    featuresPtr resultFeatures = Features::NIL;
    switch (op)
    {
    case FEATURES_STATEMENT:
    case GUARD_STATEMENT:
    {
        resultFeatures = features->clone();
        if (replaceVariables && item && !item->environmentIsEmpty())
        {
            bool effect = false;
            item->environmentReplaceVariables(resultFeatures, effect);
        }
    }
    break;

    case INHERITED_FEATURES_STATEMENT:
    {
        resultFeatures = item->getInheritedFeatures()->clone();
        if (replaceVariables && item && !item->environmentIsEmpty())
        {
            bool effect = false;
            item->environmentReplaceVariables(resultFeatures, effect);
        }
    }
    break;

    case VARIABLE_STATEMENT:
    {
        valuePtr _value = item->environmentGet(code);
        if (!_value)
        {
            FATAL_ERROR_STM(shared_from_this());
        }
        if (_value && _value->isFeatures())
            resultFeatures = _value->getFeatures()->clone();
    }
    break;

    case INHERITED_CHILDREN_FEATURES_STATEMENT:
    {
        resultFeatures = (*item->getInheritedChildFeatures())[getFirst()]->clone();
        if (replaceVariables && item && !item->environmentIsEmpty())
        {
            bool effect = false;
            item->environmentReplaceVariables(resultFeatures, effect);
        }
    }
    break;

    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
    {
        resultFeatures = (*item->getSynthesizedChildFeatures())[getFirst()]->clone();
        if (replaceVariables && item && !item->environmentIsEmpty())
        {
            bool effect = false;
            item->environmentReplaceVariables(resultFeatures, effect);
        }
    }
    break;

    case UNIF_STATEMENT:
    {
        featuresPtr fs1 = first->evalFeatures(item, parser, synthesizer, replaceVariables, verbose);
        featuresPtr fs2 = second->evalFeatures(item, parser, synthesizer, replaceVariables, verbose);
        if ((!fs1) || (!fs2))
        {
            resultFeatures = featuresPtr();
        }
        else
        {
            fs1->subFlags(Flags::SEEN);
            fs2->subFlags(Flags::SEEN);
            resultFeatures = unif(shared_from_this(), fs1, fs2, item, verbose);
            if (replaceVariables && item && !item->environmentIsEmpty())
            {
                bool effect = false;
                item->environmentReplaceVariables(resultFeatures, effect);
            }
        }
    }
    break;

    default:
        FATAL_ERROR_UNEXPECTED;
    }
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::evalFeatures DONE #######################" << std::endl;
    std::cout << "<div>" << std::endl;
    this->toHTML(std::cout);
    std::cout << std::endl;
    if (resultFeatures)
        resultFeatures->toHTML(std::cout);
    else
        std::cout << "NULL";
    std::cout << "</div>" << std::endl;
#endif
    return resultFeatures;
}

/* **************************************************
 *
 ************************************************** */
pairpPtr Statement::evalPairp(class Item *item, Parser &parser, Generator *synthesizer, bool replaceVariables, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::evalPairp #######################" << std::endl;
    std::cout << "<div>" << std::endl;
    this->toHTML(std::cout);
    std::cout << "</div>" << std::endl;
#endif
    pairpPtr resultPairp = Pairp::NIL;
    switch (op)
    {

    case PAIRP_STATEMENT:
        resultPairp = pairp->clone();
        if (replaceVariables && item && !item->environmentIsEmpty())
        {
            bool effect = false;
            item->environmentReplaceVariables(resultPairp, effect);
        }
        break;

    case VARIABLE_STATEMENT:
    {
        valuePtr _value = item->environmentGet(code);
        if (!_value)
        {
            FATAL_ERROR_STM(shared_from_this());
        }
        else if (_value->isNil())
            resultPairp = Pairp::NIL;
        else if (_value->isPairp())
            resultPairp = _value->getPairp()->clone();
        else
        {
            std::ostringstream oss1, oss2;
            this->toHTML(oss1);
            item->printRule(oss2, -1, true);
            WARNING_STM;
            "<P>Variable " + oss1.str() + " not initialized in</P>" + oss2.str();
        }
    }
    break;

    case SEARCH_STATEMENT:
    {
        featuresPtr features = first->evalFeatures(item, parser, synthesizer, replaceVariables, verbose);
        if (!features)
        {
            FATAL_ERROR_UNEXPECTED;
        }
        uint32_t head = features->assignHead();
        uint32_t pos = code;
        auto foundpos = parser.findCacheLexicon(pos);
        if (foundpos != parser.cendCacheLexicon() && (!foundpos->second->empty()))
        {
            Parser::entries_map *listHead = foundpos->second;
            entriesPtr entries = synthesizer->findByHeadThenCompactedLexicon(parser, listHead, pos, head);
            if (entries && entries->size() > 0)
            {
                for (auto &entry : *entries)
                {
                    // auto it = entries->begin();
                    featuresPtr entryFeatures = entry->getFeatures();
                    if (entryFeatures)
                    {
                        std::stringstream stringStream;
                        entryFeatures->flatPrint(stringStream);
                        parser.parseBuffer("#(", ")", stringStream.str(), stringStream.str());
                        if (resultPairp->isNil())
                            resultPairp = Pairp::create(Value::createFeatures(parser.getLocalFeatures()));
                        else
                            resultPairp = Pairp::create(Pairp::create(Value::createFeatures(parser.getLocalFeatures())), resultPairp);
                    }
                }
            }
            else
            {
                // throw fatal_exception("search operator error: No entry for " + Vartable::codeToString(features->assignHead()));
            }
        }
    }
    break;

    default:
        FATAL_ERROR_UNEXPECTED;
        break;
    }
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::evalPairp DONE #######################" << std::endl;
    std::cout << "<div>" << std::endl;
    this->toHTML(std::cout);
    std::cout << std::endl;
    if (resultPairp)
        resultPairp->toHTML(std::cout);
    else
        std::cout << "NULL";
    std::cout << "</div>" << std::endl;
#endif
    return resultPairp;
}

/* **************************************************
 *
 ************************************************** */
valuePtr Statement::evalValue(class Item *item, Parser &parser, Generator *synthesizer, bool replaceVariables, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::evalValue #######################" << std::endl;
    std::cout << "<div>" << std::endl;
    this->toHTML(std::cout, 0);
    item->toHTML(std::cout);
    std::cout << "</div>" << std::endl;
    std::cout << "<H3>####################### ITEM #######################</H3>" << std::endl;
    item->toHTML(std::cout);
    std::cout << std::endl;
#endif
    valuePtr resultValue = valuePtr();
    featuresPtr resultFeatures = featuresPtr();
    pairpPtr resultPairp = pairpPtr();
    switch (op)
    {

    case NIL_STATEMENT:
        resultValue = Value::STATIC_NIL;
        break;

    case ANONYMOUS_STATEMENT:
        resultValue = Value::STATIC_ANONYMOUS;
        break;

    case DASH_STATEMENT:
    {
        uint8_t first = getFirst();
        uint8_t second = getSecond();
        termsPtr t = item->getTerms(first);
        if (t->isOptional())
        {
            resultValue = Value::STATIC_FALSE;
        }
        else
        {
            // if (#i)
            if (second == UINT8_MAX)
            {
                resultValue = Value::STATIC_TRUE;
            }
            // if (#i.j)
            else
            {
                if (second == item->getIndexTerms()[first])
                {
                    resultValue = Value::STATIC_TRUE;
                }
                else
                {
                    resultValue = Value::STATIC_FALSE;
                }
            }
        }
        goto valueBuilt;
    }
    break;

    case NUMBER_STATEMENT:
        resultValue = Value::createNumber(number);
        goto valueBuilt;
        break;

    case STRING_STATEMENT:
        resultValue = Value::createForm(string);
        goto valueBuilt;
        break;

    case FEATURES_STATEMENT:
        resultFeatures = features;
        break;

    case INHERITED_FEATURES_STATEMENT:
        resultFeatures = item->getInheritedFeatures();
        break;

    case SYNTHESIZED_FEATURES_STATEMENT:
        resultFeatures = item->getSynthesizedFeatures();
        break;

    case VARIABLE_STATEMENT:
        if (replaceVariables)
        {
            resultValue = item->environmentGet(code);
            if (!resultValue)
            {
                FATAL_ERROR_MSG("Variable " + Vartable::codeToName(code) + " not available");
            }
            goto valueBuilt;
        }
        else if (replaceVariables)
        {
            FATAL_ERROR_MSG("Variable " + Vartable::codeToName(code) + " not available");
            resultValue = valuePtr();
            goto valueBuilt;
        }
        else
        {
            resultValue = Value::createVariable(code);
        }
        break;

    case CONSTANT_STATEMENT:
        resultValue = Value::createConstant(bitset);
        break;

    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
        resultFeatures = (*item->getSynthesizedChildFeatures())[getFirst()];
        break;

    case INHERITED_CHILDREN_FEATURES_STATEMENT:
        resultFeatures = (*item->getInheritedChildFeatures())[getFirst()];
        break;

    case UNIF_STATEMENT:
    {
        featuresPtr fs1 = first->evalFeatures(item, parser, synthesizer, replaceVariables, verbose);
        if (!fs1)
        {
            resultValue = valuePtr();
            goto valueBuilt;
        }
        else
        {
            featuresPtr fs2 = second->evalFeatures(item, parser, synthesizer, replaceVariables, verbose);
            if (!fs2)
            {
                resultValue = valuePtr();
                goto valueBuilt;
            }
            else
            {
                fs1->subFlags(Flags::SEEN);
                fs2->subFlags(Flags::SEEN);
                resultFeatures = unif(shared_from_this(), fs1, fs2, item, verbose);
            }
        }
    }
    break;

    case SEARCH_STATEMENT:
        resultPairp = evalPairp(item, parser, synthesizer, replaceVariables, verbose);
        break;

    case ATTEST_STATEMENT:
        FATAL_ERROR_STM(shared_from_this());
        break;

    case PAIRP_STATEMENT:
        resultPairp = evalPairp(item, parser, synthesizer, replaceVariables, verbose);
        break;

    case FUNCTION_STATEMENT:
        switch (function)
        {
        case NOP:
            break;

        case NOT:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if (!v1)
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                // FATAL_ERROR_UNEXPECTED;
            }
            else if (v1->isFalse())
            {
                resultValue = Value::STATIC_TRUE;
            }
            else
                resultValue = Value::STATIC_FALSE;
            goto valueBuilt;
        }
        break;

        case AND:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if (!v1 || !v2)
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isFalse()) || (v2->isFalse()))
            {
                resultValue = Value::STATIC_FALSE;
            }
            else
            {
                resultValue = Value::STATIC_TRUE;
            }
            goto valueBuilt;
        }
        break;

        case OR:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) || (!v2))
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isFalse()) && (v2->isFalse()))
                resultValue = Value::STATIC_FALSE;
            else
                resultValue = Value::STATIC_TRUE;
            goto valueBuilt;
        }
        break;

        case PLUS:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            bool isv1astring = false;
            std::string v1str;
            if (v1)
            {
                isv1astring = true;
                if (v1->isVariable())
                    v1str = v1->getBitset()->to_string();
                else if (v1->isIdentifier())
                    v1str = Vartable::codeToName(v1->getCode());
                else if (v1->isString())
                    v1str = v1->getString();
                else
                    isv1astring = false;
            }
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            bool isv2astring = false;
            std::string v2str;
            if (v2)
            {
                isv2astring = true;
                if (v2->isVariable())
                    v2str = v2->getBitset()->to_string();
                else if (v2->isIdentifier())
                    v2str = Vartable::codeToName(v2->getCode());
                else if (v2->isString())
                    v2str = v2->getString();
                else
                    isv2astring = false;
            }

            if ((!v1) || (!v2))
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }

            else if ((v1->isNumber()) && (v2->isNumber()))
            {
                resultValue = Value::createNumber(v1->getNumber() + v2->getNumber());
            }

            else if (isv1astring && isv2astring)
            {
                resultValue = Value::createForm(v1str + v2str);
            }

            else
            {
                std::cout << "Error line " << this->lineno << ": plus operator applied to non numbers or non strings: ";
                v1->flatPrint(std::cout);
                std::cout << " + ";
                v2->flatPrint(std::cout);
                FATAL_ERROR_UNEXPECTED
            }
            goto valueBuilt;
        }
        break;

        case MINUS:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) || (!v2))
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isNumber()) && (v2->isNumber()))
            {
                resultValue = Value::createNumber(v1->getNumber() - v2->getNumber());
            }
            else
            {
                std::cout << "Error line " << this->lineno << ": minus operator applied to non numbers: ";
                v1->flatPrint(std::cout);
                std::cout << " - ";
                v2->flatPrint(std::cout);
                FATAL_ERROR_UNEXPECTED
            }
            goto valueBuilt;
        }
        break;

        case TIMES:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) || (!v2))
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isNumber()) && (v2->isNumber()))
            {
                resultValue = Value::createNumber(v1->getNumber() * v2->getNumber());
            }
            else
            {
                std::cout << "Error line " << this->lineno << ": times operator applied to non numbers: ";
                v1->flatPrint(std::cout);
                std::cout << " * ";
                v2->flatPrint(std::cout);
                FATAL_ERROR_UNEXPECTED;
            }
            goto valueBuilt;
        }
        break;

        case DIVIDE:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) || (!v2))
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isNumber()) && (v2->isNumber()))
            {
                resultValue = Value::createNumber(v1->getNumber() / v2->getNumber());
            }
            else
            {
                std::cout << "Error line " << this->lineno << ": divide operator applied to non numbers: ";
                v1->flatPrint(std::cout);
                std::cout << " / ";
                v2->flatPrint(std::cout);
                FATAL_ERROR_UNEXPECTED;
            }
            goto valueBuilt;
        }
        break;

        case MODULO:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) || (!v2))
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isNumber()) && (v2->isNumber()))
            {
                resultValue = Value::createNumber(fmod(v1->getNumber(), v2->getNumber()));
            }
            else
            {
                std::cout << "Error line " << this->lineno << ": modulo operator applied to non numbers: ";
                v1->flatPrint(std::cout);
                std::cout << " % ";
                v2->flatPrint(std::cout);
                FATAL_ERROR_UNEXPECTED;
            }
            goto valueBuilt;
        }
        break;

        case MINUS_U:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if (!v1)
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isNumber()))
            {
                resultValue = Value::createNumber(-v1->getNumber());
            }
            else
            {
                std::cout << "Error line " << this->lineno << ": minus operator applied to non numbers: ";
                std::cout << " - ";
                v1->flatPrint(std::cout);
                FATAL_ERROR_UNEXPECTED;
            }
            goto valueBuilt;
        }
        break;

        case FLOOR:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if (!v1)
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isNumber()))
            {
                resultValue = Value::createNumber(floor(v1->getNumber()));
            }
            else
            {
                std::cout << "Error line " << this->lineno << ": floor operator applied to non numbers: ";
                std::cout << " floor ";
                v1->flatPrint(std::cout);
                FATAL_ERROR_UNEXPECTED;
            }
            goto valueBuilt;
        }
        break;

        case EQUAL:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) && (!v2))
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
                // resultValue = Value::STATIC_TRUE;
            }
            else if (!v1 || !v2)
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                resultValue = valuePtr();
                FATAL_ERROR_UNEXPECTED;
                // resultValue = Value::STATIC_FALSE;
            }

            else if (v1->equal(v2))
                resultValue = Value::STATIC_TRUE;

            else
                resultValue = Value::STATIC_FALSE;

            goto valueBuilt;
        }
        break;

        case DIFF:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) && (!v2))
                resultValue = Value::STATIC_FALSE;

            else if ((!v1) || (!v2))
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = Value::STATIC_TRUE;
            }

            else if (v1->equal(v2))
                resultValue = Value::STATIC_FALSE;

            else
                resultValue = Value::STATIC_TRUE;

            goto valueBuilt;
        }
        break;

        case LT:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            // si l'une est nulle
            if ((!v1) || (!v2))
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = Value::STATIC_NIL;
            }
            else if (v1->lessThan(v2))
                resultValue = Value::STATIC_TRUE;
            else
                resultValue = Value::STATIC_NIL;
            goto valueBuilt;
        }
        break;

        case LE:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            // si l'une est variable libre
            if ((!v1) || (!v2))
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = Value::STATIC_NIL;
            }
            else if ((v1->lessThan(v2)) || (v1->equal(v2)))
                resultValue = Value::STATIC_TRUE;
            else
                resultValue = Value::STATIC_NIL;
            goto valueBuilt;
        }
        break;

        case GT:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            // si l'une est variable libre
            if ((!v1) || (!v2))
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = Value::STATIC_NIL;
            }
            else if (!(v1->lessThan(v2)) && (!(v1->equal(v2))))
                resultValue = Value::STATIC_TRUE;
            else
                resultValue = Value::STATIC_NIL;
            goto valueBuilt;
        }
        break;

        case GE:
        {
            valuePtr v1 = first->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = second->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            // si l'une est variable libre
            if ((!v1) || (!v2))
            {
                std::cout << "Error line " << this->lineno << ": Value not available" << std::endl;
                FATAL_ERROR_UNEXPECTED;
                resultValue = Value::STATIC_NIL;
            }
            else if (!(v1->lessThan(v2)))
                resultValue = Value::STATIC_TRUE;
            else
                resultValue = Value::STATIC_NIL;
            goto valueBuilt;
        }
        break;

        case RANDOM:
            resultValue = Value::createNumber((double)rand());
            goto valueBuilt;
            break;
        }
        break;

    default:
        FATAL_ERROR_UNEXPECTED;
        break;
    }

    if (!resultFeatures && !resultValue && !resultPairp /* && !resultListFeatures*/)
    {
        FATAL_ERROR_UNEXPECTED;
    }

    if (resultPairp)
    {
        if (replaceVariables && !item->environmentIsEmpty())
        {
            bool effect = false;
            item->environmentReplaceVariables(resultPairp, effect);
        }
        resultValue = Value::createPairp(resultPairp);
    }

    else if (resultFeatures)
    {
        if (resultFeatures->isNil())
            resultValue = Value::STATIC_NIL;
        else if (resultFeatures->isBottom())
            resultValue = Value::STATIC_NIL;
        else
        {
            if (replaceVariables && !item->environmentIsEmpty())
            {
                bool effect = false;
                item->environmentReplaceVariables(resultFeatures, effect);
            }
            resultValue = Value::createFeatures(resultFeatures);
        }
    }

valueBuilt:
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::evalValue DONE #######################" << std::endl;
    std::cout << "<div>" << std::endl;
    this->toHTML(std::cout);
    std::cout << "<H3>";
    if (resultValue)
        resultValue->toHTML(std::cout);
    else
        std::cout << "NULL";
    std::cout << "</H3>";
    std::cout << "</div>" << std::endl;
#endif
    return resultValue;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Statement::unif(statementPtr statementRoot, const featuresPtr &fs1, const featuresPtr &fs2, class Item *item, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::unif #######################" << std::endl;
    std::cout << "<table border=\"1\"><tr><th>fs1</th><th>fs2</th><th>Environment</th></tr>";
    std::cout << "<tr><td>";
    if (fs1)
        fs1->toHTML(std::cout);
    std::cout << "</td><td>";
    if (fs2)
        fs2->toHTML(std::cout);
    std::cout << "</td><td>";
    if (item->_getEnvironment())
        item->_getEnvironment()->toHTML(std::cout);
    std::cout << "</td></tr></table>";
#endif

    featuresPtr result = featuresPtr();

    if (!fs1 || !fs2)
    {
        result = Features::NIL;
        goto endUnif;
    }
    if (fs1->isBottom() || fs2->isBottom())
    {
        result = Features::BOTTOM;
        goto endUnif;
    }
    if (fs1->isNil() && fs2->isNil())
    {
        result = Features::NIL;
        goto endUnif;
    }
    if (fs1->isNil())
    {
        result = fs2;
        goto endUnif;
    }
    if (fs2->isNil())
    {
        result = fs1;
        goto endUnif;
    }
    result = Features::create();
    for (Features::list_of_feature::const_iterator i1 = fs1->begin(); i1 != fs1->end(); ++i1)
    {

        if ((*i1)->isHead() || (*i1)->isLemma())
        {
            Features::list_of_feature::const_iterator i2 = fs2->begin();
            while (i2 != fs2->end())
            {
                if ((*i2)->getType() == (*i1)->getType())
                {
                    (*i2)->addFlags(Flags::SEEN);
                    switch ((*i1)->getValue()->getType())
                    {

                    case Value::IDENTIFIER_VALUE:
                    {
                        switch ((*i2)->getValue()->getType())
                        {
                        case Value::IDENTIFIER_VALUE:
                            if ((*i1)->getValue()->getCode() != (*i2)->getValue()->getCode())
                            {
                                result = Features::BOTTOM;
                                goto endUnif;
                            }
                            break;

                        case Value::VARIABLE_VALUE:
                            result->add(Feature::createHead((*i1)->getValue()));
                            item->environmentAdd(statementRoot, (*i2)->getValue()->getCode(), (*i1)->getValue(), verbose);
                            break;

                        default:
                            FATAL_ERROR_STM(statementRoot);
                            break;
                        }
                    }
                    break;

                    case Value::VARIABLE_VALUE:

                        if (((*i2)->getValue()->isVariable()) &&
                            ((*i1)->getValue()->getCode() == (*i2)->getValue()->getCode()))
                        {
                        } /* empty */
                        else
                        {
                            if (item)
                            {
                                item->environmentAdd(statementRoot, (*i1)->getValue()->getCode(), (*i2)->getValue(), verbose);
                            }
                        }
                        result->add(Feature::createHead((*i2)->getValue()));
                        break;

                    case Value::ANONYMOUS_VALUE:
                        result->add(Feature::createHead((*i2)->getValue()));
                        break;

                    default:
                        FATAL_ERROR_STM(statementRoot);
                        break;
                    }

                    break;
                }
                ++i2;
            }
            result->add(*i1);
        }
        else if ((*i1)->isForm())
        {
            Features::list_of_feature::const_iterator i2 = fs2->begin();
            while (i2 != fs2->end())
            {
                if ((*i2)->isForm())
                {

                    (*i2)->addFlags(Flags::SEEN);
                    if (!(*i1)->getValue()->isString() || !(*i2)->getValue()->isString())
                        FATAL_ERROR_STM(statementRoot);

                    if ((*i1)->getValue()->getString() != (*i2)->getValue()->getString())
                    {
                        result = Features::BOTTOM;
                        goto endUnif;
                    }
                    break;
                }

                ++i2;
            }
            result->add(*i1);
        }
        else if ((*i1)->isConstant())
        {
            Features::list_of_feature::const_iterator i2 = fs2->begin();
            while (i2 != fs2->end())
            {
                if (((*i2)->isConstant()) &&
                    (*(*i1)->getAttribute() & *(*i2)->getAttribute()).any())
                {
                    (*i2)->addFlags(Flags::SEEN);
                    if ((!(*i1)->getValue()) || (!(*i2)->getValue()))
                    {
                        result = Features::BOTTOM;
                        goto endUnif;
                    }

                    switch ((*i1)->getValue()->getType())
                    {

                    case Value::NIL_VALUE:
                    case Value::FALSE_VALUE:
                        FATAL_ERROR_UNEXPECTED

                    case Value::FORM_VALUE:
                        switch ((*i2)->getValue()->getType())
                        {
                        case Value::FORM_VALUE:
                            if ((*i1)->getValue()->getString() != (*i2)->getValue()->getString())
                            {
                                result = Features::BOTTOM;
                                goto endUnif;
                            }
                            result->add(Feature::createConstant((*i1)->getAttribute(),
                                                                (*i1)->getValue()));
                            break;

                        case Value::VARIABLE_VALUE:
                            FATAL_ERROR_STM(statementRoot);
                            /*
                          result->add(new Feature((*i2)->getAttribute(), (*i1)->getValue(), Feature::CONSTANT));
                          if (item->getEnvironment()==NULL)
                          item->setEnvironment(new Environment());
                          item->getEnvironment()->_add(*(*i2)->getValue()->getBits(), (*i1)->getValue());
                            */
                            break;

                        default:
                            FATAL_ERROR_STM(statementRoot);
                            break;
                        }
                        break;

                        // case Value::FALSE:
                    case Value::TRUE_VALUE:
                    {
                        switch ((*i2)->getValue()->getType())
                        {
                        // case Value::FALSE:
                        case Value::TRUE_VALUE:
                            if ((*i1)->getValue()->isNil() != (*i2)->getValue()->isNil())
                            {
                                result = Features::BOTTOM;
                                goto endUnif;
                            }

                            result->add(Feature::createConstant((*i1)->getAttribute(),
                                                                (*i1)->getValue()));
                            break;
                        case Value::VARIABLE_VALUE:
                            result->add(Feature::createConstant((*i2)->getAttribute(),
                                                                (*i1)->getValue()));
                            item->environmentAdd(statementRoot, (*i2)->getValue()->getCode(), (*i1)->getValue(), verbose);
                            break;
                        default:
                            std::cerr << (*i2)->getValue()->getType();
                            FATAL_ERROR_STM(statementRoot);
                            break;
                        }
                    }
                    break;

                    case Value::NUMBER_VALUE:
                    {
                        switch ((*i2)->getValue()->getType())
                        {
                        case Value::NUMBER_VALUE:
                            if ((*i1)->getValue()->getNumber() != (*i2)->getValue()->getNumber())
                            {
                                result = Features::BOTTOM;
                                goto endUnif;
                            }

                            result->add(Feature::createConstant((*i1)->getAttribute(),
                                                                Value::createNumber((*i1)->getValue()->getNumber())));
                            break;
                        case Value::VARIABLE_VALUE:
                            result->add(Feature::createConstant((*i2)->getAttribute(),
                                                                (*i1)->getValue()));
                            item->environmentAdd(statementRoot, (*i2)->getValue()->getCode(), (*i1)->getValue(), verbose);
                            break;
                        default:
                            FATAL_ERROR_STM(statementRoot);
                            break;
                        }
                    }
                    break;

                    case Value::IDENTIFIER_VALUE:
                    {
                        switch ((*i2)->getValue()->getType())
                        {
                        case Value::IDENTIFIER_VALUE:
                            if ((*i1)->getValue()->getCode() != (*i2)->getValue()->getCode())
                            {
                                result = Features::BOTTOM;
                                goto endUnif;
                            }

                            result->add(Feature::createConstant((*i1)->getAttribute(),
                                                                Value::createIdentifier((*i1)->getValue()->getCode())));
                            break;
                        case Value::VARIABLE_VALUE:
                            result->add(Feature::createConstant((*i2)->getAttribute(),
                                                                (*i1)->getValue()));
                            item->environmentAdd(statementRoot, (*i2)->getValue()->getCode(), (*i1)->getValue(), verbose);
                            break;
                        default:
                            FATAL_ERROR_STM(statementRoot);
                            break;
                        }
                    }
                    break;

                    case Value::CONSTANT_VALUE:
                    {
                        switch ((*i2)->getValue()->getType())
                        {
                        case Value::CONSTANT_VALUE:
                            if (((*(*i1)->getValue()->getBitset()) & (*(*i2)->getValue()->getBitset())).none())
                            {
                                result = Features::BOTTOM;
                                goto endUnif;
                            }

                            result->add(Feature::createConstant((*i1)->getAttribute(),
                                                                Value::createConstant(Bitset::create(
                                                                    *(*i1)->getValue()->getBitset() &
                                                                    *(*i2)->getValue()->getBitset()))));
                            break;
                        case Value::VARIABLE_VALUE:
                            result->add(Feature::createConstant((*i2)->getAttribute(),
                                                                (*i1)->getValue()));
                            item->environmentAdd(statementRoot, (*i2)->getValue()->getCode(), (*i1)->getValue(), verbose);
                            break;
                        case Value::ANONYMOUS_VALUE:
                            result->add(Feature::createConstant((*i2)->getAttribute(),
                                                                (*i1)->getValue()));
                            break;
                        case Value::IDENTIFIER_VALUE:
                        {
                            std::ostringstream oss;
                            oss << "Try to unify an atom with an identifier";
                            FATAL_ERROR_OSS_MSG_STM(statementRoot, oss);
                        }
                        break;

                        default:
                            FATAL_ERROR_UNEXPECTED;
                            break;
                        }
                    }
                    break;

                    case Value::VARIABLE_VALUE:

                        if (((*i2)->getValue()->isVariable()) &&
                            ((*i1)->getValue()->getCode()) == ((*i2)->getValue()->getCode()))
                        {
                        } /* empty */
                        else
                        {
                            if (item)
                            {
                                item->environmentAdd(statementRoot, (*i1)->getValue()->getCode(), (*i2)->getValue(), verbose);
                            }
                        }
                        result->add(Feature::createConstant((*i1)->getAttribute(), (*i2)->getValue()));
                        break;

                    case Value::SYNTHESIZED_CHILD_FEATURES_VALUE:
                        result->add(Feature::createConstant((*i1)->getAttribute(), (*i1)->getValue()));
                        break;

                    case Value::ANONYMOUS_VALUE:
                        result->add(Feature::createConstant((*i1)->getAttribute(), (*i2)->getValue()));
                        break;

                    case Value::FEATURES_VALUE:
                    {
                        featuresPtr _features = unif(statementRoot, (*i1)->getValue()->getFeatures(),
                                                     (*i2)->getValue()->getFeatures(), item, verbose);
                        if (_features->isBottom())
                        {
                            result = _features;
                            goto endUnif;
                        }
                        else
                            result->add(Feature::createConstant((*i1)->getAttribute(),
                                                                Value::createFeatures(_features)));
                    }
                    break;

                    case Value::PAIRP_VALUE:
                        result->add(Feature::createConstant((*i1)->getAttribute(), (*i1)->getValue()));
                        break;
                    }

                    break;
                }
                ++i2;
            }
            if (i2 == fs2->end())
            {
                result->add(*i1);
            }
        }
    }
    for (Features::list_of_feature::const_iterator i2 = fs2->begin(); i2 != fs2->end(); ++i2)
    {
        if ((*i2)->isUnsetFlags(Flags::SEEN))
            result->add(*i2);
    }

    for (Features::list_of_feature::const_iterator i1 = fs1->begin(); i1 != fs1->end(); ++i1)
    {
        (*i1)->subFlags(Flags::SEEN);
    }
    for (Features::list_of_feature::const_iterator i2 = fs2->begin(); i2 != fs2->end(); ++i2)
    {
        (*i2)->subFlags(Flags::SEEN);
    }

endUnif:

#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::unif DONE #######################" << std::endl;
    std::cout << "<table border=\"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
    std::cout << "<tr><td>";
    if (result)
        result->toHTML(std::cout);
    std::cout << "</td><td>";
    if (item->_getEnvironment())
        item->_getEnvironment()->toHTML(std::cout);
    std::cout << "</td></tr></table>";
#endif
    return result;
}

/* ************************************************************
 * ↓i = …
 ************************************************************ */
void Statement::buildInheritedChildFeatures(class Item *item, Parser &parser, Generator *synthesizer, bool replaceVariables, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::buildInheritedChildFeatures #######################" << std::endl;
    std::cout << "buildInheritedChildFeatures: ";
    toHTML(std::cout);
    std::cout << std::endl;
#endif
    if (!item->getInheritedChildFeatures()->get(first->getFirst())->isNil())
    {
        std::ostringstream oss;
        oss << "*** warning: ↓" << first->getFirst() + 1 << " defined twice";
        WARNING_STM_OSS(oss);
    }
    if (item->getInheritedChildFeatures()->size() < first->getFirst())
    {
        std::ostringstream oss;
        oss << "↓" << first->getFirst() + 1 << " not available";
        FATAL_ERROR_OSS_MSG(oss);
    }
    featuresPtr _features = second->evalFeatures(item, parser, synthesizer, true, verbose);

    if (_features->isNil())
    {
        addFlags(Flags::BOTTOM);
    }
    else
    {
        featuresPtr featuresCopy = _features->clone();
        if (replaceVariables && item && !item->environmentIsEmpty() && featuresCopy->containsVariable())
        {
            item->environmentReplaceVariables(featuresCopy, verbose);
        }
        if (replaceVariables && item && featuresCopy->containsSynthesizedChildFeatures())
        {
            item->replaceSynthesizedChildFeaturesValue(featuresCopy);
        }

        item->getInheritedChildFeatures()->add(first->getFirst(), featuresCopy);
    }
}

/* ************************************************************
 * ⇑ = …
 ************************************************************ */
void Statement::buildSynthesizedFeatures(class Item *item, Parser &parser, Generator *synthesizer, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::buildSynthesizedFeatures #######################" << std::endl;
    std::cout << "buildSynthesizedFeatures: ";
    toHTML(std::cout);
    std::cout << std::endl;
#endif
    if (!item->getSynthesizedFeatures()->isNil())
    {
        std::ostringstream oss;
        oss << "⇑"
            << " defined twice";
        FATAL_ERROR_OSS_MSG(oss);
    }
    featuresPtr _features = second->evalFeatures(item, parser, synthesizer, true, verbose);
    if (_features->isNil())
        addFlags(Flags::BOTTOM);
    else
    {
        // CERR_LINE;
        item->setSynthesizedFeatures(_features->clone());
    }
}

/* ************************************************************
 * [ … $X … ] ⊂ ⇓1;
 * $X = ⇓1;
 ************************************************************ */
void Statement::buildEnvironmentWithSynthesize(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::buildEnvironmentWithSynthesize #######################" << std::endl;
    std::cout << "buildEnvironmentWithSynthesize: ";
    toHTML(std::cout);
    std::cout << std::endl;
#endif
    switch (op)
    {
    case ASSIGNMENT_STATEMENT:
    {
        if (!first->isVariable())
        {
            FATAL_ERROR_STM(shared_from_this());
        }
        // $X = ⇓1;
        featuresPtr sonSynth = second->evalFeatures(item, parser, synthesizer, true, verbose);
        if (sonSynth)
        {
            item->environmentAdd(statementRoot, first->code, Value::createFeatures(sonSynth), verbose);
        }
        else
            FATAL_ERROR_STM(shared_from_this());
    }
    break;

    case SUBSUME_STATEMENT:
    {
        // [ … $X … ] ⊂ ...;

        featuresPtr left = first->evalFeatures(item, parser, synthesizer, false, verbose);
        if (!left)
        {
            FATAL_ERROR_STM(shared_from_this());
            // WARNING_STM;
        }
        else
        {
            featuresPtr sonSynth = second->evalFeatures(item, parser, synthesizer, true, verbose);
            if (sonSynth)
            {
                if (!left->buildEnvironment(statementRoot, item->_getEnvironment(), sonSynth, true
#ifdef TRACE_BUILD_ENVIRONMENT
                                            ,
                                            true
#endif
                                            ,
                                            verbose))
                {

                    addFlags(Flags::BOTTOM);
                }
            }
            else
            {
                FATAL_ERROR_STM(shared_from_this());
            }
        }
    }
    break;

    default:
        FATAL_ERROR_UNEXPECTED;
        break;
    }
}

/* ************************************************************
 * [ … $X … ] ⊂ ↑;
 * $X = ↑;
 ************************************************************ */
void Statement::buildEnvironmentWithInherited(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::buildEnvironmentWithInherited #######################" << std::endl;
    std::cout << "buildEnvironmentWithInherited: ";
    toHTML(std::cout);
    std::cout << std::endl;
#endif
    switch (op)
    {
    case ASSIGNMENT_STATEMENT:
    {
        // $X = ↑;
        featuresPtr right = second->evalFeatures(item, parser, synthesizer, true, verbose);
        if (!right)
        {
            WARNING_STM;
        }
        else
        {
            item->environmentAdd(statementRoot, first->code, Value::createFeatures(right), verbose);
        }
    }
    break;

    case SUBSUME_STATEMENT:
    {
        featuresPtr left = first->evalFeatures(item, parser, synthesizer, false, verbose);
        if (!left)
        {
            FATAL_ERROR_UNEXPECTED;
            // WARNING_STM;
        }
        else
        {
            featuresPtr right = second->evalFeatures(item, parser, synthesizer, true, verbose);
            if (!right)
            {
                FATAL_ERROR_UNEXPECTED;
                // WARNING_STM;
            }
            else
            {

                if (!left->buildEnvironment(statementRoot, item->_getEnvironment(), right, true
#ifdef TRACE_BUILD_ENVIRONMENT
                                            ,
                                            true
#endif
                                            ,
                                            verbose))
                {
                    addFlags(Flags::BOTTOM);
                }
            }
        }
    }
    break;

    default:
        FATAL_ERROR_UNEXPECTED;
        break;
    }
}

/* ************************************************************
 * [ … $X … ] ⊂ Y;
 * [ … $X … ] ⊂ [ … ];
 * $X = a;
 * $X = [ … ];
 * $X = < … >;
 * $X = sort $X with a;
 * $X = reverse X
 * $X = <expr>
 * < … > = < … >
 * < … > = sort $X with a;
 * < … > = reverse $X;
 * < … > = $X;
 ************************************************************ */
void Statement::buildEnvironmentWithValue(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::buildEnvironmentWithValue #######################" << std::endl;
    toHTML(std::cout);
    std::cout << std::endl;
#endif
    switch (op)
    {
    case ASSIGNMENT_STATEMENT:
        // 	 $X = a;
        // 	 $X = $Y;
        // 	 $X = … ∪ … ;
        // 	 $X = [ … ];
        // 	 $X = <expr>;
        // 	 $X = < … >
        // 	 $X = sort $X with a;
        // 	 $X = reverse $X;

        if (first->isVariable())
        {
            valuePtr right = second->evalValue(item, parser, synthesizer, true, verbose);
            if (!right)
            {
                this->toHTML(std::cerr);
                WARNING_STM;
            }
            else
            {
                item->environmentAdd(statementRoot, first->code, right, verbose);
            }
        }

        // 	 < … > = $X;
        // 	 < … > = ( … )
        // 	 < … > = sort $X with a;
        // 	 < … > = reverse $X;
        else if (first->isPairp())
        {
            pairpPtr right = second->evalPairp(item, parser, synthesizer, true, verbose);
            if (!right)
            {
                FATAL_ERROR_STM(shared_from_this());
            }
            else
            {
                if (right->isNil())
                {
                    toHTML(std::cerr);
                    FATAL_ERROR_STM(shared_from_this());
                }
                pairpPtr left = first->evalPairp(item, parser, synthesizer, false, verbose);
                if (!left)
                {
                    WARNING_STM;
                }
                else
                {

                    if (!left->buildEnvironment(statementRoot, item->_getEnvironment(), right, true, true, verbose))
                    {
                        addFlags(Flags::BOTTOM);
                    }
                }
            }
        }
        else
            FATAL_ERROR_STM(shared_from_this());
        break;

    case SUBSUME_STATEMENT:
    {
        featuresPtr right = second->evalFeatures(item, parser, synthesizer, true, verbose);
        if (!right)
        {
            WARNING_STM;
        }
        else
        {
            // if (right->isNil())
            //{
            // } // empty
            featuresPtr left = first->evalFeatures(item, parser, synthesizer, false, verbose);
            if (left)
            {
                if (!left->buildEnvironment(statementRoot, item->_getEnvironment(), right, true
#ifdef TRACE_BUILD_ENVIRONMENT
                                            ,
                                            true
#endif
                                            ,
                                            verbose))
                {
                    addFlags(Flags::BOTTOM);
                }
            }
        }
    }
    break;

    default:
        FATAL_ERROR_UNEXPECTED;
        break;
    }
}

/* ************************************************************
 * attest
 ************************************************************ */
void Statement::stmAttest(class Item *item, Parser &parser, Generator *synthesizer, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::stmAttest #######################" << std::endl;
    toHTML(std::cout);
    std::cout << std::endl;
#endif
    switch (op)
    {
    case ATTEST_STATEMENT:
    {
        valuePtr res = first->evalValue(item, parser, synthesizer, true, verbose);

        if (!res ||
            res->isFalse() ||
            (res->isFeatures() && res->getFeatures()->isBottom()))
        {
            addFlags(Flags::BOTTOM);
        }
    }
    break;
    default:
        FATAL_ERROR_UNEXPECTED;
        break;
    }
}

/* ************************************************************
 * guard
 ************************************************************ */
void Statement::stmGuard(statementPtr statementRoot, class Item *item, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::stmGuard #######################" << std::endl;
    item->toHTML(std::cout);
    toHTML(std::cout);
    std::cout << std::endl;
#endif
    if (isSetFlags(Flags::DISABLED | Flags::SEEN))
    {
        FATAL_ERROR_UNEXPECTED;
    }
    featuresPtr localFeatures = features;
    if (!localFeatures)
    {
        FATAL_ERROR_STM(shared_from_this());
    }
    featuresPtr localSecond = item->getInheritedFeatures();

    if (!localFeatures->buildEnvironment(statementRoot, item->_getEnvironment(), localSecond, false
#ifdef TRACE_BUILD_ENVIRONMENT
                                         ,
                                         true
#endif
                                         ,
                                         verbose))
    {
        addFlags(Flags::BOTTOM);
    }
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::stmGuard DONE #######################" << std::endl;
    item->toHTML(std::cout);
    std::cout << std::endl;
#endif
}

/* ************************************************************
 * foreach
 ************************************************************ */
void Statement::stmForeach(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::stmForeach #######################" << std::endl;
    item->toHTML(std::cout);
    std::cout << std::endl;
#endif
    addFlags(Flags::SEEN);
    valuePtr value = first->first->evalValue(item, parser, synthesizer, true, verbose);
    statementPtr statement = first->second;
    if (value->isPairp())
    {
        value->getPairp()->apply(statementRoot, item, parser, synthesizer, code, statement, effect, verbose);
    }

    // else if (value->isListFeatures())
    // {
    //     FATAL_ERROR_MSG("foreach does'nt apply a list");
    //     value->getListFeatures()->apply(statementRoot, item, parser, synthesizer, variable, statement, effect);
    // }

    else
    {
        FATAL_ERROR_MSG("foreach does'nt apply a list");
    }
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::stmForeach DONE #######################" << std::endl;
    item->toHTML(std::cout);
    std::cout << std::endl;
#endif
}

/* ************************************************************
 * if
 ************************************************************ */
void Statement::stmIf(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool replaceVariables, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::stmIf #######################" << std::endl;
    item->toHTML(std::cout);
    this->toHTML(std::cout);
    std::cout << std::endl;
#endif
    statementPtr leftHandSide = second->first;
    statementPtr rightHandSide = second->second;
    enum test_choice result = __NONE__;
    if (first->isSetFlags(Flags::CHOOSEN))
    {
        result = __THEN__;
    }
    else if (second && second->isSetFlags(Flags::CHOOSEN))
    {
        result = __ELSE__;
    }
    else
    {
        valuePtr res = first->evalValue(item, parser, synthesizer, true, verbose);
        if (!res || res->isFalse())
        {
            result = __ELSE__;
            leftHandSide->addFlags(Flags::REJECTED);
            if (rightHandSide)
                rightHandSide->addFlags(Flags::CHOOSEN);
        }
        else
        {
            result = __THEN__;
            leftHandSide->addFlags(Flags::CHOOSEN);
            if (rightHandSide)
                rightHandSide->addFlags(Flags::REJECTED);
        }
    }
    switch (result)
    {
    case __THEN__:
        leftHandSide->apply(statementRoot, item, parser, synthesizer, effect, replaceVariables, verbose);
        if (leftHandSide->isSetFlags(Flags::BOTTOM))
        {
            this->addFlags(Flags::BOTTOM);
        }
        if (leftHandSide->isSetFlags(Flags::SEEN))
            this->addFlags(Flags::SEEN);
        break;
    case __ELSE__:
        if (rightHandSide)
        {
            rightHandSide->apply(statementRoot, item, parser, synthesizer, effect, replaceVariables, verbose);
            if (rightHandSide->isSetFlags(Flags::BOTTOM))
            {
                this->addFlags(Flags::BOTTOM);
            }
            if (rightHandSide->isSetFlags(Flags::SEEN))
                this->addFlags(Flags::SEEN);
        }
        else
        {
            this->addFlags(Flags::SEEN);
        }
        break;
    case __NONE__:
        FATAL_ERROR_UNEXPECTED;
        break;
    }
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::stmIf DONE #######################" << std::endl;
    item->toHTML(std::cout);
    std::cout << std::endl;
#endif
}

/* ************************************************************
 * DEFERRED
 ************************************************************ */
void Statement::stmDeferred(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool replaceVariables, bool verbose)
{
    second->apply(statementRoot, item, parser, synthesizer, effect, replaceVariables, verbose);
    if (second->isSetFlags(Flags::BOTTOM))
        addFlags(Flags::BOTTOM);
    if (second->isSetFlags(Flags::SEEN))
        addFlags(Flags::SEEN);
}

/* ************************************************************
 * print
 ************************************************************ */
void Statement::stmPrint(class Item *item, Parser &parser, Generator *generator, std::ostream &out, bool verbose)
{
    addFlags(Flags::SEEN);
    for (auto statement = statements->cbegin(); statement != statements->cend(); ++statement)
    {
        if ((*statement)->isString())
        {
            out << (*statement)->string;
        }
        else
        {
            valuePtr value = (*statement)->evalValue(item, parser, generator, true, verbose);
            if (value->isString())
                out << value->getString();
            else
                value->flatPrint(out);
        }
    }
}

/* ************************************************************
 * println
 ************************************************************ */
void Statement::stmPrintln(class Item *item, Parser &parser, Generator *generator, std::ostream &out, bool verbose)
{
    stmPrint(item, parser, generator, out, verbose);
    out << std::endl;
}

/* ************************************************************
 *
 ************************************************************ */
void Statement::renameVariable(uint32_t key)
{
    switch (op)
    {
    case VARIABLE_STATEMENT:
        code = Vartable::nameToCode(Vartable::codeToName(code), key);
        break;

    case CONSTANT_STATEMENT:
    case ANONYMOUS_STATEMENT:
    case NIL_STATEMENT:
    case NUMBER_STATEMENT:
    case INHERITED_FEATURES_STATEMENT:
    case SYNTHESIZED_FEATURES_STATEMENT:
    case DASH_STATEMENT:
    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
    case INHERITED_CHILDREN_FEATURES_STATEMENT:
    case SEARCH_STATEMENT:
        break;

    case STRING_STATEMENT:
        Vartable::renameVariables(string, key);
        break;

    case ASSIGNMENT_STATEMENT:
    case SUBSUME_STATEMENT:
    case FUNCTION_STATEMENT:
    case UNIF_STATEMENT:
    case ATTEST_STATEMENT:
    case IF_STATEMENT:
    case THEN_STATEMENT:
    case THEN_ELSE_STATEMENT:
    case FOREACH_STATEMENT:
    case FOREACH_CON_T_STATEMENT:
    case DEFERRED_STATEMENT:
        if (first)
        {
            first->renameVariable(key);
        }
        if (second)
        {
            second->renameVariable(key);
        }
        break;

    case FEATURES_STATEMENT:
    case GUARD_STATEMENT:
        if (features)
        {
            features->renameVariables(key);
        }
        break;

    case PAIRP_STATEMENT:
        if (pairp)
        {
            pairp->renameVariables(key);
        }
        break;

    case STMS_STATEMENT:
    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:
    case EPRINT_STATEMENT:
    case EPRINTLN_STATEMENT:
        if (statements)
        {
            statements->renameVariables(key);
        }
        break;
    }
}

/* ************************************************************
 *
 ************************************************************ */
void Statement::testEnable(statementPtr statementRoot, class Item *item, Generator *synthesizer, bool &result, bool on)
{
#ifdef TRACE_ENABLE_STATEMENT
    std::cout << "<H3>####################### TRACE_ENABLE_STATEMENT #######################</H3>" << std::endl;
    print(std::cout);
    std::cout << std::endl;
#endif
    switch (op)
    {

    case NIL_STATEMENT:
    case INHERITED_CHILDREN_FEATURES_STATEMENT:
    case STRING_STATEMENT:
    case NUMBER_STATEMENT:
    case ANONYMOUS_STATEMENT:
    case CONSTANT_STATEMENT:

        break;

    case GUARD_STATEMENT:
        if (on)
        {
            if (item->getInheritedFeatures()->isNil())
            {
                this->addFlags(Flags::DISABLED);
                result = true;
            }
        }
        else
        {
            this->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case DASH_STATEMENT:
        if (on)
        {
            if (item->getIndexTerms()[getFirst()] == Item::POSTERM_NA)
            //|| ((getSecond() != UINT8_MAX) && (item->getIndexTerms()[getFirst()] != getSecond())))
            {
                statementRoot->addFlags(Flags::DISABLED);
                result = true;
            }
        }
        else
        {
            statementRoot->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case VARIABLE_STATEMENT:
        if (on)
        {
            if (!item->environmentGet(code))
            {
                statementRoot->addFlags(Flags::DISABLED);
                result = true;
            }
        }
        else
        {
            statementRoot->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
        if (getFirst() > item->getRuleRhs().size())
        {
            std::ostringstream oss;
            oss << "⇓" << getFirst() + 1 << " not available";
            FATAL_ERROR_OSS_MSG(oss);
        }
        if (on)
        {
            if ((*item->getSynthesizedChildFeatures())[getFirst()]->isNil())
            {
                statementRoot->addFlags(Flags::DISABLED);
                result = true;
            }
        }
        else
        {
            statementRoot->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case INHERITED_FEATURES_STATEMENT:
        if (on)
        {
            if (item->getInheritedFeatures()->isNil())
            {
                statementRoot->addFlags(Flags::DISABLED);
                result = true;
            }
        }
        else
        {
            statementRoot->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case SYNTHESIZED_FEATURES_STATEMENT:
        if (on)
        {
            if (item->getSynthesizedFeatures()->isNil())
            {
                statementRoot->addFlags(Flags::DISABLED);
                result = true;
            }
        }
        else
        {
            statementRoot->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case STMS_STATEMENT:
        statements->testEnable(item, synthesizer, result, on);
        break;

    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:
    case EPRINT_STATEMENT:
    case EPRINTLN_STATEMENT:

        if (on)
        {
            for (auto i = statements->cbegin(); i != statements->cend(); ++i)
            {
                bool effect = false;
                (*i)->testEnable(*i, item, synthesizer, effect, on);
                if (effect && (*i)->isSetFlags(Flags::DISABLED))
                {
                    statementRoot->addFlags(Flags::DISABLED);
                    result = true;
                }
            }
        }
        else
        {
            for (auto i = statements->cbegin(); i != statements->cend(); ++i)
            {
                (*i)->subFlags(Flags::DISABLED);
            }
            statementRoot->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case IF_STATEMENT:
        if (first)
        {
            first->testEnable(statementRoot, item, synthesizer, result, on);
        }
        if (statementRoot->isUnsetFlags(Flags::DISABLED))
        {
            second->testEnable(second, item, synthesizer, result, on);
        }
        break;

    case THEN_STATEMENT:
        first->testEnable(first, item, synthesizer, result, on);
        break;

    case THEN_ELSE_STATEMENT:
        first->testEnable(first, item, synthesizer, result, on);
        if (second)
            second->testEnable(second, item, synthesizer, result, on);
        break;

    case FOREACH_STATEMENT:
        first->testEnable(shared_from_this(), item, synthesizer, result, on);
        break;

    case FOREACH_CON_T_STATEMENT:
        first->testEnable(statementRoot, item, synthesizer, result, on);
        second->testEnable(second, item, synthesizer, result, on);
        break;

    case DEFERRED_STATEMENT:
        first->testEnable(shared_from_this(), item, synthesizer, result, on);
        second->testEnable(shared_from_this(), item, synthesizer, result, on);
        break;

    case ASSIGNMENT_STATEMENT:
    case SUBSUME_STATEMENT:
        second->testEnable(shared_from_this(), item, synthesizer, result, on);
        break;

    case FUNCTION_STATEMENT:
    case UNIF_STATEMENT:
        if (first)
            first->testEnable(statementRoot, item, synthesizer, result, on);
        if (second)
            second->testEnable(statementRoot, item, synthesizer, result, on);
        break;

    case ATTEST_STATEMENT:
        first->testEnable(statementRoot, item, synthesizer, result, on);
        break;

    case PAIRP_STATEMENT:
        pairp->testEnable(statementRoot, item, synthesizer, result, on);
        break;

    case FEATURES_STATEMENT:
        features->testEnable(statementRoot, item, synthesizer, result, on);
        break;

    case SEARCH_STATEMENT:
        if (first)
            first->testEnable(statementRoot, item, synthesizer, result, on);
        break;

    default:
        COUT_LINE;
        std::cout << op;
        FATAL_ERROR_UNEXPECTED;
        break;
    }
#ifdef TRACE_ENABLE_STATEMENT
    std::cout << "<H3>####################### TRACE_ENABLE_STATEMENT CON'T #######################</H3>" << std::endl;
    toHTML(std::cout);
    std::cout << std::endl;
#endif
}

/* ************************************************************
 *
 ************************************************************ */
void Statement::apply(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool replaceVariables, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "<H3>####################### TRACE_APPLY_STATEMENT #######################</H3>" << std::endl;
    std::cout << "Apply: " << std::endl;
    toHTML(std::cout);
    std::cout << std::endl;
#endif

    if (isSetFlags(Flags::SEEN | Flags::DISABLED | Flags::BOTTOM))
    {
        return;
    }

    // […]
    if (isGuard())
    {
        stmGuard(statementRoot, item, verbose);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // if
    else if (isIf())
    {
        stmIf(statementRoot, item, parser, synthesizer, effect, replaceVariables, verbose);
    }

    // foreach $i in $list
    else if (isForeach())
    {
        stmForeach(statementRoot, item, parser, synthesizer, effect, verbose);
    }

    // DEFERRED
    else if (isDeferred())
    {
        stmDeferred(statementRoot, item, parser, synthesizer, effect, replaceVariables, verbose);
    }

    // ↓i = …
    else if ((isAssignment()) && (first->isDown()))
    {
        buildInheritedChildFeatures(item, parser, synthesizer, replaceVariables, verbose);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // [ … $X … ] ⊂ ⇓1
    // $X = ⇓i
    else if (((isSubsume()) && (second->isDown2()) && (first->isFeatures())) ||
             ((isAssignment()) && (second->isDown2()) && (first->isVariable())))
    {
        buildEnvironmentWithSynthesize(statementRoot, item, parser, synthesizer, verbose);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // [ … $X … ] ⊂ ↑
    // $X = ↑
    else if (((isSubsume()) && (second->isUp()) && (first->isFeatures())) ||
             ((isAssignment()) && (second->isUp()) && (first->isVariable())))
    {
        buildEnvironmentWithInherited(statementRoot, item, parser, synthesizer, verbose);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // $X = a;
    // $X = Y;
    // $X = … ∪ … ;
    // $X = [ … ];
    // $X = <expr>;
    // $X = < … >;
    // $X = search;
    //
    // < … > = $X;
    // < … > = < … >;
    // < … > = search;
    //
    // [ … $X … ] ⊂ $Y;
    // [ … $X … ] ⊂ [ … ];
    else if (((isAssignment()) && (first->isVariable()) && ((second->isConstant()) || (second->isVariable()) || (second->isUnif()) || (second->isFeatures()) || (second->isNumber()) || (second->isString()) || (second->isFct()) || (second->isPairp()) || (second->isSearch())))

             || ((isAssignment()) && (first->isPairp()) && ((second->isVariable()) || (second->isPairp()) || (second->isSearch())))

             || ((isSubsume()) && (first->isFeatures()) && ((second->isVariable()) || (second->isFeatures()))))
    {
        buildEnvironmentWithValue(statementRoot, item, parser, synthesizer, verbose);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // ⇑ = …
    else if ((isAssignment()) && (first->isUp2()))
    {
        buildSynthesizedFeatures(item, parser, synthesizer, verbose);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // attest …
    else if (isAttest())
    {
        stmAttest(item, parser, synthesizer, verbose);
        addFlags(Flags::SEEN);
    }

    // print
    else if (isPrint())
    {
        stmPrint(item, parser, synthesizer, std::cout, verbose);
        addFlags(Flags::SEEN);
    }

    // println
    else if (isPrintln())
    {
        stmPrintln(item, parser, synthesizer, std::cout, verbose);
        addFlags(Flags::SEEN);
    }

    // eprint
    else if (isEprint())
    {
        stmPrint(item, parser, synthesizer, std::cerr, verbose);
        addFlags(Flags::SEEN);
    }

    // eprintln
    else if (isEprintln())
    {
        stmPrintln(item, parser, synthesizer, std::cerr, verbose);
        addFlags(Flags::SEEN);
    }

    // statements
    else if (isStms())
    {
        statements->apply(item, parser, synthesizer, effect, verbose);
        if (statements->isSetFlags(Flags::BOTTOM))
            addFlags(Flags::BOTTOM);
        if (statements->isSetFlags(Flags::SEEN))
            addFlags(Flags::SEEN);
    }

    // else error
    else
    {
        FATAL_ERROR_UNEXPECTED
    }

#ifdef TRACE_APPLY_STATEMENT
    std::cout << "<H3>####################### TRACE_APPLY_STATEMENT CON'T #######################</H3>" << std::endl;
    item->toHTML(std::cout);
    std::cout << std::endl;
#endif
}

/* ************************************************************
 *
 ************************************************************ */
void Statement::lookingForAssignedInheritedChildFeatures(std::vector<bool> &assignedInheritedChildFeatures)
{
    switch (op)
    {
    case ASSIGNMENT_STATEMENT:
        // ↓1 = …
        if ((isAssignment()) && (first->isDown()))
            assignedInheritedChildFeatures[first->getFirst()] = true;
        break;

    case IF_STATEMENT:
    {
        statementPtr left = second->first;
        statementPtr right = second->second;
        if (left->isSetFlags(Flags::CHOOSEN))
        {
            left->lookingForAssignedInheritedChildFeatures(assignedInheritedChildFeatures);
        }
        else if (right && right->isSetFlags(Flags::CHOOSEN))
        {
            right->lookingForAssignedInheritedChildFeatures(assignedInheritedChildFeatures);
        }
    }
    break;

    default:
        FATAL_ERROR_UNEXPECTED;
        break;
    }
}

/* ************************************************************
 *
 ************************************************************ */
bool Statement::containsVariable(const uint32_t key)
{
    switch (op)
    {

    case STMS_STATEMENT:
    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:
    case EPRINT_STATEMENT:
    case EPRINTLN_STATEMENT:
        if (statements->findVariable(key))
            return true;
        break;

    case IF_STATEMENT:
        if (second->containsVariable(key))
            return true;
        break;

    case THEN_STATEMENT:
        if (first->containsVariable(key))
            return true;
        break;

    case THEN_ELSE_STATEMENT:
        if (first->containsVariable(key))
            return true;
        if (second)
            if (second->containsVariable(key))
                return true;
        break;

    case FOREACH_STATEMENT:
        if (second->containsVariable(key))
            return true;
        break;

    case FOREACH_CON_T_STATEMENT:
        if (first->containsVariable(key))
            return true;
        if (second)
            if (second->containsVariable(key))
                return true;
        break;

    case GUARD_STATEMENT:
        if (features->findVariable(key))
            return true;
        break;

    case ASSIGNMENT_STATEMENT:
    case SUBSUME_STATEMENT:
        if (second->containsVariable(key))
            return true;
        break;

    case FUNCTION_STATEMENT:
    case UNIF_STATEMENT:
        if (first && first->containsVariable(key))
            return true;
        if (second && second->containsVariable(key))
            return true;
        break;

    case ATTEST_STATEMENT:
        if (first->containsVariable(key))
            return true;
        break;

    case VARIABLE_STATEMENT:
        if (code == key)
            return true;
        break;

    case PAIRP_STATEMENT:
        if (pairp->findVariable(key))
            return true;
        break;

    case FEATURES_STATEMENT:
        if (features->findVariable(key))
            return true;
        break;

    default:
        FATAL_ERROR_UNEXPECTED
        break;
    }
    return false;
}

/* ************************************************************
 *
 ************************************************************ */
/*
void Statement::makeSerialString()
{
    std::ostringstream stream;

    stream << '(';
    stream << static_cast<int>(op);
    stream << ',';
    stream << (rootOp ? '1' : '0');

    switch (op)
    {
    case DASH_STATEMENT:
    case INHERITED_FEATURES_STATEMENT:
    case SYNTHESIZED_FEATURES_STATEMENT:
    case INHERITED_CHILDREN_FEATURES_STATEMENT:
    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
    case ANONYMOUS_STATEMENT:
    case NIL_STATEMENT:
        break;

    case VARIABLE_STATEMENT:
    case FOREACH_STATEMENT:
    case SEARCH_STATEMENT:
        stream << ",C:" << code;
        break;

    case CONSTANT_STATEMENT:
        stream << ",B:" << (bitset ? bitset->peekSerialString() : std::string("0"));
        break;

    case FEATURES_STATEMENT:
    case GUARD_STATEMENT:
        stream << ",F:" << (features ? features->peekSerialString() : std::string("0"));
        break;

    case PAIRP_STATEMENT:
        stream << ",P:" << (pairp ? pairp->peekSerialString() : std::string("0"));
        break;

    case STRING_STATEMENT:
        stream << ",T:" << string;
        break;

    case NUMBER_STATEMENT:
        stream << ",N:" << std::setprecision(17) << number;
        break;

    case FUNCTION_STATEMENT:
        stream << ",FN:" << static_cast<int>(function);
        stream << ",A:" << (first ? first->peekSerialString() : std::string("0"));
        stream << ",B:" << (second ? second->peekSerialString() : std::string("0"));
        break;

    case ASSIGNMENT_STATEMENT:
    case SUBSUME_STATEMENT:
    case UNIF_STATEMENT:
    case ATTEST_STATEMENT:
    case IF_STATEMENT:
    case THEN_STATEMENT:
    case THEN_ELSE_STATEMENT:
    case FOREACH_CON_T_STATEMENT:
    case DEFERRED_STATEMENT:
        stream << ",A:" << (first ? first->peekSerialString() : std::string("0"));
        stream << ",B:" << (second ? second->peekSerialString() : std::string("0"));
        break;

    case STMS_STATEMENT:
    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:
    case PRINTSTDERR_STATEMENT:
    case PRINTLNSTDERR_STATEMENT:
        stream << ",S:" << (statements ? statements->peekSerialString() : std::string("0"));
        break;
    }

    stream << ')';
    serialString = stream.str();
}
*/