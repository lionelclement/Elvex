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

#include <unordered_map>

#include "forestmap.hpp"
#include "messages.hpp"
#include "forestidentifier.hpp"
#include "forest.hpp"
#include "vartable.hpp"

/* **************************************************
 *
 ************************************************** */
ForestMap::ForestMap() {
    NEW
}

/* **************************************************
 *
 ************************************************** */
ForestMap::~ForestMap() {
    DELETE
    for (auto & i : data) {
        forestPtr tmp = i.second;
        if (tmp)
            tmp.reset();
    }
}

/* **************************************************
 *
 ************************************************** */
ForestMap::map::const_iterator ForestMap::find(const forestIdentifierPtr& forestIdentifier) const {
    return data.find(forestIdentifier);
}

/* **************************************************
 *
 ************************************************** */
ForestMap::map::const_iterator ForestMap::begin() const {
    return data.begin();
}

/* **************************************************
 *
 ************************************************** */
ForestMap::map::const_iterator ForestMap::end() const {
    return data.end();
}

/* **************************************************
 *
 ************************************************** */
void ForestMap::clear() {
    return data.clear();
}

/* **************************************************
 *
 ************************************************** */
bool ForestMap::_insert(forestIdentifierPtr key, forestPtr value) {
    auto result = data.insert(std::make_pair(key, value)).second;
    //CERR_LINE
    //std::cerr << "insert " << key->peekSerialString() << std::endl;
    return result;
}

