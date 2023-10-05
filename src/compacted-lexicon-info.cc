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

#include "compacted-lexicon-info.hpp"
#include "messages.hpp"

/* **************************************************
 *
 ************************************************** */
CompactedLexiconInfo::CompactedLexiconInfo(class CompactedLexiconInfo *next, uint32_t offset)
{
    NEW this->address = 0;
    this->next = next;
    this->offset = offset;
}

/* **************************************************
 *
 ************************************************** */
CompactedLexiconInfo::~CompactedLexiconInfo()
{
    DELETE
    if (next)
    {
        delete (next);
        next = NULL;
    }
}

/* **************************************************
 *
 ************************************************** */
class CompactedLexiconInfo *CompactedLexiconInfo::getNext(void) const
{
    return next;
}

/* **************************************************
 *
 ************************************************** */
uint32_t CompactedLexiconInfo::getOffset(void) const
{
    return offset;
}

/* **************************************************
 *
 ************************************************** */
uint32_t CompactedLexiconInfo::getAddress(void) const
{
    return address;
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexiconInfo::setAddress(uint32_t _address)
{
    this->address = _address;
}
