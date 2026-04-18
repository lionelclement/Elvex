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

#include <iostream>
#include "serializable.hpp"
#include "messages.hpp"

/* **************************************************
 *
 ************************************************** */
Serializable::Serializable()
{
    coreSerialString = std::string();
    coreSerialHashCode = 0;
}

/* **************************************************
 *
 ************************************************** */
Serializable::~Serializable()
{
}

/* **************************************************
 *
 ************************************************** */
std::string Serializable::peekCoreSerialString()
{
    if (coreSerialHashCode == 0)
    {
        std::string old = coreSerialString;
        makeCoreSerialString();
        if (!old.empty() && old != coreSerialString){
            std::cerr << old << " != " << coreSerialString << std::endl;
        }
        coreSerialHashCode = std::hash<std::string>{}(coreSerialString);
    }
    return coreSerialString;
}

/* **************************************************
 *
 ************************************************** */
void Serializable::resetCoreSerial()
 {
    coreSerialHashCode = 0;
 }

/* **************************************************
 *
 ************************************************** */
size_t Serializable::coreHash()
{
    if (coreSerialHashCode == 0)
    {
        makeCoreSerialString();
        return coreSerialHashCode = std::hash<std::string>{}(coreSerialString);
    }
    return coreSerialHashCode;
}
