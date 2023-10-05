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

#ifndef COMPACTEDLEXICONBUFFER_H
#define COMPACTEDLEXICONBUFFER_H

#include <iostream>

struct CompactedLexiconBuffer
{
private:
    uint32_t next;
    uint32_t offset;

public:
    CompactedLexiconBuffer(uint32_t next, uint32_t offset);

    CompactedLexiconBuffer(void);

    uint32_t getOffset() const;

    uint32_t getNext() const;

    bool isNext() const;

    bool isOffset() const;

    void print(std::ostream &) const;
};

#endif // COMPACTEDLEXICONBUFFER_H
