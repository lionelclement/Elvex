/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI, 
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

#include "feature.hpp"

#include <utility>
#include "environment.hpp"
#include "value.hpp"
#include "statement.hpp"
#include "statements.hpp"
#include "messages.hpp"
#include "item.hpp"
#include "vartable.hpp"

/* ************************************************************
 * 
 ************************************************************ */
Feature::Feature(enum Feature::Type type, bitsetPtr _attribute, valuePtr _value) {
    this->type = type;
    this->attribute = std::move(_attribute);
    this->value = std::move(_value);
    NEW
}

/* ************************************************************
 * 
 ************************************************************ */
Feature::~Feature() {
    DELETE
    if (attribute)
        attribute.reset();
    if (value)
        value.reset();
}

/* ************************************************************
 * 
 ************************************************************ */
featurePtr Feature::create(Feature::Type type, bitsetPtr _attribute, valuePtr _value) {
    return featurePtr(new Feature(type, std::move(_attribute), std::move(_value)));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Feature::getValue() const {
    return this->value;
}

/* **************************************************
 *
 ************************************************** */
Feature::Type Feature::getType() const {
    return this->type;
}

/* **************************************************
 *
 ************************************************** */
void Feature::setType(const Feature::Type _type) {
    this->type = _type;
}

/* **************************************************
 *
 ************************************************** */
bitsetPtr Feature::getAttribute() const {
    return this->attribute;
}

/* **************************************************
 *
 ************************************************** */
std::string Feature::attributeToString() const {
    return attribute->toString();
}

/* **************************************************
 *
 ************************************************** */
void Feature::setAttribute(bitsetPtr _attribute) {
    this->attribute = std::move(_attribute);
}

/* **************************************************
 *
 ************************************************** */
void Feature::setValue(valuePtr _value) {
    this->value = std::move(_value);
}

/* **************************************************
 *
 ************************************************** */
void Feature::print(std::ostream &outStream) const {
    switch (type) {
        case Feature::PRED:
            outStream << R"(<TD ALIGN="LEFT">PRED</TD><TD ALIGN="LEFT">)";
            if (value)
                value->print(outStream);
            else
                outStream << "NIL";
            outStream << "</TD>";
            break;
        case Feature::LEMMA:
            outStream << R"(<TD ALIGN="LEFT">LEMMA</TD><TD ALIGN="LEFT">)";
            if (value)
                value->print(outStream);
            else
                outStream << "NIL";
            outStream << "</TD>";
            break;
        case Feature::FORM:
            outStream << R"(<TD ALIGN="LEFT">FORM</TD><TD ALIGN="LEFT">)";
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
            if (value && !value->_isNil()) {
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
void Feature::flatPrint(std::ostream &outStream) const {
    switch (type) {
        case Feature::PRED:
            outStream << "PRED:";
            if (value)
                value->flatPrint(outStream);
            else
                outStream << "NIL";
            break;
        case Feature::LEMMA:
            outStream << "LEMMA:";
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
            outStream << attributeToString();
            if (value && !value->_isNil()) {
                value->flatPrint(outStream);
            }
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Feature::makeSerialString() {
    switch (type) {
        case Feature::PRED:
            serialString = 'P';
            break;
        case Feature::LEMMA:
            serialString = 'L';
            break;
        case Feature::FORM:
            serialString = 'F';
            break;
        case Feature::CONSTANT:
            serialString = attribute->peekSerialString();
            break;
        case Feature::VARIABLE:
            serialString = '$' + attribute->peekSerialString();
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
   xmlNodePtr f=xmlNewChild(nodeRoot, nullptr, (const xmlChar*)"F", nullptr);

   switch(type) {
       case Feature::PRED:
           xmlSetProp(f, (xmlChar*)"type", (const xmlChar*)"pred");
           break;
       case Feature::LEMMA:
           xmlSetProp(f, (xmlChar*)"type", (const xmlChar*)"lemma");
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
        case Feature::LEMMA:
        case Feature::CONSTANT:
            if (value)
                if (value->renameVariables(i))
                    effect = true;
            break;
        case Feature::FORM:
            break;
        case Feature::VARIABLE: {
            std::string str = attributeToString() + '_' + std::to_string(i);
            bitsetPtr variableBits = Vartable::createVariable(str);
            attribute = variableBits;
            if (value)
                value->renameVariables(i);
            _resetSerial();
            effect = true;
        }
            break;
    }
    return effect;
}

/* **************************************************
 *
 ************************************************** */
void Feature::enable(const statementPtr& root, const itemPtr& item, Synthesizer *synthesizer, bool &effect, bool on) {
    switch (type) {
        case Feature::PRED:
        case Feature::LEMMA:
        case Feature::FORM:
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
            } else {
                root->subFlags(Flags::DISABLED);
                effect = true;
            }
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Feature::findVariable(const bitsetPtr& variable) {
    switch (type) {
        case Feature::PRED:
        case Feature::LEMMA:
        case Feature::FORM:
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
bool Feature::containsVariable() {
    bool result = false;
    if (variableFlag.containsVariable())
        return true;
    switch (type) {
        case Feature::PRED:
        case Feature::LEMMA:
        case Feature::FORM:
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
        variableFlag.setFlag(VariableFlag::CONTAINS);
    else
        variableFlag.setFlag(VariableFlag::DOES_NOT_CONTAIN);
    return result;
}
