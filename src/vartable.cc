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

const unsigned int Vartable::_END_;
const unsigned int Vartable::_START_TERM_;

unsigned int Vartable::codeMapIndex;
std::bitset<MAXBITS> Vartable::variableMapIndex;
Vartable::string_to_bitset Vartable::variableMap;
Vartable::unsigned_int_to_string Vartable::codeMap;
Vartable::string_to_unsigned_int Vartable::stringMap;
Vartable::unsigned_int_to_string Vartable::bitMap;

Vartable vartable;

/* ************************************************************
 *
 ************************************************************ */
Vartable::Vartable() {
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
bitsetPtr Vartable::createVariable(std::string str) {
    bitsetPtr result = bitsetPtr();
    string_to_bitset_const_iterator varTableIt;
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
            throw fatal_exception("Too much values to create a new variable");
    } else {
        result = varTableIt->second;
    }
    return result;
}

/* ************************************************************
 *
 ************************************************************ */
unsigned int Vartable::stringToCode(const std::string& str) {
    unsigned int code;
    string_to_unsigned_int_iterator it(stringMap.find(str));
    if (it == stringMap.end()) {
        code = codeMapIndex;
        stringMap.insert(std::make_pair(str, codeMapIndex));
        codeMap.insert(std::make_pair(codeMapIndex++, str));
        //stringMap[str] = codeMapIndex;
        //codeMap[codeMapIndex++] = str;
    } else
        code = it->second;
    return code;
}

/* ************************************************************
 *
 ************************************************************ */
std::string Vartable::codeToString(unsigned int i) {
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
Vartable::unsigned_int_to_string_iterator Vartable::bitMapFind(unsigned int key) {
    return bitMap.find(key);
}

/* ************************************************************
 *
 ************************************************************ */
Vartable::unsigned_int_to_string_const_iterator Vartable::bitMapcEnd() {
    return bitMap.cend();
}

/* ************************************************************
 *
 ************************************************************ */
std::string Vartable::bitToVariable(unsigned int key) {
    return bitMap[key];
}

