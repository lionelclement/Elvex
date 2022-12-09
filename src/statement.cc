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
#include "synthesizer.hpp"
#include "parser.hpp"
#include "bitset.hpp"
#include "vartable.hpp"

/* **************************************************
 *
 ************************************************** */
Statement::Statement(unsigned int lineno, std::string bufferName, type op, bool rootOp)
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
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    return statementPtr(statement);
}

/* **************************************************
 * DOWN DOWN2 DASH
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp, unsigned int first, unsigned int second)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->first = first;
    statement->second = second;
    return statementPtr(statement);
}

/* **************************************************
 * STMS PRINT PRINTLN
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp, statementsPtr statements)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->statements = statements;
    return statementPtr(statement);
}

/* **************************************************
 * GUARD FEATURES
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp, featuresPtr features)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->features = std::move(features);
    return statementPtr(statement);
}

/* **************************************************
 * ATTEST
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp, statementPtr lhs)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->lhs = std::move(lhs);
    return statementPtr(statement);
}

/* **************************************************
 * AFF SUBSUME IF IF_CON_T WAIT FOREACH FOREACH_CON_T UNIF
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp, statementPtr lhs, statementPtr rhs)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->lhs = std::move(lhs);
    statement->rhs = std::move(rhs);
    return statementPtr(statement);
}

/* **************************************************
 * VARIABLE CONSTANT
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp, bitsetPtr bitset)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->bitset = std::move(bitset);
    return statementPtr(statement);
}

/* **************************************************
 * PAIRP
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp, pairpPtr pairp)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->pairp = std::move(pairp);
    return statementPtr(statement);
}

/* **************************************************
 * FCT
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp,
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
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp, double number)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->number = number;
    return statementPtr(statement);
}

/* **************************************************
 * STRING
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp, std::string string)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->string = string;
    return statementPtr(statement);
}

/* **************************************************
 * ANONYMOUS
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp, valuePtr &value)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->value = std::move(value);
    return statementPtr(statement);
}

/* **************************************************
 * SEARCH
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, std::string bufferName, type op, bool rootOp, statementPtr lhs, unsigned int first)
{
    Statement *statement = new Statement(lineno, bufferName, op, rootOp);
    statement->lhs = std::move(lhs);
    statement->first = first;
    return statementPtr(statement);
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isAff() const
{
    return op == AFF_STATEMENT;
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
bool Statement::isWait() const
{
    return op == WAIT_STATEMENT;
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
unsigned int Statement::getFirst() const
{
    return first;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Statement::getSecond() const
{
    return second;
}

/* **************************************************
 *
 ************************************************** */
std::string Statement::getString() const
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
unsigned int Statement::getLineno() const
{
    return lineno;
}

/* **************************************************
 *
 ************************************************** */
void Statement::brln(std::ostream &out, int tabulation) const
{
    out << "<BR>";
    for (unsigned int j = 1; j <= tabulation; ++j)
        out << "&nbsp;";
}

/* **************************************************
 *
 ************************************************** */
