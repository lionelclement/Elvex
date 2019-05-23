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

#include "feature.hh"
#include "environment.hh"
#include "value.hh"
#include "statement.hh"
#include "statements.hh"
#include "messages.hh"
#include "item.hh"

/* ************************************************************
 * 
 ************************************************************ */
Feature::Feature(enum Feature::Type type, bitsetPtr attribute, valuePtr value)
{
  NEW;
  this->type=type;
  this->attribute = attribute;
  this->value = value;
}

/* ************************************************************
 * 
 ************************************************************ */
Feature::~Feature()
{
  if (attribute)
    attribute.reset();
  if (value)
    value.reset();
  DELETE;
}

/* **************************************************
 *
 ************************************************** */
void Feature::setId(idType id)
{
  FATAL_ERROR;
}

/* ************************************************************
 * 
 ************************************************************ */
featurePtr Feature::create(Feature::Type type, bitsetPtr attribute, valuePtr value)
{
  return featurePtr( new Feature(type, attribute, value) );
}

/* **************************************************
 *
 ************************************************** */
const valuePtr Feature::getValue(void) const 
{
  return this->value;
}

/* **************************************************
 *
 ************************************************** */
const Feature::Type Feature::getType(void) const 
{
  return this->type;
}

/* **************************************************
 *
 ************************************************** */
void Feature::setType(const Feature::Type type)
{
  this->type=type;
}

/* **************************************************
 *
 ************************************************** */
const bitsetPtr Feature::getAttribute(void) const
{
  return this->attribute;
}

/* **************************************************
 *
 ************************************************** */
std::string Feature::attributeToString(void) const 
{
  return attribute->_toString();
}

/* **************************************************
 *
 ************************************************** */
void Feature::setAttribute(bitsetPtr attribute)
{
  this->attribute=attribute;
}

/* **************************************************
 *
 ************************************************** */
void 
Feature::setValue(valuePtr value)
{
  this->value=value;
}

/* **************************************************
 *
 ************************************************** */
void
Feature::print(std::ostream& outStream, bool flat) const
{
  switch(type){
  case Feature::PRED:
    if (!flat)
      outStream << "<TD ALIGN=\"LEFT\">";
    outStream << "PRED";
    if (!flat)
      outStream << "</TD><TD ALIGN=\"LEFT\">";
    else
      outStream << ":";
    if (value)
      value->print(outStream, false, flat);
    else
      outStream << "NIL";
    if (!flat)
      outStream << "</TD>";
    break;
  case Feature::FORM:
    if (!flat)
      outStream << "<TD ALIGN=\"LEFT\">";
    outStream << "FORM";
    if (!flat)
      outStream << "</TD><TD ALIGN=\"LEFT\">";
    else
      outStream << ":";
    if (value)
      value->print(outStream, true, flat);
    else
      outStream << "NIL";
    if (!flat)
      outStream << "</TD>";
    break;
  case Feature::CONSTANT:
    if (!flat)
      outStream << "<TD ALIGN=\"LEFT\">";
    outStream << attributeToString();
    if (!flat)
      outStream << "</TD><TD ALIGN=\"LEFT\">";
    else
      outStream << ":";
    if (value)
      value->print(outStream, true, flat);
    else
      outStream << "NIL";
    if (!flat)
      outStream << "</TD>";
    break;
  case Feature::VARIABLE:
    if (!flat)
      outStream << "<TD ALIGN=\"LEFT\">";
    outStream << attributeToString();
    if (!flat)
      outStream << "</TD>";
    if (value && !value->isNil()){
      if (!flat)
	outStream << "<TD ALIGN=\"LEFT\">";
      else
	outStream << ":";
      value->print(outStream, true, flat);
      if (!flat)
	outStream << "</TD>";
    }
    break;
  }
}

/* **************************************************
 *
 ************************************************** */
const std::string
Feature::makeSerializationId()
{
  switch(type){
  case Feature::PRED:
    serialId = 'P';
    break;
  case Feature::FORM:
    serialId = 'F';
    break;
  case Feature::CONSTANT:
    serialId = this->attribute->serialize() + ':';
    break;
  case Feature::VARIABLE:
    serialId = '$' + this->attribute->serialize() + ':';
    break;
  }
  if (value)
    serialId += value->serialize();
  else
    serialId += 'N';
  return serialId;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Feature::toXML(xmlNodePtr nodeRoot)
{
  xmlNodePtr f=xmlNewChild(nodeRoot, NULL, (const xmlChar*)"F", NULL);

  switch(type){
  case Feature::PRED:
    xmlSetProp(f, (xmlChar*)"type", (const xmlChar*)"pred");
    break;
  case Feature::FORM:
    xmlSetProp(f, (xmlChar*)"type", (const xmlChar*)"form");
    break;
  case Feature::CONSTANT:
    xmlSetProp(f, (xmlChar*)"type", (const xmlChar*)"constant");
    xmlSetProp(f, (xmlChar*)"name", (const xmlChar*)attributeToString().c_str());
    break;
  case Feature::VARIABLE:
    xmlSetProp(f, (xmlChar*)"type", (const xmlChar*)"variable");
    xmlSetProp(f, (xmlChar*)"name", (const xmlChar*)attributeToString().c_str());
    break;
  }
  if (value)
    value->toXML(f);
}
#endif

/* **************************************************
 *
 ************************************************** */
featurePtr 
Feature::clone()
{
  featurePtr result = create(type, attribute, (value) ? value->clone() : valuePtr());
  return result;
}

/* **************************************************
 *
 ************************************************** */
const bool
Feature::renameVariables(const unsigned int i)
{
  bool effect=false;
  switch(type){
  case Feature::PRED:
  case Feature::CONSTANT:
    if (value)
      if (value->renameVariables(i)) effect=true;
    break;
  case Feature::FORM:
    break;
  case Feature::VARIABLE:
    {
      std::string str = attributeToString() + '_' + std::to_string(i);
      bitsetPtr variableBits=Vartable::varTableAdd(str);
      attribute=variableBits;
      if (value)
	value->renameVariables(i);
      resetSerialId();
      effect = true;
    }
    break;
  }
  return effect;
}

/* **************************************************
 *
 ************************************************** */
void
Feature::enable(statementPtr root, itemPtr item, bool &effect, bool on)
{
  switch(type){
  case Feature::FORM:
  case Feature::PRED:
  case Feature::CONSTANT:
    if (value)
      value->enable(root, item, effect, on);
    break;
  case Feature::VARIABLE:
    if (on){
      if ((!item->getEnvironment())
	  || (!item->getEnvironment()->find(getAttribute()))){
	  root->addFlags(Flags::DISABLED);
	  effect = true;
      }
    }
    else {
      root->subFlags(Flags::DISABLED);
      effect = true;
    }
    break;
  }
}

/* **************************************************
 *
 ************************************************** */
const bool
Feature::findVariable(const bitsetPtr variable) const
{
  switch(type){
  case Feature::FORM:
  case Feature::PRED:
  case Feature::CONSTANT:
    if (value && value->findVariable(variable))
      return true;
    break;
  case Feature::VARIABLE:
    if (*getAttribute() == *variable)
      return true;
    break;
  }
  return false;
}
