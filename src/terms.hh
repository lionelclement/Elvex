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

#ifndef TERMS_H
#define TERMS_H

#include <iostream>
#include <vector>
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif
#include "flags.hh"

class Terms {

private:
  std::vector< class Term * > terms;
  bool optional;

public:
  Terms(std::vector<class Term *> &, bool optional=false);
  Terms(class Term *, bool optional=false);
  ~Terms();

  bool isOptional(void) const;
  void setOptional(void);
  void unsetOptional(void);

  size_t size(void) const;
  std::vector<class Term *>::const_iterator begin(void) const;
  std::vector<class Term *>::const_iterator end(void) const;
  void erase(std::vector<class Term*>::iterator begin, std::vector<class Term *>::iterator end);
  void push_back(class Term * term);

  void print(std::ostream &outStream=std::cout);
  class Terms *clone(void) const;
#ifdef OUTPUT_XML
  void toXML(const xmlNodePtr);
#endif

  // compare deux termes
  struct Less {
    const bool operator() (const class Terms *t1, const class Terms *t2) const;
  };

  class Term *operator[] (unsigned int);
};  

#endif // TERMS_H
