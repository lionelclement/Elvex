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

#include <sstream>
#include "itemset.hpp"
#include "messages.hpp"
#include "rule.hpp"
#include "application.hpp"

/* **************************************************
 *
 ************************************************** */
ItemSet::ItemSet(unsigned int id) {
    this->id = id;
    NEW
}

/* **************************************************
 *
 ************************************************** */
ItemSet::~ItemSet() {
    DELETE
    for (auto tmp : items) {
        if (tmp)
            (tmp).reset();
    }
    items.clear();
}

/* **************************************************
 *
 ************************************************** */
itemSetPtr ItemSet::create(unsigned int id) {
    return itemSetPtr(new ItemSet(id));
}

/* **************************************************
 *
 ************************************************** */
unsigned int ItemSet::getId(void) {
    return id;
}

/* **************************************************
 *
 ************************************************** */
ItemSet::set &ItemSet::getItems() {
    return items;
}

/* **************************************************
 *
 ************************************************** */
ItemSet::const_iterator ItemSet::begin() const {
    return items.begin();
}

/* **************************************************
 *
 ************************************************** */
ItemSet::const_iterator ItemSet::end() const {
    return items.end();
}

/* **************************************************
 *
 ************************************************** */
ItemSet::const_iterator ItemSet::find(const itemPtr& item) const {
    return items.find(item);
}

/* **************************************************
 *
 ************************************************** */
bool ItemSet::insert(const itemPtr& item, Application *application) {
    if (items.size() > application->getMaxCardinal()) {
        FATAL_ERROR ("*** error: too much items build : " << items.size() << " (" << application->getMaxCardinal() << " Max)");
    }
#ifdef TRACE_INSERT
    std::cout << "<H3>####################### INSERT " << item->getId() << " #######################</H3>" << std::endl;
    item->print(std::cout);
    std::cout << std::endl;
#endif
    //std::cerr << items.size() << std::endl;
    return items.insert(item).second;
}

/* **************************************************
 *
 ************************************************** */
void ItemSet::erase(const itemPtr& item) {
    items.erase(item);
}

/* **************************************************
 *
 ************************************************** */
size_t ItemSet::size() const {
    return items.size();
}

/* **************************************************
 *
 ************************************************** */
void ItemSet::resetUsages() {
    for (const auto & item : items) {
        item->getRule()->resetUsages();

    }
}

/* **************************************************
 *
 ************************************************** */
void ItemSet::print(std::ostream &oss) {
    oss << "<TABLE border=\"0\">";
    for (const auto & item : items) {
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
void
ItemSet::toXML(xmlNodePtr node)
{
   xmlNodePtr s=xmlNewChild(node, NULL, (const xmlChar*)"STATE", NULL);
   xmlSetProp(s, (xmlChar*)"id", (xmlChar*)(std::to_string(this->id)).c_str());
   xmlSetProp(s, (xmlChar*)"fillcolor", (xmlChar*)"WHITE");
   xmlSetProp(s, (xmlChar*)"color", (xmlChar*)"BLACK");
   std::ostringstream oss;
   oss << "<TABLE BORDER=\"0\">";
   oss << "<TR><TD><FONT COLOR=\"BLUE\" FACE=\"Times-Roman\" POINT-SIZE=\"16\">Q" << id << "</FONT></TD></TR>";
   oss << "<TR>";
   oss << "<TD ALIGN=\"LEFT\">";
   print(oss);
   oss << "</TD>";
   oss << "</TR>";
   oss << "</TABLE>";
   xmlSetProp(s, (xmlChar*)"rule", (xmlChar*)(oss.str().c_str()));
}
#endif

