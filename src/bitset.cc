/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2018 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: Lionel Clément,
 * Labri -- 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#include <map>

#include "bitset.hh"
#include "flags.hh"
#include "vartable.hh"
#include "messages.hh"
#include "ipointer.hh"

const std::bitset< MAXBITS> Bitset::LEXBITSET = 1ul;
const std::bitset< MAXBITS> Bitset::ARGBITSET = Bitset::LEXBITSET << 1;
const std::bitset< MAXBITS> Bitset::SYSBITSET = Bitset::ARGBITSET << 1;
const std::bitset< MAXBITS> Bitset::FIRSTBITSET = Bitset::SYSBITSET << 1;

Bitset::bitsToStrType Bitset::bitsToStrTable;

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(unsigned int data): std::bitset< MAXBITS>(data)
{
  NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(std::bitset< MAXBITS>& data): std::bitset< MAXBITS>(data)
{
  NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(bitsetPtr bitset): std::bitset< MAXBITS>(*bitset)
{
  NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::~Bitset()
{
  DELETE;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr Bitset::create(unsigned int data)
{
  return shared_ptr< Bitset >( new Bitset(data) );
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr Bitset::create(std::bitset< MAXBITS> data)
{
  return shared_ptr< Bitset >( new Bitset(data) );
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr Bitset::create(bitsetPtr bs)
{
  return shared_ptr< Bitset >( new Bitset(bs) );
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
std::string
Bitset::toString()
{
  std::stringstream s;
  size_t c=this->count();
  size_t sz=this->size();
  bool first=true;
  for( size_t i = 0 ; i < sz && c > 0 ; ++i) {
    if (this->test(i)){
      --c;
      if (first) first=false; else s<<'|';
      s << bitsToStrTable[i];
    }
  }
  return s.str();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
const std::string
Bitset::makeSerializationId()
{
  size_t c = this->count();
  size_t sz = this->size();
  bool first = true;
  serialId.clear();
  for( size_t i = 0 ; i < sz && c > 0 ; ++i) {
    if (this->test(i)){
      --c;
      if (first) first=false; else serialId += '|';
      serialId += std::to_string(i);
    }
  }
  return serialId;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
unsigned int
Bitset::toFirstInt()
{
  size_t sz=this->size();
  for(size_t i = 0 ; i < sz; ++i )
    if (this->test(i))
      return i;
  return 0;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
unsigned int
Bitset::toFirstInt(std::bitset< MAXBITS> b)
{
  size_t sz=b.size();
  for(size_t i = 0 ; i < sz; ++i )
    if (b.test(i))
      return i;
  return 0;
}

#ifdef OUTPUT_XML
/* ************************************************************
 *                                                            *
 ************************************************************ */
void Bitset::toXML(xmlNodePtr nodeRoot)
{
  xmlNodePtr f=xmlNewChild(nodeRoot, NULL, (const xmlChar*)"ALT", NULL);
  bitsToStrType::const_iterator varTableIt;
  size_t c=this->count();
  size_t sz=this->size();
  for(unsigned int i = 0 ; i < sz && c > 0; ++i)
    if (this->test(i)){
      --c;
      varTableIt = bitsToStrTable.find(i);
      if (varTableIt != bitsToStrTable.end())
	xmlNewChild(f, NULL, (const xmlChar*)"OPT", (const xmlChar*)varTableIt->second.c_str());
    }
}
#endif
