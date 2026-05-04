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
        std::ostringstream oss;                                                                          \
        if (statement)                                                                                   \
        {                                                                                                \
            oss << "statement " << ' ' << statement->bufferName << '(' << statement->_getLineno() << ')'; \
        }                                                                                                \
        throw fatal_exception(oss);                                                                      \
    }

#define FATAL_ERROR_OSS_MSG_STM(statement, oss)                            \
    {                                                          \
        oss << ' ' << statement->bufferName << '(' << statement->_getLineno() << ')'; \
        throw fatal_exception(oss);                            \
    }

#define FATAL_ERROR_MSG(msg)                                      \
    {                                                                 \
        std::ostringstream oss;                                       \
        oss << msg << ' ' << bufferName << '(' << _getLineno() << ')'; \
        throw fatal_exception(oss);                                   \
    }

#define FATAL_ERROR_OSS_MSG(oss)                            \
    {                                                          \
        oss << ' ' << bufferName << '(' << _getLineno() << ')'; \
        throw fatal_exception(oss);                            \
    }

#define WARNING_STM                                                              \
    {                                                                            \
        std::ostringstream oss;                                                  \
        oss << "*** warning " << ' ' << bufferName << '(' << _getLineno() << ')'; \
        std::cerr << oss.str() << std::endl;                                     \
    }

#define WARNING_STM_OSS(oss)                                                              \
    {                                                                            \
        oss << ' ' << bufferName << '(' << _getLineno() << ')'; \
        std::cerr << oss.str() << std::endl;                                     \
    }

