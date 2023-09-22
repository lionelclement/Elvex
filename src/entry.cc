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

uint16_t Entry::FORM_HEAD = 0;

/* **************************************************
 *
 ************************************************** */
Entry::Entry(uint16_t pos, uint16_t head, std::string form, featuresPtr features)
{
    this->pos = pos;
    this->head = head;
    this->form = std::move(form);
    this->features = features;
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Entry::Entry(uint16_t pos, uint16_t head, featuresPtr features)
{
    this->pos = pos;
    this->head = head;
    this->form = std::string();
    this->features = features;
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Entry::Entry(uint16_t pos, std::string head, std::string form, featuresPtr features)
{
    this->pos = pos;
    this->head = Vartable::nameToCode(std::move(head));
    this->form = std::move(form);
    this->features = features;
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Entry::Entry(uint16_t pos, featuresPtr features)
{
    this->pos = pos;
    this->head = UINT16_MAX;
    this->form = std::string();
    this->features = features;
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Entry::Entry(uint16_t pos)
{
    this->pos = pos;
    this->head = UINT16_MAX;
    this->form = std::string();
    this->features = featuresPtr();
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
entryPtr Entry::create(uint16_t term, uint16_t head, std::string form, featuresPtr features)
{
    return entryPtr(new Entry(term, head, std::move(form), features));
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entry::create(uint16_t term, uint16_t head, featuresPtr features)
{
    return entryPtr(new Entry(term, head, features));
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entry::create(uint16_t term, std::string head, std::string form, featuresPtr features)
{
    return entryPtr(new Entry(term, std::move(head), std::move(form), features));
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entry::create(uint16_t term, featuresPtr features)
{
    return entryPtr(new Entry(term, features));
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entry::create(uint16_t term)
{
    return entryPtr(new Entry(term));
}

/* **************************************************
 *
 ************************************************** */
uint16_t Entry::getPos() const
{
    return pos;
}

/* **************************************************
 *
 ************************************************** */
void Entry::setPos(uint16_t pos)
{
    this->pos = pos;
}

/* **************************************************
 *
 ************************************************** */
uint16_t Entry::getHead() const
{
    return head;
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
    if (this->pos != (uint16_t)-1)
    {
        xmlSetProp(entry, (xmlChar *)"pos", (xmlChar *)std::to_string(this->pos).c_str());
        xmlSetProp(entry, (xmlChar *)"posStr", (xmlChar *)Vartable::codeToName(this->pos).c_str());
    }
    if (this->head != (uint16_t)-1)
    {
        xmlSetProp(entry, (xmlChar *)"codeHead", (xmlChar *)std::to_string(this->head).c_str());
        xmlSetProp(entry, (xmlChar *)"codeHeadStr", (xmlChar *)Vartable::codeToName(this->head).c_str());
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
    os << "[pos:" << Vartable::codeToName(this->pos);
    if ((this->head != UINT16_MAX))
        os << ", head:" << Vartable::codeToName(this->head);
    else
        os << ", head:UINT16_MAX";
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

/* **************************************************
 *
 ************************************************** */
void Entry::renameVariables(size_t k)
{

    std::string pattern =
        std::string(
            "(\\$([a-zA-Z_]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß)([a-zA-Z0-9_]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß)+)");
    // std::cmatch match;

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
    return create(pos, std::move(head), std::move(form), features->clone());
}
