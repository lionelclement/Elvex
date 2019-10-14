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

#include <climits>
#include <sstream>
#include <map>
#include <unordered_map>
#include "vartable.hh"

const unsigned int Vartable::_END_;
const unsigned int Vartable::_STARTTERM_;
const unsigned int Vartable::_EMPTY_;
const unsigned int Vartable::_OPEN_;
const unsigned int Vartable::_FIRSTID_;

unsigned int Vartable::intToStrIndex;
std::bitset<MAXBITS> Vartable::varTableIndex;
std::unordered_map<std::string, bitsetPtr > Vartable::varTable;
std::map< unsigned int, std::string > Vartable::intToStrTable;
std::unordered_map<std::string, unsigned int > Vartable::strToIntTable;

/* **************************************************
 *
 ************************************************** */
void
Vartable::init()
{
  intToStrTable[_END_]="_END_";
  intToStrTable[_STARTTERM_]="_STARTTERM_";
  intToStrTable[_EMPTY_]="_EMPTY_";
  intToStrTable[_OPEN_]="_OPEN_";
  intToStrTable[_FIRSTID_]="_FIRSTID_";
  intToStrIndex = _FIRSTID_ + 1;
  varTableIndex = 1;
}

/* ************************************************************
 * ajoute une nouvelle variable à la table
 * y associe un poids de bitset
 * bitsToStrTable[poids] := str
 * varTable[str] := bitset
 ************************************************************ */
bitsetPtr
Vartable::varTableAdd(std::string str)
{
  bitsetPtr result = bitsetPtr();
  std::unordered_map<std::string, bitsetPtr >::const_iterator varTableIt;
  varTableIt = varTable.find(str);
  if (varTableIt == varTable.end()) {
    result=Bitset::create(varTableIndex);
    varTable.insert (std::make_pair(str, result));

    size_t i=0;
    while ((i < varTableIndex.size()) && !varTableIndex.test(i))
      ++i;
    Bitset::bitsToStrTable[i]=str;
    varTableIndex <<= 1;

    if (varTableIndex.none())
      throw "Too much values";

  } else 
    result=varTableIt->second;
  return result;
}

/* **************************************************
 *
 ************************************************** */
unsigned int
Vartable::strToInt(std::string str)
{
  unsigned int code;
  std::unordered_map<std::string, unsigned int >::const_iterator it(strToIntTable.find(str));
  if (it==strToIntTable.end()){
    code=intToStrIndex;
    strToIntTable[str]=intToStrIndex;
    intToStrTable[intToStrIndex++]=str;
  }
  else
    code = it->second;
  return code;
}

/* **************************************************
 *
 ************************************************** */
std::string
Vartable::intToStr(unsigned int i)
{
  if (i!=UINT_MAX)
    return intToStrTable[i];
  else
    return std::string("UINT_MAX");
}
