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

#include "compact-lexicon-info.hh"
#include "messages.hh"

/* **************************************************
 *
 ************************************************** */
CompactLexiconInfo::CompactLexiconInfo(class CompactLexiconInfo *next, unsigned long int offset) {
   this->address = 0;
   this->next = next;
   this->offset = offset;
   NEW;
}

/* **************************************************
 *
 ************************************************** */
CompactLexiconInfo::~CompactLexiconInfo() {
   DELETE;
   if (next) {
      delete (next);
      next = NULL;
   }
}

/* **************************************************
 *
 ************************************************** */
class CompactLexiconInfo *CompactLexiconInfo::getNext(void) const {
   return next;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int CompactLexiconInfo::getOffset(void) const {
   return offset;
}

/* **************************************************
 *
 ************************************************** */
unsigned long int CompactLexiconInfo::getAddress(void) const {
   return address;
}

/* **************************************************
 *
 ************************************************** */
void CompactLexiconInfo::setAddress(unsigned long int address) {
   this->address = address;
}

