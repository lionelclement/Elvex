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

#ifndef BITSET_H
#define BITSET_H

#ifndef MAXBITS
#define MAXBITS 512
#endif

#include <unordered_map>
#include <bitset>

#include "shared_ptr.hpp"
#include "serializable.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Bitset :
        public std::bitset<MAXBITS>, public Serializable, public std::enable_shared_from_this<Bitset> {

private:

    explicit Bitset(unsigned int = 0);

    explicit Bitset(std::bitset<MAXBITS> &);

    explicit Bitset(const bitsetPtr&);

    void makeSerialString() override;

public:
    ~Bitset() override;

    static bitsetPtr create(unsigned int = 0);

    static bitsetPtr create(std::bitset<MAXBITS>);

    static bitsetPtr create(const bitsetPtr&);

    std::string toString() const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif
};

#endif // BITSET_H
