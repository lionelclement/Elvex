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

#ifndef ENTRIES_H
#define ENTRIES_H

#include <list>
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif
#include "ipointer.hh"

class Entries:
  public enable_shared_from_this< class Entries > {

private:
  std::list<entryPtr> entries;

  Entries();
  Entries(entryPtr );
  Entries(std::list<entryPtr >&);
  Entries(int codePos, int codeLemma, std::string form);

public:
  ~Entries();
  static entriesPtr create();
  static entriesPtr create(entryPtr );
  static entriesPtr create(std::list<entryPtr >&);
  static entriesPtr create(int codePos, int codeLemma, std::string form);

  const size_t size() const;
  std::list<entryPtr >::const_iterator begin() const;
  std::list<entryPtr >::const_iterator end() const;

  void add(const entryPtr);
#ifdef OUTPUT_XML
  void toXML(const xmlNodePtr) const;
#endif
  void print(std::ostream &) const;
};

#endif // ENTRIES_H
