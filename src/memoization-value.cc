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

#include "memoization-value.hpp"

#include <utility>
#include "messages.hpp"

/* ************************************************************
 *
 ************************************************************ */
MemoizationValue::MemoizationValue(featuresPtr features, class ForestIdentifier *forestIdentifier)
{
    NEW;
    this->features = features;
    this->forestIdentifier = std::move(forestIdentifier);
}

/* ************************************************************
 *
 ************************************************************ */
MemoizationValue::~MemoizationValue()
{
    DELETE;
}

/* ************************************************************
 *
 ************************************************************ */
class MemoizationValue *MemoizationValue::create(featuresPtr features, class ForestIdentifier *forestIdentifier)
{
    return new MemoizationValue(features, std::move(forestIdentifier));
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr MemoizationValue::getFeatures() const
{
    return this->features;
}

/* ************************************************************
 *
 ************************************************************ */
class ForestIdentifier *MemoizationValue::getForestIdentifier() const
{
    return this->forestIdentifier;
}
