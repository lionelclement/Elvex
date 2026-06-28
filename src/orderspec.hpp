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
#include <string>
#include <cstdint>
#include "shared_ptr.hpp"

class OrderSpec
{
public:
    enum Kind
    {
        CHAIN,
        FIRST,
        LAST,
        FIELD_ACCESS
    };

private:
    Kind kind;
    std::vector<uint32_t> indexes;

    // Used only for FIELD_ACCESS.
    statementPtr fieldAccessStatement;
    std::vector<valuePtr> fieldAccessValues;

public:
    OrderSpec();

    OrderSpec(Kind kind, const std::vector<uint32_t> &indexes);

    OrderSpec(Kind kind,
              const std::vector<uint32_t> &indexes,
              const statementPtr &fieldAccessStatement,
              const std::vector<valuePtr> &fieldAccessValues);

    static OrderSpec chain(const std::vector<uint32_t> &indexes);
    static OrderSpec first(uint32_t index);
    static OrderSpec last(uint32_t index);
    static OrderSpec createFieldAccess(const std::vector<uint32_t> &indexes,
                                       const statementPtr &fieldAccessStatement,
                                       const std::vector<valuePtr> &fieldAccessValues);

    Kind getKind() const;
    const std::vector<uint32_t> &getIndexes() const;

    const statementPtr &getFieldAccess() const;
    const std::vector<valuePtr> &getFieldAccessValues() const;

    bool hasFieldAccess() const;

    void addEdges(std::vector<std::vector<bool>> &edge,
                  const std::vector<uint32_t> &rhsIndexes) const;

    std::string toString() const;
    std::string coreSerialString() const;

    bool operator==(const OrderSpec &other) const;
    bool operator!=(const OrderSpec &other) const;
};

#endif