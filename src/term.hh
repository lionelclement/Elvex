/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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

#ifndef TERM_H
#define TERM_H

#include <iostream>
#include "flags.hh"

class Term:
  public Flags {

private:
  unsigned int code;

public:
  Term(unsigned int code=0);
  ~Term();

  unsigned int getCode(void) const;
  void print(std::ostream &outStream=std::cout) const;
  std::string toString() const;
  class Term* clone();

  // compare deux termes
  struct Less {
    const bool operator() (const Term *t1, const Term *t2) const;
  };

};  

#endif // TERM_H
