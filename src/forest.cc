/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2020 LABRI, 
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

//#include <stdio.h>
#include <string.h>

#include <utility>

#include "forest.hpp"
#include "messages.hpp"
#include "entry.hpp"
#include "shared_ptr.hpp"
#include "node.hpp"

/* **************************************************
 *
 ************************************************** */
Forest::Forest(entryPtr entry, unsigned int from, unsigned int to) {
    this->entry = std::move(entry);
    this->from = from;
    this->to = to;
    if (from == to)
        this->empty = true;
    else
        this->empty = false;
    NEW
}

/* **************************************************
 *
 ************************************************** */
forestPtr Forest::create(entryPtr entry, unsigned int from, unsigned int to) {
    return forestPtr(new Forest(std::move(entry), from, to));
}

/* **************************************************
 *
 ************************************************** */
Forest::~Forest() {
    DELETE
    for (auto tmp : nodes) {
        if (tmp)
            tmp.reset();
    }
    if (entry)
        entry.reset();
}

/* **************************************************
 *
 ************************************************** */
const Forest::vectorNodes &Forest::getNodes() const {
    return nodes;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Forest::getFrom() const {
    return from;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Forest::getTo() const {
    return to;
}

/* **************************************************
 *
 ************************************************** */
bool Forest::isEmpty() const {
    return from == to;
}

/* **************************************************
 *
 ************************************************** */
const std::vector<std::string> &
Forest::getOutput() const {
    return this->output;
}

/* **************************************************
 *
 ************************************************** */
void Forest::addNode(const nodePtr& node) {
    empty = false;
    nodes.push_back(node);
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
    if (isUnsetFlags(Flags::GENERATED)) {
        addFlags(Flags::GENERATED);
        if (entry && !entry->getForm().empty()) {
            output.push_back(entry->getForm());
        } else if (!nodes.empty()) {
            auto nodeIt = nodes.begin();
            nodePtr node;
            if (random) {
                size_t rv = std::rand() / ((RAND_MAX + 1u) / nodes.size());
                node = nodes.at(rv);
            }
            while (nodeIt != nodes.end()) {
                if (!random)
                    node = *nodeIt;
                if (node->isUnsetFlags(Flags::GENERATED))
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
