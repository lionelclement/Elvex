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

#ifndef COMPACTLEXICONTREE_H
#define COMPACTLEXICONTREE_H

class CompactLexiconTree {

private:
    CompactLexiconTree *child;
    CompactLexiconTree *sibling;

    class CompactLexiconInfo *info;

    char character;
    unsigned long int address;

public:
    CompactLexiconTree(CompactLexiconTree *child, CompactLexiconTree *sibling, class CompactLexiconInfo *info,
                       const char character);

    ~CompactLexiconTree();

    void setChild(CompactLexiconTree *);

    CompactLexiconTree *getChild() const;

    void add(const char *, unsigned long int);

    void setIndexStaticFSA(unsigned long int &);

    void printStaticFSA(FILE *, class CompactLexicon *) const;

    void setIndexStaticInfo(unsigned long int &);

    void printStaticInfo(FILE *) const;
};

#endif // COMPACTLEXICONTREE_H
