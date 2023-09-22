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

#include <climits>
#include <map>
#include <unordered_map>
#include <utility>
#include "vartable.hpp"
#include "messages.hpp"

const uint16_t Vartable::_END_;
const uint16_t Vartable::_START_TERM_;

uint16_t Vartable::codeMapIndex;
std::bitset<MAXBITS> Vartable::variableMapIndex;
Vartable::string_to_bitset Vartable::nameToBitsetMap;
Vartable::uint16_t_to_string Vartable::codeToNameMap;
Vartable::string_to_uint16_t Vartable::nameToCodeMap;
Vartable::uint16_t_to_string Vartable::bitToNameMap;

Vartable vartable;

/* ************************************************************
 *
 ************************************************************ */
Vartable::Vartable()
{
    codeMapIndex = 0;
    variableMapIndex = 1;
    insertCodeMap(_END_, "_END_");
    insertCodeMap(_START_TERM_, "_STARTTERM_");
}

/* ************************************************************
 * ajoute une nouvelle variable à la table
 * y associe un poids de bitset
 * bitMap[poids] := str
 * variableMap[str] := bitset
 ************************************************************ */
bitsetPtr Vartable::createVariable(const std::string &str)
{
    bitsetPtr result = bitsetPtr();
    string_to_bitset_const_iterator varTableIt;
    varTableIt = nameToBitsetMap.find(str);
    if (varTableIt == nameToBitsetMap.end())
    {
        result = Bitset::create(variableMapIndex);
        nameToBitsetMap.insert(std::make_pair(str, result));
        size_t i = 0;
        while ((i < variableMapIndex.size()) && !variableMapIndex.test(i))
            ++i;
        Vartable::bitToNameMap[i] = str;
        variableMapIndex <<= 1;
        if (variableMapIndex.none())
            throw fatal_exception("Too much values to create a new variable");
    }
    else
    {
        result = varTableIt->second;
    }
    return result;
}

/* ************************************************************
 *
 ************************************************************ */
uint16_t Vartable::nameToCode(const std::string &str)
{
    uint16_t code;
    string_to_uint16_t_iterator it(nameToCodeMap.find(str));
    if (it == nameToCodeMap.end())
    {
        code = codeMapIndex;
        nameToCodeMap.insert(std::make_pair(str, codeMapIndex));
        codeToNameMap.insert(std::make_pair(codeMapIndex++, str));
        // stringMap[str] = codeMapIndex;
        // codeMap[codeMapIndex++] = str;
    }
    else
        code = it->second;
    return code;
}

/* ************************************************************
 *
 ************************************************************ */
std::string Vartable::codeToName(uint16_t i)
{
    if (i != UINT16_MAX)
        return codeToNameMap[i];
    else
        return std::string("UINT_MAX");
}

/* ************************************************************
 *
 ************************************************************ */
void Vartable::insertCodeMap(const uint16_t key, const std::string &value)
{
    codeToNameMap[key] = std::move(value);
    if (codeMapIndex <= key)
        codeMapIndex = key + 1;
}

/* ************************************************************
 *
 ************************************************************ */
Vartable::uint16_t_to_string_iterator Vartable::bitMapFind(uint16_t key)
{
    return bitToNameMap.find(key);
}

/* ************************************************************
 *
 ************************************************************ */
Vartable::uint16_t_to_string_const_iterator Vartable::bitMapcEnd()
{
    return bitToNameMap.cend();
}

/* ************************************************************
 *
 ************************************************************ */
std::string Vartable::bitToVariable(uint16_t key)
{
    return bitToNameMap[key];
}
