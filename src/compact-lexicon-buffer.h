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

#ifndef COMPACTLEXICONBUFFER_H
#define COMPACTLEXICONBUFFER_H

#include <ostream>

struct CompactLexiconBuffer {
private:
    unsigned long int next;
    unsigned long int offset;

public:
    CompactLexiconBuffer(unsigned long int next, unsigned long int offset);

    CompactLexiconBuffer(void);

    unsigned long int getOffset() const;

    unsigned long int getNext() const;

    bool isNext() const;

    bool isOffset() const;

    void print(std::ostream &) const;

};

#endif // COMPACTLEXICONBUFFER_H
