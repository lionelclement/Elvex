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

#ifndef ELVEX_ID_H
#define ELVEX_ID_H

#include <cstddef>

class Id {

private:
    static size_t uniqId;
    size_t id;

public:
    Id(size_t id);

    size_t getId(void) const;

};

#endif // ELVEX_ID_H
