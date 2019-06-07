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

#include "value.hh"
#include "environment.hh"
#include "list.hh"
#include "features.hh"
#include "statement.hh"
#include "statements.hh"
#include "messages.hh"
#include "item.hh"
#include "ipointer.hh"

valuePtr Value::_nil=Value::create(Value::BOOL, (unsigned int)0);
valuePtr Value::_true=Value::create(Value::BOOL, (unsigned int)1);
valuePtr Value::_anonymous=Value::create(Value::ANONYMOUS);

/* **************************************************
 *
 ************************************************** */
Value::Value(const Value::Type type, std::string str)
{
  NEW;
  this->type=type;
  this->integer=0;
  this->number=0;
  unsigned int found=0;
  if (type==IDENTIFIER){
    found=Vartable::strToInt(str);
    this->integer=found;
  }
  else if (type==STR){
    this->str=str;
  }
}

/* **************************************************
 *
 ************************************************** */
Value::Value(const Value::Type type, unsigned int integer, double number, bitsetPtr bits, featuresPtr features, listPtr list)
{
  NEW;
  this->type=type;
  this->integer=integer;
  this->number=number;
  this->bits=bits;
  this->features=features;
  this->list=list;
}

/* **************************************************
 *
 ************************************************** */
Value::~Value()
{
  //if (bits)
  //  bits->reset();
  //if (list)
  //list->reset();
  //DELETE;
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type)
{
  return valuePtr(new Value(type));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, double number)
{
  return valuePtr(new Value(type, 0, number));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, unsigned int integer)
{
  return valuePtr(new Value(type, integer));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, std::string str)
{
  return valuePtr(new Value(type, str));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, bitsetPtr bits)
{
  return valuePtr(new Value(type, 0, 0, bits));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, featuresPtr features)
{
  return valuePtr(new Value(type, 0, 0, bitsetPtr(), features));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, listPtr lst)
{
  return valuePtr(new Value(type, 0, 0, bitsetPtr(), featuresPtr(), lst));
}

/* **************************************************
 *
 ************************************************** */
void Value::setId(idType id)
{
  FATAL_ERROR;
}

/* **************************************************
 *
 ************************************************** */
Value::Type Value::getType(void) const 
{
  return type;
}

/* **************************************************
 *
 ************************************************** */
bitsetPtr Value::getBits(void) const 
{
  return bits;
}


/* **************************************************
 *
 ************************************************** */
unsigned int Value::getIdentifier(void) const 
{
  return integer;
}


/* **************************************************
 *
 ************************************************** */
featuresPtr Value::getFeatures(void) const 
{
  return features;
}


/* **************************************************
 *
 ************************************************** */
double Value::getDouble(void) const 
{
  return number;
}

/* **************************************************
 *
 ************************************************** */
std::string Value::getStr(void) const 
{
  return str;
}

/* **************************************************
 *
 ************************************************** */
listPtr Value::getList(void) const 
{
  return list;
}


/* **************************************************
 *
 ************************************************** */
