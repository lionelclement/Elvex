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

#include <sstream>
#include <iostream>
#include "messages.hh"
#include "serializable.hh"

/* **************************************************
 *
 ************************************************** */
Serializable::Serializable(){
  NEW;
  serialHashCode = 0;
  serialString = std::string();
}

/* **************************************************
 *
 ************************************************** */
Serializable::~Serializable(){
  DELETE;
}

/* **************************************************
 *
 ************************************************** */
const size_t Serializable::hashCode()
{
  if (serialHashCode == 0) {
    makeSerialString();
    serialHashCode = std::hash<std::string>()(serialString);
  }
  return serialHashCode;
}

/* **************************************************
 *
 ************************************************** */
const std::string Serializable::peekSerialString()
{
  if (serialString.size()==0) {
    makeSerialString();
    serialHashCode = std::hash<std::string>()(serialString);
  }
  return serialString;
}

/* **************************************************
 *
 ************************************************** */
void Serializable::resetSerial(){
  serialHashCode = 0;
  serialString = std::string();
}
