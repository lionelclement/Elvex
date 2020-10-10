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

#ifndef COMPACTLEXICONINFO_H
#define COMPACTLEXICONINFO_H

class CompactLexiconInfo {
private:
    class CompactLexiconInfo *next;

    unsigned long int offset;
    unsigned long int address;

public:
    CompactLexiconInfo(class CompactLexiconInfo *next = nullptr, unsigned long int offset = 0);

    ~CompactLexiconInfo();

    class CompactLexiconInfo *getNext(void) const;

    unsigned long int getOffset(void) const;

    unsigned long int getAddress(void) const;

    void setAddress(unsigned long int);
};

#endif // COMPACTLEXICONINFO_H
