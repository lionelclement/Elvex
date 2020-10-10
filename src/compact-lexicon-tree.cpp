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

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compact-lexicon.h"
#include "compact-lexicon-fsa.h"
#include "compact-lexicon-info.h"
#include "compact-lexicon-buffer.h"
#include "messages.h"

/* **************************************************
 *
 ************************************************** */
CompactLexiconTree::CompactLexiconTree(CompactLexiconTree *child, CompactLexiconTree *sibling, class CompactLexiconInfo *info, char character) {
   this->address = 0;
   this->child = child;
   this->sibling = sibling;
   this->info = info;
   this->character = character;
   NEW;
}

/* **************************************************
 *
 ************************************************** */
CompactLexiconTree::~CompactLexiconTree() {
   DELETE;
}

/* **************************************************
 *
 ************************************************** */
CompactLexiconTree*
CompactLexiconTree::getChild() const {
   return child;
}

/* **************************************************
 *
 ************************************************** */
void CompactLexiconTree::setChild(CompactLexiconTree *child) {
   this->child = child;
}

/* **************************************************
 // Compute offsets of FSA array
 ************************************************** */
void CompactLexiconTree::setIndexStaticFSA(unsigned long int &index) {
   for (class CompactLexiconTree *lexiconSy = this; lexiconSy != NULL; lexiconSy = lexiconSy->sibling) {
      lexiconSy->address = index++;
      if (lexiconSy->child)
         lexiconSy->child->setIndexStaticFSA(index);
   }
}

/* **************************************************
 // write record of FSA
 ************************************************** */
void CompactLexiconTree::printStaticFSA(FILE *out, class CompactLexicon *lex) const {
   const class CompactLexiconTree *lexiconSy;
   if (this == lex->lexiconInit) {
      lex->init = this->address;
   }
   for (lexiconSy = this; lexiconSy; lexiconSy = lexiconSy->sibling) {
      CompactLexiconFsa *elt = new CompactLexiconFsa((lexiconSy->child == NULL) ? (unsigned long int)~0UL : lexiconSy->child->address,
            (lexiconSy->sibling == NULL) ? (unsigned long int)~0UL : lexiconSy->sibling->address,
            (lexiconSy->info == NULL) ? (unsigned long int)~0UL : lexiconSy->info->getAddress(), lexiconSy->character);
      if (!fwrite(elt, sizeof(CompactLexiconFsa), 1, out)) {
         FATAL_ERROR_UNEXPECTED
      }
#ifdef TRACE_DIFF
      elt->print(std::cout);
#endif //TRACE_DIFF
      free(elt);
      if (lexiconSy->child)
         lexiconSy->child->printStaticFSA(out, lex);
   }
}

/* **************************************************
 // Calculate offsets of the array
 ************************************************** */
void CompactLexiconTree::setIndexStaticInfo(unsigned long int &index) {
   for (CompactLexiconTree *lexiconSy = this; lexiconSy != NULL; lexiconSy = lexiconSy->sibling) {
      if (lexiconSy->child)
         lexiconSy->child->setIndexStaticInfo(index);
   }
   for (CompactLexiconTree *lexiconSy = this; lexiconSy != NULL; lexiconSy = lexiconSy->sibling) {
      for (CompactLexiconInfo *infoSy = lexiconSy->info; infoSy != NULL; infoSy = infoSy->getNext()) {
         infoSy->setAddress(index++);
      }
   }
}

/* **************************************************
 // write the records
 // offsets are calculated on 32 (vs 16) bits if long==1
 ************************************************** */
void CompactLexiconTree::printStaticInfo(FILE *out) const {
   for (const CompactLexiconTree *lexiconSy = this; lexiconSy != NULL; lexiconSy = lexiconSy->sibling) {
      if (lexiconSy->child)
         lexiconSy->child->printStaticInfo(out);
   }
   for (const CompactLexiconTree *lexiconSy = this; lexiconSy != NULL; lexiconSy = lexiconSy->sibling) {
      for (CompactLexiconInfo *infoSy = lexiconSy->info; infoSy != NULL; infoSy = infoSy->getNext()) {
         CompactLexiconBuffer *elt = new CompactLexiconBuffer((infoSy->getNext() != NULL) ? infoSy->getNext()->getAddress() : (unsigned long int)(~(0UL)), infoSy->getOffset());
         if (!fwrite(elt, sizeof(CompactLexiconBuffer), 1, out)) {
            FATAL_ERROR_UNEXPECTED
         }
#ifdef TRACE_DIFF
         std::cout << infoSy->getAddress() << ' ';
         elt->print(std::cout);
#endif //TRACE_DIFF
      }
   }
}

/* **************************************************
 // add a word
 ************************************************** */
void CompactLexiconTree::add(const char *str, unsigned long int offset) {
   if (!this->character) {
      this->character = str[0];
      if (!str[1]) {
         this->info = new CompactLexiconInfo(this->info, offset);
      }
      else {
         if (!this->child)
            this->child = new CompactLexiconTree(NULL, NULL, NULL, str[1]);
         this->child->add((char *)str + 1, offset);
      }
   }
   else if (this->character == str[0]) {
      if (!str[1]) {
         this->info = new CompactLexiconInfo(this->info, offset);
      }
      else {
         if (!this->child)
            this->child = new CompactLexiconTree(NULL, NULL, NULL, str[1]);
         this->child->add((char *)str + 1, offset);
      }
   }
   else if (this->sibling)
      this->sibling->add(str, offset);
   else {
      this->sibling = new CompactLexiconTree(NULL, NULL, NULL, str[0]);
      this->sibling->add(str, offset);
   }
}
