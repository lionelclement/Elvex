/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2020 LABRI, 
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

#include "term.h"
#include "vartable.h"
#include "messages.h"

/* **************************************************
 *
 ************************************************** */
Term::Term(unsigned int code) {
    this->code = code;
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Term::~Term() {
    DELETE;
}

/* **************************************************
 *
 ************************************************** */
termPtr Term::create(unsigned int code) {
    return termPtr(new Term(code));
}

/* **************************************************
 *
 ************************************************** */
unsigned int Term::getCode(void) const {
    return code;
}

/* **************************************************
 *
 ************************************************** */
bool Term::Less::operator()(const termPtr t1, const termPtr t2) const {
    if (t1->getCode() != t2->getCode())
        return (t1->getCode() < t2->getCode());
    return false;
}

/* **************************************************
 *
 ************************************************** */
void Term::print(std::ostream &outStream) const {
    outStream << Vartable::codeToIdentifier(code);
}

/* **************************************************
 *
 ************************************************** */
std::string Term::toString() const {
    return Vartable::codeToIdentifier(code);
}

/* **************************************************
 *
 ************************************************** */
termPtr Term::clone() const {
    return create(code);
}
