/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2018 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: Lionel Clément,
 * Labri -- 351, cours de la Libération
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
Entries::Entries(void)
{
  NEW;
}

/* **************************************************
 *
 ************************************************** */
Entries::Entries(entryPtr  entry)
{
  NEW;
  this->entries.push_front(entry);
}

/* **************************************************
 *
 ************************************************** */
Entries::Entries(std::list<entryPtr  >& entries)
{
  NEW;
  this->entries=entries;
}

/* **************************************************
 *
 ************************************************** */
Entries::Entries(int codePos, int codeLemma, std::string form)
{
  NEW;
  this->entries.push_front(Entry::create(codePos, codeLemma, form));
}

/* **************************************************
 *
 ************************************************** */
Entries::~Entries()
{
  for (std::list<entryPtr  >::iterator i=entries.begin();
       i!=entries.end();
       i++) {
    entryPtr tmp = *i;
    if (tmp)
      tmp.reset();
  }
  DELETE;
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create(void)
{
  return entriesPtr( new Entries() );
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create(entryPtr  entry)
{
  return entriesPtr( new Entries(entry) );
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create(std::list<entryPtr  > &entries)
{
  return entriesPtr( new Entries(entries) );
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Entries::create(int codePos, int codeLemma, std::string form)
{
  return entriesPtr( new Entries(codePos, codeLemma, form) );
}

/* **************************************************
 *
 ************************************************** */
const size_t Entries::size(void) const
{
  return this->entries.size();
}

/* **************************************************
 *
 ************************************************** */
std::list<entryPtr >::const_iterator Entries::begin(void) const
{
  return this->entries.begin();
}

/* **************************************************
 *
 ************************************************** */
std::list<entryPtr >::const_iterator Entries::end(void) const
{
  return this->entries.end();
}

/* **************************************************
 *
 ************************************************** */
void Entries::add(entryPtr  entry)
{
  this->entries.push_back(entry);
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Entries::toXML(xmlNodePtr nodeRoot) const
{
  xmlNodePtr node=xmlNewChild(nodeRoot, NULL, (const xmlChar*)"ENTRIES", NULL);
  for (std::list<entryPtr  >::const_iterator i=entries.begin();
       i!=entries.end();
       i++)
    (*i)->toXML(node);
}
#endif

/* **************************************************
 *
 ************************************************** */
void
Entries::print(std::ostream& out) const
{
  for (std::list<entryPtr  >::const_iterator i = entries.begin();
       i != entries.end();
       ++i)
    (*i)->print(out);
}
