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

#ifndef TERM_H
#define TERM_H

#include <iostream>
#include "flags.hh"
#include "shared_ptr.hh"

class Term:
      public Flags, public std::enable_shared_from_this<class Term> {

private:
   unsigned int code;
   Term(unsigned int code);

public:
   ~Term();
   static termPtr create(unsigned int code = 0);

   unsigned int getCode(void) const;
   void print(std::ostream &outStream = std::cout) const;
   std::string toString() const;
   termPtr clone() const;

   // compare deux termes
   struct Less {
      const bool operator()(const termPtr t1, const termPtr t2) const;
   };

};

#endif // TERM_H
