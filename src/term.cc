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

#include "term.hh"
#include "vartable.hh"
#include "messages.hh"

/* **************************************************
 *
 ************************************************** */
Term::Term(unsigned int code)
{
  NEW;
  this->code=code;
}

/* **************************************************
 *
 ************************************************** */
Term::~Term()
{
  //DELETE;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Term::getCode(void) const 
{
  return code;
}

/* **************************************************
 *
 ************************************************** */
const bool Term::Less::operator() (const class Term* t1, const class Term* t2) const
{
  if (t1->getCode() != t2->getCode())
    return (t1->getCode() < t2->getCode());
  return false;
}

/* **************************************************
 *
 ************************************************** */
void
Term::print(std::ostream& outStream) const
{
  outStream << Vartable::intToStr(code);
}

/* **************************************************
 *
 ************************************************** */
std::string
Term::toString() const
{
  return Vartable::intToStr(code);
}

/* **************************************************
 *
 ************************************************** */
class Term* 
Term::clone() const
{
  return new Term(code);
}
