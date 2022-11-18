/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI, 
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

#ifndef ELVEX_TERMS_H
#define ELVEX_TERMS_H

#include <iostream>
#include <vector>

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "shared_ptr.hpp"

class Terms :
        public std::enable_shared_from_this<class Terms> {

private:
    std::vector<unsigned int> terms;
    bool optional;

    Terms(std::vector<unsigned int> &, bool optional);

    Terms(unsigned int, bool optional);

    Terms(void);

public:
    ~Terms();

    static termsPtr create(std::vector<unsigned int> &, bool optional = false);

    static termsPtr create(unsigned int, bool optional = false);

    static termsPtr create(void);

    bool isOptional(void) const;

    void setOptional(void);

    void unsetOptional(void);

    size_t size(void) const;

    std::vector<unsigned int>::const_iterator begin(void) const;

    std::vector<unsigned int>::const_iterator end(void) const;

    void erase(std::vector<unsigned int>::iterator begin, std::vector<unsigned int>::iterator end);

    void push_back(unsigned int term);

    void print(std::ostream &outStream = std::cout);

    termsPtr clone(void) const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    // compares two terms
    struct Less {
        bool operator()(const termsPtr t1, const termsPtr t2) const;
    };

    unsigned int operator[](unsigned int);
};

#endif // ELVEX_TERMS_H
