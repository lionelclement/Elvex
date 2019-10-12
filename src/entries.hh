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

#ifndef ENTRIES_H
#define ENTRIES_H

#include <iostream>
#include <vector>
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif
#include "ipointer.hh"

class Entries:
  public std::enable_shared_from_this< class Entries > {

private:
  std::vector< entryPtr > entries;

  Entries();
  Entries(entryPtr);
  Entries(const std::vector< entryPtr >&);
  Entries(const int codePos, const int codeLemma, const std::string form);

public:
  ~Entries();
  static entriesPtr create();
  static entriesPtr create(entryPtr);
  static entriesPtr create(const std::vector<entryPtr> &);
  static entriesPtr create(int codePos, const int codeLemma, const std::string form);

  const size_t size() const;
  std::vector<entryPtr >::const_iterator begin() const;
  std::vector<entryPtr >::const_iterator end() const;
  entryPtr at(const size_t) const;

  void add(const entryPtr);
#ifdef OUTPUT_XML
  void toXML(xmlNodePtr) const;
#endif
  void print(std::ostream &) const;
};

#endif // ENTRIES_H
