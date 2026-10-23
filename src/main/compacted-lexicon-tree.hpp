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

#ifndef COMPACTEDLEXICONTREE_H
#define COMPACTEDLEXICONTREE_H

#include <cstdio>
#include <cstdint>

/**
 * Mutable trie used to construct the compacted lexicon before serialization.
 * The runtime lookup uses the serialized FSA rather than this tree.
 * Sibling insertion order, child traversal order, and payload-chain order
 * determine the indices stored on disk and must remain stable.
 */
class CompactedLexiconTree
{

private:
    CompactedLexiconTree *child;
    CompactedLexiconTree *next;
    class CompactedLexiconInfo *info;

    char character;
    uint32_t address;

    /** Complete insertion once the matching sibling has been found. */
    void addMatchingKey(const char *str, uint32_t offset);

public:
    CompactedLexiconTree(CompactedLexiconTree *child, CompactedLexiconTree *sibling, class CompactedLexiconInfo *info,
                         const char character);

    ~CompactedLexiconTree();

    void setChild(CompactedLexiconTree *);

    CompactedLexiconTree *getChild() const;

    /** Insert a lexical key and its payload offset into the trie. */
    void add(const char *, uint32_t);

    /** Assign stable indices to transitions before writing the FSA. */
    void setIndexStaticFSA(uint32_t &);

    void printStaticFSA(FILE *, class CompactedLexicon *) const;

    /** Assign stable indices to the lexical payload records. */
    void setIndexStaticInfo(uint32_t &);

    void printStaticInfo(FILE *) const;
};

#endif // COMPACTEDLEXICONTREE_H
