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
ForestIdentifier::ForestIdentifier(size_t code, uint8_t from, uint8_t to,
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
ForestIdentifier::create(size_t code,
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
    uint64_t encode = static_cast<uint64_t>(code) << 32 | static_cast<uint64_t>(from) << 8 | static_cast<uint64_t>(to);
    stream << std::hex << encode << '-' << featuresSerialString;
    //stream << std::hex << code << '-' << from << '-' << to << '-' << featuresSerialString;
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
