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

// #include <utility>

#include "feature.hpp"
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
Feature::Feature(enum Feature::Type type, bitsetPtr _attribute, valuePtr _value)
{
    NEW;
    this->type = type;
    this->attribute = std::move(_attribute);
    this->value = std::move(_value);
}

/* ************************************************************
 *
 ************************************************************ */
Feature::~Feature()
{
    DELETE;
    if (attribute)
        attribute.reset();
    if (value)
        value.reset();
}

/* ************************************************************
 *
 ************************************************************ */
featurePtr Feature::create(Feature::Type type, bitsetPtr _attribute, valuePtr _value)
{
    return featurePtr(new Feature(type, std::move(_attribute), std::move(_value)));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Feature::getValue() const
{
    return this->value;
}

/* **************************************************
 *
 ************************************************** */
Feature::Type Feature::_getType() const
{
    return this->type;
}

/* **************************************************
 *
 ************************************************** */
void Feature::setType(const Feature::Type _type)
{
    this->type = _type;
}

/* **************************************************
 *
 ************************************************** */
bool Feature::isHead() const
{
    return this->type == _HEAD_;
}

/* **************************************************
 *
 ************************************************** */
bool Feature::isForm() const
{
    return this->type == _FORM_;
}

/* **************************************************
 *
 ************************************************** */
bool Feature::isLemma() const
{
    return this->type == _LEMMA_;
}

/* **************************************************
 *
 ************************************************** */
bool Feature::isConstant() const
{
    return this->type == _CONSTANT_;
}

/* **************************************************
 *
 ************************************************** */
bool Feature::isVariable() const
{
    return this->type == _VARIABLE_;
}

/* **************************************************
 *
 ************************************************** */
bitsetPtr Feature::getAttribute() const
{
    return this->attribute;
}

/* **************************************************
 *
 ************************************************** */
std::string Feature::attributeToString() const
{
    return attribute->toString();
}

/* **************************************************
 *
 ************************************************** */
void Feature::setAttribute(bitsetPtr _attribute)
{
    this->attribute = std::move(_attribute);
}

/* **************************************************
 *
 ************************************************** */
void Feature::setValue(valuePtr _value)
{
    this->value = std::move(_value);
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
void Feature::print(std::ostream& outStream) const {
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
            if (value && !value->isNil()) {
                outStream << "<TD ALIGN=\"LEFT\">";
                value->print(outStream);
                outStream << "</TD>";
            }
            break;
=======
void Feature::print(std::ostream &outStream) const
{
    switch (type)
    {
    case Feature::_HEAD_:
        outStream << R"(<TD ALIGN="LEFT">HEAD</TD><TD ALIGN="LEFT">)";
        if (value)
            value->print(outStream);
        else
            outStream << "NIL";
        outStream << "</TD>";
        break;
    case Feature::_LEMMA_:
        outStream << R"(<TD ALIGN="LEFT">LEMMA</TD><TD ALIGN="LEFT">)";
        if (value)
            value->print(outStream);
        else
            outStream << "NIL";
        outStream << "</TD>";
        break;
    case Feature::_FORM_:
        outStream << R"(<TD ALIGN="LEFT">FORM</TD><TD ALIGN="LEFT">)";
        if (value)
            value->print(outStream);
        else
            outStream << "NIL";
        outStream << "</TD>";
        break;
    case Feature::_CONSTANT_:
        outStream << "<TD ALIGN=\"LEFT\">" << attributeToString() << "</TD><TD ALIGN=\"LEFT\">";
        if (value)
            value->print(outStream);
        else
            outStream << "NIL";
        outStream << "</TD>";
        break;
    case Feature::_VARIABLE_:
        outStream << "<TD ALIGN=\"LEFT\">" << attributeToString() << "</TD>";
        if (value && !value->isNil())
        {
            outStream << "<TD ALIGN=\"LEFT\">";
            value->print(outStream);
            outStream << "</TD>";
        }
        break;
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    }
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
void Feature::flatPrint(std::ostream& outStream) const {
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
            if (value && !value->isNil()) {
                value->flatPrint(outStream);
            }
            break;
=======
void Feature::flatPrint(std::ostream &outStream) const
{
    switch (type)
    {
    case Feature::_HEAD_:
        outStream << "HEAD:";
        if (value)
            value->flatPrint(outStream);
        else
            outStream << "NIL";
        break;
    case Feature::_LEMMA_:
        outStream << "LEMMA:";
        if (value)
            value->flatPrint(outStream);
        else
            outStream << "NIL";
        break;
    case Feature::_FORM_:
        outStream << "FORM:";
        if (value)
            value->flatPrint(outStream);
        else
            outStream << "NIL";
        break;
    case Feature::_CONSTANT_:
        outStream << attributeToString() << ':';
        if (value)
            value->flatPrint(outStream);
        else
            outStream << "NIL";
        break;
    case Feature::_VARIABLE_:
        outStream << attributeToString();
        if (value && !value->isNil())
        {
            value->flatPrint(outStream);
        }
        break;
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    }
}

/* **************************************************
 *
 ************************************************** */
void Feature::makeSerialString()
{
    switch (type)
    {
    case Feature::_HEAD_:
        serialString = '\0';
        break;
    case Feature::_LEMMA_:
        serialString = '\1';
        break;
    case Feature::_FORM_:
        serialString = '\2';
        break;
    case Feature::_CONSTANT_:
        serialString = attribute->peekSerialString();
        break;
    case Feature::_VARIABLE_:
        serialString = '\3' + attribute->peekSerialString();
        break;
    }
    if (value)
        serialString += '\4' + value->peekSerialString();
    else
        serialString += '\5';
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void Feature::toXML(xmlNodePtr nodeRoot)
{
    xmlNodePtr f = xmlNewChild(nodeRoot, nullptr, (const xmlChar *)"F", nullptr);

    switch (type)
    {
    case Feature::_HEAD_:
        xmlSetProp(f, (xmlChar *)"type", (const xmlChar *)"head");
        break;
    case Feature::_LEMMA_:
        xmlSetProp(f, (xmlChar *)"type", (const xmlChar *)"lemma");
        break;
    case Feature::_FORM_:
        xmlSetProp(f, (xmlChar *)"type", (const xmlChar *)"form");
        break;
    case Feature::_CONSTANT_:
        xmlSetProp(f, (xmlChar *)"type", (const xmlChar *)"constant");
        xmlSetProp(f, (xmlChar *)"name", (const xmlChar *)attributeToString().c_str());
        break;
    case Feature::_VARIABLE_:
        xmlSetProp(f, (xmlChar *)"type", (const xmlChar *)"variable");
        xmlSetProp(f, (xmlChar *)"name", (const xmlChar *)attributeToString().c_str());
        break;
    }
    if (value)
        value->toXML(f);
}
#endif

/* **************************************************
 *
 ************************************************** */
featurePtr Feature::clone() const
{
    return create(type, attribute, (value) ? value->clone() : valuePtr());
}

/* **************************************************
 *
 ************************************************** */
bool Feature::renameVariables(size_t i)
{
    bool effect = false;
    switch (type)
    {
    case Feature::_HEAD_:
    case Feature::_LEMMA_:
    case Feature::_CONSTANT_:
        if (value)
            if (value->renameVariables(i))
                effect = true;
        break;
    case Feature::_FORM_:
        break;
    case Feature::_VARIABLE_:
    {
        std::string str = attributeToString() + '_' + std::to_string(i);
        bitsetPtr variableBits = Vartable::createVariable(str);
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
<<<<<<< HEAD
void Feature::enable(const statementPtr& root, const itemPtr& item, Application* application, bool& effect, bool on) {
    switch (type) {
        case Feature::PRED:
        case Feature::LEMMA:
        case Feature::FORM:
        case Feature::CONSTANT:
            if (value)
                value->enable(root, item, application, effect, on);
            break;
        case Feature::VARIABLE:
            if (on) {
                if ((!item->getEnvironment()) || (!item->getEnvironment()->find(getAttribute()))) {
                    root->addFlags(Flags::DISABLED);
                    effect = true;
                }
            } else {
                root->subFlags(Flags::DISABLED);
=======
void Feature::enable(const statementPtr &root, class Item *item, Synthesizer *synthesizer, bool &effect, bool on)
{
    switch (type)
    {
    case Feature::_HEAD_:
    case Feature::_LEMMA_:
    case Feature::_FORM_:
    case Feature::_CONSTANT_:
        if (value)
            value->enable(root, item, synthesizer, effect, on);
        break;
    case Feature::_VARIABLE_:
        if (on)
        {
            if ((!item->getEnvironment()) || (!item->getEnvironment()->find(getAttribute())))
            {
                root->addFlags(Flags::DISABLED);
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
                effect = true;
            }
        }
        else
        {
            root->subFlags(Flags::DISABLED);
            effect = true;
        }
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Feature::findVariable(const bitsetPtr &variable)
{
    switch (type)
    {
    case Feature::_HEAD_:
    case Feature::_LEMMA_:
    case Feature::_FORM_:
    case Feature::_CONSTANT_:
        if (value && value->findVariable(variable))
            return true;
        break;
    case Feature::_VARIABLE_:
        if (*getAttribute() == *variable)
            return true;
        break;
    }
    return false;
}

/* **************************************************
 *
 ************************************************** */
bool Feature::containsVariable()
{
    bool result = false;
    if (variableFlag.containsVariable())
        return true;
    switch (type)
    {
    case Feature::_HEAD_:
    case Feature::_LEMMA_:
    case Feature::_FORM_:
    case Feature::_CONSTANT_:
        if (value && value->containsVariable())
        {
            result = true;
        }
        break;
    case Feature::_VARIABLE_:
        result = true;
        break;
    }
    if (result)
<<<<<<< HEAD
        variableFlag.setFlag(VariableFlag::DOES_NOT_CONTAIN_VARIABLE);
=======
        variableFlag.setFlag(VariableFlag::CONTAINS);
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    else
        variableFlag.setFlag(VariableFlag::DOES_NOT_CONTAIN_VARIABLE);
    return result;
}

