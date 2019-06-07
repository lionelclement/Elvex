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
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif
#include "item.hh"
#include "ipointer.hh"

class ItemSet:
  public enable_shared_from_this< class ItemSet > {

private:
  unsigned int id;
  std::set< itemPtr, Item::Less > items;
  
public:
  typedef std::set<itemPtr, Item::Less>::const_iterator const_iterator;
  typedef std::set<itemPtr, Item::Less>::iterator iterator;
  //
private:
  ItemSet (int);
  
public:
  ~ItemSet();
  static itemSetPtr create(unsigned int);
  
  unsigned int getId(void);
  std::set<itemPtr, Item::Less>& getItems(void);
  
  const_iterator begin(void) const;
  const_iterator end(void) const;
  const_iterator find(itemPtr) const;
  bool insert(itemPtr, class Synthesizer *);
  void erase(itemPtr);
  unsigned int size(void) const;
  void resetUsages(void);
  
  void print(std::ostream &);
#ifdef OUTPUT_XML
  void toXML(xmlNodePtr);
#endif
  
};
#endif // ITEM_H
