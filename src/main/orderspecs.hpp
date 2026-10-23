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

#ifndef ELVEX_ORDERSPECS_H
#define ELVEX_ORDERSPECS_H

#include <vector>
#include <string>
#include "orderspec.hpp"

class OrderSpecs
{
private:
    std::vector<OrderSpec> specs;

public:
    typedef std::vector<OrderSpec>::iterator iterator;
    typedef std::vector<OrderSpec>::const_iterator const_iterator;

    OrderSpecs();

    void add(const OrderSpec &spec);
    void clear();

    bool empty() const;
    size_t size() const;

    const_iterator begin() const;
    const_iterator end() const;
    iterator begin();
    iterator end();

    const std::vector<OrderSpec> &asVector() const;

    void addEdges(std::vector<std::vector<bool>> &edge,
                  const std::vector<uint32_t> &rhsIndexes) const;

    std::string toString() const;
    std::string coreSerialString() const;

    bool operator==(const OrderSpecs &other) const;
    bool operator!=(const OrderSpecs &other) const;
};

#endif