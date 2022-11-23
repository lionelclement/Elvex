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

#ifndef ELVEX_STATEMENT_H
#define ELVEX_STATEMENT_H

#include <climits>
#include <vector>
#include <string>
#include "facade.hpp"
#include "shared_ptr.hpp"
#include "serializable.hpp"
#include "synthesizer.hpp"

#define FATAL_ERROR_STM                          \
    {                                            \
        CERR_LINE;                               \
        std::ostringstream oss;                  \
        oss << "statement " << ' ' << bufferName << '(' << getLineno() << ')'; \
        throw fatal_exception(oss);              \
    }
#define FATAL_ERROR_MSG_STM(msg)               \
    {                                          \
        std::ostringstream oss;                \
        oss << msg << ' ' << bufferName << '(' << getLineno() << ')'; \
        throw fatal_exception(oss);            \
    }
#define FATAL_ERROR_OS_MSG_STM(oss)     \
    {                                   \
        oss << ' ' << bufferName << '(' << getLineno() << ')'; \
        throw fatal_exception(oss);     \
    }
#define WARNING_STM                                \
    {                                              \
        CERR_LINE;                                 \
        std::ostringstream oss;                    \
        oss << "*** warning " << ' ' << bufferName << '(' << getLineno() << ')'; \
        std::cerr << oss.str() << std::endl;       \
    }

class Statement : public Facade,
                  public Serializable,
                  public std::enable_shared_from_this<class Statement>
{

public:
    enum type
    {
        DASH,
        AFF,
        SUBSUME,
        UP,
        UP2,
        DOWN,
        DOWN2,
        FEATURES,
        VARIABLE,
        ANONYMOUS,
        CONSTANT,
        NIL,
        UNIF,
        GUARD,
        PRINT,
        PRINTLN,
        ATTEST,
        IF,
        THENELSE,
        FOREACH,
        IN,
        STMS,
        STR,
        PAIRP,
        NUMBER,
        FCT,
        SEARCH,
        FINISHED
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
        RAND
    };

private:
    unsigned int lineno;
    std::string bufferName;
    static std::string nullBufferName;
    enum type op;
    statementPtr lhs;
    statementPtr rhs;

    struct pair
    {
        unsigned int first;
        unsigned int second;
    } pair{};
    featuresPtr features;
    valuePtr value;
    bitsetPtr bitset;
    std::string str;
    arithmetic_op fct;
    pairpPtr pairp;
    statementsPtr statements;
    double number;

public:
    Statement(unsigned int lineno, std::string , type op, std::string str);

    Statement(unsigned int, std::string , type, bitsetPtr, statementPtr = statementPtr());

    Statement(unsigned int, std::string , type op, statementPtr = statementPtr(), statementPtr = statementPtr(),
              unsigned int = UINT_MAX, unsigned int = UINT_MAX,
              featuresPtr = featuresPtr(), bitsetPtr = bitsetPtr(), arithmetic_op = NOP,
              pairpPtr = pairpPtr(), statementsPtr = statementsPtr(), double = 0.0);

    Statement(unsigned int, std::string bufferName, type op, valuePtr value);

    void makeSerialString();

public:
    ~Statement();

    static statementPtr create(unsigned int lineno, std::string bufferName, type op, statementPtr lhs = statementPtr(),
                               statementPtr rhs = statementPtr());

    static statementPtr create(unsigned int lineno, std::string bufferName, type op, unsigned int first,
                               unsigned int second = UINT_MAX);

    static statementPtr create(unsigned int lineno, std::string bufferName, type op, unsigned int first,
                               statementPtr lhs);

    static statementPtr create(unsigned int lineno, std::string bufferName, type op, featuresPtr features);

    static statementPtr create(unsigned int lineno, std::string bufferName, type op, valuePtr &value);

    static statementPtr create(unsigned int lineno, std::string bufferName, type op, bitsetPtr bits, statementPtr lhs = statementPtr());

    static statementPtr create(unsigned int lineno, std::string bufferName, type op, std::string str);

    static statementPtr create(unsigned int lineno, std::string bufferName, type op, arithmetic_op fct,
                               statementPtr lhs = statementPtr(),
                               statementPtr rhs = statementPtr());

    static statementPtr create(unsigned int lineno, std::string bufferName, type op, pairpPtr);

    static statementPtr create(unsigned int lineno, std::string bufferName, type op, statementsPtr);

    static statementPtr create(unsigned int lineno, std::string bufferName, type op, double);

    static statementPtr create();

    bool isAff() const;

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

    bool isStms() const;

    bool isStr() const;

    bool isPairp() const;

    bool isNumber() const;

    bool isFct() const;

    bool isSearch() const;

    arithmetic_op getFct() const;

    statementPtr getLhs() const;

    statementPtr getRhs() const;

    featuresPtr getFeatures() const;

    bitsetPtr getBits() const;

    unsigned int getFirst() const;

    unsigned int getSecond() const;

    std::string getStr() const;

    pairpPtr getPairp() const;

    statementsPtr getStatements() const;

    double getNumber() const;

    unsigned int getLineno() const;

    void print(std::ostream &, unsigned int tabulation = 0, int yetColored = 0) const;

    featuresPtr evalFeatures(class Item *, class Parser &, class Synthesizer *, bool);

    pairpPtr evalPairp(class Item *, bool);

    valuePtr evalValue(class Item *, Parser &, Synthesizer *, bool);

    listFeaturesPtr evalListFeatures(class Item *, Parser &, Synthesizer *, bool);

    featuresPtr unif(const featuresPtr &, const featuresPtr &, class Item *);

    statementPtr clone(const std::bitset<FLAGS> &savedFlags = std::bitset<FLAGS>());

    void buildInheritedSonFeatures(class Item *, Parser &, Synthesizer *synthesizer);

    void buildSynthesizedFeatures(class Item *, Parser &, Synthesizer *synthesizer);

    void buildEnvironmentWithInherited(class Item *, Parser &, Synthesizer *synthesizer);

    void buildEnvironmentWithSynthesize(class Item *, Parser &, Synthesizer *synthesizer);

    void buildEnvironmentWithValue(class Item *, Parser &, Synthesizer *);

    void stmAttest(class Item *, class Parser &, class Synthesizer *);

    void stmGuard(class Item *);

    void stmForeach(class Item *item, class Parser &, class Synthesizer *, bool &);

    void stmIf(class Item *item, class Parser &, class Synthesizer *, bool &);

    void stmPrint(class Item *, class Parser &, class Synthesizer *);

    void stmPrintln(class Item *, class Parser &, class Synthesizer *);

    void renameVariables(size_t);

    void enable(const statementPtr &, class Item *, class Synthesizer *, bool &, bool);

    void apply(class Item *, class Parser &, class Synthesizer *, bool &);

    void lookingForAssignedInheritedSonFeatures(std::vector<bool> &);

    bool findVariable(const bitsetPtr &);
};

#endif // ELVEX_STATEMENT_H
