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
 * LaBRI -- Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef COMPACTEDLEXICONINFO_H
#define COMPACTEDLEXICONINFO_H

class CompactedLexiconInfo
{
private:
    class CompactedLexiconInfo *next;

    unsigned long int offset;

    unsigned long int address;

public:
    CompactedLexiconInfo(class CompactedLexiconInfo *next = nullptr, unsigned long int offset = 0);

    ~CompactedLexiconInfo();

    class CompactedLexiconInfo *getNext(void) const;

    unsigned long int getOffset(void) const;

    unsigned long int getAddress(void) const;

    void setAddress(unsigned long int);
};

#endif // COMPACTEDLEXICONINFO_H
