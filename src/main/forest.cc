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

#include <string.h>
#include <utility>

#include "forest.hpp"
#include "messages.hpp"
#include "shared_ptr.hpp"
#include "node.hpp"
#include "generator.hpp"

std::string Forest::EMPTY_FORM = "";

/* **************************************************
 *
 ************************************************** */
Forest::Forest(uint32_t from, uint32_t to, std::string &form)
    : from(from), to(to), empty(from == to), form(form)
{
    NEW;
}

/* **************************************************
 *
 ************************************************** */
forestPtr Forest::create(uint32_t from, uint32_t to, std::string &form)
{
    return std::make_shared<Forest>(from, to, form);
}

/* **************************************************
 *
 ************************************************** */
Forest::~Forest()
{
    DELETE;
    // The vector automatically releases its shared node references.
}

/* **************************************************
 *
 ************************************************** */
uint32_t Forest::getFrom() const
{
    return from;
}

/* **************************************************
 *
 ************************************************** */
uint32_t Forest::getTo() const
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
/** Write the attributes of a fully serialized (non-reference) forest. */
void Forest::writeXmlAttributes(xmlNodePtr forestNode) const
{
    xmlSetProp(forestNode, (xmlChar *)"from", (xmlChar *)std::to_string(from).c_str());
    xmlSetProp(forestNode, (xmlChar *)"to", (xmlChar *)std::to_string(to).c_str());
    xmlSetProp(forestNode, (xmlChar *)"size", (xmlChar *)std::to_string(nodes.size()).c_str());
    xmlSetProp(forestNode, (xmlChar *)"empty", (xmlChar *)(empty ? "yes" : "no"));
}

/** Write the cached texts, or the legacy NONE marker if none exist. */
void Forest::writeXmlOutput(xmlNodePtr forestNode) const
{
    xmlNodePtr outputNode = xmlNewChild(forestNode, NULL, (const xmlChar *)"OUTPUT", NULL);
    if (output.empty())
    {
        xmlNewChild(outputNode, NULL, (const xmlChar *)"TEXT", (xmlChar *)"NONE");
        return;
    }
    for (const auto &text : output)
        xmlNewChild(outputNode, NULL, (const xmlChar *)"TEXT", (xmlChar *)text.c_str());
}

void Forest::toXML(xmlNodePtr nodeRoot, bool root)
{
    xmlNodePtr forestNode = xmlNewChild(nodeRoot, NULL, (const xmlChar *)"FOREST", NULL);
    if (root)
        xmlSetProp(forestNode, (xmlChar *)"root", (xmlChar *)"yes");

    // A forest may appear in several parent nodes; emit its body only once.
    if (isSetFlags(Flags::XML))
    {
        xmlSetProp(forestNode, (xmlChar *)"idref", (xmlChar *)getIdStr().c_str());
        return;
    }

    xmlSetProp(forestNode, (xmlChar *)"id", (xmlChar *)getIdStr().c_str());
    addFlags(Flags::XML);
    writeXmlAttributes(forestNode);
    writeXmlOutput(forestNode);

    // Keep alternatives at the document root, as in the existing XML format.
    for (const auto &node : nodes)
        node->toXML(nodeRoot, forestNode);
}
#endif

/** Preserve the historical push_front ordering of alternatives. */
void Forest::appendNodeOutputs(const nodePtr &node)
{
    for (auto text = node->output_cbegin(); text != node->output_cend(); ++text)
        output.push_front(*text);
}

/** Select and expand one alternative, or all of them, on demand. */
void Forest::generateAlternatives(Generator *generator, bool randomResult, bool singleResult)
{
    nodePtr randomNode;
    if (randomResult)
        randomNode = nodes.at(generator->randomIndex(nodes.size()));

    for (const auto &alternative : nodes)
    {
        const nodePtr &node = randomResult ? randomNode : alternative;
        if (node->isUnsetFlags(Flags::GENERATED))
            node->generate(generator, randomResult, singleResult);
        appendNodeOutputs(node);

        if (randomResult || singleResult)
            break;
    }
}

void Forest::generate(Generator *generator, bool randomResult, bool singleResult)
{
    if (isSetFlags(Flags::GENERATED))
        return;

    addFlags(Flags::GENERATED);
    if (!form.empty())
        output.push_front(form);
    else if (!nodes.empty())
        generateAlternatives(generator, randomResult, singleResult);
}
