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

#ifndef LISTFEATURES_H
#define LISTFEATURES_H

#include <vector>

#include "ipointer.hh"
#include "flags.hh"
#include "id.hh"

class ListFeatures:
  public Id,
  public Flags,
  public enable_shared_from_this< class ListFeatures > {
  
 private:
  std::vector< featuresPtr > listFeatures;
  ListFeatures(void);
  void setId(idType);
  
 public:
  ~ListFeatures();
  static listFeaturesPtr create(void);
  void push_back( featuresPtr );
  void add(unsigned int, featuresPtr);
  void clear(void);
  std::vector< featuresPtr >::const_iterator begin(void) const;
  std::vector< featuresPtr >::const_iterator end(void) const;
  unsigned int size() const;
  listFeaturesPtr clone(void);
  featuresPtr operator[](unsigned int);
};

#endif // LISTFEATURES_H
