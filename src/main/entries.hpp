/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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

#ifndef ENTRIES_H
#define ENTRIES_H

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include <vector>
#include "shared_ptr.hpp"

/**
 * Collection of lexical analyses associated with a lexical lookup.
 * Callers may receive shared entries; generation clones an entry before unification.
 */
class Entries : public std::enable_shared_from_this<class Entries>
{

private:
    std::vector<entryPtr> entries;

public:
    Entries();

    Entries(const entryPtr &);

    Entries(const std::vector<entryPtr> &);

    ~Entries();

    static entriesPtr create();

    static entriesPtr create(const entryPtr &);

    static entriesPtr create(const std::vector<entryPtr> &);

    size_t size() const;

    std::vector<entryPtr>::const_iterator cbegin() const;

    std::vector<entryPtr>::const_iterator cend() const;

    std::vector<entryPtr>::iterator begin();

    std::vector<entryPtr>::iterator end();

    /** Return a shared entry handle (the entry itself is not copied). */
    entryPtr get(unsigned int) const;

    void add(const entryPtr &);

    /**
     * Append another collection of lexical analyses to this list.
     * Do not mutate a parser-owned list when merging independent sources.
     */
    void add(entriesPtr);

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr) const;
#endif

    void print(std::ostream &) const;
};

#endif // ENTRIES_H
