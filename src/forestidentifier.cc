/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI, 
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

#include "forestidentifier.hpp"
#include "messages.hpp"
#include "vartable.hpp"

/* ************************************************************
 *                                                            *
 ************************************************************ */
ForestIdentifier::ForestIdentifier(unsigned int code, const std::string &featuresSerialString, unsigned int from,
                                   unsigned int to) {
    this->code = code;
    this->featuresSerialString = featuresSerialString;
    this->from = from;
    this->to = to;
    NEW
}

/* **************************************************
 *
 ************************************************** */
ForestIdentifier::~ForestIdentifier() {
    DELETE
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
forestIdentifierPtr
ForestIdentifier::create(unsigned int code, const std::string &featuresSerialString, unsigned int from,
                         unsigned int to) {
    return forestIdentifierPtr(new ForestIdentifier(code, featuresSerialString, from, to));
}

/* **************************************************
 *
 ************************************************** */
void ForestIdentifier::makeSerialString() {
    serialString = std::to_string(code) + '-' + Vartable::codeToString(code) + '[' + std::to_string(from) + '-' + std::to_string(to) + ']'
                    + featuresSerialString;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool ForestIdentifier::operator<(const ForestIdentifier &o) const {
    return ((this->code < o.code) || (this->from < o.from) || (this->to < o.to) ||
            (this->featuresSerialString < o.featuresSerialString));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool ForestIdentifier::operator!=(const ForestIdentifier &o) const {
    return ((this->code != o.code) || (this->from != o.from) || (this->to != o.to) ||
            (this->featuresSerialString != o.featuresSerialString));
}

/* **************************************************
 *
 ************************************************** */
size_t ForestIdentifier::hash::operator()(const forestIdentifierPtr i) const {
    return i->hashCode();
}

/* **************************************************
 *
 ************************************************** */
bool ForestIdentifier::equal_to::operator()(const forestIdentifierPtr i1, const forestIdentifierPtr i2) const {
    return i1->peekSerialString() == i2->peekSerialString();
}

