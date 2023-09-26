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

#ifndef ELVEX_FOREST_H
#define ELVEX_FOREST_H

#include <vector>
#include "facade.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "flags.hpp"
#include "shared_ptr.hpp"

class Forest : public Facade,
               public std::enable_shared_from_this<class Forest>
{

public:
    typedef std::vector<nodePtr> vectorNodes;

private:
    uint8_t from;
    uint8_t to;
    vectorNodes nodes;
    bool empty;
    terminalPtr terminal;
    std::vector<std::string> output;
    Forest(terminalPtr terminal, uint8_t from, uint8_t to);

public:
    ~Forest();

    static forestPtr create(terminalPtr terminal, uint8_t from, uint8_t to);

    uint8_t getFrom(void) const;

    uint8_t getTo(void) const;

    bool isEmpty(void) const;

    size_t output_size(void) const;

    const std::vector<std::string>::const_iterator output_cbegin(void) const;

    const std::vector<std::string>::const_iterator output_cend(void) const;

    void push_back_node(const nodePtr &);

#ifdef OUTPUT_XML
    void toXML(const xmlNodePtr, bool);
#endif

    void generate(bool randomResult, bool singleResult);
};

#endif // ELVEX_FOREST_H
