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

#include <utility>
#include "listfeatures.hpp"
#include "features.hpp"
#include "shared_ptr.hpp"
#include "messages.hpp"

/* **************************************************
 *
 ************************************************** */
ListFeatures::ListFeatures() {
    NEW
}

/* **************************************************
 *
 ************************************************** */
ListFeatures::~ListFeatures() {
    DELETE
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
std::vector<featuresPtr>::const_iterator ListFeatures::begin() const {
    return listFeatures.begin();
}

/* **************************************************
 *
 ************************************************** */
std::vector<featuresPtr>::const_iterator ListFeatures::end() const {
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
    for (auto & listFeature : listFeatures)
        lf->push_back(listFeature->clone());
    return lf;
}
