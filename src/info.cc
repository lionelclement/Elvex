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

#include "info.hh"
#include "messages.hh"

/* **************************************************
 *
 ************************************************** */
Info::Info(class Info *next, unsigned long int offset)
{
  NEW;
  address = 0;
  this->next = next;
  this->offset = offset;
}

/* **************************************************
 *
 ************************************************** */
Info::~Info()
{
  if (next) {
    delete(next);
    next = NULL;
  }
  DELETE;
}

/* **************************************************
 *
 ************************************************** */
class Info *Info::getNext(void) const
{
  return next;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int Info::getOffset(void) const 
{
  return offset;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int Info::getAddress(void) const 
{
  return address;
}

/* **************************************************
 *
 ************************************************** */
void Info::setAddress(unsigned long int address)
{
  this->address=address;
}

