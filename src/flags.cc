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

#include <iostream>
#include "flags.hpp"
#include "messages.hpp"

const std::bitset<MAX_FLAGS> Flags::SEEN = std::bitset<MAX_FLAGS>(1ul << 1u);
const std::bitset<MAX_FLAGS> Flags::XML = std::bitset<MAX_FLAGS>(1ul << 2u);
const std::bitset<MAX_FLAGS> Flags::GENERATED = std::bitset<MAX_FLAGS>(1ul << 3u);
const std::bitset<MAX_FLAGS> Flags::DISABLED = std::bitset<MAX_FLAGS>(1ul << 4u);
const std::bitset<MAX_FLAGS> Flags::NIL = std::bitset<MAX_FLAGS>(1ul << 5u);
const std::bitset<MAX_FLAGS> Flags::BOTTOM = std::bitset<MAX_FLAGS>(1ul << 6u);
const std::bitset<MAX_FLAGS> Flags::CHOOSEN = std::bitset<MAX_FLAGS>(1ul << 7u);
const std::bitset<MAX_FLAGS> Flags::REJECTED = std::bitset<MAX_FLAGS>(1ul << 8u);

/* **************************************************
 *
 ************************************************** */
Flags::Flags()
{
    this->flags = 0;
}

/* **************************************************
 *
 ************************************************** */
Flags::Flags(const std::bitset<MAX_FLAGS> &flags)
{
    this->flags = flags;
}

/* **************************************************
 *
 ************************************************** */
std::bitset<MAX_FLAGS> &Flags::getFlags()
{
    return this->flags;
}

/* **************************************************
 *
 ************************************************** */
bool Flags::isSet(const std::bitset<MAX_FLAGS> &cmp) const
{
    return (this->flags & cmp).any();
}

/* **************************************************
 *
 ************************************************** */
bool Flags::isUnset(const std::bitset<MAX_FLAGS> &cmp) const
{
    return (this->flags & cmp).none();
}

/* **************************************************
 *
 ************************************************** */
void Flags::add(const std::bitset<MAX_FLAGS> &_flags)
{
    this->flags |= _flags;
}

/* **************************************************
 *
 ************************************************** */
void Flags::sub(const std::bitset<MAX_FLAGS> &_flags)
{
    this->flags &= ~_flags;
}

/* **************************************************
 *
 ************************************************** */
void Flags::print(std::ostream &outStream) const
{
    if (isSet(Flags::SEEN))
        outStream << "SEEN ";
    if (isSet(XML))
        outStream << "XML ";
    if (isSet(GENERATED))
        outStream << "GENERATED ";
    if (isSet(DISABLED))
        outStream << "DISABLED ";
    if (isSet(NIL))
        outStream << "NIL ";
    if (isSet(BOTTOM))
        outStream << "BOTTOM ";
    if (isSet(CHOOSEN))
        outStream << "CHOOSEN ";
    if (isSet(REJECTED))
        outStream << "REJECTED ";
}
