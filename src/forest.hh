/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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

#ifndef FOREST_H
#define FOREST_H

#include <set>

#include "id.hh"
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif
#include "flags.hh"
#include "node.hh"
#include "ipointer.hh"
#include "synthesizer.hh"

class Forest: public Id,
	      public Flags,
	      public enable_shared_from_this< class Forest > {

public:
  typedef std::set<nodePtr, Node::Less> setNodes;

private:
  unsigned int from;
  unsigned int to;
  setNodes nodes;
  bool empty;
  entryPtr entry;
  std::vector<std::string> output;
  Forest (entryPtr entry, unsigned int from, unsigned int to);
  void setId(idType);

public:
  ~Forest();
  static forestPtr create(entryPtr entry, unsigned int from, unsigned int to);

  setNodes &getNodes(void);
  unsigned int getFrom(void) const;
  unsigned int getTo(void) const;
  bool isEmpty(void) const;
  
  std::vector<std::string> &getOutput(void);
  
  bool addNode(nodePtr);
#ifdef OUTPUT_XML
  void toXML(const xmlNodePtr, bool);
#endif
  
  void generate(bool);
  //void generate(void);

};
#endif // FOREST_H
