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

/* **************************************************
 *
 ************************************************** */
Serializable::Serializable()
{
    serialHashCode = 0;
    serialString = "";
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
std::string Serializable::peekSerialString()
{
    if (!serialHashCode)
    {
        makeSerialString();
        serialHashCode = std::hash<std::string>{}(serialString);
    }
    return serialString;
}

/* **************************************************
 *
 ************************************************** */
void Serializable::resetSerial()
 {
     serialHashCode = 0;
     serialString = "";
 }

/* **************************************************
 *
 ************************************************** */
size_t Serializable::hash()
{
    if (!serialHashCode)
    {
        makeSerialString();
        return serialHashCode = std::hash<std::string>{}(serialString);
    }
    return serialHashCode;
}

