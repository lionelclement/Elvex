/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "compacted-lexicon.hpp"
#include "compacted-lexicon-fsa.hpp"
#include "compacted-lexicon-info.hpp"
#include "compacted-lexicon-buffer.hpp"
#include "messages.hpp"

/* **************************************************
 *
 ************************************************** */
CompactedLexiconTree::CompactedLexiconTree(CompactedLexiconTree *child, CompactedLexiconTree *next,
                                           class CompactedLexiconInfo *info, char character)
{
    NEW this->address = 0;
    this->child = child;
    this->next = next;
    this->info = info;
    this->character = character;
}

/* **************************************************
 *
 ************************************************** */
CompactedLexiconTree::~CompactedLexiconTree(){
    DELETE}

/* **************************************************
 *
 ************************************************** */
CompactedLexiconTree *CompactedLexiconTree::getChild() const
{
    return child;
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexiconTree::setChild(CompactedLexiconTree *_child)
{
    this->child = _child;
}

/* **************************************************
 // Compute offsets of FSA array
 ************************************************** */
void CompactedLexiconTree::setIndexStaticFSA(uint32_t &index)
{
    for (class CompactedLexiconTree *lexiconSy = this; lexiconSy != nullptr; lexiconSy = lexiconSy->next)
    {
        lexiconSy->address = index++;
        if (lexiconSy->child)
            lexiconSy->child->setIndexStaticFSA(index);
    }
}

/* **************************************************
 // write record of FSA
 ************************************************** */
void CompactedLexiconTree::printStaticFSA(FILE *out, class CompactedLexicon *lex) const
{
    const class CompactedLexiconTree *lexiconSy;
    if (this == lex->lexiconInit)
    {
        lex->init = this->address;
    }
    for (lexiconSy = this; lexiconSy; lexiconSy = lexiconSy->next)
    {
        auto *elt = new CompactedLexiconFsa(
            (lexiconSy->child == nullptr) ? (uint32_t)~0UL : lexiconSy->child->address,
            (lexiconSy->next == nullptr) ? (uint32_t)~0UL : lexiconSy->next->address,
            (lexiconSy->info == nullptr) ? (uint32_t)~0UL : lexiconSy->info->getAddress(),
            lexiconSy->character);
        if (!fwrite(elt, sizeof(CompactedLexiconFsa), 1, out))
        {
            FATAL_ERROR_UNEXPECTED;
        }
#ifdef TRACE_DIFF
        elt->print(std::cout);
#endif // TRACE_DIFF
        delete elt;
        if (lexiconSy->child)
            lexiconSy->child->printStaticFSA(out, lex);
    }
}

/* **************************************************
 // Calculate offsets of the array
 ************************************************** */
void CompactedLexiconTree::setIndexStaticInfo(uint32_t &index)
{
    // Assign child subtrees first; the second pass then assigns this level's
    // payload chains. Do not interleave these passes: offsets are serialized.
    for (CompactedLexiconTree *lexiconSy = this; lexiconSy != nullptr; lexiconSy = lexiconSy->next)
    {
        if (lexiconSy->child)
            lexiconSy->child->setIndexStaticInfo(index);
    }
    for (CompactedLexiconTree *lexiconSy = this; lexiconSy != nullptr; lexiconSy = lexiconSy->next)
    {
        for (CompactedLexiconInfo *infoSy = lexiconSy->info; infoSy != nullptr; infoSy = infoSy->getNext())
        {
            infoSy->setAddress(index++);
        }
    }
}

/* **************************************************
 // write the records
 // offsets are calculated on 32 (vs 16) bits if long==1
 ************************************************** */
void CompactedLexiconTree::printStaticInfo(FILE *out) const
{
    for (const CompactedLexiconTree *lexiconSy = this; lexiconSy != nullptr; lexiconSy = lexiconSy->next)
    {
        if (lexiconSy->child)
            lexiconSy->child->printStaticInfo(out);
    }
    for (const CompactedLexiconTree *lexiconSy = this; lexiconSy != nullptr; lexiconSy = lexiconSy->next)
    {
        for (CompactedLexiconInfo *infoSy = lexiconSy->info; infoSy != nullptr; infoSy = infoSy->getNext())
        {
            auto *elt = new CompactedLexiconBuffer(
                (infoSy->getNext() != nullptr) ? infoSy->getNext()->getAddress() : (uint32_t)(~(0UL)),
                infoSy->getOffset());
            if (!fwrite(elt, sizeof(CompactedLexiconBuffer), 1, out))
            {
                FATAL_ERROR_UNEXPECTED;
            }
#ifdef TRACE_DIFF
            std::cout << infoSy->getAddress() << ' ';
            elt->print(std::cout);
#endif // TRACE_DIFF
        }
    }
}

/* **************************************************
 // add a word
 ************************************************** */
void CompactedLexiconTree::add(const char *str, uint32_t offset)
{
    // The first insertion initializes an empty root without creating a sibling.
    if (!character)
        character = str[0];

    if (character == str[0])
    {
        addMatchingKey(str, offset);
    }
    else if (next)
    {
        next->add(str, offset);
    }
    else
    {
        next = new CompactedLexiconTree(nullptr, nullptr, nullptr, str[0]);
        next->add(str, offset);
    }
}

/* **************************************************
 * Preserve the original LIFO order of lexical payloads. In particular,
 * adding a duplicate spelling prepends its offset to the existing chain.
 ************************************************** */
void CompactedLexiconTree::addMatchingKey(const char *str, uint32_t offset)
{
    if (!str[1])
    {
        info = new CompactedLexiconInfo(info, offset);
    }
    else
    {
        if (!child)
            child = new CompactedLexiconTree(nullptr, nullptr, nullptr, str[1]);
        child->add(str + 1, offset);
    }
}
