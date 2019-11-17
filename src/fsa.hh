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

#ifndef FSA_H
#define FSA_H

#include <ostream>

struct Fsa {
private:
	unsigned long int child;
	unsigned long int sibling;
	unsigned long int info;
	char character;

public:
	Fsa(unsigned long int, unsigned long int, unsigned long int, char);
	Fsa();
	void print(std::ostream &) const;
	bool isChild() const;
	bool isInfo() const;
	bool isSibling() const;
	unsigned long int getChild(void) const;
	unsigned long int getSibling(void) const;
	unsigned long int getInfo(void) const;
	bool isThisChar(char character) const;

};
#endif // FSA_H
