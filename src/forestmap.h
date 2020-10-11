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

#ifndef ELVEX_FORESTMAP_H
#define ELVEX_FORESTMAP_H

#include <unordered_map>
#include "shared_ptr.h"
#include "forestidentifier.h"

class ForestMap {

public:
    typedef std::unordered_map<const forestIdentifierPtr, forestPtr, ForestIdentifier::hash, ForestIdentifier::equal_to> map;
    typedef std::pair<const forestIdentifierPtr, forestPtr> pair;

private:
    map data;
    __unused static int nb;

public:
    ForestMap();

    ~ForestMap();

    map::const_iterator find(const forestIdentifierPtr&) const;

    map::const_iterator begin() const;

    map::const_iterator end() const;

    void clear();

    bool insert(pair);

};

#endif // ELVEX_FORESTMAP_H
