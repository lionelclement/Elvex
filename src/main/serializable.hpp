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

/**
 * Provides canonical serialization and hashing of an object core.
 * Derived classes define which structural fields participate in identity.
 */
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
    /** Get the canonical core representation used for structural equality. */
    std::string peekCoreSerialString();

    // Hash logique
    /** Hash the canonical core representation. */
    size_t coreHash();

    // Invalide uniquement la sérialisation logique
    /** Invalidate a cached core representation after a structural change. */
    void resetCoreSerial();
};

#endif // ELVEX_SERIALIZABLE_H