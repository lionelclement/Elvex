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

#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include "pattern.hh"
#include "messages.hh"

std::list<const std::string> *Pattern::emptyList = new std::list<const std::string>();

/* **************************************************
 *
 ************************************************** */
Pattern::Pattern(void) {
	NEW;
}

/* **************************************************
 *
 ************************************************** */
void Pattern::add(std::string key, const std::string value) {
	Unordered_map::iterator it = unordered_map.find(key);
	if (it != unordered_map.end())
		(*it).second->push_back(value);
	else {
		std::list<const std::string> *list = new std::list<const std::string>();
		list->push_back(value);
		unordered_map[key] = list;
	}
}

/* **************************************************
 *
 ************************************************** */
std::list<const std::string> *Pattern::find(const std::string key) {
	Unordered_map::const_iterator it = unordered_map.find(key);
	if (it != unordered_map.end()) {
		return (*it).second;
	}
	else {
		return emptyList;
	}
}

/* **************************************************
 *
 ************************************************** */
std::string &Pattern::toString(void) const
{
	static std::string result;
	std::ostringstream oss;
	oss << unordered_map.size();
	result = oss.str();
	return result;
}
