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

#include <iostream>
#include "memoizationmap.hh"
#include "features.hh"
#include "forestidentifier.hh"

/* ************************************************************
 * 
 ************************************************************ */
std::map<std::string, std::list< memoizationValuePtr > >::iterator
MemoizationMap::find(const std::string key)
{
  auto memItem = map.find(key);
#ifdef TRACE_MEMOIZATION
  if (memItem != map.end()) {
    std::cerr << "<H3>####################### RECORDED SHIFT FOUND #######################</H3>" << std::endl;
    std::cerr << "<BR>";
    std::cerr << std::endl;
  }
#endif
  return memItem;
}

/* ************************************************************
 * 
 ************************************************************ */
std::map<std::string, std::list< memoizationValuePtr > >::iterator
MemoizationMap::end(void) 
{
  return map.end();
}

/* ************************************************************
 * 
 ************************************************************ */
void MemoizationMap::insert(const std::string key, featuresPtr features, forestIdentifierPtr forestIdentifier)
{
#ifdef TRACE_MEMOIZATION
  std::cerr << "<H3>####################### RECORD SHIFT #######################</H3>" << std::endl;
  std::cerr << "<BR>";
  std::cerr << std::endl;
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
