/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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

#ifndef ELVEX_MEMOIZATIONMAP_H
#define ELVEX_MEMOIZATIONMAP_H

#include <string>
#include <unordered_map>
#include <vector>
#include "memoization-value.hpp"

/**
 * Indexes reduction results by a serialized pair of chart items.
 * Values are stored in insertion order within each key. The existing
 * raw-pointer lifetime policy is unchanged: clear() only empties the index.
 */
class MemoizationMap : public std::enable_shared_from_this<class MemoizationMap>
{

public:
    typedef std::unordered_map<std::string, std::vector<class MemoizationValue *>> map;

private:
    map memoizationMap;

public:
    /** Discard indexed pointers without destroying their pointees. */
    void clear(void);

    map::const_iterator cend(void) const;

    /** Look up a pair; returns cend() if it has no memoized results. */
    map::const_iterator find(const std::string &) const;

    /** Append one result; repeated keys retain the insertion order. */
    void insert(const std::string &, featuresPtr, class ForestIdentifier *, class Item *);
};

#endif // ELVEX_MEMOIZATIONMAP_H
