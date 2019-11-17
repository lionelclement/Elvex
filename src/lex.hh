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

#ifndef LEX_H
#define LEX_H

#define MAXSTRING 10000
#define SEP_PREF ""
#define SEP_UW "UNKNOWN"
#define SEP_SUFF "\n"
#define SEP_OR "|"

//#include <iostream>
#include <string>

extern bool isLexString;
extern char *lexString;
extern char *currentLexString;
extern class Entry *localEntry;

class Lex {

public:
	char *buffer;
	struct Fsa *fsa;         // table fsa
	struct InfoBuff *info;   //table des info
	unsigned long int init;
	class Tree *lexiconInit;
	Lex(void);

	void printResults(std::ostream &, unsigned long int index, bool sep) const;
	unsigned long int searchStatic(unsigned long int index, std::string) const;
	bool saveFsa(FILE *file);
	bool loadFsa(FILE *file);
	bool build(std::string &directory, std::string &prefix, std::istream &inputStream, class Pattern &pattern);
	bool load(const std::string &directory, const std::string &prefix);
	bool consult(std::string inputFileName);
};
#endif // LEX_H
