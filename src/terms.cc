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

/* **************************************************
 *
 ************************************************** */
Terms::Terms(std::vector<class Term* >& terms, bool optional)
{
  NEW;
  this->terms = terms;
  this->optional = optional;
  // this->ready = false;
}

/* **************************************************
 *
 ************************************************** */
Terms::Terms(class Term* term, bool optional)
{
  NEW;
  this->terms.push_back(term);
  this->optional = optional;
  // this->ready = false;
}

/* **************************************************
 *
 ************************************************** */
Terms::~Terms()
{
  //DELETE;
}

/* **************************************************
 *
 ************************************************** */
bool Terms::isOptional(void) const 
{
  return optional;
}

/* **************************************************
 *
 ************************************************** */
void Terms::setOptional()
{
  this->optional = true;
}

/* **************************************************
 *
 ************************************************** */
void Terms::unsetOptional()
{
  this->optional = false;
}

/* **************************************************
 *
 ************************************************** */
size_t Terms::size(void) const 
{
  return terms.size();
}

/* **************************************************
 *
 ************************************************** */
std::vector<class Term*>::const_iterator Terms::begin(void) const 
{
  return terms.begin();
}

/* **************************************************
 *
 ************************************************** */
std::vector<class Term*>::const_iterator Terms::end(void) const 
{
  return terms.end();
}

/* **************************************************
 *
 ************************************************** */
void Terms::erase(std::vector<class Term*>::iterator begin, std::vector<class Term*>::iterator end)
{
  terms.erase(begin, end);
}

/* **************************************************
 *
 ************************************************** */
void Terms::push_back(class Term* term)
{
  terms.push_back(term);
}

/* **************************************************
 *
 ************************************************** */
const bool Terms::Less::operator () (const class Terms* t1, const class Terms* t2) const
{
  if (t1->optional != t2->optional)
    return (t1->optional < t2->optional);

  if (t1->size() != t2->size())
    return (t1->size() < t2->size());

  std::vector<class Term*>::const_iterator s1=t1->begin();
  std::vector<class Term*>::const_iterator s2=t2->begin();
  while (s1!=t1->end()){
    if ((*s1) != (*s2))
      return ((*s1) < (*s2));
    ++s1; ++s2;
  }
  return false;
}

/* **************************************************
 *
 ************************************************** */
void
Terms::print(std::ostream& outStream)
{
  if (optional)
    outStream << '[';
  if (size()>1){
    bool first = true;
    for (std::vector< class Term * >::const_iterator term = begin();
	 term != end();
	 ++term){
      if (first)
	first = false;
      else
	outStream << '|';
      (*term)->print(outStream);
    }
  }
  else{
    terms[0]->print(outStream);
  }
  if (optional)
    outStream << ']';
}

/* **************************************************
 *
 ************************************************** */
class Terms * 
Terms::clone(void)
{
  std::vector<class Term * > new_terms;
  for (std::vector<class Term * >::const_iterator t = begin();
       t != end();
       ++t)
    new_terms.push_back((*t)->clone());
  return new Terms(new_terms, optional);
}

class Term *
Terms::operator[] (unsigned int i)
{
  return terms[i];
}
