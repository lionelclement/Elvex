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

#ifndef COMPACTEDLEXICONFSA_H
#define COMPACTEDLEXICONFSA_H

#include <ostream>

struct CompactedLexiconFsa
{
private:
    unsigned long int child;
    unsigned long int next;
    unsigned long int info;
    char character;

public:
    CompactedLexiconFsa(unsigned long int, unsigned long int, unsigned long int, char);

    CompactedLexiconFsa();

    void print(std::ostream &) const;

    bool hasChild() const;

    bool hasInfo() const;

    bool hasNext() const;

    unsigned long int getChild(void) const;

    unsigned long int getNext(void) const;

    unsigned long int getInfo(void) const;

    bool equalsThisChar(char character) const;

    char getCharacter() const { return character; }
};

#endif // COMPACTEDLEXICONFSA_H
