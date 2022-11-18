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

#ifndef ELVEX_UNIQ_ID_H
#define ELVEX_UNIQ_ID_H

#include <cstddef>

class UniqId {

private:
    static size_t uniqId;
    size_t id;

public:
    explicit UniqId(size_t id = 0); // if zero => autoinc
    size_t getId(void) const;

};

#endif // ELVEX_UNIQ_ID_H
