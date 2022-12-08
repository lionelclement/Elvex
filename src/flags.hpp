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

#ifndef ELVEX_FLAGS_H
#define ELVEX_FLAGS_H

#include <bitset>

#define FLAGS 9

class Flags
{

public:
    static const std::bitset<FLAGS> SEEN;
    static const std::bitset<FLAGS> XML;
    static const std::bitset<FLAGS> GENERATED;
    static const std::bitset<FLAGS> DISABLED;
    static const std::bitset<FLAGS> NIL;
    static const std::bitset<FLAGS> BOTTOM;
    static const std::bitset<FLAGS> REJECTED;
    static const std::bitset<FLAGS> CHOOSEN;

private:
    std::bitset<FLAGS> flags;

public:
    Flags();

    explicit Flags(const std::bitset<FLAGS> &flags);

    std::bitset<FLAGS> &getFlags();

    bool isSet(const std::bitset<FLAGS> &cmp) const;

    bool isUnset(const std::bitset<FLAGS> &cmp) const;

    void add(const std::bitset<FLAGS> &f);

    void sub(const std::bitset<FLAGS> &f);

    void print(std::ostream &) const;
};

#endif // ELVEX_FLAGS_H
