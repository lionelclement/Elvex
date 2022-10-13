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

#ifndef COMPACTEDLEXICONBUFFER_H
#define COMPACTEDLEXICONBUFFER_H

#include <iostream>

struct CompactedLexiconBuffer {
private:
    unsigned long int next;
    unsigned long int offset;

public:
    CompactedLexiconBuffer(unsigned long int next, unsigned long int offset);

    CompactedLexiconBuffer(void);

    unsigned long int getOffset() const;

    unsigned long int getNext() const;

    bool isNext() const;

    bool isOffset() const;

    void print(std::ostream &) const;

};

#endif // COMPACTEDLEXICONBUFFER_H
