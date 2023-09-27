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

#ifndef ELVEX_STATEMENT_H
#define ELVEX_STATEMENT_H

#include <climits>
#include <vector>
#include <string>
#include "facade.hpp"
#include "shared_ptr.hpp"
#include "serializable.hpp"
#include "generator.hpp"

#define FATAL_ERROR_STM(statement)                                                                       \
    {                                                                                                    \
        CERR_LINE;                                                                                       \
        std::ostringstream oss;                                                                          \
        if (statement)                                                                                   \
        {                                                                                                \
            oss << "statement " << ' ' << statement->bufferName << '(' << statement->getLineno() << ')'; \
        }                                                                                                \
        throw fatal_exception(oss);                                                                      \
    }

#define FATAL_ERROR_MSG_STM(msg)                                      \
    {                                                                 \
        std::ostringstream oss;                                       \
        oss << msg << ' ' << bufferName << '(' << getLineno() << ')'; \
        throw fatal_exception(oss);                                   \
    }
#define FATAL_ERROR_OS_MSG_STM(oss)                            \
    {                                                          \
        oss << ' ' << bufferName << '(' << getLineno() << ')'; \
        throw fatal_exception(oss);                            \
    }
#define WARNING_STM                                                              \
    {                                                                            \
        CERR_LINE;                                                               \
        std::ostringstream oss;                                                  \
        oss << "*** warning " << ' ' << bufferName << '(' << getLineno() << ')'; \
        std::cerr << oss.str() << std::endl;                                     \
    }

