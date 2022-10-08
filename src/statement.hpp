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

#ifndef ELVEX_STATEMENT_H
#define ELVEX_STATEMENT_H

#include <climits>
#include <vector>
#include "flags.hpp"
#include "shared_ptr.hpp"
#include "serializable.hpp"
#include "application.hpp"

#define FATAL_ERROR_STM {FATAL_ERROR("*** fatal error with statement line " << getLineno());}
#define FATAL_ERROR_MSG_STM(msg) {FATAL_ERROR("*** fatal error: " << msg << " with statement line " << getLineno());}
#define WARNING_STM {CERR_LINE; std::ostringstream oss; oss << "*** warning with statement line " << getLineno(); std::cerr << oss.str() << std::endl;}

class Statement :
        public Flags, public Serializable, public std::enable_shared_from_this<class Statement> {

public:
    enum type {
        DASH,
        AFF,
        SUBSUME,
        INSET,
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
        LIST,
        NUMBER,
        FCT,
        SEARCH,
        FINISHED
    };

    enum arithmetic_op {
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
    enum type op;
    statementPtr lhs;
    statementPtr rhs;

    struct pair {
        unsigned int first;
        unsigned int second;
    } pair{};
    featuresPtr features;
    valuePtr value;
    bitsetPtr bitset;
    std::string str;
    arithmetic_op fct;
    listPtr list;
    statementsPtr statements;
    double number;

public:
    Statement(unsigned int, type, std::string);

    Statement(unsigned int, type op, bitsetPtr bits, statementPtr lhs = statementPtr());

    Statement(unsigned int, type op = FINISHED, statementPtr lhs = statementPtr(), statementPtr rhs = statementPtr(),
              unsigned int first = UINT_MAX, unsigned int second = UINT_MAX,
              featuresPtr features = featuresPtr(), bitsetPtr bits = bitsetPtr(), arithmetic_op fct = NOP,
              listPtr list = listPtr(), statementsPtr stms = statementsPtr(), double = 0.0);

    Statement(unsigned int, type op, valuePtr value);

    void makeSerialString();

public:
    ~Statement();

    static statementPtr
    create(unsigned int lineno, type op, statementPtr lhs = statementPtr(), statementPtr rhs = statementPtr());

    static statementPtr create(unsigned int lineno, type op, unsigned int first, unsigned int second = UINT_MAX);

    static statementPtr create(unsigned int lineno, type op, featuresPtr features);

    static statementPtr create(unsigned int lineno, type op, valuePtr& value);

    static statementPtr create(unsigned int lineno, type op, bitsetPtr bits, statementPtr lhs = statementPtr());

    static statementPtr create(unsigned int lineno, type op, std::string str);

    static statementPtr create(unsigned int lineno, type op, arithmetic_op fct, statementPtr lhs = statementPtr(),
                               statementPtr rhs = statementPtr());

    static statementPtr create(unsigned int lineno, type op, listPtr);

    static statementPtr create(unsigned int lineno, type op, statementsPtr);

    static statementPtr create(unsigned int lineno, type op, double);

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

    bool isList() const;

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

    listPtr getList() const;

    statementsPtr getStatements() const;

    double getNumber() const;

    unsigned int getLineno() const;

    void print(std::ostream& , unsigned int tabulation = 0, int yetColored = 0) const;

    featuresPtr evalFeatures(const itemPtr&, class Application* application, bool);

    listPtr evalList(const itemPtr&, bool);

    valuePtr evalValue(const itemPtr& item, Application* application, bool replaceVariables);

    featuresPtr unif(const featuresPtr&, const featuresPtr&, const itemPtr&);

    statementPtr clone(const std::bitset<FLAGS>& savedFlags = std::bitset<FLAGS>());

    void buildInheritedSonFeatures(const itemPtr& item, Application* application);

    void buildSynthesizedFeatures(const itemPtr& item, Application* application);

    void buildEnvironmentWithInherited(const itemPtr& item, Application* application);

    void buildEnvironmentWithSynthesize(const itemPtr& item, Application* application);

    void buildEnvironmentWithValue(const itemPtr& item, Application* application);

    void stmAttest(const itemPtr&, class Application* application);

    void stmGuard(const itemPtr&/**/);

    void stmForeach(const itemPtr& item, class Application* application, bool& effect);

    void stmIf(const itemPtr& item, class Application* application, bool& effect);

    void stmPrint(const itemPtr&, class Application* application);

    void stmPrintln(const itemPtr&, class Application* application);

    void renameVariables(size_t);

  void enable(const statementPtr& root, const itemPtr& item, Application* application, bool& effect, bool on);

    void apply(const itemPtr& item, class Application* application, bool& effect);

    void lookingForAssignedInheritedSonFeatures(std::vector<bool>& );

    bool findVariable(const bitsetPtr&);

};

#endif // ELVEX_STATEMENT_H
