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

#ifndef ELVEX_NODE_H
#define ELVEX_NODE_H

#include <vector>
#include <forward_list>

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

private:
    vectorForests forests;
    std::forward_list<std::string> output;
    bool withSpace;
    bool bidirectional;
    bool permutable;

public:
    Node(bool withSpace, bool bidirectional, bool permutable);

    ~Node(void);

    static nodePtr create(bool withSpace, bool bidirectional, bool permutable);

    bool empty() const;

    vectorForests::iterator begin();

    vectorForests::iterator end();

    vectorForests::const_iterator cbegin() const;

    vectorForests::const_iterator cend() const;

    size_t size() const;

    forestPtr at(size_t);
    
    void push_back(const forestPtr&);
    
    const std::forward_list<std::string>::const_iterator output_cbegin(void) const;

    const std::forward_list<std::string>::const_iterator output_cend(void) const;

    bool getWithSpace() const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr, xmlNodePtr) const;
#endif

    void generateLR(std::string &currentCombination, vectorForests::const_iterator forestIt);
    void generateRL(std::string currentCombination, vectorForests::const_iterator forestIt);
    void generatePermutations(vectorForests& forests, int start, int end);
    void generate(bool randomResult, bool singleResult);

};

#endif // ELVEX_NODE_H

