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

#ifndef LIST_H
#define LIST_H

#include "flags.hh"
#include "id.hh"
#include "vartable.hh"
#include "serializable.hh"
#include "ipointer.hh"

class List:
  public std::enable_shared_from_this< List >,
  public Serializable,
  public Flags,
  public Id {
  
public:
  enum Type {ATOM, PAIRP, NIL};
  static listPtr nil;

private:
  static bitsetPtr gwith;
  enum Type type;
  valuePtr value;
  struct {
    listPtr car;
    listPtr cdr;
  } pairp;

  List (enum Type type, valuePtr value=valuePtr(), listPtr car=listPtr(), listPtr cdr=listPtr());

  static listPtr create(void);
  void makeSerialString(void);

public:
  ~List();
  static listPtr create(valuePtr value);
  static listPtr create(listPtr car, listPtr cdr);

  Type getType(void) const;
  valuePtr getValue(void) const;
  void setValue(valuePtr value);
  listPtr car(void) const;
  listPtr cdr(void) const;
  listPtr cadr(void) const;
  listPtr cddr(void) const;
  listPtr caar(void) const;
  listPtr cdar(void) const;
  bool isNil(void) const;
  bool isAtom(void) const;
  bool isPairp(void) const;

  bitsetPtr getBits(void) const;
  featuresPtr getfeaturePtrs(void) const;
  unsigned int getIdentifier(void) const;

  void print(std::ostream &) const;
  void flatPrint(std::ostream &, bool par) const;
  bool buildEnvironment(environmentPtr, listPtr , bool, bool);
  void deleteAnonymousVariables(void);
  bool renameVariables(unsigned int);
  void apply(itemPtr item, class Synthesizer *synthesizer, bool &result, bool &effect, bool trace, statementPtr variable, statementPtr body);
#ifdef OUTPUT_XML
  void toXML(xmlNodePtr);
#endif
  listPtr clone(void) const;
  void enable(statementPtr, itemPtr, bool &, bool);
  bool subsumes(listPtr , environmentPtr );

  listPtr pushFront(valuePtr value);
  listPtr pushBack(valuePtr value);
  bool findVariable(bitsetPtr);
};

#endif // LIST_H
