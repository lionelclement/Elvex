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
#include "orderspec.hpp"
#include "statement.hpp"
#include "value.hpp"

OrderSpec::OrderSpec()
    : kind(CHAIN),
      indexes(),
      fieldAccessStatement(),
      fieldAccessValues()
{
}

OrderSpec::OrderSpec(Kind kind, const std::vector<uint32_t> &indexes)
    : kind(kind),
      indexes(indexes),
      fieldAccessStatement(),
      fieldAccessValues()
{
}

OrderSpec::OrderSpec(Kind kind,
                     const std::vector<uint32_t> &indexes,
                     const statementPtr &fieldAccessStatement,
                     const std::vector<valuePtr> &fieldAccessValues)
    : kind(kind),
      indexes(indexes),
      fieldAccessStatement(fieldAccessStatement),
      fieldAccessValues(fieldAccessValues)
{
}

OrderSpec OrderSpec::chain(const std::vector<uint32_t> &indexes)
{
    return OrderSpec(CHAIN, indexes);
}

OrderSpec OrderSpec::first(uint32_t index)
{
    return OrderSpec(FIRST, {index});
}

OrderSpec OrderSpec::last(uint32_t index)
{
    return OrderSpec(LAST, {index});
}

OrderSpec OrderSpec::createFieldAccess(const std::vector<uint32_t> &indexes,
                                        const statementPtr &fieldAccessStatement,
                                        const std::vector<valuePtr> &fieldAccessValues)
{
    return OrderSpec(FIELD_ACCESS, indexes, fieldAccessStatement, fieldAccessValues);
}

OrderSpec::Kind OrderSpec::getKind() const
{
    return kind;
}

const std::vector<uint32_t> &OrderSpec::getIndexes() const
{
    return indexes;
}

const statementPtr &OrderSpec::getFieldAccess() const
{
    return fieldAccessStatement;
}

const std::vector<valuePtr> &OrderSpec::getFieldAccessValues() const
{
    return fieldAccessValues;
}

bool OrderSpec::hasFieldAccess() const
{
    return static_cast<bool>(fieldAccessStatement);
}

/**
 * Constraints refer to original RHS indices, but the graph contains only
 * the children participating in the current derivation. The first matching
 * position is used when an index occurs more than once.
 */
int OrderSpec::findChildPosition(const std::vector<uint32_t> &rhsIndexes, uint32_t rhsIndex)
{
    for (size_t i = 0; i < rhsIndexes.size(); ++i)
    {
        if (rhsIndexes[i] == rhsIndex)
            return static_cast<int>(i);
    }
    return -1;
}

void OrderSpec::addEdge(std::vector<std::vector<bool>> &edge, size_t before, size_t after)
{
    if (before != after)
        edge[before][after] = true;
}

/** Project a chain onto present children, preserving their declared order. */
void OrderSpec::addChainEdges(std::vector<std::vector<bool>> &edge,
                              const std::vector<uint32_t> &rhsIndexes) const
{
    std::vector<size_t> projected;
    for (auto rhsIndex : indexes)
    {
        int childPosition = findChildPosition(rhsIndexes, rhsIndex);
        if (childPosition >= 0)
            projected.push_back(static_cast<size_t>(childPosition));
    }

    for (size_t i = 0; i + 1 < projected.size(); ++i)
        addEdge(edge, projected[i], projected[i + 1]);
}

/** Force one present child before (FIRST) or after (LAST) every other child. */
void OrderSpec::addBoundaryEdges(std::vector<std::vector<bool>> &edge,
                                 const std::vector<uint32_t> &rhsIndexes, bool first) const
{
    if (indexes.empty())
        return;

    int childPosition = findChildPosition(rhsIndexes, indexes[0]);
    if (childPosition < 0)
        return;

    const size_t boundary = static_cast<size_t>(childPosition);
    for (size_t i = 0; i < edge.size(); ++i)
    {
        if (i != boundary)
        {
            if (first)
                addEdge(edge, boundary, i);
            else
                addEdge(edge, i, boundary);
        }
    }
}

/**
 * A field-access constraint orders pairs only when both children exist,
 * both values are present, and the values compare strictly. Equal values
 * intentionally add no edge.
 */
void OrderSpec::addFieldAccessEdges(std::vector<std::vector<bool>> &edge,
                                    const std::vector<uint32_t> &rhsIndexes) const
{
    if (indexes.size() != fieldAccessValues.size())
        return;

    for (size_t i = 0; i < indexes.size(); ++i)
    {
        int posI = findChildPosition(rhsIndexes, indexes[i]);
        if (posI < 0)
            continue;

        const valuePtr &valueI = fieldAccessValues[i];
        if (!valueI || valueI->isNil())
            continue;

        for (size_t j = i + 1; j < indexes.size(); ++j)
        {
            int posJ = findChildPosition(rhsIndexes, indexes[j]);
            if (posJ < 0)
                continue;

            const valuePtr &valueJ = fieldAccessValues[j];
            if (!valueJ || valueJ->isNil())
                continue;

            if (valueI->lessThan(valueJ))
                addEdge(edge, static_cast<size_t>(posI), static_cast<size_t>(posJ));
            else if (valueJ->lessThan(valueI))
                addEdge(edge, static_cast<size_t>(posJ), static_cast<size_t>(posI));
        }
    }
}

void OrderSpec::addEdges(std::vector<std::vector<bool>> &edge,
                         const std::vector<uint32_t> &rhsIndexes) const
{
    switch (kind)
    {
    case CHAIN:
        addChainEdges(edge, rhsIndexes);
        break;
    case FIRST:
        addBoundaryEdges(edge, rhsIndexes, true);
        break;
    case LAST:
        addBoundaryEdges(edge, rhsIndexes, false);
        break;
    case FIELD_ACCESS:
        addFieldAccessEdges(edge, rhsIndexes);
        break;
    }
}

std::string OrderSpec::toString() const
{
    std::ostringstream out;

    if (kind == CHAIN)
    {
        out << "order ";
        for (size_t i = 0; i < indexes.size(); ++i)
        {
            if (i)
                out << " < ";
            out << indexes[i] + 1;
        }
        out << ";";
    }
    else if (kind == FIRST)
    {
        out << "order << ";
        if (!indexes.empty())
            out << indexes[0] + 1;
        out << ";";
    }
    else if (kind == LAST)
    {
        out << "order >> ";
        if (!indexes.empty())
            out << indexes[0] + 1;
        out << ";";
    }
    else if (kind == FIELD_ACCESS)
    {
        out << "order ";
        for (size_t i = 0; i < indexes.size(); ++i)
        {
            if (i)
                out << ", ";
            out << indexes[i] + 1;
        }
        out << " by ";
        if (fieldAccessStatement)
            fieldAccessStatement->flatPrint(out);
        out << ";";
    }

    return out.str();
}

std::string OrderSpec::coreSerialString() const
{
    std::ostringstream stream;

    stream << static_cast<int>(kind) << ':';

    for (auto index : indexes)
        stream << index << ',';

    if (fieldAccessStatement)
        stream << ':' << fieldAccessStatement->peekCoreSerialString();

    for (auto value : fieldAccessValues)
        stream << ':' << (value ? value->peekCoreSerialString() : "0");

    return stream.str();
}

bool OrderSpec::operator==(const OrderSpec &other) const
{
    return coreSerialString() == other.coreSerialString();
}

bool OrderSpec::operator!=(const OrderSpec &other) const
{
    return !(*this == other);
}