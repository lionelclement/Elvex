/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2018 LABRI, 
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

/* ************************************************************
 * 
 ************************************************************ */
std::map<std::string, std::list< memoizationValuePtr > >::iterator
MemoizationMap::find(const std::string key)
{
  auto memItem = map.find(key);
  if (memItem != map.end()) {
#ifdef TRACE_MEMOIZATION
    std::cerr << "####################### RECORDED SHIFT FOUND " << key << " #######################" << std::endl;
    std::cerr << "<BR>";
    std::cerr << std::endl;
#endif
  }
  return memItem;
}

/* ************************************************************
 * 
 ************************************************************ */
// std::map<std::string, std::list< memoizationValuePtr > >::iterator MemoizationMap::begin() const
// {
//   return memoizationMap.begin();
// }


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
void MemoizationMap::insert(const std::string key, std::list< memoizationValuePtr > &values)
{
#ifdef TRACE_MEMOIZATION
  std::cerr << "####################### RECORD SHIFT " << key << " #######################" << std::endl;
  std::cerr << "<BR>";
  std::cerr << std::endl;
#endif
  map[key] = values;
}
