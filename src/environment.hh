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

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <bitset>
#include <map>
#include <vector>
#include "vartable.hh"
#include "ipointer.hh"

class Environment: 
  public enable_shared_from_this< class Environment > {

private:
  Environment();
  
public:
  ~Environment();
  static environmentPtr create(void);

  typedef std::map< const std::string, valuePtr > mapStringValue;
  
private:
  mapStringValue env;
  void add(const std::string, valuePtr=valuePtr());
  
public:
  void add(bitsetPtr, valuePtr=valuePtr());
  void add(environmentPtr);
  void add(environmentPtr, environmentPtr);
  mapStringValue::const_iterator begin() const;
  mapStringValue::const_iterator end() const;
  const size_t size() const;
  
  void print(std::ostream &) const;
  environmentPtr clone(void);
  valuePtr find(bitsetPtr) const;
  valuePtr replaceVariables(valuePtr, bool &);
  std::string replaceVariables(std::string, bool &);
  void replaceVariables(featuresPtr, bool &);
  void replaceVariables(listFeaturesPtr, bool &);
  void replaceVariables(listPtr, bool &);
};
#endif // ENVIRONMENT_H
