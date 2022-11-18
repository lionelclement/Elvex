/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI,
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI -- Université Bordeaux
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
    this->features = std::move(features);
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
    return new MemoizationValue(std::move(features), std::move(forestIdentifier));
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
