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

#ifndef COMPACTLEXICONFSA_H
#define COMPACTLEXICONFSA_H

#include <ostream>

struct CompactLexiconFsa {
private:
    unsigned long int child;
    unsigned long int sibling;
    unsigned long int info;
    char character;

public:
    CompactLexiconFsa(unsigned long int, unsigned long int, unsigned long int, char);

    CompactLexiconFsa();

    void print(std::ostream &) const;

    bool isChild() const;

    bool isInfo() const;

    bool isSibling() const;

    unsigned long int getChild(void) const;

    unsigned long int getSibling(void) const;

    unsigned long int getInfo(void) const;

    bool isThisChar(char character) const;

};

#endif // COMPACTLEXICONFSA_H
