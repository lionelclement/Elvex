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
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp)
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
    statement->first = first;
    statement->second = second;
    return statementPtr(statement);
}

/* **************************************************
 * STMS PRINT PRINTLN PRINTSTDERR PRINTSTDERRLN
 ************************************************** */
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementsPtr statements)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->statements = statements;
    return statementPtr(statement);
}

/* **************************************************
 * GUARD FEATURES
 ************************************************** */
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp, featuresPtr features)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->features = std::move(features);
    return statementPtr(statement);
}

/* **************************************************
 * ATTEST
 ************************************************** */
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementPtr lhs)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->lhs = std::move(lhs);
    return statementPtr(statement);
}

/* **************************************************
 * AFF SUBSUME IF IF_CON_T DEFERRED FOREACH FOREACH_CON_T UNIF
 ************************************************** */
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementPtr lhs, statementPtr rhs)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->lhs = std::move(lhs);
    statement->rhs = std::move(rhs);
    return statementPtr(statement);
}

/* **************************************************
 * VARIABLE CONSTANT
 ************************************************** */
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp, bitsetPtr bitset)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->bitset = std::move(bitset);
    return statementPtr(statement);
}

/* **************************************************
 * PAIRP
 ************************************************** */
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp, pairpPtr pairp)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->pairp = std::move(pairp);
    return statementPtr(statement);
}

/* **************************************************
 * FCT
 ************************************************** */
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp,
                               arithmetic_op fct, statementPtr lhs, statementPtr rhs)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->fct = fct;
    statement->lhs = lhs ? std::move(lhs) : statementPtr();
    statement->rhs = rhs ? std::move(rhs) : statementPtr();
    return statementPtr(statement);
}

/* **************************************************
 * NUMBER
 ************************************************** */
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp, double number)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->number = number;
    return statementPtr(statement);
}

/* **************************************************
 * STRING
 ************************************************** */
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp, std::string string)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->string = string;
    return statementPtr(statement);
}

/* **************************************************
 * ANONYMOUS
 ************************************************** */
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp, valuePtr &value)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->value = std::move(value);
    return statementPtr(statement);
}

/* **************************************************
 * SEARCH
 ************************************************** */
