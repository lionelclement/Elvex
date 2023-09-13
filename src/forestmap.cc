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
 * LaBRI -- Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
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
ForestMap::ForestMap()
{
    NEW;
}

/* **************************************************
 *
 ************************************************** */
ForestMap::~ForestMap()
{
    DELETE;
    for (auto &i : data)
    {
        forestPtr tmp = i.second;
        if (tmp)
            tmp.reset();
    }
}

/* **************************************************
 *
 ************************************************** */
ForestMap::map::const_iterator ForestMap::find(class ForestIdentifier *forestIdentifier) const
{
    return data.find(forestIdentifier);
}

/* **************************************************
 *
 ************************************************** */
ForestMap::map::const_iterator ForestMap::cbegin() const
{
    return data.cbegin();
}

/* **************************************************
 *
 ************************************************** */
ForestMap::map::const_iterator ForestMap::cend() const
{
    return data.cend();
}

/* **************************************************
 *
 ************************************************** */
void ForestMap::clear()
{
    return data.clear();
}

/* **************************************************
 *
 ************************************************** */
bool ForestMap::insert(class ForestIdentifier *key, forestPtr value)
{
    auto result = data.insert(std::make_pair(key, value)).second;
    // CERR_LINE
    // std::cerr << "insert " << key->peekSerialString() << std::endl;
    return result;
}
