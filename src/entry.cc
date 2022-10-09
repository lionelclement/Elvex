/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2020 LABRI, 
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
//#include "term.h"
#include "shared_ptr.hpp"

/* **************************************************
 *
 ************************************************** */
Entry::Entry(unsigned int pos, unsigned int pred, std::string form, featuresPtr features) {
    this->pos = pos;
    this->pred = pred;
    this->form = std::move(form);
    this->features = std::move(features);
    NEW
}

/* **************************************************
 *
 ************************************************** */
Entry::Entry(unsigned int pos, std::string pred, std::string form, featuresPtr features) {
    this->pos = pos;
    this->pred = Vartable::identifierToCode(std::move(pred));
    this->form = std::move(form);
    this->features = std::move(features);
    NEW
}

/* **************************************************
 *
 ************************************************** */
Entry::~Entry() {
    DELETE
    if (features)
        features.reset();
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entry::create(unsigned int term, unsigned int codePred, std::string form, featuresPtr features) {
    return entryPtr(new Entry(term, codePred, std::move(form), std::move(features)));
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entry::create(unsigned int term, std::string pred, std::string form, featuresPtr features) {
    return entryPtr(new Entry(term, std::move(pred), std::move(form), std::move(features)));
}

/* **************************************************
 *
 ************************************************** */
unsigned int Entry::getPos() const {
    return pos;
}

/* **************************************************
 *
 ************************************************** */
void Entry::setPos(unsigned int pos) {
    this->pos = pos;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Entry::getPred() const {
    return pred;
}

/* **************************************************
 *
 ************************************************** */
std::string&
Entry::getForm() {
    return form;
}

/* **************************************************
 *
 ************************************************** */
void Entry::setForm(std::string form) {
    this->form = std::move(form);
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Entry::getFeatures() const {
    return features;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Entry::toXML(xmlNodePtr nodeRoot) const
{
   xmlNodePtr entry = xmlNewChild(nodeRoot, nullptr, (const xmlChar*)"ENTRY", nullptr);
   if (this->pos != (unsigned int)-1) {
      xmlSetProp(entry, (xmlChar*)"pos", (xmlChar*)std::to_string(this->pos).c_str());
      xmlSetProp(entry, (xmlChar*)"posStr", (xmlChar*)Vartable::codeToIdentifier(this->pos).c_str());

   }
   if (this->pred != (unsigned int)-1) {
      xmlSetProp(entry, (xmlChar*)"codePred", (xmlChar*)std::to_string(this->pred).c_str());
      xmlSetProp(entry, (xmlChar*)"codePredStr", (xmlChar*)Vartable::codeToIdentifier(this->pred).c_str());

   }
   if (!this->form.empty()) {
      xmlSetProp(entry, (xmlChar*)"form", (xmlChar*)this->form.c_str());
   }
   if (this->features) {
      this->features->toXML(entry);
   }
}
#endif

/* **************************************************
 *
 ************************************************** */
void Entry::print(std::ostream &out) const {
    out << "(id: " << this->getId() << ", term: " << Vartable::codeToIdentifier(this->pos);
    if ((this->pred != UINT_MAX))
        out << ", pred: " << Vartable::codeToIdentifier(this->pred);
    if (!this->form.empty())
        out << ", form: " << this->form;
    out << ")";
}

/* **************************************************
 *
 ************************************************** */
void Entry::makeSerialString() {
    serialString = std::to_string(pos) + std::to_string(pred) + '"' + form + '"';
    if (features)
      serialString += features->peekSerialString();
    else
      serialString += 'N';
}
