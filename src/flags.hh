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
  static const int FLAGS = 8;
  static const std::bitset<FLAGS> SEEN;
  static const std::bitset<FLAGS> XML;
  static const std::bitset<FLAGS> GEN;
  static const std::bitset<FLAGS> DISABLED;
  static const std::bitset<FLAGS> NIL;
  static const std::bitset<FLAGS> BOTTOM;
  static const std::bitset<FLAGS> REJECTED;
  static const std::bitset<FLAGS> CHOOSEN;
  
private:
  std::bitset<FLAGS> flags;
  
public:
  Flags(void);
  Flags(const std::bitset<FLAGS> &flags);
  //~Flags(void);
  
  std::bitset<FLAGS> &getFlags(void);
  //void setFlags(const std::bitset<FLAGS> &flags);
    bool isSetFlags(const std::bitset<FLAGS>& cmp) const;
  bool isUnsetFlags(const std::bitset<FLAGS>& cmp) const;
  void resetFlags(void);
  void addFlags(const std::bitset<FLAGS> &f);
  void subFlags(const std::bitset<FLAGS> &f);
  void printFlags(std::ostream&) const;
  
};

#endif // FLAGS_H
