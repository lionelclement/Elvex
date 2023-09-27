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

#include "serializable.hpp"

/* **************************************************
 *
 ************************************************** */
Serializable::Serializable()
{
    serialHashCode = 0;
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
uint32_t Serializable::hashCode()
{
    if (serialHashCode == 0)
    {
        peekSerialString();
    }
    return serialHashCode;
}

/* **************************************************
 *
 ************************************************** */
std::string Serializable::peekSerialString()
{
    if (serialString.empty())
    {
        makeSerialString();
        serialHashCode = static_cast<uint32_t>(std::hash<std::string>{}(serialString));
    }
    return serialString;
}

/* **************************************************
 *
 ************************************************** */
void Serializable::resetSerial()
{
    serialHashCode = 0;
    serialString = std::string();
}
