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

#include "id.hh"
#include "messages.hh"

idType Id::uniqId=1;

/* **************************************************
 *
 ************************************************** */
Id::Id()
{
  NEW;
  this->id = ++uniqId;
  if (this->id == 0) {
    std::cerr << "*** too ids" << std::endl;
    FATAL_ERROR;
  }
}

/* **************************************************
 *
 ************************************************** */
Id::~Id()
{
  DELETE;
}

/* **************************************************
 *
 ************************************************** */
const idType Id::getId(void) const
{
  return this->id;
}
