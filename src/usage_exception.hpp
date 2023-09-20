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

#ifndef ELVEX_USAGE_EXCEPTION_HPP
#define ELVEX_USAGE_EXCEPTION_HPP

#include <string>
#include <sstream>

#include "fatal_exception.hpp"

class usage_exception :
    public fatal_exception {

    public:
        usage_exception(std::string message);
        usage_exception(std::ostringstream& oss);

};


#endif //ELVEX_USAGE_EXCEPTION_HPP
