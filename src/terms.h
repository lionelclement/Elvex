/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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

#ifndef ELVEX_TERMS_H
#define ELVEX_TERMS_H

#include <iostream>
#include <vector>

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "shared_ptr.h"

class Terms :
        public std::enable_shared_from_this<class Terms> {

private:
    std::vector<termPtr> terms;
    bool optional;

    Terms(std::vector<termPtr> &, bool optional);

    Terms(termPtr, bool optional);

    Terms(void);

public:
    ~Terms();

    static termsPtr create(std::vector<termPtr> &, bool optional = false);

    static termsPtr create(termPtr, bool optional = false);

    static termsPtr create(void);

    bool isOptional(void) const;

    void setOptional(void);

    void unsetOptional(void);

    size_t size(void) const;

    std::vector<termPtr>::const_iterator begin(void) const;

    std::vector<termPtr>::const_iterator end(void) const;

    void erase(std::vector<termPtr>::iterator begin, std::vector<termPtr>::iterator end);

    void push_back(termPtr term);

    void print(std::ostream &outStream = std::cout);

    termsPtr clone(void) const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    // compare deux termes
    struct Less {
        bool operator()(const termsPtr t1, const termsPtr t2) const;
    };

    termPtr operator[](unsigned int);
};

#endif // ELVEX_TERMS_H
