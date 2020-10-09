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

#include <sstream>
#include "value.hh"
#include "environment.hh"
#include "list.hh"
#include "features.hh"
#include "statement.hh"
#include "statements.hh"
#include "messages.hh"
#include "item.hh"
#include "shared_ptr.hh"
#include "synthesizer.hh"
#include "vartable.hh"

valuePtr Value::NIL_VALUE = Value::create(Value::BOOL, (unsigned int)0);//Value::create(Value::FEATURES);
valuePtr Value::TRUE_VALUE = Value::create(Value::BOOL, (unsigned int)1);
valuePtr Value::FALSE_VALUE = Value::create(Value::BOOL, (unsigned int)0);
valuePtr Value::ANONYMOUS_VALUE = Value::create(Value::ANONYMOUS);

/* **************************************************
 *
 ************************************************** */
Value::Value(Value::Type const type, std::string str)
  : Id(0) {
  this->type = type;
  this->integer = 0;
  this->number = 0;
  unsigned int found = 0;
  if (type == CODE) {
    found = Vartable::identifierToCode(str);
    this->integer = found;
  }
  else if (type == STR) {
    this->str = str;
  }NEW;
}

/* **************************************************
 *
 ************************************************** */
Value::Value(Value::Type const type, unsigned int integer, double number, bitsetPtr bits, featuresPtr features, listPtr list)
  : Id(0) {
  this->type = type;
  this->integer = integer;
  this->number = number;
  this->bits = bits;
  this->features = features;
  this->list = list;
  NEW;
}

/* **************************************************
 *
 ************************************************** */
Value::~Value() {
  DELETE;
  if (bits)
    bits.reset();
  if (features)
    features.reset();
  if (list)
    list.reset();
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type) {
  return valuePtr(new Value(type));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, double number) {
  return valuePtr(new Value(type, 0, number));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, unsigned int integer) {
  return valuePtr(new Value(type, integer));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, std::string str) {
  return valuePtr(new Value(type, str));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, bitsetPtr bits) {
  return valuePtr(new Value(type, 0, 0, bits));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, featuresPtr features) {
  return valuePtr(new Value(type, 0, 0, bitsetPtr(), features));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, listPtr lst) {
  return valuePtr(new Value(type, 0, 0, bitsetPtr(), featuresPtr(), lst));
}

/* **************************************************
 *
 ************************************************** */
Value::Type Value::getType(void) const {
  return type;
}

/* **************************************************
 *
 ************************************************** */
