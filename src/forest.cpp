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

#include <stdio.h>
#include <string.h>

#include "forest.h"
#include "messages.h"
#include "entry.h"
#include "shared_ptr.h"
#include "node.h"

/* **************************************************
 *
 ************************************************** */
Forest::Forest(entryPtr entry, unsigned int from, unsigned int to)
      : Id(0) {
   this->entry = entry;
   this->from = from;
   this->to = to;
   if (from == to)
      this->empty = true;
   else
      this->empty = false;
   NEW;
}

/* **************************************************
 *
 ************************************************** */
forestPtr Forest::create(entryPtr entry, unsigned int from, unsigned int to) {
   return forestPtr(new Forest(entry, from, to));
}

/* **************************************************
 *
 ************************************************** */
Forest::~Forest() {
   DELETE;
   for (vectorNodes::iterator n = nodes.begin(); n != nodes.end(); ++n) {
      nodePtr tmp = *n;
      if (tmp)
         tmp.reset();
   }
   if (entry)
      entry.reset();
}

/* **************************************************
 *
 ************************************************** */
const Forest::vectorNodes &Forest::getNodes(void) const {
   return nodes;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Forest::getFrom(void) const {
   return from;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Forest::getTo(void) const {
   return to;
}

/* **************************************************
 *
 ************************************************** */
bool Forest::isEmpty(void) const {
   return from == to;
}

/* **************************************************
 *
 ************************************************** */
const std::vector<std::string> &
Forest::getOutput(void) const {
   return this->output;
}

/* **************************************************
 *
 ************************************************** */
void Forest::addNode(nodePtr n) {
   empty = false;
   nodes.push_back(n);
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
   if (isSetFlags(Flags::XML)) {
      xmlSetProp(f, (xmlChar*)"idref", (xmlChar*)(std::to_string(this->getId())).c_str());
   }
   else {
      xmlSetProp(f, (xmlChar*)"id", (xmlChar*)(std::to_string(this->getId())).c_str());
      addFlags(Flags::XML);
      xmlSetProp(f, (xmlChar*)"from", (xmlChar*)std::to_string(this->from).c_str());
      xmlSetProp(f, (xmlChar*)"to", (xmlChar*)std::to_string(this->to).c_str());
      xmlSetProp(f, (xmlChar*)"size", (xmlChar*)(std::to_string(nodes.size())).c_str());

      if (empty)
      xmlSetProp(f, (xmlChar*)"empty", (xmlChar*)"yes");
      else
      xmlSetProp(f, (xmlChar*)"empty", (xmlChar*)"no");

      if (entry)
      entry->toXML(f);

      if (output.size()>0) {
         xmlNodePtr o=xmlNewChild(f, NULL, (const xmlChar*)"OUTPUT", NULL);
         for(std::vector<std::string>::const_iterator s=output.begin(); s!=output.end(); ++s)
         xmlNewChild(o, NULL, (const xmlChar*)"S", (xmlChar*)(*s).c_str());
      }
      for(Forest::vectorNodes::const_iterator n=nodes.begin(); n!=nodes.end(); ++n) {
         (*n)->toXML(nodeRoot, f);
      }
   }
}
#endif

/* **************************************************
 *
 ************************************************** */
void Forest::generate(bool random, bool one) {
   if (isUnsetFlags(Flags::GEN)) {
      addFlags(Flags::GEN);
      if (entry && entry->getForm().size() != 0) {
         output.push_back(entry->getForm());
      }
      else if (nodes.size() != 0) {
         Forest::vectorNodes::const_iterator nodeIt = nodes.begin();
         nodePtr node;
         if (random) {
            size_t rv = std::rand() / ((RAND_MAX + 1u) / nodes.size());
            node = nodes.at(rv);
         }
         while (nodeIt != nodes.end()) {
            if (!random)
               node = *nodeIt;
            if (node->isUnsetFlags(Flags::GEN))
	      node->generate(random, one);
            for (std::vector<std::string>::const_iterator s = node->getOutput().begin(); s != node->getOutput().end(); ++s)
               output.push_back(*s);
            if (random || one)
               break;
            ++nodeIt;
         }
      }
   }
}

