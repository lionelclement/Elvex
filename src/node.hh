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
  public enable_shared_from_this<class Node> {

public:
  typedef std::vector<forestPtr> vectorForests;
  
private:
  int nbrCS;
  vectorForests forests;
  std::vector<std::string> output;
  
  Node(void);
  void setId(idType);
  void generate(vectorForests::const_iterator);

public:
  ~Node();
  static nodePtr create(void);

  vectorForests &getForests(void);
  std::vector<std::string> &getOutput(void);
  
  void addForest(forestPtr);
  forestPtr getForest(unsigned int) const;
  
#ifdef OUTPUT_XML
  void toXML(const xmlNodePtr, const xmlNodePtr);
#endif
  void generate(bool);

  // compare deux items
  struct Less {
    bool operator() (nodePtr, nodePtr) const;
  };

};

#endif // NODE_H
 