class Statement : public Facade,
                  public Serializable,
                  public std::enable_shared_from_this<class Statement>
{

public:
    enum type
    {
        DASH_STATEMENT,
        ASSIGNMENT_STATEMENT,
        SUBSUME_STATEMENT,
        INHERITED_FEATURES_STATEMENT,
        SYNTHESIZED_FEATURES_STATEMENT,
        INHERITED_CHILDREN_FEATURES_STATEMENT,
        SYNTHESIZED_CHILDREN_FEATURES_STATEMENT,
        FEATURES_STATEMENT,
        VARIABLE_STATEMENT,
        ANONYMOUS_STATEMENT,
        CONSTANT_STATEMENT,
        NIL_STATEMENT,
        UNIF_STATEMENT,
        GUARD_STATEMENT,
        PRINT_STATEMENT,
        PRINTLN_STATEMENT,
        ATTEST_STATEMENT,
        IF_STATEMENT,
        IF_CON_T_STATEMENT,
        FOREACH_STATEMENT,
        FOREACH_CON_T_STATEMENT,
        STMS_STATEMENT,
        STRING_STATEMENT,
        PAIRP_STATEMENT,
        NUMBER_STATEMENT,
        FUNCTION_STATEMENT,
        SEARCH_STATEMENT,
        DEFERRED_STATEMENT
    };

    enum arithmetic_op
    {
        NOP,
        NOT,
        AND,
        OR,
        DIFF,
        EQ,
        LT,
        LE,
        GT,
        GE,
        PLUS,
        MINUS,
        TIMES,
        DIVIDE,
        MODULO,
        MINUS_U,
        RANDOM
    };

    enum test_choice
    {
        __NONE__,
        __THEN__,
        __ELSE__
    };

private:
    uint32_t lineno;
    std::string bufferName;
    static std::string nullBufferName;
    enum type op;
    bool rootOp;

    statementPtr lhs;
    statementPtr rhs;
    uint8_t first;
    uint8_t second;
    featuresPtr features;
    valuePtr value;
    bitsetPtr bitset;
    std::string string;
    arithmetic_op fct;
    pairpPtr pairp;
    statementsPtr statements;
    double number;

public:
    Statement(uint32_t lineno, std::string bufferName, type op, bool rootOp);

    void makeSerialString();

public:
    ~Statement();

    // NIL UP UP2
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp);

    // DOWN DOWN2 DASH
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, uint8_t first, uint8_t second = UINT8_MAX);

    // STMS PRINT PRINTLN
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementsPtr);

    // GUARD FEATURES
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, featuresPtr features);

    // ATTEST THEN
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementPtr lhs);

    // AFF SUBSUME IF IF_CON_T DEFERRED FOREACH FOREACH_CON_T UNIF
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementPtr lhs, statementPtr rhs);

    // VARIABLE CONSTANT
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, bitsetPtr bits);

    // PAIRP
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, pairpPtr);

    // FCT
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, arithmetic_op fct,
                               statementPtr lhs = statementPtr(),
                               statementPtr rhs = statementPtr());

    // NUMBER
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, double);

    // STRING
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, std::string str);

    // ANONYMOUS
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, valuePtr &value);

    // SEARCH
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementPtr lhs, uint8_t first);

    bool isAssignment() const;

    bool isSubsume() const;

    bool isUp() const;

    bool isUp2() const;

    bool isDown() const;

    bool isDown2() const;

    bool isFeatures() const;

    bool isVariable() const;

    bool isConstant() const;

    bool isUnif() const;

    bool isGuard() const;

    bool isPrint() const;

    bool isPrintln() const;

    bool isAttest() const;

    bool isIf() const;

    bool isForeach() const;

    bool isDeferred() const;

    bool isStms() const;

    bool isString() const;

    bool isPairp() const;

    bool isNumber() const;

    bool isFct() const;

    bool isSearch() const;

    bool containsDash() const;

    arithmetic_op getFct() const;

    statementPtr getLhs() const;

    statementPtr getRhs() const;

    featuresPtr getFeatures() const;

    bitsetPtr getBits() const;

    uint8_t getFirst() const;

    uint8_t getSecond() const;

    std::string getString() const;

    pairpPtr getPairp() const;

    statementsPtr getStatements() const;

    double getNumber() const;

    uint32_t getLineno() const;

    std::string getBufferName() const;

    void brln(std::ostream &out, int tabulation) const;

    void print(std::ostream &, uint8_t tabulationLenght = 5, uint8_t tabulation = 0, uint32_t color = 0x000000, uint32_t bgcolor = 0xFFFFFF) const;

    featuresPtr evalFeatures(class Item *, class Parser &, class Generator *, bool);

    pairpPtr evalPairp(class Item *, Parser &, Generator *, bool);

    valuePtr evalValue(class Item *, Parser &, Generator *, bool);

    static featuresPtr unif(statementPtr from, const featuresPtr &, const featuresPtr &, class Item *);

    statementPtr clone(const std::bitset<FLAGS> &savedFlags = std::bitset<FLAGS>());

    void buildInheritedSonFeatures(class Item *, Parser &, Generator *synthesizer);

    void buildSynthesizedFeatures(class Item *, Parser &, Generator *synthesizer);

    void buildEnvironmentWithInherited(statementPtr from, class Item *, Parser &, Generator *synthesizer);

    void buildEnvironmentWithSynthesize(statementPtr from, class Item *, Parser &, Generator *synthesizer);

    void buildEnvironmentWithValue(statementPtr from, class Item *, Parser &, Generator *);

    void stmAttest(class Item *, class Parser &, class Generator *);

    void stmGuard(statementPtr from, class Item *);

    void stmForeach(statementPtr from, class Item *item, class Parser &, class Generator *, bool &);

    void stmIf(statementPtr from, class Item *item, class Parser &, class Generator *, bool &);

    void stmDeferred(statementPtr from, class Item *item, class Parser &, class Generator *, bool &);

    void stmPrint(class Item *, class Parser &, class Generator *);

    void stmPrintln(class Item *, class Parser &, class Generator *);

    void renameVariables(size_t);

    void toggleEnable(const statementPtr &, class Item *, class Generator *, bool &, bool);

    void apply(statementPtr from, class Item *, class Parser &, class Generator *, bool &);

    void lookingForAssignedInheritedSonFeatures(std::vector<bool> &);

    bool findVariable(const bitsetPtr &);
};

#endif // ELVEX_STATEMENT_H
