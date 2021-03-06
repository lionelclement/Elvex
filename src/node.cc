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

//#include <cstring>
//#include <cstdlib>
//#include <iostream>
//#include <ctime>
#include "node.hpp"
#include "messages.hpp"
#include "forest.hpp"

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::Node() {
    this->nbrCS = 0;
    NEW
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::~Node() {
    DELETE
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
nodePtr Node::create() {
    return nodePtr(new Node());
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
std::vector<forestPtr> &Node::getForests() {
    return forests;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Node::addForest(const forestPtr& forest) {
    forests.push_back(forest);
}

/* **************************************************
 *
 ************************************************** */
const std::vector<std::string> &
Node::getOutput() const {
    return this->output;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Node::toXML(xmlNodePtr nodeRoot, xmlNodePtr nodeFather) const
{
   xmlNodePtr node=xmlNewChild(nodeFather, nullptr, (const xmlChar*)"NODE", nullptr);
   xmlSetProp(node, (xmlChar*)"id", (xmlChar*)(std::to_string(this->getId())).c_str());
   for (const auto & s : forests) {
      if (s->isUnsetFlags(Flags::XML))
      s->toXML(nodeRoot, false);
      xmlNodePtr forest=xmlNewChild(node, nullptr, (const xmlChar*)"SON", nullptr);
      xmlSetProp(forest, (xmlChar*)"from", (xmlChar*)std::to_string(s->getFrom()).c_str());
      xmlSetProp(forest, (xmlChar*)"to", (xmlChar*)std::to_string(s->getTo()).c_str());
      xmlSetProp(forest, (xmlChar*)"idref", (xmlChar*)(std::to_string(s->getId())).c_str());
   }
   if (!output.empty()) {
      xmlNodePtr o=xmlNewChild(node, nullptr, (const xmlChar*)"OUTPUT", nullptr);
      for(const auto & s : output)
      xmlNewChild(o, nullptr, (const xmlChar*)"S", (xmlChar*)s.c_str());
   }
}

#endif

/* **************************************************
 *
 ************************************************** */
void Node::generate(std::vector<forestPtr>::const_iterator forest) {
   if ((*forest)->getOutput().size() > 0) {
      for (auto s = (*forest)->getOutput().begin(); s != (*forest)->getOutput().end(); ++s) {
         if (output.size() == 0) {
            output.push_back(*s);
         }
         else {
            for (auto o = output.begin(); o != output.end(); ++o) {
               if (o->size() != 0 && s->size() != 0) {
                  *o += ' ' + *s;
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
void Node::generate(bool random, bool one) {
   if (isUnsetFlags(Flags::GENERATED)) {
      addFlags(Flags::GENERATED);
      for (std::vector<forestPtr>::const_iterator forestIterator = forests.begin(); forestIterator != forests.end(); ++forestIterator) {
         if ((*forestIterator)->isUnsetFlags(Flags::GENERATED))
	   (*forestIterator)->generate(random, one);
      }
      if (!forests.empty())
	generate(forests.begin());
   }
}
