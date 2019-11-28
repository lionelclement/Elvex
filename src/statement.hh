/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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

#ifndef STATEMENT_H
#define STATEMENT_H

#include <climits>
#include <vector>
#include "flags.hh"
#include "ipointer.hh"
#include "serializable.hh"
#include "synthesizer.hh"

#define FATAL_ERROR_STM {std::ostringstream oss; oss << "*** fatal error with statement line " << getLineno(); throw oss.str();}
#define FATAL_ERROR_MSG_STM(msg) {std::ostringstream oss; oss << "*** fatal error: " << msg << " with statement line " << getLineno(); throw oss.str();}
#define WARNING_STM {CERR_LINE; std::ostringstream oss; oss << "*** warning with statement line " << getLineno(); std::cerr << oss.str() << std::endl;}

class Statement:
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
      NOT_NIL,
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
      DOUBLE,
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
   } pair;
   featuresPtr features;
   bitsetPtr bits;
   std::string str;
   arithmetic_op fct;
   listPtr list;
   statementsPtr statements;
   double number;

private:
   Statement(unsigned int, type op, std::string str);
   Statement(unsigned int, type op, bitsetPtr bits, statementPtr lhs = statementPtr());
   Statement(unsigned int, type op = FINISHED, statementPtr lhs = statementPtr(), statementPtr rhs = statementPtr(), unsigned int first = UINT_MAX, unsigned int second = UINT_MAX,
         featuresPtr features = featuresPtr(), bitsetPtr bits = bitsetPtr(), arithmetic_op fct = NOP, listPtr list = listPtr(), statementsPtr stms = statementsPtr(), double = 0.0);
   void makeSerialString(void);

public:
   ~Statement();
   static statementPtr create(unsigned int lineno, type op, statementPtr lhs = statementPtr(), statementPtr rhs = statementPtr());
   static statementPtr create(unsigned int lineno, type op, unsigned int first, unsigned int second = UINT_MAX);
   static statementPtr create(unsigned int lineno, type op, featuresPtr features);
   static statementPtr create(unsigned int lineno, type op, valuePtr value);
   static statementPtr create(unsigned int lineno, type op, bitsetPtr bits, statementPtr lhs = statementPtr());
   static statementPtr create(unsigned int lineno, type op, std::string str);
   static statementPtr create(unsigned int lineno, type op, arithmetic_op fct, statementPtr lhs = statementPtr(), statementPtr rhs = statementPtr());
   static statementPtr create(unsigned int lineno, type op, listPtr);
   static statementPtr create(unsigned int lineno, type op, statementsPtr);
   static statementPtr create(unsigned int lineno, type op, double);
   static statementPtr create();

   const bool isAff(void) const;
   const bool isSubsume(void) const;
   const bool isUp(void) const;
   const bool isUp2(void) const;
   const bool isDown(void) const;
   const bool isDown2(void) const;
   const bool isFeatures(void) const;
   const bool isVariable(void) const;
   const bool isConstant(void) const;
   const bool isUnif(void) const;
   const bool isGuard(void) const;
   const bool isPrint(void) const;
   const bool isPrintln(void) const;
   const bool isAttest(void) const;
   const bool isIf(void) const;
   const bool isForeach(void) const;
   const bool isStms(void) const;
   const bool isStr(void) const;
   const bool isList(void) const;
   const bool isDouble(void) const;
   const bool isFct(void) const;
   const bool isSearch(void) const;

   const arithmetic_op getFct(void) const;
   const statementPtr getLhs(void) const;
   const statementPtr getRhs(void) const;
   const featuresPtr getFeatures(void) const;
   const bitsetPtr getBits(void) const;
   const unsigned int getFirst(void) const;
   const unsigned int getSecond(void) const;
   const std::string getStr(void) const;
   const listPtr getList(void) const;
   const statementsPtr getStatements(void) const;
   const double getNumber(void) const;
   const unsigned int getLineno(void) const;

   void print(std::ostream &, unsigned int tabulation = 0, int yetColored = 0) const;
   featuresPtr evalFeatures(itemPtr, class Parser &parser, class Synthesizer *synthesizer, bool);
   listPtr evalList(itemPtr, bool);
   valuePtr evalValue(itemPtr item, Parser &parser, Synthesizer *synthesizer, bool replaceVariables);
   featuresPtr unif(featuresPtr, featuresPtr, itemPtr);
   statementPtr clone(const std::bitset<Flags::FLAGS> &savedFlags = std::bitset<Flags::FLAGS>());
   void buildInheritedSonFeatures(itemPtr item, Parser &parser, Synthesizer *synthesizer);
   void buildSynthesizedFeatures(itemPtr item, Parser &parser, Synthesizer *synthesizer);
   void buildEnvironmentWithInherited(itemPtr item, Parser &parser, Synthesizer *synthesizer);
   void buildEnvironmentWithSynthesize(itemPtr item, Parser &parser, Synthesizer *synthesizer);
   void buildEnvironmentWithValue(itemPtr item, Parser &parser, Synthesizer *synthesizer);
   void stmAttest(itemPtr, class Parser &parser, class Synthesizer *synthesizer);
   void stmGuard(itemPtr, class Synthesizer *synthesizer);
   void stmForeach(itemPtr item, class Parser &parser, class Synthesizer *synthesizer);
   void stmIf(itemPtr item, class Parser &parser, class Synthesizer *synthesizer);
   void stmPrint(itemPtr, class Parser &parser, class Synthesizer *synthesizer);
   void stmPrintln(itemPtr, class Parser &parser, class Synthesizer *synthesizer);
   void _renameVariables(size_t);
   void enable(statementPtr root, itemPtr item, class Synthesizer *synthesizer, bool &effect, bool on);
   void apply(itemPtr item, class Parser &parser, class Synthesizer *synthesizer);
   void lookingForAssignedInheritedSonFeatures(std::vector<bool> &);
   const bool findVariable(bitsetPtr);

};

#endif // STATEMENT_H
