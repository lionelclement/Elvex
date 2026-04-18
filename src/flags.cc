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
const std::bitset<MAX_FLAGS> Flags::CONTAINS_VARIABLE = std::bitset<MAX_FLAGS>(1ul << 9u);
const std::bitset<MAX_FLAGS> Flags::DOES_NOT_CONTAIN_VARIABLE = std::bitset<MAX_FLAGS>(1ul << 10u);
const std::bitset<MAX_FLAGS> Flags::CONTAINS_SYNTHESIZED_CHILD_FEATURES = std::bitset<MAX_FLAGS>(1ul << 11u);
const std::bitset<MAX_FLAGS> Flags::DOES_NOT_CONTAIN_SYNTHESIZED_CHILD_FEATURES = std::bitset<MAX_FLAGS>(1ul << 12u);

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
bool Flags::contains(const std::bitset<MAX_FLAGS> &cmp) const
{
    return (this->flags & cmp).any();
}

/* **************************************************
 *
 ************************************************** */
bool Flags::doesNotContain(const std::bitset<MAX_FLAGS> &cmp) const
{
    return (this->flags & cmp).none();
}

/* **************************************************
 *
 ************************************************** */
void Flags::set(const std::bitset<MAX_FLAGS> &_flags)
{
    this->flags |= _flags;
}

/* **************************************************
 *
 ************************************************** */
void Flags::clear(const std::bitset<MAX_FLAGS> &_flags)
{
    this->flags &= ~_flags;
}

/* **************************************************
 *
 ************************************************** */
void Flags::print(std::ostream &outStream) const
{
    if (contains(Flags::SEEN))
        outStream << "SEEN ";
    if (contains(XML))
        outStream << "XML ";
    if (contains(GENERATED))
        outStream << "GENERATED ";
    if (contains(DISABLED))
        outStream << "DISABLED ";
    if (contains(NIL))
        outStream << "NIL ";
    if (contains(BOTTOM))
        outStream << "BOTTOM ";
    if (contains(CHOOSEN))
        outStream << "CHOOSEN ";
    if (contains(REJECTED))
        outStream << "REJECTED ";
    if (contains(CONTAINS_VARIABLE))
        outStream << "CONTAINS_VARIABLE ";
    if (contains(DOES_NOT_CONTAIN_VARIABLE))
        outStream << "DOES_NOT_CONTAIN_VARIABLE ";
    if (contains(CONTAINS_SYNTHESIZED_CHILD_FEATURES))
        outStream << "CONTAINS_SYNTHESIZED_CHILD_FEATURES ";
    if (contains(DOES_NOT_CONTAIN_SYNTHESIZED_CHILD_FEATURES))
        outStream << "DOES_NOT_CONTAIN_SYNTHESIZED_CHILD_FEATURES ";
}
