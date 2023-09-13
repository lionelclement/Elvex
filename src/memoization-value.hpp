/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2023 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: 
 * Lionel Clément
 * LaBRI - Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef ELVEX_MEMOIZATIONVALUE_H
#define ELVEX_MEMOIZATIONVALUE_H

#include "shared_ptr.hpp"

class MemoizationValue {

private:
    featuresPtr features;
    class ForestIdentifier* forestIdentifier;

    MemoizationValue(featuresPtr, class ForestIdentifier*);

public:
    ~MemoizationValue();

    static class MemoizationValue* create(featuresPtr, class ForestIdentifier*);

    featuresPtr getFeatures(void) const;

    class ForestIdentifier* getForestIdentifier(void) const;

};

#endif // ELVEX_MEMOIZATIONVALUE_H
