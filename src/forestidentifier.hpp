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

    uint16_t code;
    uint8_t from;
    uint8_t to;
    std::string featuresSerialString;

    ForestIdentifier(uint16_t code, uint8_t from, uint8_t to, 
            const std::string& featuresSerialString);

public:
    ~ForestIdentifier() override;

    static class ForestIdentifier* create(uint16_t code, uint8_t from, uint8_t to, 
            const std::string& featuresSerialString);

    void makeSerialString() override;
    
    uint8_t getFrom() const {
        return from;
    };

    uint8_t getTo() const {
        return to;
    };

    uint16_t getCode() const {
        return code;
    };

    struct hash {
        size_t operator()(class ForestIdentifier*) const;
    };

    struct equal_to {
        bool operator()(class ForestIdentifier*, class ForestIdentifier*) const;
    };

};

#endif // ELVEX_FORESTIDENTIFIER_H
