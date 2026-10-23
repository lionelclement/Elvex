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

#ifndef ELVEX_FORESTIDENTIFIER_H
#define ELVEX_FORESTIDENTIFIER_H

#include "serializable.hpp"
#include "shared_ptr.hpp"

/**
 * Canonical key identifying a constituent by symbol and chart span.
 * Used to look up shared forests independently of pointer identity.
 * The serialized key and its hash are computed lazily by Serializable.
 */
class ForestIdentifier :
        public Serializable {

private:

    uint32_t code;
    uint32_t from;
    uint32_t to;
    

public:
    ForestIdentifier(uint32_t code, uint32_t from, uint32_t to);

    ~ForestIdentifier() override;

    /** Allocate a key for the symbol and chart span [from, to].
     * The caller is responsible for the lifetime of the returned pointer.
     */
    static class ForestIdentifier* create(uint32_t code, uint32_t from, uint32_t to);

    /** Encode the three identity fields for content-based equality. */
    void makeCoreSerialString() override;
    
    uint32_t getFrom() const {
        return from;
    };

    uint32_t getTo() const {
        return to;
    };

    uint32_t getCode() const {
        return code;
    };

    /** Hash raw pointers according to their serialized identifier content. */
    struct Hash {
         size_t operator()(class ForestIdentifier *) const;
    };

    /** Compare serialized keys, not the addresses of the key objects. */
    struct KeyEqual {
         bool operator()(class ForestIdentifier *, class ForestIdentifier *) const;
    };

};

#endif // ELVEX_FORESTIDENTIFIER_H
