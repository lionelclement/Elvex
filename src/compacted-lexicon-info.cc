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

#include "compacted-lexicon-info.hpp"
#include "messages.hpp"

/* **************************************************
 *
 ************************************************** */
CompactedLexiconInfo::CompactedLexiconInfo(class CompactedLexiconInfo *next, unsigned long int offset) {
    NEW
    this->address = 0;
    this->next = next;
    this->offset = offset;
}

/* **************************************************
 *
 ************************************************** */
CompactedLexiconInfo::~CompactedLexiconInfo() {
    DELETE
    if (next) {
        delete (next);
        next = NULL;
    }
}

/* **************************************************
 *
 ************************************************** */
class CompactedLexiconInfo *CompactedLexiconInfo::getNext(void) const {
    return next;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int CompactedLexiconInfo::getOffset(void) const {
    return offset;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int CompactedLexiconInfo::getAddress(void) const {
    return address;
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexiconInfo::setAddress(unsigned long int _address) {
    this->address = _address;
}

