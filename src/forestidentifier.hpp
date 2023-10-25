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

#ifndef ELVEX_FORESTIDENTIFIER_H
#define ELVEX_FORESTIDENTIFIER_H

#include "serializable.hpp"
#include "shared_ptr.hpp"

class ForestIdentifier :
        public Serializable {

private:

    uint32_t code;
    uint32_t from;
    uint32_t to;
    

public:
    ForestIdentifier(uint32_t code, uint32_t from, uint32_t to);

    ~ForestIdentifier() override;

    static class ForestIdentifier* create(uint32_t code, uint32_t from, uint32_t to);

    void makeSerialString() override;
    
    uint32_t getFrom() const {
        return from;
    };

    uint32_t getTo() const {
        return to;
    };

    uint32_t getCode() const {
        return code;
    };

    struct Hash {
         size_t operator()(class ForestIdentifier *) const;
    };

    struct KeyEqual {
         bool operator()(class ForestIdentifier *, class ForestIdentifier *) const;
    };

};

#endif // ELVEX_FORESTIDENTIFIER_H
