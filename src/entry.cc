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

#include <iterator>
#include <iostream>
#include <string>
#include <climits>
#include <utility>

#include "messages.hpp"
#include "entry.hpp"
#include "features.hpp"
#include "value.hpp"
#include "vartable.hpp"
#include "shared_ptr.hpp"

/* **************************************************
 *
 ************************************************** */
Entry::Entry(unsigned int pos, unsigned int head, std::string form, featuresPtr features)
{
    this->pos = pos;
    this->head = head;
    this->form = std::move(form);
    this->features = std::move(features);
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Entry::Entry(unsigned int pos, std::string head, std::string form, featuresPtr features)
{
    this->pos = pos;
    this->head = Vartable::stringToCode(std::move(head));
    this->form = std::move(form);
    this->features = std::move(features);
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Entry::~Entry()
{
    DELETE;
    if (features)
        features.reset();
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entry::create(unsigned int term, unsigned int codeHead, std::string form, featuresPtr features)
{
    return entryPtr(new Entry(term, codeHead, std::move(form), std::move(features)));
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entry::create(unsigned int term, std::string head, std::string form, featuresPtr features)
{
    return entryPtr(new Entry(term, std::move(head), std::move(form), std::move(features)));
}

/* **************************************************
 *
 ************************************************** */
unsigned int Entry::getPos() const
{
    return pos;
}

/* **************************************************
 *
 ************************************************** */
void Entry::setPos(unsigned int pos)
{
    this->pos = pos;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Entry::getHead() const
{
    return head;
}

/* **************************************************
 *
 ************************************************** */
std::string & Entry::getForm()
{
    return form;
}

/* **************************************************
 *
 ************************************************** */
void Entry::setForm(std::string form)
{
    this->form = std::move(form);
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Entry::getFeatures() const
{
    return features;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void Entry::toXML(xmlNodePtr nodeRoot) const
{
    xmlNodePtr entry = xmlNewChild(nodeRoot, nullptr, (const xmlChar *)"ENTRY", nullptr);
    if (this->pos != (unsigned int)-1)
    {
        xmlSetProp(entry, (xmlChar *)"pos", (xmlChar *)std::to_string(this->pos).c_str());
        xmlSetProp(entry, (xmlChar *)"posStr", (xmlChar *)Vartable::codeToString(this->pos).c_str());
    }
    if (this->head != (unsigned int)-1)
    {
        xmlSetProp(entry, (xmlChar *)"codeHead", (xmlChar *)std::to_string(this->head).c_str());
        xmlSetProp(entry, (xmlChar *)"codeHeadStr", (xmlChar *)Vartable::codeToString(this->head).c_str());
    }
    if (!this->form.empty())
    {
        xmlSetProp(entry, (xmlChar *)"form", (xmlChar *)this->form.c_str());
    }
    if (this->features)
    {
        this->features->toXML(entry);
    }
}
#endif

/* **************************************************
 *
 ************************************************** */
void Entry::print(std::ostream &os) const
{
    os << "[pos:" << Vartable::codeToString(this->pos);
    if ((this->head != UINT_MAX))
        os << ", head:" << Vartable::codeToString(this->head);
    else
        os << ", head:UINT_MAX";
    if (!this->form.empty())
        os << ", form:\"" << this->form << '"';
    else
        os << ", form:\"\"";
    os << ']';
}

/* **************************************************
 *
 ************************************************** */
void Entry::makeSerialString()
{
    serialString = std::to_string(pos) + std::to_string(head) + '"' + form + '"';
    if (features)
        serialString += features->peekSerialString();
    else
        serialString += 'N';
}
