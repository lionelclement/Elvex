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
ForestIdentifier::ForestIdentifier(uint32_t code, uint8_t from, uint8_t to,
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
ForestIdentifier::_create(uint32_t code,
                         uint8_t from,
                         uint8_t to,
                         const std::string &featuresSerialString)
{
    return new ForestIdentifier(code, from, to, featuresSerialString);
}

/* **************************************************
 *
 ************************************************** */
void ForestIdentifier::makeSerialString()
{
    std::ostringstream stream;
    uint32_t encode = static_cast<uint32_t>(code) << 16 | static_cast<uint32_t>(from) << 8 | static_cast<uint32_t>(to);
    stream << std::hex << encode << '\x0' << featuresSerialString;
    serialString = stream.str();
}

/* **************************************************
 *
 ************************************************** */
size_t ForestIdentifier::hash::operator()(class ForestIdentifier *forestIdentifier) const
{
    return forestIdentifier->hashCode();
}

/* **************************************************
 *
 ************************************************** */
bool ForestIdentifier::equal_to::operator()(class ForestIdentifier *forestIdentifier1, class ForestIdentifier *forestIdentifier2) const
{
    return forestIdentifier1->peekSerialString() == forestIdentifier2->peekSerialString();
}
