/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2020 LABRI, 
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

#ifndef ELVEX_LISTFEATURES_H
#define ELVEX_LISTFEATURES_H

#include <vector>
#include "shared_ptr.h"
#include "flags.h"
#include "id.h"

class ListFeatures :
        public Id, public Flags, public std::enable_shared_from_this<class ListFeatures> {

public:
    typedef std::vector<featuresPtr> featuresVector;

private:
    featuresVector listFeatures;

    ListFeatures(void);

public:
    ~ListFeatures();

    static listFeaturesPtr create(void);

    void push_back(featuresPtr);

    void add(unsigned int, featuresPtr);

    void clear(void);

    featuresVector::const_iterator begin(void) const;

    featuresVector::const_iterator end(void) const;

    size_t size() const;

    listFeaturesPtr clone(void);

    featuresPtr operator[](unsigned int);
};

#endif // ELVEX_LISTFEATURES_H
