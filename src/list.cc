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
#include "list.hh"
#include "environment.hh"
#include "features.hh"
#include "messages.hh"
#include "ipointer.hh"
#include "grammar.hh"
#include "statement.hh"

listPtr List::NILLIST = List::create();
bitsetPtr List::gwith;

/* **************************************************
 *
 ************************************************** */
List::List(enum List::Type type, valuePtr value, listPtr car, listPtr cdr): Id(0)
{
  this->type = type;
  this->value = value;
  this->pairp.car = car;
  this->pairp.cdr = cdr;
  NEW;
}

/* **************************************************
 *
 ************************************************** */
List::~List()
{
  DELETE;
  if (pairp.car)
	  pairp.car.reset();
  if (pairp.cdr)
	  pairp.cdr.reset();
}

/* **************************************************
 *
 ************************************************** */
listPtr List::create()
{
  return listPtr( new List(List::NIL) );
}

/* **************************************************
 *
 ************************************************** */
listPtr List::create(valuePtr value)
{
  return listPtr( new List(List::ATOM, value) );
}

/* **************************************************
 *
 ************************************************** */
listPtr List::create(listPtr car, listPtr cdr)
{
  return listPtr( new List(List::PAIRP, valuePtr(), car, cdr) );
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
List::Type List::getType(void) const 
{
  return type;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
valuePtr List::getValue(void) const 
{
  return value;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void List::setValue(valuePtr value)
{
  this->value = value;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
listPtr List::car(void) const 
{
  return pairp.car;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
listPtr List::cdr(void) const 
{
  return pairp.cdr;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
listPtr List::cadr(void) const 
{
  return pairp.cdr->pairp.car;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
listPtr List::cddr(void) const 
{
  return pairp.cdr->pairp.cdr;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
listPtr List::caar(void) const 
{
  return pairp.car->pairp.car;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
listPtr List::cdar(void) const 
{
  return pairp.car->pairp.cdr;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool List::isNil(void) const 
{
  return (this->type == List::NIL);
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool List::isAtom(void) const 
{
  return (this->type == List::ATOM);
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool List::isPairp(void) const 
{
  return (this->type == PAIRP);
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr
List::getBits() const
{
  return value->getBits();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
featuresPtr 
List::getfeaturePtrs(void) const
{
  return value->getFeatures();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
unsigned int
List::getIdentifier(void) const
{
  return value->getIdentifier();
}

/* **************************************************
 *
 ************************************************** */
void
List::makeSerialString(void)
{
  switch (type){
  case NIL:
    serialString  =  'N';
    break;
  case ATOM:
    serialString  =  value->peekSerialString();
    break;
  case PAIRP:
    serialString  =  '<' + car()->peekSerialString();
    if (cdr()->isAtom()){
      serialString += ':' + cdr()->peekSerialString();
    }
    else if (cdr()->isNil()){
    }
    else{
      serialString += ',' + cdr()->peekSerialString();
    }
    serialString += '>';
    break;
  }
}

/* **************************************************
 *
 ************************************************** */
void
List::print(std::ostream& outStream) const
{
  switch (type){
  case NIL:
    outStream << "NIL";
    break;
  case ATOM:
    value->print(outStream);
    break;
  case PAIRP:
    car()->print(outStream);
    if (cdr()->isAtom()){
      outStream << "::";
      cdr()->print(outStream);
    }
    else if (!cdr()->isNil()){
      cdr()->print(outStream);
    }
    break;
  }
}

/* **************************************************
 *
 ************************************************** */
void
List::flatPrint(std::ostream& outStream, bool par) const
{
  switch (type){
  case NIL:
    outStream << "NIL";
    break;
  case ATOM:
    value->flatPrint(outStream);
    break;
  case PAIRP:
	    if (par || cdr()->isAtom()){
		outStream << "&lt;";
	    }
	    car()->flatPrint(outStream, true);
	    if (cdr()->isAtom()){
	      outStream << "::";
	      cdr()->flatPrint(outStream, true);
	    }
	    else if (!cdr()->isNil()){
	      outStream << ",";
	      cdr()->flatPrint(outStream, false);
	    }
	    if (par || cdr()->isAtom()){
	      outStream << "&gt;";
	    }
	    break;
  }
}

/* **************************************************
 *
 ************************************************** */
bool
List::buildEnvironment(environmentPtr environment, listPtr otherList, bool acceptToFilterNULLVariables, bool root)
{
  bool ret = true;
  /***
  std::cerr << "<H4>List::buildEnvironment</H4>" << std::endl;
  std::cerr << "<table border = \"1\"><tr><th>this</th><th>list</th><th>Environment</th></tr>";
  std::cerr << "<tr><td>";
  this->flatPrint(std::cerr, true);
  std::cerr << "</td><td>";
  otherList->flatPrint(std::cerr, true);
  std::cerr << "</td><td>";
  environment->print(std::cerr);
  std::cerr << "</td></tr></table>";
   ***/
  
  switch (this->type){
	  case NIL:
		  if (otherList->type == NIL){
			  ret=true;
		  }
		  else if ((otherList->type == ATOM) && (otherList->value->getType() == Value::VARIABLE)){
			  environment->add(otherList->value->getBits(), Value::NIL);
		  }
		  else {
			  ret = false;
		  }
		  break;
	  case ATOM:
		  if (this->value->getType() == Value::VARIABLE){
			  if (!otherList){
				  FATAL_ERROR;
			  } else {
				  switch (otherList->getType()){
					  case NIL:
						  environment->add(this->value->getBits(), Value::NIL);
						  break;
					  case ATOM:
						  environment->add(this->value->getBits(), otherList->getValue());
						  break;
					  case PAIRP:
						  environment->add(this->value->getBits(), Value::create(Value::LIST, otherList));
						  break;
				  }
			  }
		  }
		  else if (!otherList){
			  ret = false;
		  }
		  else if (otherList->getType() == ATOM){
			  if (otherList->value->getType() == Value::VARIABLE)
				  environment->add(otherList->value->getBits(), this->getValue());
			  else if (!this->value->buildEnvironment(environment, otherList->value, acceptToFilterNULLVariables, root))
				  ret = false;
		  }
		  else
			  ret = false;
		  break;
	  case PAIRP:
		  if (otherList->getType() == PAIRP) {
			  if ((this->car()->getType() == NIL) && (otherList->car()->getType() == NIL)) {
				  ret = true;
			  } else if (!this->car()->buildEnvironment(environment, otherList->car(), acceptToFilterNULLVariables, root)){
				  ret = false;
			  } else if ((this->cdr()->getType() == NIL) && (otherList->cdr()->getType() == NIL)) {
				  ret = true;
			  } else if (!this->cdr()->buildEnvironment(environment, otherList->cdr(), acceptToFilterNULLVariables, root)){
				  ret = false;
			  }
		  }
		  else
			  ret = false;
		  break;
  }

  /***
  std::cerr << "<H4>Result List::buildEnvironment</H4>" << std::endl;
  std::cerr << "<table border = \"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
  std::cerr << "<tr><td>" << (ret?"TRUE":"FALSE") << "</td><td>";
  environment->print(std::cerr);
  std::cerr << "</td></tr></table>";
   ***/
  return ret;
}

/* **************************************************
 *
 ************************************************** */
void
List::deleteAnonymousVariables()
{
  switch (type){
  case NIL:
    break;
  case ATOM:
    if (value)
      value->deleteAnonymousVariables();
    break;
  case PAIRP:
    car()->deleteAnonymousVariables();
    cdr()->deleteAnonymousVariables();
    break;
  }
}

/* **************************************************
 *
 ************************************************** */
bool
List::renameVariables(unsigned int i)
{
  bool effect = false;
  switch (type){
  case NIL:
    break;
  case ATOM:
    if (value)
      if (value->renameVariables(i)) effect = true;
    break;
  case PAIRP:
    if (car()->renameVariables(i)) effect = true;
    if (cdr()->renameVariables(i)) effect  =  true;
    break;
  }
  return effect;
}


#ifdef OUTPUT_XML
/* ************************************************************
 *                                                            *
 ************************************************************ */
void 
List::toXML(xmlNodePtr nodeRoot)
{
  xmlNodePtr l = xmlNewChild(nodeRoot, NULL, (const xmlChar*)"LIST", NULL);
  switch (type){
  case NIL:
    break;
  case ATOM:
    value->toXML(l);
    break;
  case PAIRP:
    car()->toXML(l);
    cdr()->toXML(l);
    break;
  }
}
#endif

/* **************************************************
 *
 ************************************************** */
listPtr 
List::clone() const
{
  switch (type){
  case NIL:
    return NILLIST;
    break;
  case ATOM:
    if (value)
      return create(value->clone());
    break;
  case PAIRP:
    return create(car()->clone(), cdr()->clone());
    break;
  }
  return listPtr();
}

/* ************************************************************
 * this < o
 ************************************************************ */
bool
List::subsumes(listPtr o, environmentPtr environment)
{
  /***
      BUG;
      this->print(std::cerr);
      std::cerr << " ";
      o->print(std::cerr);
      std::cerr << std::endl;
  ***/
  switch (type){
    // NIL < L
  case NIL:
    if (o->getType() != NIL)
      return false;
    break;
    // atom < L
  case ATOM:
    if (o->getType() != ATOM)
      return false;
    else if (!value->subsumes(o->getValue(), environment))
      return false;
    break;
    // (a1::a2) < L
  case PAIRP:
    if (o->getType() != PAIRP)
      return false;
    else if (!car()->subsumes(o->car(), environment))
      return false;
    else if (!cdr()->subsumes(o->cdr(), environment))
      return false;
    break;
  }
  return true;
}

/* **************************************************
 *
 ************************************************** */
listPtr 
List::pushFront(valuePtr value)
{
  switch (type){
  case NIL:
    WARNING_MSG("pushFront fails");
    break;
  case ATOM:
    WARNING_MSG("pushFront fails");
    break;
  case PAIRP:
    {
      listPtr n = create(create(value), shared_from_this());
      return n;
      break;
    }
  }
  return listPtr();
}

/* **************************************************
 *
 ************************************************** */
listPtr 
List::pushBack(valuePtr value)
{
  switch (type){
  case NIL:
    WARNING_MSG("pushFront fails");
    break;
  case ATOM:
    WARNING_MSG("pushFront fails");
    break;
  case PAIRP:
    {
      listPtr m = this->clone();
      listPtr n = m;
      while (n->cdr() != List::NILLIST)
	n = n->cdr();
      n->pairp.cdr = create(create(value), List::NILLIST);
      return m;
      break;
    }
  }
  return listPtr();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void 
List::enable(statementPtr root, itemPtr item, bool &effect, bool on)
{
  switch (type){
  case NIL:
    break;
  case ATOM:
    value->enable(root, item, effect, on);
    break;
  case PAIRP:
    if (car())
      car()->enable(root, item, effect, on);
    if (cdr())
      cdr()->enable(root, item, effect, on);
    break;
  }
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool 
List::findVariable(bitsetPtr variable)
{
  switch (type){
  case NIL:
    break;
  case ATOM:
    if (value->findVariable(variable))
      return true;
    break;
  case PAIRP:
    if (car() && car()->findVariable(variable))
      return true;
    if (cdr() && cdr()->findVariable(variable))
      return true;
    break;
  }
  return false;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void List::apply(itemPtr item, class Synthesizer *synthesizer, bool &result, bool &effect, bool trace, statementPtr variable, statementPtr body)
{
  switch (type){
  case NIL:
    break;
  case ATOM:
    value->apply(item, synthesizer, result, effect, trace, variable, body->clone(0));
    break;
  case PAIRP:
    if (car())
      car()->apply(item, synthesizer, result, effect, trace, variable, body);
    if (cdr())
      cdr()->apply(item, synthesizer, result, effect, trace, variable, body);
    break;
  }
}
