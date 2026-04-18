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

#include <climits>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "vartable.hpp"
#include "messages.hpp"

uint32_t Vartable::codeMapIndex = 0;
std::bitset<MAXBITS> Vartable::variableMapIndex = std::bitset<MAXBITS>(1);

Vartable::string_to_bitset Vartable::nameToBitsetMap;
Vartable::uint32_t_to_string Vartable::codeToNameMap;
Vartable::string_to_uint32_t Vartable::nameToCodeMap;
Vartable::uint32_t_to_string Vartable::bitToNameMap;

uint32_t Vartable::code_for_IS_A_FORM = 0;
uint32_t Vartable::code_for_DOES_NOT_CONTAIN_A_HEAD = 0;

Vartable vartable;

/* ************************************************************
 *
 ************************************************************ */
Vartable::Vartable()
{
    codeMapIndex = 0;
    variableMapIndex.reset();
    variableMapIndex.set(0);

    nameToBitsetMap.clear();
    codeToNameMap.clear();
    nameToCodeMap.clear();
    bitToNameMap.clear();

    createSymbol(CONTAINS_A_FORM);
    code_for_IS_A_FORM = nameToCode(CONTAINS_A_FORM);

    createSymbol(DOES_NOT_CONTAIN_A_HEAD);
    code_for_DOES_NOT_CONTAIN_A_HEAD = nameToCode(DOES_NOT_CONTAIN_A_HEAD);
}

/* ************************************************************
 *
 ************************************************************ */
std::string Vartable::makeScopedName(const std::string& name, uint32_t key)
{
    std::ostringstream oss;
    oss << name << '_' << std::hex << key;
    return oss.str();
}

/* ************************************************************
 *
 ************************************************************ */
std::string Vartable::makeHexSuffix(uint32_t key)
{
    std::ostringstream oss;
    oss << '_' << std::hex << key;
    return oss.str();
}

/* ************************************************************
 *
 ************************************************************ */
bool Vartable::isVariableStart(unsigned char c)
{
    return std::isalpha(c) || c == '_' || c >= 128;
}

/* ************************************************************
 *
 ************************************************************ */
bool Vartable::isVariableChar(unsigned char c)
{
    return std::isalnum(c) || c == '_' || c >= 128;
}

/* ************************************************************
 * ajoute une nouvelle variable à la table
 * y associe un poids de bitset
 * bitMap[poids] := str
 * variableMap[str] := bitset
 ************************************************************ */
bitsetPtr Vartable::createSymbol(const std::string& name)
{
    const auto it = nameToBitsetMap.find(name);
    if (it != nameToBitsetMap.end())
    {
        return it->second;
    }

    if (variableMapIndex.none())
    {
        throw fatal_exception("Too much values to create a new symbol (" + name + " not created)");
    }

    bitsetPtr result = Bitset::create(variableMapIndex);
    nameToBitsetMap.emplace(name, result);

    size_t bitIndex = 0;
    while (bitIndex < variableMapIndex.size() && !variableMapIndex.test(bitIndex))
    {
        ++bitIndex;
    }

    if (bitIndex >= variableMapIndex.size())
    {
        throw fatal_exception("Internal error while creating symbol (" + name + ")");
    }

    bitToNameMap[static_cast<uint32_t>(bitIndex)] = name;

    variableMapIndex <<= 1;

    return result;
}

/* ************************************************************
 *
 ************************************************************ */
bitsetPtr Vartable::createSymbol(const std::string& name, uint32_t key)
{
    return createSymbol(makeScopedName(name, key));
}

/* ************************************************************
 *
 ************************************************************ */
uint32_t Vartable::nameToCode(const std::string& name)
{
    const auto it = nameToCodeMap.find(name);
    if (it != nameToCodeMap.end())
    {
        return it->second;
    }

    if (codeMapIndex == UINT32_MAX)
    {
        throw fatal_exception("Too much values to create a new variable (" + name + " not created)");
    }

    const uint32_t code = codeMapIndex;
    nameToCodeMap.emplace(name, code);
    codeToNameMap.emplace(code, name);
    ++codeMapIndex;

    return code;
}

/* ************************************************************
 *
 ************************************************************ */
uint32_t Vartable::nameToCode(const std::string& name, uint32_t key)
{
    return nameToCode(makeScopedName(name, key));
}

/* ************************************************************
 *
 ************************************************************ */
const std::string& Vartable::codeToName(uint32_t code)
{
    const auto it = codeToNameMap.find(code);
    if (it == codeToNameMap.end())
    {
        throw fatal_exception("Unknown code in codeToName: " + std::to_string(code));
    }
    return it->second;
}

/* ************************************************************
 *
 ************************************************************ */
void Vartable::insertCodeMap(uint32_t key, const std::string& value)
{
    codeToNameMap[key] = value;
    nameToCodeMap[value] = key;

    if (codeMapIndex <= key)
    {
        codeMapIndex = key + 1;
    }
}

/* ************************************************************
 *
 ************************************************************ */
Vartable::uint32_t_to_string_iterator Vartable::bitMapFind(uint32_t key)
{
    return bitToNameMap.find(key);
}

/* ************************************************************
 *
 ************************************************************ */
Vartable::uint32_t_to_string_const_iterator Vartable::bitMapcEnd()
{
    return bitToNameMap.cend();
}

/* ************************************************************
 *
 ************************************************************ */
const std::string& Vartable::bitToName(uint32_t key)
{
    const auto it = bitToNameMap.find(key);
    if (it == bitToNameMap.end())
    {
        throw fatal_exception("Unknown bit in bitToName: " + std::to_string(key));
    }
    return it->second;
}

/* **************************************************
 *
 ************************************************** */
void Vartable::renameVariables(std::string& data, uint32_t key)
{
    if (data.find('$') == std::string::npos)
    {
        return;
    }

    const std::string suffix = makeHexSuffix(key);

    std::string output;
    output.reserve(data.size() + 16);

    size_t i = 0;
    while (i < data.size())
    {
        if (data[i] != '$')
        {
            output.push_back(data[i]);
            ++i;
            continue;
        }

        if (i + 1 >= data.size())
        {
            output.push_back(data[i]);
            ++i;
            continue;
        }

        const unsigned char first = static_cast<unsigned char>(data[i + 1]);
        if (!isVariableStart(first))
        {
            output.push_back(data[i]);
            ++i;
            continue;
        }

        const size_t begin = i;
        i += 2;

        while (i < data.size())
        {
            const unsigned char c = static_cast<unsigned char>(data[i]);
            if (!isVariableChar(c))
            {
                break;
            }
            ++i;
        }

        output.append(data, begin, i - begin);
        output += suffix;
    }

    data.swap(output);
}