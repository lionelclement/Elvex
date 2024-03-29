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
    static uint32_t IS_A_FORM;
    static uint32_t DOES_NOT_CONTAIN_A_HEAD;


    // symbol => bitset
    // i.e. subject => 36 (MAXBITS values)
    typedef std::unordered_map<std::string, bitsetPtr> string_to_bitset;
    typedef string_to_bitset::iterator string_to_bitset_iterator;
    typedef string_to_bitset::const_iterator string_to_bitset_const_iterator;

    // int => variable
    typedef std::unordered_map<uint32_t, std::string> uint32_t_to_string;
    typedef uint32_t_to_string::iterator uint32_t_to_string_iterator;
    typedef uint32_t_to_string::const_iterator uint32_t_to_string_const_iterator;

    // string => int
    // i.e. "TO_SAY" => 89 (MAX_UINT values)
    typedef std::unordered_map<std::string, uint32_t> string_to_uint32_t;
    typedef string_to_uint32_t::iterator string_to_uint32_t_iterator;
    typedef string_to_uint32_t::const_iterator string_to_uint32_t_const_iterator;

private:
    static std::bitset<MAXBITS> variableMapIndex;
    static uint32_t codeMapIndex;
    static string_to_bitset nameToBitsetMap;
    static uint32_t_to_string codeToNameMap;
    static string_to_uint32_t nameToCodeMap;
    static uint32_t_to_string bitToNameMap;

public:
    Vartable();

    static bitsetPtr createSymbol(const std::string &); // variable -> bitset

    static bitsetPtr createSymbol(const std::string &name, uint32_t code);

    static uint32_t nameToCode(const std::string &); // identifier -> code

    static uint32_t nameToCode(const std::string &, uint32_t code); // identifier -> code

    static std::string &codeToName(uint32_t); // code -> identifier

    static std::string &bitToName(uint32_t); // bit weight -> identifier 

    static void insertCodeMap(const uint32_t, const std::string &);

    static uint32_t_to_string_iterator bitMapFind(uint32_t);

    static uint32_t_to_string_const_iterator bitMapcEnd(void);

    static void renameVariables(std::string &data, uint32_t code);

};

#endif // ELVEX_VARTABLE_H
