/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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

#ifndef ELVEX_ORDERSPEC_H
#define ELVEX_ORDERSPEC_H

#include <vector>
#include <cstdint>

struct OrderSpec
{
    enum Kind
    {
        CHAIN,
        FIRST,
        LAST
    };

    Kind kind;
    std::vector<uint32_t> indexes;

    OrderSpec() = default;

    OrderSpec(Kind kind, const std::vector<uint32_t> &indexes)
        : kind(kind), indexes(indexes)
    {
    }

    bool operator==(const OrderSpec &other) const
    {
        return kind == other.kind && indexes == other.indexes;
    }

    bool operator!=(const OrderSpec &other) const
    {
        return !(*this == other);
    }
};

typedef std::vector<OrderSpec> vectorOrderSpecs;

#endif