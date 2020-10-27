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

//#include <sstream>
//#include <iostream>
//#include "messages.hpp"
#include "serializable.hpp"

/* **************************************************
 *
 ************************************************** */
Serializable::Serializable() {
    serialHashCode = 0;
    serialString = std::string();
}

/* **************************************************
 *
 ************************************************** */
Serializable::~Serializable() {
}

/* **************************************************
 *
 ************************************************** */
size_t Serializable::hashCode() {
    if (serialHashCode == 0) {
        peekSerialString();
    }
    return serialHashCode;
}

/* **************************************************
 *
 ************************************************** */
std::string Serializable::peekSerialString() {
  if (serialString.empty()) {
        makeSerialString();
        serialHashCode = std::hash<std::string>()(serialString);
    }
    return serialString;
}

/* **************************************************
 *
 ************************************************** */
void Serializable::resetSerial() {
    serialHashCode = 0;
    serialString = std::string();
}
