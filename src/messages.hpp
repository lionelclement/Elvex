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

#ifndef ELVEX_MESSAGES_H
#define ELVEX_MESSAGES_H

#include <iostream>
#include "fatal_exception.hpp"

#ifdef TRACE_MALLOC
#define NEW                                               \
    {                                                     \
        std::cerr << "$$$ New " << __FILE__ << std::endl; \
    }
#define DELETE                                               \
    {                                                        \
        std::cerr << "$$$ Delete " << __FILE__ << std::endl; \
    }
#else
#define NEW \
    {       \
    }
#define DELETE \
    {          \
    }
#endif

#define CERR_LINE                                                   \
    {                                                               \
        std::cerr << __FILE__ << "(" << std::dec << __LINE__ << ")" \
                  << "<br>" << std::endl;                           \
    }
#define COUT_LINE                                                                 \
    {                                                                             \
        std::cout << "<BR>" << __FILE__ << "(" << std::dec << __LINE__ << ")" << "<BR>" << std::endl; \
    }

#define FATAL_ERROR_UNEXPECTED                   \
    {                                            \
        COUT_LINE;                               \
        throw fatal_exception("*** unexpected"); \
    }
#define WARNING(msg)                                      \
    {                                                     \
        std::cout << "*** warning: " << msg << std::endl; \
    }

// #define _BUG_ {CERR_LINE; std::cerr << "*** Will cause a memory access error (segmentation fault)" << std::endl; int *x = NULL; *x = 36;}

#endif // ELVEX_MESSAGES_H
