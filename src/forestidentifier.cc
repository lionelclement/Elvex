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
ForestIdentifier::ForestIdentifier(uint32_t code, uint32_t from, uint32_t to)
{
    NEW;
    this->code = code;
    this->from = from;
    this->to = to;
    //this->featuresSerialString = featuresSerialString;
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
ForestIdentifier::create(uint32_t code,
                         uint32_t from,
                         uint32_t to)
{
    return new ForestIdentifier(code, from, to);
}

/* **************************************************
 *
 ************************************************** */
void ForestIdentifier::makeSerialString()
{
    std::ostringstream stream;
    stream << '#' << std::hex << code << '#' << from << '#' << to;
    stream.flush();
    serialString = stream.str();
}

/* **************************************************
 *
 ************************************************** */
size_t ForestIdentifier::Hash::operator()(ForestIdentifier *forestIdentifier) const
{
    return forestIdentifier->hash();
}

/* **************************************************
 *
 ************************************************** */
bool ForestIdentifier::KeyEqual::operator()(ForestIdentifier *forestIdentifier1, ForestIdentifier *forestIdentifier2) const
{
    return forestIdentifier1->peekSerialString() == forestIdentifier2->peekSerialString();
}
