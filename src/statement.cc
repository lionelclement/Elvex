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
#include "list.hpp"
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
Statement::Statement(unsigned int lineno, type op, std::string str) {
    NEW
    this->lineno = lineno;
    this->op = op;
    this->lhs = statementPtr();
    this->rhs = statementPtr();
    this->pair.first = 0;
    this->pair.second = 0;
    this->features = featuresPtr();
    this->bitset = bitsetPtr();
    this->str = std::move(str);
    this->fct = NOP;
    this->list = listPtr();
    this->statements = statementsPtr();
    this->number = 0;
}

/* **************************************************
 *
 ************************************************** */
Statement::Statement(unsigned int lineno, type op, statementPtr lhs, statementPtr rhs, unsigned int first,
                     unsigned int second, featuresPtr features, bitsetPtr bits,
                     arithmetic_op fct, listPtr list, statementsPtr statements, double number) {
    NEW
    this->lineno = lineno;
    this->op = op;
    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);
    this->pair.first = first;
    this->pair.second = second;
    this->features = std::move(features);
    this->bitset = std::move(bits);
    this->str = std::string();
    this->fct = fct;
    this->list = std::move(list);
    this->statements = std::move(statements);
    this->number = number;
}

/* **************************************************
 *
 ************************************************** */
Statement::Statement(unsigned int lineno, type op, valuePtr value) {
    NEW
    this->lineno = lineno;
    this->op = op;
    this->lhs = statementPtr();
    this->rhs = statementPtr();
    this->value = value;
}

/* **************************************************
 *
 ************************************************** */
