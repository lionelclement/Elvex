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

#include "compact-lexicon-buffer.h"

/* **************************************************
 *
 ************************************************** */
CompactLexiconBuffer::CompactLexiconBuffer(unsigned long int next, unsigned long int offset) {
    this->next = next;
    this->offset = offset;
}

/* **************************************************
 *
 ************************************************** */
CompactLexiconBuffer::CompactLexiconBuffer(void) {
    this->next = (unsigned long int) (~0UL);
    this->offset = (unsigned long int) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
unsigned long int CompactLexiconBuffer::getOffset() const {
    return offset;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int CompactLexiconBuffer::getNext() const {
    return next;
}

/* **************************************************
 *
 ************************************************** */
bool CompactLexiconBuffer::isNext() const {
    return next != (unsigned long int) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
bool CompactLexiconBuffer::isOffset() const {
    return offset != (unsigned long int) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
void CompactLexiconBuffer::print(std::ostream &out) const {
    out << (long int) next << ' ' << (long int) offset << std::endl;
}

