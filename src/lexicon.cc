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

#include "lexicon.hh"

#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include "messages.hh"

std::list<std::string> *Lexicon::emptyList = new std::list<std::string>();

/* **************************************************
 *
 ************************************************** */
Lexicon::Lexicon(void) {
   NEW;
}

/* **************************************************
 *
 ************************************************** */
void Lexicon::add(std::string key, const std::string value) {
   Unordered_map::iterator it = unordered_map.find(key);
   if (it != unordered_map.end())
      (*it).second->push_back(value);
   else {
      std::list<std::string> *list = new std::list<std::string>();
      list->push_back(value);
      unordered_map[key] = list;
   }
}

/* **************************************************
 *
 ************************************************** */
std::list<std::string> *Lexicon::find(const std::string key) {
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
std::string &Lexicon::toString(void) const {
   static std::string result;
   std::ostringstream oss;
   oss << unordered_map.size();
   result = oss.str();
   return result;
}
