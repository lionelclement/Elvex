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

#ifndef ELVEX_FORESTMAP_H
#define ELVEX_FORESTMAP_H

#include <unordered_map>
#include "shared_ptr.hpp"
#include "forestidentifier.hpp"

class ForestMap {

public:
<<<<<<< HEAD
    typedef std::unordered_map<forestIdentifierPtr, forestPtr, ForestIdentifier::hash, ForestIdentifier::equal_to> map;
=======
    typedef std::unordered_map<class ForestIdentifier*, forestPtr, ForestIdentifier::hash, ForestIdentifier::equal_to> map;
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723

private:
    map data;

public:
    ForestMap();

    ~ForestMap();

    map::const_iterator find(class ForestIdentifier*) const;

    map::const_iterator cbegin() const;

    map::const_iterator cend() const;

    void clear();

    bool insert(class ForestIdentifier*, forestPtr);

};

#endif // ELVEX_FORESTMAP_H
