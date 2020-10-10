/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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
#include "bitset.h"
#include "shared_ptr.h"

class Vartable {

public:
    static const unsigned int _END_ = 0;
    static const unsigned int _STARTTERM_ = 1;
    static const unsigned int _EMPTY_ = 2;
    static const unsigned int _OPEN_ = 3;
    static const unsigned int _FIRSTID_ = 4;

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
    static unsigned int identifierToCode(std::string); // identifier -> code
    static std::string codeToIdentifier(unsigned int);

    static std::string bitToVariable(unsigned int);

    static void insertCodeMap(const unsigned int, std::string);

    static std::unordered_map<unsigned int, std::string>::const_iterator bitMapFind(unsigned int);

    static std::unordered_map<unsigned int, std::string>::const_iterator bitMapEnd(void);
};

#endif // ELVEX_VARTABLE_H
