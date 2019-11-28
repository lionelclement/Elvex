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

#include "messages.hh"
#include "entries.hh"
#include "entry.hh"

/* **************************************************
 *
 ************************************************** */
Entries::Entries(void) {
   NEW;
}

/* **************************************************
 *
 ************************************************** */
Entries::Entries(entryPtr entry) {
   this->entries.insert(this->entries.begin(), entry);
   NEW;
}

/* **************************************************
 *
 ************************************************** */
Entries::Entries(const list &entries) {
   this->entries = entries;
   NEW;
}

/* **************************************************
 *
 ************************************************** */
Entries::Entries(const unsigned int codePos, const unsigned int codeLemma, const std::string form) {
   this->entries.insert(this->entries.begin(), Entry::create(codePos, codeLemma, form));
   NEW;
}

/* **************************************************
 *
 ************************************************** */
Entries::~Entries() {
   DELETE;
   for (list::iterator i = entries.begin(); i != entries.end(); i++) {
      entryPtr tmp = *i;
      if (tmp)
         tmp.reset();
   }
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create(void) {
   return entriesPtr(new Entries());
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create(entryPtr entry) {
   return entriesPtr(new Entries(entry));
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create(const list &entries) {
   return entriesPtr(new Entries(entries));
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create(unsigned int codePos, unsigned int codeLemma, std::string form) {
   return entriesPtr(new Entries(codePos, codeLemma, form));
}

/* **************************************************
 *
 ************************************************** */
const size_t Entries::size(void) const {
   return this->entries.size();
}

/* **************************************************
 *
 ************************************************** */
Entries::list::const_iterator Entries::begin(void) const {
   return this->entries.begin();
}

/* **************************************************
 *
 ************************************************** */
Entries::list::const_iterator Entries::end(void) const {
   return this->entries.end();
}

/* **************************************************
 *
 ************************************************** */
void Entries::add(entryPtr entry) {
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
   for (list::const_iterator i=entries.begin();
         i!=entries.end();
         ++i)
   (*i)->toXML(node);
}
#endif

/* **************************************************
 *
 ************************************************** */
void Entries::print(std::ostream& out) const {
   for (list::const_iterator i = entries.begin(); i != entries.end(); ++i)
      (*i)->print(out);
}
