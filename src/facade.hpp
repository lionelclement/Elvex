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
    Facade(std::size_t id = 0, const std::bitset<MAX_FLAGS> &flags = 0);

    ~Facade();

    std::bitset<MAX_FLAGS> &getFlags();

    bool isSetFlags(const std::bitset<MAX_FLAGS> &cmp) const;

    bool isUnsetFlags(const std::bitset<MAX_FLAGS> &cmp) const;

    void addFlags(const std::bitset<MAX_FLAGS> &f);

    void subFlags(const std::bitset<MAX_FLAGS> &f);

    void printFlags(std::ostream &) const;

    std::uint32_t getId(void) const;
    
    std::string getIdStr(void) const;
};

#endif // ELVEX_FACADE_H
