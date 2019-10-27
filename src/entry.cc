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

#include <regex>
#include <iterator>
#include <iostream>
#include <string>

#include "messages.hh"
#include "entry.hh"
#include "features.hh"
#include "value.hh"

/* **************************************************
 *
 ************************************************** */
Entry::Entry(unsigned int code, unsigned int codePred, std::string form, featuresPtr features): Id(0)
{
  this->code = code;
  this->codePred = codePred;
  this->form = form;
  this->features = features;
  NEW;
}

/* **************************************************
 *
 ************************************************** */
Entry::Entry(unsigned int code, std::string pred, std::string form, featuresPtr features): Id(0)
{
  this->code = code;
  this->codePred = Vartable::strToInt(pred);
  this->form = form;
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
entryPtr Entry::create(unsigned int code, unsigned int codePred, std::string form, featuresPtr features)
{
  return entryPtr( new Entry(code, codePred, form, features) );
}

/* **************************************************
 *
 ************************************************** */
entryPtr Entry::create(unsigned int code, std::string pred, std::string form, featuresPtr features)
{
  return entryPtr( new Entry(code, pred, form, features) );
}

/* **************************************************
 *
 ************************************************** */
const unsigned int Entry::getCode(void) const
{
  return code;
}

/* **************************************************
 *
 ************************************************** */
void Entry::setCode(unsigned int code)
{
  this->code = code;
}

/* **************************************************
 *
 ************************************************** */
const unsigned int Entry::getCodePred(void) const
{
  return codePred;
}

/* **************************************************
 *
 ************************************************** */
std::string &
Entry::getForm(void)
{
  return form;
}

/* **************************************************
 *
 ************************************************** */
void Entry::setForm(std::string form)
{
  this->form = form;
}

/* **************************************************
 *
 ************************************************** */
const featuresPtr Entry::getFeatures(void) const 
{
  return features;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Entry::toXML(xmlNodePtr nodeRoot) const
{
  xmlNodePtr entry = xmlNewChild(nodeRoot, NULL, (const xmlChar*)"ENTRY", NULL);
  if (this->code!=(unsigned int)-1){
    xmlSetProp(entry, (xmlChar*)"code", (xmlChar*)Vartable::intToStr(this->code).c_str());
    xmlSetProp(entry, (xmlChar*)"codeStr", (xmlChar*)Vartable::intToStr(this->code).c_str());

  }
  if (this->codePred != (unsigned int)-1){
    xmlSetProp(entry, (xmlChar*)"codePred", (xmlChar*)Vartable::intToStr(this->codePred).c_str());
    xmlSetProp(entry, (xmlChar*)"codePredStr", (xmlChar*)Vartable::intToStr(this->codePred).c_str());

  }
  if (this->form.size() != 0){
    xmlSetProp(entry, (xmlChar*)"form", (xmlChar*)this->form.c_str());
  }
  if (this->features){
    this->features->toXML(entry);
  }
}
#endif

/* **************************************************
 *
 ************************************************** */
void
Entry::print(std::ostream& out) const
{
  out << "(id: " << this->getId() << ", code: " << Vartable::intToStr(this->code);
  if ((this->codePred != UINT_MAX))
    out << ", pred: " << Vartable::intToStr(this->codePred);
  if (this->form.size()!=0)
    out << ", form: " << this->form;
  out << ")";
}

/* **************************************************
 *
 ************************************************** */
void
Entry::makeSerialString()
{
  serialString = std::to_string(code) + std::to_string(codePred) + '"' + form + '"';
  if (features)
    serialString += features->peekSerialString();
  else
    serialString += 'N';
}
