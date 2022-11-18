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
 * lionel.clement@labri.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef ELVEX_FACADE_H
#define ELVEX_FACADE_H

#include "flags.hpp"
#include "uniq-id.hpp"
#include "shared_ptr.hpp"
#include "serializable.hpp"
#include "variableflag.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Facade
{

private:
    UniqId uniqId;
    Flags flags;

public:
    Facade(std::size_t id = 0, const std::bitset<FLAGS> &flags = 0);

    ~Facade();

    std::bitset<FLAGS> &getFlags();

    bool isSetFlags(const std::bitset<FLAGS> &cmp) const;

    bool isUnsetFlags(const std::bitset<FLAGS> &cmp) const;

    void addFlags(const std::bitset<FLAGS> &f);

    void subFlags(const std::bitset<FLAGS> &f);

    void printFlags(std::ostream &) const;

    std::size_t getId(void) const;
};

#endif // ELVEX_FACADE_H
