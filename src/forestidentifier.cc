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

#include "forestidentifier.hh"
#include "vartable.hh"
#include "messages.hh"
#include "entry.hh"

/* ************************************************************
 *                                                            *
 ************************************************************ */
ForestIdentifier::ForestIdentifier (unsigned int code, std::string const featuresSerialString, unsigned int from, unsigned int to)
{
  NEW;
  this->code = code;
  this->featuresSerialString = featuresSerialString;
  this->from = from;
  this->to = to;
}

/* **************************************************
 *
 ************************************************** */
ForestIdentifier::~ForestIdentifier ()
{
  DELETE;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
forestIdentifierPtr ForestIdentifier::create(unsigned int code, std::string const featuresSerialString, unsigned int from, unsigned int to)  
{
  return forestIdentifierPtr( new ForestIdentifier(code, featuresSerialString, from, to) );
}

/* **************************************************
 *
 ************************************************** */
void 
ForestIdentifier::makeSerialString(void)
{
  serialString = std::to_string(code);
  serialString += '[';
  serialString += from;
  serialString += '-';
  serialString += to;
  serialString += ']';
  serialString += featuresSerialString;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool
ForestIdentifier::operator <(ForestIdentifier const &o) const
{
   return ((this->code < o.code)
    	  ||(this->from < o.from)
    	  ||(this->to < o.to)
    	  ||(this->featuresSerialString < o.featuresSerialString));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool
ForestIdentifier::operator !=(ForestIdentifier const &o) const
{
   return ((this->code != o.code)
   	  ||(this->from != o.from)
   	  ||(this->to != o.to)
   	  ||(this->featuresSerialString != o.featuresSerialString));
}

/* **************************************************
 *
 ************************************************** */
void 
ForestIdentifier::print(std::ostream& out) const
{
  out << "#" << code << '[' << from << '-' << to << ']';
}

///* ************************************************************
// *                                                            *
// ************************************************************ */
//bool
//ForestIdentifier::_less::operator()(forestIdentifierPtr const lhs, forestIdentifierPtr const rhs) const
//{
//  if (lhs->code != rhs->code)
//    return lhs->code < rhs->code;
//  if (lhs->from != rhs->from)
//    return lhs->from < rhs->from;
//  if (lhs->to != rhs->to)
//    return lhs->to < rhs->to;
//  if (lhs->featuresSerialString != rhs->featuresSerialString)
//    return lhs->featuresSerialString < rhs->featuresSerialString;
//  return false;
//}
//
/* **************************************************
 *
 ************************************************** */
size_t ForestIdentifier::hash::operator() (forestIdentifierPtr const i) const
{
  return i->hashCode();
}

/* **************************************************
 *
 ************************************************** */
bool ForestIdentifier::equal_to::operator() (forestIdentifierPtr const i1, forestIdentifierPtr const i2) const
{
  return i1->peekSerialString() == i2->peekSerialString();
}

