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

#include "infobuff.hh"

/* **************************************************
 *
 ************************************************** */
InfoBuff::InfoBuff(unsigned long int next, unsigned long int offset) {
  this->next = next;
  this->offset = offset;
}

/* **************************************************
 *
 ************************************************** */
InfoBuff::InfoBuff(void) {
  this->next = (unsigned long int)(~0UL);
  this->offset = (unsigned long int)(~0UL);
}

/* **************************************************
 *
 ************************************************** */
unsigned long int InfoBuff::getOffset() const
{
  return offset;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int InfoBuff::getNext() const
{
  return next;
}

/* **************************************************
 *
 ************************************************** */
bool InfoBuff::isNext() const
{
  return next != (unsigned long int)(~0UL);
}

/* **************************************************
 *
 ************************************************** */
bool InfoBuff::isOffset() const
{
  return offset != (unsigned long int)(~0UL);
}

/* **************************************************
 *
 ************************************************** */
void InfoBuff::print(std::ostream& out) const
{
  out << (long int)next << ' ' << (long int)offset << std::endl;
}