statementPtr Statement::create(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementPtr lhs, uint8_t first)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->lhs = std::move(lhs);
    statement->first = first;
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
bool Statement::isPrintstderr() const
{
    return op == PRINTSTDERR_STATEMENT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isPrintlnstderr() const
{
    return op == PRINTLNSTDERR_STATEMENT;
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
    if (lhs)
        result = result || lhs->containsDash();
    if (rhs)
        result = result || rhs->containsDash();
    return result;
}

/* **************************************************
 *
 ************************************************** */
Statement::arithmetic_op Statement::getFct() const
{
    return fct;
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::getLhs() const
{
    return lhs;
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::getRhs() const
{
    return rhs;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Statement::getFeatures() const
{
    return features;
}

/* **************************************************
 *
 ************************************************** */
bitsetPtr Statement::getBits() const
{
    return bitset;
}

/* **************************************************
 *
 ************************************************** */
uint8_t Statement::getFirst() const
{
    return first;
}

/* **************************************************
 *
 ************************************************** */
uint8_t Statement::getSecond() const
{
    return second;
}

/* **************************************************
 *
 ************************************************** */
std::string &Statement::getString()
{
    return string;
}

/* **************************************************
 *
 ************************************************** */
pairpPtr Statement::getPairp() const
{
    return pairp;
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Statement::getStatements() const
{
    return statements;
}

/* **************************************************
 *
 ************************************************** */
double Statement::getNumber() const
{
    return number;
}

/* **************************************************
 *
 ************************************************** */
uint32_t Statement::getLineno() const
{
    return lineno;
}

/* **************************************************
 *
 ************************************************** */
std::string Statement::getBufferName() const
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
void Statement::print(std::ostream &out, uint8_t tabulationLenght, uint8_t tabulation, uint32_t color, uint32_t bgcolor) const
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
        getFeatures()->flatPrint(out);
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case ATTEST_STATEMENT:
        OPENSPAN;
        out << "<B>attest</B>&nbsp;";
        lhs->print(out);
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case ASSIGNMENT_STATEMENT:
        OPENSPAN;
        lhs->print(out);
        out << "&nbsp;=&nbsp;";
        rhs->print(out);
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case SUBSUME_STATEMENT:
        OPENSPAN;
        lhs->print(out);
        out << "&nbsp;⊂&nbsp;";
        rhs->print(out);
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case PRINT_STATEMENT:
        OPENSPAN;
        out << "<B>print</B>&nbsp;";
        getStatements()->print(out, tabulationLenght, tabulation, color, bgcolor, false, "(", ")", ",&nbsp;");
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case PRINTLN_STATEMENT:
        OPENSPAN;
        out << "<B>println</B>&nbsp;";
        getStatements()->print(out, tabulationLenght, tabulation, color, bgcolor, false, "(", ")", ",&nbsp;");
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case PRINTSTDERR_STATEMENT:
        OPENSPAN;
        out << "<B>printstderr</B>&nbsp;";
        getStatements()->print(out, tabulationLenght, tabulation, color, bgcolor, false, "(", ")", ",&nbsp;");
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case PRINTLNSTDERR_STATEMENT:
        OPENSPAN;
        out << "<B>printlnstderr</B>&nbsp;";
        getStatements()->print(out, tabulationLenght, tabulation, color, bgcolor, false, "(", ")", ",&nbsp;");
        out << ";";
        BR;
        CLOSESPAN;
        break;

    case SEARCH_STATEMENT:
        out << "<B>search</B>&nbsp;";
        lhs->print(out);
        out << "&nbsp;<B>on</B>&nbsp;";
        out << Vartable::codeToName(first);
        break;

    case STMS_STATEMENT:
        getStatements()->print(out, tabulationLenght, tabulation, color, bgcolor, true, "{", "}", "");
        break;

    case IF_STATEMENT:
        OPENSPAN;
        out << "<B>if</B>&nbsp;(";
        lhs->print(out);
        out << ')';
        CLOSESPAN;
        rhs->print(out, tabulationLenght, tabulation, color, bgcolor);
        break;

    case IF_CON_T_STATEMENT:
        if (lhs->isSetFlags(Flags::REJECTED))
            bgcolor = PINK;
        if (lhs->isSetFlags(Flags::CHOOSEN))
            bgcolor = GREEN;
        if (lhs->isStms())
            lhs->print(out, tabulationLenght, tabulation, color, bgcolor);
        else
        {
            brln(out, tabulation + tabulationLenght);
            lhs->print(out, tabulationLenght, tabulation + tabulationLenght, color, bgcolor);
        }

        if (rhs)
        {
            for (uint8_t j = 1; j <= tabulation; j++)
                out << "&nbsp;";
            OPENSPAN;
            out << "<B>else</B>";
            CLOSESPAN;

            if (rhs->isSetFlags(Flags::REJECTED))
                bgcolor = PINK;
            if (rhs->isSetFlags(Flags::CHOOSEN))
                bgcolor = GREEN;
            if (rhs->isStms())
                rhs->print(out, tabulationLenght, tabulation, color, bgcolor);
            else
            {
                brln(out, tabulation + tabulationLenght);
                rhs->print(out, tabulationLenght, tabulation + tabulationLenght, color, bgcolor);
            }
        }
        break;

    case DEFERRED_STATEMENT:
        OPENSPAN;
        out << "<B>deferred</B>&nbsp;(";
        lhs->print(out);
        out << ')';
        CLOSESPAN;
        if (rhs->isStms())
        {
            rhs->print(out, tabulationLenght, tabulation, color);
        }
        else
        {
            brln(out, tabulation + tabulationLenght);
            rhs->print(out, tabulationLenght, tabulation + tabulationLenght, color);
        }
        break;

    case FOREACH_STATEMENT:
        OPENSPAN;
        out << "<B>foreach</B>&nbsp;";
        lhs->print(out);
        out << "&nbsp;";
        CLOSESPAN;
        rhs->print(out, tabulationLenght, tabulation, color);
        break;

    case FOREACH_CON_T_STATEMENT:
        OPENSPAN;
        out << "<B>in</B>&nbsp;";
        lhs->print(out);
        CLOSESPAN;
        if (rhs->isStms())
            rhs->print(out, tabulationLenght, tabulation, color);
        else
        {
            brln(out, tabulation + tabulationLenght);
            rhs->print(out, tabulationLenght, tabulation + tabulationLenght, color);
        }
        break;

    case NIL_STATEMENT:
        out << "<B>NIL</B>";
        break;

    case CONSTANT_STATEMENT:
    case VARIABLE_STATEMENT:
        out << getBits()->toString();
        break;

    case ANONYMOUS_STATEMENT:
        out << '_';
        break;

    case FEATURES_STATEMENT:
        getFeatures()->flatPrint(out);
        break;

    case PAIRP_STATEMENT:
        getPairp()->flatPrint(out, true);
        break;

    case UNIF_STATEMENT:
        out << "&nbsp;(";
        lhs->print(out);
        out << "&nbsp;∪&nbsp;";
        rhs->print(out);
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
        out << "↓" << getFirst() + 1;
        if (getSecond() != UINT8_MAX)
            out << "." << getSecond() + 1;
        break;

    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
        out << "⇓";
        out << getFirst() + 1;
        break;

    case STRING_STATEMENT:
        out << "&quot;" << string << "&quot;";
        break;

    case NUMBER_STATEMENT:
        out << getNumber();
        break;

    case FUNCTION_STATEMENT:
        switch (this->getFct())
        {
        case NOP:
            out << "<B>nop</B>&nbsp;";
            break;
        case NOT:
            out << "¬";
            out << "&nbsp;(";
            lhs->print(out);
            out << ")&nbsp;";
            break;
        case AND:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;∧&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case OR:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;∨&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case PLUS:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;+&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case MINUS:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;-&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case TIMES:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;*&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case DIVIDE:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;/&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case MODULO:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;%&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case EQ:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;==&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case DIFF:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;≠&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case LT:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;<&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case LE:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;≤&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case GT:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;>&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case GE:
            out << "&nbsp;(";
            lhs->print(out);
            out << "&nbsp;≥&nbsp;";
            rhs->print(out);
            out << ")&nbsp;";
            break;
        case MINUS_U:
            out << "-&nbsp;";
            lhs->print(out);
            break;
        case RANDOM:
            out << "rand()";
            break;
        default:
            FATAL_ERROR_UNEXPECTED;
        }
    }
}

/* **************************************************
 *
 ************************************************** */
void Statement::makeSerialString()
{
    serialString = std::string();
    switch (this->op)
    {
    case ATTEST_STATEMENT:
        serialString = 'A' + lhs->peekSerialString();
        break;
    case NIL_STATEMENT:
        serialString = 'B';
        break;
    case ASSIGNMENT_STATEMENT:
        serialString = 'C' + lhs->peekSerialString() + rhs->peekSerialString();
        break;
    case SUBSUME_STATEMENT:
        serialString = 'D' + lhs->peekSerialString() + rhs->peekSerialString();
        break;
    case FUNCTION_STATEMENT:
        switch (this->getFct())
        {
        case NOP:
            serialString = 'E';
            break;
        case NOT:
            serialString = 'F' + lhs->peekSerialString();
            break;
        case AND:
            serialString = 'G' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case OR:
            serialString = 'H' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case DIFF:
            serialString = 'I' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case EQ:
            serialString = 'J' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case PLUS:
            serialString = 'K' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case MINUS:
            serialString = 'L' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case TIMES:
            serialString = 'M' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case DIVIDE:
            serialString = 'N' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case MODULO:
            serialString = 'O' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case LT:
            serialString = 'P' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case LE:
            serialString = 'Q' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case GT:
            serialString = 'R' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case GE:
            serialString = 'S' + lhs->peekSerialString() + rhs->peekSerialString();
            break;
        case MINUS_U:
            serialString = 'T' + lhs->peekSerialString();
            break;
        case RANDOM:
            serialString = 'U';
            break;
        }
        break;
    case CONSTANT_STATEMENT:
    case VARIABLE_STATEMENT:
        serialString = getBits()->peekSerialString();
        break;
    case ANONYMOUS_STATEMENT:
        serialString = 'V';
        break;
    case PRINT_STATEMENT:
        serialString = 'W' + getStatements()->peekSerialString();
        break;
    case PRINTLN_STATEMENT:
        serialString = 'X' + getStatements()->peekSerialString();
        break;
    case PRINTSTDERR_STATEMENT:
        serialString = 'Y' + getStatements()->peekSerialString();
        break;
    case PRINTLNSTDERR_STATEMENT:
        serialString = 'Z' + getStatements()->peekSerialString();
        break;
    case FEATURES_STATEMENT:
        serialString = '0' + getFeatures()->peekSerialString();
        break;
    case PAIRP_STATEMENT:
        serialString = '1' + getPairp()->peekSerialString();
        break;
    case GUARD_STATEMENT:
        serialString = '2' + getFeatures()->peekSerialString();
        break;
    case UNIF_STATEMENT:
        serialString = '3' + lhs->peekSerialString() + rhs->peekSerialString();
        break;
    case INHERITED_FEATURES_STATEMENT:
        serialString = '4';
        break;
    case SYNTHESIZED_FEATURES_STATEMENT:
        serialString = '5';
        break;
    case DASH_STATEMENT:
        serialString = '6' + std::to_string(getFirst());
        if (getSecond() != UINT8_MAX)
            serialString += '7' + std::to_string(getSecond());
        break;
    case INHERITED_CHILDREN_FEATURES_STATEMENT:
        serialString = '8' + std::to_string(getFirst() + 1);
        if (getSecond() != UINT8_MAX)
            serialString += '9' + std::to_string(getSecond() + 1);
        break;
    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
        serialString = 'a' + std::to_string(getFirst() + 1);
        break;
    case IF_STATEMENT:
        serialString = 'b' + lhs->peekSerialString() + rhs->peekSerialString();
        break;
    case IF_CON_T_STATEMENT:
        serialString = 'c' + lhs->peekSerialString();
        if (rhs)
        {
            serialString += 'd' + rhs->peekSerialString();
        }
        break;
    case DEFERRED_STATEMENT:
        serialString = 'e' + lhs->peekSerialString() + rhs->peekSerialString();
        break;
    case FOREACH_STATEMENT:
        serialString = 'f' + lhs->peekSerialString() + rhs->peekSerialString();
        break;
    case FOREACH_CON_T_STATEMENT:
        serialString = 'g' + lhs->peekSerialString();
        if (rhs)
        {
            serialString += 'h' + rhs->peekSerialString();
        }
        break;
    case STRING_STATEMENT:
        serialString = '/' + getString() + '/';
        break;
    case STMS_STATEMENT:
        serialString = '{' + getStatements()->peekSerialString() + '}';
        break;
    case NUMBER_STATEMENT:
        serialString = 'i' + getNumber();
        break;
    case SEARCH_STATEMENT:
        if (getBits())
            serialString = 'j' + getBits()->peekSerialString() + 'k' + lhs->peekSerialString();
        else
            serialString = 'l' + lhs->peekSerialString();
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::clone(const std::bitset<MAX_FLAGS> &protectedFlags)
{
    statementPtr statement = shared_from_this();
    switch (this->op)
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
        statement = Statement::create(this->lineno, this->bufferName, this->op, this->rootOp, getFeatures()->clone());
        break;
    case PAIRP_STATEMENT:
        statement = Statement::create(this->lineno, this->bufferName, this->op, this->rootOp, getPairp()->clone());
        break;
    case VARIABLE_STATEMENT:
    case CONSTANT_STATEMENT:
        statement = Statement::create(this->lineno, this->bufferName, this->op, this->rootOp, getBits()->clone());
        break;
    case ATTEST_STATEMENT:
        statement = Statement::create(this->lineno, this->bufferName, this->op, this->rootOp, this->lhs ? lhs->clone(protectedFlags) : statementPtr());
        break;
    case IF_STATEMENT:
    case IF_CON_T_STATEMENT:
    case FOREACH_STATEMENT:
    case FOREACH_CON_T_STATEMENT:
    case DEFERRED_STATEMENT:
    case UNIF_STATEMENT:
    case ASSIGNMENT_STATEMENT:
    case SUBSUME_STATEMENT:
        statement = Statement::create(this->lineno, this->bufferName, this->op, this->rootOp,
                                      lhs ? lhs->clone(protectedFlags) : statementPtr(),
                                      rhs ? rhs->clone(protectedFlags) : statementPtr());
        break;
    case FUNCTION_STATEMENT:
        statement = Statement::create(this->lineno, this->bufferName, this->op, this->rootOp, this->getFct(),
                                      lhs ? lhs->clone(protectedFlags) : statementPtr(),
                                      rhs ? rhs->clone(protectedFlags) : statementPtr());
        break;
    case STMS_STATEMENT:
    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:
    case PRINTSTDERR_STATEMENT:
    case PRINTLNSTDERR_STATEMENT:
        statement = Statement::create(this->lineno, this->bufferName, this->op, this->rootOp,
                                      getStatements()->clone(protectedFlags));
        break;
    case SEARCH_STATEMENT:
        statement = Statement::create(this->lineno, this->bufferName, this->op, this->rootOp,
                                      lhs ? lhs->clone(protectedFlags) : statementPtr(), this->getFirst());
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
    this->print(std::cout);
    std::cout << std::endl;
    item->print(std::cout);
    std::cout << "</div>" << std::endl;
#endif

    featuresPtr resultFeatures = Features::NIL;
    switch (this->op)
    {
    case FEATURES_STATEMENT:
    case GUARD_STATEMENT:
    {
        resultFeatures = getFeatures()->clone();
        if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0)
        {
            bool effect = false;
            item->getEnvironment()->replaceVariables(resultFeatures, effect);
        }
    }
    break;

    case INHERITED_FEATURES_STATEMENT:
    {
        resultFeatures = item->getInheritedFeatures()->clone();
        if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0)
        {
            bool effect = false;
            item->getEnvironment()->replaceVariables(resultFeatures, effect);
        }
    }
    break;

    case VARIABLE_STATEMENT:
    {
        if (item->getEnvironment())
        {
            valuePtr _value = item->getEnvironment()->find(getBits());
            if (!_value)
            {
                FATAL_ERROR_STM(shared_from_this());
            }
            if (_value && _value->isFeatures())
                resultFeatures = _value->getFeatures()->clone();
        }
    }
    break;

    case INHERITED_CHILDREN_FEATURES_STATEMENT:
    {
        resultFeatures = (*item->getInheritedSonFeatures())[getFirst()]->clone();
        if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0)
        {
            bool effect = false;
            item->getEnvironment()->replaceVariables(resultFeatures, effect);
        }
    }
    break;

    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
    {
        resultFeatures = (*item->getSynthesizedSonFeatures())[getFirst()]->clone();
        if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0)
        {
            bool effect = false;
            item->getEnvironment()->replaceVariables(resultFeatures, effect);
        }
    }
    break;

    case UNIF_STATEMENT:
    {
        featuresPtr fs1 = lhs->evalFeatures(item, parser, synthesizer, replaceVariables, verbose);
        featuresPtr fs2 = rhs->evalFeatures(item, parser, synthesizer, replaceVariables, verbose);
        if ((!fs1) || (!fs2))
        {
            resultFeatures = featuresPtr();
        }
        else
        {
            fs1->subFlags(Flags::SEEN);
            fs2->subFlags(Flags::SEEN);
            resultFeatures = unif(shared_from_this(), fs1, fs2, item, verbose);
            if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0)
            {
                bool effect = false;
                item->getEnvironment()->replaceVariables(resultFeatures, effect);
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
    this->print(std::cout);
    std::cout << std::endl;
    if (resultFeatures)
        resultFeatures->print(std::cout);
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
    this->print(std::cout);
    std::cout << "</div>" << std::endl;
#endif
    pairpPtr resultPairp = Pairp::NIL;
    switch (this->op)
    {

    case PAIRP_STATEMENT:
        resultPairp = getPairp()->clone();
        if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0)
        {
            bool effect = false;
            item->getEnvironment()->replaceVariables(resultPairp, effect);
        }
        break;

    case VARIABLE_STATEMENT:
        if (item->getEnvironment())
        {
            valuePtr _value = item->getEnvironment()->find(getBits());
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
                this->print(oss1);
                item->rulePrint(oss2, -1, true);
                WARNING_STM
                "<P>Variable " + oss1.str() + " not initialized in</P>" + oss2.str();
            }
        }
        break;

    case SEARCH_STATEMENT:
    {
        featuresPtr features = lhs->evalFeatures(item, parser, synthesizer, replaceVariables, verbose);
        if (!features)
        {
            FATAL_ERROR_UNEXPECTED;
        }
        uint16_t head = features->assignHead();
        uint16_t pos = this->getFirst();
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
                            resultPairp = Pairp::create(Value::create(parser.getLocalFeatures()));
                        else
                            resultPairp = Pairp::create(Pairp::create(Value::create(parser.getLocalFeatures())), resultPairp);
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
    this->print(std::cout);
    std::cout << std::endl;
    if (resultPairp)
        resultPairp->print(std::cout);
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
    this->print(std::cout, 0);
    item->print(std::cout);
    std::cout << "</div>" << std::endl;
    std::cout << "<H3>####################### ITEM #######################</H3>" << std::endl;
    item->print(std::cout);
    std::cout << std::endl;
#endif
    valuePtr resultValue = valuePtr();
    featuresPtr resultFeatures = featuresPtr();
    pairpPtr resultPairp = pairpPtr();
    switch (this->op)
    {

    case NIL_STATEMENT:
        resultValue = Value::STATIC_NIL;
        break;

    case ANONYMOUS_STATEMENT:
        resultValue = Value::STATIC_ANONYMOUS;
        break;

    case DASH_STATEMENT:
    {
        termsPtr t = item->getTerms(getFirst());
        // if (#i) false
        if (t->isOptional())
            resultValue = Value::STATIC_FALSE;
        else
        {
            // if (#i)
            if (getSecond() == UINT8_MAX)
            {
                resultValue = Value::STATIC_TRUE;
            }
            // if (#i.j)
            else
            {
                if (getSecond() == item->getIndexTerms()[getFirst()])
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
        resultValue = Value::create(Value::NUMBER_VALUE, getNumber());
        goto valueBuilt;
        break;

    case STRING_STATEMENT:
        resultValue = Value::create(Value::FORM_VALUE, getString());
        goto valueBuilt;
        break;

    case FEATURES_STATEMENT:
        resultFeatures = getFeatures();
        break;

    case INHERITED_FEATURES_STATEMENT:
        resultFeatures = item->getInheritedFeatures();
        break;

    case SYNTHESIZED_FEATURES_STATEMENT:
        resultFeatures = item->getSynthesizedFeatures();
        break;

    case VARIABLE_STATEMENT:
        if (replaceVariables && item->getEnvironment())
        {
            resultValue = item->getEnvironment()->find(bitset);
            if (!resultValue)
            {
                FATAL_ERROR_MSG_STM("Variable " + bitset->toString() + " not available");
            }
            goto valueBuilt;
        }
        else if (replaceVariables)
        {
            FATAL_ERROR_MSG_STM("Variable " + bitset->toString() + " not available");
            resultValue = valuePtr();
            goto valueBuilt;
        }
        else
        {
            resultValue = Value::create(Value::VARIABLE_VALUE, bitset);
        }
        break;

    case CONSTANT_STATEMENT:
        resultValue = Value::create(Value::CONSTANT_VALUE, getBits());
        break;

    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
        resultFeatures = (*item->getSynthesizedSonFeatures())[getFirst()];
        break;

    case INHERITED_CHILDREN_FEATURES_STATEMENT:
        resultFeatures = (*item->getInheritedSonFeatures())[getFirst()];
        break;

    case UNIF_STATEMENT:
    {
        featuresPtr fs1 = lhs->evalFeatures(item, parser, synthesizer, replaceVariables, verbose);
        if (!fs1)
        {
            resultValue = valuePtr();
            goto valueBuilt;
        }
        else
        {
            featuresPtr fs2 = rhs->evalFeatures(item, parser, synthesizer, replaceVariables, verbose);
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
        switch (getFct())
        {
        case NOP:
            break;

        case NOT:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if (!v1)
            {
                FATAL_ERROR_MSG_STM("Value not available");
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
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if (!v1 || !v2)
            {
                FATAL_ERROR_MSG_STM("Value not available");
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
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) || (!v2))
            {
                FATAL_ERROR_MSG_STM("Value not available");
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
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            bool isv1astring = false;
            std::string v1str;
            if (v1)
            {
                isv1astring = true;
                if (v1->isVariable())
                    v1str = v1->getBits()->to_string();
                else if (v1->isIdentifier())
                    v1str = Vartable::codeToName(v1->getCode());
                else if (v1->isString())
                    v1str = v1->getString();
                else
                    isv1astring = false;
            }
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            bool isv2astring = false;
            std::string v2str;
            if (v2)
            {
                isv2astring = true;
                if (v2->isVariable())
                    v2str = v2->getBits()->to_string();
                else if (v2->isIdentifier())
                    v2str = Vartable::codeToName(v2->getCode());
                else if (v2->isString())
                    v2str = v2->getString();
                else
                    isv2astring = false;
            }

            if ((!v1) || (!v2))
            {
                FATAL_ERROR_MSG_STM("Value not available");
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isNumber()) && (v2->isNumber()))
                resultValue = Value::create(Value::NUMBER_VALUE, v1->getNumber() + v2->getNumber());

            else if (isv1astring && isv2astring)
                resultValue = Value::create(Value::FORM_VALUE, v1str + v2str);

            else if ((v1->isPairp()) && (v2->isPairp()))
            {
                WARNING_STM;
                resultValue = valuePtr();
            }

            else
            {
                v1->flatPrint(std::cout);
                v2->flatPrint(std::cout);
                FATAL_ERROR_UNEXPECTED
            }
            goto valueBuilt;
        }
        break;

        case MINUS:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) || (!v2))
            {
                FATAL_ERROR_MSG_STM("Value not available");
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isNumber()) && (v2->isNumber()))
                resultValue = Value::create(Value::NUMBER_VALUE, v1->getNumber() - v2->getNumber());
            else
                resultValue = valuePtr();
            goto valueBuilt;
        }
        break;

        case TIMES:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) || (!v2))
            {
                FATAL_ERROR_MSG_STM("Value not available");
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isNumber()) && (v2->isNumber()))
                resultValue = Value::create(Value::NUMBER_VALUE, v1->getNumber() * v2->getNumber());
            else
                resultValue = valuePtr();
            goto valueBuilt;
        }
        break;

        case DIVIDE:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) || (!v2))
            {
                FATAL_ERROR_MSG_STM("Value not available");
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isNumber()) && (v2->isNumber()))
                resultValue = Value::create(Value::NUMBER_VALUE, v1->getNumber() / v2->getNumber());
            else
                resultValue = valuePtr();
            goto valueBuilt;
        }
        break;

        case MODULO:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) || (!v2))
            {
                FATAL_ERROR_MSG_STM("Value not available");
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isNumber()) && (v2->isNumber()))
                resultValue = Value::create(Value::NUMBER_VALUE, fmod(v1->getNumber(), v2->getNumber()));
            else
                resultValue = valuePtr();
            goto valueBuilt;
        }
        break;

        case MINUS_U:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if (!v1)
            {
                FATAL_ERROR_MSG_STM("Value not available");
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
            }
            else if ((v1->isNumber()))
                resultValue = Value::create(Value::NUMBER_VALUE, -v1->getNumber());
            else
                resultValue = valuePtr();
            goto valueBuilt;
        }
        break;

        case EQ:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) && (!v2))
            {
                FATAL_ERROR_MSG_STM("Value not available");
                FATAL_ERROR_UNEXPECTED;
                resultValue = valuePtr();
                // resultValue = Value::STATIC_TRUE;
            }
            else if (!v1 || !v2)
            {
                FATAL_ERROR_MSG_STM("Value not available");
                resultValue = valuePtr();
                FATAL_ERROR_UNEXPECTED;
                // resultValue = Value::STATIC_FALSE;
            }

            else if (v1->eq(v2))
                resultValue = Value::STATIC_TRUE;

            else
                resultValue = Value::STATIC_FALSE;

            goto valueBuilt;
        }
        break;

        case DIFF:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            if ((!v1) && (!v2))
                resultValue = Value::STATIC_FALSE;

            else if ((!v1) || (!v2))
            {
                FATAL_ERROR_MSG_STM("Value not available");
                FATAL_ERROR_UNEXPECTED;
                resultValue = Value::STATIC_TRUE;
            }

            else if (v1->eq(v2))
                resultValue = Value::STATIC_FALSE;

            else
                resultValue = Value::STATIC_TRUE;

            goto valueBuilt;
        }
        break;

        case LT:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            // si l'une est nulle
            if ((!v1) || (!v2))
            {
                FATAL_ERROR_MSG_STM("Value not available");
                FATAL_ERROR_UNEXPECTED;
                resultValue = Value::STATIC_NIL;
            }
            else if (v1->lt(v2))
                resultValue = Value::STATIC_TRUE;
            else
                resultValue = Value::STATIC_NIL;
            goto valueBuilt;
        }
        break;

        case LE:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            // si l'une est variable libre
            if ((!v1) || (!v2))
            {
                FATAL_ERROR_MSG_STM("Value not available");
                FATAL_ERROR_UNEXPECTED;
                resultValue = Value::STATIC_NIL;
            }
            else if ((v1->lt(v2)) || (v1->eq(v2)))
                resultValue = Value::STATIC_TRUE;
            else
                resultValue = Value::STATIC_NIL;
            goto valueBuilt;
        }
        break;

        case GT:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            // si l'une est variable libre
            if ((!v1) || (!v2))
            {
                FATAL_ERROR_MSG_STM("Value not available");
                FATAL_ERROR_UNEXPECTED;
                resultValue = Value::STATIC_NIL;
            }
            else if (!(v1->lt(v2)) && (!(v1->eq(v2))))
                resultValue = Value::STATIC_TRUE;
            else
                resultValue = Value::STATIC_NIL;
            goto valueBuilt;
        }
        break;

        case GE:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables, verbose);
            // si l'une est variable libre
            if ((!v1) || (!v2))
            {
                FATAL_ERROR_MSG_STM("Value not available");
                FATAL_ERROR_UNEXPECTED;
                resultValue = Value::STATIC_NIL;
            }
            else if (!(v1->lt(v2)))
                resultValue = Value::STATIC_TRUE;
            else
                resultValue = Value::STATIC_NIL;
            goto valueBuilt;
        }
        break;

        case RANDOM:
            resultValue = Value::create(Value::NUMBER_VALUE, (double)rand());
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
        if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0)
        {
            bool effect = false;
            item->getEnvironment()->replaceVariables(resultPairp, effect);
        }
        resultValue = Value::create(resultPairp);
    }

    else if (resultFeatures)
    {
        if (resultFeatures->isNil())
            resultValue = Value::STATIC_NIL;
        else if (resultFeatures->isBottom())
            resultValue = Value::STATIC_NIL;
        else
        {
            if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0)
            {
                bool effect = false;
                item->getEnvironment()->replaceVariables(resultFeatures, effect);
            }
            resultValue = Value::create(resultFeatures);
        }
    }

