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

#ifndef ELVEX_FOREST_H
#define ELVEX_FOREST_H

#include <vector>
#include "id.h"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "flags.h"
#include "shared_ptr.h"

class Forest :
        public Id, public Flags, public std::enable_shared_from_this<class Forest> {

public:
    typedef std::vector<nodePtr> vectorNodes;

private:
    unsigned int from;
    unsigned int to;
    vectorNodes nodes;
    bool empty;
    entryPtr entry;
    std::vector<std::string> output;

    Forest(entryPtr entry, unsigned int from, unsigned int to);

public:
    ~Forest();

    static forestPtr create(entryPtr entry, unsigned int from, unsigned int to);

    const vectorNodes &getNodes(void) const;

    unsigned int getFrom(void) const;

    unsigned int getTo(void) const;

    bool isEmpty(void) const;

    const std::vector<std::string> &getOutput(void) const;

    void addNode(const nodePtr&);

#ifdef OUTPUT_XML
    void toXML(const xmlNodePtr, bool);
#endif

    void generate(bool random, bool one);

};

#endif // ELVEX_FOREST_H
