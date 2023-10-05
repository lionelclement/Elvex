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

#ifndef COMPACTEDLEXICONFSA_H
#define COMPACTEDLEXICONFSA_H

#include <ostream>

struct CompactedLexiconFsa
{
private:
    uint32_t child;
    uint32_t next;
    uint32_t info;
    char character;

public:
    CompactedLexiconFsa(uint32_t, uint32_t, uint32_t, char);

    CompactedLexiconFsa();

    void print(std::ostream &) const;

    bool hasChild() const;

    bool hasInfo() const;

    bool hasNext() const;

    uint32_t getChild(void) const;

    uint32_t getNext(void) const;

    uint32_t getInfo(void) const;

    bool equalsThisChar(char character) const;

    char getCharacter() const { return character; }
};

#endif // COMPACTEDLEXICONFSA_H
