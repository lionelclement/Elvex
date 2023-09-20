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

const std::bitset<FLAGS> Flags::SEEN = std::bitset<FLAGS>(1ul << 1u);
const std::bitset<FLAGS> Flags::XML = std::bitset<FLAGS>(1ul << 2u);
const std::bitset<FLAGS> Flags::GENERATED = std::bitset<FLAGS>(1ul << 3u);
const std::bitset<FLAGS> Flags::DISABLED = std::bitset<FLAGS>(1ul << 4u);
const std::bitset<FLAGS> Flags::NIL = std::bitset<FLAGS>(1ul << 5u);
const std::bitset<FLAGS> Flags::BOTTOM = std::bitset<FLAGS>(1ul << 6u);
const std::bitset<FLAGS> Flags::CHOOSEN = std::bitset<FLAGS>(1ul << 7u);
const std::bitset<FLAGS> Flags::REJECTED = std::bitset<FLAGS>(1ul << 8u);

/* **************************************************
 *
 ************************************************** */
Flags::Flags() {
    this->flags = 0;
}

/* **************************************************
 *
 ************************************************** */
Flags::Flags(const std::bitset<FLAGS> &flags) {
    this->flags = flags;
}

/* **************************************************
 *
 ************************************************** */
std::bitset<FLAGS> &Flags::getFlags() {
    return this->flags;
}

/* **************************************************
 *
 ************************************************** */
bool Flags::isSet(const std::bitset<FLAGS> &cmp) const {
    return (this->flags & cmp).any();
}

/* **************************************************
 *
 ************************************************** */
bool Flags::isUnset(const std::bitset<FLAGS> &cmp) const {
    return (this->flags & cmp).none();
}

/* **************************************************
 *
 ************************************************** */
void Flags::add(const std::bitset<FLAGS>& _flags) {
    this->flags |= _flags;
}

/* **************************************************
 *
 ************************************************** */
void Flags::sub(const std::bitset<FLAGS>& _flags) {
    this->flags &= ~_flags;
}

/* **************************************************
 *
 ************************************************** */
void Flags::print(std::ostream &outStream) const {
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
