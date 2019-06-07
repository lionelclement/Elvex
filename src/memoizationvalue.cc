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

#include "memoizationvalue.hh"
#include "messages.hh"

/* ************************************************************
 * 
 ************************************************************ */
MemoizationValue::MemoizationValue(featuresPtr features, forestIdentifierPtr forestIdentifier)
{
  NEW;
  this->features = features;
  this->forestIdentifier = forestIdentifier;
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
memoizationValuePtr MemoizationValue::create(featuresPtr features, forestIdentifierPtr forestIdentifier)
{
  return memoizationValuePtr( new MemoizationValue(features, forestIdentifier) );
}

/* ************************************************************
 * 
 ************************************************************ */
featuresPtr MemoizationValue::getFeatures(void)
{
  return this->features;
}

/* ************************************************************
 * 
 ************************************************************ */
forestIdentifierPtr MemoizationValue::getForestIdentifier(void)
{
  return this->forestIdentifier;
}
