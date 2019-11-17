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

#include <iostream>     // std::cout, std::endl
#include <iomanip>

#include "statements.hh"
#include "environment.hh"
#include "messages.hh"
#include "item.hh"
#include "statement.hh"
#include "synthesizer.hh"
#include "listfeatures.hh"

/* **************************************************
 *
 ************************************************** */
Statements::Statements(statementPtr statement)
		: Id(0), Flags() {
	if (statement)
		statements.push_front(statement);
	NEW;
}

/* **************************************************
 *
 ************************************************** */
Statements::~Statements() {
	DELETE;
	for (list::iterator i = statements.begin(); i != statements.end(); ++i)
		i->reset();
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Statements::create(statementPtr statement) {
	return statementsPtr(new Statements(statement));
}

/* **************************************************
 *
 ************************************************** */
size_t Statements::size(void) {
	return this->statements.size();
}

/* **************************************************
 *
 ************************************************** */
Statements::list::const_iterator Statements::begin(void) const {
	return this->statements.begin();
}

/* **************************************************
 *
 ************************************************** */
Statements::list::const_iterator Statements::end(void) const {
	return this->statements.end();
}

/* **************************************************
 *
 ************************************************** */
void Statements::addStatement(statementPtr statement) {
	if (statement->isGuard())
		this->guard = statement;
	else
		this->statements.push_back(statement);
}

/* **************************************************
 *
 ************************************************** */
void Statements::print(std::ostream& outStream, unsigned int tabulation, int yetColored) const {
	int color = yetColored;
	if (isSetFlags(Flags::SEEN)) {
		color |= 0x0000FF;
	}
	if (isSetFlags(Flags::DISABLED)) {
		color |= 0xC0C0C0;
	}
	if (isSetFlags(Flags::BOTTOM)) {
		color |= 0xFF0000;
	}
	if (color != 0)
		outStream << "<div style=\"color:#" << std::setfill('0') << std::setw(6) << std::hex << color << ";\">";
	else
		outStream << "<div>";
	tabulation += 3;
	for (unsigned int j = 1; j <= tabulation; ++j)
		outStream << "&nbsp;";
	outStream << "{<BR>";
	if (guard)
		guard->print(outStream, tabulation, yetColored | color);
	for (list::const_iterator i = statements.begin(); i != statements.end(); ++i)
		(*i)->print(outStream, tabulation, yetColored | color);
	for (unsigned int j = 1; j <= tabulation; ++j)
		outStream << "&nbsp;";
	outStream << "}";
	outStream << "</div>";
}

/* **************************************************
 *
 ************************************************** */
void Statements::makeSerialString() {
	serialString = '{';
	if (guard)
		serialString += guard->peekSerialString() + ';';
	for (list::const_iterator i = statements.begin(); i != statements.end(); ++i)
		serialString += (*i)->peekSerialString() + ';';
	serialString += '}';
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Statements::clone(const std::bitset<Flags::FLAGS> &protectedFlags) {
	statementsPtr statements = Statements::create();
	statements->guard = (guard) ? guard->clone(protectedFlags) : statementPtr();
	for (list::const_iterator i = this->statements.begin(); i != this->statements.end(); ++i)
		statements->addStatement((*i)->clone(protectedFlags));
	statements->addFlags(protectedFlags & this->getFlags());
	return statements;
}

/* **************************************************
 *
 ************************************************** */
void Statements::renameVariables(unsigned int i) {
	if (guard)
		guard->renameVariables(i);
	for (list::const_iterator j = this->statements.begin(); j != this->statements.end(); ++j)
		(*j)->renameVariables(i);
}

/* **************************************************
 * Applique l'ensemble des instructions
 ************************************************** */
void Statements::apply(itemPtr item, Parser &parser, bool trace) {
	if (item->isSetFlags(Flags::BOTTOM))
		return;

	if (guard) {
		if (guard->isUnsetFlags(Flags::SEEN)) {
			guard->apply(item, parser, trace);
			guard->addFlags(Flags::SEEN);
			if (guard->isSetFlags(Flags::BOTTOM)) {
				//this->addFlags(Flags::BOTTOM);
				item->addFlags(Flags::BOTTOM);
				return;
			}
		}
	}

	bool allDone = true;
	for (list::iterator statement = statements.begin(); statement != statements.end(); ++statement) {
		if ((*statement)->isUnsetFlags(Flags::SEEN)) {
			bool effect = false;
			(*statement)->enable(*statement, item, effect, false);
			if (effect)
				(*statement)->enable(*statement, item, effect, true);
			if (effect)
				allDone = false;
			if ((*statement)->isSetFlags(Flags::DISABLED)) {
				allDone = false;
				continue;
			}
			if (!item->getEnvironment() || item->getEnvironment()->size() == 0) {
				item->setEnvironment(environmentPtr());
			}
			(*statement)->apply(item, parser, trace);
			if ((*statement)->isSetFlags(Flags::BOTTOM)) {
				//this->addFlags(Flags::BOTTOM);
				item->addFlags(Flags::BOTTOM);
				break;
			}
		}
	}
	if (allDone)
		this->addFlags(Flags::SEEN);

}

/* **************************************************
 *
 ************************************************** */
void Statements::lookingForAssignedInheritedSonFeatures(std::vector<bool> &assignedInheritedSonFeatures) {
	FATAL_ERROR
	;
	for (list::const_iterator i = statements.begin(); i != statements.end(); ++i) {
		std::cerr << '.';
		(*i)->lookingForAssignedInheritedSonFeatures(assignedInheritedSonFeatures);
	}
}

/* **************************************************
 *
 ************************************************** */
void Statements::enable(itemPtr item, bool &effect, bool on) {
	if (guard)
		guard->enable(guard, item, effect, on);
	for (list::const_iterator i = statements.begin(); i != statements.end(); ++i) {
		(*i)->enable(*i, item, effect, on);
	}
}

/* **************************************************
 *
 ************************************************** */
bool Statements::findVariableElsewhere(statementPtr o, bitsetPtr variable) {
	FATAL_ERROR
	;
	for (list::const_iterator i = statements.begin(); i != statements.end(); ++i) {
		if ((*i) == o)
			continue;
		if ((*i)->findVariable(variable))
			return true;
	}
	return false;
}

