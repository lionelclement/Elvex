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
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifdef TRACE_MEMOIZATION
#include <iostream>
#endif
#include <utility>
#include "memoization-map.hpp"
#include "features.hpp"
#include "forestidentifier.hpp"
#include "messages.hpp"

/* ************************************************************
 * 
 ************************************************************ */
MemoizationMap::map::const_iterator MemoizationMap::find(std::string const& key) const {
    auto memItem = memoizationMap.find(key);
#ifdef TRACE_MEMOIZATION
    if (memItem != memoizationMap.end()) {
       std::cout << "<H3>####################### RECORDED VALUE FOUND #######################</H3>" << std::endl;
       std::cout << "<BR>";
       std::cout << std::endl;
    }
#endif
    return memItem;
}

/* ************************************************************
 * 
 ************************************************************ */
MemoizationMap::map::const_iterator MemoizationMap::cend() const {
    return memoizationMap.cend();
}

/* ************************************************************
 * 
 ************************************************************ */
void MemoizationMap::insert(std::string const& key, featuresPtr features, forestIdentifierPtr forestIdentifier) {
#ifdef TRACE_MEMOIZATION
    std::cout << "<H3>####################### RECORD VALUE #######################</H3>" << std::endl;
    std::cout << "<BR>";
    std::cout << std::endl;
#endif
    memoizationValuePtr value = MemoizationValue::create(std::move(features), std::move(forestIdentifier));
    auto memItem = memoizationMap.find(key);
    if (memItem != memoizationMap.end()) {
        memItem->second.push_back(value);
    } else {
        std::vector<memoizationValuePtr> values;
        values.push_back(value);
        if (!memoizationMap.insert(std::make_pair(key, values)).second)
            FATAL_ERROR_UNEXPECTED;
    }
}

/* ************************************************************
 *
 ************************************************************ */
void MemoizationMap::clear() {
    memoizationMap.clear();
}

