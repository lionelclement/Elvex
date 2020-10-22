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

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "node.hpp"
#include "messages.hpp"
#include "forest.hpp"

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::Node()
        : Id(0) {
    this->nbrCS = 0;
    NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::~Node() {
    DELETE;
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
   xmlNodePtr node=xmlNewChild(nodeFather, NULL, (const xmlChar*)"NODE", NULL);
   xmlSetProp(node, (xmlChar*)"id", (xmlChar*)(std::to_string(this->getId())).c_str());
   for (std::vector< forestPtr >::const_iterator s=forests.begin();
         s!=forests.end();
         ++s) {
      if ((*s)->isUnsetFlags(Flags::XML))
      (*s)->toXML(nodeRoot, false);
      xmlNodePtr forest=xmlNewChild(node, NULL, (const xmlChar*)"SON", NULL);
      xmlSetProp(forest, (xmlChar*)"from", (xmlChar*)std::to_string((*s)->getFrom()).c_str());
      xmlSetProp(forest, (xmlChar*)"to", (xmlChar*)std::to_string((*s)->getTo()).c_str());
      xmlSetProp(forest, (xmlChar*)"idref", (xmlChar*)(std::to_string((*s)->getId())).c_str());
   }
   if (output.size()) {
      xmlNodePtr o=xmlNewChild(node, NULL, (const xmlChar*)"OUTPUT", NULL);
      for(std::vector<std::string>::const_iterator s = output.begin() ; s != output.end(); ++s)
      xmlNewChild(o, NULL, (const xmlChar*)"S", (xmlChar*)(*s).c_str());
   }
}

#endif

/* **************************************************
 *
 ************************************************** */
void Node::generate(std::vector<forestPtr>::const_iterator forest) {
    if (!(*forest)->getOutput().empty()) {
        for (const auto & s : (*forest)->getOutput()) {
            if (output.empty()) {
                output.push_back(s);
            } else {
                for (auto & o : output) {
                    if (!o.empty() && !s.empty()) {
                        o += ' ' + s;
                    } else if (!s.empty()) {
                        o = s;
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
    if (isUnsetFlags(Flags::GEN)) {
        addFlags(Flags::GEN);
        for (std::vector<forestPtr>::const_iterator forestIterator = forests.begin();
             forestIterator != forests.end(); ++forestIterator) {
            if ((*forestIterator)->isUnsetFlags(Flags::GEN))
                (*forestIterator)->generate(random, one);
        }
        if (!forests.empty())
            generate(forests.begin());
    }
}

