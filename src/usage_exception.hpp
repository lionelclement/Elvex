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

#ifndef ELVEX_USAGE_EXCEPTION_HPP
#define ELVEX_USAGE_EXCEPTION_HPP


#include <string>
#include <exception>

class usage_exception :
    public std::exception {

public:
    usage_exception(std::string);
    usage_exception();
};


#endif //ELVEX_USAGE_EXCEPTION_HPP
