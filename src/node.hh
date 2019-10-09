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

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <list>
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "flags.hh"
#include "id.hh"
#include "ipointer.hh"

class Node: 
  public Flags,
  public Id,
  public std::enable_shared_from_this<class Node> {

  //public:
  //typedef std::vector< forestPtr > vectorForests;
  
private:
  unsigned int nbrCS;
  std::vector< forestPtr > forests;
  std::vector< std::string > output;
  
  Node(void);
  void generate(std::vector< forestPtr >::const_iterator);

public:
  ~Node();
  static nodePtr create(void);

  std::vector< forestPtr > &getForests(void);
  const std::vector<std::string> &getOutput(void) const;
  
  void addForest(forestPtr);
  forestPtr getForest(unsigned int) const;
  
#ifdef OUTPUT_XML
  void toXML(const xmlNodePtr, const xmlNodePtr) const;
#endif
  void generate(bool);

  // compare deux nodes
  //struct less {
  //bool operator() (nodePtr, nodePtr) const;
  //};

};

#endif // NODE_H
 
