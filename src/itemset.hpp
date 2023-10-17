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

#ifndef ELVEX_ITEMSET_H
#define ELVEX_ITEMSET_H

#include <unordered_set>

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "item.hpp"
#include "shared_ptr.hpp"

class ItemSet
{

public:
    typedef std::unordered_set<class Item *,
                               Item::Hash,
                               Item::KeyEqual,
                               std::allocator<class Item *>>
        set_of_item;
    typedef set_of_item::const_iterator set_of_item_const_iterator;
    typedef set_of_item::iterator set_of_item_iterator;

private:
    unsigned int id;

    set_of_item items;

public:
    ItemSet(unsigned int);

    ~ItemSet();

    static class ItemSet *create(unsigned int);

    unsigned int getId(void);

    set_of_item &getItems(void);

    set_of_item_const_iterator cbegin(void) const;

    set_of_item_const_iterator cend(void) const;

    set_of_item_iterator begin(void);

    set_of_item_iterator end(void);

    set_of_item_const_iterator find(class Item *) const;

    bool insert(class Item *, class Generator *);

    void erase(class Item *);

    size_t size(void) const;

    void resetUsages(void);

    void print(std::ostream &);

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif
};

#endif // ITEM_H
