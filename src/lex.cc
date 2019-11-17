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

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <map>
#include <sstream>

#include "lex.hh"
#include "messages.hh"
#include "vartable.hh"
#include "entries.hh"
#include "entry.hh"
#include "fsa.hh"
#include "infobuff.hh"
#include "tree.hh"
#include "pattern.hh"
#include "parser.hh"
#include "statement.hh"


/* **************************************************
 *
 ************************************************** */
Lex::Lex()
{
	buffer = NULL;
	fsa = NULL;
	info = NULL;
	init = 0;
	lexiconInit = 0;
}

/* **************************************************
 *
 ************************************************** */
void Lex::printResults(std::ostream &output, unsigned long int index, bool sep) const {
	char tag[MAXSTRING];
	if (sep)
		output << SEP_PREF;
	if (index == (unsigned long int)(~0UL)) {
		output << SEP_UW;
		if (sep)
			output << SEP_SUFF;
		return;
	}
	while (index != (unsigned long int)(~0UL)) {
		// an other element will be describe
		strcpy(tag, buffer + (info[index].getOffset()));
		output << tag;
		if (info[index].isNext())
			output << SEP_OR;
		if (info[index].isNext())
			index = info[index].getNext();
		else
			index = (unsigned long int)(~0UL);
	}
	if (sep)
		output << SEP_SUFF;
}

////////////////////////////////////////////////////////////
// input: string
// output: info
////////////////////////////////////////////////////////////
unsigned long int Lex::searchStatic(unsigned long int index, std::string s) const {
	char *str = strdup(s.c_str());
	char *str2 = str;
	index = fsa[index].getChild();
	// for each letter of the suffix
	while (*str) {
		// parse the brothers while founding the actual char
		while (!fsa[index].isThisChar(*str)) {
			if (fsa[index].isSibling())
				index = fsa[index].getSibling();
			else
				return (unsigned long int)(~0UL);
		}
		if (!fsa[index].isThisChar(*str))
			return ((unsigned long int)(~0UL));
		if (*(str + 1)) {
			if (fsa[index].isChild())
				index = fsa[index].getChild();
			else
				return (unsigned long int)(~0UL);

		}
		else if (fsa[index].isInfo())
			return fsa[index].getInfo();
		str++;

	}
	delete str2;
	return (unsigned long int)(~0UL);
}

/* **************************************************
 *
 ************************************************** */
bool Lex::saveFsa(FILE *file) {
	int nbrBytes = sizeof(unsigned long int);
	// encodage des offsets (16 ou 32 bits)
	if (!fwrite(&nbrBytes, sizeof(nbrBytes), 1, file))
		FATAL_ERROR
		;
#ifdef TRACE_DIFF
	std::cout << "nbreBytes:" << nbrBytes << std::endl;
#endif //TRACE_DIFF
	unsigned long int maxSize = (unsigned long int)~0UL;
	if (!fwrite(&maxSize, sizeof(maxSize), 1, file))
		FATAL_ERROR
		;
#ifdef TRACE_DIFF
	std::cout << "maxSize:" << maxSize << std::endl;
#endif //TRACE_DIFF
	// nombre d'offsets du fsa
	unsigned long int sizeFsa = 0;
	lexiconInit->setIndexStaticFSA(sizeFsa);
	if (!fwrite(&sizeFsa, sizeof(sizeFsa), 1, file))
		FATAL_ERROR
		;
#ifdef TRACE_DIFF
	std::cout << "sizeFsa:" << sizeFsa << std::endl;
#endif //TRACE_DIFF
	if (sizeFsa == (unsigned long int)~0UL) {
		std::cerr << "*** Error: Lexicon too large" << std::endl;
		return false;

	}
	unsigned long int sizeInfo = 0;
	lexiconInit->setIndexStaticInfo(sizeInfo);
	if (!fwrite(&sizeInfo, sizeof(sizeInfo), 1, file))
		FATAL_ERROR
		;
#ifdef TRACE_DIFF
	std::cout << "sizeInfo:" << sizeInfo << std::endl;
#endif //TRACE_DIFF
	if (sizeInfo == (unsigned long int)~0UL) {
		std::cerr << "*** Error: Data too large" << std::endl;
		return false;

	}
#ifdef TRACE_DIFF
	std::cout << "---FSA---" << std::endl;
#endif //TRACE_DIFF
	lexiconInit->printStaticFSA(file, this);

#ifdef TRACE_DIFF
	std::cout << "---Info---" << std::endl;
#endif //TRACE_DIFF
	lexiconInit->printStaticInfo(file);
	std::cerr << "*** Writing Data" << std::endl;
	// table
	fflush(file);
	if (!fwrite(&init, sizeof(init), 1, file))
		FATAL_ERROR
		;
#ifdef TRACE_DIFF
	std::cout << "init:" << init << std::endl;
#endif //TRACE_DIFF
	return true;
}

