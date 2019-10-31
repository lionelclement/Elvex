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

#ifndef RULE_H
#define RULE_H

#include <climits>
#include <ostream>
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif
#include "id.hh"
#include "ipointer.hh"
#include "serializable.hh"

class Rule:
		public Id::Id,
		public std::enable_shared_from_this<class Rule> {

private:
	termPtr lhs;
	std::vector<termsPtr> rhs;
	statementsPtr statements;
	unsigned int usages;
	std::string filename;
	unsigned int lineno;
	Rule(size_t id, unsigned int lineno, std::string filename, termPtr lhs, statementsPtr statements = statementsPtr());
	Rule(unsigned int lineno, std::string filename, termPtr lhs, statementsPtr statements = statementsPtr());
	Rule(unsigned int lineno, std::string filename, termPtr lhs, std::vector<termsPtr> &rhs, statementsPtr statements = statementsPtr());
	Rule(size_t id, unsigned int lineno, std::string filename, termPtr lhs, std::vector<termsPtr> &rhs, statementsPtr statements = statementsPtr());

public:
	static rulePtr create(size_t id, unsigned int lineno, std::string filename, termPtr lhs, statementsPtr statements = statementsPtr());
	static rulePtr create(unsigned int lineno, std::string filename, termPtr lhs, statementsPtr statements = statementsPtr());
	static rulePtr create(unsigned int lineno, std::string filename, termPtr lhs, std::vector<termsPtr> &rhs, statementsPtr statements = statementsPtr());
	static rulePtr create(size_t id, unsigned int lineno, std::string filename, termPtr lhs, std::vector<termsPtr> &rhs, statementsPtr statements = statementsPtr());
	~Rule();

	termPtr getLhs(void) const;
	std::vector<termsPtr> &getRhs(void);

	termPtr getCurrentTerm(void) const;
	termsPtr getCurrentTerms() const;
	termsPtr getTerms(unsigned int) const;
	void setCurrentTerms(termsPtr);

	statementsPtr getStatements(void) const;
	void incUsages(class Synthesizer *);
	void resetUsages(void);

	const unsigned int getLineno(void) const;
	const std::string &getFilename(void) const;

	rulePtr clone() const;
	void print(std::ostream &, unsigned int = UINT_MAX, bool = false, bool = true) const;

#ifdef OUTPUT_XML
	void toXML(xmlNodePtr);
#endif
	void addDefaults(void);

};

#endif // RULE_H
