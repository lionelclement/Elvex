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

#ifndef ELVEX_MEMOIZATIONVALUE_H
#define ELVEX_MEMOIZATIONVALUE_H

#include "shared_ptr.h"

class MemoizationValue :
        public std::enable_shared_from_this<class MemoizationValue> {

private:
    featuresPtr features;
    forestIdentifierPtr forestIdentifier;

    MemoizationValue(featuresPtr, forestIdentifierPtr);

public:
    ~MemoizationValue();

    static memoizationValuePtr create(featuresPtr, forestIdentifierPtr);

    featuresPtr getFeatures(void) const;

    forestIdentifierPtr getForestIdentifier(void) const;

};

#endif // ELVEX_MEMOIZATIONVALUE_H
