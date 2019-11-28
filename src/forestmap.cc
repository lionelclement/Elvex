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

#include "forestmap.hh"
#include "messages.hh"

int ForestMap::nb = 0;

/* **************************************************
 *
 ************************************************** */
ForestMap::ForestMap() {
   NEW;
}

/* **************************************************
 *
 ************************************************** */
ForestMap::~ForestMap() {
   DELETE;
   for (map::iterator i = data.begin(); i != data.end(); ++i) {
      forestPtr tmp = i->second;
      if (tmp)
         tmp.reset();
   }
}

/* **************************************************
 *
 ************************************************** */
const ForestMap::map::const_iterator ForestMap::find(forestIdentifierPtr forestIdentifier) const {
   return data.find(forestIdentifier);
}

/* **************************************************
 *
 ************************************************** */
const ForestMap::map::const_iterator ForestMap::begin(void) const {
   return data.begin();
}

/* **************************************************
 *
 ************************************************** */
const ForestMap::map::const_iterator ForestMap::end(void) const {
   return data.end();
}

/* **************************************************
 *
 ************************************************** */
void ForestMap::clear(void) {
   return data.clear();
}

/* **************************************************
 *
 ************************************************** */
const bool ForestMap::insert(ForestMap::pair pair) {
   return data.insert(pair).second;
}

