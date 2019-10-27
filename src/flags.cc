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

#include "flags.hh"
#include "messages.hh"

const std::bitset<Flags::FLAGS> Flags::SEEN 			= 	std::bitset<Flags::FLAGS>(1ul<<1);
const std::bitset<Flags::FLAGS> Flags::XML	 		= 	std::bitset<Flags::FLAGS>(1ul<<2);
const std::bitset<Flags::FLAGS> Flags::GEN 			= 	std::bitset<Flags::FLAGS>(1ul<<3);
const std::bitset<Flags::FLAGS> Flags::DISABLED		= 	std::bitset<Flags::FLAGS>(1ul<<4);
const std::bitset<Flags::FLAGS> Flags::NIL			= 	std::bitset<Flags::FLAGS>(1ul<<5);
const std::bitset<Flags::FLAGS> Flags::BOTTOM		= 	std::bitset<Flags::FLAGS>(1ul<<6);
const std::bitset<Flags::FLAGS> Flags::CHOOSEN		= 	std::bitset<Flags::FLAGS>(1ul<<7);
const std::bitset<Flags::FLAGS> Flags::REJECTED		= 	std::bitset<Flags::FLAGS>(1ul<<8);

/* **************************************************
 *
 ************************************************** */
Flags::Flags(void)
{
  this->flags = 0;
}

/* **************************************************
 *
 ************************************************** */
Flags::Flags(const std::bitset<Flags::FLAGS> &flags)
{
  this->flags = flags;
}

/* **************************************************
 *
 ************************************************** */
//Flags::~Flags(void)
//{
//}

///* **************************************************
// *
// ************************************************** */
//void Flags::setFlags(const std::bitset<Flags::FLAGS> &flags)
//{
//  this->flags = flags;
//}
//
/* **************************************************
 *
 ************************************************** */
std::bitset<Flags::FLAGS> &Flags::getFlags(void)
{
  return this->flags;
}

/* **************************************************
 *
 ************************************************** */
void Flags::resetFlags(void)
{
  this->flags = 0;
}

/* **************************************************
 *
 ************************************************** */
bool Flags::isSetFlags(const std::bitset<Flags::FLAGS> &cmp) const
{
  return (this->flags & cmp).any();
}

/* **************************************************
 *
 ************************************************** */
bool Flags::isUnsetFlags(const std::bitset<Flags::FLAGS> &cmp) const
{
  return (this->flags & cmp).none();
}

/* **************************************************
 *
 ************************************************** */
void Flags::addFlags(const std::bitset<Flags::FLAGS> &f)
{
  this->flags |= f;
}

/* **************************************************
 *
 ************************************************** */
void Flags::subFlags(const std::bitset<Flags::FLAGS> &f)
{
  this->flags &= ~f;
}

/* **************************************************
 *
 ************************************************** */
void 
Flags::printFlags(std::ostream &outStream) const
{
  if (isSetFlags(Flags::SEEN))
    outStream << "SEEN ";
  if (isSetFlags(XML))
    outStream << "XML ";
  if (isSetFlags(GEN))
    outStream << "GEN ";
  if (isSetFlags(DISABLED))
    outStream << "DISABLED ";
  if (isSetFlags(NIL))
    outStream << "NIL ";
  if (isSetFlags(BOTTOM))
    outStream << "BOTTOM ";
  if (isSetFlags(CHOOSEN))
    outStream << "CHOOSEN ";
  if (isSetFlags(REJECTED))
    outStream << "REJECTED ";
}
