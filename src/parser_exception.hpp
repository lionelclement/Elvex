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
 * lionel.clement@labri.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef ELVEX_PARSER_EXCEPTION_HPP
#define ELVEX_PARSER_EXCEPTION_HPP

#include <string>
#include <exception>

class parser_exception :
    public std::exception {

private:
    std::string message;

public:
    parser_exception(std::string message);
    parser_exception(std::ostringstream& _oss);
    std::string getMessage();
};


#endif //ELVEX_PARSER_EXCEPTION_HPP