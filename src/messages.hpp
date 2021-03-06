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

#ifndef ELVEX_MESSAGES_H
#define ELVEX_MESSAGES_H

#include <iostream>
#include <sstream>
#include <string>
#include "fatal_exception.hpp"

#ifdef TRACE_MALLOC
#define NEW {std::cerr << "$$$ New " << __FILE__ << std::endl; }
#define DELETE {std::cerr << "$$$ Delete " << __FILE__ << std::endl; }
#else
#define NEW {}
#define DELETE {}
#endif

#define CERR_LINE  {std::cerr << __FILE__ << "(" << std::dec <<  __LINE__ << ")" << "<br>" << std::endl;}
#define COUT_LINE  {std::cout << __FILE__ << "(" << std::dec <<__LINE__ << ")" << std::endl;}

#define FATAL_ERROR_UNEXPECTED {CERR_LINE; throw fatal_exception("*** unexpected");}
#define FATAL_ERROR(msg) {std::ostringstream _oss; _oss << "*** " << msg; throw fatal_exception(_oss.str());}
#define WARNING(msg) {std::cerr << "*** " << msg << std::endl;}

#endif // ELVEX_MESSAGES_H
