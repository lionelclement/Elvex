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

#include "forestidentifier.hpp"
#include "messages.hpp"
#include "vartable.hpp"

/* ************************************************************
 *                                                            *
 ************************************************************ */
ForestIdentifier::ForestIdentifier(unsigned int code, unsigned int from, unsigned int to,
                                   const std::string &featuresSerialString)
{
    NEW;
    this->code = code;
    this->featuresSerialString = featuresSerialString;
    this->from = from;
    this->to = to;
}

/* **************************************************
 *
 ************************************************** */
ForestIdentifier::~ForestIdentifier()
{
    DELETE;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
class ForestIdentifier *
ForestIdentifier::create(unsigned int code,
                         unsigned int from,
                         unsigned int to,
                         const std::string &featuresSerialString)
{
    return new ForestIdentifier(code, from, to, featuresSerialString);
}

/* **************************************************
 *
 ************************************************** */
void ForestIdentifier::makeSerialString()
{
    serialString =
        std::to_string(code) + '[' + std::to_string(from) + '-' + std::to_string(to) + ']' + featuresSerialString;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool ForestIdentifier::operator<(const ForestIdentifier &o) const
{
    return ((this->code < o.code) || (this->from < o.from) || (this->to < o.to) ||
            (this->featuresSerialString < o.featuresSerialString));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool ForestIdentifier::operator!=(const ForestIdentifier &o) const
{
    return ((this->code != o.code) || (this->from != o.from) || (this->to != o.to) ||
            (this->featuresSerialString != o.featuresSerialString));
}

/* **************************************************
 *
 ************************************************** */
size_t ForestIdentifier::hash::operator()(class ForestIdentifier *i) const
{
    return i->hashCode();
}

/* **************************************************
 *
 ************************************************** */
bool ForestIdentifier::equal_to::operator()(class ForestIdentifier *i1, class ForestIdentifier *i2) const
{
    return i1->peekSerialString() == i2->peekSerialString();
}
