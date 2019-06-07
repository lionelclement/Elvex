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

#include "forestmap.hh"
#include "messages.hh"

/* **************************************************
 *
 ************************************************** */
ForestMap::ForestMap()
{
  NEW;
}

/* **************************************************
 *
 ************************************************** */
ForestMap::~ForestMap()
{
  for (mapForestIdentifierForest::iterator i=data.begin();
       i!=data.end(); ++i){
    forestPtr tmp = i->second;
    if (tmp)
      tmp.reset();
  }
  DELETE;
}

/* **************************************************
 *
 ************************************************** */
ForestMap::mapForestIdentifierForest::const_iterator ForestMap::find(forestIdentifierPtr forestIdentifier)
{
  return data.find(forestIdentifier);
}

/* **************************************************
 *
 ************************************************** */
ForestMap::mapForestIdentifierForest::const_iterator ForestMap::begin(void) const
{
  return data.begin();
}

/* **************************************************
 *
 ************************************************** */
ForestMap::mapForestIdentifierForest::const_iterator ForestMap::end(void) const
{
  return data.end();
}

/* **************************************************
 *
 ************************************************** */
void ForestMap::clear(void)
{
  return data.clear();
}

/* **************************************************
 *
 ************************************************** */
bool ForestMap::insert (ForestMap::pairForestIdentifierForest pair)
{
  return data.insert(pair).second;
}

