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
ForestIdentifier::ForestIdentifier (unsigned int code, std::string featuresSerialID, unsigned int from, unsigned int to)
{
  NEW;
  this->code = code;
  this->featuresSerialID = featuresSerialID;
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
forestIdentifierPtr ForestIdentifier::create(unsigned int code, std::string featuresSignature, unsigned int from, unsigned int to)  
{
  return forestIdentifierPtr( new ForestIdentifier(code, featuresSignature, from, to) );
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
const bool
ForestIdentifier::operator <(const ForestIdentifier &o) const
{
  return ((this->code < o.code)||(this->from < o.from)||(this->to < o.to)||(this->featuresSerialID < o.featuresSerialID));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
const bool
ForestIdentifier::operator !=(const ForestIdentifier &o) const
{
  return ((this->code != o.code)||(this->from != o.from)||(this->to != o.to)||(this->featuresSerialID != o.featuresSerialID));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
const bool
ForestIdentifier::Less::operator()(const forestIdentifierPtr lhs, const forestIdentifierPtr rhs) const
{
  if (lhs->code < rhs->code){
    return true;
  }
  if (lhs->code > rhs->code){
    return false;
  }
  if (lhs->from < rhs->from){
    return true;
  }
  if (lhs->from > rhs->from){
    return false;
  }
  if (lhs->to < rhs->to){
    return true;
  }
  if (lhs->to > rhs->to){
    return false;
  }
  if (lhs->featuresSerialID < rhs->featuresSerialID) {
    return true;
  }
  if (lhs->featuresSerialID > rhs->featuresSerialID) {
    return false;
  }
  return false;
}

/* **************************************************
 *
 ************************************************** */
const std::string
ForestIdentifier::makeSerializationId()
{
  return Vartable::intToStr(code)
    + std::to_string(code)
    + '['
    + std::to_string(from)
    + '-'
    + std::to_string(to)
    + ']';
}

/* **************************************************
 *
 ************************************************** */
void 
ForestIdentifier::print(std::ostream& out) const
{
  out << "#" << Vartable::intToStr(code) << code << '[' << from << '-' << to << ']';
}
