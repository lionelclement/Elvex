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

    unsigned int code;
    unsigned int from;
    unsigned int to;
    std::string featuresSerialString;

    ForestIdentifier(unsigned int code, unsigned int from, unsigned int to, 
            const std::string& featuresSerialString);

public:
    ~ForestIdentifier() override;

    static class ForestIdentifier* create(unsigned int code, unsigned int from, unsigned int to, 
            const std::string& featuresSerialString);

    void makeSerialString() override;

    unsigned int getFrom() const {
        return from;
    };

    unsigned int getTo() const {
        return to;
    };

    unsigned int getCode() const {
        return code;
    };

    bool operator<(ForestIdentifier const&) const;

    bool operator!=(ForestIdentifier const&) const;

    struct hash {
        size_t operator()(class ForestIdentifier*) const;
    };

    struct equal_to {
        bool operator()(class ForestIdentifier*, class ForestIdentifier*) const;
    };

};

#endif // ELVEX_FORESTIDENTIFIER_H
