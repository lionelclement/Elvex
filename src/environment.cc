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

#include <regex>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "environment.hh"
#include "messages.hh"
#include "list.hh"
#include "feature.hh"
#include "features.hh"
#include "value.hh"
#include "ipointer.hh"
#include "listfeatures.hh"

/* **************************************************
 *
 ************************************************** */
Environment::Environment() {
	NEW;
}

/* **************************************************
 *
 ************************************************** */
Environment::~Environment() {
	DELETE;
	for (unordered_map::iterator i = env.begin(); i != env.end(); ++i) {
		valuePtr tmp = i->second;
		if (tmp)
			tmp.reset();
	}
}

/* **************************************************
 *
 ************************************************** */
environmentPtr Environment::create() {
	return environmentPtr(new Environment());
}

/* **************************************************
 *
 ************************************************** */
void Environment::add(const std::string key, valuePtr value) {
	Environment::unordered_map::iterator it = env.find(key);
	if (it == env.end()) {
		env.insert(std::make_pair(key, value));
	}
	else {
		it->second = value;
	}
}

/* **************************************************
 *
 ************************************************** */
void Environment::remove(const std::string key) {
	env.erase(key);
}

/* **************************************************
 *
 ************************************************** */
void Environment::add(bitsetPtr attr, valuePtr value) {
	const std::string key = attr->toString();
	add(key, value);
}

/* **************************************************
 *
 ************************************************** */
void Environment::add(const environmentPtr e) {
	for (Environment::unordered_map::const_iterator i = e->begin(); i != e->end(); ++i)
		add(i->first, i->second);
}

/* **************************************************
 *
 ************************************************** */
void Environment::add(const environmentPtr e, const environmentPtr where) {
	if (where)
		for (Environment::unordered_map::const_iterator i = e->begin(); i != e->end(); i++)
			if (where->env.find(i->first) != where->env.end())
				add(i->first, i->second);
}

/* **************************************************
 *
 ************************************************** */
void Environment::remove(bitsetPtr attr) {
	const std::string key = attr->toString();
	remove(key);
}

/* **************************************************
 *
 ************************************************** */
Environment::unordered_map::const_iterator Environment::begin() const {
	return env.begin();
}

/* **************************************************
 *
 ************************************************** */
Environment::unordered_map::const_iterator Environment::end() const {
	return env.end();
}

/* **************************************************
 *
 ************************************************** */
const size_t Environment::size() const {
	return env.size();
}

/* **************************************************
 *
 ************************************************** */
valuePtr Environment::find(bitsetPtr attr) const {
	const std::string key = attr->toString();
	Environment::unordered_map::const_iterator it = env.find(key);
	if (it != env.end())
		return it->second;
	else
		return valuePtr();
}

/* **************************************************
 *
 ************************************************** */