/* **************************************************
 *
 ************************************************** */
bool Lex::loadFsa(FILE *file) {
	//std::cerr << "*** Loading Finite State Automata" << std::endl;
	int nbrBytes;
	if (!fread(&nbrBytes, sizeof(nbrBytes), 1, file))
		FATAL_ERROR
		;
#ifdef TRACE_DIFF
	std::cout << "nbreBytes:" << nbrBytes << std::endl;
#endif //TRACE_DIFF
	unsigned long int maxSize;
	if (!fread(&maxSize, sizeof(maxSize), 1, file))
		FATAL_ERROR
		;
#ifdef TRACE_DIFF
	std::cout << "maxSize:" << maxSize << std::endl;
#endif //TRACE_DIFF
	if (nbrBytes != (sizeof(unsigned long int)) || (maxSize != (unsigned long int)~0UL)) {
		std::cerr << "*** lexicon compiled with an incompatible system" << std::endl;
		return false;

	}
	unsigned long int sizeFsa;
	if (!fread(&sizeFsa, sizeof(sizeFsa), 1, file))
		FATAL_ERROR
		;
#ifdef TRACE_DIFF
	std::cout << "sizeFsa:" << sizeFsa << std::endl;
#endif //TRACE_DIFF
	unsigned long int sizeInfo;
	if (!fread(&sizeInfo, sizeof(sizeInfo), 1, file))
		FATAL_ERROR
		;
#ifdef TRACE_DIFF
	std::cout << "sizeInfo:" << sizeInfo << std::endl;
#endif //TRACE_DIFF

#ifdef TRACE_DIFF
	std::cout << "---FSA---" << std::endl;
#endif //TRACE_DIFF
	fsa = new Fsa[sizeFsa + 1]();
	if (!fread(fsa, sizeof(Fsa), sizeFsa, file))
		FATAL_ERROR
		;
#ifdef TRACE_DIFF
	for(unsigned long int sizeSy=0;sizeSy<sizeFsa;sizeSy++) {
		fsa[sizeSy].print(std::cout);
	}
#endif //TRACE_DIFF

#ifdef TRACE_DIFF
	std::cout << "---Info---" << std::endl;
#endif //TRACE_DIFF
	info = new InfoBuff[sizeInfo + 1]();
	if (!fread(info, sizeof(InfoBuff), sizeInfo, file))
		FATAL_ERROR
		;
#ifdef TRACE_DIFF
	for(unsigned long int sizeSy=0;sizeSy<sizeInfo;sizeSy++) {
		std::cout << sizeSy << ' ';
		info[sizeSy].print(std::cout);
	}
#endif //TRACE_DIFF
	if (!fread(&init, sizeof(init), 1, file))
		FATAL_ERROR
		;
#ifdef TRACE_DIFF
	std::cout << "init:" << init << std::endl;
#endif //TRACE_DIFF
	return true;
}

/* **************************************************
 *
 ************************************************** */
