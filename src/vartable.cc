/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2020 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: 
 * Lionel Clément
 * LaBRI -- Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
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

const unsigned int Vartable::END_;
const unsigned int Vartable::STARTTERM_;

unsigned int Vartable::codeMapIndex;
std::bitset<MAXBITS> Vartable::variableMapIndex;
std::unordered_map<std::string, bitsetPtr> Vartable::variableMap;
std::map<const unsigned int, std::string> Vartable::codeMap;
std::unordered_map<std::string, unsigned int> Vartable::identifierMap;
std::unordered_map<unsigned int, std::string> Vartable::bitMap;

Vartable vartable;

/* ************************************************************
 *
 ************************************************************ */
Vartable::Vartable() {
    codeMapIndex = 0;
    variableMapIndex = 1;
    insertCodeMap(END_, "_END_");
    insertCodeMap(STARTTERM_, "_STARTTERM_");
}

/* ************************************************************
 * ajoute une nouvelle variable à la table
 * y associe un poids de bitset
 * bitMap[poids] := str
 * variableMap[str] := bitset
 ************************************************************ */
bitsetPtr Vartable::createVariable(std::string str) {
    bitsetPtr result = bitsetPtr();
    std::unordered_map<std::string, bitsetPtr>::const_iterator varTableIt;
    varTableIt = variableMap.find(str);
    if (varTableIt == variableMap.end()) {
        result = Bitset::create(variableMapIndex);
        variableMap.insert(std::make_pair(str, result));
        size_t i = 0;
        while ((i < variableMapIndex.size()) && !variableMapIndex.test(i))
            ++i;
        Vartable::bitMap[i] = str;
        variableMapIndex <<= 1;
        if (variableMapIndex.none())
            FATAL_ERROR("Too much values")
    } else {
        result = varTableIt->second;
    }
    return result;
}

/* ************************************************************
 *
 ************************************************************ */
unsigned int Vartable::identifierToCode(const std::string& str) {
    unsigned int code;
    std::unordered_map<std::string, unsigned int>::const_iterator it(identifierMap.find(str));
    if (it == identifierMap.end()) {
        code = codeMapIndex;
        identifierMap[str] = codeMapIndex;
        codeMap[codeMapIndex++] = str;
    } else
        code = it->second;
    return code;
}

/* ************************************************************
 *
 ************************************************************ */
std::string Vartable::codeToIdentifier(unsigned int i) {
    if (i != UINT_MAX)
        return codeMap[i];
    else
        return std::string("UINT_MAX");
}

/* ************************************************************
 *
 ************************************************************ */
void Vartable::insertCodeMap(const unsigned int key, std::string value) {
    codeMap[key] = std::move(value);
    if (codeMapIndex <= key)
        codeMapIndex = key + 1;
}

/* ************************************************************
 *
 ************************************************************ */
std::unordered_map<unsigned int, std::string>::const_iterator Vartable::bitMapFind(unsigned int key) {
    return bitMap.find(key);
}

/* ************************************************************
 *
 ************************************************************ */
std::unordered_map<unsigned int, std::string>::const_iterator Vartable::bitMapEnd() {
    return bitMap.end();
}

/* ************************************************************
 *
 ************************************************************ */
std::string Vartable::bitToVariable(unsigned int key) {
    return bitMap[key];
}

