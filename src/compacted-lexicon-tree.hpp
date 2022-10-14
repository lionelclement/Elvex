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

#ifndef COMPACTEDLEXICONTREE_H
#define COMPACTEDLEXICONTREE_H

class CompactedLexiconTree {

private:
    CompactedLexiconTree* child;
    CompactedLexiconTree* next;
    class CompactedLexiconInfo* info;

    char character;
    unsigned long int address;

public:
    CompactedLexiconTree(CompactedLexiconTree* child, CompactedLexiconTree* sibling, class CompactedLexiconInfo* info,
                       const char character);

    ~CompactedLexiconTree();

    void setChild(CompactedLexiconTree* );

    CompactedLexiconTree* getChild() const;

    void add(const char* , unsigned long int);

    void setIndexStaticFSA(unsigned long int &);

    void printStaticFSA(FILE* , class CompactedLexicon* ) const;

    void setIndexStaticInfo(unsigned long int&);

    void printStaticInfo(FILE* ) const;
};

#endif // COMPACTEDLEXICONTREE_H
