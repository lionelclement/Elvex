/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2018 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: Lionel Clément,
 * Labri -- 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#include "itemset.hh"
#include "messages.hh"
#include "item.hh"
#include "rule.hh"
#include "synthesizer.hh"

/* **************************************************
 *
 ************************************************** */
ItemSet::ItemSet (int id)
{
  NEW;
  this->id = id;
}

/* **************************************************
 *
 ************************************************** */
ItemSet::~ItemSet()
{
  for (iterator it = items.begin();
       it != items.end();
       ++it){
    itemPtr tmp = *it;
    if (tmp)
      (tmp).reset();
  }
  items.clear();
  DELETE;
}

/* **************************************************
 *
 ************************************************** */
itemSetPtr ItemSet::create (unsigned int id)
{
  return itemSetPtr( new ItemSet(id) );
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
std::set<itemPtr, Item::Less> &ItemSet::getItems(void)
{
  return items;
}

/* **************************************************
 *
 ************************************************** */
ItemSet::const_iterator ItemSet::begin(void) const 
{
  return items.begin();
}

/* **************************************************
 *
 ************************************************** */
ItemSet::const_iterator ItemSet::end(void) const 
{
  return items.end();
}

/* **************************************************
 *
 ************************************************** */
ItemSet::const_iterator ItemSet::find(itemPtr item) const 
{
  return items.find(item);
}

/* **************************************************
 *
 ************************************************** */
bool ItemSet::insert(itemPtr item, Synthesizer *synthesizer)
{
  if (items.size() > synthesizer->getMaxCardinal()){
    synthesizer->setMaxCardinalMsg(true);
  }
#ifdef TRACE_INSERT
  std::cerr << "####################### INSERT " << item->getId() << " #######################" << std::endl;
  item->print(std::cerr);
  std::cerr << std::endl;
#endif
  std::pair<iterator, bool> result = items.insert(item);
  return result.second;
}

/* **************************************************
 *
 ************************************************** */
void ItemSet::erase(itemPtr item)
{
  items.erase(item);
}

/* **************************************************
 *
 ************************************************** */
unsigned int ItemSet::size(void) const 
{
  return items.size();
}

/* **************************************************
 *
 ************************************************** */
void
ItemSet::resetUsages()
{
  for (iterator item=items.begin();
       item!=items.end();
       item++){
    (*item)->getRule()->resetUsages();

  }
}

/* **************************************************
 *
 ************************************************** */
void
ItemSet::print(std::ostream& oss)
{
  oss << "<TABLE border=\"0\">";
  for (iterator item=items.begin();
       item!=items.end();
       item++){
    oss << "<TR>";
    oss << "<TD align=\"LEFT\">";
    (*item)->print(oss);
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

