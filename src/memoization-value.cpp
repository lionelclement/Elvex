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

#include "memoization-value.h"
#include "messages.h"

/* ************************************************************
 * 
 ************************************************************ */
MemoizationValue::MemoizationValue(featuresPtr features, forestIdentifierPtr forestIdentifier) {
    this->features = features;
    this->forestIdentifier = forestIdentifier;
    NEW;
}

/* ************************************************************
 * 
 ************************************************************ */
MemoizationValue::~MemoizationValue() {
    DELETE;
}

/* ************************************************************
 * 
 ************************************************************ */
memoizationValuePtr MemoizationValue::create(featuresPtr features, forestIdentifierPtr forestIdentifier) {
    return memoizationValuePtr(new MemoizationValue(features, forestIdentifier));
}

/* ************************************************************
 * 
 ************************************************************ */
featuresPtr MemoizationValue::getFeatures(void) const {
    return this->features;
}

/* ************************************************************
 * 
 ************************************************************ */
forestIdentifierPtr MemoizationValue::getForestIdentifier(void) const {
    return this->forestIdentifier;
}
