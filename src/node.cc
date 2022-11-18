/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI,
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI -- Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#include "node.hpp"
#include "messages.hpp"
#include "forest.hpp"

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::Node()
{
   NEW;
   this->nbrCS = 0;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::~Node()
{
   DELETE;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
nodePtr Node::create()
{
   return nodePtr(new Node());
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool Node::empty() const
{
   return forests.empty();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::vectorForests_iterator Node::begin()
{
   return forests.begin();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::vectorForests_iterator Node::end()
{
   return forests.end();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::vectorForests_const_iterator Node::cbegin() const
{
   return forests.cbegin();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::vectorForests_const_iterator Node::cend() const
{
   return forests.cend();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
size_t Node::size() const
{
   return forests.size();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
forestPtr Node::at(size_t index)
{
   return forests.at(index);
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Node::push_back(const forestPtr &forestPtr)
{
   forests.push_back(forestPtr);
}

/* **************************************************
 *
 ************************************************** */
const std::vector<std::string> &Node::getOutput() const
{
   return this->output;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void Node::toXML(xmlNodePtr nodeRoot, xmlNodePtr nodeFather) const
{
   xmlNodePtr node = xmlNewChild(nodeFather, nullptr, (const xmlChar *)"NODE", nullptr);
   xmlSetProp(node, (xmlChar *)"id", (xmlChar *)(std::to_string(this->getId())).c_str());
   for (const auto &s : forests)
   {
      if (s->isUnsetFlags(Flags::XML))
         s->toXML(nodeRoot, false);
      xmlNodePtr forest = xmlNewChild(node, nullptr, (const xmlChar *)"SON", nullptr);
      xmlSetProp(forest, (xmlChar *)"from", (xmlChar *)std::to_string(s->getFrom()).c_str());
      xmlSetProp(forest, (xmlChar *)"to", (xmlChar *)std::to_string(s->getTo()).c_str());
      xmlSetProp(forest, (xmlChar *)"idref", (xmlChar *)(std::to_string(s->getId())).c_str());
   }
   if (!output.empty())
   {
      xmlNodePtr o = xmlNewChild(node, nullptr, (const xmlChar *)"OUTPUT", nullptr);
      for (const auto &s : output)
         xmlNewChild(o, nullptr, (const xmlChar *)"S", (xmlChar *)s.c_str());
   }
}

#endif

/* **************************************************
 *
 ************************************************** */
void Node::generate(vectorForests::const_iterator forest)
{
   if ((*forest)->getOutput_size() > 0)
   {
      for (auto s = (*forest)->getOutput_cbegin(); s != (*forest)->getOutput_cend(); ++s)
      {
         if (output.size() == 0)
         {
            output.push_back(*s);
         }
         else
         {
            for (auto o = output.begin(); o != output.end(); ++o)
            {
               if (o->size() != 0 && s->size() != 0)
               {
                  *o += ' ' + *s;
               }
               else if (s->size() != 0)
               {
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
void Node::generate(bool random, bool one)
{
   if (isUnsetFlags(Flags::GENERATED))
   {
      addFlags(Flags::GENERATED);
      for (vectorForests::const_iterator forestIterator = forests.cbegin(); forestIterator != forests.cend(); ++forestIterator)
      {
         if ((*forestIterator)->isUnsetFlags(Flags::GENERATED))
            (*forestIterator)->generate(random, one);
      }
      if (!forests.empty())
         generate(forests.begin());
   }
}
