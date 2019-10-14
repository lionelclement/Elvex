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

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <bitset>
#include <unordered_map>
#include <vector>
#include "vartable.hh"
#include "ipointer.hh"

class Environment: 
  public std::enable_shared_from_this< class Environment > {

public:
  typedef std::unordered_map< std::string const, valuePtr, std::hash<std::string>, std::equal_to<std::string> > unordered_map;
  
private:
  Environment();
  
private:
  unordered_map env;
  void add(std::string const, valuePtr=valuePtr());
  void remove(std::string const);

public:
  ~Environment();
  static environmentPtr create(void);

  void add(const bitsetPtr, valuePtr=valuePtr());
  void add(const environmentPtr);
  void add(const environmentPtr, const environmentPtr);
  void remove(const bitsetPtr);
  unordered_map::const_iterator begin() const;
  unordered_map::const_iterator end() const;
  const size_t size() const;
  
  void print(std::ostream &) const;
  environmentPtr clone(void) const;
  valuePtr find(bitsetPtr) const;
  valuePtr replaceVariables(valuePtr, bool &);
  void replaceVariables(featuresPtr, bool &);
  void replaceVariables(listFeaturesPtr, bool &);
  void replaceVariables(listPtr, bool &);
  std::string replaceVariables(const std::string, bool &);
};
#endif // ENVIRONMENT_H
