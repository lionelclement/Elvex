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

#ifndef ELVEX_SERIALIZABLE_H
#define ELVEX_SERIALIZABLE_H

#include <string>

class Serializable {

private:
    int serialHashCode;

    virtual void makeSerialString() = 0;

protected:
    std::string serialString;

public:
    explicit Serializable();

    virtual ~Serializable();

    std::string peekSerialString();

    size_t hashCode();

    void resetSerial();

};

#endif // ELVEX_SERIALIZABLE_H
