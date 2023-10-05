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

#include "compacted-lexicon-buffer.hpp"

/* **************************************************
 *
 ************************************************** */
CompactedLexiconBuffer::CompactedLexiconBuffer(uint32_t next, uint32_t offset) {
    this->next = next;
    this->offset = offset;
}

/* **************************************************
 *
 ************************************************** */
CompactedLexiconBuffer::CompactedLexiconBuffer() {
    this->next = (uint32_t) (~0UL);
    this->offset = (uint32_t) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
uint32_t CompactedLexiconBuffer::getOffset() const {
    return offset;
}

/* **************************************************
 *
 ************************************************** */
uint32_t CompactedLexiconBuffer::getNext() const {
    return next;
}

/* **************************************************
 *
 ************************************************** */
bool CompactedLexiconBuffer::isNext() const {
    return next != (uint32_t) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
bool CompactedLexiconBuffer::isOffset() const {
    return offset != (uint32_t) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexiconBuffer::print(std::ostream &out) const {
    out << (long int) next << ' ' << (long int) offset << std::endl;
}

