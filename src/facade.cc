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
    return flags.isSet(cmp);
}

/* **************************************************
 *
 ************************************************** */
bool Facade::isUnsetFlags(const std::bitset<FLAGS> &cmp) const
{
    return flags.isUnset(cmp);
}

/* **************************************************
 *
 ************************************************** */
void Facade::addFlags(const std::bitset<FLAGS> &f)
{
    flags.add(f);
}

/* **************************************************
 *
 ************************************************** */
void Facade::subFlags(const std::bitset<FLAGS> &f)
{
    flags.sub(f);
}

/* **************************************************
 *
 ************************************************** */
void Facade::printFlags(std::ostream &out) const
{
    flags.print(out);
}

/* **************************************************
 *
 ************************************************** */
std::uint32_t Facade::getId(void) const
{
    return uniqId.getId();
}

/* **************************************************
 *
 ************************************************** */
std::string Facade::getIdStr(void) const
{
    return uniqId.getIdStr();
}