void Environment::print(std::ostream &out) const {
	bool first = true;
	Environment::unordered_map::const_iterator i = begin();
	out << "<TABLE border=\"1\"><TR>";
	while (i != end()) {
		if (first)
			first = false;
		else
			out << "</TR><TR>";
		out << "<TD>";
		out << "env:" << (*i).first;
		if ((*i).second) {
			out << ":</TD><TD>";
			(*i).second->print(out);
		}
		out << "</TD>";
		++i;
	}
	out << "</TR></TABLE>";
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(featuresPtr features, bool &effect) {
	/***
	 std::cerr << "<H4>Environment::replaceVariables(features)</H4>" << std::endl;
	 std::cerr << "<table border=\"1\"><tr><th>featurePtrs</th><th>Environment</th></tr>";
	 std::cerr << "<tr><td>";
	 features->print(std::cerr);
	 std::cerr << "</td><td>";
	 this->print(std::cerr);
	 std::cerr << "</td></tr></table>";
	 ***/
	if (!features->containsVariable())
		return;

	redo: for (std::list<featurePtr>::iterator feature = features->begin(); feature != features->end(); ++feature) {
		switch ((*feature)->getType()) {
			case Feature::PRED:
				if ((*feature)->getValue())
					replaceVariables((*feature)->getValue(), effect);
				break;
			case Feature::FORM:
			case Feature::CONSTANT:
				if ((*feature)->getValue()) {
					replaceVariables((*feature)->getValue(), effect);
				}
				else
					FATAL_ERROR
					;
				break;
			case Feature::VARIABLE: {
				if ((*feature)->getValue()) {
					effect = true;
					replaceVariables((*feature)->getValue(), effect);
				}

				valuePtr value = find((*feature)->getAttribute());
				if (!value) {
					/* do nothing */
				}

				else if (value->isNil()) {
					/* do nothing */
				}

				else if (value->isFeatures()) {
					features->erase(feature);
					for (std::list<featurePtr>::iterator f = value->getFeatures()->begin(); f != value->getFeatures()->end(); ++f) {
						features->add(*f);
					}
					effect = true;
					goto redo;
				}

				else if (value->isConstant()) {
					(*feature)->setType(Feature::CONSTANT);
					(*feature)->setAttribute(value->getBits());
				}

				else if (value->isAnonymous()) {
					features->erase(feature);
					effect = true;
					goto redo;
				}

				else {
					FATAL_ERROR_MSG("environment: variable substitution failed");
				}
			}
			break;
		}
		features->setVariableFlag(VariableFlag::DOES_NOT_CONTAIN);
	}
	/***
	 std::cerr << "<H4>Environment::replaceVariables(features) DONE</H4>" << std::endl;
	 std::cerr << "<table border=\"1\"><tr><th>Features</th><th>Environment</th></tr>";
	 std::cerr << "<tr><td>";
	 features->print(std::cerr);
	 std::cerr << "</td><td>";
	 this->print(std::cerr);
	 std::cerr << "</td></tr></table>";
	 ***/
	if (effect)
		features->resetSerial();
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(listFeaturesPtr listFeatures, bool &effect) {
	for (ListFeatures::vector::const_iterator vf = listFeatures->begin(); vf != listFeatures->end(); ++vf)
		//if (*vf)
		this->replaceVariables(*vf, effect);
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(valuePtr value, bool &effect) {
	/***
	 std::cerr << "<H4>Environment::replaceVariables(value)</H4>" << std::endl;
	 std::cerr << "<table border=\"1\"><tr><th>Value</th><th>Environment</th></tr>";
	 std::cerr << "<tr><td>";
	 value->print(std::cerr);
	 std::cerr << "</td><td>";
	 this->print(std::cerr);
	 std::cerr << "</td></tr></table>";
	 ***/
	if (!value->containsVariable())
		return;
	if (!value->isNil() && !value->isTrue()) {
		switch (value->getType()) {
			case Value::BOOL:
			case Value::STR:
			case Value::CONSTANT:
			case Value::IDENTIFIER:
			case Value::ANONYMOUS:
			case Value::DOUBLE:
				break;
			case Value::FEATURES:
				replaceVariables(value->getFeatures(), effect);
				break;
			case Value::LIST:
				replaceVariables(value->getList(), effect);
				break;
			case Value::VARIABLE:
				valuePtr val = find(value->getBits());
				if (val && (val != value)) {
					effect = true;
					*value = *val;
					replaceVariables(value, effect);
				}
				break;
		}
		value->setVariableFlag(VariableFlag::DOES_NOT_CONTAIN);
	}
	/***
	 std::cerr << "<H4>Environment::replaceVariables(value) result</H4>" << std::endl;
	 std::cerr << "<table border=\"1\"><tr><th>Std::List</th></tr>";
	 std::cerr << "<tr><td>";
	 std::cerr << "</td></tr></table>";
	 ***/
	if (effect)
		value->resetSerial();
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(listPtr list, bool &effect) {
	/***
	 std::cerr << "<H4>Environment::replaceVariables(list)</H4>" << std::endl;
	 std::cerr << "<table border=\"1\"><tr><th>List</th><th>Environment</th></tr>";
	 std::cerr << "<tr><td>";
	 list->flatPrint(std::cerr, 0);
	 std::cerr << "</td><td>";
	 this->print(std::cerr);
	 std::cerr << "</	td></tr></table>";
	 ***/
	if (!list->containsVariable())
		return;
	switch (list->getType()) {
		case List::ATOM:
			if (list->isVariable()) {
				valuePtr value = this->find(list->getValue()->getBits());
				if (value->isList()) {
					*list = *(value->getList());
				}
				else if (value->isNil()) {
					*list = *List::NIL_LIST;
					;
				}
				else {
					FATAL_ERROR
					;
				}
			}
			else
				//if (list->containsVariable())
				replaceVariables(list->getValue(), effect);
			break;

		case List::PAIRP:
			//if (list->getCar()->containsVariable())
			replaceVariables(list->getCar(), effect);
			//if (list->getCdr()->containsVariable())
			replaceVariables(list->getCdr(), effect);
			break;

		case List::NIL:
			break;
	}
	list->setVariableFlag(VariableFlag::DOES_NOT_CONTAIN);
	/***
	 std::cerr << "<H4>Environment::replaceVariables(list) result</H4>" << std::endl;
	 std::cerr << "<table border=\"1\"><tr><th>List</th></tr>";
	 std::cerr << "<tr><td>";
	 list->flatPrint(std::cerr, 0);
	 std::cerr << "</td></tr></table>";
	 ***/
	if (effect)
		list->resetSerial();
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(std::string &str, bool &effect) {
	/*** */
	std::cerr << "<H4>Environment::replaceVariables(list)</H4>" << std::endl;
	std::cerr << "<table border=\"1\"><tr><th>std::string</th><th>Environment</th></tr>";
	std::cerr << "<tr><td>";
	std::cerr << str;
	std::cerr << "</td><td>";
	this->print(std::cerr);
	std::cerr << "</td></tr></table>";
	/* ***/
	FATAL_ERROR;
	std::string pattern =
			std::string(
					"(\\$([a-zA-Z_]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß)([a-zA-Z0-9_]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß)+)");
	std::cmatch match;

	try {
		std::regex regexpression(pattern, std::regex_constants::ECMAScript);
		while (std::regex_search(str.c_str(), match, regexpression, std::regex_constants::format_first_only)) {
			const std::string key = match[1];
			Environment::unordered_map::iterator i = this->env.find(key);
			if (i == this->env.end()) {
				std::cerr << "*** error variable " << match[1] << " not found" << std::endl;
				exit(1);
			}
			else {
				std::ostringstream oss;
				i->second->print(oss);
				str = std::regex_replace(str, regexpression, oss.str(), std::regex_constants::format_first_only);
			}
		}
	}

	catch (const std::regex_error& e) {
		std::cout << "regex_error caught: " << e.what() << '(' << e.code() << ')' << std::regex_constants::error_brack << '\n';
	}
	/*** */
	std::cerr << "<H4>Environment::replaceVariables(list) result</H4>" << std::endl;
	std::cerr << "<table border=\"1\"><tr><th>Std::List</th></tr>";
	std::cerr << "<tr><td>";
	this->print(std::cerr);
	std::cerr << "</td></tr></table>";
	/* ***/
	//return result;
}

/* **************************************************
 *
 ************************************************** */
environmentPtr Environment::clone(void) const {
	environmentPtr environment = Environment::create();
	for (Environment::unordered_map::const_iterator i = begin(); i != end(); ++i) {
		environment->add((*i).first, ((*i).second) ? (*i).second->clone() : valuePtr());
	}
	return environment;
}