bitsetPtr Value::getBits(void) const {
  return bits;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Value::getIdentifier(void) const {
  return integer;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Value::getFeatures(void) const {
  return features;
}

/* **************************************************
 *
 ************************************************** */
double Value::getDouble(void) const {
  return number;
}

/* **************************************************
 *
 ************************************************** */
std::string Value::getStr(void) const {
  return str;
}

/* **************************************************
 *
 ************************************************** */
listPtr Value::getList(void) const {
  return list;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isNil(void) const {
  return (type == Value::BOOL && integer == 0);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isFalse(void) const {
  return ((type == Value::BOOL && integer == 0)) || (type == Value::ANONYMOUS);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isTrue(void) const {
  return (type == Value::BOOL && integer == 1);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isAnonymous(void) const {
  return (type == Value::ANONYMOUS);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isDouble(void) const {
  return getType() == NUMBER;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isStr(void) const {
  return getType() == STR;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isFeatures(void) const {
  return getType() == FEATURES;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isConstant(void) const {
  return getType() == CONSTANT;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isVariable(void) const {
  return getType() == VARIABLE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isIdentifier(void) const {
  return getType() == CODE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isList(void) const {
  return getType() == LIST;
}

/* **************************************************
 *
 ************************************************** */
void Value::print(std::ostream& outStream) const {
  if (isNil())
    outStream << "NIL";
  else if (isTrue())
    outStream << "TRUE";
  else
    switch (type) {
    case BOOL:
      FATAL_ERROR_UNEXPECTED
	break;
    case CONSTANT:
      outStream << getBits()->toString();
      break;
    case VARIABLE:
      outStream << getBits()->toString();
      break;
    case ANONYMOUS:
      outStream << '_';
      break;
    case CODE:
      outStream << Vartable::codeToIdentifier(getIdentifier());
      break;
    case NUMBER:
      outStream << getDouble();
      break;
    case STR:
      outStream << "&quot;" << getStr() << "&quot;";
      break;
    case FEATURES:
      getFeatures()->print(outStream);
      break;
    case LIST:
      getList()->flatPrint(outStream, true);
      break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Value::flatPrint(std::ostream& outStream) const {
  if (isNil())
    outStream << "NIL";
  else if (isTrue())
    outStream << "TRUE";
  else
    switch (type) {
    case BOOL:
      FATAL_ERROR_UNEXPECTED
	break;
    case CONSTANT:
      outStream << getBits()->toString();
      break;
    case VARIABLE:
      outStream << getBits()->toString();
      break;
    case ANONYMOUS:
      outStream << '_';
      break;
    case CODE:
      outStream << Vartable::codeToIdentifier(getIdentifier());
      break;
    case NUMBER:
      outStream << getDouble();
      break;
    case STR:
      outStream << '"' << getStr() << '"';
      break;
    case FEATURES:
      getFeatures()->flatPrint(outStream);
      break;
    case LIST:
      getList()->flatPrint(outStream, true);
      break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Value::makeSerialString(void) {
  if (isNil())
    serialString = 'N';
  else if (isTrue())
    serialString = 'T';
  else
    switch (type) {
    case BOOL:
      FATAL_ERROR_UNEXPECTED
	break;
    case CONSTANT:
      serialString = getBits()->peekSerialString();
      break;
    case VARIABLE:
      serialString = '$' + getBits()->peekSerialString();
      break;
    case ANONYMOUS:
      serialString = '_';
      break;
    case CODE:
      //serialString = std::to_string(getIdentifier());
      serialString = Vartable::codeToIdentifier(getIdentifier());
      break;
    case NUMBER:
      serialString = getDouble();
      break;
    case STR:
      serialString = getStr();
      break;
    case FEATURES:
      serialString = getFeatures()->peekSerialString();
      break;
    case LIST:
      serialString = getList()->peekSerialString();
      break;
    }
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Value::toXML(xmlNodePtr nodeRoot) const
{
  xmlNodePtr v = xmlNewChild(nodeRoot, NULL, (const xmlChar*)"VAL", NULL);
  switch(type) {
  case BOOL:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"bool");
    if (isNil())
      xmlSetProp(v, (xmlChar*)"value", (const xmlChar*)"NIL");
    else
      xmlSetProp(v, (xmlChar*)"value", (const xmlChar*)"TRUE");
    break;
  case CONSTANT:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"constant");
    getBits()->toXML(v);
    break;
  case VARIABLE:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"variable");
    getBits()->toXML(v);
    break;
  case ANONYMOUS:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"anonymous");
    getBits()->toXML(v);
    break;
  case CODE:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"identifier");
    xmlNewChild(v, NULL, (const xmlChar*)"VAL", (const xmlChar*)Vartable::codeToIdentifier(getIdentifier()).c_str());
    break;
  case NUMBER:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"double");
    xmlSetProp(v, (xmlChar*)"value",(const xmlChar*)std::to_string(getDouble()).c_str());
    break;
  case STR:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"str");
    xmlNewChild(v, NULL, (const xmlChar*)"VAL", (const xmlChar*)getStr().c_str());
    break;
  case FEATURES:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"fs");
    getFeatures()->toXML(v);
    break;
  case LIST:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"list");
    getList()->toXML(v);
    break;

  }
}
#endif

/* **************************************************
 *
 ************************************************** */
valuePtr Value::clone(void) {
  valuePtr result = valuePtr();
  switch (type) {
  case BOOL:
  case CONSTANT:
  case CODE:
  case STR:
  case NUMBER:
  case ANONYMOUS:
    result = shared_from_this();
    break;
  case FEATURES:
    result = Value::create(Value::FEATURES, getFeatures()->clone());
    break;
  case LIST:
    result = Value::create(Value::LIST, getList()->clone());
    break;
  case VARIABLE:
    result = Value::create(VARIABLE, getBits());
    break;
  }
  return result;
}

/* ************************************************************
 *
 ************************************************************ */
bool Value::buildEnvironment(environmentPtr environment, valuePtr value, bool acceptToFilterNULLVariables, bool root) {
  /*** 
  CERR_LINE;
  std::cerr << "<H4>Value::buildEnvironment</H4>" << std::endl;
  std::cerr << "<table border=\"1\"><tr><th>this</th><th>value</th><th>Environment</th></tr>";
  std::cerr << "<tr><td>";
  this->print(std::cerr);
  std::cerr << "</td><td>";
  if (value)
    value->print(std::cerr);
  else
    std::cerr << "NULL";
  std::cerr << "</td><td>";
  environment->print(std::cerr);
  std::cerr << "</td></tr></table>";
  ***/

  bool ret = true;
  switch (type) {

  case BOOL:
    if (value->type == VARIABLE)
      environment->add(value->getBits(), shared_from_this());
    else if (value->type == BOOL) {
      if (this->isNil() || value->isNil())
	ret = false;
    }
    else if (value->type == ANONYMOUS) {
    }
    else {
      ret = false;
    }
    break;

  case FEATURES:
    if (value->type == VARIABLE) {
      environment->add(value->getBits(), shared_from_this());
    }
    else if (value->type == FEATURES) {
      if (!this->getFeatures()->buildEnvironment(environment, value->getFeatures(), acceptToFilterNULLVariables, root))
	ret = false;
    }
    else if (value->type == ANONYMOUS) {
      if (!this->getFeatures()->buildEnvironment(environment, Features::create(), acceptToFilterNULLVariables, root))
	ret = false;
    }
    else if (value->type == BOOL) {
      environment->add(value->getBits(), shared_from_this());
    }
    else {
      ret = false;
    }
    break;

  case CONSTANT:
    if (value->type == VARIABLE) {
      environment->add(value->getBits(), shared_from_this());
    }
    else if (value->type == CONSTANT) {
      if ((*getBits() & *value->getBits()).none())
	ret = false;
    }
    else if (value->type == CODE) {
      if (getBits()->toString() != Vartable::codeToIdentifier(value->getIdentifier()))
	ret = false;
    }
    else if (value->type == ANONYMOUS) {
    }
    else {
      ret = false;
    }
    break;
	
  case CODE:
    if (value->type == VARIABLE) {
      environment->add(value->getBits(), shared_from_this());
    }
    else if (value->type == CONSTANT) {
      if (Vartable::codeToIdentifier(getIdentifier()) != value->getBits()->toString())
	ret = false;
    }
    else if (value->type == CODE) {
      if (getIdentifier() != value->getIdentifier())
	ret = false;
    }
    else if (value->type == ANONYMOUS) {
    }
    else {
      ret = false;
    }
    break;
    
  case NUMBER:
    if (value->type == VARIABLE) {
      environment->add(value->getBits(), shared_from_this());
    }
    else if (value->type == NUMBER) {
      if (getDouble() != value->getDouble()) {
	ret = false;
      }
    }
    else if (value->type == ANONYMOUS) {
    }
    else {
      ret = false;
    }
    break;
    
  case STR:
    if (value->type == VARIABLE) {
      environment->add(value->getBits(), shared_from_this());
    }
    else if (value->type == STR) {
      if (getStr() != value->getStr()) {
	ret = false;
      }
    }
    else if (value->type == ANONYMOUS) {
    }
    else {
      ret = false;
    }
    break;

  case LIST:
    if (value->type == LIST) {
      if (!this->getList()->buildEnvironment(environment, value->getList(), acceptToFilterNULLVariables, root))
	ret = false;
    }
    else if (value->type == VARIABLE) {
      environment->add(value->getBits(), shared_from_this());
    }
    else if (value->type == ANONYMOUS) {
    }
    else {
      ret = false;
    }
    break;

  case VARIABLE:
    if (!value) {
      environment->add(this->getBits(), NIL_VALUE);
    }
    else {
      environment->add(this->getBits(), value);
    }
    break;

  case ANONYMOUS:
    break;
  }
  /*** 
       std::cerr << "<H4>Result Value::buildEnvironment</H4>" << std::endl;
       std::cerr << "<table border=\"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
       std::cerr << "<tr><td>" << (ret?"TRUE":"FALSE") << "</td><td>";
       environment->print(std::cerr);
       std::cerr << "</td></tr></table>";
  ***/
  return ret;
}
  
/* ************************************************************
 * this < o
 ************************************************************ */
bool Value::subsumes(valuePtr o, environmentPtr environment) {
  bool ret = true;
  /***
      std::cerr << "<DIV>";
      std::cerr << "Value::subsumes (" << this << ")";
      std::cerr << "<TABLE><TR>";
      std::cerr << "<TD>";
      this->print(std::cerr);
      std::cerr << "</TD>&lt;<TD>";
      o->print(std::cerr);
      std::cerr << "</TD>";
      std::cerr << "</TR></TABLE>";
      std::cerr << "</DIV>";
  ***/

  // X < …
  if (type == VARIABLE) {
    environment->add(getBits(), o);
  }

  // … < X
  else if (o->type == VARIABLE) {
    //FATAL_ERROR;
    environment->add(o->getBits(), shared_from_this());
    //FATAL_ERROR;

  }

  // NIL < NIL
  else if (isNil() && o->isNil()) {

  }

  // NIL < …
  // … < NIL
  else if (isNil() || o->isNil()) {
    //FATAL_ERROR;

  }

  // TRUE < TRUE
  else if (isTrue() && o->isTrue()) {

  }

  // TRUE < …
  // … < TRUE
  else if (isTrue() || o->isTrue()) {
    ret = false;

  }

  else if ((type != o->type)) {
    ret = false;

  }

  else {
    switch (o->type) {
      // a < a
    case CODE:
      if (getIdentifier() != o->getIdentifier())
	ret = false;
      break;
    case NUMBER:
      if (getDouble() != o->getDouble())
	ret = false;
      break;
    case CONSTANT:
      if ((*getBits() & *o->getBits()).none())
	ret = false;
      break;
    case STR:
      if (getStr() != o->getStr())
	ret = false;
      break;
    case FEATURES:
      ret = getFeatures()->subsumes(o->getFeatures(), environment);
      break;
    case LIST:
      ret = getList()->subsumes(o->getList(), environment);
      break;
    default:
      FATAL_ERROR_UNEXPECTED
	break;

    }

  }
  /***
      std::cerr << "<DIV>";
      std::cerr << "result: (" << shared_from_this() << ")";
      std::cerr << "</DIV>";
  ***/
  return ret;
}

/* ************************************************************
 *
 ************************************************************ */
bool Value::eq(valuePtr o) const {
  /***
      STD::CERR_LINE;
      this->print(std::cerr);
      std::cerr << " = ";
      o->print(std::cerr);
      std::cerr << std::endl;
  ***/

  bool ret = false;

  if (o->isNil() && this->isNil())
    ret = true;

  else if (o->isNil() || this->isNil())
    ret = false;

  else if (o->type == ANONYMOUS || this->type == ANONYMOUS)
    ret = true;

  else {
    switch (o->type) {
    case BOOL:
      FATAL_ERROR_UNEXPECTED
	break;
    case CODE:
      if ((type == CODE) && ((getIdentifier() == o->getIdentifier())))
	ret = true;
      break;
    case CONSTANT:
      if ((type == CONSTANT) && ((*getBits() & *o->getBits()).any()))
	ret = true;
      else if ((type == CODE) && (o->getBits()->toString() == Vartable::codeToIdentifier(getIdentifier())))
	ret = true;
      break;
    case STR:
      if ((type == STR) && (getStr() == o->getStr()))
	ret = true;
      break;
    case NUMBER:
      if ((type == NUMBER) && (getDouble() == o->getDouble()))
	ret = true;
      break;
    case FEATURES:
      if ((type == FEATURES) && (getFeatures()->peekSerialString() == o->getFeatures()->peekSerialString()))
	ret = true;
      break;
    default:
      FATAL_ERROR_UNEXPECTED
	break;
    }
  }
  return ret;
}

/* ************************************************************
 *
 ************************************************************ */
bool Value::lt(valuePtr o) const {
  bool ret = false;
  /***
      STD::CERR_LINE;
      this->print(std::cerr);
      std::cerr << " < ";
      o->print(std::cerr);
      std::cerr << std::endl;
  ***/
  if (isDouble() && o->isDouble())
    return (getDouble() < o->getDouble());
  else
    FATAL_ERROR_UNEXPECTED
      return ret;
}

/* ************************************************************
 *
 ************************************************************ */
void Value::deleteAnonymousVariables() {
  switch (type) {
  case BOOL:
  case CODE:
  case CONSTANT:
  case STR:
  case VARIABLE:
  case ANONYMOUS:
  case NUMBER:
    break;
  case FEATURES:
    getFeatures()->deleteAnonymousVariables();
    break;
  case LIST:
    getList()->deleteAnonymousVariables();
    break;
  }
}

/* **************************************************
 *
 ************************************************** */
bool Value::renameVariables(size_t i) {
  bool effect = false;
  switch (type) {
  case CONSTANT:
  case CODE:
  case STR:
  case BOOL:
  case NUMBER:
  case ANONYMOUS:
    break;
  case VARIABLE: {
    std::ostringstream oss;
    oss << getBits()->toString() << "_" << i;
    std::string str = oss.str();
    bitsetPtr variableBits = Vartable::createVariable(str);
    this->bits = variableBits;
    resetSerial();
    effect = true;
  }
    break;
  case FEATURES:
    if (getFeatures())
      if (getFeatures()->renameVariables(i))
	effect = true;
    break;
  case LIST:
    if (getList())
      if (getList()->renameVariables(i))
	effect = true;
    break;
  }
  return effect;
}

/* **************************************************
 *
 ************************************************** */
void Value::enable(statementPtr root, itemPtr item, Synthesizer *synthesizer, bool &effect, bool on) {
  switch (type) {
  case BOOL:
  case CODE:
  case STR:
  case CONSTANT:
  case NUMBER:
  case ANONYMOUS:
    break;
  case VARIABLE:
    if (on) {
      if ((!item->getEnvironment()) || (!item->getEnvironment()->find(getBits()))) {
	root->addFlags(Flags::DISABLED);
	effect = true;
      }
    }
    else {
      root->subFlags(Flags::DISABLED);
      effect = true;
    }
    break;
  case FEATURES:
    getFeatures()->enable(root, item, synthesizer, effect, on);
    break;
  case LIST:
    getList()->enable(root, item, synthesizer, effect, on);
    break;
  }
}

/* **************************************************
 *
 ************************************************** */
bool Value::findVariable(bitsetPtr variable) {
  switch (type) {
  case BOOL:
  case CODE:
  case STR:
  case CONSTANT:
  case NUMBER:
  case ANONYMOUS:
    break;
  case VARIABLE:
    if (*getBits() == *variable)
      return true;
    break;
  case FEATURES:
    if (getFeatures()->findVariable(variable))
      return true;
    break;
  case LIST:
    if (getList()->findVariable(variable))
      return true;
    break;
  }
  return false;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Value::apply(itemPtr item, Parser &parser, Synthesizer *synthesizer, statementPtr variable, statementPtr body, bool &effect) {
  switch (type) {
  case FEATURES:
    CERR_LINE;
    item->getEnvironment()->add(variable->getBits(), shared_from_this());
    effect = true;
    body->apply(item, parser, synthesizer, effect);
    item->getEnvironment()->remove(variable->getBits());
    break;
  default:
    FATAL_ERROR_UNEXPECTED
      break;
  }
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool Value::containsVariable(void) {
  bool result = false;
  if (variableFlag.containsVariable())
    return true;
  switch (type) {
  case BOOL:
  case CODE:
  case STR:
  case CONSTANT:
  case NUMBER:
  case ANONYMOUS:
    break;
  case VARIABLE:
    result = true;
    break;
  case LIST:
    if (this->getList()->containsVariable()) {
      result = true;
    }
    break;
  case FEATURES:
    if (this->getFeatures()->containsVariable()) {
      result = true;
    }
    break;
  }
  if (result)
    this->variableFlag.setFlag(VariableFlag::DOES_CONTAIN);
  else
    this->variableFlag.setFlag(VariableFlag::DOES_NOT_CONTAIN);
  return result;
}

/* **************************************************
 *
 ************************************************** */
void Value::setVariableFlag(enum VariableFlag::flagValues flag) {
  this->variableFlag.setFlag(flag);
}
