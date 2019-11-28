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

#ifndef LISTFEATURES_H
#define LISTFEATURES_H

#include <vector>
#include "ipointer.hh"
#include "flags.hh"
#include "id.hh"

class ListFeatures:
      public Id, public Flags, public std::enable_shared_from_this<class ListFeatures> {

public:
   typedef std::vector<featuresPtr> vector;

private:
   vector listFeatures;
   ListFeatures(void);

public:
   ~ListFeatures();
   static listFeaturesPtr create(void);
   void push_back(featuresPtr);
   void add(unsigned int, featuresPtr);
   void clear(void);
   vector::const_iterator begin(void) const;
   vector::const_iterator end(void) const;
   size_t size() const;
   listFeaturesPtr clone(void);
   featuresPtr operator[](unsigned int);
};

#endif // LISTFEATURES_H
