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

#include "uniq-id.hpp"

std::size_t UniqId::uniqId = 1;

/* **************************************************
 *
 ************************************************** */
UniqId::UniqId(size_t id) {
    if (id)
        this->id = id;
    else
        this->id = ++uniqId;
}

/* **************************************************
 *
 ************************************************** */
std::size_t UniqId::getId() const {
    return this->id;
}
