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

#include <sstream>
#include "itemset.hpp"
#include "messages.hpp"
#include "rule.hpp"
#include "generator.hpp"

/* **************************************************
 *
 ************************************************** */
ItemSet::ItemSet(unsigned int id)
{
    NEW;
    this->id = id;
}

/* **************************************************
 *
 ************************************************** */
ItemSet::~ItemSet()
{
    DELETE;
    for (auto tmp : items)
    {
        if (tmp)
            free(tmp);
    }
    items.clear();
}

/* **************************************************
 *
 ************************************************** */
class ItemSet *ItemSet::create(unsigned int id)
{
    return new ItemSet(id);
}

/* **************************************************
 *
 ************************************************** */
unsigned int ItemSet::getId(void)
{
    return id;
}

/* **************************************************
 *
 ************************************************** */
ItemSet::set_of_item &ItemSet::getItems()
{
    return items;
}

/* **************************************************
 *
 ************************************************** */
ItemSet::set_of_item_const_iterator ItemSet::cbegin() const
{
    return items.cbegin();
}

/* **************************************************
 *
 ************************************************** */
ItemSet::set_of_item_const_iterator ItemSet::cend() const
{
    return items.cend();
}

/* **************************************************
 *
 ************************************************** */
ItemSet::set_of_item_iterator ItemSet::begin()
{
    return items.begin();
}

/* **************************************************
 *
 ************************************************** */
ItemSet::set_of_item_iterator ItemSet::end()
{
    return items.end();
}

/* **************************************************
 *
 ************************************************** */
ItemSet::set_of_item_const_iterator ItemSet::find(class Item *item) const
{
    return items.find(item);
}

/* **************************************************
 *
 ************************************************** */
bool ItemSet::insert(class Item* item, Synthesizer* synthesizer)
{
    if (items.size() > synthesizer->getMaxItems())
    {
        std::ostringstream oss;
        oss << "too much items build : " << items.size() << " (" << synthesizer->getMaxItems() << " Max)";
        throw fatal_exception(oss);
    }
#ifdef TRACE_INSERT
    std::cout << "<H3>####################### INSERT " << item->getId() << " #######################</H3>" << std::endl;
    item->print(std::cout);
    std::cout << std::endl;
#endif
    return items.insert(item).second;
}

/* **************************************************
 *
 ************************************************** */
void ItemSet::erase(class Item *item)
{
    items.erase(item);
}

/* **************************************************
 *
 ************************************************** */
size_t ItemSet::size() const
{
    return items.size();
}

/* **************************************************
 *
 ************************************************** */
void ItemSet::resetUsages()
{
    for (const auto &item : items)
    {
        item->ruleResetUsages();
    }
}

/* **************************************************
 *
 ************************************************** */
void ItemSet::print(std::ostream &oss)
{
    oss << "<TABLE border=\"0\">";
    for (const auto &item : items)
    {
        oss << "<TR>";
        oss << "<TD align=\"LEFT\">";
        item->print(oss);
        oss << "</TD>";
        oss << "</TR>";
    }
    oss << "</TABLE>";
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void ItemSet::toXML(xmlNodePtr node)
{
    xmlNodePtr s = xmlNewChild(node, NULL, (const xmlChar *)"STATE", NULL);
    xmlSetProp(s, (xmlChar *)"id", (xmlChar *)(std::to_string(this->id)).c_str());
    xmlSetProp(s, (xmlChar *)"fillcolor", (xmlChar *)"WHITE");
    xmlSetProp(s, (xmlChar *)"color", (xmlChar *)"BLACK");
    std::ostringstream oss;
    oss << "<TABLE BORDER=\"0\">";
    oss << "<TR><TD><FONT COLOR=\"BLUE\" FACE=\"Times-Roman\" POINT-SIZE=\"16\">Q" << id << "</FONT></TD></TR>";
    oss << "<TR>";
    oss << "<TD ALIGN=\"LEFT\">";
    print(oss);
    oss << "</TD>";
    oss << "</TR>";
    oss << "</TABLE>";
    xmlSetProp(s, (xmlChar *)"rule", (xmlChar *)(oss.str().c_str()));
}
#endif
