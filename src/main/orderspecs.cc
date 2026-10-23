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

#include <sstream>
#include "orderspecs.hpp"

OrderSpecs::OrderSpecs()
    : specs()
{
}

void OrderSpecs::add(const OrderSpec &spec)
{
    for (const auto &existing : specs)
    {
        if (existing == spec)
            return;
    }

    specs.push_back(spec);
}

void OrderSpecs::clear()
{
    specs.clear();
}

bool OrderSpecs::empty() const
{
    return specs.empty();
}

size_t OrderSpecs::size() const
{
    return specs.size();
}

OrderSpecs::const_iterator OrderSpecs::begin() const
{
    return specs.begin();
}

OrderSpecs::const_iterator OrderSpecs::end() const
{
    return specs.end();
}

OrderSpecs::iterator OrderSpecs::begin()
{
    return specs.begin();
}

OrderSpecs::iterator OrderSpecs::end()
{
    return specs.end();
}

const std::vector<OrderSpec> &OrderSpecs::asVector() const
{
    return specs;
}

void OrderSpecs::addEdges(std::vector<std::vector<bool>> &edge,
                          const std::vector<uint32_t> &rhsIndexes) const
{
    for (const auto &spec : specs)
        spec.addEdges(edge, rhsIndexes);
}

std::string OrderSpecs::toString() const
{
    std::ostringstream out;

    for (const auto &spec : specs)
        out << spec.toString() << '\n';

    return out.str();
}

std::string OrderSpecs::coreSerialString() const
{
    std::ostringstream stream;

    for (const auto &spec : specs)
        stream << spec.coreSerialString() << '/';

    return stream.str();
}

bool OrderSpecs::operator==(const OrderSpecs &other) const
{
    return coreSerialString() == other.coreSerialString();
}

bool OrderSpecs::operator!=(const OrderSpecs &other) const
{
    return !(*this == other);
}