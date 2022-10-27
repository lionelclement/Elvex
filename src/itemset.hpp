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
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef ELVEX_ITEMSET_H
#define ELVEX_ITEMSET_H

#include <unordered_set>
#include <climits>

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "item.hpp"
#include "shared_ptr.hpp"

class ItemSet :
    public std::enable_shared_from_this<class ItemSet> {

public:
    typedef std::unordered_set<itemPtr, Item::hash, Item::equal_to> set_of_item;
    typedef set_of_item::const_iterator set_of_item_const_iterator;
    typedef set_of_item::iterator set_of_item_iterator;

private:
    unsigned int id;
    set_of_item items;

    ItemSet(unsigned int);

public:
    ~ItemSet();

    static itemSetPtr create(unsigned int);

    unsigned int getId(void);

    set_of_item& getItems(void);

    set_of_item_const_iterator cbegin(void) const;

    set_of_item_const_iterator cend(void) const;

    set_of_item_iterator begin(void);

    set_of_item_iterator end(void);

    set_of_item_const_iterator find(const itemPtr&) const;

    void insert(const itemPtr&, class Synthesizer*);

    void erase(const itemPtr&);

    size_t size(void) const;

    void resetUsages(void);

    void print(std::ostream&);

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

};

#endif // ITEM_H
