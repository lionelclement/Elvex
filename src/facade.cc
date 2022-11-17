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

#include "facade.hpp"
#include "messages.hpp"

/* **************************************************
 *
 ************************************************** */
Facade::Facade(std::size_t id, const std::bitset<FLAGS> &args)
{
    NEW;
    uniqId = UniqId(id);
    flags = Flags(args);
}

/* **************************************************
 *
 ************************************************** */
Facade::~Facade()
{
    DELETE;
}

/* **************************************************
 *
 ************************************************** */
std::bitset<FLAGS> &Facade::getFlags()
{
    return flags.getFlags();
}

/* **************************************************
 *
 ************************************************** */
bool Facade::isSetFlags(const std::bitset<FLAGS> &cmp) const
{
    return flags.isSetFlags(cmp);
}

/* **************************************************
 *
 ************************************************** */
bool Facade::isUnsetFlags(const std::bitset<FLAGS> &cmp) const
{
    return flags.isUnsetFlags(cmp);
}

/* **************************************************
 *
 ************************************************** */
void Facade::addFlags(const std::bitset<FLAGS> &f)
{
    flags.addFlags(f);
}

/* **************************************************
 *
 ************************************************** */
void Facade::subFlags(const std::bitset<FLAGS> &f)
{
    flags.subFlags(f);
}

/* **************************************************
 *
 ************************************************** */
void Facade::printFlags(std::ostream &out) const
{
    flags.printFlags(out);
}

/* **************************************************
 *
 ************************************************** */
std::size_t Facade::getId(void) const
{
    return uniqId.getId();
}
