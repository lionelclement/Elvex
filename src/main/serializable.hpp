/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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
#include <cstddef>

class Serializable
{
private:
    size_t coreSerialHashCode;

    virtual void makeCoreSerialString() = 0;

protected:
    std::string coreSerialString;

public:
    explicit Serializable();

    virtual ~Serializable();

    // Sérialisation d'identité logique (clé des sets/maps)
    std::string peekCoreSerialString();

    // Hash logique
    size_t coreHash();

    // Invalide uniquement la sérialisation logique
    void resetCoreSerial();
};

#endif // ELVEX_SERIALIZABLE_H