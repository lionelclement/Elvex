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

#ifndef COMPACTEDLEXICONFSA_H
#define COMPACTEDLEXICONFSA_H

#include <ostream>

struct CompactedLexiconFsa {
private:
    unsigned long int child;
    unsigned long int sibling;
    unsigned long int info;
    char character;

public:
    CompactedLexiconFsa(unsigned long int, unsigned long int, unsigned long int, char);

    CompactedLexiconFsa();

    void print(std::ostream &) const;

    bool isChild() const;

    bool isInfo() const;

    bool isSibling() const;

    unsigned long int getChild(void) const;

    unsigned long int getSibling(void) const;

    unsigned long int getInfo(void) const;

    bool isThisChar(char character) const;

};

#endif // COMPACTEDLEXICONFSA_H