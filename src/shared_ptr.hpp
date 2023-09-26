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

#ifndef ELVEX_SHARED_PTR_H
#define ELVEX_SHARED_PTR_H

#include <memory>

typedef std::shared_ptr<class Bitset> bitsetPtr;
typedef std::shared_ptr<class Entries> entriesPtr;
typedef std::shared_ptr<class Entry> entryPtr;
typedef std::shared_ptr<class Environment> environmentPtr;
typedef std::shared_ptr<class Feature> featurePtr;
typedef std::shared_ptr<class Features> featuresPtr;
typedef std::shared_ptr<class Forest> forestPtr;
typedef std::shared_ptr<class Pairp> pairpPtr;
typedef std::shared_ptr<class ListFeatures> listFeaturesPtr;
typedef std::shared_ptr<class Node> nodePtr;
typedef std::shared_ptr<class Rule> rulePtr;
typedef std::shared_ptr<class Statement> statementPtr;
typedef std::shared_ptr<class Statements> statementsPtr;
typedef std::shared_ptr<class Terminal> terminalPtr;
typedef std::shared_ptr<class Terms> termsPtr;
typedef std::shared_ptr<class Value> valuePtr;

#endif // ELVEX_SHARED_PTR_H
