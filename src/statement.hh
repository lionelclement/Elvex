/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: Lionel Clément,
 * Labri -- 351, cours de la Libération
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
#include "id.hh"
#include "vartable.hh"
#include "ipointer.hh"
#include "serializable.hh"

  #define FATAL_ERROR_STM {std::ostringstream oss; oss << "fatal error with statement line " << getLineno(); FATAL_ERROR;}
#define WARNING_STM {CERR_LINE; std::ostringstream oss; oss << "warning with statement line " << getLineno(); std::cerr << oss.str() << std::endl;}

class Statement:
  public Flags,
  public Serializable,
  public enable_shared_from_this< class Statement > {
  
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
    STMS,
    STR,
    LIST,
    SORT,
    REVERSE,
    DOUBLE,
    FCT,
    FINISHED
  };

  enum arithmetic_op {
    NOP, NOT, AND, OR, DIFF, EQ, LT, LE, GT, GE, PLUS, MINUS, TIMES, DIVIDE, MODULO, MINUS_U, RAND
    // Here arithmetic functions
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
  Statement (unsigned int, type op, std::string str);
  Statement (unsigned int, type op=FINISHED, statementPtr lhs=statementPtr(), statementPtr rhs=statementPtr(), unsigned int first=UINT_MAX, unsigned int second=UINT_MAX, featuresPtr features=featuresPtr(), bitsetPtr bits=bitsetPtr(), arithmetic_op fct=NOP, listPtr list=listPtr(), statementsPtr stms=statementsPtr(), double=0.0);
  const std::string makeSerializationId(void);
  
public:
  ~Statement ();
  static statementPtr create (unsigned int lineno, type op, statementPtr lhs=statementPtr(), statementPtr rhs=statementPtr());
  static statementPtr create (unsigned int lineno, type op, unsigned int first, unsigned int second=UINT_MAX);
  static statementPtr create (unsigned int lineno, type op, featuresPtr features);
  static statementPtr create (unsigned int lineno, type op, valuePtr value);
  static statementPtr create (unsigned int lineno, type op, bitsetPtr bits);
  static statementPtr create (unsigned int lineno, type op, std::string str);
  static statementPtr create (unsigned int lineno, type op, arithmetic_op fct, statementPtr lhs=statementPtr(), statementPtr rhs=statementPtr());
  static statementPtr create (unsigned int lineno, type op, listPtr );
  static statementPtr create (unsigned int lineno, type op, statementsPtr );
  static statementPtr create (unsigned int lineno, type op, double);
  static statementPtr create ();

  type getOp(void) const;
  arithmetic_op getFct(void) const;
  statementPtr getLhs(void) const;
  statementPtr getRhs(void) const;
  featuresPtr getFeatures(void) const;
  bitsetPtr getBits(void) const;
  unsigned int getFirst(void) const;
  unsigned int getSecond(void) const;
  std::string getStr(void) const;
  listPtr getList(void) const;
  statementsPtr getStatements(void) const;
  double getNumber(void) const;
  int getLineno(void) const;
  void print(std::ostream &, int=0) const;
  featuresPtr evalFeatures(itemPtr, bool);
  listPtr evalList(itemPtr, bool);
  valuePtr evalValue(itemPtr, bool);
  featuresPtr unif(featuresPtr, featuresPtr, itemPtr);
  statementPtr clone(const std::bitset<NBRFLAGS> &savedFlags);
  void buildInheritedSonFeatures(itemPtr, bool &);
  void buildSynthesizedFeatures(itemPtr, bool &);
  void buildEnvironmentWithInherited(itemPtr, bool &);
  void buildEnvironmentWithSynthesize(itemPtr, bool &);
  void buildEnvironmentWithValue(itemPtr, bool &);
  void attest(itemPtr, bool &);
  void guard(itemPtr, bool &, bool);
  void stmPrint(itemPtr);
  void stmPrintln(itemPtr);
  void renameVariables(unsigned int);
  void enable(statementPtr, itemPtr, bool&, bool);
  void apply(itemPtr, bool &, bool &, bool);
  void lookingForAssignedInheritedSonFeatures(std::vector< bool > &);
  bool findVariable(bitsetPtr);

}; 

#endif // STATEMENT_H
