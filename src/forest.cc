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

#include <string.h>
#include <utility>

#include "forest.hpp"
#include "messages.hpp"
#include "terminal.hpp"
#include "shared_ptr.hpp"
#include "node.hpp"

std::string Forest::EMPTY_FORM = "";

/* **************************************************
 *
 ************************************************** */
Forest::Forest(uint8_t from, uint8_t to, std::string &form)
{
    NEW;
    this->from = from;
    this->to = to;
    if (from == to)
        this->empty = true;
    else
        this->empty = false;
    this->form = form;
}

/* **************************************************
 *
 ************************************************** */
forestPtr Forest::create(uint8_t from, uint8_t to, std::string &form)
{
    return forestPtr(new Forest(from, to, form));
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
}

/* **************************************************
 *
 ************************************************** */
uint8_t Forest::getFrom() const
{
    return from;
}

/* **************************************************
 *
 ************************************************** */
uint8_t Forest::getTo() const
{
    return to;
}

/* **************************************************
 *
 ************************************************** */
bool Forest::output_empty() const
{
    return output.empty();
}

/* **************************************************
 *
 ************************************************** */
const std::forward_list<std::string>::const_iterator Forest::output_cbegin() const
{
    return output.cbegin();
}

/* **************************************************
 *
 ************************************************** */
const std::forward_list<std::string>::const_iterator Forest::output_cend() const
{
    return output.cend();
}

/* **************************************************
 *
 ************************************************** */
void Forest::push_output(std::string str)
{
    output.push_front(str);
}

/* **************************************************
 *
 ************************************************** */
void Forest::push_node(const nodePtr &node)
{
    empty = false;
    nodes.push_back(node);
}

/* **************************************************
 *
 ************************************************** */
std::string &Forest::getForm(void)
{
    return form;
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
        xmlSetProp(f, (xmlChar *)"idref", (xmlChar *)(this->getIdStr()).c_str());
    }
    else
    {
        xmlSetProp(f, (xmlChar *)"id", (xmlChar *)(this->getIdStr()).c_str());
        addFlags(Flags::XML);
        xmlSetProp(f, (xmlChar *)"from", (xmlChar *)std::to_string(this->from).c_str());
        xmlSetProp(f, (xmlChar *)"to", (xmlChar *)std::to_string(this->to).c_str());
        xmlSetProp(f, (xmlChar *)"size", (xmlChar *)(std::to_string(nodes.size())).c_str());

        if (empty)
            xmlSetProp(f, (xmlChar *)"empty", (xmlChar *)"yes");
        else
            xmlSetProp(f, (xmlChar *)"empty", (xmlChar *)"no");

        // if (terminal)
        //     terminal->toXML(f);
        // if (entry)
        //     entry->toXML(f);

        if (!output.empty())
        {
            xmlNodePtr o = xmlNewChild(f, NULL, (const xmlChar *)"OUTPUT", NULL);
            for (const auto &s : output)
                xmlNewChild(o, NULL, (const xmlChar *)"TEXT", (xmlChar *)(s.c_str()));
        }
        else
        {
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
        if (!form.empty())
        {
            output.push_front(form);
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
                if (node->isUnsetFlags(Flags::GENERATED))
                {
                    node->generate(randomResult, singleResult);
                }
                for (std::forward_list<std::string>::const_iterator s = node->output_cbegin(); s != node->output_cend(); ++s)
                {
                    output.push_front(*s);
                }
                if (randomResult || singleResult)
                    break;
                ++nodeIt;
            }
        }
    }
}