bool Lex::build(std::string &directory, std::string &prefix, std::istream &inputStream, Pattern &pattern)
{
	bool result = true;
	FILE *fsaFile;
	FILE *tableFile;
	char line[MAXSTRING];
	std::string oldOutput;
	unsigned int range;
	unsigned long int offset;
	std::ostringstream oss;

	offset = 0;
	range = 0;

	oss << directory << "/" << prefix << ".tbl";
	std::string osss = oss.str();
	tableFile = fopen(osss.c_str(), "w"); //tableFileName.c_str(), "w");
	if (tableFile == NULL) {
		std::cerr << "Unable to open file " << osss << " for writing" << std::endl;
		result = false;
	}
	else {

		inputStream.seekg(0, std::ios::end);
		size_t size = inputStream.tellg();
		inputStream.seekg(0, std::ios::beg);

		Tree *lexicon;
		lexicon = new Tree(NULL, NULL, NULL, '\0');
		lexicon->setChild(new Tree(NULL, NULL, NULL, '\0'));
		lexiconInit = lexicon;
		lexicon = lexicon->getChild();

		int nbrItem = 0;
		while (inputStream.getline(line, MAXSTRING)) {
			if (!*line)
				continue;
			if (strchr(line, '#'))
				continue;
			//std::cout << "/line:/" << line << '/' << std::endl;
			char form[MAXSTRING];
			strcpy(form, line);
			char *rhs = strchr(form, '\t');
			*rhs = 0;

			char line2[MAXSTRING];
			strcpy(line2, line);
			char *pos = strchr(line2, '\t') + 1;
			rhs = strchr(pos, '\t');
			*rhs = 0;

			char line3[MAXSTRING];
			char line4[MAXSTRING];
			strcpy(line3, line);
			char *lemma = strchr(line3, '\t') + 1;
			lemma = strchr(lemma, '\t') + 1;
			rhs = strchr(lemma, '\t');
			char *fs = NULL;
			if (rhs) {
				*rhs = 0;
				strcpy(line4, line);
				fs = strchr(line4, '\t') + 1;
				fs = strchr(fs, '\t') + 1;
				fs = strchr(fs, '\t') + 1;
			}

			//std::cerr << "/line:/" << line << '/' << std::endl;
			//std::cerr << "/form:/" << form << '/' << std::endl;
			//std::cerr << "/pos:/" << pos << '/' << std::endl;
			//std::cerr << "/lemma:/" << lemma << '/' << std::endl;
			//std::cerr << "/fs:/" << (fs ? fs : "NULL") << '/' << std::endl;

			std::stringstream input2Stream;
			input2Stream << pos << "#_" << lemma;
			std::string input = std::string(input2Stream.str());

			extern Parser parser;
			featuresPtr features;
			if (fs && fs[0]) {
				std::stringstream fsStream;
				fsStream << '[' << fs << ']';
				std::string fsString = fsStream.str();
				if (parser.parseBuffer("#", fsString, "features"))
					std::cerr << "*** error in lexicon: " << line << std::endl;
				features = parser.getLocalFeatures();
			}
			else
				features = featuresPtr();

			std::stringstream outputStream;
			outputStream << form << "#[";
			if (fs && fs[0]) {
						parser.getLocalFeatures()->flatPrint(outputStream, false);
			}
			outputStream << ']';
			std::string output = outputStream.str();

			//CERR_LINE;
			//std::cerr << input << std::endl;
			  
			std::list<const std::string> *o = pattern.find(input);
			if (o->size()) {
				//features->flatPrint(std::cerr);

				for (std::list<const std::string>::const_iterator it = o->begin();
						it != o->end();
						++it) {

					//CERR_LINE;
					//std::cerr << "aaa" << input << std::endl;
					//std::cerr << "bbb" << *it << std::endl;

					char predicatePattern[MAXSTRING];
					strcpy(predicatePattern, it->c_str());
					char *rhs = strchr(predicatePattern, '#');
					*rhs = 0;

					char fsPatternLine[MAXSTRING];
					strcpy(fsPatternLine, it->c_str());
					char *fsPattern = strchr(fsPatternLine, '#')+1;
					std::stringstream fsPatternStream;
					fsPatternStream << '[' << fsPattern << ']';
					std::string fsPatternString = fsPatternStream.str();
					if (parser.parseBuffer("#", fsPatternString, "features"))
						std::cerr << "*** error in pattern: " << fsPatternString << std::endl;
					featuresPtr featuresPattern = parser.getLocalFeatures();

					std::stringstream input3Stream;
					input3Stream << pos << "#_" << predicatePattern;
					std::string input3 = std::string(input3Stream.str());

					statementPtr statement;
					featuresPtr unif;
					if (features && featuresPattern) {
							unif = statement->unif(features, featuresPattern, itemPtr());
					}
					else if (featuresPattern) {
						unif = featuresPattern;
					}
					else {
						unif = features;
					}

					//CERR_LINE;
				  //unif->flatPrint(std::cerr);
				  //std::cerr << std::endl;
				  if (!unif->isBottom()) {
				  	offset = ftell(tableFile);
				  	lexicon->add(input3.c_str(), offset);
				  	std::stringstream output2Stream;
				  	output2Stream << form << '#' << '[';
				  	unif->flatPrint(output2Stream, false);
				  	output2Stream << ']';
				  	std::string output2 = output2Stream.str();
				  	fprintf(tableFile, "%s%c", output2.c_str(), 0);
				  }

					//std::cout << "/Inputzzz:/" << input << '/' << std::endl;
					//std::cout << "/Outputzzz:/" << output2 << '/' << std::endl;

					//std::cerr << "/OK/" << input << " -> " << output2.c_str() << std::endl;
				}
				//	std::cerr << "/line:/" << line << '/' << std::endl;
				//	std::cerr << "/pos:/" << pos << '/' << std::endl;
				//	std::cerr << "/predicate:/" << predicate << '/' << std::endl;
				//	std::cerr << "/form:/" << form << '/' << std::endl;
				//	std::cerr << "/fs:/" << fs << '/' << std::endl;
			}
			else {
				offset = ftell(tableFile);
				lexicon->add(input.c_str(), offset);
				fprintf(tableFile, "%s%c", output.c_str(), 0);
			}

			nbrItem += strlen(line) + 1;
			if (!(range++ % 997)) {
				int k = (40 * (unsigned long int)(inputStream.tellg())) / (unsigned long int)size;
				std::cerr << " " << round(2.5*k) << "%[";
				int i = 0 ;
				for ( ; i <= k ; i++)
				  std::cerr << '#';
				for ( ; i <= 40 ; i++)
				  std::cerr << ' ';
				std::cerr << ']' << "\r";
			}
		}
		fclose(tableFile);

	}
	oss.str("");
	oss << directory << "/" << prefix << ".fsa";
	osss = oss.str();
	std::cerr << "*** Writing Finite State Automata " << osss << std::endl;
	fsaFile = fopen(osss.c_str(), "w");
	if (fsaFile == NULL) {
		std::cerr << "Unable to open file " << osss << " for writing" << std::endl;
		result = false;
	}
	else {
		if (!saveFsa(fsaFile))
			result = false;
		fclose(fsaFile);
	}
	return result;
}

