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
Forest::Forest(entryPtr entry, unsigned int from, unsigned int to)
{
    NEW;
    this->entry = std::move(entry);
    this->from = from;
    this->to = to;
    if (from == to)
        this->empty = true;
    else
        this->empty = false;
}

/* **************************************************
 *
 ************************************************** */
forestPtr Forest::create(entryPtr entry, unsigned int from, unsigned int to)
{
    return forestPtr(new Forest(std::move(entry), from, to));
}

/* **************************************************
 *
 ************************************************** */
Forest::~Forest()
{
    DELETE;
    for (auto tmp : nodes)
    {
        if (tmp)
            tmp.reset();
    }
    if (entry)
        entry.reset();
}

/* **************************************************
 *
 ************************************************** */
unsigned int Forest::getFrom() const
{
    return from;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Forest::getTo() const
{
    return to;
}

/* **************************************************
 *
 ************************************************** */
bool Forest::isEmpty() const
{
    return from == to;
}

/* **************************************************
 *
 ************************************************** */
size_t Forest::output_size() const
{
    return this->output.size();
}

/* **************************************************
 *
 ************************************************** */
const std::vector<std::string>::const_iterator Forest::output_cbegin() const
{
    return this->output.cbegin();
}

/* **************************************************
 *
 ************************************************** */
const std::vector<std::string>::const_iterator Forest::output_cend() const
{
    return this->output.cend();
}

/* **************************************************
 *
 ************************************************** */
void Forest::push_back_node(const nodePtr &node)
{
    empty = false;
    nodes.push_back(node);
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void Forest::toXML(xmlNodePtr nodeRoot, bool root)
{
    xmlNodePtr f = xmlNewChild(nodeRoot, NULL, (const xmlChar *)"FOREST", NULL);
    if (root)
        xmlSetProp(f, (xmlChar *)"root", (xmlChar *)"yes");
    if (isSetFlags(Flags::XML))
    {
        xmlSetProp(f, (xmlChar *)"idref", (xmlChar *)(std::to_string(this->getId())).c_str());
    }
    else
    {
        xmlSetProp(f, (xmlChar *)"id", (xmlChar *)(std::to_string(this->getId())).c_str());
        addFlags(Flags::XML);
        xmlSetProp(f, (xmlChar *)"from", (xmlChar *)std::to_string(this->from).c_str());
        xmlSetProp(f, (xmlChar *)"to", (xmlChar *)std::to_string(this->to).c_str());
        xmlSetProp(f, (xmlChar *)"size", (xmlChar *)(std::to_string(nodes.size())).c_str());

        if (empty)
            xmlSetProp(f, (xmlChar *)"empty", (xmlChar *)"yes");
        else
            xmlSetProp(f, (xmlChar *)"empty", (xmlChar *)"no");

        //if (entry)
        //    entry->toXML(f);

        if (output.size() > 0)
        {
            xmlNodePtr o = xmlNewChild(f, NULL, (const xmlChar *)"OUTPUT", NULL);
            for (std::vector<std::string>::const_iterator s = output.begin(); s != output.end(); ++s)
                xmlNewChild(o, NULL, (const xmlChar *)"TEXT", (xmlChar *)(*s).c_str());
        }
        else {
            xmlNodePtr o = xmlNewChild(f, NULL, (const xmlChar *)"OUTPUT", NULL);
            xmlNewChild(o, NULL, (const xmlChar *)"TEXT", (xmlChar *)"NONE");
        
        }        
        for (Forest::vectorNodes::const_iterator n = nodes.begin(); n != nodes.end(); ++n)
        {
            (*n)->toXML(nodeRoot, f);
        }
    }
}
#endif

/* **************************************************
 *
 ************************************************** */
void Forest::generate(bool randomResult, bool singleResult)
{
    if (isUnsetFlags(Flags::GENERATED))
    {
        addFlags(Flags::GENERATED);
        if (entry && !entry->getForm().empty())
        {
            output.push_back(entry->getForm());
        }
        else if (!nodes.empty())
        {
            auto nodeIt = nodes.begin();
            nodePtr node;
            if (randomResult)
            {
                size_t rv = std::rand() / ((RAND_MAX + 1u) / nodes.size());
                node = nodes.at(rv);
            }
            while (nodeIt != nodes.end())
            {
                if (!randomResult)
                    node = *nodeIt;
                if (node->isUnsetFlags(Flags::GENERATED)){
                    node->generate(randomResult, singleResult);
                }
                for (std::vector<std::string>::const_iterator s = node->output_cbegin(); s != node->output_cend(); ++s)
                    {
                        //std::cerr << *s << std::endl;
                        output.push_back(*s);
                    }
                if (randomResult || singleResult)
                    break;
                ++nodeIt;
            }
        }
    }
}
