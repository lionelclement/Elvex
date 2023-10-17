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
    this->attribute = _attribute;
    this->value = _value;
}

/* ************************************************************
 *
 ************************************************************ */
Feature::Feature(enum Feature::Type type, uint32_t code, valuePtr _value)
{
    NEW;
    this->type = type;
    this->attribute = bitsetPtr();
    this->code = code;
    this->value = _value;
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
featurePtr Feature::createConstant(bitsetPtr _attribute, valuePtr _value)
{
    return featurePtr(new Feature(_CONSTANT_, _attribute, _value));
}

/* ************************************************************
 *
 ************************************************************ */
featurePtr Feature::createHead(valuePtr _value)
{
    return featurePtr(new Feature(_HEAD_, bitsetPtr(), _value));
}

/* ************************************************************
 *
 ************************************************************ */
featurePtr Feature::createForm(valuePtr _value)
{
    return featurePtr(new Feature(_FORM_, bitsetPtr(), _value));
}

/* ************************************************************
 *
 ************************************************************ */
featurePtr Feature::createLemma(valuePtr _value)
{
    return featurePtr(new Feature(_LEMMA_, bitsetPtr(), _value));
}

/* ************************************************************
 *
 ************************************************************ */
featurePtr Feature::createVariable(uint32_t code, valuePtr _value)
{
    return featurePtr(new Feature(_VARIABLE_, code, _value));
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
Feature::Type Feature::getType() const
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
uint32_t Feature::getCode() const
{
    return this->code;
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
    this->attribute = _attribute;
}

/* **************************************************
 *
 ************************************************** */
void Feature::setValue(valuePtr _value)
{
    this->value = _value;
}

/* **************************************************
 *
 ************************************************** */
void Feature::print(std::ostream &outStream) const
{
    switch (type)
    {
    case Feature::_HEAD_:
        outStream << R"(<TD ALIGN="LEFT">HEAD</TD><TD ALIGN="LEFT">)";
        if (value)
            value->print(outStream);
        else
            FATAL_ERROR_UNEXPECTED;
        // outStream << "nullptr";
        outStream << "</TD>";
        break;
    case Feature::_LEMMA_:
        outStream << R"(<TD ALIGN="LEFT">LEMMA</TD><TD ALIGN="LEFT">)";
        if (value)
            value->print(outStream);
        else
            FATAL_ERROR_UNEXPECTED;
        // outStream << "nullptr";
        outStream << "</TD>";
        break;
    case Feature::_FORM_:
        outStream << R"(<TD ALIGN="LEFT">FORM</TD><TD ALIGN="LEFT">)";
        if (value)
            value->print(outStream);
        else
            FATAL_ERROR_UNEXPECTED;
        // outStream << "nullptr";
        outStream << "</TD>";
        break;
    case Feature::_CONSTANT_:
        outStream << "<TD ALIGN=\"LEFT\">" << attributeToString() << "</TD><TD ALIGN=\"LEFT\">";
        if (value)
            value->print(outStream);
        else
            FATAL_ERROR_UNEXPECTED;
        // outStream << "nullptr";
        outStream << "</TD>";
        break;
    case Feature::_VARIABLE_:
        outStream << "<TD ALIGN=\"LEFT\">$" << Vartable::codeToName(code) << "</TD>";
        if (value && !value->isNil())
        {
            outStream << "<TD ALIGN=\"LEFT\">$";
            value->print(outStream);
            outStream << "</TD>";
        }
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
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
        outStream << '$' << Vartable::codeToName(code);
        if (value && !value->isNil())
        {
            //value->flatPrint(outStream);
        }
        break;
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
        serialString = 'H';
        break;
    case Feature::_LEMMA_:
        serialString = 'L';
        break;
    case Feature::_FORM_:
        serialString = 'F';
        break;
    case Feature::_CONSTANT_:
        serialString = 'C' + attribute->peekSerialString();
        break;
    case Feature::_VARIABLE_:
        serialString = 'R' + std::to_string(code);
        break;
    }
    if (value)
        serialString += 'V' + value->peekSerialString();
    else
        serialString += 'N';
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
    if (attribute)
        return featurePtr(new Feature(type, attribute->clone(), (value) ? value->clone() : valuePtr()));
    else
        return featurePtr(new Feature(type, code, (value) ? value->clone() : valuePtr()));
}

/* **************************************************
 *
 ************************************************** */
bool Feature::renameVariables(uint32_t code)
{
    bool effect = false;
    if (type == Feature::_VARIABLE_)
    {
        attribute = Vartable::createSymbol(attribute->toString(), code);
        resetSerial();
        effect = true;
    }
    if (value)
    {
        if (value->renameVariables(code))
        {
            resetSerial();
            effect = true;
        }
    }
    return effect;
}

/* **************************************************
 *
 ************************************************** */
void Feature::enable(const statementPtr &root, class Item *item, Generator *synthesizer, bool &effect, bool on)
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
            if ((!item->getEnvironment()) || (!item->getEnvironment()->find(getCode())))
            {
                root->addFlags(Flags::DISABLED);
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
bool Feature::findVariable(uint32_t key) const
{
    switch (type)
    {
    case Feature::_HEAD_:
    case Feature::_LEMMA_:
    case Feature::_FORM_:
    case Feature::_CONSTANT_:
        if (value && value->findVariable(key))
            return true;
        break;
    case Feature::_VARIABLE_:
        if ((code == key)
        && (!value || value->findVariable(key)))
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
        variableFlag.setFlag(VariableFlag::CONTAINS);
    else
        variableFlag.setFlag(VariableFlag::DOES_NOT_CONTAIN);
    return result;
}
