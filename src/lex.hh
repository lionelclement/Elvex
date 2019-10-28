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

#include <string>
#include <map>

#define MAXSTRING 1000000
#define SEP_PREF ""
#define SEP_UW "UNKNOWN"
#define SEP_SUFF "\n"
#define SEP_OR "|"

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

	void printResults(std::ostream &, unsigned long int index, bool sep) const;
	unsigned long int searchStatic(unsigned long int index, std::string) const;
	bool saveFsa(FILE *file);
	bool loadFsa(FILE *file);
	bool build(char *directory, char *prefix, std::istream *input);
	bool load(char *directory, char *prefix);
	bool consult(std::string inputFileName);
};
#endif // LEX_H
