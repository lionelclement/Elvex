/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI, 
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

#include "compacted-lexicon-buffer.hpp"

/* **************************************************
 *
 ************************************************** */
CompactedLexiconBuffer::CompactedLexiconBuffer(unsigned long int next, unsigned long int offset) {
    this->next = next;
    this->offset = offset;
}

/* **************************************************
 *
 ************************************************** */
CompactedLexiconBuffer::CompactedLexiconBuffer() {
    this->next = (unsigned long int) (~0UL);
    this->offset = (unsigned long int) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
unsigned long int CompactedLexiconBuffer::getOffset() const {
    return offset;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int CompactedLexiconBuffer::getNext() const {
    return next;
}

/* **************************************************
 *
 ************************************************** */
bool CompactedLexiconBuffer::isNext() const {
    return next != (unsigned long int) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
bool CompactedLexiconBuffer::isOffset() const {
    return offset != (unsigned long int) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexiconBuffer::print(std::ostream &out) const {
    out << (long int) next << ' ' << (long int) offset << std::endl;
}

