/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2023 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: 
 * Lionel Clément
 * LaBRI - Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#include "terms.hpp"
#include "messages.hpp"
#include "shared_ptr.hpp"
#include "vartable.hpp"

/* **************************************************
 *
 ************************************************** */
Terms::Terms(std::vector<unsigned int> &terms, bool optional) {
    this->terms = terms;
    this->optional = optional;
    NEW
}

/* **************************************************
 *
 ************************************************** */
Terms::Terms(unsigned int term, bool optional) {
    this->terms.push_back(term);
    this->optional = optional;
    NEW
}

/* **************************************************
 *
 ************************************************** */
Terms::Terms() {
    this->optional = false;
    NEW
}

/* **************************************************
 *
 ************************************************** */
Terms::~Terms() {
    DELETE
}

/* **************************************************
 *
 ************************************************** */
termsPtr Terms::create(std::vector<unsigned int> &terms, bool optional) {
    return termsPtr(new Terms(terms, optional));
}

/* **************************************************
 *
 ************************************************** */
termsPtr Terms::create(unsigned int term, bool optional) {
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
std::vector<unsigned int>::const_iterator Terms::begin(void) const {
    return terms.begin();
}

/* **************************************************
 *
 ************************************************** */
std::vector<unsigned int>::const_iterator Terms::end(void) const {
    return terms.end();
}

/* **************************************************
 *
 ************************************************** */
void Terms::erase(std::vector<unsigned int>::iterator begin, std::vector<unsigned int>::iterator end) {
    terms.erase(begin, end);
}

/* **************************************************
 *
 ************************************************** */
void Terms::push_back(unsigned int term) {
    terms.push_back(term);
}

/* **************************************************
 *
 ************************************************** */
bool Terms::Less::operator()(const termsPtr t1, const termsPtr t2) const {
    if (t1->optional != t2->optional)
        return (t1->optional < t2->optional);

    if (t1->size() != t2->size())
        return (t1->size() < t2->size());

    auto s1 = t1->begin();
    auto s2 = t2->begin();
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
void Terms::print(std::ostream &outStream) {
    if (optional)
        outStream << '[';
    if (size() > 1) {
        bool first = true;
        for (auto term = this->begin(); term != this->end(); ++term) {
            if (first)
                first = false;
            else
                outStream << '|';
            outStream << Vartable::codeToString(*term);
        }
    } else {
        outStream << Vartable::codeToString(terms[0]);
    }
    if (optional)
        outStream << ']';
}

/* **************************************************
 *
 ************************************************** */
termsPtr Terms::clone(void) const {
    std::vector<unsigned int> new_terms;
    for (auto t = begin(); t != end(); ++t)
        new_terms.push_back((*t));
    return Terms::create(new_terms, optional);
}

unsigned int Terms::operator[](unsigned int i) {
    return terms[i];
}