void Statement::print(std::ostream &out, unsigned int tabulation, int yetColored) const
{
#define BLACK 0x000000u
#define RED 0xFF0000u
#define GREEN 0x00FF00u
#define BLUE 0x0000FFu
#define GRAY 0xC0C0C0u
    unsigned int color = yetColored;
    if (isSetFlags(Flags::SEEN))
    {
        color |= BLUE;
    }
    if (isSetFlags(Flags::DISABLED))
    {
        color |= GRAY;
    }
    if (isSetFlags(Flags::BOTTOM))
    {
        color |= RED;
    }

    switch (this->op)
    {
    case ATTEST_STATEMENT:
    case AFF_STATEMENT:
    case SUBSUME_STATEMENT:
    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:
    case GUARD_STATEMENT:
        if (color)
        {
            out << "<SPAN style=\"color:#" << std::setfill('0') << std::setw(6) << std::hex << color << ";\">";
        }
        break;
    case STMS_STATEMENT:
        if ((color & GRAY) == GRAY)
        {
            out << "<SPAN style=\"color:#" << std::setfill('0') << std::setw(6) << std::hex << (color & GRAY) << ";\">";
        }
    default:
        break;
    }

    switch (this->op)
    {

    case STMS_STATEMENT:
        getStatements()->print(out, tabulation, yetColored, true, "{", "}", "");
        break;

    case IF_STATEMENT:
        if (color)
        {
            out << "<SPAN style=\"color:#" << std::setfill('0') << std::setw(6) << std::hex << color << ";\">";
        }
        out << "if&nbsp;(";
        lhs->print(out);
        out << ')';
        if (color)
        {
            out << "</SPAN>";
        }
        rhs->print(out, tabulation, color);
        break;

    case IF_CON_T_STATEMENT:
        if (lhs->isSetFlags(Flags::REJECTED))
        {
            out << "<S>";
        }
        if (lhs->isSetFlags(Flags::CHOOSEN))
        {
            out << "<U>";
        }
        if (lhs->isStms())
        {
            lhs->print(out, tabulation, color);
        }
        else
        {
            brln(out, tabulation + 3);
            lhs->print(out, tabulation + 3, color);
        }
        if (lhs->isSetFlags(Flags::CHOOSEN))
        {
            out << "</U>";
        }
        if (lhs->isSetFlags(Flags::REJECTED))
        {
            out << "</S>";
        }

        if (rhs)
        {
            for (unsigned int j = 1; j <= tabulation; j++)
                out << "&nbsp;";
            out << "else ";

            if (rhs->isSetFlags(Flags::REJECTED))
            {
                out << "<S>";
            }
            if (rhs->isSetFlags(Flags::CHOOSEN))
            {
                out << "<U>";
            }
            if (rhs->isStms())
            {
                rhs->print(out, tabulation, color);
            }
            else
            {
                brln(out, tabulation + 3);
                rhs->print(out, tabulation + 3, color);
            }
            if (rhs->isSetFlags(Flags::CHOOSEN))
            {
                out << "</U>";
            }
            if (rhs->isSetFlags(Flags::REJECTED))
            {
                out << "</S>";
            }
        }
        break;

    case WAIT_STATEMENT:
        if (color)
        {
            out << "<SPAN style=\"color:#" << std::setfill('0') << std::setw(6) << std::hex << color << ";\">";
        }
        out << "wait&nbsp;(";
        lhs->print(out);
        out << ')';
        if (color)
        {
            out << "</SPAN>";
        }
        if (rhs->isStms())
        {
            rhs->print(out, tabulation, color);
        }
        else
        {
            brln(out, tabulation + 3);
            rhs->print(out, tabulation + 3, color);
        }
        break;

    case FOREACH_STATEMENT:
        if (color)
        {
            out << "<SPAN style=\"color:#" << std::setfill('0') << std::setw(6) << std::hex << color << ";\">";
        }
        out << "foreach&nbsp;";
        lhs->print(out);
        out << "&nbsp;";
        if (color)
        {
            out << "</SPAN>";
        }
        rhs->print(out, tabulation, color);
        break;

    case FOREACH_CON_T_STATEMENT:
        if (color)
        {
            out << "<SPAN style=\"color:#" << std::setfill('0') << std::setw(6) << std::hex << color << ";\">";
        }
        out << "in&nbsp;";
        lhs->print(out);
        if (color)
        {
            out << "</SPAN>";
        }
        if (rhs->isStms())
        {
            rhs->print(out, tabulation, color);
        }
        else
        {
            brln(out, tabulation + 3);
            rhs->print(out, tabulation + 3, color);
        }
        break;

    case ATTEST_STATEMENT:
        out << "attest&nbsp;";
        lhs->print(out);
        break;
    case NIL_STATEMENT:
        out << "NIL";
        break;
    case AFF_STATEMENT:
        lhs->print(out);
        out << "&nbsp;=&nbsp;";
        rhs->print(out);
        break;
    case SUBSUME_STATEMENT:
        lhs->print(out);
        out << "&nbsp;⊂&nbsp;";
        rhs->print(out);
        break;
    case CONSTANT_STATEMENT:
    case VARIABLE_STATEMENT:
        out << getBits()->toString();
        break;
    case ANONYMOUS_STATEMENT:
        out << '_';
        break;
    case PRINT_STATEMENT:
        out << "print&nbsp;";
        getStatements()->print(out, tabulation, yetColored, false, "(", ")", ",&nbsp;");
        break;
    case PRINTLN_STATEMENT:
        out << "println&nbsp;";
        getStatements()->print(out, tabulation, yetColored, false, "(", ")", ",&nbsp;");
        break;
    case FEATURES_STATEMENT:
        getFeatures()->flatPrint(out);
        break;
    case PAIRP_STATEMENT:
        getPairp()->flatPrint(out, true);
        break;
    case GUARD_STATEMENT:
        getFeatures()->flatPrint(out);
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
        if (getSecond() != UINT_MAX)
        {
            out << "." << std::to_string(getSecond() + 1);
        }
        break;
    case INHERITED_CHILDREN_FEATURES_STATEMENT:
        out << "↓" << getFirst() + 1;
        if (getSecond() != UINT_MAX)
        {
            out << "." << getSecond() + 1;
        }
        break;
    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
        out << "⇓";
        out << getFirst() + 1;
        break;
    case STRING_STATEMENT:
        out << "&quot;" << getString() << "&quot;";
        break;
    case NUMBER_STATEMENT:
        out << getNumber();
        break;
    case SEARCH_STATEMENT:
        out << "search&nbsp;";
        lhs->print(out);
        out << "&nbsp;on&nbsp;";
        out << Vartable::codeToString(first);
        break;
    case FUNCTION_STATEMENT:
        switch (this->getFct())
        {
        case NOP:
            out << "nop&nbsp;";
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
        case RAND:
            out << "rand()";
            break;
        default:
            FATAL_ERROR_UNEXPECTED;
        }
    }

    switch (this->op)
    {
    case STMS_STATEMENT:
        if ((color & GRAY) == GRAY)
        {
            out << "</SPAN>";
        }
        break;
    case ATTEST_STATEMENT:
    case AFF_STATEMENT:
    case SUBSUME_STATEMENT:
    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:
    case GUARD_STATEMENT:
        if (color)
        {
            out << "</SPAN>";
        }
        out << ";<BR>";
        break;
    default:
        break;
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
        serialString = 'N';
        break;
    case AFF_STATEMENT:
        serialString = lhs->peekSerialString() + '=' + rhs->peekSerialString();
        break;
    case SUBSUME_STATEMENT:
        serialString = lhs->peekSerialString() + "⊂" + rhs->peekSerialString();
        break;
    case FUNCTION_STATEMENT:
        switch (this->getFct())
        {
        case NOP:
            serialString = ';';
            break;
        case NOT:
            serialString = "¬(" + lhs->peekSerialString() + ')';
            break;
        case AND:
            serialString = '(' + lhs->peekSerialString() + "∧" + rhs->peekSerialString() + ')';
            break;
        case OR:
            serialString = '(' + lhs->peekSerialString() + "∨" + rhs->peekSerialString() + ')';
            break;
        case DIFF:
            serialString = '(' + lhs->peekSerialString() + "≠" + rhs->peekSerialString() + ')';
            break;
        case EQ:
            serialString = '(' + lhs->peekSerialString() + "==" + rhs->peekSerialString() + ')';
            break;
        case PLUS:
            serialString = '(' + lhs->peekSerialString() + '+' + rhs->peekSerialString() + ')';
            break;
        case MINUS:
            serialString = '(' + lhs->peekSerialString() + '-' + rhs->peekSerialString() + ')';
            break;
        case TIMES:
            serialString = '(' + lhs->peekSerialString() + '*' + rhs->peekSerialString() + ')';
            break;
        case DIVIDE:
            serialString = '(' + lhs->peekSerialString() + '/' + rhs->peekSerialString() + ')';
            break;
        case MODULO:
            serialString = '(' + lhs->peekSerialString() + '%' + rhs->peekSerialString() + ')';
            break;
        case LT:
            serialString = '(' + lhs->peekSerialString() + '<' + rhs->peekSerialString() + ')';
            break;
        case LE:
            serialString = '(' + lhs->peekSerialString() + "≤" + rhs->peekSerialString() + ')';
            break;
        case GT:
            serialString = '(' + lhs->peekSerialString() + '>' + rhs->peekSerialString() + ')';
            break;
        case GE:
            serialString = '(' + lhs->peekSerialString() + "≥" + rhs->peekSerialString() + ')';
            break;
        case MINUS_U:
            serialString = '-' + lhs->peekSerialString();
            break;
        case RAND:
            serialString = "r()";
            break;
        }
        break;
    case CONSTANT_STATEMENT:
    case VARIABLE_STATEMENT:
        serialString = getBits()->peekSerialString();
        break;
    case ANONYMOUS_STATEMENT:
        serialString = '_';
        break;
    case PRINT_STATEMENT:
        serialString = "P " + getStatements()->peekSerialString();
        break;
    case PRINTLN_STATEMENT:
        serialString = "PL " + getStatements()->peekSerialString();
        break;
    case FEATURES_STATEMENT:
        serialString = getFeatures()->peekSerialString();
        break;
    case PAIRP_STATEMENT:
        serialString = getPairp()->peekSerialString();
        break;
    case GUARD_STATEMENT:
        serialString = "G " + getFeatures()->peekSerialString();
        break;
    case UNIF_STATEMENT:
        serialString = '(' + lhs->peekSerialString() + "∪" + rhs->peekSerialString() + ')';
        break;
    case INHERITED_FEATURES_STATEMENT:
        serialString = "↑";
        break;
    case SYNTHESIZED_FEATURES_STATEMENT:
        serialString = "⇑";
        break;
    case DASH_STATEMENT:
        serialString = '#' + std::to_string(getFirst() + 1);
        if (getSecond() != UINT_MAX)
            serialString += "." + std::to_string(getSecond() + 1);
        break;
    case INHERITED_CHILDREN_FEATURES_STATEMENT:
        serialString = "↓" + std::to_string(getFirst() + 1);
        if (getSecond() != UINT_MAX)
            serialString += '.' + std::to_string(getSecond() + 1);
        break;
    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
        serialString = "⇓" + std::to_string(getFirst() + 1);
        break;
    case IF_STATEMENT:
        serialString = "I(" + lhs->peekSerialString() + ')' + rhs->peekSerialString();
        break;
    case IF_CON_T_STATEMENT:
        serialString = "T(" + lhs->peekSerialString() + ')';
        if (rhs)
        {
            serialString += "E(" + rhs->peekSerialString() + ')';
        }
        break;
    case WAIT_STATEMENT:
        serialString = "W(" + lhs->peekSerialString() + ')' + rhs->peekSerialString();
        break;
    case FOREACH_STATEMENT:
        serialString = "O(" + lhs->peekSerialString() + ')' + rhs->peekSerialString();
        break;
    case FOREACH_CON_T_STATEMENT:
        serialString = "IN(" + lhs->peekSerialString() + ')';
        if (rhs)
        {
            serialString += "D(" + rhs->peekSerialString() + ')';
        }
        break;
    case STRING_STATEMENT:
        serialString = '"' + getString() + '"';
        break;
    case STMS_STATEMENT:
        serialString = getStatements()->peekSerialString();
        break;
    case NUMBER_STATEMENT:
        serialString = getNumber();
        break;
    case SEARCH_STATEMENT:
        if (getBits())
            serialString = "S(" + getBits()->peekSerialString() + ',' + lhs->peekSerialString() + ')';
        else
            serialString = "S(" + lhs->peekSerialString() + ')';
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::clone(const std::bitset<FLAGS> &protectedFlags)
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
    case CONSTANT_STATEMENT:
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
        statement = Statement::create(this->lineno, this->bufferName, this->op, this->rootOp, getBits());
        break;
    case ATTEST_STATEMENT:
        statement = Statement::create(this->lineno, this->bufferName, this->op, this->rootOp, this->lhs ? lhs->clone(protectedFlags) : statementPtr());
        break;
    case IF_STATEMENT:
    case IF_CON_T_STATEMENT:
    case FOREACH_STATEMENT:
    case FOREACH_CON_T_STATEMENT:
    case WAIT_STATEMENT:
    case UNIF_STATEMENT:
    case AFF_STATEMENT:
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
Statement::evalFeatures(class Item *item, Parser &parser, Synthesizer *synthesizer, bool replaceVariables)
{
#ifdef TRACE_EVAL
    std::cout << "####################### EVAL FEATURES #######################" << std::endl;
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
        featuresPtr fs1 = lhs->evalFeatures(item, parser, synthesizer, replaceVariables);
        featuresPtr fs2 = rhs->evalFeatures(item, parser, synthesizer, replaceVariables);
        if ((!fs1) || (!fs2))
        {
            resultFeatures = featuresPtr();
        }
        else
        {
            fs1->subFlags(Flags::SEEN);
            fs2->subFlags(Flags::SEEN);
            resultFeatures = unif(shared_from_this(), fs1, fs2, item);
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
#ifdef TRACE_EVAL
    std::cout << "####################### EVAL FEATURES DONE #######################" << std::endl;
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
pairpPtr Statement::evalPairp(class Item *item, Parser &parser, Synthesizer *synthesizer, bool replaceVariables)
{
#ifdef TRACE_EVAL
    std::cout << "####################### EVAL PAIRP #######################" << std::endl;
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
        featuresPtr features = lhs->evalFeatures(item, parser, synthesizer, replaceVariables);
        if (!features)
        {
            FATAL_ERROR_UNEXPECTED;
        }
        unsigned int pred = features->assignPred();
        unsigned int pos = this->getFirst();
        auto foundpos = parser.findCacheLexicon(pos);
        if (foundpos != parser.cendCacheLexicon() && (!foundpos->second->empty()))
        {
            Parser::entries_map *listPred = foundpos->second;
            entriesPtr entries = synthesizer->findByPred(parser, listPred, pos, pred);
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
                        parser.parseBuffer("#", stringStream.str(), stringStream.str());
                        if (resultPairp->isNil())
                            resultPairp = Pairp::create(Value::create(parser.getLocalFeatures()));
                        else
                            resultPairp = Pairp::create(Pairp::create(Value::create(parser.getLocalFeatures())), resultPairp);
                    }
                }
            }
            else
            {
                throw fatal_exception("search operator error: No entry for " + Vartable::codeToString(features->assignPred()));
            }
        }
    }
    break;

    default:
        FATAL_ERROR_UNEXPECTED;
        break;
    }
