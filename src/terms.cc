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

#include "terms.hh"
#include "term.hh"
#include "messages.hh"
#include "ipointer.hh"

/* **************************************************
 *
 ************************************************** */
Terms::Terms(std::vector<termPtr>& terms, bool optional) {
   this->terms = terms;
   this->optional = optional;
   NEW;
}

/* **************************************************
 *
 ************************************************** */
Terms::Terms(termPtr term, bool optional) {
   this->terms.push_back(term);
   this->optional = optional;
   NEW;
}

/* **************************************************
 *
 ************************************************** */
Terms::Terms() {
   this->optional = false;
   NEW;
}

/* **************************************************
 *
 ************************************************** */
Terms::~Terms() {
   DELETE;
   for (termPtr t : terms) {
      t.reset();
   }
}

/* **************************************************
 *
 ************************************************** */
termsPtr Terms::create(std::vector<termPtr>& terms, bool optional) {
   return termsPtr(new Terms(terms, optional));
}

/* **************************************************
 *
 ************************************************** */
termsPtr Terms::create(termPtr term, bool optional) {
   return termsPtr(new Terms(term, optional));
}

/* **************************************************
 *
 ************************************************** */
termsPtr Terms::create() {
   return termsPtr(new Terms());
}

/* **************************************************
 *
 ************************************************** */
bool Terms::isOptional(void) const {
   return optional;
}

/* **************************************************
 *
 ************************************************** */
void Terms::setOptional() {
   this->optional = true;
}

/* **************************************************
 *
 ************************************************** */
void Terms::unsetOptional() {
   this->optional = false;
}

/* **************************************************
 *
 ************************************************** */
size_t Terms::size(void) const {
   return terms.size();
}

/* **************************************************
 *
 ************************************************** */
std::vector<termPtr>::const_iterator Terms::begin(void) const {
   return terms.begin();
}

/* **************************************************
 *
 ************************************************** */
std::vector<termPtr>::const_iterator Terms::end(void) const {
   return terms.end();
}

/* **************************************************
 *
 ************************************************** */
void Terms::erase(std::vector<termPtr>::iterator begin, std::vector<termPtr>::iterator end) {
   terms.erase(begin, end);
}

/* **************************************************
 *
 ************************************************** */
void Terms::push_back(termPtr term) {
   terms.push_back(term);
}

/* **************************************************
 *
 ************************************************** */
const bool Terms::Less::operator ()(const termsPtr t1, const termsPtr t2) const {
   if (t1->optional != t2->optional)
      return (t1->optional < t2->optional);

   if (t1->size() != t2->size())
      return (t1->size() < t2->size());

   std::vector<termPtr>::const_iterator s1 = t1->begin();
   std::vector<termPtr>::const_iterator s2 = t2->begin();
   while (s1 != t1->end()) {
      if ((*s1) != (*s2))
         return ((*s1) < (*s2));
      ++s1;
      ++s2;
   }
   return false;
}

/* **************************************************
 *
 ************************************************** */
void Terms::print(std::ostream& outStream) {
   if (optional)
      outStream << '[';
   if (size() > 1) {
      bool first = true;
      for (std::vector<termPtr>::const_iterator term = begin(); term != end(); ++term) {
         if (first)
            first = false;
         else
            outStream << '|';
         (*term)->print(outStream);
      }
   }
   else {
      terms[0]->print(outStream);
   }
   if (optional)
      outStream << ']';
}

/* **************************************************
 *
 ************************************************** */
termsPtr Terms::clone(void) const {
   std::vector<termPtr> new_terms;
   for (std::vector<termPtr>::const_iterator t = begin(); t != end(); ++t)
      new_terms.push_back((*t)->clone());
   return Terms::create(new_terms, optional);
}

termPtr Terms::operator[](unsigned int i) {
   return terms[i];
}
