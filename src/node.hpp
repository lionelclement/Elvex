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

#ifndef ELVEX_NODE_H
#define ELVEX_NODE_H

#include <vector>
#include <list>

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "flags.hpp"
#include "uniq-id.hpp"
#include "shared_ptr.hpp"

class Node :
        public Flags, public UniqId, public std::enable_shared_from_this<class Node> {

private:
    unsigned int nbrCS;
    std::vector<forestPtr> forests;
    std::vector<std::string> output;

    Node();

    void generate(std::vector<forestPtr>::const_iterator);

public:
    ~Node();

    static nodePtr create();

    std::vector<forestPtr> &getForests();

    const std::vector<std::string> &getOutput() const;

    void addForest(const forestPtr&);

    forestPtr getForest(unsigned int) const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr, xmlNodePtr) const;
#endif

    void generate(bool random, bool one);

};

#endif // ELVEX_NODE_H

