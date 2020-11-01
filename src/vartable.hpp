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

#ifndef ELVEX_VARTABLE_H
#define ELVEX_VARTABLE_H

#include <string>
#include <bitset>
#include <unordered_map>
#include <map>
#include "bitset.hpp"
#include "shared_ptr.hpp"

class Vartable {

public:
    static const unsigned int END_ = 0;
    static const unsigned int STARTTERM_ = 1;

private:
    static unsigned int codeMapIndex;
    static std::bitset<MAXBITS> variableMapIndex;
    static std::unordered_map<std::string, bitsetPtr> variableMap;
    static std::map<const unsigned int, std::string> codeMap;
    static std::unordered_map<std::string, unsigned int> identifierMap;
    static std::unordered_map<unsigned int, std::string> bitMap;

public:
    Vartable();

    static bitsetPtr createVariable(std::string); // variable -> bitset
    static unsigned int identifierToCode(const std::string&); // identifier -> code
    static std::string codeToIdentifier(unsigned int);

    static std::string bitToVariable(unsigned int);

    static void insertCodeMap(const unsigned int, std::string);

    static std::unordered_map<unsigned int, std::string>::const_iterator bitMapFind(unsigned int);

    static std::unordered_map<unsigned int, std::string>::const_iterator bitMapEnd(void);
};

#endif // ELVEX_VARTABLE_H
