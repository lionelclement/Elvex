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

#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>

class Serializable {

private:
	int serialHashCode;
	virtual void makeSerialString(void) = 0;

protected:
	std::string serialString;

public:
	Serializable();
	virtual ~Serializable();
	const std::string peekSerialString(void);
	const size_t hashCode(void);
	void resetSerial(void);

};

#endif // SERIALIZABLE_H