bool Value::isNil(void) const 
{
  return (type==Value::BOOL && integer==0);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isFalse(void) const 
{
  return ((type==Value::BOOL && integer==0)
	  || (type==Value::ANONYMOUS));
}

/* **************************************************
 *
 ************************************************** */
bool Value::isTrue(void) const 
{
  return (type==Value::BOOL && integer==1);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isAnonymous(void) const 
{
  return (type==Value::ANONYMOUS);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isDouble(void) const 
{
  return getType()==DOUBLE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isStr(void) const 
{
  return getType()==STR;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isFeatures(void) const 
{
  return getType()==FEATURES;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isConstant(void) const 
{
  return getType()==CONSTANT;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isVariable(void) const 
{
  return getType()==VARIABLE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isIdentifier(void) const 
{
  return getType()==IDENTIFIER;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isList(void) const 
{
  return getType()==LIST;
}

/* **************************************************
 *
 ************************************************** */
void 
Value::print(std::ostream& outStream, bool par, bool flat) const 
{
  if (isNil())
    outStream << "NIL";
  else if (isTrue())
    outStream << "TRUE";
  else
    switch(type){
    case BOOL:
      FATAL_ERROR;
      break;
    case CONSTANT:
      outStream << getBits()->_toString();
      break;
    case VARIABLE:
      outStream << getBits()->_toString();
      break;
    case ANONYMOUS:
      outStream << '_';
      break;
    case IDENTIFIER:
      outStream << Vartable::intToStr(getIdentifier());
      break;
    case DOUBLE:
      outStream << getDouble();
      break;
    case STR:
      outStream << "&quot;" << getStr() << "&quot;";
      break;
    case FEATURES:
      getFeatures()->print(outStream, par, flat);
      break;
    case LIST:
      getList()->print(outStream, true, flat);
      break;
    }
}

/* **************************************************
 *
 ************************************************** */
const std::string
Value::makeSerializationId(void)
{
  if (isNil())
    serialId = 'N';
  else if (isTrue())
    serialId = 'T';
  else
    switch(type){
    case BOOL:
      FATAL_ERROR;
      break;
    case CONSTANT:
      serialId = 'C' + getBits()->serialize();
      break;
    case VARIABLE:
      serialId = '$' + getBits()->serialize();;
      break;
    case ANONYMOUS:
      serialId = '_';
      break;
    case IDENTIFIER:
      serialId = std::to_string(getIdentifier());
      break;
    case DOUBLE:
      serialId = getDouble();
      break;
    case STR:
      serialId = getStr();
      break;
    case FEATURES:
      serialId = getFeatures()->serialize();
      break;
    case LIST:
      serialId = getList()->serialize();
      break;
    }
  return serialId;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void 
Value::toXML(xmlNodePtr nodeRoot) const
{
  xmlNodePtr v = xmlNewChild(nodeRoot, NULL, (const xmlChar*)"VAL", NULL);
  switch(type){
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
  case IDENTIFIER:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"identifier");
    xmlNewChild(v, NULL, (const xmlChar*)"VAL", (const xmlChar*)Vartable::intToStr(getIdentifier()).c_str());
    break;
  case DOUBLE:
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
valuePtr 
Value::clone(void)
{
  valuePtr result=valuePtr();
  switch(type){
  case BOOL:
  case CONSTANT:
  case IDENTIFIER:
  case STR:
  case DOUBLE:
  case ANONYMOUS:
    result=shared_from_this();
    break;
  case FEATURES:
    result=Value::create(Value::FEATURES, getFeatures()->clone());
    break;
  case LIST:
    result=Value::create(Value::LIST, getList()->clone());
    break;
  case VARIABLE:
    result=Value::create(VARIABLE, getBits());
    break;
  }
  return result;
}

/* ************************************************************
 *
 ************************************************************ */
bool
Value::buildEnvironment(environmentPtr environment, valuePtr value, bool acceptToFilterNULLVariables, bool root)
{
  /***
      std::cerr << "<H4>Value::buildEnvironment</H4>" << std::endl;
      std::cerr << "<table border=\"1\"><tr><th></th><th></th><th>Environment</th></tr>";
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
      
  bool ret=true;
  switch(type){
  case BOOL:
    if (value->type == VARIABLE)
      environment->add(value->getBits(), shared_from_this());
    else if (this->isNil() || value->isNil())
      ret=false;
    break;
  case FEATURES:
    if (value->type == FEATURES){
      if (!this->getFeatures()->buildEnvironment(environment, value->getFeatures(), acceptToFilterNULLVariables, root))
	ret=false;
    }
    else
      ret=false;
    break;
  case CONSTANT:
    if (value->type == VARIABLE)
      environment->add(value->getBits(), shared_from_this());
    else if (value->type == CONSTANT){
      if ((*getBits() & *value->getBits()).none())
	ret=false;
    }
    else if (value->type == IDENTIFIER){
      if (Vartable::intToStr(getIdentifier()) != getBits()->_toString())
	ret=false;
    }
    else {
      this->print(std::cerr);
      std::cerr << std::endl << value->type << std::endl;
      FATAL_ERROR;
    }
    break;
  case IDENTIFIER:
    if (value->type == VARIABLE)
      environment->add(value->getBits(), shared_from_this());
    else if (getIdentifier() != value->getIdentifier())
      ret=false;
    break;
  case DOUBLE:
    if (value->type == VARIABLE)
      environment->add(value->getBits(), shared_from_this());
    else if (getDouble() != value->getDouble())
      ret=false;
    break;
  case STR:
    if (value->type == VARIABLE)
      environment->add(value->getBits(), shared_from_this());
    else if (getStr() != value->getStr())
      ret=false;
    break;
  case LIST:
    if (value->type == LIST){
      if (!this->getList()->buildEnvironment(environment, value->getList(), acceptToFilterNULLVariables, root))
	ret=false;
    }
    else if (value->type == VARIABLE)
      environment->add(value->getBits(), shared_from_this());
    else
      ret=false;
    break;
  case VARIABLE:
    if (!value)
      environment->add(this->getBits(), _nil);
    else
      environment->add(this->getBits(), value);
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
bool
Value::subsumes(valuePtr o, environmentPtr environment)
{
  bool ret=true;
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
  if (type==VARIABLE){
    environment->add(getBits(), o);
  }

  // … < X
  else if (o->type==VARIABLE){
    //FATAL_ERROR;
    environment->add(o->getBits(), shared_from_this());
    //FATAL_ERROR;

  }

  // NIL < NIL
  else if (isNil() && o->isNil()){

  }

  // NIL < …
  // … < NIL
  else if (isNil() || o->isNil()){
    //FATAL_ERROR;

  }

  // TRUE < TRUE
  else if (isTrue() && o->isTrue()){

  }

  // TRUE < …
  // … < TRUE
  else if (isTrue() || o->isTrue()){
    ret=false;


  }

  else if ((type != o->type)){
    ret=false;

  }

  else
    {
      switch (o->type){
	// a < a
      case IDENTIFIER:
	if (getIdentifier() != o->getIdentifier())
	  ret=false;
	break;
      case DOUBLE:
	if (getDouble() != o->getDouble())
	  ret=false;
	break;
      case CONSTANT:
	if ((*getBits() & *o->getBits()).none())
	  ret=false;
	break;
      case STR:
	if (getStr() != o->getStr())
	  ret=false;
	break;
      case FEATURES:
	ret=getFeatures()->subsumes(o->getFeatures(), environment);
	break;
      case LIST:
	ret=getList()->subsumes(o->getList(), environment);
	break;
      case BOOL:
      case VARIABLE:
      case ANONYMOUS:
	FATAL_ERROR;
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
bool
Value::eq(valuePtr o) const
{
  /*** 
       STD::CERR_LINE;
       this->print(std::cerr);
       std::cerr << " = ";
       o->print(std::cerr);
       std::cerr << std::endl;
  ***/

  bool ret=false;

  if (o->isNil() && this->isNil())
    ret = true;

  else if (o->isNil() || this->isNil())
    ret = false;

  else if (o->type == ANONYMOUS || this->type==ANONYMOUS)
    ret = true;

  else{
    switch (o->type){
    case BOOL:
      FATAL_ERROR;
      break;
    case IDENTIFIER:
      if ((type==IDENTIFIER) && ((getIdentifier() == o->getIdentifier())))
	ret=true;
      break;
    case CONSTANT:
      if ((type==CONSTANT) && ((*getBits() & *o->getBits()).any()))
	ret=true;
      else if ((type==IDENTIFIER) && (o->getBits()->_toString() == Vartable::intToStr(getIdentifier())))
	ret=true;
      break;
    case STR:
      if ((type==STR) && (getStr() == o->getStr()))
	ret=true;
      break;
    case DOUBLE:
      if ((type==DOUBLE) && (getDouble() == o->getDouble()))
	ret=true;
      break;
    case FEATURES:
      if ((type==FEATURES) && (getFeatures()->serialize() == o->getFeatures()->serialize()))
	ret=true;
      break;
    default:
      std::cerr << "###" << o->type << std::endl;
      FATAL_ERROR;
      break;
    }
  }
  return ret;
}

/* ************************************************************
 *
 ************************************************************ */
bool
Value::lt(valuePtr o) const
{
  bool ret=false;
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
    FATAL_ERROR;
  return ret;
}

/* ************************************************************
 *
 ************************************************************ */
void
Value::deleteAnonymousVariables()
{
  switch(type){
  case BOOL:
  case IDENTIFIER:
  case CONSTANT:
  case STR:
  case VARIABLE:
  case ANONYMOUS:
  case DOUBLE:
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
bool
Value::renameVariables(unsigned int i)
{
  bool effect=false;
  switch(type){
  case CONSTANT:
  case IDENTIFIER:
  case STR:
  case BOOL:
  case DOUBLE:
  case ANONYMOUS:
    break;
  case VARIABLE:
    {
      std::ostringstream oss;
      oss << getBits()->_toString() << "_" << i;
      std::string str = oss.str();
      bitsetPtr variableBits=Vartable::varTableAdd(str);
      this->bits=variableBits;
      resetSerialId();
      effect=true;
    }
    break;
  case FEATURES:
    if (getFeatures())
      if (getFeatures()->renameVariables(i)) effect=true;
    break;
  case LIST:
    if (getList())
      if (getList()->renameVariables(i)) effect=true;
    break;
  }
  return effect;
}

/* **************************************************
 *
 ************************************************** */
void 
Value::enable(statementPtr root, itemPtr item, bool &effect, bool on)
{
  switch(type){
  case BOOL:
  case IDENTIFIER:
  case STR:
  case CONSTANT:
  case DOUBLE:
  case ANONYMOUS:
    break;
  case VARIABLE:
    if (on){
      if ((!item->getEnvironment())
	  || (!item->getEnvironment()->find(getBits()))){
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
    getFeatures()->enable(root, item, effect, on);
    break;
  case LIST:
    getList()->enable(root, item, effect, on);
    break;
  }
}

/* **************************************************
 *
 ************************************************** */
bool 
Value::findVariable(bitsetPtr variable)
{
  switch(type){
  case BOOL:
  case IDENTIFIER:
  case STR:
  case CONSTANT:
  case DOUBLE:
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
