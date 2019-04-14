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

#ifndef INFO_H
#define INFO_H

#include <string>

class Info {
private:
  class Info *next;
  unsigned long int offset;
  unsigned long int adress;

public:
  Info(class Info *next = NULL, unsigned long int offset = 0);
  ~Info();

  class Info *getNext(void) const;
  unsigned long int getOffset(void) const;
  unsigned long int getAdress(void) const;
  void setAdress(unsigned long int adress);

  void printStatic(FILE *) const;
};

#endif // INFO_H
