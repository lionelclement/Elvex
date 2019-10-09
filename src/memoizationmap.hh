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

#ifndef MEMOIZATIONMAP_H
#define MEMOIZATIONMAP_H

#include "memoizationvalue.hh"
#include "ipointer.hh"
#include <list>
#include <map>
#include <string>

class MemoizationMap:
  public std::enable_shared_from_this< class MemoizationMap > {
  
private:
  std::map<std::string, std::list< memoizationValuePtr > > map;

public:
  std::map<std::string, std::list< memoizationValuePtr > >::const_iterator end(void) const;
  std::map<std::string, std::list< memoizationValuePtr > >::const_iterator find(const std::string) const;
  void insert(std::string, featuresPtr, forestIdentifierPtr);
  
};  
#endif // MEMOIZATIONMAP_H
