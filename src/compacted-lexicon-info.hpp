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

#ifndef COMPACTEDLEXICONINFO_H
#define COMPACTEDLEXICONINFO_H

#include <cstdint>

class CompactedLexiconInfo
{
private:
    class CompactedLexiconInfo *next;

    uint32_t offset;

    uint32_t address;

public:
    CompactedLexiconInfo(class CompactedLexiconInfo *next = nullptr, uint32_t offset = 0);

    ~CompactedLexiconInfo();

    class CompactedLexiconInfo *getNext(void) const;

    uint32_t getOffset(void) const;

    uint32_t getAddress(void) const;

    void setAddress(uint32_t);
};

#endif // COMPACTEDLEXICONINFO_H
