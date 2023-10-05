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

#ifndef COMPACTEDLEXICONTREE_H
#define COMPACTEDLEXICONTREE_H

#include <cstdio>

class CompactedLexiconTree
{

private:
    CompactedLexiconTree *child;
    CompactedLexiconTree *next;
    class CompactedLexiconInfo *info;

    char character;
    uint32_t address;

public:
    CompactedLexiconTree(CompactedLexiconTree *child, CompactedLexiconTree *sibling, class CompactedLexiconInfo *info,
                         const char character);

    ~CompactedLexiconTree();

    void setChild(CompactedLexiconTree *);

    CompactedLexiconTree *getChild() const;

    void add(const char *, uint32_t);

    void setIndexStaticFSA(uint32_t &);

    void printStaticFSA(FILE *, class CompactedLexicon *) const;

    void setIndexStaticInfo(uint32_t &);

    void printStaticInfo(FILE *) const;
};

#endif // COMPACTEDLEXICONTREE_H