class Statement : public Facade,
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
        EPRINT_STATEMENT,
        EPRINTLN_STATEMENT,
        ATTEST_STATEMENT,
        IF_STATEMENT,
        THEN_STATEMENT,
        THEN_ELSE_STATEMENT,
        FOREACH_STATEMENT,
        FOREACH_CON_T_STATEMENT,
        STMS_STATEMENT,
        STRING_STATEMENT,
        PAIRP_STATEMENT,
        NUMBER_STATEMENT,
        FUNCTION_STATEMENT,
        SEARCH_STATEMENT,
        DEFERRED_STATEMENT,
        FIELD_ACCESS_STATEMENT
    };

    enum function_type
    {
        NOP,
        NOT,
        AND,
        OR,
        DIFF,
        EQUAL,
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
        FLOOR,
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

    statementPtr first;
    statementPtr second;
    uint32_t code;
    featuresPtr features;
    valuePtr value;
    bitsetPtr bitset;
    std::string string;
    function_type function;
    pairpPtr pairp;
    statementsPtr statements;
    double number;

public:
    Statement(uint32_t lineno, std::string bufferName, type op, bool rootOp);

    ~Statement();

    // NIL UP UP2
    static statementPtr createEmpty(uint32_t lineno, std::string bufferName, type op, bool rootOp);

    // DOWN DOWN2 DASH
    static statementPtr create(uint32_t lineno, std::string bufferName, type op, bool rootOp, uint8_t first, uint8_t second = UINT8_MAX);

    // STMS PRINT PRINTLN
    static statementPtr createStatements(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementsPtr);

    // GUARD FEATURES
    static statementPtr createFeatures(uint32_t lineno, std::string bufferName, type op, bool rootOp, featuresPtr features);

    // ATTEST THEN
    static statementPtr createFirst(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementPtr first);

    // AFF SUBSUME IF IF_CON_T DEFERRED FOREACH_CON_T UNIF
    static statementPtr createFirstSecond(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementPtr first, statementPtr second);

    // AFF SUBSUME IF IF_CON_T DEFERRED FOREACH_CON_T UNIF
    static statementPtr createFirstSecondThird(uint32_t lineno, std::string bufferName, type op, bool rootOp, statementPtr first, statementPtr second);

    // FOREACH
    static statementPtr createForeach(uint32_t lineno, std::string bufferName, bool rootOp, uint32_t code, statementPtr first);

    // SEARCH
    static statementPtr createSearch(uint32_t lineno, std::string bufferName, bool rootOp, uint32_t code, statementPtr first);

// FIELD_ACCESS_STATEMENT
// ↑.attr or ⇓i.attr
static statementPtr createFieldAccess(
    uint32_t lineno,
    std::string bufferName,
    bool rootOp,
    statementPtr base,
    bitsetPtr attribute
);

// CONSTANT
    static statementPtr createConstant(uint32_t lineno, std::string bufferName, bool rootOp, bitsetPtr bits);

    // VARIABLE
    static statementPtr createVariable(uint32_t lineno, std::string bufferName, bool rootOp, uint32_t code);

    // PAIRP
    static statementPtr createPairp(uint32_t lineno, std::string bufferName, bool rootOp, pairpPtr);

    // FCT
    static statementPtr createFunction(uint32_t lineno, std::string bufferName, bool rootOp, function_type fct,
                               statementPtr first = statementPtr(),
                               statementPtr second = statementPtr());

    // NUMBER
    static statementPtr createNumber(uint32_t lineno, std::string bufferName, bool rootOp, double);

    // STRING
    static statementPtr createString(uint32_t lineno, std::string bufferName, bool rootOp, std::string str);

    // ANONYMOUS
    static statementPtr createAnonymous(uint32_t lineno, std::string bufferName, bool rootOp);

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

    bool isEprint() const;

    bool isEprintln() const;

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

bool isFieldAccess() const;

bool containsDash() const;

    function_type _getFct() const;

    statementPtr _getFirst() const;

    statementPtr _getSecond() const;

    featuresPtr _getFeatures() const;

    bitsetPtr _getBitset() const;

    uint32_t getCode() const;

    uint8_t getFirst() const;

    uint8_t getSecond() const;

    std::string &_getString();

    pairpPtr _getPairp() const;

    statementsPtr _getStatements() const;

    double _getNumber() const;

    uint32_t _getLineno() const;

    std::string _getBufferName() const;

    void brln(std::ostream &out, int tabulation) const;

    void toHTML(std::ostream &, uint8_t tabulationLenght = 5, uint8_t tabulation = 0, uint32_t color = 0x000000, uint32_t bgcolor = 0xFFFFFF) const;

    featuresPtr evalFeatures(class Item *, class Parser &, class Generator *, bool replaceVariables, bool verbose);

    pairpPtr evalPairp(class Item *, Parser &, Generator *, bool, bool verbose);

    valuePtr evalValue(class Item *, Parser &, Generator *, bool, bool verbose);

    static featuresPtr unif(statementPtr statement, const featuresPtr &, const featuresPtr &, class Item *, bool verbose);

    statementPtr clone(const std::bitset<MAX_FLAGS> &savedFlags = std::bitset<MAX_FLAGS>());

    void buildInheritedChildFeatures(class Item *item, Parser &parser, Generator *synthesizer, bool replaceVariables, bool verbose);

    void buildSynthesizedFeatures(class Item *, Parser &, Generator *synthesizer, bool verbose);

    void buildEnvironmentWithInherited(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool verbose);

    void buildEnvironmentWithSynthesize(statementPtr statement, class Item *, Parser &, Generator *synthesizer, bool verbose);

    void buildEnvironmentWithValue(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool verbose);

    void stmAttest(class Item *item, Parser &parser, Generator *synthesizer, bool verbose);

    void stmGuard(statementPtr statementRoot, class Item *item, bool verbose);

    void stmForeach(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool verbose);

    void stmIf(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool replaceVariables, bool verbose);
    
    void stmDeferred(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool replaceVariables, bool verbose);

    void stmPrint(class Item *item, Parser &parser, Generator *generator, std::ostream &out, bool verbose);

    void stmPrintln(class Item *item, Parser &parser, Generator *generator, std::ostream &out, bool verbose);

    void testEnable(statementPtr statementRoot, class Item *, class Generator *, bool &, bool);

    void apply(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool replaceVariables, bool verbose);

    void lookingForAssignedInheritedChildFeatures(std::vector<bool> &);

    void renameVariable(uint32_t);

    bool containsVariable(const uint32_t);

//protected:
//    void makeSerialString() override;
};

#endif // ELVEX_STATEMENT_H
