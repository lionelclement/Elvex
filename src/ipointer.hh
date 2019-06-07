/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: Lionel Clément,
 * Labri -- 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef IPOINTER_H
#define IPOINTER_H

//#include <tr1/memory>
#include <memory>

//using namespace std::tr1;
using namespace std;

typedef shared_ptr< class Bitset > bitsetPtr;
typedef shared_ptr< class Feature > featurePtr;
typedef shared_ptr< class Features > featuresPtr;
typedef shared_ptr< class ListFeatures > listFeaturesPtr;
typedef shared_ptr< class Value > valuePtr;
typedef shared_ptr< class List > listPtr;
typedef shared_ptr< class MemoizationValue > memoizationValuePtr;
typedef shared_ptr< class Node > nodePtr;
typedef shared_ptr< class Forest > forestPtr;
typedef shared_ptr< class Statement > statementPtr;
typedef shared_ptr< class Statements > statementsPtr;
typedef shared_ptr< class Item > itemPtr;
typedef shared_ptr< class ItemSet > itemSetPtr;
typedef shared_ptr< class ForestIdentifier > forestIdentifierPtr;
typedef shared_ptr< class Entry > entryPtr;
typedef shared_ptr< class Entries > entriesPtr;
typedef shared_ptr< class Environment > environmentPtr;

#endif // IPOINTER_H

