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

#ifndef ENTRIES_H
#define ENTRIES_H

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include <vector>
#include "shared_ptr.hpp"

class Entries :
        public std::enable_shared_from_this<class Entries> {

private:
    std::vector<entryPtr> entries;

    Entries();

    Entries(const entryPtr& );

    Entries(const std::vector<entryPtr>& );

    Entries(unsigned int codePos, unsigned int codeLemma, std::string& form);

public:
    ~Entries();

    static entriesPtr create();

    static entriesPtr create(const entryPtr& );

    static entriesPtr create(const std::vector<entryPtr>& );

    static entriesPtr create(unsigned int codePos, unsigned int codeLemma, std::string& form);

    size_t size() const;

    std::vector<entryPtr>::iterator begin();

    std::vector<entryPtr>::iterator end();

    entryPtr get(unsigned int) const;

    void add(const entryPtr& );

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr) const;
#endif

    void print(std::ostream& ) const;
};

#endif // ENTRIES_H
