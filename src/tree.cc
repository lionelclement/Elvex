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
#include "tree.hh"
#include "messages.hh"
#include "fsa.hh"
#include "info.hh"
#include "infobuff.hh"
#include "lex.hh"

/* **************************************************
 *
 ************************************************** */
Tree::Tree(Tree *child, Tree *sibling, class Info *info, char character) {
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
Tree::~Tree() {
	DELETE;
}

/* **************************************************
 *
 ************************************************** */
Tree*
Tree::getChild() const {
	return child;
}

/* **************************************************
 *
 ************************************************** */
void Tree::setChild(Tree *child) {
	this->child = child;
}

/* **************************************************
 // Compute offsets of FSA array
 ************************************************** */
void Tree::setIndexStaticFSA(unsigned long int &index) {
	for (class Tree *lexiconSy = this; lexiconSy != NULL; lexiconSy = lexiconSy->sibling) {
		lexiconSy->address = index++;
		if (lexiconSy->child)
			lexiconSy->child->setIndexStaticFSA(index);
	}
}

/* **************************************************
 // write record of FSA
 ************************************************** */
void Tree::printStaticFSA(FILE *out, class Lex *lex) const {
	const class Tree *lexiconSy;
	if (this == lex->lexiconInit) {
		lex->init = this->address;
	}
	for (lexiconSy = this; lexiconSy; lexiconSy = lexiconSy->sibling) {
		struct Fsa *elt = new Fsa((lexiconSy->child == NULL) ? (unsigned long int)~0UL : lexiconSy->child->address,
				(lexiconSy->sibling == NULL) ? (unsigned long int)~0UL : lexiconSy->sibling->address, (lexiconSy->info == NULL) ? (unsigned long int)~0UL : lexiconSy->info->getAddress(),
				lexiconSy->character);
		if (!fwrite(elt, sizeof(struct Fsa), 1, out)) {
			FATAL_ERROR
			;
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
void Tree::setIndexStaticInfo(unsigned long int &index)
{
  for (Tree *lexiconSy = this; lexiconSy != NULL; lexiconSy = lexiconSy->sibling) {
    if (lexiconSy->child)
      lexiconSy->child->setIndexStaticInfo(index);
  }
  for (Tree *lexiconSy = this; lexiconSy != NULL; lexiconSy = lexiconSy->sibling) {
    for (Info *infoSy = lexiconSy->info; infoSy != NULL; infoSy = infoSy->getNext()) {
      infoSy->setAddress(index++);
    }
  }
}

/* **************************************************
 // write the records
 // offsets are calculated on 32 (vs 16) bits if long==1
 ************************************************** */
void Tree::printStaticInfo(FILE *out) const {
	for (const Tree *lexiconSy = this; lexiconSy != NULL; lexiconSy = lexiconSy->sibling) {
		if (lexiconSy->child)
			lexiconSy->child->printStaticInfo(out);
	}
	for (const Tree *lexiconSy = this; lexiconSy != NULL; lexiconSy = lexiconSy->sibling) {
		for (Info *infoSy = lexiconSy->info; infoSy != NULL; infoSy = infoSy->getNext()) {
			struct InfoBuff *elt = new InfoBuff((infoSy->getNext() != NULL) ? infoSy->getNext()->getAddress() : (unsigned long int)(~(0UL)), infoSy->getOffset());
			if (!fwrite(elt, sizeof(struct InfoBuff), 1, out))
				FATAL_ERROR
			;
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
void Tree::add(const char *str, unsigned long int offset) {
	if (!this->character) {
		this->character = str[0];
		if (!str[1]) {
			this->info = new Info(this->info, offset);
		}
		else {
			if (!this->child)
				this->child = new Tree(NULL, NULL, NULL, str[1]);
			this->child->add((char *)str + 1, offset);
		}
	}
	else if (this->character == str[0]) {
		if (!str[1]) {
			this->info = new Info(this->info, offset);
		}
		else {
			if (!this->child)
				this->child = new Tree(NULL, NULL, NULL, str[1]);
			this->child->add((char *)str + 1, offset);
		}
	}
	else if (this->sibling)
		this->sibling->add(str, offset);
	else {
		this->sibling = new Tree(NULL, NULL, NULL, str[0]);
		this->sibling->add(str, offset);

	}
}
