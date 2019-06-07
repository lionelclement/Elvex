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

#ifndef FEATURE_H
#define FEATURE_H

#include "flags.hh"
#include "id.hh"

#include "vartable.hh"
#include "ipointer.hh"
#include "serializable.hh"

  class Feature:
  public Id,
  public Flags,
  public Serializable,
  public enable_shared_from_this< class Feature > {
  
 public:
  enum Type {
    PRED=0,
    CONSTANT,
    FORM,
    VARIABLE,
  };
  
  static const Type first_type = PRED;
  static const Type last_type = VARIABLE;

 private:
  enum Type type;
  bitsetPtr attribute; // variable ou constante
  valuePtr value;
  Feature(Type, bitsetPtr, valuePtr );
  void setId(idType);
  const std::string makeSerializationId(void);

 public:
  ~Feature();
  static featurePtr create(enum Type type=CONSTANT, bitsetPtr attribute=bitsetPtr(), valuePtr value=valuePtr());

  const bitsetPtr getAttribute(void) const;
  void setAttribute(const bitsetPtr);
  const valuePtr getValue(void) const;
  void setValue(const valuePtr );
  const Type getType(void) const;
  void setType(const enum Type);

  std::string attributeToString(void) const;

  featurePtr clone(void);
  void print(std::ostream &, bool flat=false) const;
  
#ifdef OUTPUT_XML
  void toXML(xmlNodePtr nodeRoot);
#endif
  const bool renameVariables(const unsigned int);
  void enable(statementPtr, itemPtr, bool &, bool);
  const bool findVariable(const bitsetPtr) const;
  
};

#endif // FEATURE_H
