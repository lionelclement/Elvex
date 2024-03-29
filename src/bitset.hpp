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

#ifndef BITSET_H
#define BITSET_H

#include <unordered_map>
#include <bitset>

#include "shared_ptr.hpp"
#include "serializable.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#ifndef MAXBITS
#define MAXBITS 512
#endif

class Bitset : public std::bitset<MAXBITS>,
               public Serializable,
               public std::enable_shared_from_this<Bitset>
{

private:
    void makeSerialString() override;

public:
    explicit Bitset(unsigned int = 0);

    explicit Bitset(const std::bitset<MAXBITS> &);

    explicit Bitset(const bitsetPtr &);

    ~Bitset() override;

    static bitsetPtr create(unsigned int = 0);

    static bitsetPtr create(const std::bitset<MAXBITS>);

    static bitsetPtr create(const bitsetPtr &);

    std::string toString() const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    bitsetPtr clone(void);
};

#endif // BITSET_H
