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
 * LaBRI - Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#include "usage_exception.hpp"

/* **************************************************
 *
 ************************************************** */
usage_exception::usage_exception(std::string message): fatal_exception(message) {
}

/* **************************************************
 *
 ************************************************** */
usage_exception::usage_exception(std::ostringstream& oss): fatal_exception(oss) {
}

