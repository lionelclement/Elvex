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
#include <regex>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>

#include "vartable.hpp"
#include "messages.hpp"

uint32_t Vartable::codeMapIndex;
std::bitset<MAXBITS> Vartable::variableMapIndex;
Vartable::string_to_bitset Vartable::nameToBitsetMap;
Vartable::uint32_t_to_string Vartable::codeToNameMap;
Vartable::string_to_uint32_t Vartable::nameToCodeMap;
Vartable::uint32_t_to_string Vartable::bitToNameMap;
uint32_t Vartable::IS_A_FORM;
uint32_t Vartable::DOES_NOT_CONTAIN_A_HEAD;

Vartable vartable;

/* ************************************************************
 *
 ************************************************************ */
Vartable::Vartable()
{
    codeMapIndex = 0;
    variableMapIndex = 1;
    createSymbol("CONTAINS_A_FORM");
    IS_A_FORM = nameToCode("CONTAINS_A_FORM");
    createSymbol("DOES_NOT_CONTAIN_A_HEAD");
    DOES_NOT_CONTAIN_A_HEAD = nameToCode("DOES_NOT_CONTAIN_A_HEAD");
}

/* ************************************************************
 * ajoute une nouvelle variable à la table
 * y associe un poids de bitset
 * bitMap[poids] := str
 * variableMap[str] := bitset
 ************************************************************ */
bitsetPtr Vartable::createSymbol(const std::string &name)
{
    bitsetPtr result = bitsetPtr();
    string_to_bitset_const_iterator varTableIt;
    varTableIt = nameToBitsetMap.find(name);
    if (varTableIt == nameToBitsetMap.end())
    {
        result = Bitset::create(variableMapIndex);
        nameToBitsetMap.insert(std::make_pair(name, result));
        size_t i = 0;
        while ((i < variableMapIndex.size()) && !variableMapIndex.test(i))
            ++i;
        Vartable::bitToNameMap[i] = name;
        variableMapIndex <<= 1;
        if (variableMapIndex.none())
            throw fatal_exception("Too much values to create a new variable (" + name + " not created)");
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
bitsetPtr Vartable::createSymbol(const std::string &name, uint32_t key)
{
    std::stringstream ss;
    ss << name << '_' << std::hex << key;
    return Vartable::createSymbol(ss.str());
}

/* ************************************************************
 *
 ************************************************************ */
uint32_t Vartable::nameToCode(const std::string &name)
{
    uint32_t code;
    string_to_uint32_t_iterator it(nameToCodeMap.find(name));
    if (it == nameToCodeMap.end())
    {
        code = codeMapIndex;
        nameToCodeMap.insert(std::make_pair(name, codeMapIndex));
        codeToNameMap.insert(std::make_pair(codeMapIndex++, name));
    }
    else
        code = it->second;
    return code;
}

/* ************************************************************
 *
 ************************************************************ */
uint32_t Vartable::nameToCode(const std::string &name, uint32_t key)
{
    std::stringstream ss;
    ss << name << '_' << std::hex << key;
    return Vartable::nameToCode(ss.str());
}

/* ************************************************************
 *
 ************************************************************ */
std::string &Vartable::codeToName(uint32_t i)
{
    return codeToNameMap[i];
}

/* ************************************************************
 *
 ************************************************************ */
void Vartable::insertCodeMap(const uint32_t key, const std::string &value)
{
    codeToNameMap[key] = value;
    if (codeMapIndex <= key)
        codeMapIndex = key + 1;
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
std::string &Vartable::bitToName(uint32_t key)
{
    return bitToNameMap[key];
}

/* **************************************************
 *
 ************************************************** */
void Vartable::renameVariables(std::string &data, uint32_t key)
{

    size_t found = data.find('$');

    if (found != (std::string::npos))
    {
        std::string pattern =
            std::string(
                "(\\$([a-zA-Z_]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß)([a-zA-Z0-9_]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß)*)");
        std::cmatch match;

        try
        {
            std::regex regexpression(pattern, std::regex_constants::ECMAScript);
            if (std::regex_search(data.c_str(), match, regexpression))
            {
                auto match_begin = std::sregex_iterator(data.begin(), data.end(), regexpression);
                auto match_end = std::sregex_iterator();
                for (std::sregex_iterator i = match_begin; i != match_end; ++i)
                {
                    std::string match_str = i->str();
                    std::ostringstream oss;
                    oss << match_str << '_' << std::hex << (int)key;
                    data = std::regex_replace(data, regexpression, oss.str(), std::regex_constants::format_first_only);
                }
            }
        }
        catch (const std::regex_error &e)
        {
            std::cout << "regex_error caught: " << e.what() << '(' << e.code() << ')' << std::regex_constants::error_brack
                      << '\n';
        }
    }
}
