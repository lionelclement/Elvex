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

#include "fatal_exception.hpp"

/* **************************************************
 *
 ************************************************** */
fatal_exception::fatal_exception(std::string message)
    : message(std::move(message))
{}

/* **************************************************
 *
 ************************************************** */
fatal_exception::fatal_exception(std::ostringstream &oss)
    : message(oss.str())
{}

/* **************************************************
 *
 ************************************************** */
const char* fatal_exception::what() const noexcept
{
    return message.c_str();
}
