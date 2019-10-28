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

#ifndef BITSET_H
#define BITSET_H

#ifndef MAXBITS
#define MAXBITS 512
#endif

#include <unordered_map>
#include <map>
#include <bitset>

#include "ipointer.hh"
#include "serializable.hh"
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Bitset:
		public std::bitset<MAXBITS>,
		public Serializable,
		public std::enable_shared_from_this<Bitset> {

		typedef std::map<unsigned int, std::string> map;

	private:
		static const std::bitset<MAXBITS> LEXBITSET;
		static const std::bitset<MAXBITS> ARGBITSET;
		static const std::bitset<MAXBITS> SYSBITSET;
		static const std::bitset<MAXBITS> FIRSTBITSET;

	public:
		static map bitsToStrTable;

	private:
		Bitset(unsigned int = 0);
		Bitset(std::bitset<MAXBITS> &);
		Bitset(bitsetPtr);
		void makeSerialString();

	public:
		~Bitset();
		static bitsetPtr create(unsigned int = 0);
		static bitsetPtr create(std::bitset<MAXBITS>);
		static bitsetPtr create(bitsetPtr);
		const std::string toString(void) const;
#ifdef OUTPUT_XML
		void toXML(xmlNodePtr);
#endif
};

#endif // BITSET_H
