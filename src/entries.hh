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

#ifndef ENTRIES_H
#define ENTRIES_H

#include <iostream>
#include <vector>
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif
#include "ipointer.hh"

class Entries:
		public std::enable_shared_from_this<class Entries> {

	public:
		typedef std::vector<entryPtr> list;

	private:
		list entries;

		Entries();
		Entries(entryPtr);
		Entries(const list&);
		Entries(const unsigned int codePos, const unsigned int codeLemma, const std::string form);

	public:
		~Entries();
		static entriesPtr create();
		static entriesPtr create(entryPtr);
		static entriesPtr create(const list &);
		static entriesPtr create(unsigned int codePos, const unsigned int codeLemma, const std::string form);

		const size_t size() const;
		list::const_iterator begin() const;
		list::const_iterator end() const;
		entryPtr get(const unsigned int) const;

		void add(const entryPtr);
#ifdef OUTPUT_XML
		void toXML(xmlNodePtr) const;
#endif
		void print(std::ostream &) const;
};

#endif // ENTRIES_H
