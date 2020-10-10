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

#ifndef ELVEX_TERM_H
#define ELVEX_TERM_H

#include <iostream>
#include "flags.h"
#include "shared_ptr.h"

class Term :
        public Flags, public std::enable_shared_from_this<class Term> {

private:
    unsigned int code;

    Term(unsigned int code);

public:
    ~Term();

    static termPtr create(unsigned int code = 0);

    unsigned int getCode(void) const;

    void print(std::ostream &outStream = std::cout) const;

    std::string toString() const;

    termPtr clone() const;

    // compare deux termes
    struct Less {
        bool operator()(const termPtr t1, const termPtr t2) const;
    };

};

#endif // ELVEX_TERM_H
