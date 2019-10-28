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

#include <map>
#include <bitset>

#include "bitset.hh"
#include "flags.hh"
#include "vartable.hh"
#include "messages.hh"
#include "ipointer.hh"

const std::bitset< MAXBITS> Bitset::LEXBITSET = 1ul;
const std::bitset< MAXBITS> Bitset::ARGBITSET = Bitset::LEXBITSET << 1;
const std::bitset< MAXBITS> Bitset::SYSBITSET = Bitset::ARGBITSET << 1;
const std::bitset< MAXBITS> Bitset::FIRSTBITSET = Bitset::SYSBITSET << 1;

Bitset::map Bitset::bitsToStrTable;

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(unsigned int data)
		: std::bitset< MAXBITS>(data) {
	NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(std::bitset< MAXBITS>& data)
		: std::bitset< MAXBITS>(data) {
	NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(bitsetPtr bitset)
		: std::bitset< MAXBITS>(*bitset) {
	NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::~Bitset() {
	DELETE;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr Bitset::create(unsigned int data) {
	return bitsetPtr(new Bitset(data));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr Bitset::create(std::bitset< MAXBITS> data) {
	return bitsetPtr(new Bitset(data));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr Bitset::create(bitsetPtr bs) {
	return bitsetPtr(new Bitset(bs));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
const std::string Bitset::toString() const {
	std::stringstream s;
	size_t c = this->count();
	size_t sz = this->size();
	bool first = true;
	for (size_t i = 0; i < sz && c > 0; ++i) {
		if ((*this)[i]) {
			--c;
			if (first)
				first = false;
			else
				s << '|';
			s << bitsToStrTable[i];
		}
	}
	return s.str();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Bitset::makeSerialString() {
	serialString = std::string();
	std::stringstream s;
	size_t c = this->count();
	size_t sz = this->size();
	for (size_t i = 0; i < sz && c > 0; ++i) {
		if ((*this)[i]) {
			--c;
			serialString += std::to_string(i);
			if (c > 0)
				serialString += ',';
			//std::to_string(i);
		}
	}
}

#ifdef OUTPUT_XML
/* ************************************************************
 *                                                            *
 ************************************************************ */
void Bitset::toXML(xmlNodePtr nodeRoot)
{
	xmlNodePtr f=xmlNewChild(nodeRoot, NULL, (const xmlChar*)"ALT", NULL);
	map::const_iterator varTableIt;
	size_t c=this->count();
	size_t sz=this->size();
	for(unsigned int i = 0; i < sz && c > 0; ++i)
	if (this->test(i)) {
		--c;
		varTableIt = bitsToStrTable.find(i);
		if (varTableIt != bitsToStrTable.end())
		xmlNewChild(f, NULL, (const xmlChar*)"OPT", (const xmlChar*)varTableIt->second.c_str());
	}
}
#endif
