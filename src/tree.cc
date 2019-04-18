/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2018 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: Lionel Clément,
 * Labri -- 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.hh"
#include "messages.hh"
#include "fsa.hh"
#include "info.hh"
#include "infobuff.hh"
#include "lex.hh"

/* **************************************************
 *
 ************************************************** */
Tree::Tree(Tree *child, Tree *sibling, class Info *info, char letter)
{
  NEW;
  this->adress=0;
  this->child = child;
  this->sibling = sibling;
  this->info = info;
  this->letter = letter;
}

/* **************************************************
 *
 ************************************************** */
Tree::~Tree()
{
  DELETE;
}

/* **************************************************
 *
 ************************************************** */
Tree*
Tree::getChild() const
{
  return child;
}

/* **************************************************
 *
 ************************************************** */
void
Tree::setChild(Tree *child)
{
  this->child = child;
}

/* **************************************************
// Calcule les offsets du tableau FSA
************************************************** */
void
Tree::setIndexStaticFSA(unsigned long int &index)
{
  for (class Tree *lexiconSy = this ; lexiconSy != NULL ; lexiconSy = lexiconSy->sibling){
    lexiconSy->adress = index++;
    if (lexiconSy->child != NULL)
      lexiconSy->child->setIndexStaticFSA(index);

  }
}

/* **************************************************
// �crit les enregistrements du FSA
// les offsets sont calcul�s sur 32 (vs 16) bits si long==1
************************************************** */
void
Tree::printStaticFSA(FILE *out, class Lex *lex) const
{
  struct Fsa elt;
  const class Tree* lexiconSy;
  if (this==lex->lexiconInit){
    lex->init=this->adress;

  }
  for (lexiconSy=this;lexiconSy;lexiconSy=lexiconSy->sibling){
    elt.child=(lexiconSy->child==NULL)?(unsigned long int)~0UL:lexiconSy->child->adress;
    elt.sibling=(lexiconSy->sibling==NULL)?(unsigned long int)~0UL:lexiconSy->sibling->adress;
    elt.info=(lexiconSy->info==NULL)?(unsigned long int)~0UL:lexiconSy->info->getAdress();
    elt.letter=lexiconSy->letter;
    if (!fwrite(&elt, sizeof(elt), 1, out))
      FATAL_ERROR
#ifdef TRACE_DIFF
	fprintf(stdout, "%lX ch:%lX sb:%lX in:%lX <%c>\n", lexiconSy->adress, elt.child, elt.sibling, elt.info, elt.letter);
#endif //TRACE_DIFF
    lexiconSy->child->printStaticFSA(out, lex);

  }
}

/* **************************************************
// Calcule les offsets du tableau info
************************************************** */
void
Tree::setIndexStaticInfo(unsigned long int &index)
{
  Info *infoSy;
  Tree *lexiconSy;
  for (lexiconSy=this;lexiconSy!=NULL;lexiconSy=lexiconSy->sibling)
    lexiconSy->child->setIndexStaticInfo(index);
  for (lexiconSy=this;lexiconSy!=NULL;lexiconSy=lexiconSy->sibling){
    for (infoSy=lexiconSy->info;infoSy!=NULL;infoSy=infoSy->getNext()){
      infoSy->setAdress(index++);

    }
  }
}

/* **************************************************
// �crit les enregistrement du tableau d'infos
// les offsets sont calcul�s sur 32 (vs 16) bits si long==1
************************************************** */
void
Tree::printStaticInfo(FILE *out) const
{
  Info *infoSy;
  const Tree *lexiconSy;
  struct InfoBuff elt;
  for (lexiconSy=this;lexiconSy!=NULL;lexiconSy=lexiconSy->sibling)
    lexiconSy->child->printStaticInfo(out);
  for (lexiconSy=this;lexiconSy!=NULL;lexiconSy=lexiconSy->sibling){
    for (infoSy=lexiconSy->info;infoSy!=NULL;infoSy=infoSy->getNext()){
      elt.next=(infoSy->getNext()!=NULL)?infoSy->getNext()->getAdress():(unsigned long int)(~(0UL));
      elt.offset=infoSy->getOffset();
      if (!fwrite(&elt, sizeof(elt), 1, out))
	FATAL_ERROR;
#ifdef TRACE_DIFF
      fprintf(stdout, "%lX su:%lX of:%lX\n", infoSy->getAdress(), elt.next, elt.offset);
#endif //TRACE_DIFF

    }

  }
}

/* **************************************************
// ajoute un mot dans l'arbre � lettres
************************************************** */
void
Tree::add(char *str,
	  unsigned long int offset)
{
  //Info *infoSy;
  if (!this->letter){
    this->letter = str[0];
    if (!str[1]){
      if(this->info){
	this->info = new Info(this->info, offset);

      }
      else
	this->info = new Info(NULL, offset);

    }
    else{
      if (!this->child)
	this->child = new Tree(NULL, NULL, NULL, str[1]);
      this->child->add((char *)str+1, offset);

    }

  }
  else if (this->letter == str[0]){
    if (!str[1]){
      if(this->info){
	this->info = new Info(this->info, offset);

      }
      else
	this->info = new Info(NULL, offset);

    }
    else{
      if (!this->child)
	this->child = new Tree(NULL, NULL, NULL, str[1]);
      this->child->add((char *)str+1, offset);

    }

  }
  else if (this->sibling)
    this->sibling->add(str, offset);
  else{
    this->sibling = new Tree(NULL, NULL, NULL, str[0]);
    this->sibling->add(str, offset);

  }
}
