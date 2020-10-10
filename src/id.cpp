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

#include "id.h"
#include "messages.h"

std::size_t Id::uniqId = 1;

/* **************************************************
 *
 ************************************************** */
Id::Id(size_t id) {
    if (id)
        this->id = id;
    else
        this->id = ++uniqId;
}

/* **************************************************
 *
 ************************************************** */
std::size_t Id::getId(void) const {
    return this->id;
}
