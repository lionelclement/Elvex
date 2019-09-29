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

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "node.hh"
#include "messages.hh"
#include "forest.hh"

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::Node(void)
{
  NEW;
  this->nbrCS = 0;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::~Node()
{
  //DELETE;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
nodePtr Node::create(void)
{
  return nodePtr( new Node() );
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::vectorForests &Node::getForests(void)
{
  return forests;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void
Node::addForest(forestPtr forest)
{
  forests.push_back(forest);
}

/* **************************************************
 *
 ************************************************** */
const std::vector<std::string> &
Node::getOutput(void)  const
{
  return this->output;
}

/* **************************************************
 *
 ************************************************** */
bool
Node::Less::operator () (nodePtr n1, nodePtr n2) const
{
  if (n1->getForests().size() < n2->getForests().size())
    return true;
  if (n1->getForests().size() > n2->getForests().size())
    return false;
  
  vectorForests::const_iterator s1=n1->forests.begin();
  vectorForests::const_iterator s2=n2->forests.begin();
  while (s1 != n1->forests.end()){
    if (!*s1 || !*s2)
      FATAL_ERROR;
    if ((*s1)->getId() != (*s2)->getId())
      return (*s1)->getId() < (*s2)->getId();
    s1++; s2++;

  }
  return false;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Node::toXML(xmlNodePtr nodeRoot, xmlNodePtr nodeFather) const
{
  xmlNodePtr node=xmlNewChild(nodeFather, NULL, (const xmlChar*)"NODE", NULL);
  xmlSetProp(node, (xmlChar*)"id", (xmlChar*)(std::to_string(this->getId())).c_str());
  for (vectorForests::const_iterator s=forests.begin() ;
       s!=forests.end() ;
       ++s){
    if ((*s)->isUnsetFlags(Flags::XML))
      (*s)->toXML(nodeRoot, false);
    xmlNodePtr forest=xmlNewChild(node, NULL, (const xmlChar*)"SON", NULL);
    xmlSetProp(forest, (xmlChar*)"from", (xmlChar*)std::to_string((*s)->getFrom()).c_str());
    xmlSetProp(forest, (xmlChar*)"to", (xmlChar*)std::to_string((*s)->getTo()).c_str());
    xmlSetProp(forest, (xmlChar*)"idref", (xmlChar*)(std::to_string((*s)->getId())).c_str());
  }
  if (output.size()){
    xmlNodePtr o=xmlNewChild(node, NULL, (const xmlChar*)"OUTPUT", NULL);
    for(std::vector<std::string>::const_iterator s=output.begin() ; s!=output.end() ; ++s)
      xmlNewChild(o, NULL, (const xmlChar*)"S", (xmlChar*)(*s).c_str());
  }
}

#endif

/* **************************************************
 *
 ************************************************** */
void
Node::generate(vectorForests::const_iterator forest)
{
  if ((*forest)->getOutput().size() > 0) {
    for (std::vector<std::string>::const_iterator s = (*forest)->getOutput().begin(); s != (*forest)->getOutput().end(); ++s){
      if (output.size() == 0 ) {
	output.push_back(*s);
      }
      else {
	for (std::vector<std::string>::iterator o = output.begin(); o != output.end(); ++o){
	  if (o->size() != 0 && s->size() != 0) {
	    *o = *o + ' ' + *s;
	  }
	  else if (s->size() != 0) {
	    *o = *s;
	  }
	}
      }
    }
  }
  forest++;
  if (forest != forests.end())
    generate(forest);
}

/* **************************************************
 *
 ************************************************** */
void
Node::generate(bool random)
{
  if (isUnsetFlags(Flags::GEN)){
    addFlags(Flags::GEN);
    for (vectorForests::const_iterator forestIterator=forests.begin(); forestIterator!=forests.end(); ++forestIterator) {
      if ((*forestIterator)->isUnsetFlags(Flags::GEN))
	(*forestIterator)->generate(random);
    }
    if (forests.size() > 0)
      generate(forests.begin());
  }
}


