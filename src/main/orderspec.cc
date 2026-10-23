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
    std::vector<uint32_t> indexes;
    indexes.push_back(index);
    return OrderSpec(FIRST, indexes);
}

OrderSpec OrderSpec::last(uint32_t index)
{
    std::vector<uint32_t> indexes;
    indexes.push_back(index);
    return OrderSpec(LAST, indexes);
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

void OrderSpec::addEdges(std::vector<std::vector<bool>> &edge,
                         const std::vector<uint32_t> &rhsIndexes) const
{
    auto findChildPosition = [&](uint32_t rhsIndex) -> int
    {
        for (size_t i = 0; i < rhsIndexes.size(); ++i)
        {
            if (rhsIndexes[i] == rhsIndex)
                return static_cast<int>(i);
        }
        return -1;
    };

    auto addEdge = [&](size_t before, size_t after)
    {
        if (before != after)
            edge[before][after] = true;
    };

    if (kind == CHAIN)
    {
        std::vector<size_t> projected;

        for (auto rhsIndex : indexes)
        {
            int childPosition = findChildPosition(rhsIndex);
            if (childPosition >= 0)
                projected.push_back(static_cast<size_t>(childPosition));
        }

        for (size_t i = 0; i + 1 < projected.size(); ++i)
            addEdge(projected[i], projected[i + 1]);

        return;
    }

    if (kind == FIRST)
    {
        if (indexes.empty())
            return;

        int childPosition = findChildPosition(indexes[0]);

        if (childPosition >= 0)
        {
            for (size_t i = 0; i < edge.size(); ++i)
            {
                if (i != static_cast<size_t>(childPosition))
                    addEdge(static_cast<size_t>(childPosition), i);
            }
        }

        return;
    }

    if (kind == LAST)
    {
        if (indexes.empty())
            return;

        int childPosition = findChildPosition(indexes[0]);

        if (childPosition >= 0)
        {
            for (size_t i = 0; i < edge.size(); ++i)
            {
                if (i != static_cast<size_t>(childPosition))
                    addEdge(i, static_cast<size_t>(childPosition));
            }
        }

        return;
    }

    if (kind == FIELD_ACCESS)
    {
        /*
         * order 1, 2, 3 by ⇓.weight;
         *
         * For each pair of listed daughters:
         *   if key_i < key_j, add i < j
         *   if key_j < key_i, add j < i
         *   if equal, add no edge
         */

        if (indexes.size() != fieldAccessValues.size())
            return;

        for (size_t i = 0; i < indexes.size(); ++i)
        {
            int posI = findChildPosition(indexes[i]);
            if (posI < 0)
                continue;

            valuePtr valueI = fieldAccessValues[i];
            if (!valueI || valueI->isNil())
                continue;

            for (size_t j = i + 1; j < indexes.size(); ++j)
            {
                int posJ = findChildPosition(indexes[j]);
                if (posJ < 0)
                    continue;

                valuePtr valueJ = fieldAccessValues[j];
                if (!valueJ || valueJ->isNil())
                    continue;

                if (valueI->lessThan(valueJ))
                {
                    addEdge(static_cast<size_t>(posI),
                            static_cast<size_t>(posJ));
                }
                else if (valueJ->lessThan(valueI))
                {
                    addEdge(static_cast<size_t>(posJ),
                            static_cast<size_t>(posI));
                }
            }
        }

        return;
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