Statement::~Statement() {
    DELETE
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, statementPtr lhs, statementPtr rhs) {
    return statementPtr(new Statement(lineno, op, std::move(lhs), std::move(rhs)));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, unsigned int first, unsigned int second) {
    return statementPtr(new Statement(lineno, op, statementPtr(), statementPtr(), first, second));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, featuresPtr features) {
    return statementPtr(new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX,
                                      UINT_MAX, std::move(features)));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, valuePtr &value) {
    return statementPtr(new Statement(lineno, op, value));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, bitsetPtr bits, statementPtr lhs) {
    return statementPtr(new Statement(lineno, op, std::move(lhs), statementPtr(), UINT_MAX,
                                      UINT_MAX, featuresPtr(), std::move(bits)));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, std::string str) {
    return statementPtr(new Statement(lineno, op, std::move(str)));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, arithmetic_op fct, statementPtr lhs, statementPtr rhs) {
    return statementPtr(
            new Statement(lineno, op, std::move(lhs), std::move(rhs), UINT_MAX, UINT_MAX, featuresPtr(), bitsetPtr(),
                          fct));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, listPtr list) {
    return statementPtr(new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX,
                                      UINT_MAX, featuresPtr(), bitsetPtr(), Statement::NOP, std::move(list)));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, statementsPtr statements) {
    return statementPtr(new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX,
                                      UINT_MAX, featuresPtr(), bitsetPtr(), Statement::NOP, listPtr(),
                                      std::move(statements)));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, double number) {
    return statementPtr(new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX,
                                      UINT_MAX, featuresPtr(), bitsetPtr(), Statement::NOP, listPtr(), statementsPtr(),
                                      number));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create() {
    return statementPtr(new Statement(0, DASH, statementPtr(), statementPtr(), UINT_MAX,
                                      UINT_MAX, featuresPtr(), bitsetPtr(), Statement::NOP, listPtr(),
                                      statementsPtr()));
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isAff() const {
    return op == AFF;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isSubsume() const {
    return op == SUBSUME;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isUp() const {
    return op == UP;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isUp2() const {
    return op == UP2;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isDown() const {
    return op == DOWN;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isSearch() const {
    return op == SEARCH;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isDown2() const {
    return op == DOWN2;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isFeatures() const {
    return op == FEATURES;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isVariable() const {
    return op == VARIABLE;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isConstant() const {
    return op == CONSTANT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isUnif() const {
    return op == UNIF;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isGuard() const {
    return op == GUARD;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isPrint() const {
    return op == PRINT;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isPrintln() const {
    return op == PRINTLN;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isAttest() const {
    return op == ATTEST;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isIf() const {
    return op == IF;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isForeach() const {
    return op == FOREACH;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isStms() const {
    return op == STMS;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isStr() const {
    return op == STR;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isList() const {
    return op == LIST;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isNumber() const {
    return op == NUMBER;
}

/* **************************************************
 *
 ************************************************** */
bool Statement::isFct() const {
    return op == FCT;
}

/* **************************************************
 *
 ************************************************** */
Statement::arithmetic_op Statement::getFct() const {
    return fct;
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::getLhs() const {
    return lhs;
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::getRhs() const {
    return rhs;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Statement::getFeatures() const {
    return features;
}

/* **************************************************
 *
 ************************************************** */
bitsetPtr Statement::getBits() const {
    return bitset;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Statement::getFirst() const {
    return pair.first;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Statement::getSecond() const {
    return pair.second;
}

/* **************************************************
 *
 ************************************************** */
std::string Statement::getStr() const {
    return str;
}

/* **************************************************
 *
 ************************************************** */
listPtr Statement::getList() const {
    return list;
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Statement::getStatements() const {
    return statements;
}

/* **************************************************
 *
 ************************************************** */
double Statement::getNumber() const {
    return number;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Statement::getLineno() const {
    return lineno;
}

/* **************************************************
 *
 ************************************************** */
void Statement::print(std::ostream &outStream, unsigned int tabulation, int yetColored) const {
    switch (this->op) {
        case ATTEST:
        case AFF:
        case SUBSUME:
        case PRINT:
        case PRINTLN:
        case GUARD:
        case IF:
        case THENELSE:
        case FOREACH:
            for (unsigned int j = 1; j <= tabulation; j++)
                outStream << "&nbsp;";
            break;
        default:
            break;
    }
    int color = yetColored;
    if (isSetFlags(Flags::SEEN)) {
        color |= 0x0000FF;
    }
    if (isSetFlags(Flags::DISABLED)) {
        color |= 0xC0C0C0;
    }
    if (isSetFlags(Flags::BOTTOM)) {
        color |= 0xFF0000;
    }
    if (color != 0)
        outStream << "<SPAN style=\"color:#" << std::setfill('0') << std::setw(6) << std::hex << color << ";\">";
    if (isSetFlags(Flags::REJECTED)) {
        outStream << "<S>";
    }
    switch (this->op) {
        case ATTEST:
            outStream << "attest&nbsp;";
            lhs->print(outStream);
            break;
        case NIL:
            outStream << "NIL";
            break;
        case NOT_NIL:
            outStream << "NOT_NIL";
            break;
        case FINISHED:
            outStream << "finished";
            break;
        case AFF:
            lhs->print(outStream);
            outStream << "&nbsp;=&nbsp;";
            rhs->print(outStream);
            break;
        case SUBSUME:
            lhs->print(outStream);
            outStream << "&nbsp;⊂&nbsp;";
            rhs->print(outStream);
            break;
        case INSET:
            lhs->print(outStream);
            outStream << "&nbsp;∈&nbsp;";
            rhs->print(outStream);
            break;
        case FCT:
            switch (this->getFct()) {
                case NOP:
                    outStream << ";";
                    break;
                case NOT:
                    outStream << "¬";
                    outStream << "&nbsp;(";
                    lhs->print(outStream);
                    outStream << ")&nbsp;";
                    break;
                case AND:
                    outStream << "&nbsp;(";
                    lhs->print(outStream);
                    outStream << "&nbsp;∧&nbsp;";
                    rhs->print(outStream);
                    outStream << ")&nbsp;";
                    break;
                case OR:
                    outStream << "&nbsp;(";
                    lhs->print(outStream);
                    outStream << "&nbsp;∨&nbsp;";
                    rhs->print(outStream);
                    outStream << ")&nbsp;";
                    break;
                case EQ:
                    outStream << "&nbsp;(";
                    lhs->print(outStream);
                    outStream << "&nbsp;==&nbsp;";
                    rhs->print(outStream);
                    outStream << ")&nbsp;";
                    break;
                case DIFF:
                    outStream << "&nbsp;(";
                    lhs->print(outStream);
                    outStream << "&nbsp;≠&nbsp;";
                    rhs->print(outStream);
                    outStream << ")&nbsp;";
                    break;
                case PLUS:
                    outStream << '(';
                    lhs->print(outStream);
                    outStream << "&nbsp;+&nbsp;";
                    rhs->print(outStream);
                    outStream << ')';
                    break;
                case MINUS:
                    outStream << '(';
                    lhs->print(outStream);
                    outStream << "&nbsp;-&nbsp;";
                    rhs->print(outStream);
                    outStream << ')';
                    break;
                case TIMES:
                    outStream << '(';
                    lhs->print(outStream);
                    outStream << "&nbsp;*&nbsp;";
                    rhs->print(outStream);
                    outStream << ')';
                    break;
                case DIVIDE:
                    outStream << '(';
                    lhs->print(outStream);
                    outStream << "&nbsp;/&nbsp;";
                    rhs->print(outStream);
                    outStream << ')';
                    break;
                case MODULO:
                    outStream << '(';
                    lhs->print(outStream);
                    outStream << "&nbsp;%&nbsp;";
                    rhs->print(outStream);
                    outStream << ')';
                    break;
                case LT:
                    outStream << '(';
                    lhs->print(outStream);
                    outStream << "&nbsp;<&nbsp;";
                    rhs->print(outStream);
                    outStream << ')';
                    break;
                case LE:
                    outStream << '(';
                    lhs->print(outStream);
                    outStream << "&nbsp;≤&nbsp;";
                    rhs->print(outStream);
                    outStream << ')';
                    break;
                case GT:
                    outStream << '(';
                    lhs->print(outStream);
                    outStream << "&nbsp;>&nbsp;";
                    rhs->print(outStream);
                    outStream << ')';
                    break;
                case GE:
                    outStream << '(';
                    lhs->print(outStream);
                    outStream << "&nbsp;≥&nbsp;";
                    rhs->print(outStream);
                    outStream << ')';
                    break;
                case MINUS_U:
                    outStream << "-&nbsp;";
                    lhs->print(outStream);
                    break;
                case RAND:
                    outStream << "rand()";
                    break;
            }
            break;
        case CONSTANT:
        case VARIABLE:
            outStream << getBits()->toString();
            break;
        case ANONYMOUS:
            outStream << '_';
            break;
        case PRINT:
            outStream << "print&nbsp;";
            lhs->print(outStream);
            break;
        case PRINTLN:
            outStream << "println&nbsp;";
            lhs->print(outStream);
            break;
        case FEATURES:
            getFeatures()->flatPrint(outStream);
            break;
        case LIST:
            getList()->flatPrint(outStream, true);
            break;
        case GUARD:
            getFeatures()->flatPrint(outStream);
            break;
        case UNIF:
            outStream << "&nbsp;(";
            lhs->print(outStream);
            outStream << "&nbsp;∪&nbsp;";
            rhs->print(outStream);
            outStream << ")&nbsp;";
            break;
        case UP:
            outStream << "↑";
            break;
        case UP2:
            outStream << "⇑";
            break;
        case DASH:
            outStream << '#' << getFirst() + 1;
            if (getSecond() != UINT_MAX) {
                outStream << "." << getSecond() + 1;
            }
            break;
        case DOWN:
            outStream << "↓" << getFirst() + 1;
            if (getSecond() != UINT_MAX) {
                outStream << "." << getSecond() + 1;
            }
            break;
        case DOWN2:
            outStream << "⇓";
            outStream << getFirst() + 1;
            break;
        case IF:
            outStream << "if&nbsp;(";
            lhs->print(outStream);
            outStream << ')';
            rhs->print(outStream, tabulation);
            break;
        case THENELSE:
            outStream << "<DIV";
            if (color != 0)
                outStream << " style=\"color:" << std::hex << color << "\"";
            outStream << ">";
            lhs->print(outStream, tabulation + 3);
            outStream << "</DIV>";
            if (rhs) {
                for (unsigned int j = 1; j <= tabulation; j++)
                    outStream << "&nbsp;";
                outStream << "else ";
                outStream << "<DIV>";
                rhs->print(outStream, tabulation + 3);
                outStream << "</DIV>";
            }
            break;
        case FOREACH:
            outStream << "foreach&nbsp;";
            lhs->print(outStream);
            outStream << "&nbsp;";
            rhs->print(outStream);
            break;
        case IN:
            outStream << "in&nbsp;";
            lhs->print(outStream);
            rhs->print(outStream, tabulation + 3);
            break;
        case STR:
            outStream << "&quot;" << getStr() << "&quot;";
            break;
        case STMS:
            getStatements()->print(outStream, tabulation);
            break;
        case NUMBER:
            outStream << getNumber();
            break;
        case SEARCH:
            outStream << "search&nbsp;(";
            outStream << getBits()->toString();
            outStream << ',';
            lhs->print(outStream);
            outStream << ')';
            break;
    }
    switch (this->op) {
        case ATTEST:
        case AFF:
        case SUBSUME:
        case PRINT:
        case PRINTLN:
        case GUARD:
            outStream << ";<BR>";
            break;
        default:
            break;
    }
    if (isSetFlags(Flags::REJECTED)) {
        outStream << "</S>";
    }
    if (color != 0)
        outStream << "</SPAN>";
}

/* **************************************************
 *
 ************************************************** */
void Statement::makeSerialString() {
    serialString = std::string();
    switch (this->op) {
        case ATTEST:
            serialString = 'A' + lhs->peekSerialString();
            break;
        case NIL:
            serialString = 'N';
            break;
        case NOT_NIL:
            serialString = '~';
            break;
        case FINISHED:
            serialString = 'F';
            break;
        case AFF:
            serialString = lhs->peekSerialString() + '=' + rhs->peekSerialString();
            break;
        case SUBSUME:
            serialString = lhs->peekSerialString() + "⊂" + rhs->peekSerialString();
            break;
        case INSET:
            serialString = lhs->peekSerialString() + "∈" + rhs->peekSerialString();
            break;
        case FCT:
            switch (this->getFct()) {
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
        case CONSTANT:
        case VARIABLE:
            serialString = getBits()->peekSerialString();
            break;
        case ANONYMOUS:
            serialString = '_';
            break;
        case PRINT:
            serialString = "P " + lhs->peekSerialString();
            break;
        case PRINTLN:
            serialString = "PL " + lhs->peekSerialString();
            break;
        case FEATURES:
            serialString = getFeatures()->peekSerialString();
            break;
        case LIST:
            serialString = getList()->peekSerialString();
            break;
        case GUARD:
            serialString = "G " + getFeatures()->peekSerialString();
            break;
        case UNIF:
            serialString = '(' + lhs->peekSerialString() + "∪" + rhs->peekSerialString() + ')';
            break;
        case UP:
            serialString = "↑";
            break;
        case UP2:
            serialString = "⇑";
            break;
        case DASH:
            serialString = '#' + std::to_string(getFirst() + 1);
            if (getSecond() != UINT_MAX)
                serialString += "." + std::to_string(getSecond() + 1);
            break;
        case DOWN:
            serialString = "↓" + std::to_string(getFirst() + 1);
            if (getSecond() != UINT_MAX)
                serialString += '.' + std::to_string(getSecond() + 1);
            break;
        case DOWN2:
            serialString = "⇓" + std::to_string(getFirst() + 1);
            break;
        case IF:
            serialString = "I(" + lhs->peekSerialString() + ')' + rhs->peekSerialString();
            break;
        case THENELSE:
            serialString = "T(" + lhs->peekSerialString() + ')';
            if (rhs) {
                serialString += "E(" + rhs->peekSerialString() + ')';
            }
            break;
        case FOREACH:
            serialString = "O(" + lhs->peekSerialString() + ')' + rhs->peekSerialString();
            break;
        case IN:
            serialString = "IN(" + lhs->peekSerialString() + ')';
            if (rhs) {
                serialString += "D(" + rhs->peekSerialString() + ')';
            }
            break;
        case STR:
            serialString = '"' + getStr() + '"';
            break;
        case STMS:
            serialString = getStatements()->peekSerialString();
            break;
        case NUMBER:
            serialString = getNumber();
            break;
        case SEARCH:
            serialString = "S(" + getBits()->peekSerialString() + ',' + lhs->peekSerialString() + ')';
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::clone(const std::bitset<Flags::FLAGS> &protectedFlags) {
    statementPtr statement = shared_from_this();
    switch (this->op) {
        case UP:
        case UP2:
        case NIL:
        case NOT_NIL:
        case DASH:
        case DOWN:
        case DOWN2:
        case CONSTANT:
        case STR:
        case NUMBER:
        case FINISHED:
        case ANONYMOUS:
            statement = shared_from_this();
            break;
        case FEATURES:
        case GUARD:
            statement = Statement::create(this->lineno, this->op, getFeatures()->clone());
            break;
        case LIST:
            statement = Statement::create(this->lineno, this->op, getList()->clone());
            break;
        case VARIABLE:
            statement = Statement::create(this->lineno, this->op, getBits());
            break;
        case ATTEST:
        case PRINT:
        case PRINTLN:
            statement = Statement::create(this->lineno, this->op, lhs ? lhs->clone(protectedFlags) : statementPtr());
            break;
        case IF:
        case THENELSE:
        case FOREACH:
        case IN:
        case UNIF:
        case AFF:
        case SUBSUME:
        case INSET:
            statement = Statement::create(this->lineno, this->op, lhs ? lhs->clone(protectedFlags) : statementPtr(),
                                          rhs ? rhs->clone(protectedFlags) : statementPtr());
            break;
        case FCT:
            statement = Statement::create(this->lineno, this->op, this->getFct(),
                                          lhs ? lhs->clone(protectedFlags) : statementPtr(),
                                          rhs ? rhs->clone(protectedFlags) : statementPtr());
            break;
        case STMS:
            statement = Statement::create(this->lineno, this->op, getStatements()->clone(protectedFlags));
            break;
        case SEARCH:
            statement = Statement::create(this->lineno, this->op, getBits(),
                                          lhs ? lhs->clone(protectedFlags) : statementPtr());
            break;
    }
    statement->addFlags(protectedFlags & this->getFlags());
    return statement;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Statement::evalFeatures(itemPtr item, Parser &parser, Synthesizer *synthesizer, bool replaceVariables) {
#ifdef TRACE_EVAL
    std::cout << "####################### EVAL FEATURES #######################" << std::endl;
    std::cout << "<div>evalFeatures: " << std::endl;
    this->print(std::cout);
    std::cout << std::endl;
    item->print(std::cout);
    std::cout << "</div>" << std::endl;
#endif

    featuresPtr resultFeatures = Features::NIL;
    switch (this->op) {
        case STR:
        case DASH:
        case PRINT:
        case PRINTLN:
        case ATTEST:
        case CONSTANT:
        case NIL:
        case NOT_NIL:
        case IF:
        case THENELSE:
        case FOREACH:
        case IN:
        case AFF:
        case SUBSUME:
        case INSET:
        case UP2:
        case LIST:
        case STMS:
        case NUMBER:
        case FCT:
        case FINISHED:
        case ANONYMOUS: {
            std::cerr << this->op << std::endl;
            FATAL_ERROR_STM
        }
            break;
        case FEATURES:
        case GUARD: {
            resultFeatures = getFeatures()->clone();
            if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
                bool effect = false;
                item->getEnvironment()->replaceVariables(resultFeatures, effect);
            }
        }
            break;

        case UP: {
            resultFeatures = item->getInheritedFeatures()->clone();
            if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
                bool effect = false;
                item->getEnvironment()->replaceVariables(resultFeatures, effect);
            }
        }
            break;

        case VARIABLE: {
            if (item->getEnvironment()) {
                valuePtr _value = item->getEnvironment()->find(getBits());
                if (!_value) {
                    FATAL_ERROR_STM
                }
                if (_value && _value->getType() == Value::FEATURES)
                    resultFeatures = _value->getFeatures()->clone();
            }
        }
            break;

        case DOWN: {
            resultFeatures = (*item->getInheritedSonFeatures())[getFirst()]->clone();
            if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
                bool effect = false;
                item->getEnvironment()->replaceVariables(resultFeatures, effect);
            }
        }
            break;

        case DOWN2: {
            resultFeatures = (*item->getSynthesizedSonFeatures())[getFirst()]->clone();
            if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
                bool effect = false;
                item->getEnvironment()->replaceVariables(resultFeatures, effect);
            }
        }
            break;

        case UNIF: {
            featuresPtr fs1 = lhs->evalFeatures(item, parser, synthesizer, replaceVariables);
            featuresPtr fs2 = rhs->evalFeatures(item, parser, synthesizer, replaceVariables);
            if ((!fs1) || (!fs2)) {
                resultFeatures = featuresPtr();
            } else {
                fs1->subFlags(Flags::SEEN);
                fs2->subFlags(Flags::SEEN);
                resultFeatures = unif(fs1, fs2, item);
                if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
                    bool effect = false;
                    item->getEnvironment()->replaceVariables(resultFeatures, effect);
                }
            }
        }
            break;
        case SEARCH: {
            featuresPtr fs = lhs->evalFeatures(item, parser, synthesizer, replaceVariables);
            if (!fs) {
                resultFeatures = featuresPtr();
            }
            if (!synthesizer->getCompactedLexicon()) FATAL_ERROR("search operator error: No compact lexicon defined.")
            entriesPtr entries = synthesizer->findCompactedLexicon(parser, 0, getBits()->toString(), fs->assignPred());
            if (entries) {
                //if (entries->size() > 1) {
                // ERROR("pred ambiguous")
                //}
                // On ne cherche que la première entrée
                auto it = entries->begin();
                featuresPtr _fs = (*it)->getFeatures();
                if (_fs) {
                    std::stringstream stringStream;
                    _fs->flatPrint(stringStream);
                    if (parser.parseBuffer("#", stringStream.str(), stringStream.str())) FATAL_ERROR_UNEXPECTED
                    else {
                        resultFeatures = parser.getLocalFeatures();
                    }
                }
            } else FATAL_ERROR("search operator error: No entry for " + Vartable::codeToIdentifier(fs->assignPred()))

        }
            break;

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
listPtr Statement::evalList(itemPtr item, bool replaceVariables) {
#ifdef TRACE_EVAL
    std::cout << "####################### EVAL LIST #######################" << std::endl;
    std::cout << "<div>" << std::endl;
    this->print(std::cout);
    std::cout << "</div>" << std::endl;
#endif
    listPtr resultList = List::NIL_LIST;
    switch (this->op) {
        case STR:
        case DASH:
        case PRINT:
        case PRINTLN:
        case ATTEST:
        case CONSTANT:
        case NIL:
        case NOT_NIL:
        case IF:
        case THENELSE:
        case FOREACH:
        case IN:
        case AFF:
        case SUBSUME:
        case INSET:
        case DOWN:
        case UP2:
        case FEATURES:
        case GUARD:
        case UP:
        case DOWN2:
        case UNIF:
        case STMS:
        case NUMBER:
        case FCT:
        case FINISHED:
        case SEARCH:
        case ANONYMOUS: FATAL_ERROR_STM
            break;
        case LIST:
            resultList = getList()->clone();
            if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
                bool effect = false;
                item->getEnvironment()->replaceVariables(resultList, effect);
            }
            break;
        case VARIABLE:
            if (item->getEnvironment()) {
                valuePtr _value = item->getEnvironment()->find(getBits());
                if (!_value) {
                    FATAL_ERROR_STM
                    resultList = listPtr();
                } else if (_value->isNil())
                    resultList = List::NIL_LIST;
                else if (_value->isList())
                    resultList = _value->getList()->clone();
                else {
                    std::ostringstream oss1, oss2;
                    this->print(oss1);
                    item->getRule()->print(oss2, -1, true);
                    WARNING_STM
                    "<P>Variable " + oss1.str() + " not initialized in</P>" + oss2.str();
                }
            }
            break;
    }
#ifdef TRACE_EVAL
    std::cout << "####################### EVAL LIST DONE #######################" << std::endl;
    std::cout << "<div>" << std::endl;
    this->print(std::cout);
    std::cout << std::endl;
    if (resultList)
      resultList->print(std::cout);
    else
      std::cout << "NULL";
    std::cout << "</div>" << std::endl;
#endif
    return resultList;
}

/* **************************************************
 *
 ************************************************** */
valuePtr Statement::evalValue(itemPtr item, Parser &parser, Synthesizer *synthesizer, bool replaceVariables) {
#ifdef TRACE_EVAL
    std::cout << "####################### EVAL VALUE #######################" << std::endl;
    std::cout << "<div>Value: " << std::endl;
    this->print(std::cout, 0);
    item->print(std::cout);
    std::cout << "</div>" << std::endl;
#endif
    valuePtr resultValue = valuePtr();
    featuresPtr resultFeatures = featuresPtr();
    listPtr resultList = listPtr();
    switch (this->op) {
        case NIL:
            resultValue = Value::NIL_VALUE;
            break;
        case NOT_NIL:
            resultValue = Value::TRUE_VALUE;
            break;
        case FINISHED:
            if (item->isCompleted())
                resultValue = Value::TRUE_VALUE;
            else
                resultValue = Value::NIL_VALUE;
            break;

        case PRINT:
        case PRINTLN:
        case IF:
        case THENELSE:
        case FOREACH:
        case IN:
        case AFF:
        case SUBSUME:
        case INSET:
        case GUARD:
        case STMS: FATAL_ERROR_STM
            break;

        case DASH: {
            termsPtr t = item->getTerms(getFirst());
            // if (#i) false
            if (t->isOptional())
                resultValue = Value::NIL_VALUE;
            else {
                // if (#i)
                if (getSecond() == UINT_MAX) {
                    resultValue = Value::TRUE_VALUE;
                }
                    //if (#i:j)
                else {
                    if (getSecond() == item->getIndexTerms()[getFirst()]) {
                        resultValue = Value::TRUE_VALUE;
                    } else {
                        resultValue = Value::NIL_VALUE;
                    }
                }
            }
            goto valueBuilt;
        }
            break;

        case NUMBER:
            resultValue = Value::create(Value::NUMBER, getNumber());
            goto valueBuilt;
            break;

        case STR:
            resultValue = Value::create(Value::STR, getStr());
            goto valueBuilt;
            break;

        case FEATURES:
            resultFeatures = getFeatures();
            break;

        case UP:
            resultFeatures = item->getInheritedFeatures();
            break;

        case UP2:
            resultFeatures = item->getSynthesizedFeatures();
            break;

        case VARIABLE:
            if (replaceVariables && item->getEnvironment()) {
                valuePtr _value = item->getEnvironment()->find(getBits());
                resultValue = _value;
                goto valueBuilt;
            } else if (replaceVariables) {
                resultValue = valuePtr();
                goto valueBuilt;
            } else {
                resultValue = Value::create(Value::VARIABLE, getBits());
            }
            break;

        case ANONYMOUS:
            resultValue = Value::ANONYMOUS_VALUE;
            break;

        case CONSTANT:
            resultValue = Value::create(Value::CONSTANT, getBits());
            break;

        case DOWN2:
            resultFeatures = (*item->getSynthesizedSonFeatures())[getFirst()];
            break;

        case DOWN:
            resultFeatures = (*item->getInheritedSonFeatures())[getFirst()];
            break;

        case UNIF: {
            featuresPtr fs1 = lhs->evalFeatures(item, parser, synthesizer, replaceVariables);
            if (!fs1) {
                resultValue = valuePtr();
                goto valueBuilt;
            } else {
                featuresPtr fs2 = rhs->evalFeatures(item, parser, synthesizer, replaceVariables);
                if (!fs2) {
                    resultValue = valuePtr();
                    goto valueBuilt;

                } else {
                    fs1->subFlags(Flags::SEEN);
                    fs2->subFlags(Flags::SEEN);
                    resultFeatures = unif(fs1, fs2, item);
                }
            }
        }
            break;

        case SEARCH:
        case ATTEST: FATAL_ERROR_STM
            goto valueBuilt;
            break;

        case LIST:
            resultList = evalList(item, replaceVariables);
            break;

        case FCT:
            switch (getFct()) {
                case NOP:
                    break;
                case PLUS: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    bool isv1astring = false;
                    std::string v1str;
                    if (v1) {
                        isv1astring = true;
                        if (v1->isVariable())
                            v1str = v1->getBits()->toString();
                        else if (v1->isIdentifier())
                            v1str = Vartable::codeToIdentifier(v1->getCode());
                        else if (v1->isStr())
                            v1str = v1->getStr();
                        else
                            isv1astring = false;
                    }
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    bool isv2astring = false;
                    std::string v2str;
                    if (v2) {
                        isv2astring = true;
                        if (v2->isVariable())
                            v2str = v2->getBits()->toString();
                        else if (v2->isIdentifier())
                            v2str = Vartable::codeToIdentifier(v2->getCode());
                        else if (v2->isStr())
                            v2str = v2->getStr();
                        else
                            isv2astring = false;
                    }

                    if ((!v1) || (!v2))
                        resultValue = valuePtr();

                    else if ((v1->isNumber()) && (v2->isNumber()))
                        resultValue = Value::create(Value::NUMBER, v1->getNumber() + v2->getNumber());

                    else if (isv1astring && isv2astring)
                        resultValue = Value::create(Value::STR, v1str + v2str);

                    else if ((v1->isList()) && (v2->isList())) {
                        WARNING_STM
                        resultValue = valuePtr();
                    } else {
                        FATAL_ERROR_UNEXPECTED
                    }
                    goto valueBuilt;
                }
                    break;

                case MINUS: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    if ((!v1) || (!v2))
                        resultValue = valuePtr();
                    else if ((v1->isNumber()) && (v2->isNumber()))
                        resultValue = Value::create(Value::NUMBER, v1->getNumber() - v2->getNumber());
                    else
                        resultValue = valuePtr();
                    goto valueBuilt;
                }
                    break;

                case TIMES: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    if ((!v1) || (!v2))
                        resultValue = valuePtr();
                    else if ((v1->isNumber()) && (v2->isNumber()))
                        resultValue = Value::create(Value::NUMBER, v1->getNumber() * v2->getNumber());
                    else
                        resultValue = valuePtr();
                    goto valueBuilt;
                }
                    break;
                case DIVIDE: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    if ((!v1) || (!v2))
                        resultValue = valuePtr();
                    else if ((v1->isNumber()) && (v2->isNumber()))
                        resultValue = Value::create(Value::NUMBER, v1->getNumber() / v2->getNumber());
                    else
                        resultValue = valuePtr();
                    goto valueBuilt;
                }
                    break;
                case MODULO: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    if ((!v1) || (!v2))
                        resultValue = valuePtr();
                    else if ((v1->isNumber()) && (v2->isNumber()))
                        resultValue = Value::create(Value::NUMBER, fmod(v1->getNumber(), v2->getNumber()));
                    else
                        resultValue = valuePtr();
                    goto valueBuilt;
                }
                    break;
                case MINUS_U: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    if (!v1)
                        resultValue = valuePtr();
                    else if ((v1->isNumber()))
                        resultValue = Value::create(Value::NUMBER, -v1->getNumber());
                    else
                        resultValue = valuePtr();
                    goto valueBuilt;
                }
                    break;

                case AND: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    if ((!v1) || (!v2))
                        resultValue = valuePtr();
                    else if ((v1->isFalse()) || (v2->isFalse()))
                        resultValue = Value::NIL_VALUE;
                    else
                        resultValue = Value::TRUE_VALUE;
                    goto valueBuilt;
                }
                    break;

                case OR: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    if ((!v1) || (!v2))
                        resultValue = valuePtr();
                    else if ((v1->isFalse()) && (v2->isFalse()))
                        resultValue = Value::NIL_VALUE;
                    else
                        resultValue = Value::TRUE_VALUE;
                    goto valueBuilt;
                }
                    break;
                case EQ: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    if ((!v1) && (!v2))
                        resultValue = Value::TRUE_VALUE;

                    else if ((!v1) || (!v2))
                        resultValue = valuePtr();

                    else if ((v1->isAnonymous()) && (v2->isAnonymous()))
                        resultValue = Value::TRUE_VALUE;

                    else if ((v1->isAnonymous()) || (v2->isAnonymous()))
                        resultValue = Value::NIL_VALUE;

                    else if (v1->eq(v2))
                        resultValue = Value::TRUE_VALUE;

                    else
                        resultValue = Value::NIL_VALUE;

                    goto valueBuilt;
                }
                    break;
                case DIFF: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    if ((!v1) && (!v2)) {
                        resultValue = Value::NIL_VALUE;
                    } else if ((!v1) || (!v2)) {
                        resultValue = Value::TRUE_VALUE;
                    } else if ((v1->isAnonymous()) && (v2->isAnonymous()))
                        resultValue = Value::NIL_VALUE;

                    else if ((v1->isAnonymous()) || (v2->isAnonymous()))
                        resultValue = Value::TRUE_VALUE;

                    else if (v1->eq(v2)) {
                        resultValue = Value::NIL_VALUE;
                    } else {
                        resultValue = Value::TRUE_VALUE;
                    }
                    goto valueBuilt;
                }
                    break;
                case LT: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    // si l'une est variable libre
                    if ((!v1) || (!v2)) {
                        resultValue = Value::NIL_VALUE;
                    } else if (v1->lt(v2))
                        resultValue = Value::TRUE_VALUE;
                    else
                        resultValue = Value::NIL_VALUE;
                    goto valueBuilt;
                }
                    break;
                case LE: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    // si l'une est variable libre
                    if ((!v1) || (!v2)) {
                        resultValue = Value::NIL_VALUE;
                    } else if ((v1->lt(v2)) || (v1->eq(v2)))
                        resultValue = Value::TRUE_VALUE;
                    else
                        resultValue = Value::NIL_VALUE;
                    goto valueBuilt;
                }
                    break;
                case GT: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    // si l'une est variable libre
                    if ((!v1) || (!v2)) {
                        resultValue = Value::NIL_VALUE;
                    } else if (!(v1->lt(v2)) && (!(v1->eq(v2))))
                        resultValue = Value::TRUE_VALUE;
                    else
                        resultValue = Value::NIL_VALUE;
                    goto valueBuilt;
                }
                    break;
                case GE: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    valuePtr v2 = rhs->evalValue(item, parser, synthesizer, replaceVariables);
                    // si l'une est variable libre
                    if ((!v1) || (!v2)) {
                        resultValue = Value::NIL_VALUE;
                    } else if (!(v1->lt(v2)))
                        resultValue = Value::TRUE_VALUE;
                    else
                        resultValue = Value::NIL_VALUE;
                    goto valueBuilt;
                }
                    break;

                case NOT: {
                    valuePtr v1 = lhs->evalValue(item, parser, synthesizer, replaceVariables);
                    if (!v1
                        || v1->isFalse())
                        resultValue = Value::TRUE_VALUE;
                    else
                        resultValue = Value::NIL_VALUE;
                    goto valueBuilt;
                }
                    break;

                case RAND: {
                    resultValue = Value::create(Value::NUMBER, (double) rand());
                    goto valueBuilt;
                }
                    break;
            }
            break;

    }

    if (!resultFeatures && !resultValue && !resultList) {
        FATAL_ERROR_STM
    }

    if (resultList) {
        if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
            bool effect = false;
            item->getEnvironment()->replaceVariables(resultList, effect);
        }
        resultValue = Value::create(Value::LIST, resultList);
    } else if (resultFeatures) {
        if (resultFeatures->isNil())
            resultValue = Value::NIL_VALUE;
        else if (resultFeatures->isBottom())
            resultValue = Value::NIL_VALUE;
        else {
            if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
                bool effect = false;
                item->getEnvironment()->replaceVariables(resultFeatures, effect);
            }
            resultValue = Value::create(Value::FEATURES, resultFeatures);
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
featuresPtr Statement::unif(featuresPtr fs1, featuresPtr fs2, itemPtr item) {
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

    if (fs1->isBottom() || fs2->isBottom()) {
        result = Features::BOTTOM;
        goto endUnif;
    }
    if (fs1->isNil() && fs2->isNil()) {
        result = Features::NIL;
        goto endUnif;
    }
    if (fs1->isNil()) {
        result = fs2;
        goto endUnif;
    }
    if (fs2->isNil()) {
        result = fs1;
        goto endUnif;
    }
    result = Features::create();
    for (std::list<featurePtr>::const_iterator i1 = fs1->begin(); i1 != fs1->end(); ++i1) {

        if ((*i1)->getType() == Feature::PRED) {
            std::list<featurePtr>::const_iterator i2 = fs2->begin();
            while (i2 != fs2->end()) {
                if ((*i2)->getType() == Feature::PRED) {
                    (*i2)->addFlags(Flags::SEEN);
                    switch ((*i1)->getValue()->getType()) {

                        case Value::CODE: {
                            switch ((*i2)->getValue()->getType()) {
                                case Value::CODE:
                                    if ((*i1)->getValue()->getCode() != (*i2)->getValue()->getCode()) {
                                        result = Features::BOTTOM;
                                        goto endUnif;
                                    }
                                    break;

                                case Value::VARIABLE:
                                    result->add(Feature::create(Feature::PRED, bitsetPtr(), (*i1)->getValue()));
                                    if (!item->getEnvironment())
                                        item->setEnvironment(Environment::create());
                                    item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
                                    break;

                                default: FATAL_ERROR_STM
                                    break;
                            }
                        }
                            break;

                        case Value::VARIABLE:

                            if (((*i2)->getValue()->getType() == Value::VARIABLE) &&
                                (*(*i1)->getValue()->getBits()) == (*(*i2)->getValue()->getBits())) {} /* empty */
                            else {
                                if (item) {
                                    if (!item->getEnvironment())
                                        item->setEnvironment(Environment::create());
                                    item->getEnvironment()->add((*i1)->getValue()->getBits(), (*i2)->getValue());
                                }
                            }
                            result->add(Feature::create(Feature::PRED, bitsetPtr(), (*i2)->getValue()));
                            break;

                        case Value::ANONYMOUS:
                            result->add(Feature::create(Feature::PRED, bitsetPtr(), (*i2)->getValue()));
                            break;

                        default: FATAL_ERROR_STM
                            break;
                    }

                    break;
                }
                ++i2;
            }
            result->add(*i1);
        } else if ((*i1)->getType() == Feature::FORM) {
            std::list<featurePtr>::const_iterator i2 = fs2->begin();
            while (i2 != fs2->end()) {
                if ((*i2)->getType() == Feature::FORM) {

                    (*i2)->addFlags(Flags::SEEN);
                    if (!(*i1)->getValue()->isStr() || !(*i2)->getValue()->isStr()) FATAL_ERROR_STM

                    if ((*i1)->getValue()->getStr() != (*i2)->getValue()->getStr()) {
                        result = Features::BOTTOM;
                        goto endUnif;
                    }
                    break;
                }

                ++i2;
            }
            result->add(*i1);
        } else if ((*i1)->getType() == Feature::CONSTANT) {
            std::list<featurePtr>::const_iterator i2 = fs2->begin();
            while (i2 != fs2->end()) {
                if (((*i2)->getType() == Feature::CONSTANT) &&
                    (*(*i1)->getAttribute() & *(*i2)->getAttribute()).any()) {
                    (*i2)->addFlags(Flags::SEEN);
                    if ((!(*i1)->getValue()) || (!(*i2)->getValue())) {
                        result = Features::BOTTOM;
                        goto endUnif;
                    }

                    switch ((*i1)->getValue()->getType()) {

                        case Value::NIL:
                            FATAL_ERROR_UNEXPECTED

                        case Value::STR:
                            switch ((*i2)->getValue()->getType()) {
                                case Value::STR:
                                    if ((*i1)->getValue()->getStr() != (*i2)->getValue()->getStr()) {
                                        result = Features::BOTTOM;
                                        goto endUnif;
                                    }
                                    result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(),
                                                                (*i1)->getValue()));
                                    break;

                                case Value::VARIABLE: FATAL_ERROR_STM
                                    /*
                                  result->add(new Feature((*i2)->getAttribute(), (*i1)->getValue(), Feature::CONSTANT));
                                  if (item->getEnvironment()==NULL)
                                  item->setEnvironment(new Environment());
                                  item->getEnvironment()->add(*(*i2)->getValue()->getBits(), (*i1)->getValue());
                                    */
                                    break;

                                default: FATAL_ERROR_STM
                                    break;

                            }
                            break;

                        case Value::FALSE:
                            case Value::TRUE: {
                            switch ((*i2)->getValue()->getType()) {
                                case Value::FALSE:
                                case Value::TRUE:
                                    if ((*i1)->getValue()->isNil() != (*i2)->getValue()->isNil()) {
                                        result = Features::BOTTOM;
                                        goto endUnif;
                                    }

                                    result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(),
                                                                (*i1)->getValue()));
                                    break;
                                case Value::VARIABLE:
                                    result->add(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(),
                                                                (*i1)->getValue()));
                                    if (!item->getEnvironment())
                                        item->setEnvironment(Environment::create());
                                    item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
                                    break;
                                default: FATAL_ERROR_STM
                                    break;
                            }
                        }
                            break;

                        case Value::NUMBER: {
                            switch ((*i2)->getValue()->getType()) {
                                case Value::NUMBER:
                                    if ((*i1)->getValue()->getNumber() != (*i2)->getValue()->getNumber()) {
                                        result = Features::BOTTOM;
                                        goto endUnif;
                                    }

                                    result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(),
                                                                Value::create(Value::NUMBER,
                                                                              (*i1)->getValue()->getNumber())));
                                    break;
                                case Value::VARIABLE:
                                    result->add(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(),
                                                                (*i1)->getValue()));
                                    if (!item->getEnvironment())
                                        item->setEnvironment(Environment::create());
                                    item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
                                    break;
                                default: FATAL_ERROR_STM
                                    break;
                            }
                        }
                            break;

                        case Value::CODE: {
                            switch ((*i2)->getValue()->getType()) {
                                case Value::CODE:
                                    if ((*i1)->getValue()->getCode() != (*i2)->getValue()->getCode()) {
                                        result = Features::BOTTOM;
                                        goto endUnif;
                                    }

                                    result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(),
                                                                Value::create(Value::CODE,
                                                                              (*i1)->getValue()->getCode())));
                                    break;
                                case Value::VARIABLE:
                                    result->add(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(),
                                                                (*i1)->getValue()));
                                    if (!item->getEnvironment())
                                        item->setEnvironment(Environment::create());
                                    item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
                                    break;
                                default: FATAL_ERROR_STM
                                    break;
                            }
                        }
                            break;

                        case Value::CONSTANT: {
                            switch ((*i2)->getValue()->getType()) {
                                case Value::CONSTANT:
                                    if (((*(*i1)->getValue()->getBits()) & (*(*i2)->getValue()->getBits())).none()) {
                                        result = Features::BOTTOM;
                                        goto endUnif;
                                    }

                                    result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(),
                                                                Value::create(Value::CONSTANT, Bitset::create(
                                                                        *(*i1)->getValue()->getBits() &
                                                                        *(*i2)->getValue()->getBits()))));
                                    break;
                                case Value::VARIABLE:
                                    result->add(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(),
                                                                (*i1)->getValue()));
                                    if (!item->getEnvironment())
                                        item->setEnvironment(Environment::create());
                                    item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
                                    break;
                                case Value::ANONYMOUS:
                                    result->add(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(),
                                                                (*i1)->getValue()));
                                    break;
                                default: FATAL_ERROR_STM
                                    break;
                            }
                        }
                            break;

                        case Value::VARIABLE:

                            if (((*i2)->getValue()->getType() == Value::VARIABLE) &&
                                (*(*i1)->getValue()->getBits()) == (*(*i2)->getValue()->getBits())) {} /* empty */
                            else {
                                if (item) {
                                    if (!item->getEnvironment())
                                        item->setEnvironment(Environment::create());
                                    item->getEnvironment()->add((*i1)->getValue()->getBits(), (*i2)->getValue());
                                }
                            }
                            result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i2)->getValue()));
                            break;

                        case Value::ANONYMOUS:
                            result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i2)->getValue()));
                            break;

                        case Value::FEATURES: {
                            featuresPtr _features = unif((*i1)->getValue()->getFeatures(),
                                                        (*i2)->getValue()->getFeatures(), item);
                            if (_features->isBottom()) {
                                result = _features;
                                goto endUnif;
                            } else
                                result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(),
                                                            Value::create(Value::FEATURES, _features)));
                        }
                            break;

                        case Value::LIST:
                            result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i1)->getValue()));
                            break;
                    }

                    break;
                }
                ++i2;
            }
            if (i2 == fs2->end()) {
                result->add(*i1);
            }
        }
    }
    for (std::list<featurePtr>::const_iterator i2 = fs2->begin(); i2 != fs2->end(); ++i2) {
        if ((*i2)->isUnsetFlags(Flags::SEEN))
            result->add(*i2);
    }

    for (std::list<featurePtr>::const_iterator i1 = fs1->begin(); i1 != fs1->end(); ++i1) {
        (*i1)->subFlags(Flags::SEEN);
    }
    for (std::list<featurePtr>::const_iterator i2 = fs2->begin(); i2 != fs2->end(); ++i2) {
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
void Statement::buildInheritedSonFeatures(itemPtr item, Parser &parser, Synthesizer *synthesizer) {
    /***
        std::cerr << "buildInheritedSonFeatures: ";
        print(std::cerr);
        std::cerr << std::endl;
    ***/
    featuresPtr _features = rhs->evalFeatures(item, parser, synthesizer, true);
    if (_features->isNil())
        addFlags(Flags::BOTTOM);
    else
        item->getInheritedSonFeatures()->add(lhs->getFirst(), _features);
}

/* ************************************************************
 * ⇑ = …
 ************************************************************ */
void Statement::buildSynthesizedFeatures(itemPtr item, Parser &parser, Synthesizer *synthesizer) {
    if (!item->getSynthesizedFeatures()->isNil()) {
        this->print(std::cerr);
        FATAL_ERROR_STM
    }
    featuresPtr _features = rhs->evalFeatures(item, parser, synthesizer, true);
    if (_features->isNil())
        addFlags(Flags::BOTTOM);
    else {
        item->setSynthesizedFeatures(_features);
    }
}

/* ************************************************************
 * [ … $X … ] ⊂ ⇓1;
 * $X = ⇓1;
 ************************************************************ */
void Statement::buildEnvironmentWithSynthesize(itemPtr item, Parser &parser, Synthesizer *synthesizer) {
    switch (this->op) {
        case AFF: {
            // $X = ⇓1;
            environmentPtr environment;
            if (item->getEnvironment()) {
                environment = item->getEnvironment();
            } else {
                environment = Environment::create();
                item->setEnvironment(environment);
            }
            featuresPtr sonSynth = rhs->evalFeatures(item, parser, synthesizer, true);
            if (sonSynth) {
                environment->add(lhs->getBits(), Value::create(Value::FEATURES, sonSynth));
            } else FATAL_ERROR_STM
        }
            break;

        case SUBSUME: {
            // [ … $X … ] ⊂ ⇓1;

            featuresPtr left = lhs->evalFeatures(item, parser, synthesizer, false);
            if (!left) {

                WARNING_STM
            } else {

                environmentPtr environment;

                if (item->getEnvironment())
                    environment = item->getEnvironment();
                else {
                    environment = Environment::create();
                    item->setEnvironment(environment);
                }

                featuresPtr sonSynth = rhs->evalFeatures(item, parser, synthesizer, true);

                if (sonSynth) {

                    if (!left->buildEnvironment(environment, sonSynth, true/*, true*/)) {

                        addFlags(Flags::BOTTOM);
                    }
                } else {
                    FATAL_ERROR_STM
                }
            }

        }
            break;

        default: FATAL_ERROR_STM
            break;
    }
}

/* ************************************************************
 * [ … $X … ] ⊂ ↑;
 * $X = ↑;
 ************************************************************ */
void Statement::buildEnvironmentWithInherited(itemPtr item, Parser &parser, Synthesizer *synthesizer) {
    /***
        std::cerr << "<DIV>buildEnvironmentWithInherited ";
        this->print(std::cerr, "", TRUE_ROOT);
        std::cerr << "</DIV>";
    ***/
    switch (this->op) {
        case AFF: {
            // $X = ↑;
            featuresPtr right = rhs->evalFeatures(item, parser, synthesizer, true);
            if (!right) {
                WARNING_STM
            } else {
                environmentPtr environment;
                if (item->getEnvironment()) {
                    environment = item->getEnvironment();
                } else {
                    environment = Environment::create();
                    item->setEnvironment(environment);
                }
                environment->add(lhs->getBits(), Value::create(Value::FEATURES, right));
            }
        }
            break;

        case SUBSUME: {
            featuresPtr left = lhs->evalFeatures(item, parser, synthesizer, false);
            if (!left) {
                WARNING_STM
            } else {
                featuresPtr right = rhs->evalFeatures(item, parser, synthesizer, true);
                if (!right) {
                    WARNING_STM
                } else {
                    environmentPtr environment;
                    if (item->getEnvironment()) {
                        environment = item->getEnvironment();
                    } else {
                        environment = Environment::create();
                        item->setEnvironment(environment);
                    }
                    if (!left->buildEnvironment(environment, right, true/*, true*/)) {
                        addFlags(Flags::BOTTOM);
                    }
                }
            }
        }
            break;

        default: FATAL_ERROR_STM
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
void Statement::buildEnvironmentWithValue(itemPtr item, Parser &parser, Synthesizer *synthesizer) {
    /***
        std::cerr << "<DIV>buildEnvironmentWithValue</DIV>";
        std::cerr << "<DIV>";
        this->print(std::cerr, 0);
        std::cerr << "</DIV>";
    ***/
    switch (this->op) {
        case AFF:
            // 	 $X = a;
            // 	 $X = $Y;
            // 	 $X = … ∪ … ;
            // 	 $X = [ … ];
            // 	 $X = <expr>;
            // 	 $X = < … >
            // 	 $X = sort $X with a;
            // 	 $X = reverse $X;

            if (lhs->isVariable()) {
                valuePtr right = rhs->evalValue(item, parser, synthesizer, true);
                if (!right) {
                    this->print(std::cerr, 0);
                    WARNING_STM
                } else {
                    environmentPtr environment;
                    if (item->getEnvironment()) {
                        environment = item->getEnvironment();
                    } else {
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
            else if (lhs->isList()) {
                listPtr right = rhs->evalList(item, true);
                if (!right) {
                    FATAL_ERROR_STM
                    WARNING_STM
                } else {
                    if (right->isNil()) {
                        FATAL_ERROR_STM
                        addFlags(Flags::BOTTOM);
                    }
                    listPtr left = lhs->evalList(item, false);
                    if (!left) {
                        WARNING_STM
                    } else {
                        environmentPtr environment;
                        if (item->getEnvironment()) {
                            environment = item->getEnvironment();
                        } else {
                            environment = Environment::create();
                            item->setEnvironment(environment);
                        }
                        if (!left->buildEnvironment(environment, right, true, true)) {
                            addFlags(Flags::BOTTOM);
                        }
                    }
                }
            } else FATAL_ERROR_STM
            break;

        case SUBSUME: {
            featuresPtr right = rhs->evalFeatures(item, parser, synthesizer, true);
            if (!right) {
                WARNING_STM
            } else {
                if (right->isNil()) {} // empty
                featuresPtr left = lhs->evalFeatures(item, parser, synthesizer, false);
                if (left) {
                    environmentPtr environment;
                    if (item->getEnvironment()) {
                        environment = item->getEnvironment();
                    } else {
                        environment = Environment::create();
                        item->setEnvironment(environment);
                    }
                    if (!left->buildEnvironment(environment, right, true/*, true*/)) {
                        addFlags(Flags::BOTTOM);
                    }
                }
            }
        }
            break;

        default: FATAL_ERROR_STM
            break;
    }
}

/* ************************************************************
 * attest
 ************************************************************ */
void Statement::stmAttest(itemPtr item, Parser &parser, Synthesizer *synthesizer) {
    /***
        std::cerr << "<DIV>*** attest</DIV>";
        std::cerr << "<DIV>";
        this->print(std::cerr);
        std::cerr << "</DIV>";
    ***/
    switch (this->op) {
        case ATTEST: {
            valuePtr res = lhs->evalValue(item, parser, synthesizer, true);
            if ((!res) || (res == Value::NIL_VALUE) || (res == Value::ANONYMOUS_VALUE) ||
                ((res->getType() == Value::FEATURES) && (res->getFeatures()->isBottom()))) {
                addFlags(Flags::BOTTOM);
            }
        }
            break;
        default: FATAL_ERROR_STM
            break;
    }
}

/* ************************************************************
 * guard
 ************************************************************ */
void Statement::stmGuard(const itemPtr &item/*, Synthesizer *synthesizer*/) {
    /***
         CERR_LINE;
         std::cerr << "<DIV>guard ";
         item->print(std::cerr);
         print(std::cerr);
         std::cerr << "</DIV>";
    ***/
    if (isSetFlags(Flags::DISABLED | Flags::SEEN)) {
        FATAL_ERROR_STM
    } else {
        featuresPtr localFeatures = getFeatures();
        if (!localFeatures) {
            FATAL_ERROR_STM
        }
        environmentPtr environment;
        if (item->getEnvironment())
            environment = item->getEnvironment();
        else {
            environment = Environment::create();
            item->setEnvironment(environment);
        }
        featuresPtr localRhs = item->getInheritedFeatures();

        if (!localFeatures->buildEnvironment(environment, localRhs, false/*, true*/)) {
            addFlags(Flags::BOTTOM);
        }
        if (item->getEnvironment()->size() == 0) {
            item->getEnvironment().reset();
            item->setEnvironment(environmentPtr());
        }
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
void Statement::stmForeach(itemPtr item, Parser &parser, Synthesizer *synthesizer, bool &effect) {
    /***
        std::cerr << "<DIV>foreach";
        item->print(std::cerr);
        print(std::cerr);
        std::cerr << "</DIV>";
    ***/

    statementPtr variable = getLhs();
    valuePtr _value = getRhs()->getLhs()->evalValue(item, parser, synthesizer, true);
    statementPtr body = getRhs()->getRhs();
    if (!_value->isList()) FATAL_ERROR_MSG_STM("foreach does'nt apply a list")
    listPtr _list = _value->getList();
    _list->apply(item, parser, synthesizer, variable, body, effect);
    /***
        std::cerr << "<DIV>foreach done";
        item->print(std::cerr);
        std::cerr << "</DIV>";
    ***/
}

/* ************************************************************
 * if
 ************************************************************ */
void Statement::stmIf(itemPtr item, Parser &parser, Synthesizer *synthesizer, bool &effect) {
    statementPtr _lhs = getRhs()->getLhs();
    statementPtr _rhs = getRhs()->getRhs();

    unsigned int resif = 0;    // 0:none 1:then 2:else
    //if (lhs->isSetFlags(Flags::CHOOSEN))
    //	resif = 1;
    //else if (rhs && rhs->isSetFlags(Flags::CHOOSEN))
    //	resif = 2;
    //else {
    {
        valuePtr res = getLhs()->evalValue(item, parser, synthesizer, true);
        if (!res)
            resif = 0;
        else if (res == Value::NIL_VALUE || res == Value::ANONYMOUS_VALUE) {
            resif = 2;
            _lhs->addFlags(Flags::REJECTED);
            if (_rhs)
                _rhs->addFlags(Flags::CHOOSEN);
        } else {
            resif = 1;
            _lhs->addFlags(Flags::CHOOSEN);
            if (_rhs)
                _rhs->addFlags(Flags::REJECTED);
        }
    }
    //bool localResult = true;
    switch (resif) {
        case 1:
            _lhs->apply(item, parser, synthesizer, effect);
            if (_lhs->isSetFlags(Flags::BOTTOM)) {
                this->addFlags(Flags::BOTTOM);
            }
            if (_lhs->isSetFlags(Flags::SEEN))
                this->addFlags(Flags::SEEN);
            break;
        case 2:
            if (_rhs) {
                _rhs->apply(item, parser, synthesizer, effect);
                if (_rhs->isSetFlags(Flags::BOTTOM))
                    this->addFlags(Flags::BOTTOM);
                if (_rhs->isSetFlags(Flags::SEEN))
                    this->addFlags(Flags::SEEN);
            } else {
                this->addFlags(Flags::SEEN);
            }
            break;
    }
}

/* ************************************************************
 * print
 ************************************************************ */
void Statement::stmPrint(itemPtr item, Parser &parser, Synthesizer *synthesizer) {
    addFlags(Flags::SEEN);
    if (lhs->isStr()) {
        std::cout << lhs->getStr();
    } else {
        valuePtr _value = lhs->evalValue(item, parser, synthesizer, true);
        _value->print(std::cout);
    }
}

/* ************************************************************
 * println
 ************************************************************ */
void Statement::stmPrintln(itemPtr item, Parser &parser, Synthesizer *synthesizer) {
    stmPrint(item, parser, synthesizer);
    std::cout << std::endl;
}

/* **************************************************
 *
 ************************************************** */
void Statement::renameVariables(size_t i) {
    switch (this->op) {
        case VARIABLE: {
            std::string _str = getBits()->toString() + "_" + std::to_string(i);
            bitsetPtr variableBits = Vartable::createVariable(_str);
            bitset = variableBits;
        }
            break;
        case CONSTANT:
        case ANONYMOUS:
        case NIL:
        case STR:
        case NOT_NIL:
        case NUMBER:
        case UP:
        case UP2:
        case DASH:
        case DOWN2:
        case DOWN:
        case SEARCH:
        case FINISHED:
            break;
        case AFF:
        case SUBSUME:
        case INSET:
        case FCT:
        case UNIF:
        case ATTEST:
        case PRINT:
        case PRINTLN:
        case IF:
        case THENELSE:
        case IN:
            if (lhs)
                lhs->renameVariables(i);
            if (rhs)
                rhs->renameVariables(i);
            break;
        case FOREACH:
            break;
        case FEATURES:
        case GUARD:
            getFeatures()->renameVariables(i);
            break;
        case LIST:
            getList()->renameVariables(i);
            break;
        case STMS:
            getStatements()->renameVariables(i);
            break;
    }
}

/* ************************************************************
 *
 ************************************************************ */
void Statement::enable(statementPtr root, itemPtr item, Synthesizer *synthesizer, bool &effect, bool on) {
#ifdef TRACE_APPLY
    if (synthesizer->getTraceAction()) {
      std::cout << "<H3>####################### ENABLE #######################</H3>" << std::endl;
      print(std::cout);
      std::cout << std::endl;
    }
#endif
    switch (this->op) {

        case STMS:
            getStatements()->enable(item, synthesizer, effect, on);
            break;

        case IF:
            //if (lhs->op != VARIABLE)
            lhs->enable(shared_from_this(), item, synthesizer, effect, on);
            rhs->enable(rhs, item, synthesizer, effect, on);
            break;

        case THENELSE:
            lhs->enable(lhs, item, synthesizer, effect, on);
            if (rhs)
                rhs->enable(rhs, item, synthesizer, effect, on);
            break;

        case FOREACH:
            //lhs->enable(shared_from_this(), item, effect, on);
            rhs->enable(rhs, item, synthesizer, effect, on);
            break;

        case IN:
            lhs->enable(lhs, item, synthesizer, effect, on);
            if (rhs)
                rhs->enable(rhs, item, synthesizer, effect, on);
            break;

        case GUARD:
            if (on) {
                if (item->getInheritedFeatures()->isNil()) {
                    this->addFlags(Flags::DISABLED);
                    effect = true;
                }
            } else {
                this->subFlags(Flags::DISABLED);
            }
            break;

        case AFF:
        case SUBSUME:
        case INSET:
            rhs->enable(shared_from_this(), item, synthesizer, effect, on);
            break;

        case FCT:
        case UNIF:
            if (lhs)
                lhs->enable(root, item, synthesizer, effect, on);
            if (rhs)
                rhs->enable(root, item, synthesizer, effect, on);
            break;

        case PRINT:
        case PRINTLN:
            lhs->enable(root, item, synthesizer, effect, on);
            break;

        case ATTEST:
            lhs->enable(root, item, synthesizer, effect, on);
            break;

        case DASH:
            // if (#1)   NP -> [det] N { if (#1) ↓1 = ↑ ∪ ⇓2 ∪ [qual:$Qual, part:$Part]; else [detNum:NIL, det:no]; }
            // if (#2)   VP -> VP [NP] {   if (#2) { ↓1 = $Rest; ↓2 = [pcas:$pcas, $PObj];} else { attest ($Pred == _pro); ↓1 = [prep_objCl:$PObj, $Rest];} }
            if (on) {
                if (item->getTerms(getFirst())
                    && ((!item->getTerms(getFirst())->isOptional() && item->getTerms(getFirst())->size() == 1)
                        || (item->getTerms(getFirst())->isOptional() && item->getForestIdentifiers()[getFirst()]))) {
                } else {
                    root->addFlags(Flags::DISABLED);
                    effect = true;
                }
            } else {
                root->subFlags(Flags::DISABLED);
                effect = true;
            }
            break;

        case VARIABLE:
            if (on) {
                if ((!item->getEnvironment()) || !(item->getEnvironment()->find(getBits()))) {
                    root->addFlags(Flags::DISABLED);
                    effect = true;
                }
            } else {
                root->subFlags(Flags::DISABLED);
                effect = true;
            }
            break;

        case LIST:
            getList()->enable(root, item, synthesizer, effect, on);
            break;

        case FEATURES:
            getFeatures()->enable(root, item, synthesizer, effect, on);
            break;

        case SEARCH:
            if (lhs)
                lhs->enable(root, item, synthesizer, effect, on);
            break;

        case DOWN2:
            if (on) {
                if ((*item->getSynthesizedSonFeatures())[getFirst()]->isNil()) {
                    root->addFlags(Flags::DISABLED);
                    effect = true;
                }
            } else {
                root->subFlags(Flags::DISABLED);
                effect = true;
            }
            break;

        case UP:
            if (on) {
                if (item->getInheritedFeatures()->isNil()) {
                    root->addFlags(Flags::DISABLED);
                    effect = true;
                }
            } else {
                root->subFlags(Flags::DISABLED);
                effect = true;
            }
            break;

        case UP2:
            if (on) {
                if (item->getSynthesizedFeatures()->isNil()) {
                    root->addFlags(Flags::DISABLED);
                    effect = true;
                }
            } else {
                root->subFlags(Flags::DISABLED);
                effect = true;
            }
            break;

        case DOWN:
        case CONSTANT:
        case ANONYMOUS:
        case NIL:
        case NOT_NIL:
        case STR:
        case FINISHED:
        case NUMBER:
            break;
    }

}

/* **************************************************
 * 
 ************************************************** */
void Statement::apply(itemPtr item, Parser &parser, Synthesizer *synthesizer, bool &effect) {
#ifdef TRACE_APPLY
    if (synthesizer->getTraceAction()) {
      std::cout << "<H3>####################### APPLY #######################</H3>" << std::endl;
      std::cout << "Apply: " << std::endl;
      print(std::cout);
      std::cout << std::endl;
    }
#endif

    if (isSetFlags(Flags::SEEN | Flags::DISABLED | Flags::BOTTOM)) {
        FATAL_ERROR_UNEXPECTED
    }

    // […]
    if (isGuard()) {
        stmGuard(item/*, synthesizer*/);
        effect = true;
        addFlags(Flags::SEEN);
    }

        // if
    else if (isIf()) {
        stmIf(item, parser, synthesizer, effect);
    }

        // foreach $i in $list
    else if (isForeach()) {
        stmForeach(item, parser, synthesizer, effect);
        addFlags(Flags::SEEN);
    }

        // ↓1 = …
    else if ((isAff()) && (getLhs()->isDown())) {
        buildInheritedSonFeatures(item, parser, synthesizer);
        effect = true;
        addFlags(Flags::SEEN);
    }

        // [ … $X … ] ⊂ ⇓1
        // $X = ⇓1
    else if (((isSubsume()) && (getRhs()->isDown2()) && (getLhs()->isFeatures())) ||
             ((isAff()) && (getRhs()->isDown2()) && (getLhs()->isVariable()))) {
        buildEnvironmentWithSynthesize(item, parser, synthesizer);
        effect = true;
        addFlags(Flags::SEEN);
    }

        // [ … $X … ] ⊂ ↑
        // $X = ↑
    else if (((isSubsume()) && (getRhs()->isUp()) && (getLhs()->isFeatures())) ||
             ((isAff()) && (getRhs()->isUp()) && (getLhs()->isVariable()))) {
        buildEnvironmentWithInherited(item, parser, synthesizer);
        effect = true;
        addFlags(Flags::SEEN);
    }

        // $X = a;
        // $X = Y;
        // $X = … ∪ … ;
        // $X = [ … ];
        // $X = <expr>;
        // $X = < … >
        // $X = sort Y with a;
        // $X = reverse Y;
        // $X = combination Y;
        // $X = search Y;
        //
        // < … > = $X;
        // < … > = < … >
        // < … > = sort $X with a;
        // < … > = reverse $X;
        //
        // [ … $X … ] ⊂ Y
        // [ … $X … ] ⊂ [ … ]
        // [ … $X … ] ⊂ search Y
    else if (((isAff()) && (getLhs()->isVariable())
              && ((getRhs()->isConstant()) || (getRhs()->isVariable()) || (getRhs()->isUnif()) ||
                  (getRhs()->isFeatures()) || (getRhs()->isNumber()) || (getRhs()->isFct())
                  || (getRhs()->isList()) || (getRhs()->isSearch()))) ||
             ((isAff()) && (getLhs()->isList()) && ((getRhs()->isVariable()) || (getRhs()->isList())))
             || ((isSubsume()) && (getLhs()->isFeatures()) &&
                 ((getRhs()->isVariable()) || (getRhs()->isFeatures()) || (getRhs()->isSearch())))) {
        buildEnvironmentWithValue(item, parser, synthesizer);
        effect = true;
        addFlags(Flags::SEEN);
    }

        // ⇑ = …
    else if ((isAff()) && (getLhs()->isUp2())) {
        buildSynthesizedFeatures(item, parser, synthesizer);
        effect = true;
        addFlags(Flags::SEEN);
    }

        // attest …
    else if (isAttest()) {
        stmAttest(item, parser, synthesizer);
        addFlags(Flags::SEEN);
    }

        // print
    else if (isPrint()) {
        stmPrint(item, parser, synthesizer);
        addFlags(Flags::SEEN);
    }

        // println
    else if (isPrintln()) {
        stmPrintln(item, parser, synthesizer);
        addFlags(Flags::SEEN);
    }

        // statements
    else if (isStms()) {
        this->statements->apply(item, parser, synthesizer, effect);
        if (this->statements->isSetFlags(Flags::BOTTOM))
            this->addFlags(Flags::BOTTOM);
        if (this->statements->isSetFlags(Flags::SEEN))
            this->addFlags(Flags::SEEN);
    }

        // else error
    else {
        FATAL_ERROR_UNEXPECTED
    }

#ifdef TRACE_APPLY
    if (synthesizer->getTraceAction()) {
      std::cout << "<H3>####################### APPLY DONE " << effect << " #######################</H3>" << std::endl;
      item->print(std::cout);
      std::cout << std::endl;
    }
#endif

}

/* **************************************************
 *
 ************************************************** */
void Statement::lookingForAssignedInheritedSonFeatures(std::vector<bool> &assignedInheritedSonFeatures) {
    switch (this->op) {
        case AFF:
            // ↓1 = …
            if ((this->isAff()) && (this->getLhs()->isDown()))
                assignedInheritedSonFeatures[this->getLhs()->getFirst()] = true;
            break;

        case IF: {
            statementPtr left = getRhs()->getLhs();
            statementPtr right = getRhs()->getRhs();
            if (left->isSetFlags(Flags::CHOOSEN)) {
                left->lookingForAssignedInheritedSonFeatures(assignedInheritedSonFeatures);
            } else if (right && right->isSetFlags(Flags::CHOOSEN)) {
                right->lookingForAssignedInheritedSonFeatures(assignedInheritedSonFeatures);
            }
        }
            break;

        case STMS:
            //getStatements()->lookingForAssignedInheritedSonFeatures(assignedInheritedSonFeatures);
            break;

        default:
            break;
    }
}

/* ************************************************************
 *
 ************************************************************ */
bool Statement::findVariable(bitsetPtr variable) {
    switch (this->op) {

        case STMS:
            FATAL_ERROR_UNEXPECTED
            /*if (getStatements()->findVariableElsewhere(statementPtr(), variable))
                return true;
            break;
             */

        case IF:
            if (rhs->findVariable(variable))
                return true;
            break;

        case THENELSE:
            if (lhs->findVariable(variable))
                return true;
            if (rhs)
                if (rhs->findVariable(variable))
                    return true;
            break;

        case FOREACH:
            if (rhs->findVariable(variable))
                return true;
            break;

        case IN:
            if (lhs->findVariable(variable))
                return true;
            if (rhs)
                if (rhs->findVariable(variable))
                    return true;
            break;

        case GUARD:
            if (getFeatures()->findVariable(variable))
                return true;
            break;

        case AFF:
        case SUBSUME:
        case INSET:
            if (rhs->findVariable(variable))
                return true;
            break;

        case FCT:
        case UNIF:
            if (lhs && lhs->findVariable(variable))
                return true;
            if (rhs && rhs->findVariable(variable))
                return true;
            break;

        case ATTEST:
        case PRINT:
        case PRINTLN:
            if (lhs->findVariable(variable))
                return true;
            break;

        case VARIABLE:
            if (getBits() == variable)
                return true;
            break;

        case LIST:
            if (getList()->findVariable(variable))
                return true;
            break;

        case FEATURES:
            if (getFeatures()->findVariable(variable))
                return true;
            break;

        case DOWN:
        case SEARCH: {
            FATAL_ERROR_UNEXPECTED
        }
            break;

        default:
            break;
    }
    return false;
}

