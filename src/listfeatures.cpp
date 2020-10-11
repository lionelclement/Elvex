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

#include <climits>
#include <utility>
#include "listfeatures.h"
#include "features.h"
#include "shared_ptr.h"
#include "messages.h"

/* **************************************************
 *
 ************************************************** */
ListFeatures::ListFeatures()
        : Id(0) {
    NEW;
}

/* **************************************************
 *
 ************************************************** */
ListFeatures::~ListFeatures() {
    DELETE;
    for (auto & listFeature : listFeatures)
        listFeature.reset();
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr ListFeatures::create() {
    return listFeaturesPtr(new ListFeatures());
}

/* **************************************************
 *
 ************************************************** */
featuresPtr ListFeatures::operator[](unsigned int j) {
    return listFeatures[j];
}

/* **************************************************
 *
 ************************************************** */
void ListFeatures::push_back(const featuresPtr& fs) {
    listFeatures.push_back(fs);
}

/* **************************************************
 *
 ************************************************** */
void ListFeatures::add(unsigned int j, featuresPtr fs) {
    listFeatures[j] = std::move(fs);
}

/* **************************************************
 *
 ************************************************** */
void ListFeatures::clear() {
    listFeatures.clear();
}

/* **************************************************
 *
 ************************************************** */
ListFeatures::featuresVector::const_iterator ListFeatures::begin() const {
    return listFeatures.begin();
}

/* **************************************************
 *
 ************************************************** */
ListFeatures::featuresVector::const_iterator ListFeatures::end() const {
    return listFeatures.end();
}

/* **************************************************
 *
 ************************************************** */
size_t ListFeatures::size() const {
    return listFeatures.size();
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr ListFeatures::clone() {
    listFeaturesPtr lf = ListFeatures::create();
    for (featuresVector::const_iterator i = listFeatures.begin(); i != listFeatures.end(); ++i)
        lf->push_back((*i)->clone());
    return lf;
}
