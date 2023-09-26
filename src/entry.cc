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
Entry::Entry(std::string form, featuresPtr features)
{
    this->form = std::move(form);
    this->features = features;
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Entry::Entry(featuresPtr features)
{
    this->form = std::string();
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
entryPtr Entry::create(std::string form, featuresPtr features)
{
    return entryPtr(new Entry( std::move(form), features));
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
    if (features){
        features->flatPrint(os);
    } else {
        FATAL_ERROR_UNEXPECTED;
    }
    os << ')';
}

/* **************************************************
 *
 ************************************************** */
void Entry::makeSerialString()
{
    serialString = form + '\1';
    if (features)
        serialString += features->peekSerialString();
    else
        serialString += '\0';
}

/* **************************************************
 *
 ************************************************** */
void Entry::renameVariables(size_t k)
{

    std::string pattern =
        std::string(
            "(\\$([a-zA-Z_]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß)([a-zA-Z0-9_]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß)+)");

    try
    {
        std::regex regexpression(pattern, std::regex_constants::ECMAScript);
        std::string replacement_str = "$&_" + std::to_string(k);
        form = std::regex_replace(form, regexpression, replacement_str);
    }

    catch (const std::regex_error &e)
    {
        std::cout << "regex_error caught: " << e.what() << '(' << e.code() << ')' << std::regex_constants::error_brack
                  << '\n';
    }
    if (features)
        features->renameVariables(k);
    resetSerial();
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entry::clone() const
{
    return create(std::move(form), features->clone());
}
