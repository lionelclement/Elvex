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
 * LaBRI - Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#include <algorithm>
#include <vector>
#include <forward_list>
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
const std::forward_list<std::string>::const_iterator Node::output_cbegin(void) const
{
   return this->output.cbegin();
}

/* **************************************************
 *
 ************************************************** */
const std::forward_list<std::string>::const_iterator Node::output_cend(void) const
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
   xmlSetProp(node, (xmlChar *)"id", (xmlChar *)(this->getIdStr().c_str()));
   for (const auto &forest : forests)
   {
      if (forest->isUnsetFlags(Flags::XML))
         forest->toXML(nodeRoot, false);
      xmlNodePtr forestNode = xmlNewChild(node, nullptr, (const xmlChar *)"SON", nullptr);
      xmlSetProp(forestNode, (xmlChar *)"from", (xmlChar *)std::to_string(forest->getFrom()).c_str());
      xmlSetProp(forestNode, (xmlChar *)"to", (xmlChar *)std::to_string(forest->getTo()).c_str());
      xmlSetProp(forestNode, (xmlChar *)"idref", (xmlChar *)(forest->getIdStr().c_str()));
   }
   if (!output.empty())
   {
      xmlNodePtr o = xmlNewChild(node, nullptr, (const xmlChar *)"OUTPUT", nullptr);
      for (const auto &s : output)
      {
         xmlNewChild(o, nullptr, (const xmlChar *)"TEXT", (xmlChar *)(s.c_str()));
      }
   }
}
#endif

#include <stack>

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Node::generateLR(std::string &currentCombination, vectorForests::const_iterator forestIt)
{
   std::stack<std::pair<std::string, vectorForests::const_iterator>> stack;
   stack.push({currentCombination, forestIt});

   while (!stack.empty())
   {
      currentCombination = stack.top().first;
      forestIt = stack.top().second;
      stack.pop();

      if (!(*forestIt)->output_empty())
      {
         for (std::forward_list<std::string>::const_iterator item = (*forestIt)->output_cbegin(); item != (*forestIt)->output_cend(); ++item)
         {
            if (withSpace && !currentCombination.empty())
            {
               if (forestIt + 1 == cend())
                  output.push_front(currentCombination + ' ' + *item);
               else

                  stack.push({currentCombination + ' ' + *item, forestIt + 1});
            }
            else
            {
               if (forestIt + 1 == cend())
                  output.push_front(currentCombination + *item);
               else
                  stack.push({currentCombination + *item, forestIt + 1});
            }
         }
      }
      else
      {
         if (forestIt + 1 == cend())
            output.push_front(currentCombination);
         else
            stack.push({currentCombination, forestIt + 1});
      }
   }
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Node::generateRL(std::string currentCombination, vectorForests::const_iterator forestIt)
{
   std::stack<std::pair<std::string, vectorForests::const_iterator>> stack;
   stack.push({currentCombination, forestIt});

   while (!stack.empty())
   {
      currentCombination = stack.top().first;
      forestIt = stack.top().second;
      stack.pop();

      if (forestIt < cbegin())
      {
         output.push_front(currentCombination);
      }
      else
      {
         if (!(*forestIt)->output_empty())
         {
            for (std::forward_list<std::string>::const_iterator item = (*forestIt)->output_cbegin(); item != (*forestIt)->output_cend(); ++item)
            {
               if (withSpace && !currentCombination.empty())
               {
                  stack.push({currentCombination + ' ' + *item, forestIt - 1});
               }
               else
               {
                  stack.push({currentCombination + *item, forestIt - 1});
               }
            }
         }
         else
         {
            stack.push({currentCombination, forestIt - 1});
         }
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
      std::string currentCombination = "";
      generateLR(currentCombination, forests.cbegin());
   }
   else
   {
      for (int i = start; i <= end; ++i)
      {
         std::swap(forests[start], forests[i]);
         generatePermutations(forests, start + 1, end);
         std::swap(forests[start], forests[i]);
      }
   }
}

/* **************************************************
 * TO do: remove empty forests
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
         generatePermutations(forests, 0, forests.size() - 1);
      }
      else if (bidirectional)
      {
         std::string currentCombination = "";
         generateLR(currentCombination, forests.cbegin());
         currentCombination = "";
         generateRL(currentCombination, forests.cend() - 1);
      }
      else
      {
         std::string currentCombination = "";
         generateLR(currentCombination, forests.cbegin());
      }
   }
}
