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

#include "fsa.hh"

/* **************************************************
 *
 ************************************************** */
Fsa::Fsa(unsigned long int child, unsigned long int sibling, unsigned long int info, char letter) {
  this->child = child;
  this->sibling = sibling;
  this->info = info;
  this->letter = letter;
}

/* **************************************************
 *
 ************************************************** */
Fsa::Fsa(void) {
  this->child = (unsigned long int)~0UL;
  this->sibling =  (unsigned long int)~0UL;
  this->info =  (unsigned long int)~0UL;
  this->letter =  (char)~0;
}

/* **************************************************
 *
 ************************************************** */
void Fsa::print(std::ostream& out) const
{
  out << (long int)child << ' ' << (long int)sibling << ' ' << (long int)info << ' ' << (int)letter << std::endl;
}

/* **************************************************
 *
 ************************************************** */
bool Fsa::isChild() const
{
  return child != (unsigned long int)(~0UL);
}

/* **************************************************
 *
 ************************************************** */
bool Fsa::isSibling() const
{
  return sibling != (unsigned long int)(~0UL);
}

/* **************************************************
 *
 ************************************************** */
bool Fsa::isInfo() const
{
  return info != (unsigned long int)(~0UL);
}

/* **************************************************
 *
 ************************************************** */
unsigned long int Fsa::getChild(void) {
  return child;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int Fsa::getSibling(void) {
  return sibling;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int Fsa::getInfo(void) {
  return info;
}

/* **************************************************
 *
 ************************************************** */
bool Fsa::isLetter(char letter) {
  return letter == this->letter;
}
