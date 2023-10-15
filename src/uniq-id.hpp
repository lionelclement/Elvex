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

#ifndef ELVEX_UNIQ_ID_H
#define ELVEX_UNIQ_ID_H

#include <cstddef>
#include <cstdint>
#include <string>

class UniqId
{

private:
    static uint32_t uniqId;
    uint32_t id;

public:
    explicit UniqId(uint32_t id = 0); // if zero => autoinc
    uint32_t getId(void) const;
    std::string getIdStr(void) const;
};

#endif // ELVEX_UNIQ_ID_H
