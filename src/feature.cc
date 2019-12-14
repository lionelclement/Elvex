/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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

#include "feature.hh"
#include "environment.hh"
#include "value.hh"
#include "statement.hh"
#include "statements.hh"
#include "messages.hh"
#include "item.hh"
#include "bitset.hh"
#include "vartable.hh"

/* ************************************************************
 * 
 ************************************************************ */
Feature::Feature(enum Feature::Type type, bitsetPtr attribute, valuePtr value)
      : Id(0) {
   this->type = type;
   this->attribute = attribute;
   this->value = value;
   NEW;
}

/* ************************************************************
 * 
 ************************************************************ */
Feature::~Feature() {
   DELETE;
   if (attribute)
      attribute.reset();
   if (value)
      value.reset();
}

/* ************************************************************
 * 
 ************************************************************ */
featurePtr Feature::create(Feature::Type type, bitsetPtr attribute, valuePtr value) {
   return featurePtr(new Feature(type, attribute, value));
}

/* **************************************************
 *
 ************************************************** */
const valuePtr Feature::getValue(void) const {
   return this->value;
}

/* **************************************************
 *
 ************************************************** */
const Feature::Type Feature::getType(void) const {
   return this->type;
}

/* **************************************************
 *
 ************************************************** */
void Feature::setType(const Feature::Type type) {
   this->type = type;
}

/* **************************************************
 *
 ************************************************** */
const bitsetPtr Feature::getAttribute(void) const {
   return this->attribute;
}

/* **************************************************
 *
 ************************************************** */
std::string Feature::attributeToString(void) const {
   return attribute->toString();
}

/* **************************************************
 *
 ************************************************** */
void Feature::setAttribute(bitsetPtr attribute) {
   this->attribute = attribute;
}

/* **************************************************
 *
 ************************************************** */
void Feature::setValue(valuePtr value) {
   this->value = value;
}

/* **************************************************
 *
 ************************************************** */
void Feature::print(std::ostream& outStream) const {
   switch (type) {
      case Feature::PRED:
         outStream << "<TD ALIGN=\"LEFT\">PRED</TD><TD ALIGN=\"LEFT\">";
         if (value)
            value->print(outStream);
         else
            outStream << "NIL";
         outStream << "</TD>";
         break;
      case Feature::FORM:
         outStream << "<TD ALIGN=\"LEFT\">FORM</TD><TD ALIGN=\"LEFT\">";
         if (value)
            value->print(outStream);
         else
            outStream << "NIL";
         outStream << "</TD>";
         break;
      case Feature::CONSTANT:
         outStream << "<TD ALIGN=\"LEFT\">" << attributeToString() << "</TD><TD ALIGN=\"LEFT\">";
         if (value)
            value->print(outStream);
         else
            outStream << "NIL";
         outStream << "</TD>";
         break;
      case Feature::VARIABLE:
         outStream << "<TD ALIGN=\"LEFT\">" << attributeToString() << "</TD>";
         if (value && !value->isNil()) {
            outStream << "<TD ALIGN=\"LEFT\">";
            value->print(outStream);
            outStream << "</TD>";
         }
         break;
   }
}

/* **************************************************
 *
 ************************************************** */
void Feature::flatPrint(std::ostream& outStream) const {
   switch (type) {
      case Feature::PRED:
         outStream << "PRED:";
         if (value)
            value->flatPrint(outStream);
         else
            outStream << "NIL";
         break;
      case Feature::FORM:
         outStream << "FORM:";
         if (value)
            value->flatPrint(outStream);
         else
            outStream << "NIL";
         break;
      case Feature::CONSTANT:
         outStream << attributeToString() << ':';
         if (value)
            value->flatPrint(outStream);
         else
            outStream << "NIL";
         break;
      case Feature::VARIABLE:
         outStream << attributeToString() << ':';
         if (value && !value->isNil()) {
            value->flatPrint(outStream);
         }
         break;
   }
}

/* **************************************************
 *
 ************************************************** */
void Feature::makeSerialString(void) {
   switch (type) {
      case Feature::PRED:
         serialString = 'P';
         break;
      case Feature::FORM:
         serialString = 'F';
         break;
      case Feature::CONSTANT:
         serialString = this->attribute->peekSerialString();
         break;
      case Feature::VARIABLE:
         serialString = '$' + this->attribute->peekSerialString();
         break;
   }
   if (value)
      serialString += ':' + value->peekSerialString();
   else
      serialString += 'N';
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Feature::toXML(xmlNodePtr nodeRoot)
{
   xmlNodePtr f=xmlNewChild(nodeRoot, NULL, (const xmlChar*)"F", NULL);

   switch(type) {
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
featurePtr Feature::clone() const {
   return create(type, attribute, (value) ? value->clone() : valuePtr());
}

/* **************************************************
 *
 ************************************************** */
bool Feature::renameVariables(size_t i) {
   bool effect = false;
   switch (type) {
      case Feature::PRED:
      case Feature::CONSTANT:
         if (value)
            if (value->renameVariables(i))
               effect = true;
         break;
      case Feature::FORM:
         break;
      case Feature::VARIABLE: {
         std::string str = attributeToString() + '_' + std::to_string(i);
         bitsetPtr variableBits = Vartable::varTableAdd(str);
         attribute = variableBits;
         if (value)
            value->renameVariables(i);
         resetSerial();
         effect = true;
      }
         break;
   }
   return effect;
}

/* **************************************************
 *
 ************************************************** */
void Feature::enable(statementPtr root, itemPtr item, Synthesizer *synthesizer, bool &effect, bool on) {
   switch (type) {
      case Feature::FORM:
      case Feature::PRED:
      case Feature::CONSTANT:
         if (value)
            value->enable(root, item, synthesizer, effect, on);
         break;
      case Feature::VARIABLE:
         if (on) {
            if ((!item->getEnvironment()) || (!item->getEnvironment()->find(getAttribute()))) {
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
bool Feature::findVariable(const bitsetPtr variable) {
   switch (type) {
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

/* **************************************************
 *
 ************************************************** */
bool Feature::containsVariable(void) {
   bool result = false;
   if (variableFlag.containsVariable())
      return true;
   switch (type) {
      case Feature::FORM:
      case Feature::PRED:
      case Feature::CONSTANT:
         if (value && value->containsVariable()) {
            result = true;
         }
         break;
      case Feature::VARIABLE:
         result = true;
         break;
   }
   if (result)
      variableFlag.setFlag(VariableFlag::DOES_CONTAIN);
   else
      variableFlag.setFlag(VariableFlag::DOES_NOT_CONTAIN);
   return result;
}

/* **************************************************
 *
 ************************************************** */
void Feature::setVariableFlag(enum VariableFlag::flagValues flag) {
   this->variableFlag.setFlag(flag);
}
