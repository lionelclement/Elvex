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

#include <climits>
#include "listfeatures.hh"
#include "features.hh"
#include "ipointer.hh"
#include "messages.hh"

/* **************************************************
 *
 ************************************************** */
ListFeatures::ListFeatures(void)
		: Id(0) {
	NEW;
}

/* **************************************************
 *
 ************************************************** */
ListFeatures::~ListFeatures(void) {
	DELETE;
	for (std::vector<featuresPtr>::iterator i = listFeatures.begin(); i != listFeatures.end(); ++i)
		i->reset();
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr ListFeatures::create(void) {
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
void ListFeatures::push_back(featuresPtr fs) {
	listFeatures.push_back(fs);
}

/* **************************************************
 *
 ************************************************** */
void ListFeatures::add(unsigned int j, featuresPtr fs) {
	listFeatures[j] = fs;
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
ListFeatures::vector::const_iterator ListFeatures::begin() const {
	return listFeatures.begin();
}

/* **************************************************
 *
 ************************************************** */
ListFeatures::vector::const_iterator ListFeatures::end() const {
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
	for (vector::const_iterator i = listFeatures.begin(); i != listFeatures.end(); ++i)
		lf->push_back((*i)->clone());
	return lf;
}
