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

#ifndef VALUE_H
#define VALUE_H

#include "flags.hh"
#include "id.hh"
#include "vartable.hh"
#include "ipointer.hh"
#include "serializable.hh"

class Value:
  public Id,
  public Flags,
  public Serializable,
  public std::enable_shared_from_this< class Value > {
  
public:
  enum Type {
    BOOL,
    CONSTANT,
    VARIABLE,
    ANONYMOUS,
    IDENTIFIER,
    FEATURES,
    LIST,
    DOUBLE,
    STR
  };

private:
  bitsetPtr bits; // pour encoder les constantes et les variables
  unsigned int integer; // pour encoder les identifiers
  listPtr list;
  std::string str;
  double number;

public:
  static valuePtr NIL_VALUE;
  static valuePtr ANONYMOUS_VALUE;
  static valuePtr TRUE_VALUE;

  Type type;
  featuresPtr features; // pour encoder les SF

private:
  Value(const enum Type, std::string);
  Value(const enum Type, unsigned int=0, double=0.0, bitsetPtr bitset=bitsetPtr(), featuresPtr=featuresPtr(), listPtr lst=listPtr());
  void makeSerialString(void);

public:
  ~Value();
  static valuePtr create(const enum Type);
  static valuePtr create(const enum Type, double);
  static valuePtr create(const enum Type, unsigned int);
  static valuePtr create(const enum Type, std::string);
  static valuePtr create(const enum Type, bitsetPtr);
  static valuePtr create(const enum Type, featuresPtr);
  static valuePtr create(const enum Type, class Set *);
  static valuePtr create(const enum Type, listPtr );

  Type getType(void) const;
  bitsetPtr getBits(void) const;
  unsigned int getIdentifier(void) const;
  featuresPtr getFeatures(void) const;
  double getDouble(void) const;
  std::string getStr(void) const;
  listPtr getList(void) const;

  void print(std::ostream&) const;
  void flatPrint(std::ostream&) const;
  #ifdef OUTPUT_XML
  void toXML(xmlNodePtr) const;
#endif
  bool buildEnvironment(environmentPtr , valuePtr , bool, bool);
  bool subsumes(valuePtr , environmentPtr );
  valuePtr clone(void);
  void deleteAnonymousVariables(void);
  bool renameVariables(unsigned int);
  bool isNil(void) const;
  bool isFalse(void) const;
  bool isTrue(void) const;
  bool isAnonymous(void) const;
  bool isDouble(void) const;
  bool isStr(void) const;
  bool isVariable(void) const;
  bool isIdentifier(void) const;
  bool isFeatures(void) const;
  bool isConstant(void) const;
  bool isList(void) const;
  void enable(statementPtr, itemPtr, bool &, bool);
  bool eq(valuePtr ) const;
  bool lt(valuePtr ) const;
  bool findVariable(bitsetPtr);
  void apply(itemPtr item, class Synthesizer *synthesizer, bool trace, statementPtr variable, statementPtr body);
  bool containsVariable(void) const;
};

#endif // VALUE_H
