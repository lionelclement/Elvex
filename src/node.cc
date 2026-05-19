/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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
#include <functional>

#include "node.hpp"
#include "messages.hpp"
#include "forest.hpp"

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::Node(bool withSpaces, bool unordered)
{
   NEW;
   this->withSpaces = withSpaces;
   this->unordered = unordered;
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
nodePtr Node::create(bool withSpaces, bool unordered)
{
   return std::make_shared<Node>(withSpaces, unordered);
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
Node::vectorForests::iterator Node::begin()
{
   return forests.begin();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::vectorForests::iterator Node::end()
{
   return forests.end();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::vectorForests::const_iterator Node::cbegin() const
{
   return forests.cbegin();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Node::vectorForests::const_iterator Node::cend() const
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

/* **************************************************
 *
 ************************************************** */
void Node::push_back(const forestPtr &forestPtr)
{
   push_back(static_cast<uint32_t>(forests.size()), forestPtr);
}

/* **************************************************
 *
 ************************************************** */
void Node::push_back(uint32_t rhsIndex, const forestPtr &forestPtr)
{
   forests.push_back(forestPtr);
   rhsIndexes.push_back(rhsIndex);
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
   return this->withSpaces;
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
#include "rule.hpp"

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Node::generateLR(std::string &currentCombination, const vectorForests &forestsToGenerate)
{
   if (forestsToGenerate.empty())
   {
      output.push_front(currentCombination);
      return;
   }

   std::stack<std::pair<std::string, size_t>> stack;
   stack.push({currentCombination, 0});

   while (!stack.empty())
   {
      currentCombination = stack.top().first;
      size_t forestIndex = stack.top().second;
      stack.pop();

      const forestPtr &forest = forestsToGenerate.at(forestIndex);
      bool last = (forestIndex + 1 == forestsToGenerate.size());

      if (!forest->output_empty())
      {
         for (std::forward_list<std::string>::const_iterator item = forest->output_cbegin();
              item != forest->output_cend();
              ++item)
         {
            std::string nextCombination;

            if (withSpaces && !currentCombination.empty())
               nextCombination = currentCombination + ' ' + *item;
            else
               nextCombination = currentCombination + *item;

            if (last)
               output.push_front(nextCombination);
            else
               stack.push({nextCombination, forestIndex + 1});
         }
      }
      else
      {
         if (last)
            output.push_front(currentCombination);
         else
            stack.push({currentCombination, forestIndex + 1});
      }
   }
}

/* **************************************************
 *
 ************************************************** */
void Node::generatePermutations(Node::vectorForests &forestsToGenerate, int start, int end)
{
   if (start >= end)
   {
      std::string currentCombination = "";
      generateLR(currentCombination, forestsToGenerate);
   }
   else
   {
      for (int i = start; i <= end; ++i)
      {
         std::swap(forestsToGenerate[start], forestsToGenerate[i]);
         generatePermutations(forestsToGenerate, start + 1, end);
         std::swap(forestsToGenerate[start], forestsToGenerate[i]);
      }
   }
}

/* **************************************************
 *
 ************************************************** */
void Node::generateWithOrder(const std::vector<size_t> &order)
{
   vectorForests orderedForests;

   for (auto childPosition : order)
   {
      orderedForests.push_back(forests.at(childPosition));
   }

   std::string currentCombination = "";
   generateLR(currentCombination, orderedForests);
}

/* **************************************************
 * TO do: remove empty forests
 ************************************************** */
void Node::generate(class Generator *generator, bool randomResult, bool singleResult)
{
   if (isUnsetFlags(Flags::GENERATED))
   {
      addFlags(Flags::GENERATED);
      if (!forests.empty())
      {
         for (vectorForests::const_iterator forest = cbegin(); forest != cend(); ++forest)
            if ((*forest)->isUnsetFlags(Flags::GENERATED))
            {
               (*forest)->generate(generator, randomResult, singleResult);
            }
      }
      if (!orderSpecs.empty() && unordered)
      {
         FATAL_ERROR("A node cannot be both unordered and constrained by order");
      }

      else if (!orderSpecs.empty())
      {
         std::vector<std::vector<size_t>> orders = computeTopologicalOrders();

         if (orders.empty())
         {
            FATAL_ERROR("cyclic order constraints");
         }

         for (const auto &order : orders)
         {
            generateWithOrder(order);
         }
      }
      else if (unordered)
      {
         vectorForests forestsToGenerate = forests;
         generatePermutations(forestsToGenerate, 0, static_cast<int>(forestsToGenerate.size()) - 1);
      }
      else
      {
         std::string currentCombination = "";
         generateLR(currentCombination, forests);
      }
   }
}

/* **************************************************
 *
 ************************************************** */
uint32_t Node::rhsIndexAt(size_t index) const
{
   return rhsIndexes.at(index);
}

/* **************************************************
 *
 ************************************************** */
void Node::setOrderSpecs(const vectorOrderSpecs &_orderSpecs)
{
   orderSpecs = _orderSpecs;
}

/* **************************************************
 *
 ************************************************** */
const vectorOrderSpecs &Node::getOrderSpecs() const
{
   return orderSpecs;
}

/* **************************************************
 *
 ************************************************** */
const std::vector<uint32_t> &Node::getRhsIndexes() const
{
   return rhsIndexes;
}

/* **************************************************
 *
 ************************************************** */
std::vector<std::vector<size_t>> Node::computeTopologicalOrders() const
{
   std::vector<std::vector<size_t>> result;

   const size_t n = forests.size();

   if (n == 0)
   {
      result.push_back(std::vector<size_t>());
      return result;
   }

   std::vector<std::vector<bool>> edge(n, std::vector<bool>(n, false));

   auto findChildPosition = [&](uint32_t rhsIndex) -> int
   {
      for (size_t i = 0; i < rhsIndexes.size(); ++i)
      {
         if (rhsIndexes[i] == rhsIndex)
            return static_cast<int>(i);
      }
      return -1;
   };

   auto addEdge = [&](size_t before, size_t after)
   {
      if (before != after)
         edge[before][after] = true;
   };

   for (const auto &spec : orderSpecs)
   {
      if (spec.kind == OrderSpec::CHAIN)
      {
         std::vector<size_t> projected;

         for (auto rhsIndex : spec.indexes)
         {
            int childPosition = findChildPosition(rhsIndex);
            if (childPosition >= 0)
               projected.push_back(static_cast<size_t>(childPosition));
         }

         for (size_t i = 0; i + 1 < projected.size(); ++i)
         {
            addEdge(projected[i], projected[i + 1]);
         }
      }
      else if (spec.kind == OrderSpec::FIRST)
      {
         if (spec.indexes.empty())
            continue;

         int childPosition = findChildPosition(spec.indexes[0]);

         if (childPosition >= 0)
         {
            for (size_t i = 0; i < n; ++i)
            {
               if (i != static_cast<size_t>(childPosition))
                  addEdge(static_cast<size_t>(childPosition), i);
            }
         }
      }
      else if (spec.kind == OrderSpec::LAST)
      {
         if (spec.indexes.empty())
            continue;

         int childPosition = findChildPosition(spec.indexes[0]);

         if (childPosition >= 0)
         {
            for (size_t i = 0; i < n; ++i)
            {
               if (i != static_cast<size_t>(childPosition))
                  addEdge(i, static_cast<size_t>(childPosition));
            }
         }
      }
   }

   std::vector<int> indegree(n, 0);

   for (size_t i = 0; i < n; ++i)
   {
      for (size_t j = 0; j < n; ++j)
      {
         if (edge[i][j])
            ++indegree[j];
      }
   }

   std::vector<bool> used(n, false);
   std::vector<size_t> current;

   std::function<void()> visit = [&]()
   {
      if (current.size() == n)
      {
         result.push_back(current);
         return;
      }

      bool found = false;

      for (size_t i = 0; i < n; ++i)
      {
         if (!used[i] && indegree[i] == 0)
         {
            found = true;

            used[i] = true;
            current.push_back(i);

            for (size_t j = 0; j < n; ++j)
            {
               if (edge[i][j])
                  --indegree[j];
            }

            visit();

            for (size_t j = 0; j < n; ++j)
            {
               if (edge[i][j])
                  ++indegree[j];
            }

            current.pop_back();
            used[i] = false;
         }
      }

      /*
       * No available node while the order is incomplete:
       * this means there is a cycle.
       */
      if (!found && current.size() < n)
      {
         return;
      }
   };

   visit();

   return result;
}