#ifdef TRACE_EVAL
    std::cout << "####################### EVAL PAIRP DONE #######################" << std::endl;
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
valuePtr Statement::evalValue(class Item *item, Parser &parser, Synthesizer *synthesizer, bool replaceVariables)
{
#ifdef TRACE_EVAL
    std::cout << "####################### EVAL VALUE #######################" << std::endl;
    std::cout << "<div>" << std::endl;
    this->print(std::cout, 0);
    item->print(std::cout);
    std::cout << "</div>" << std::endl;
#endif
    valuePtr resultValue = valuePtr();
    featuresPtr resultFeatures = featuresPtr();
    pairpPtr resultPairp = pairpPtr();
    // listFeaturesPtr resultListFeatures = listFeaturesPtr();
    switch (this->op)
    {

    case NIL_STATEMENT:
        resultValue = Value::STATIC_NIL;
        break;

    case DASH_STATEMENT:
    {
        termsPtr t = item->getTerms(getFirst());
        // if (#i) false
        if (t->isOptional())
            resultValue = Value::STATIC_NIL;
        else
        {
            // if (#i)
            if (getSecond() == UINT_MAX)
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
                    resultValue = Value::STATIC_NIL;
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
            resultValue = item->getEnvironment()->find(getBits());
            goto valueBuilt;
        }
        else if (replaceVariables)
        {
            resultValue = valuePtr();
            goto valueBuilt;
        }
        else
        {
            resultValue = Value::create(Value::VARIABLE_VALUE, getBits());
        }
        break;

    case ANONYMOUS_STATEMENT:
        resultValue = Value::STATIC_ANONYMOUS;
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
        featuresPtr fs1 = lhs->evalFeatures(item, parser, synthesizer, replaceVariables);
        if (!fs1)
        {
            resultValue = valuePtr();
            goto valueBuilt;
        }
        else
        {
            featuresPtr fs2 = rhs->evalFeatures(item, parser, synthesizer, replaceVariables);
            if (!fs2)
            {
                resultValue = valuePtr();
                goto valueBuilt;
            }
            else
            {
                fs1->subFlags(Flags::SEEN);
                fs2->subFlags(Flags::SEEN);
                resultFeatures = unif(shared_from_this(), fs1, fs2, item);
            }
        }
    }
    break;

    case SEARCH_STATEMENT:
        resultPairp = evalPairp(item, parser, synthesizer, replaceVariables);
        break;

    case ATTEST_STATEMENT:
        FATAL_ERROR_STM(shared_from_this());
        break;

    case PAIRP_STATEMENT:
        resultPairp = evalPairp(item, parser, synthesizer, replaceVariables);
        break;

    case FUNCTION_STATEMENT:
        switch (getFct())
        {
        case NOP:
            break;

        case PLUS:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            bool isv1astring = false;
            std::string v1str;
            if (v1)
            {
                isv1astring = true;
                if (v1->isVariable())
                    v1str = v1->getBits()->to_string();
                else if (v1->isIdentifier())
                    v1str = Vartable::codeToString(v1->getCode());
                else if (v1->isForm())
                    v1str = v1->getStr();
                else
                    isv1astring = false;
            }
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            bool isv2astring = false;
            std::string v2str;
            if (v2)
            {
                isv2astring = true;
                if (v2->isVariable())
                    v2str = v2->getBits()->to_string();
                else if (v2->isIdentifier())
                    v2str = Vartable::codeToString(v2->getCode());
                else if (v2->isForm())
                    v2str = v2->getStr();
                else
                    isv2astring = false;
            }

            if ((!v1) || (!v2))
                resultValue = valuePtr();

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
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            if ((!v1) || (!v2))
                resultValue = valuePtr();
            else if ((v1->isNumber()) && (v2->isNumber()))
                resultValue = Value::create(Value::NUMBER_VALUE, v1->getNumber() - v2->getNumber());
            else
                resultValue = valuePtr();
            goto valueBuilt;
        }
        break;

        case TIMES:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            if ((!v1) || (!v2))
                resultValue = valuePtr();
            else if ((v1->isNumber()) && (v2->isNumber()))
                resultValue = Value::create(Value::NUMBER_VALUE, v1->getNumber() * v2->getNumber());
            else
                resultValue = valuePtr();
            goto valueBuilt;
        }
        break;

        case DIVIDE:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            if ((!v1) || (!v2))
                resultValue = valuePtr();
            else if ((v1->isNumber()) && (v2->isNumber()))
                resultValue = Value::create(Value::NUMBER_VALUE, v1->getNumber() / v2->getNumber());
            else
                resultValue = valuePtr();
            goto valueBuilt;
        }
        break;

        case MODULO:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            if ((!v1) || (!v2))
                resultValue = valuePtr();
            else if ((v1->isNumber()) && (v2->isNumber()))
                resultValue = Value::create(Value::NUMBER_VALUE, fmod(v1->getNumber(), v2->getNumber()));
            else
                resultValue = valuePtr();
            goto valueBuilt;
        }
        break;

        case MINUS_U:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            if (!v1)
                resultValue = valuePtr();
            else if ((v1->isNumber()))
                resultValue = Value::create(Value::NUMBER_VALUE, -v1->getNumber());
            else
                resultValue = valuePtr();
            goto valueBuilt;
        }
        break;

        case AND:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            if (!v1 || !v2)
            {
                resultValue = valuePtr();
            }
            else if ((v1->isFalse()) || (v2->isFalse()))
                resultValue = Value::STATIC_NIL;
            else
                resultValue = Value::STATIC_TRUE;
            goto valueBuilt;
        }
        break;

        case OR:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            if ((!v1) || (!v2))
                resultValue = valuePtr();
            else if ((v1->isFalse()) && (v2->isFalse()))
                resultValue = Value::STATIC_NIL;
            else
                resultValue = Value::STATIC_TRUE;
            goto valueBuilt;
        }
        break;

        case EQ:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            if ((!v1) && (!v2))
                resultValue = Value::STATIC_TRUE;

            else if ((!v1) || (!v2))
                resultValue = valuePtr();

            else if ((v1->isNil()) && (v2->isNil()))
                resultValue = Value::STATIC_TRUE;

            else if ((v1->isNil()) || (v2->isNil()))
                resultValue = Value::STATIC_NIL;

            else if ((v1->isAnonymous()) && (v2->isAnonymous()))
                resultValue = Value::STATIC_TRUE;

            else if ((v1->isAnonymous()) || (v2->isAnonymous()))
                resultValue = Value::STATIC_NIL;

            else if (v1->eq(v2))
                resultValue = Value::STATIC_TRUE;

            else
                resultValue = Value::STATIC_NIL;

            goto valueBuilt;
        }
        break;

        case DIFF:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            if ((!v1) && (!v2))
                resultValue = Value::STATIC_NIL;

            else if ((!v1) || (!v2))
                resultValue = Value::STATIC_TRUE;

            else if ((v1->isNil()) && (v2->isNil()))
                resultValue = Value::STATIC_NIL;

            else if ((v1->isNil()) || (v2->isNil()))
                resultValue = Value::STATIC_TRUE;

            else if ((v1->isAnonymous()) && (v2->isAnonymous()))
                resultValue = Value::STATIC_NIL;

            else if ((v1->isAnonymous()) || (v2->isAnonymous()))
                resultValue = Value::STATIC_TRUE;

            else if (v1->eq(v2))
                resultValue = Value::STATIC_NIL;

            else
                resultValue = Value::STATIC_TRUE;

            goto valueBuilt;
        }
        break;

        case LT:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            // si l'une est variable libre
            if ((!v1) || (!v2))
            {
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
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            // si l'une est variable libre
            if ((!v1) || (!v2))
            {
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
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            // si l'une est variable libre
            if ((!v1) || (!v2))
            {
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
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
            // si l'une est variable libre
            if ((!v1) || (!v2))
            {
                resultValue = Value::STATIC_NIL;
            }
            else if (!(v1->lt(v2)))
                resultValue = Value::STATIC_TRUE;
            else
                resultValue = Value::STATIC_NIL;
            goto valueBuilt;
        }
        break;

        case NOT:
        {
            valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
            if (!v1 || v1->isNil() || v1->isAnonymous())
                resultValue = Value::STATIC_TRUE;
            else
                resultValue = Value::STATIC_NIL;
            goto valueBuilt;
        }
        break;

        case RAND:
        {
            resultValue = Value::create(Value::NUMBER_VALUE, (double)rand());
            goto valueBuilt;
        }
        break;
        }

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
#ifdef TRACE_EVAL
    std::cout << "####################### EVAL VALUE DONE #######################" << std::endl;
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
featuresPtr Statement::unif(statementPtr self, const featuresPtr &fs1, const featuresPtr &fs2, class Item *item)
{
#ifdef TRACE_EVAL
    std::cout << "####################### EVAL UNIF #######################" << std::endl;
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

        if ((*i1)->isPred() || (*i1)->isLemma())
        {
            Features::list_of_feature::const_iterator i2 = fs2->begin();
            while (i2 != fs2->end())
            {
                if ((*i2)->_getType() == (*i1)->_getType())
                {
                    (*i2)->addFlags(Flags::SEEN);
                    switch ((*i1)->getValue()->_getType())
                    {

                    case Value::IDENTIFIER_VALUE:
                    {
                        switch ((*i2)->getValue()->_getType())
                        {
                        case Value::IDENTIFIER_VALUE:
                            if ((*i1)->getValue()->getCode() != (*i2)->getValue()->getCode())
                            {
                                result = Features::BOTTOM;
                                goto endUnif;
                            }
                            break;

                        case Value::VARIABLE_VALUE:
                            result->add(Feature::create(Feature::_PRED_, bitsetPtr(), (*i1)->getValue()));
                            if (!item->getEnvironment())
                                item->setEnvironment(Environment::create());
                            item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
                            break;

                        default:
                            FATAL_ERROR_STM(self);
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
                                item->getEnvironment()->add((*i1)->getValue()->getBits(), (*i2)->getValue());
                            }
                        }
                        result->add(Feature::create(Feature::_PRED_, bitsetPtr(), (*i2)->getValue()));
                        break;

                    case Value::ANONYMOUS_VALUE:
                        result->add(Feature::create(Feature::_PRED_, bitsetPtr(), (*i2)->getValue()));
                        break;

                    default:
                        FATAL_ERROR_STM(self);
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
                    if (!(*i1)->getValue()->isForm() || !(*i2)->getValue()->isForm())
                        FATAL_ERROR_STM(self);

                    if ((*i1)->getValue()->getStr() != (*i2)->getValue()->getStr())
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

                    switch ((*i1)->getValue()->_getType())
                    {

                    case Value::LIST_FEATURES_VALUE:
                        FATAL_ERROR_UNEXPECTED

                    case Value::NIL_VALUE:
                        FATAL_ERROR_UNEXPECTED

                    case Value::FORM_VALUE:
                        switch ((*i2)->getValue()->_getType())
                        {
                        case Value::FORM_VALUE:
                            if ((*i1)->getValue()->getStr() != (*i2)->getValue()->getStr())
                            {
                                result = Features::BOTTOM;
                                goto endUnif;
                            }
                            result->add(Feature::create(Feature::_CONSTANT_, (*i1)->getAttribute(),
                                                        (*i1)->getValue()));
                            break;

                        case Value::VARIABLE_VALUE:
                            FATAL_ERROR_STM(self);
                            /*
                          result->add(new Feature((*i2)->getAttribute(), (*i1)->getValue(), Feature::CONSTANT));
                          if (item->getEnvironment()==NULL)
                          item->setEnvironment(new Environment());
                          item->getEnvironment()->add(*(*i2)->getValue()->getBits(), (*i1)->getValue());
                            */
                            break;

                        default:
                            FATAL_ERROR_STM(self);
                            break;
                        }
                        break;

                        // case Value::FALSE:
                    case Value::TRUE_VALUE:
                    {
                        switch ((*i2)->getValue()->_getType())
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
                            item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
                            break;
                        default:
                            FATAL_ERROR_STM(self);
                            break;
                        }
                    }
                    break;

                    case Value::NUMBER_VALUE:
                    {
                        switch ((*i2)->getValue()->_getType())
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
                            item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
                            break;
                        default:
                            FATAL_ERROR_STM(self);
                            break;
                        }
                    }
                    break;

                    case Value::IDENTIFIER_VALUE:
                    {
                        switch ((*i2)->getValue()->_getType())
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
                            item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
                            break;
                        default:
                            FATAL_ERROR_STM(self);
                            break;
                        }
                    }
                    break;

                    case Value::CONSTANT_VALUE:
                    {
                        switch ((*i2)->getValue()->_getType())
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
                            item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
                            break;
                        case Value::ANONYMOUS_VALUE:
                            result->add(Feature::create(Feature::_CONSTANT_, (*i2)->getAttribute(),
                                                        (*i1)->getValue()));
                            break;
                        default:
                            FATAL_ERROR_STM(self);
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
                                item->getEnvironment()->add((*i1)->getValue()->getBits(), (*i2)->getValue());
                            }
                        }
                        result->add(Feature::create(Feature::_CONSTANT_, (*i1)->getAttribute(), (*i2)->getValue()));
                        break;

                    case Value::ANONYMOUS_VALUE:
                        result->add(Feature::create(Feature::_CONSTANT_, (*i1)->getAttribute(), (*i2)->getValue()));
                        break;

                    case Value::FEATURES_VALUE:
                    {
                        featuresPtr _features = unif(self, (*i1)->getValue()->getFeatures(),
                                                     (*i2)->getValue()->getFeatures(), item);
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

#ifdef TRACE_EVAL
    std::cout << "####################### EVAL UNIF DONE #######################" << std::endl;
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
 * ↓1 = …
 ************************************************************ */
void Statement::buildInheritedSonFeatures(class Item *item, Parser &parser, Synthesizer *synthesizer)
{
    /***
        std::cerr << "buildInheritedSonFeatures: ";
        print(std::cerr);
        std::cerr << std::endl;
    ***/
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
    featuresPtr _features = rhs->evalFeatures(item, parser, synthesizer, true);
    if (_features->isNil())
        addFlags(Flags::BOTTOM);
    else
        item->getInheritedSonFeatures()->add(lhs->getFirst(), _features);
}

/* ************************************************************
 * ⇑ = …
 ************************************************************ */
void Statement::buildSynthesizedFeatures(class Item *item, Parser &parser, Synthesizer *synthesizer)
{
    if (!item->getSynthesizedFeatures()->isNil())
    {
        std::ostringstream oss;
        oss << "⇑"
            << " defined twice";
        FATAL_ERROR_OS_MSG_STM(oss);
    }
    featuresPtr _features = rhs->evalFeatures(item, parser, synthesizer, true);
    if (_features->isNil())
        addFlags(Flags::BOTTOM);
    else
    {
        item->setSynthesizedFeatures(_features);
    }
}

/* ************************************************************
 * [ … $X … ] ⊂ ⇓1;
 * $X = ⇓1;
 ************************************************************ */
void Statement::buildEnvironmentWithSynthesize(class Item *item, Parser &parser, Synthesizer *synthesizer)
{
    switch (this->op)
    {
    case AFF_STATEMENT:
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
        featuresPtr sonSynth = rhs->evalFeatures(item, parser, synthesizer, true);
        if (sonSynth)
        {
            environment->add(lhs->getBits(), Value::create(sonSynth));
        }
        else
            FATAL_ERROR_STM(shared_from_this());
    }
    break;

    case SUBSUME_STATEMENT:
    {
        // [ … $X … ] ⊂ ⇓1;

        featuresPtr left = lhs->evalFeatures(item, parser, synthesizer, false);
        if (!left)
        {

            WARNING_STM;
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

            featuresPtr sonSynth = rhs->evalFeatures(item, parser, synthesizer, true);

            if (sonSynth)
            {

                if (!left->buildEnvironment(environment, sonSynth, true))
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
void Statement::buildEnvironmentWithInherited(class Item *item, Parser &parser, Synthesizer *synthesizer)
{
    /***
        std::cerr << "<DIV>buildEnvironmentWithInherited ";
        this->print(std::cerr, "", TRUE_ROOT);
        std::cerr << "</DIV>";
    ***/
    switch (this->op)
    {
    case AFF_STATEMENT:
    {
        // $X = ↑;
        featuresPtr right = rhs->evalFeatures(item, parser, synthesizer, true);
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
            environment->add(lhs->getBits(), Value::create(right));
        }
    }
    break;

    case SUBSUME_STATEMENT:
    {
        featuresPtr left = lhs->evalFeatures(item, parser, synthesizer, false);
        if (!left)
        {
            WARNING_STM;
        }
        else
        {
            featuresPtr right = rhs->evalFeatures(item, parser, synthesizer, true);
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
                if (!left->buildEnvironment(environment, right, true /*, true*/))
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
void Statement::buildEnvironmentWithValue(class Item *item, Parser &parser, Synthesizer *synthesizer)
{
    /***
        std::cerr << "<DIV>buildEnvironmentWithValue</DIV>";
        std::cerr << "<DIV>";
        this->print(std::cerr, 0);
        std::cerr << "</DIV>";
    ***/
    switch (this->op)
    {
    case AFF_STATEMENT:
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
            valuePtr right = rhs->evalValue(item, parser, synthesizer, true);
            if (!right)
            {
                this->print(std::cerr, 0);
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
                environment->add(lhs->getBits(), right);
            }
        }

        // 	 < … > = $X;
        // 	 < … > = ( … )
        // 	 < … > = sort $X with a;
        // 	 < … > = reverse $X;
        else if (lhs->isPairp())
        {
            pairpPtr right = rhs->evalPairp(item, parser, synthesizer, true);
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
                pairpPtr left = lhs->evalPairp(item, parser, synthesizer, false);
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
                    if (!left->buildEnvironment(environment, right, true, true))
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
        featuresPtr right = rhs->evalFeatures(item, parser, synthesizer, true);
        if (!right)
        {
            WARNING_STM;
        }
        else
        {
            if (right->isNil())
            {
            } // empty
            featuresPtr left = lhs->evalFeatures(item, parser, synthesizer, false);
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
                if (!left->buildEnvironment(environment, right, true /*, true*/))
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
void Statement::stmAttest(class Item *item, Parser &parser, Synthesizer *synthesizer)
{
    /***
        std::cout << "<DIV>*** attest</DIV>";
        std::cout << "<DIV>";
        this->print(std::cout);
        std::cout << "</DIV>";
    ***/
    switch (this->op)
    {
    case ATTEST_STATEMENT:
    {
        valuePtr res = lhs->evalValue(item, parser, synthesizer, true);
        if ((!res) || (res == Value::STATIC_NIL) || (res == Value::STATIC_ANONYMOUS) ||
            ((res->isFeatures() && (res->getFeatures()->isBottom()))))
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
void Statement::stmGuard(class Item *item /*, Synthesizer *synthesizer*/)
{
    /***
         CERR_LINE;
         std::cerr << "<DIV>guard ";
         item->print(std::cerr);
         print(std::cerr);
         std::cerr << "</DIV>";
    ***/
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

    if (!localFeatures->buildEnvironment(environment, localRhs, false))
    {
        addFlags(Flags::BOTTOM);
    }
    if (item->getEnvironment()->size() == 0)
    {
        item->getEnvironment().reset();
        item->setEnvironment(environmentPtr());
    }
    /***
        std::cerr << "<DIV>guard done";
        item->print(std::cerr);
        std::cerr << "</DIV>";
    ***/
}

/* ************************************************************
 * foreach
 ************************************************************ */
void Statement::stmForeach(class Item *item, Parser &parser, Synthesizer *synthesizer, bool &effect)
{
    /***
    COUT_LINE;
    std::cout << "<DIV>foreach";
    item->print(std::cout);
    print(std::cout);
    std::cout << "</DIV>";
    ***/

    addFlags(Flags::SEEN);
    statementPtr variable = getLhs();
    valuePtr value = getRhs()->getLhs()->evalValue(item, parser, synthesizer, true);
    statementPtr statement = getRhs()->getRhs();
    if (value->isPairp())
    {
        value->getPairp()->apply(item, parser, synthesizer, variable, statement, effect);
    }

    else if (value->isListFeatures())
    {
        FATAL_ERROR_MSG_STM("foreach does'nt apply a list");
        value->getListFeatures()->apply(item, parser, synthesizer, variable, statement, effect);
    }

    else
    {
        FATAL_ERROR_MSG_STM("foreach does'nt apply a list");
    }
    /***
    COUT_LINE;
    std::cout << "<DIV>foreach done, effect:" << effect;
    item->print(std::cout);
    std::cout << "</DIV>";
    ***/
}

/* ************************************************************
 * if
 ************************************************************ */
void Statement::stmIf(class Item *item, Parser &parser, Synthesizer *synthesizer, bool &effect)
{
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
        valuePtr res = getLhs()->evalValue(item, parser, synthesizer, true);
        if (!res || res->isNil() || res->isAnonymous())
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
        leftHandSide->apply(item, parser, synthesizer, effect);
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
            rightHandSide->apply(item, parser, synthesizer, effect);
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
}

/* ************************************************************
 * wait
 ************************************************************ */
void Statement::stmWait(class Item *item, Parser &parser, Synthesizer *synthesizer, bool &effect)
{
    rhs->apply(item, parser, synthesizer, effect);
    if (rhs->isSetFlags(Flags::BOTTOM))
        addFlags(Flags::BOTTOM);
    if (rhs->isSetFlags(Flags::SEEN))
        addFlags(Flags::SEEN);
}

/* ************************************************************
 * print
 ************************************************************ */
void Statement::stmPrint(class Item *item, Parser &parser, Synthesizer *synthesizer)
{
    addFlags(Flags::SEEN);
    for (auto statement = getStatements()->cbegin(); statement != getStatements()->cend(); ++statement)
    {
        if ((*statement)->isString())
        {
            std::cout << (*statement)->getString();
        }
        else
        {
            valuePtr value = (*statement)->evalValue(item, parser, synthesizer, true);
            if (value->isForm())
                std::cout << value->getStr();
            else
                value->flatPrint(std::cout);
        }
    }
}

/* ************************************************************
 * println
 ************************************************************ */
void Statement::stmPrintln(class Item *item, Parser &parser, Synthesizer *synthesizer)
{
    stmPrint(item, parser, synthesizer);
    std::cout << std::endl;
}

/* **************************************************
 *
 ************************************************** */
void Statement::renameVariables(size_t i)
{
    switch (this->op)
    {
    case VARIABLE_STATEMENT:
    {
        std::string _str = getBits()->to_string() + "_" + std::to_string(i);
        bitsetPtr variableBits = Vartable::createVariable(_str);
        bitset = variableBits;
    }
    break;
    case CONSTANT_STATEMENT:
    case ANONYMOUS_STATEMENT:
    case NIL_STATEMENT:
    case STRING_STATEMENT:
    case NUMBER_STATEMENT:
    case INHERITED_FEATURES_STATEMENT:
    case SYNTHESIZED_FEATURES_STATEMENT:
    case DASH_STATEMENT:
    case SYNTHESIZED_CHILDREN_FEATURES_STATEMENT:
    case INHERITED_CHILDREN_FEATURES_STATEMENT:
    case SEARCH_STATEMENT:
        break;
    case AFF_STATEMENT:
    case SUBSUME_STATEMENT:
    case FUNCTION_STATEMENT:
    case UNIF_STATEMENT:
    case ATTEST_STATEMENT:
    case IF_STATEMENT:
    case IF_CON_T_STATEMENT:
    case FOREACH_STATEMENT:
    case FOREACH_CON_T_STATEMENT:
    case WAIT_STATEMENT:
        if (lhs)
            lhs->renameVariables(i);
        if (rhs)
            rhs->renameVariables(i);
        break;
    case FEATURES_STATEMENT:
    case GUARD_STATEMENT:
        getFeatures()->renameVariables(i);
        break;
    case PAIRP_STATEMENT:
        getPairp()->renameVariables(i);
        break;
    case STMS_STATEMENT:
    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:
        getStatements()->renameVariables(i);
        break;
    }
}

/* ************************************************************
 *
 ************************************************************ */
void Statement::toggleEnable(const statementPtr &root, class Item *item, Synthesizer *synthesizer, bool &result, bool on)
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
            if (item->getIndexTerms()[getFirst()] == UINT_MAX)
            //|| ((getSecond() != UINT_MAX) && (item->getIndexTerms()[getFirst()] != getSecond())))
            {
                root->addFlags(Flags::DISABLED);
                result = true;
            }
        }
        else
        {
            root->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case VARIABLE_STATEMENT:
        if (on)
        {
            if (!item->getEnvironment() || !item->getEnvironment()->find(getBits()))
            {
                root->addFlags(Flags::DISABLED);
                result = true;
            }
        }
        else
        {
            root->subFlags(Flags::DISABLED);
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
                root->addFlags(Flags::DISABLED);
                result = true;
            }
        }
        else
        {
            root->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case INHERITED_FEATURES_STATEMENT:
        if (on)
        {
            if (item->getInheritedFeatures()->isNil())
            {
                root->addFlags(Flags::DISABLED);
                result = true;
            }
        }
        else
        {
            root->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case SYNTHESIZED_FEATURES_STATEMENT:
        if (on)
        {
            if (item->getSynthesizedFeatures()->isNil())
            {
                root->addFlags(Flags::DISABLED);
                result = true;
            }
        }
        else
        {
            root->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case STMS_STATEMENT:
        getStatements()->toggleEnable(item, synthesizer, result, on);
        break;

    case PRINT_STATEMENT:
    case PRINTLN_STATEMENT:

        if (on)
        {
            for (auto i = getStatements()->cbegin(); i != getStatements()->cend(); ++i)
            {
                bool effect = false;
                (*i)->toggleEnable(*i, item, synthesizer, effect, on);
                if (effect && (*i)->isSetFlags(Flags::DISABLED))
                {
                    root->addFlags(Flags::DISABLED);
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
            root->subFlags(Flags::DISABLED);
            result = true;
        }
        break;

    case IF_STATEMENT:
        if (lhs->containsDash())
        {
            lhs->toggleEnable(root, item, synthesizer, result, on);
        }
        if (root->isUnsetFlags(Flags::DISABLED))
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
        lhs->toggleEnable(root, item, synthesizer, result, on);
        rhs->toggleEnable(rhs, item, synthesizer, result, on);
        break;

    case WAIT_STATEMENT:
        lhs->toggleEnable(shared_from_this(), item, synthesizer, result, on);
        rhs->toggleEnable(shared_from_this(), item, synthesizer, result, on);
        break;

    case AFF_STATEMENT:
    case SUBSUME_STATEMENT:
        rhs->toggleEnable(shared_from_this(), item, synthesizer, result, on);
        break;

    case FUNCTION_STATEMENT:
    case UNIF_STATEMENT:
        if (lhs)
            lhs->toggleEnable(root, item, synthesizer, result, on);
        if (rhs)
            rhs->toggleEnable(root, item, synthesizer, result, on);
        break;

    case ATTEST_STATEMENT:
        lhs->toggleEnable(root, item, synthesizer, result, on);
        break;

    case PAIRP_STATEMENT:
        getPairp()->enable(root, item, synthesizer, result, on);
        break;

    case FEATURES_STATEMENT:
        getFeatures()->enable(root, item, synthesizer, result, on);
        break;

    case SEARCH_STATEMENT:
        if (lhs)
            lhs->toggleEnable(root, item, synthesizer, result, on);
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
void Statement::apply(class Item *item, Parser &parser, Synthesizer *synthesizer, bool &effect)
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
        // FATAL_ERROR_UNEXPECTED
    }

    // […]
    if (isGuard())
    {
        stmGuard(item);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // if
    else if (isIf())
    {
        stmIf(item, parser, synthesizer, effect);
    }

    // foreach $i in $list
    else if (isForeach())
    {
        stmForeach(item, parser, synthesizer, effect);
    }

    // wait
    else if (isWait())
    {
        stmWait(item, parser, synthesizer, effect);
    }

    // ↓1 = …
    else if ((isAff()) && (getLhs()->isDown()))
    {
        buildInheritedSonFeatures(item, parser, synthesizer);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // [ … $X … ] ⊂ ⇓1
    // $X = ⇓1
    else if (((isSubsume()) && (getRhs()->isDown2()) && (getLhs()->isFeatures())) ||
             ((isAff()) && (getRhs()->isDown2()) && (getLhs()->isVariable())))
    {
        buildEnvironmentWithSynthesize(item, parser, synthesizer);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // [ … $X … ] ⊂ ↑
    // $X = ↑
    else if (((isSubsume()) && (getRhs()->isUp()) && (getLhs()->isFeatures())) ||
             ((isAff()) && (getRhs()->isUp()) && (getLhs()->isVariable())))
    {
        buildEnvironmentWithInherited(item, parser, synthesizer);
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
    else if (((isAff()) && (getLhs()->isVariable()) && ((getRhs()->isConstant()) || (getRhs()->isVariable()) || (getRhs()->isUnif()) || (getRhs()->isFeatures()) || (getRhs()->isNumber()) || (getRhs()->isString()) || (getRhs()->isFct()) || (getRhs()->isPairp()) || (getRhs()->isSearch())))

             || ((isAff()) && (getLhs()->isPairp()) && ((getRhs()->isVariable()) || (getRhs()->isPairp()) || (getRhs()->isSearch())))

             || ((isSubsume()) && (getLhs()->isFeatures()) && ((getRhs()->isVariable()) || (getRhs()->isFeatures()))))
    {
        buildEnvironmentWithValue(item, parser, synthesizer);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // ⇑ = …
    else if ((isAff()) && (getLhs()->isUp2()))
    {
        buildSynthesizedFeatures(item, parser, synthesizer);
        effect = true;
        addFlags(Flags::SEEN);
    }

    // attest …
    else if (isAttest())
    {
        stmAttest(item, parser, synthesizer);
        addFlags(Flags::SEEN);
    }

    // print
    else if (isPrint())
    {
        stmPrint(item, parser, synthesizer);
        addFlags(Flags::SEEN);
    }

    // println
    else if (isPrintln())
    {
        stmPrintln(item, parser, synthesizer);
        addFlags(Flags::SEEN);
    }

    // statements
    else if (isStms())
    {
        statements->apply(item, parser, synthesizer, effect);
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
    case AFF_STATEMENT:
        // ↓1 = …
        if ((this->isAff()) && (this->getLhs()->isDown()))
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

    case AFF_STATEMENT:
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