/* **************************************************
 *
 ************************************************** */
bool Lex::load(const std::string &directory, const std::string &prefix) {
	unsigned long int size;
	std::ostringstream oss;
	oss << directory << "/" << prefix << ".fsa";
	std::string osss = oss.str();
	FILE *fsaFile = fopen(osss.c_str(), "r");
	if (fsaFile == NULL) {
		std::cerr << "File " << osss << " not found" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		if (!loadFsa(fsaFile)) {
			return false;
		}
		fclose(fsaFile);
	}
	oss.str("");
	oss << directory << "/" << prefix << ".tbl";
	osss = oss.str();
	FILE *tableFile = fopen(osss.c_str(), "r");
	if (tableFile == NULL) {
		std::cerr << "File " << osss << " not found" << std::endl;
		exit(EXIT_FAILURE);

	}
	else {
		//cerr << "*** Load buffer in memory" << endl;
		struct stat *statbuf;
		statbuf = (struct stat *)malloc(sizeof(struct stat));
		stat(osss.c_str(), statbuf);
		size = statbuf->st_size;
		free(statbuf);
		buffer = new char[size];
		buffer[0] = 0;
		if (!fread(buffer, 1, size, tableFile))
			FATAL_ERROR
			;
		fclose(tableFile);
	}
	return true;
}

/* **************************************************
 *
 ************************************************** */
bool Lex::consult(std::string inputFileName) {
	FILE *inputFile = NULL;
	if (inputFileName == "-") {
		std::cerr << "*** Searching from stdin" << std::endl;
		inputFile = stdin;
	}

	else if (inputFileName != "") {
		std::cerr << "*** Seaching " << inputFileName << std::endl;
		inputFile = fopen(inputFileName.c_str(), "r");
		if (!inputFile) {
			std::cerr << "Unable to open file " << inputFileName << " for reading" << std::endl;
			exit(EXIT_FAILURE);
		}

	}
	unsigned long int info;
	char str[MAXSTRING];
	if (inputFile) {
		while (fgets(str, MAXSTRING, inputFile)) {
			str[strlen(str) - 1] = 0;
			info = searchStatic(init, str);
			printResults(std::cout, info, 1);
			fflush(stdout);
		}
		fclose(inputFile);

	}
	return true;
}

