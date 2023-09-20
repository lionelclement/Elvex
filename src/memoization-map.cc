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

#ifdef TRACE_MEMOIZATION
#include <iostream>
#endif
#include <utility>
#include "memoization-map.hpp"
#include "features.hpp"
#include "forestidentifier.hpp"

/* ************************************************************
 *
 ************************************************************ */
MemoizationMap::map::const_iterator MemoizationMap::find(std::string const &key) const
{
    auto memItem = memoizationMap.find(key);
#ifdef TRACE_MEMOIZATION
    if (memItem != memoizationMap.end())
    {
        std::cout << "<H3>####################### RECORDED SHIFT FOUND #######################</H3>" << std::endl;
        std::cout << "<BR>";
        std::cout << std::endl;
    }
#endif
    return memItem;
}

/* ************************************************************
 *
 ************************************************************ */
MemoizationMap::map::const_iterator MemoizationMap::cend() const
{
    return memoizationMap.cend();
}

/* ************************************************************
 *
 ************************************************************ */
void MemoizationMap::insert(std::string const &key, featuresPtr features, class ForestIdentifier *forestIdentifier)
{
#ifdef TRACE_MEMOIZATION
    std::cout << "<H3>####################### RECORD SHIFT #######################</H3>" << std::endl;
    std::cout << "<BR>";
    std::cout << std::endl;
#endif
    class MemoizationValue *value = MemoizationValue::create(std::move(features), std::move(forestIdentifier));
    auto memItem = memoizationMap.find(key);
    if (memItem != memoizationMap.end())
    {
        memItem->second.push_back(value);
    }
    else
    {
        std::vector<class MemoizationValue *> values;
        values.push_back(value);
        memoizationMap[key] = values;
    }
}

/* ************************************************************
 *
 ************************************************************ */
void MemoizationMap::clear()
{
    memoizationMap.clear();
}
