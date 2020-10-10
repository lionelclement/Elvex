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

#include "messages.h"
#include "entries.h"
#include "entry.h"

/* **************************************************
 *
 ************************************************** */
Entries::Entries() {
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Entries::Entries(const entryPtr &entry) {
    this->entries.insert(this->entries.begin(), entry);
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Entries::Entries(const vector &entries) {
    this->entries = entries;
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Entries::Entries(const unsigned int codePos, const unsigned int codeLemma, const std::string &form) {
    this->entries.insert(this->entries.begin(), Entry::create(codePos, codeLemma, form));
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Entries::~Entries() {
    for (auto i = entries.begin(); i != entries.end(); i++) {
        entryPtr tmp = *i;
        if (tmp)
            tmp.reset();
    }
    DELETE;
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create() {
    return entriesPtr(new Entries());
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create(const entryPtr &entry) {
    return entriesPtr(new Entries(entry));
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create(const vector &entries) {
    return entriesPtr(new Entries(entries));
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create(unsigned int codePos, unsigned int codeLemma, const std::string& form) {
    return entriesPtr(new Entries(codePos, codeLemma, form));
}

/* **************************************************
 *
 ************************************************** */
size_t Entries::size() const {
    return this->entries.size();
}

/* **************************************************
 *
 ************************************************** */
Entries::vector::const_iterator Entries::begin() const {
    return this->entries.begin();
}

/* **************************************************
 *
 ************************************************** */
Entries::vector::const_iterator Entries::end() const {
    return this->entries.end();
}

/* **************************************************
 *
 ************************************************** */
void Entries::add(const entryPtr& entry) {
    this->entries.push_back(entry);
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entries::get(unsigned int i) const {
    return this->entries.at(i);
}

/* **************************************************
 *
 ************************************************** */
//entryPtr Entries::get(const unsigned int index) const
//{
//  return this->entries[index];
//}
#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Entries::toXML(xmlNodePtr nodeRoot) const
{
   xmlNodePtr node=xmlNewChild(nodeRoot, NULL, (const xmlChar*)"ENTRIES", NULL);
   for (auto i = entries.begin();
         i!=entries.end();
         ++i)
   (*i)->toXML(node);
}
#endif

/* **************************************************
 *
 ************************************************** */
void Entries::print(std::ostream &out) const {
    for (auto i = entries.begin(); i != entries.end(); ++i)
        (*i)->print(out);
}
