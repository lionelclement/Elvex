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

#ifndef ELVEX_FATAL_EXCEPTION_HPP
#define ELVEX_FATAL_EXCEPTION_HPP

#include <string>
#include <exception>
#include <sstream>

class fatal_exception : public std::exception
{
private:
    std::string message;

public:
    fatal_exception(std::string message);
    fatal_exception(std::ostringstream &oss);
    const char* what() const noexcept override;
};

#endif // ELVEX_FATAL_EXCEPTION_HPP
