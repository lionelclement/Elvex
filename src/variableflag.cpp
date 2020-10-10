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

#include "variableflag.h"
#include "messages.h"

/* **************************************************
 *
 ************************************************** */
VariableFlag::VariableFlag() noexcept
{
   flag = NONE;
   NEW;
}

/* **************************************************
 *
 ************************************************** */
void VariableFlag::setFlag(enum flagValues flag) {
   this->flag = flag;
}

/* **************************************************
 *
 ************************************************** */
bool VariableFlag::containsVariable(void) {
   if (flag != 0)
      return (flag == 1);
   return false;
}
