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

#ifndef FORESTMAP_H
#define FORESTMAP_H

#include <map>

#include "forestidentifier.hh"
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class ForestMap {

public:
  typedef std::map<const forestIdentifierPtr, forestPtr, ForestIdentifier::Less> mapForestIdentifierForest;
  typedef std::pair<const forestIdentifierPtr, forestPtr> pairForestIdentifierForest;

private:
  mapForestIdentifierForest data;

public:
  ForestMap(void);
  ~ForestMap();

  mapForestIdentifierForest::const_iterator find(const forestIdentifierPtr);
  mapForestIdentifierForest::const_iterator begin(void) const;
  mapForestIdentifierForest::const_iterator end(void) const;
  void clear(void);
  bool insert (pairForestIdentifierForest);

};
#endif // FORESTMAP_H
