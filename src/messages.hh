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

#ifndef ELVEX_MESSAGES_H
#define ELVEX_MESSAGES_H

#include <iostream>
#include <string>

#ifdef TRACE_MALLOC
#define NEW {std::cerr << "$$$ New " << __FILE__ << std::endl; }
#define DELETE {std::cerr << "$$$ Delete " << __FILE__ << std::endl; }
#else
#define NEW
#ifdef RESTORE_MEMORY
#define DELETE {}
#else
#define DELETE  {return;}
#endif
#endif

#define CERR_LINE  {std::cerr << __FILE__ << "(" << std::dec <<  __LINE__ << ")" << "<br>" << std::endl;}
#define COUT_LINE  {std::cout << __FILE__ << "(" << std::dec <<__LINE__ << ")" << std::endl;}

#define FATAL_ERROR_UNEXPECTED {CERR_LINE; throw "*** unexpected";}
#define FATAL_ERROR(msg) {std::ostringstream oss; oss << "*** " << msg; throw oss.str();}
#define WARNING(msg) {std::cerr << "*** " << msg << std::endl;}

#endif // ELVEX_MESSAGES_H
