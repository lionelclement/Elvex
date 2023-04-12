/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2023 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: 
 * Lionel Clément
 * LaBRI -- Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#include "variableflag.hpp"
#include "messages.hpp"

/* **************************************************
 *
 ************************************************** */
VariableFlag::VariableFlag() noexcept {
    NEW
    flag = NONE;
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
bool VariableFlag::containsVariable() {
    if (flag == CONTAINS_VARIABLE)
        return true;
    return false;
}

