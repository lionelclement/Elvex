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

#ifndef FLAGS_H
#define FLAGS_H

#include <bitset>

class Flags {

public:
  static const size_t NBRFLAGS=8;
  static const std::bitset<NBRFLAGS> SEEN;
  static const std::bitset<NBRFLAGS> XML;
  static const std::bitset<NBRFLAGS> GEN;
  static const std::bitset<NBRFLAGS> DISABLED;
  static const std::bitset<NBRFLAGS> NIL;
  static const std::bitset<NBRFLAGS> BOTTOM;
  static const std::bitset<NBRFLAGS> REJECTED;
  static const std::bitset<NBRFLAGS> CHOOSEN;
  
private:
  std::bitset<NBRFLAGS> flags;
  
public:
  Flags(void);
  Flags(const std::bitset<NBRFLAGS> &flags);
  ~Flags(void);
  
  std::bitset<NBRFLAGS> &getFlags(void);
  bool isSetFlags(const std::bitset<NBRFLAGS>&  cmp) const;
  bool isUnsetFlags(const std::bitset<NBRFLAGS>&  cmp) const;
  void setFlags(const std::bitset<NBRFLAGS> &flags);
  void resetFlags(void);
  void addFlags(const std::bitset<NBRFLAGS>& f);
  void subFlags(const std::bitset<NBRFLAGS>& f);
  void printFlags(std::ostream&) const;
  
};

#endif // FLAGS_H
