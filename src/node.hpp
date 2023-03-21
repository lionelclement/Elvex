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
 * LaBRI -- Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef ELVEX_NODE_H
#define ELVEX_NODE_H

#include <vector>

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "facade.hpp"
#include "shared_ptr.hpp"

class Node :
        public Facade, 
        public std::enable_shared_from_this<class Node> {

public:
    typedef std::vector<forestPtr> vectorForests;
    typedef vectorForests::iterator vectorForests_iterator;
    typedef vectorForests::const_iterator vectorForests_const_iterator;

private:
    unsigned int nbrCS;
    vectorForests forests;
    std::vector<std::string> output;

    Node(void);

    void generate(vectorForests_const_iterator);

public:
    ~Node(void);

    static nodePtr create(void);

    bool empty() const;

    vectorForests_iterator begin();

    vectorForests_iterator end();

    vectorForests_const_iterator cbegin() const;

    vectorForests_const_iterator cend() const;

    size_t size() const;

    forestPtr at(size_t);
    
    void push_back(const forestPtr&);
    
    const std::vector<std::string>& getOutput(void) const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr, xmlNodePtr) const;
#endif

    void generate(bool random, bool first);

};

#endif // ELVEX_NODE_H

