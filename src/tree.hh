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

#ifndef TREE_H
#define TREE_H

#include <string>

class Tree {
private:
  Tree *child;
  Tree *sibling;
  class Info *info;
  char letter;
  unsigned long int address;
  
public:
  Tree(Tree *child, Tree *sibling, class Info *info, const char letter);
  ~Tree();
  
  void setChild( Tree*);
  Tree *getChild() const;
  void add(char *, unsigned long int);
  void setIndexStaticFSA(unsigned long int &);
  void printStaticFSA(FILE *, class Lex *) const;
  void setIndexStaticInfo(unsigned long int &);
  void printStaticInfo(FILE *) const;
};
#endif // TREE_H
