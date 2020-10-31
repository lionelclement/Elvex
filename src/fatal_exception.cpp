/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2020 LABRI,
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

#include "fatal_exception.hpp"

fatal_exception::fatal_exception(std::string message) {
    this->message = message;

}
