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

#include <stdio.h>
#include <string.h>

#include "forest.hh"
#include "messages.hh"
#include "entry.hh"
#include "ipointer.hh"
#include "node.hh"

/* **************************************************
 *
 ************************************************** */
Forest::Forest(entryPtr  entry, unsigned int from, unsigned int to)
{
  NEW;
  this->entry=entry;
  this->from=from;
  this->to=to;
  if (from==to)
    this->empty=true;
  else
    this->empty=false;
}

/* **************************************************
 *
 ************************************************** */
forestPtr Forest::create(entryPtr  entry, unsigned int from, unsigned int to)
{
  return forestPtr( new Forest(entry, from, to) );
}

/* **************************************************
 *
 ************************************************** */
Forest::~Forest()
{
  for(setNodes::iterator n=nodes.begin() ; n!=nodes.end() ; ++n) {
    nodePtr tmp = *n;
    if (tmp)
      tmp.reset();
  }
  if (entry)
    entry.reset();
  DELETE;
}

/* **************************************************
 *
 ************************************************** */
void Forest::setId(idType id)
{
  FATAL_ERROR;
}

/* **************************************************
 *
 ************************************************** */
Forest::setNodes &Forest::getNodes(void)
{
  return nodes;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Forest::getFrom(void) const
{
  return from;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Forest::getTo(void) const
{
  return to;
}

/* **************************************************
 *
 ************************************************** */
bool Forest::isEmpty(void) const
{
  return from == to;
}

/* **************************************************
 *
 ************************************************** */
std::vector<std::string> &
Forest::getOutput(void)
{
  return this->output;
}

/* **************************************************
 *
 ************************************************** */
bool
Forest::addNode(nodePtr n)
{
  std::pair<Forest::setNodes::iterator, bool> result = nodes.insert(n);
  empty=false;
  return result.second;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Forest::toXML(xmlNodePtr nodeRoot, bool root)
{
  xmlNodePtr f=xmlNewChild(nodeRoot, NULL, (const xmlChar*)"FOREST", NULL);
  if (root)
    xmlSetProp(f, (xmlChar*)"root", (xmlChar*)"yes");
  if (isSetFlags(Flags::XML)){
    xmlSetProp(f, (xmlChar*)"idref", (xmlChar*)(std::to_string(this->getId())).c_str());
  }
  else {
    xmlSetProp(f, (xmlChar*)"id", (xmlChar*)(std::to_string(this->getId())).c_str());
    addFlags(Flags::XML);
    xmlSetProp(f, (xmlChar*)"from", (xmlChar*)std::to_string(this->from).c_str());
    xmlSetProp(f, (xmlChar*)"to", (xmlChar*)std::to_string(this->to).c_str());
    xmlSetProp(f, (xmlChar*)"size", (xmlChar*)(std::to_string((unsigned int)nodes.size())).c_str());
    
    if (empty)
      xmlSetProp(f, (xmlChar*)"empty", (xmlChar*)"yes");
    else
      xmlSetProp(f, (xmlChar*)"empty", (xmlChar*)"no");
    
    if (entry)
      entry->toXML(f);
    
    if (output.size()>0){
      xmlNodePtr o=xmlNewChild(f, NULL, (const xmlChar*)"OUTPUT", NULL);
      for(std::vector<std::string>::const_iterator s=output.begin() ; s!=output.end() ; ++s)
	xmlNewChild(o, NULL, (const xmlChar*)"S", (xmlChar*)(*s).c_str());
    }
    for(Forest::setNodes::const_iterator n=nodes.begin() ; n!=nodes.end() ; ++n){
      (*n)->toXML(nodeRoot, f);
    }
  }
}
#endif

/* **************************************************
 *
 ************************************************** */
void
Forest::generate(bool random)
{
  if (isUnsetFlags(Flags::GEN)){
    addFlags(Flags::GEN);
    if (entry && entry->getForm().size() != 0) {
      output.push_back(entry->getForm());
    }
    else if (nodes.size() != 0) {
      Forest::setNodes::const_iterator n = nodes.begin() ;
      if (random) {
	int rv = std::rand()/((RAND_MAX + 1u)/nodes.size());
	int i = 0;
	while (i++ < rv)
	  ++n;
      }
      while (n != nodes.end()) {
	if ((*n)->isUnsetFlags(Flags::GEN))
	  (*n)->generate(random);
	for (std::vector<std::string>::const_iterator s = (*n)->getOutput().begin(); s != (*n)->getOutput().end(); ++s)
	  output.push_back(*s);
	if (random)
	  break;
	else
	++n;
      }
    }
  }
}

