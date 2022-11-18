/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI,
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

#include "fatal_exception.hpp"

#include <iostream>
#include <sstream>
#include <utility>

/* **************************************************
 *
 ************************************************** */
fatal_exception::fatal_exception(std::string message) {
    this->message = message;
}

/* **************************************************
 *
 ************************************************** */
fatal_exception::fatal_exception(std::ostringstream& oss) {
  this->message = oss.str();
}

/* **************************************************
 *
 ************************************************** */
std::string fatal_exception::getMessage() {
    return message;
}
