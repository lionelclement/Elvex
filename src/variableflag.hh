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

#ifndef VARIABLE_FLAG_H
#define VARIABLE_FLAG_H

class VariableFlag {

public:

	enum flagValues {
		DOES_CONTAIN,
		DOES_NOT_CONTAIN,
		NONE
	};
private:
	enum flagValues flag;

public:
	VariableFlag(void) noexcept;
	bool containsVariable(void);
	void setFlag(enum flagValues flag);
};

#endif // VARIABLE_FLAG_H
