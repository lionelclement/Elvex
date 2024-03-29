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

#include <string>
#include <ostream>
#include "compacted-lexicon-fsa.hpp"

/* **************************************************
 *
 ************************************************** */
CompactedLexiconFsa::CompactedLexiconFsa(uint32_t child, uint32_t next,
                                         uint32_t info,
                                         char character)
{
    this->child = child;
    this->next = next;
    this->info = info;
    this->character = character;
}

/* **************************************************
 *
 ************************************************** */
CompactedLexiconFsa::CompactedLexiconFsa(void)
{
    this->child = (uint32_t)~0UL;
    this->next = (uint32_t)~0UL;
    this->info = (uint32_t)~0UL;
    this->character = (char)~0;
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexiconFsa::print(std::ostream &out) const
{
    out << (long int)child << ' ' << (long int)next << ' ' << (long int)info << ' ' << (int)character
        << std::endl;
}

/* **************************************************
 *
 ************************************************** */
bool CompactedLexiconFsa::hasChild() const
{
    return child != (uint32_t)(~0UL);
}

/* **************************************************
 *
 ************************************************** */
bool CompactedLexiconFsa::hasNext() const
{
    return next != (uint32_t)(~0UL);
}

/* **************************************************
 *
 ************************************************** */
bool CompactedLexiconFsa::hasInfo() const
{
    return info != (uint32_t)(~0UL);
}

/* **************************************************
 *
 ************************************************** */
uint32_t CompactedLexiconFsa::getChild(void) const
{
    return child;
}

/* **************************************************
 *
 ************************************************** */
uint32_t CompactedLexiconFsa::getNext() const
{
    return next;
}

/* **************************************************
 *
 ************************************************** */
uint32_t CompactedLexiconFsa::getInfo(void) const
{
    return info;
}

/* **************************************************
 *
 ************************************************** */
bool CompactedLexiconFsa::equalsThisChar(char _character) const
{
    return this->character == _character;
}