valueBuilt:
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::evalValue DONE #######################" << std::endl;
    std::cout << "<div>" << std::endl;
    this->print(std::cout);
    std::cout << "<H3>";
    if (resultValue)
        resultValue->print(std::cout);
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
        fs1->print(std::cout);
    std::cout << "</td><td>";
    if (fs2)
        fs2->print(std::cout);
    std::cout << "</td><td>";
    if (item->getEnvironment())
        item->getEnvironment()->print(std::cout);
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
                            result->add(Feature::create(Feature::_HEAD_, bitsetPtr(), (*i1)->getValue()));
                            if (!item->getEnvironment())
                            {
                                item->setEnvironment(Environment::create());
                            }
                            item->getEnvironment()->add(statementRoot, (*i2)->getValue()->getBits(), (*i1)->getValue(), verbose);
                            break;

                        default:
                            FATAL_ERROR_STM(statementRoot);
                            break;
                        }
                    }
                    break;

                    case Value::VARIABLE_VALUE:

                        if (((*i2)->getValue()->isVariable()) &&
                            (*(*i1)->getValue()->getBits()) == (*(*i2)->getValue()->getBits()))
                        {
                        } /* empty */
                        else
                        {
                            if (item)
                            {
                                if (!item->getEnvironment())
                                    item->setEnvironment(Environment::create());
                                item->getEnvironment()->add(statementRoot, (*i1)->getValue()->getBits(), (*i2)->getValue(), verbose);
                            }
                        }
                        result->add(Feature::create(Feature::_HEAD_, bitsetPtr(), (*i2)->getValue()));
                        break;

                    case Value::ANONYMOUS_VALUE:
                        result->add(Feature::create(Feature::_HEAD_, bitsetPtr(), (*i2)->getValue()));
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

                    // case Value::LIST_FEATURES_VALUE:
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
                            result->add(Feature::create(Feature::_CONSTANT_, (*i1)->getAttribute(),
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

                            result->add(Feature::create(Feature::_CONSTANT_, (*i1)->getAttribute(),
                                                        (*i1)->getValue()));
                            break;
                        case Value::VARIABLE_VALUE:
                            result->add(Feature::create(Feature::_CONSTANT_, (*i2)->getAttribute(),
                                                        (*i1)->getValue()));
                            if (!item->getEnvironment())
                                item->setEnvironment(Environment::create());
                            item->getEnvironment()->add(statementRoot, (*i2)->getValue()->getBits(), (*i1)->getValue(), verbose);
                            break;
                        default:
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

                            result->add(Feature::create(Feature::_CONSTANT_, (*i1)->getAttribute(),
                                                        Value::create(Value::NUMBER_VALUE,
                                                                      (*i1)->getValue()->getNumber())));
                            break;
                        case Value::VARIABLE_VALUE:
                            result->add(Feature::create(Feature::_CONSTANT_, (*i2)->getAttribute(),
                                                        (*i1)->getValue()));
                            if (!item->getEnvironment())
                                item->setEnvironment(Environment::create());
                            item->getEnvironment()->add(statementRoot, (*i2)->getValue()->getBits(), (*i1)->getValue(), verbose);
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

                            result->add(Feature::create(Feature::_CONSTANT_, (*i1)->getAttribute(),
                                                        Value::create(Value::IDENTIFIER_VALUE,
                                                                      (*i1)->getValue()->getCode())));
                            break;
                        case Value::VARIABLE_VALUE:
                            result->add(Feature::create(Feature::_CONSTANT_, (*i2)->getAttribute(),
                                                        (*i1)->getValue()));
                            if (!item->getEnvironment())
                                item->setEnvironment(Environment::create());
                            item->getEnvironment()->add(statementRoot, (*i2)->getValue()->getBits(), (*i1)->getValue(), verbose);
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
                            if (((*(*i1)->getValue()->getBits()) & (*(*i2)->getValue()->getBits())).none())
                            {
                                result = Features::BOTTOM;
                                goto endUnif;
                            }

                            result->add(Feature::create(Feature::_CONSTANT_, (*i1)->getAttribute(),
                                                        Value::create(Value::CONSTANT_VALUE, Bitset::create(
                                                                                                 *(*i1)->getValue()->getBits() &
                                                                                                 *(*i2)->getValue()->getBits()))));
                            break;
                        case Value::VARIABLE_VALUE:
                            result->add(Feature::create(Feature::_CONSTANT_, (*i2)->getAttribute(),
                                                        (*i1)->getValue()));
                            if (!item->getEnvironment())
                                item->setEnvironment(Environment::create());
                            item->getEnvironment()->add(statementRoot, (*i2)->getValue()->getBits(), (*i1)->getValue(), verbose);
                            break;
                        case Value::ANONYMOUS_VALUE:
                            result->add(Feature::create(Feature::_CONSTANT_, (*i2)->getAttribute(),
                                                        (*i1)->getValue()));
                            break;
                        default:
                            FATAL_ERROR_STM(statementRoot);
                            break;
                        }
                    }
                    break;

                    case Value::VARIABLE_VALUE:

                        if (((*i2)->getValue()->isVariable()) &&
                            (*(*i1)->getValue()->getBits()) == (*(*i2)->getValue()->getBits()))
                        {
                        } /* empty */
                        else
                        {
                            if (item)
                            {
                                if (!item->getEnvironment())
                                    item->setEnvironment(Environment::create());
                                item->getEnvironment()->add(statementRoot, (*i1)->getValue()->getBits(), (*i2)->getValue(), verbose);
                            }
                        }
                        result->add(Feature::create(Feature::_CONSTANT_, (*i1)->getAttribute(), (*i2)->getValue()));
                        break;

                    case Value::ANONYMOUS_VALUE:
                        result->add(Feature::create(Feature::_CONSTANT_, (*i1)->getAttribute(), (*i2)->getValue()));
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
                            result->add(Feature::create(Feature::_CONSTANT_, (*i1)->getAttribute(),
                                                        Value::create(_features)));
                    }
                    break;

                    case Value::PAIRP_VALUE:
                        result->add(Feature::create(Feature::_CONSTANT_, (*i1)->getAttribute(), (*i1)->getValue()));
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
        result->print(std::cout);
    std::cout << "</td><td>";
    if (item->getEnvironment())
        item->getEnvironment()->print(std::cout);
    std::cout << "</td></tr></table>";
