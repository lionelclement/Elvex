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

#include <regex>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
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
Entry::Entry(const std::string &form, featuresPtr features)
{
    this->form = form;
    this->features = features;
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Entry::Entry(featuresPtr features)
{
    this->form = "";
    this->features = features;
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
entryPtr Entry::create(const std::string &form, featuresPtr features)
{
    return entryPtr(new Entry(form, features));
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entry::create(featuresPtr features)
{
    return entryPtr(new Entry(features));
}

/* **************************************************
 *
 ************************************************** */
std::string &Entry::getForm()
{
    return form;
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
    os << "Entry(" /*<< Vartable::codeToName(this->pos) */;
    if (!this->form.empty())
        os << "form:\"" << this->form << "\", ";
    if (features)
    {
        features->flatPrint(os);
    }
    else
    {
        FATAL_ERROR_UNEXPECTED;
    }
    os << ')';
}

/* **************************************************
 *
 ************************************************** */
void Entry::makeSerialString()
{
    std::ostringstream stream;
    stream << form << '/';
    if (features)
        stream << features->peekSerialString();
    else
        stream << '/';
    serialString = stream.str();
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entry::clone() const
{
    return create(std::string(form), features->clone());
}
