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

#ifndef ELVEX_FORESTMAP_H
#define ELVEX_FORESTMAP_H

#include <unordered_map>
#include "shared_ptr.hpp"
#include "forestidentifier.hpp"

/**
 * Registry of shared forests keyed by constituent identifiers.
 * Hashing and equality use the identifier content, not pointer identity.
 * The map owns forest shared pointers but does not own the raw key pointers;
 * callers must keep the inserted identifiers alive while they are indexed.
 */
class ForestMap {

public:
    typedef std::unordered_map<class ForestIdentifier*, 
                                forestPtr, 
                                ForestIdentifier::Hash, 
                                ForestIdentifier::KeyEqual> map;


private:
    map data;

public:
    ForestMap();

    ~ForestMap();

    map::const_iterator find(class ForestIdentifier*) const;

    map::const_iterator cbegin() const;

    map::const_iterator cend() const;

    /** Drop the indexed forests (but not the raw identifier objects). */
    void clear();

    /** Insert a new forest; return false if an equivalent identifier exists. */
    bool insert(class ForestIdentifier*, forestPtr);

};

#endif // ELVEX_FORESTMAP_H
