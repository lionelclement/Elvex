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

#ifndef ELVEX_FLAGS_H
#define ELVEX_FLAGS_H

#include <bitset>

#define MAX_FLAGS 8

class Flags
{

public:
    static const std::bitset<MAX_FLAGS> SEEN;
    static const std::bitset<MAX_FLAGS> XML;
    static const std::bitset<MAX_FLAGS> GENERATED;
    static const std::bitset<MAX_FLAGS> DISABLED;
    static const std::bitset<MAX_FLAGS> NIL;
    static const std::bitset<MAX_FLAGS> BOTTOM;
    static const std::bitset<MAX_FLAGS> REJECTED;
    static const std::bitset<MAX_FLAGS> CHOOSEN;

private:
    std::bitset<MAX_FLAGS> flags;

public:
    Flags();

    explicit Flags(const std::bitset<MAX_FLAGS> &flags);

    std::bitset<MAX_FLAGS> &getFlags();

    bool isSet(const std::bitset<MAX_FLAGS> &cmp) const;

    bool isUnset(const std::bitset<MAX_FLAGS> &cmp) const;

    void add(const std::bitset<MAX_FLAGS> &f);

    void sub(const std::bitset<MAX_FLAGS> &f);

    void print(std::ostream &) const;
};

#endif // ELVEX_FLAGS_H
