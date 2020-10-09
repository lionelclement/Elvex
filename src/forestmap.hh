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

#ifndef ELVEX_FORESTMAP_H
#define ELVEX_FORESTMAP_H

#include <unordered_map>
#include "shared_ptr.hh"
#include "forestidentifier.hh"

class ForestMap {

public:
    typedef std::unordered_map<const forestIdentifierPtr, forestPtr, ForestIdentifier::hash, ForestIdentifier::equal_to> map;
    typedef std::pair<const forestIdentifierPtr, forestPtr> pair;

private:
    map data;
    static int nb;

public:
    ForestMap(void);

    ~ForestMap();

    const map::const_iterator find(const forestIdentifierPtr) const;

    const map::const_iterator begin(void) const;

    const map::const_iterator end(void) const;

    void clear(void);

    const bool insert(pair);

};

#endif // ELVEX_FORESTMAP_H