#endif
    return result;
}

/* ************************************************************
 * ↓i = …
 ************************************************************ */
void Statement::buildInheritedSonFeatures(class Item *item, Parser &parser, Generator *synthesizer, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::buildInheritedSonFeatures #######################" << std::endl;
    std::cout << "buildInheritedSonFeatures: ";
    print(std::cout);
    std::cout << std::endl;
#endif
    if (!item->getInheritedSonFeatures()->get(lhs->getFirst())->isNil())
    {
        std::ostringstream oss;
        oss << "↓" << lhs->getFirst() + 1 << " defined twice";
        FATAL_ERROR_OS_MSG_STM(oss);
    }
    if (item->getInheritedSonFeatures()->size() < lhs->getFirst())
    {
        std::ostringstream oss;
        oss << "↓" << lhs->getFirst() + 1 << " not available";
        FATAL_ERROR_OS_MSG_STM(oss);
    }
    featuresPtr _features = rhs->evalFeatures(item, parser, synthesizer, true, verbose);

    if (_features->isNil())
        addFlags(Flags::BOTTOM);
    else
    {
        // CERR_LINE;
        item->getInheritedSonFeatures()->add(lhs->getFirst(), _features->clone());
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
    print(std::cout);
    std::cout << std::endl;
#endif
    if (!item->getSynthesizedFeatures()->isNil())
    {
        std::ostringstream oss;
        oss << "⇑"
            << " defined twice";
        FATAL_ERROR_OS_MSG_STM(oss);
    }
    featuresPtr _features = rhs->evalFeatures(item, parser, synthesizer, true, verbose);
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
    print(std::cout);
    std::cout << std::endl;
#endif
    switch (this->op)
    {
    case ASSIGNMENT_STATEMENT:
    {
        // $X = ⇓1;
        environmentPtr environment;
        if (item->getEnvironment())
        {
            environment = item->getEnvironment();
        }
        else
        {
            environment = Environment::create();
            item->setEnvironment(environment);
        }
        featuresPtr sonSynth = rhs->evalFeatures(item, parser, synthesizer, true, verbose);
        if (sonSynth)
        {
            environment->add(statementRoot, lhs->getBits(), Value::create(sonSynth), verbose);
        }
        else
            FATAL_ERROR_STM(shared_from_this());
    }
    break;

    case SUBSUME_STATEMENT:
    {
        // [ … $X … ] ⊂ ...;

        featuresPtr left = lhs->evalFeatures(item, parser, synthesizer, false, verbose);
        if (!left)
        {
            FATAL_ERROR_STM(shared_from_this());
            // WARNING_STM;
        }
        else
        {
            environmentPtr environment;
            if (item->getEnvironment())
                environment = item->getEnvironment();
            else
            {
                environment = Environment::create();
                item->setEnvironment(environment);
            }
            featuresPtr sonSynth = rhs->evalFeatures(item, parser, synthesizer, true, verbose);
            if (sonSynth)
            {
                if (!left->buildEnvironment(statementRoot, environment, sonSynth, true
#ifdef TRACE_BUILD_ENVIRONMENT
                                            ,true
#endif
                                            , verbose))
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
    print(std::cout);
    std::cout << std::endl;
#endif
    switch (this->op)
    {
    case ASSIGNMENT_STATEMENT:
    {
        // $X = ↑;
        featuresPtr right = rhs->evalFeatures(item, parser, synthesizer, true, verbose);
        if (!right)
        {
            WARNING_STM;
        }
        else
        {
            environmentPtr environment;
            if (item->getEnvironment())
            {
                environment = item->getEnvironment();
            }
            else
            {
                environment = Environment::create();
                item->setEnvironment(environment);
            }
            environment->add(statementRoot, lhs->getBits(), Value::create(right), verbose);
        }
    }
    break;

    case SUBSUME_STATEMENT:
    {
        featuresPtr left = lhs->evalFeatures(item, parser, synthesizer, false, verbose);
        if (!left)
        {
            FATAL_ERROR_UNEXPECTED;
            // WARNING_STM;
        }
        else
        {
            featuresPtr right = rhs->evalFeatures(item, parser, synthesizer, true, verbose);
            if (!right)
            {
                FATAL_ERROR_UNEXPECTED;
                // WARNING_STM;
            }
            else
            {
                environmentPtr environment;
                if (item->getEnvironment())
                {
                    environment = item->getEnvironment();
                }
                else
                {
                    environment = Environment::create();
                    item->setEnvironment(environment);
                }
                if (!left->buildEnvironment(statementRoot, environment, right, true
#ifdef TRACE_BUILD_ENVIRONMENT
                                            ,
                                            true
#endif
                                            , verbose))
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
    print(std::cout);
    std::cout << std::endl;
#endif
    switch (this->op)
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

        if (lhs->isVariable())
        {
            valuePtr right = rhs->evalValue(item, parser, synthesizer, true, verbose);
            if (!right)
            {
                this->print(std::cerr);
                WARNING_STM;
            }
            else
            {
                environmentPtr environment;
                if (item->getEnvironment())
                {
                    environment = item->getEnvironment();
                }
                else
                {
                    environment = Environment::create();
                    item->setEnvironment(environment);
                }
                environment->add(statementRoot, lhs->getBits(), right, verbose);
            }
        }

        // 	 < … > = $X;
        // 	 < … > = ( … )
        // 	 < … > = sort $X with a;
        // 	 < … > = reverse $X;
        else if (lhs->isPairp())
        {
            pairpPtr right = rhs->evalPairp(item, parser, synthesizer, true, verbose);
            if (!right)
            {
                FATAL_ERROR_STM(shared_from_this());
            }
            else
            {
                if (right->isNil())
                {
                    print(std::cerr);
                    FATAL_ERROR_STM(shared_from_this());
                }
                pairpPtr left = lhs->evalPairp(item, parser, synthesizer, false, verbose);
                if (!left)
                {
                    WARNING_STM;
                }
                else
                {
                    environmentPtr environment;
                    if (item->getEnvironment())
                    {
                        environment = item->getEnvironment();
                    }
                    else
                    {
                        environment = Environment::create();
                        item->setEnvironment(environment);
                    }
                    if (!left->buildEnvironment(statementRoot, environment, right, true, true, verbose))
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
        featuresPtr right = rhs->evalFeatures(item, parser, synthesizer, true, verbose);
        if (!right)
        {
            WARNING_STM;
        }
        else
        {
            // if (right->isNil())
            //{
            // } // empty
            featuresPtr left = lhs->evalFeatures(item, parser, synthesizer, false, verbose);
            if (left)
            {
                environmentPtr environment;
                if (item->getEnvironment())
                {
                    environment = item->getEnvironment();
                }
                else
                {
                    environment = Environment::create();
                    item->setEnvironment(environment);
                }
                if (!left->buildEnvironment(statementRoot, environment, right, true
#ifdef TRACE_BUILD_ENVIRONMENT
                                            ,
                                            true
#endif
                                            , verbose))
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
    print(std::cout);
    std::cout << std::endl;
#endif
    switch (this->op)
    {
    case ATTEST_STATEMENT:
    {
        valuePtr res = lhs->evalValue(item, parser, synthesizer, true, verbose);
        if (!res || res->isFalse() ||
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
    item->print(std::cout);
    print(std::cout);
    std::cout << std::endl;
#endif
    if (isSetFlags(Flags::DISABLED | Flags::SEEN))
    {
        FATAL_ERROR_UNEXPECTED;
    }
    featuresPtr localFeatures = getFeatures();
    if (!localFeatures)
    {
        FATAL_ERROR_STM(shared_from_this());
    }
    environmentPtr environment;
    if (item->getEnvironment())
        environment = item->getEnvironment();
    else
    {
        environment = Environment::create();
        item->setEnvironment(environment);
    }
    featuresPtr localRhs = item->getInheritedFeatures();

    if (!localFeatures->buildEnvironment(statementRoot, environment, localRhs, false
#ifdef TRACE_BUILD_ENVIRONMENT
                                         ,
                                         true
#endif
                                         , verbose))
    {
        addFlags(Flags::BOTTOM);
    }
    if (item->getEnvironment()->size() == 0)
    {
        item->getEnvironment().reset();
        item->setEnvironment(environmentPtr());
    }
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::stmGuard DONE #######################" << std::endl;
    item->print(std::cout);
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
    item->print(std::cout);
    std::cout << std::endl;
#endif
    addFlags(Flags::SEEN);
    statementPtr variable = getLhs();
    valuePtr value = getRhs()->getLhs()->evalValue(item, parser, synthesizer, true, verbose);
    statementPtr statement = getRhs()->getRhs();
    if (value->isPairp())
    {
        value->getPairp()->apply(statementRoot, item, parser, synthesizer, variable, statement, effect, verbose);
    }

    // else if (value->isListFeatures())
    // {
    //     FATAL_ERROR_MSG_STM("foreach does'nt apply a list");
    //     value->getListFeatures()->apply(statementRoot, item, parser, synthesizer, variable, statement, effect);
    // }

    else
    {
        FATAL_ERROR_MSG_STM("foreach does'nt apply a list");
    }
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::stmForeach DONE #######################" << std::endl;
    item->print(std::cout);
    std::cout << std::endl;
#endif
}

/* ************************************************************
 * if
 ************************************************************ */
void Statement::stmIf(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "####################### Statement::stmIf #######################" << std::endl;
    item->print(std::cout);
    std::cout << std::endl;
#endif
    statementPtr leftHandSide = getRhs()->getLhs();
    statementPtr rightHandSide = getRhs()->getRhs();
    enum test_choice result = __NONE__;
    if (lhs->isSetFlags(Flags::CHOOSEN))
    {
        result = __THEN__;
    }
    else if (rhs && rhs->isSetFlags(Flags::CHOOSEN))
    {
        result = __ELSE__;
    }
    else
    {
        valuePtr res = getLhs()->evalValue(item, parser, synthesizer, true, verbose);
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
        leftHandSide->apply(statementRoot, item, parser, synthesizer, effect, verbose);
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
            rightHandSide->apply(statementRoot, item, parser, synthesizer, effect, verbose);
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
    item->print(std::cout);
    std::cout << std::endl;
#endif
}

/* ************************************************************
 * DEFERRED
 ************************************************************ */
void Statement::stmDeferred(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool verbose)
{
    rhs->apply(statementRoot, item, parser, synthesizer, effect, verbose);
    if (rhs->isSetFlags(Flags::BOTTOM))
        addFlags(Flags::BOTTOM);
    if (rhs->isSetFlags(Flags::SEEN))
        addFlags(Flags::SEEN);
}

/* ************************************************************
 * print
 ************************************************************ */
void Statement::stmPrint(class Item *item, Parser &parser, Generator *generator, std::ostream &out, bool verbose)
{
    addFlags(Flags::SEEN);
    for (auto statement = getStatements()->cbegin(); statement != getStatements()->cend(); ++statement)
    {
        if ((*statement)->isString())
        {
            out << (*statement)->getString();
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

/* **************************************************
 *
 ************************************************** */
void Statement::renameVariables(uint32_t code)
{
    switch (this->op)
    {
    case VARIABLE_STATEMENT:
        bitset = Vartable::createVariable(getBits()->toString(), code);
        resetSerial();
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
        Vartable::renameVariables(string, code);
        break;
    case ASSIGNMENT_STATEMENT:
    case SUBSUME_STATEMENT:
    case FUNCTION_STATEMENT:
    case UNIF_STATEMENT:
    case ATTEST_STATEMENT:
    case IF_STATEMENT:
    case IF_CON_T_STATEMENT:
    case FOREACH_STATEMENT:
    case FOREACH_CON_T_STATEMENT:
    case DEFERRED_STATEMENT:
        if (lhs)
            lhs->renameVariables(code);
        if (rhs)
            rhs->renameVariables(code);
        break;
    case FEATURES_STATEMENT:
    case GUARD_STATEMENT:
        getFeatures()->renameVariables(code);
        break;
    case PAIRP_STATEMENT:
        getPairp()->renameVariables(code);
        break;
    case STMS_STATEMENT:
    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:
    case PRINTSTDERR_STATEMENT:
    case PRINTLNSTDERR_STATEMENT:
        getStatements()->renameVariables(code);
        break;
    }
}

/* ************************************************************
 *
 ************************************************************ */
void Statement::toggleEnable(statementPtr statementRoot, class Item *item, Generator *synthesizer, bool &result, bool on)
{
#ifdef TRACE_ENABLE_STATEMENT
    std::cout << "<H3>####################### TRACE_ENABLE_STATEMENT #######################</H3>" << std::endl;
    print(std::cout);
    std::cout << std::endl;
#endif
    switch (this->op)
    {

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
        // if (getFirst() > item->getRuleRhs().size())
        // {
        //     std::ostringstream oss;
        //     oss << "#" << lhs->getFirst() + 1 << " not available";
        //     FATAL_ERROR_OS_MSG_STM(oss);
        // }
        if (on)
        {
            if (item->getIndexTerms()[getFirst()] == Item::NA)
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
            if (!item->getEnvironment() || !item->getEnvironment()->find(getBits()))
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
            oss << "⇓" << lhs->getFirst() + 1 << " not available";
            FATAL_ERROR_OS_MSG_STM(oss);
        }
        if (on)
        {
            if ((*item->getSynthesizedSonFeatures())[getFirst()]->isNil())
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
        getStatements()->toggleEnable(item, synthesizer, result, on);
        break;

    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:
    case PRINTSTDERR_STATEMENT:
    case PRINTLNSTDERR_STATEMENT:

        if (on)
        {
            for (auto i = getStatements()->cbegin(); i != getStatements()->cend(); ++i)
            {
                bool effect = false;
                (*i)->toggleEnable(*i, item, synthesizer, effect, on);
                if (effect && (*i)->isSetFlags(Flags::DISABLED))
                {
                    statementRoot->addFlags(Flags::DISABLED);
                    result = true;
                }
            }
        }
        else
        {
            for (auto i = getStatements()->cbegin(); i != getStatements()->cend(); ++i)
            {
                (*i)->subFlags(Flags::DISABLED);
            }
            statementRoot->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case IF_STATEMENT:
        if (lhs)
        {
            lhs->toggleEnable(statementRoot, item, synthesizer, result, on);
        }
        if (statementRoot->isUnsetFlags(Flags::DISABLED))
        {
            rhs->toggleEnable(rhs, item, synthesizer, result, on);
        }
        break;

    case IF_CON_T_STATEMENT:
        lhs->toggleEnable(lhs, item, synthesizer, result, on);
        if (rhs)
            rhs->toggleEnable(rhs, item, synthesizer, result, on);
        break;

    case FOREACH_STATEMENT:
        rhs->toggleEnable(shared_from_this(), item, synthesizer, result, on);
        break;

    case FOREACH_CON_T_STATEMENT:
        lhs->toggleEnable(statementRoot, item, synthesizer, result, on);
        rhs->toggleEnable(rhs, item, synthesizer, result, on);
        break;

    case DEFERRED_STATEMENT:
        lhs->toggleEnable(shared_from_this(), item, synthesizer, result, on);
        rhs->toggleEnable(shared_from_this(), item, synthesizer, result, on);
        break;

    case ASSIGNMENT_STATEMENT:
    case SUBSUME_STATEMENT:
        rhs->toggleEnable(shared_from_this(), item, synthesizer, result, on);
        break;

    case FUNCTION_STATEMENT:
    case UNIF_STATEMENT:
        if (lhs)
            lhs->toggleEnable(statementRoot, item, synthesizer, result, on);
        if (rhs)
            rhs->toggleEnable(statementRoot, item, synthesizer, result, on);
        break;

    case ATTEST_STATEMENT:
        lhs->toggleEnable(statementRoot, item, synthesizer, result, on);
        break;

    case PAIRP_STATEMENT:
        getPairp()->enable(statementRoot, item, synthesizer, result, on);
        break;

    case FEATURES_STATEMENT:
        getFeatures()->enable(statementRoot, item, synthesizer, result, on);
        break;

    case SEARCH_STATEMENT:
        if (lhs)
            lhs->toggleEnable(statementRoot, item, synthesizer, result, on);
        break;

    default:
        break;
    }
#ifdef TRACE_ENABLE_STATEMENT
    std::cout << "<H3>####################### TRACE_ENABLE_STATEMENT CON'T #######################</H3>" << std::endl;
    root->printFlags(std::cout);
    print(std::cout);
    std::cout << std::endl;
#endif
}

/* **************************************************
 *
 ************************************************** */
void Statement::apply(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool verbose)
{
#ifdef TRACE_APPLY_STATEMENT
    std::cout << "<H3>####################### TRACE_APPLY_STATEMENT #######################</H3>" << std::endl;
    std::cout << "Apply: " << std::endl;
    print(std::cout);
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
        stmIf(statementRoot, item, parser, synthesizer, effect, verbose);
    }

    // foreach $i in $list
    else if (isForeach())
    {
        stmForeach(statementRoot, item, parser, synthesizer, effect, verbose);
    }

    // DEFERRED
    else if (isDeferred())
    {
        stmDeferred(statementRoot, item, parser, synthesizer, effect, verbose);
    }

    // ↓i = …
    else if ((isAssignment()) && (getLhs()->isDown()))
    {
        buildInheritedSonFeatures(item, parser, synthesizer, verbose);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // [ … $X … ] ⊂ ⇓1
    // $X = ⇓i
    else if (((isSubsume()) && (getRhs()->isDown2()) && (getLhs()->isFeatures())) ||
             ((isAssignment()) && (getRhs()->isDown2()) && (getLhs()->isVariable())))
    {
        buildEnvironmentWithSynthesize(statementRoot, item, parser, synthesizer, verbose);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // [ … $X … ] ⊂ ↑
    // $X = ↑
    else if (((isSubsume()) && (getRhs()->isUp()) && (getLhs()->isFeatures())) ||
             ((isAssignment()) && (getRhs()->isUp()) && (getLhs()->isVariable())))
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
    else if (((isAssignment()) && (getLhs()->isVariable()) && ((getRhs()->isConstant()) || (getRhs()->isVariable()) || (getRhs()->isUnif()) || (getRhs()->isFeatures()) || (getRhs()->isNumber()) || (getRhs()->isString()) || (getRhs()->isFct()) || (getRhs()->isPairp()) || (getRhs()->isSearch())))

             || ((isAssignment()) && (getLhs()->isPairp()) && ((getRhs()->isVariable()) || (getRhs()->isPairp()) || (getRhs()->isSearch())))

             || ((isSubsume()) && (getLhs()->isFeatures()) && ((getRhs()->isVariable()) || (getRhs()->isFeatures()))))
    {
        buildEnvironmentWithValue(statementRoot, item, parser, synthesizer, verbose);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // ⇑ = …
    else if ((isAssignment()) && (getLhs()->isUp2()))
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

    // printstderr
    else if (isPrintstderr())
    {
        stmPrint(item, parser, synthesizer, std::cerr, verbose);
        addFlags(Flags::SEEN);
    }

    // printlnsterr
    else if (isPrintlnstderr())
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
    item->print(std::cout);
    std::cout << std::endl;
#endif
}

/* **************************************************
 *
 ************************************************** */
void Statement::lookingForAssignedInheritedSonFeatures(std::vector<bool> &assignedInheritedSonFeatures)
{
    switch (this->op)
    {
    case ASSIGNMENT_STATEMENT:
        // ↓1 = …
        if ((this->isAssignment()) && (this->getLhs()->isDown()))
            assignedInheritedSonFeatures[this->getLhs()->getFirst()] = true;
        break;

    case IF_STATEMENT:
    {
        statementPtr left = getRhs()->getLhs();
        statementPtr right = getRhs()->getRhs();
        if (left->isSetFlags(Flags::CHOOSEN))
        {
            left->lookingForAssignedInheritedSonFeatures(assignedInheritedSonFeatures);
        }
        else if (right && right->isSetFlags(Flags::CHOOSEN))
        {
            right->lookingForAssignedInheritedSonFeatures(assignedInheritedSonFeatures);
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
bool Statement::findVariable(const bitsetPtr &variable)
{
    switch (this->op)
    {

    case STMS_STATEMENT:
    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:
    case PRINTSTDERR_STATEMENT:
    case PRINTLNSTDERR_STATEMENT:
        if (getStatements()->findVariable(variable))
            return true;
        break;

    case IF_STATEMENT:
        if (rhs->findVariable(variable))
            return true;
        break;

    case IF_CON_T_STATEMENT:
        if (lhs->findVariable(variable))
            return true;
        if (rhs)
            if (rhs->findVariable(variable))
                return true;
        break;

    case FOREACH_STATEMENT:
        if (rhs->findVariable(variable))
            return true;
        break;

    case FOREACH_CON_T_STATEMENT:
        if (lhs->findVariable(variable))
            return true;
        if (rhs)
            if (rhs->findVariable(variable))
                return true;
        break;

    case GUARD_STATEMENT:
        if (getFeatures()->findVariable(variable))
            return true;
        break;

    case ASSIGNMENT_STATEMENT:
    case SUBSUME_STATEMENT:
        if (rhs->findVariable(variable))
            return true;
        break;

    case FUNCTION_STATEMENT:
    case UNIF_STATEMENT:
        if (lhs && lhs->findVariable(variable))
            return true;
        if (rhs && rhs->findVariable(variable))
            return true;
        break;

    case ATTEST_STATEMENT:
        if (lhs->findVariable(variable))
            return true;
        break;

    case VARIABLE_STATEMENT:
        if (getBits() == variable)
            return true;
        break;

    case PAIRP_STATEMENT:
        if (getPairp()->findVariable(variable))
            return true;
        break;

    case FEATURES_STATEMENT:
        if (getFeatures()->findVariable(variable))
            return true;
        break;

    default:
        FATAL_ERROR_UNEXPECTED
        break;
    }
    return false;
}
