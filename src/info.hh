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

#ifndef INFO_H
#define INFO_H

#include <string>

class Info {
private:
	class Info *next;
	unsigned long int offset;
	unsigned long int address;

public:
	Info(class Info *next = NULL, unsigned long int offset = 0);
	~Info();

	class Info *getNext(void) const;
	unsigned long int getOffset(void) const;
	unsigned long int getAddress(void) const;
	void setAddress(unsigned long int);

	void printStatic(FILE *) const;
};

#endif // INFO_H
