/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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

#ifndef MESSAGES_H
#define MESSAGES_H

#include <iostream>     // cout
#include <sstream>      // ostringstream

#ifdef TRACE_MALLOC
#define NEW {std::cerr << "$$$ New " << __FILE__ << std::endl; }
#define DELETE {std::cerr << "$$$ Delete " << __FILE__ << std::endl; }
#else
#define NEW
#define DELETE
#endif

#define CERR_LINE  {std::cerr << __FILE__ << "(" << std::dec <<  __LINE__ << ")" << "<br>" << std::endl;}
#define COUT_LINE  {std::cout << __FILE__ << "(" << std::dec <<__LINE__ << ")" << std::endl;}

#define WARNING_MSG(msg)  {CERR_LINE; std::cerr << "WARNING: " << msg << std::endl;}
#define FATAL_ERROR_MSG(msg)  {CERR_LINE; std::cerr << "FATAL ERROR" << std::endl; throw msg;}

#define FATAL_ERROR {FATAL_ERROR_MSG("");}

#endif // MESSAGES_H
