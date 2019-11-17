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

#ifndef PATTERN_H
#define PATTERN_H

#include <string>
#include <list>
#include <unordered_map>

class Pattern {
  
public:
  typedef std::unordered_map<const std::string, std::list<const std::string> *, std::hash<std::string>, std::equal_to<std::string>, std::allocator< std::pair<const std::string, std::list<const std::string> *> >> Unordered_map;
  Unordered_map unordered_map;
  static std::list<const std::string> *emptyList;

  Pattern(void);
  void add(const std::string key, const std::string value);
  std::list<const std::string> *find(const std::string key);
  std::string &toString(void) const;
  
};

#endif // PATTERN_H

