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

#ifndef IPOINTER_H
#define IPOINTER_H

#include <memory>

typedef std::shared_ptr< class Bitset > bitsetPtr;
typedef std::shared_ptr< class Entries > entriesPtr;
typedef std::shared_ptr< class Entry > entryPtr;
typedef std::shared_ptr< class Environment > environmentPtr;
typedef std::shared_ptr< class Feature > featurePtr;
typedef std::shared_ptr< class Features > featuresPtr;
typedef std::shared_ptr< class Forest > forestPtr;
typedef std::shared_ptr< class ForestIdentifier > forestIdentifierPtr;
typedef std::shared_ptr< class Item > itemPtr;
typedef std::shared_ptr< class ItemSet > itemSetPtr;
typedef std::shared_ptr< class List > listPtr;
typedef std::shared_ptr< class ListFeatures > listFeaturesPtr;
typedef std::shared_ptr< class MemoizationValue > memoizationValuePtr;
typedef std::shared_ptr< class Node > nodePtr;
typedef std::shared_ptr< class Statement > statementPtr;
typedef std::shared_ptr< class Statements > statementsPtr;
typedef std::shared_ptr< class Term > termPtr;
typedef std::shared_ptr< class Terms > termsPtr;
typedef std::shared_ptr< class Value > valuePtr;

#endif // IPOINTER_H

