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

#include "compacted-lexicon-fsa.hpp"

/* **************************************************
 *
 ************************************************** */
CompactedLexiconFsa::CompactedLexiconFsa(unsigned long int child, unsigned long int sibling, unsigned long int info,
                                     char character) {
    this->child = child;
    this->sibling = sibling;
    this->info = info;
    this->character = character;
}

/* **************************************************
 *
 ************************************************** */
CompactedLexiconFsa::CompactedLexiconFsa(void) {
    this->child = (unsigned long int) ~0UL;
    this->sibling = (unsigned long int) ~0UL;
    this->info = (unsigned long int) ~0UL;
    this->character = (char) ~0;
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexiconFsa::print(std::ostream &out) const {
    out << (long int) child << ' ' << (long int) sibling << ' ' << (long int) info << ' ' << (int) character
        << std::endl;
}

/* **************************************************
 *
 ************************************************** */
bool CompactedLexiconFsa::isChild() const {
    return child != (unsigned long int) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
bool CompactedLexiconFsa::isSibling() const {
    return sibling != (unsigned long int) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
bool CompactedLexiconFsa::isInfo() const {
    return info != (unsigned long int) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
unsigned long int CompactedLexiconFsa::getChild(void) const {
    return child;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int CompactedLexiconFsa::getSibling(void) const {
    return sibling;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int CompactedLexiconFsa::getInfo(void) const {
    return info;
}

/* **************************************************
 *
 ************************************************** */
bool CompactedLexiconFsa::isThisChar(char character) const {
    return character == this->character;
}
