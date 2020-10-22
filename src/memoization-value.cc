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

#include "memoization-value.hpp"

#include <utility>
#include "messages.hpp"

/* ************************************************************
 * 
 ************************************************************ */
MemoizationValue::MemoizationValue(featuresPtr features, forestIdentifierPtr forestIdentifier) {
    this->features = std::move(features);
    this->forestIdentifier = std::move(forestIdentifier);
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
    return memoizationValuePtr(
new MemoizationValue(std::move(features), std::move(forestIdentifier)));
}

/* ************************************************************
 * 
 ************************************************************ */
featuresPtr MemoizationValue::getFeatures() const {
    return this->features;
}

/* ************************************************************
 * 
 ************************************************************ */
forestIdentifierPtr MemoizationValue::getForestIdentifier() const {
    return this->forestIdentifier;
}
