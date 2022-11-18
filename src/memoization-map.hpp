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

class MemoizationMap : public std::enable_shared_from_this<class MemoizationMap>
{

public:
    typedef std::unordered_map<std::string, std::vector<class MemoizationValue *>> map;

private:
    map memoizationMap;

public:
    void clear(void);

    map::const_iterator cend(void) const;

    map::const_iterator find(const std::string &) const;

    void insert(const std::string &, featuresPtr, class ForestIdentifier *);
};

#endif // ELVEX_MEMOIZATIONMAP_H
