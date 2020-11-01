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

#include "messages.hpp"
#include "entries.hpp"
#include "entry.hpp"

/* **************************************************
 *
 ************************************************** */
Entries::Entries() {
    NEW
}

/* **************************************************
 *
 ************************************************** */
Entries::Entries(const entryPtr &entry) {
    this->entries.insert(this->entries.begin(), entry);
    NEW
}

/* **************************************************
 *
 ************************************************** */
Entries::Entries(const std::vector<entryPtr>& entries) {
    this->entries = entries;
    NEW
}

/* **************************************************
 *
 ************************************************** */
Entries::Entries(const unsigned int codePos, const unsigned int codeLemma, const std::string &form) {
    this->entries.insert(this->entries.begin(), Entry::create(codePos, codeLemma, form));
    NEW
}

/* **************************************************
 *
 ************************************************** */
Entries::~Entries() {
    for (auto tmp : entries) {
        if (tmp)
            tmp.reset();
    }
    DELETE
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
entriesPtr Entries::create(const std::vector<entryPtr>& entries) {
    return entriesPtr(new Entries(entries));
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create(unsigned int codePos, unsigned int codeLemma, const std::string &form) {
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
std::vector<entryPtr>::iterator Entries::begin() {
    return entries.begin();
}

/* **************************************************
 *
 ************************************************** */
std::vector<entryPtr>::iterator  Entries::end() {
    return entries.end();
}

/* **************************************************
 *
 ************************************************** */
void Entries::add(const entryPtr &entry) {
    this->entries.push_back(entry);
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entries::get(unsigned int i) const {
    return this->entries.at(i);
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Entries::toXML(xmlNodePtr nodeRoot) const
{
   xmlNodePtr node=xmlNewChild(nodeRoot, nullptr, (const xmlChar*)"ENTRIES", nullptr);
   for (const auto & entrie : entries)
   entrie->toXML(node);
}
#endif

/* **************************************************
 *
 ************************************************** */
void Entries::print(std::ostream &out) const {
  for (const auto& i : entries)
        i->print(out);
}
