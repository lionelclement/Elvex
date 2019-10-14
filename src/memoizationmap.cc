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

#include <iostream>
#include "memoizationmap.hh"
#include "features.hh"
#include "forestidentifier.hh"
#include "messages.hh"

/* ************************************************************
 * 
 ************************************************************ */
MemoizationMap::unordered_map::const_iterator
MemoizationMap::find(std::string const key) const
{
  auto memItem = map.find(key);
#ifdef TRACE_MEMOIZATION
  if (memItem != map.end()) {
    std::cout << "<H3>####################### RECORDED SHIFT FOUND #######################</H3>" << std::endl;
    std::cout << "<BR>";
    std::cout << std::endl;
  }
#endif
  return memItem;
}

/* ************************************************************
 * 
 ************************************************************ */
MemoizationMap::unordered_map::const_iterator
MemoizationMap::end(void) const
{
  return map.end();
}

/* ************************************************************
 * 
 ************************************************************ */
void MemoizationMap::insert(std::string const key, featuresPtr features, forestIdentifierPtr forestIdentifier)
{
#ifdef TRACE_MEMOIZATION
  std::cout << "<H3>####################### RECORD SHIFT #######################</H3>" << std::endl;
  std::cout << "<BR>";
  std::cout << std::endl;
#endif
  memoizationValuePtr value = MemoizationValue::create(features, forestIdentifier);
  auto memItem = map.find(key);
  if (memItem != map.end()) {
    memItem->second.push_back(value);
  }
  else {
    std::list< memoizationValuePtr > values;
    values.push_back(value);
    map[key] = values;
    }
}

