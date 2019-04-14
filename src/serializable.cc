/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2018 LABRI, 
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

#include <sstream>
#include <iostream>
#include "messages.hh"
#include "serializable.hh"

/* **************************************************
 *
 ************************************************** */
Serializable::Serializable(){
  NEW;
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
const std::string Serializable::serialize()
{
  if (serialId.empty())
    serialId = makeSerializationId();
  return serialId;
}

/* **************************************************
 *
 ************************************************** */
void Serializable::resetSerialId(){
  serialId.clear();
}
