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
#include "terminal.hpp"
#include "features.hpp"
#include "value.hpp"
#include "vartable.hpp"
#include "shared_ptr.hpp"

/* **************************************************
 *
 ************************************************** */
Terminal::Terminal(uint16_t code)
{
    this->code = code;
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Terminal::Terminal(uint16_t code, std::string form)
{
    this->code = code;
    this->form = std::move(form);
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Terminal::Terminal(uint16_t code, std::string form, featuresPtr features)
{
    this->code = code;
    this->form = std::move(form);
    this->features = features;
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Terminal::~Terminal()
{
    DELETE;
}

/* **************************************************
 *
 ************************************************** */
terminalPtr Terminal::create(uint16_t code, std::string form, featuresPtr features)
{
    return terminalPtr(new Terminal(code, std::move(form), features));
}

/* **************************************************
 *
 ************************************************** */
terminalPtr Terminal::create(uint16_t code, std::string form)
{
    return terminalPtr(new Terminal(code, std::move(form)));
}

/* **************************************************
 *
 ************************************************** */
terminalPtr Terminal::create(uint16_t code)
{
    return terminalPtr(new Terminal(code));
}

/* **************************************************
 *
 ************************************************** */
std::string &Terminal::getForm()
{
    return form;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void Terminal::toXML(xmlNodePtr nodeRoot) const
{
    xmlNodePtr entry = xmlNewChild(nodeRoot, nullptr, (const xmlChar *)"TERMINAL", nullptr);
    if (this->code)
    {
        xmlSetProp(entry, (xmlChar *)"code", (xmlChar *)std::to_string(this->code).c_str());
        xmlSetProp(entry, (xmlChar *)"codeStr", (xmlChar *)Vartable::codeToName(this->code).c_str());
    }
}
#endif

/* **************************************************
 *
 ************************************************** */
void Terminal::print(std::ostream &os) const
{
    os << "Terminal[" << Vartable::codeToName(this->code) << ']';
}

/* **************************************************
 *
 ************************************************** */
void Terminal::makeSerialString()
{
    std::ostringstream stream;
    stream << std::hex << code << '/' << form << '/' << features->peekSerialString();
    serialString = stream.str();
   //serialString = std::to_string(code);
}

/* **************************************************
 *
 ************************************************** */
terminalPtr Terminal::clone() const
{
    return create(code);
}
