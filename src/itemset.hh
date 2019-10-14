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

#ifndef ITEMSET_H
#define ITEMSET_H

#include <set>
#include <unordered_set>
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif
#include "item.hh"
#include "ipointer.hh"

class ItemSet:
  public std::enable_shared_from_this< class ItemSet > {

public:
  typedef std::unordered_set<itemPtr, Item::hash, Item::equal_to > set;
  typedef std::unordered_set<itemPtr, Item::hash, Item::equal_to >::const_iterator const_iterator;
  typedef std::unordered_set<itemPtr, Item::hash, Item::equal_to >::iterator iterator;

private:
  unsigned int id;
  set items;
  ItemSet (unsigned int);
  
public:
  ~ItemSet();
  static itemSetPtr create(unsigned int);
  
  unsigned int getId(void);
  set &getItems(void);
  
  const_iterator begin(void) const;
  const_iterator end(void) const;
  const_iterator find(itemPtr) const;
  bool insert(itemPtr, class Synthesizer *);
  void erase(itemPtr);
  size_t size(void) const;
  void resetUsages(void);
  
  void print(std::ostream &);
#ifdef OUTPUT_XML
  void toXML(xmlNodePtr);
#endif
  
};
#endif // ITEM_H
