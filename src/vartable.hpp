/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI,
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI -- Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef ELVEX_VARTABLE_H
#define ELVEX_VARTABLE_H

#include <string>
#include <bitset>
#include <unordered_map>
#include <map>
#include "bitset.hpp"
#include "shared_ptr.hpp"

class Vartable
{

public:
    static const unsigned int _END_ = 0;
    static const unsigned int _START_TERM_ = 1;

    // variable => bitset
    // i.e. subject => 36 (MAXBITS values)
    typedef std::unordered_map<std::string, bitsetPtr> string_to_bitset;
    typedef string_to_bitset::iterator string_to_bitset_iterator;
    typedef string_to_bitset::const_iterator string_to_bitset_const_iterator;

    // int => variable
    typedef std::unordered_map<unsigned int, std::string> unsigned_int_to_string;
    typedef unsigned_int_to_string::iterator unsigned_int_to_string_iterator;
    typedef unsigned_int_to_string::const_iterator unsigned_int_to_string_const_iterator;

    // string => int
    // i.e. "TO_SAY" => 89 (MAX_UINT values)
    typedef std::unordered_map<std::string, unsigned int> string_to_unsigned_int;
    typedef string_to_unsigned_int::iterator string_to_unsigned_int_iterator;
    typedef string_to_unsigned_int::const_iterator string_to_unsigned_int_const_iterator;

private:
    static std::bitset<MAXBITS> variableMapIndex;
    static unsigned int codeMapIndex;
    static string_to_bitset variableMap;
    static unsigned_int_to_string codeMap;
    static string_to_unsigned_int stringMap;
    static unsigned_int_to_string bitMap;

public:
    Vartable();

    static bitsetPtr createVariable(std::string); // variable -> bitset

    static unsigned int stringToCode(const std::string &); // identifier -> code

    static std::string codeToString(unsigned int);

    static std::string bitToVariable(unsigned int);

    static void insertCodeMap(const unsigned int, std::string);

    static unsigned_int_to_string_iterator bitMapFind(unsigned int);

    static unsigned_int_to_string_const_iterator bitMapcEnd(void);
};

#endif // ELVEX_VARTABLE_H
