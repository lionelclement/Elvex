/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2023 LABRI,
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

#include <algorithm>
#include <vector>
#include "node.hpp"
#include "messages.hpp"
#include "forest.hpp"

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::Node(bool withSpace, bool bidirectional, bool permutable)
{
   NEW;
   this->withSpace = withSpace;
   this->bidirectional = bidirectional;
   this->permutable = permutable;
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
nodePtr Node::create(bool withSpace, bool bidirectional, bool permutable)
{
   return nodePtr(new Node(withSpace, bidirectional, permutable));
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
const std::vector<std::string>::const_iterator Node::output_cbegin(void) const
{
   return this->output.cbegin();
}

/* **************************************************
 *
 ************************************************** */
const std::vector<std::string>::const_iterator Node::output_cend(void) const
{
   return this->output.cend();
}

/* **************************************************
 *
 ************************************************** */
bool Node::getWithSpace() const
{
   return this->withSpace;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void Node::toXML(xmlNodePtr nodeRoot, xmlNodePtr nodeFather) const
{
   xmlNodePtr node = xmlNewChild(nodeFather, nullptr, (const xmlChar *)"NODE", nullptr);
   xmlSetProp(node, (xmlChar *)"id", (xmlChar *)(std::to_string(this->getId())).c_str());
   for (const auto &forest : forests)
   {
      if (forest->isUnsetFlags(Flags::XML))
         forest->toXML(nodeRoot, false);
      xmlNodePtr forestNode = xmlNewChild(node, nullptr, (const xmlChar *)"SON", nullptr);
      xmlSetProp(forestNode, (xmlChar *)"from", (xmlChar *)std::to_string(forest->getFrom()).c_str());
      xmlSetProp(forestNode, (xmlChar *)"to", (xmlChar *)std::to_string(forest->getTo()).c_str());
      xmlSetProp(forestNode, (xmlChar *)"idref", (xmlChar *)(std::to_string(forest->getId())).c_str());
   }
   if (!output.empty())
   {
      xmlNodePtr o = xmlNewChild(node, nullptr, (const xmlChar *)"OUTPUT", nullptr);
      for (const auto &s : output)
      {
         xmlNewChild(o, nullptr, (const xmlChar *)"TEXT", (xmlChar *)s.c_str());
      }
   }
}

#endif

/* **************************************************
 * Algorithm to Rewrite
 ************************************************** */
void Node::generateLR()
{
   std::vector<std::string> list;
   for (const auto &forestIt : forests)
   {
      if (forestIt->output_size() > 0)
      {
         if (list.empty())
         {
            for (auto s = forestIt->output_cbegin(); s != forestIt->output_cend(); ++s)
            {
               list.push_back(*s);
            }
         }
         else
         {
            for (auto o = list.begin(); o != list.end(); ++o)
            {
               for (auto s = forestIt->output_cbegin(); s != forestIt->output_cend(); ++s)
               {
                  if (!o->empty() && !s->empty())
                  {
                     *o += ' ' + *s;
                  }
                  else if (!s->empty())
                  {
                     *o = *s;
                  }
               }
            }
         }
      }
   }
   for (auto &o : list)
   {
      output.push_back(o);
   }
}

/* **************************************************
 * Algorithm to Rewrite
 ************************************************** */
void Node::generateRL()
{
   std::vector<std::string> list;
   for (auto forest = forests.end() - 1; forest >= forests.begin(); forest = forest - 1)
   {
      if ((*forest)->output_size() > 0)
      {
         if (list.empty())
         {
            for (auto s = (*forest)->output_cbegin(); s != (*forest)->output_cend(); ++s)
            {
               list.push_back(*s);
            }
         }
         else
         {
            for (auto o = list.begin(); o != list.end(); ++o)
            {
               for (auto s = (*forest)->output_cbegin(); s != (*forest)->output_cend(); ++s)
               {
                  if (!o->empty() && !s->empty())
                  {
                     *o += ' ' + *s;
                  }
                  else if (!s->empty())
                  {
                     *o = *s;
                  }
               }
            }
         }
      }
   }
   for (auto &o : list)
   {
      output.push_back(o);
   }
}

/* **************************************************
 * Algorithm to Rewrite
 ************************************************** */
void Node::generateOutputPermutations(std::string base, vectorForests::const_iterator forestIterator)
{
   if (forestIterator == forests.cend())
   {
      output.push_back(base);
   }
   else
   {
      if ((*forestIterator)->output_size())
      {
         for (auto s = (*forestIterator)->output_cbegin(); s != (*forestIterator)->output_cend(); ++s)
         {
            if ((forestIterator != cbegin()) && base.size())
            {
               if (withSpace)
                  generateOutputPermutations(base + ' ' + *s, forestIterator + 1);
               else
                  generateOutputPermutations(base + *s, forestIterator + 1);
            }
            else
            {
               generateOutputPermutations(*s, forestIterator + 1);
            }
         }
      }
      else
      {
         generateOutputPermutations(base, forestIterator + 1);
      }
   }
}

/* **************************************************
 *
 ************************************************** */
void Node::generatePermutations(Node::vectorForests &forests, int start, int end)
{
   if (start == end)
   {
      generateOutputPermutations(std::string(), forests.cbegin());
   }
   else
   {
      for (int i = start; i <= end; i++)
      {
         std::swap(forests[start], forests[i]);
         generatePermutations(forests, start + 1, end);
         std::swap(forests[start], forests[i]);
      }
   }
}

/* **************************************************
 *
 ************************************************** */
void Node::generate(bool randomResult, bool singleResult)
{
   if (isUnsetFlags(Flags::GENERATED))
   {
      addFlags(Flags::GENERATED);
      if (!forests.empty())
      {
         for (vectorForests::const_iterator forest = cbegin(); forest != cend(); ++forest)
            if ((*forest)->isUnsetFlags(Flags::GENERATED))
               (*forest)->generate(randomResult, singleResult);
      }
      if (permutable)
      {
         WARNING("@permutable Not yet implemented");
         generatePermutations(forests, 0, forests.size() - 1);
      }
      else if (bidirectional)
      {
         WARNING("@bidirectional Not yet implemented");
         generateLR();
         generateRL();
      }
      else
      {
         generateLR();
      }
   }
}
