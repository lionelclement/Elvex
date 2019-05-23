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

#ifndef BITSET_H
#define BITSET_H

#ifndef MAXBITS
#define MAXBITS 512
#endif

#include <map>
#include <bitset>

#include "ipointer.hh"
#include "serializable.hh"
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Bitset:
  public enable_shared_from_this< Bitset >,
  public Serializable,
  public std::bitset<MAXBITS> {

  typedef std::map<size_t, std::string, std::less<size_t> > bitsToStrType;

private:
  static const std::bitset<MAXBITS> LEXBITSET;
  static const std::bitset<MAXBITS> ARGBITSET;
  static const std::bitset<MAXBITS> SYSBITSET;
  static const std::bitset<MAXBITS> FIRSTBITSET;

public:
  static bitsToStrType bitsToStrTable;

private:
  Bitset(unsigned int=0);
  Bitset(std::bitset<MAXBITS> &);
  Bitset(bitsetPtr);
  const std::string makeSerializationId();

public:
  ~Bitset();
  static bitsetPtr create(unsigned int=0);
  static bitsetPtr create(std::bitset<MAXBITS>);
  static bitsetPtr create(bitsetPtr);
  std::string _toString(void);
#ifdef OUTPUT_XML
  void toXML(xmlNodePtr);
  #endif
};

#endif // BITSET_H
