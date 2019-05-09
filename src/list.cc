/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2018 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: Lionel Clément,
 * Labri -- 351, cours de la Libération
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

listPtr List::nil=List::create();
bitsetPtr List::gwith;

/* **************************************************
 *
 ************************************************** */
List::List(enum List::Type type, valuePtr value, listPtr car, listPtr cdr)
{
  NEW;
  this->type=type;
  this->value=value;
  this->pairp.car=car;
  this->pairp.cdr=cdr;
}

/* **************************************************
 *
 ************************************************** */
List::~List()
{
  //DELETE;
}

/* **************************************************
 *
 ************************************************** */
void List::setId(idType id)
{
  FATAL_ERROR;
}

/* **************************************************
 *
 ************************************************** */
listPtr List::create()
{
  return shared_ptr< class List >( new List(List::NIL) );
}

/* **************************************************
 *
 ************************************************** */
listPtr List::create(valuePtr value)
{
  return shared_ptr< class List >( new List(List::ATOM, value) );
}

/* **************************************************
 *
 ************************************************** */
listPtr List::create(listPtr car, listPtr cdr)
{
  return shared_ptr< class List >( new List(List::PAIRP, valuePtr(), car, cdr) );
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
  this->value=value;
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
  return (this->type==List::NIL);
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool List::isAtom(void) const 
{
  return (this->type==List::ATOM);
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool List::isPairp(void) const 
{
  return (this->type==PAIRP);
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
int
List::getIdentifier(void) const
{
  return value->getIdentifier();
}

/* **************************************************
 *
 ************************************************** */
const std::string
List::makeSerializationId(void)
{
  switch (type){
  case NIL:
    serialId = 'N';
    break;
  case ATOM:
    serialId = value->serialize();
    break;
  case PAIRP:
    serialId = '<';
    serialId += car()->serialize();
    if (cdr()->isAtom()){
      serialId += ':';
      serialId += cdr()->serialize();
    }
    else if (cdr()->isNil()){
    }
    else{
      serialId += ',';
      serialId += cdr()->serialize();
    }
    serialId += '>';
    break;
  }
  return serialId;
}

/* **************************************************
 *
 ************************************************** */
void
List::print(std::ostream& outStream, bool par, bool flat) const
{
  switch (type){
  case NIL:
    outStream << "&lt;&gt;";
    break;
  case ATOM:
    value->print(outStream, true, flat);
    break;
  case PAIRP:
    if (par || cdr()->isAtom()){
      outStream << "&lt;";
    }
    car()->print(outStream, true, flat);
    if (cdr()->isAtom()){
      outStream << "::";
      cdr()->print(outStream, true, flat);
    }
    else if (cdr()->isNil()){
    }
    else{
      outStream << ",";
      cdr()->print(outStream, false, flat);
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
List::buildEnvironment(environmentPtr environment, listPtr list, bool acceptToFilterNULLVariables, bool root)
{
  bool ret=true;
  /***
      cerr << "<H4>List::buildEnvironment</H4>" << endl;
      cerr << "<table border=\"1\"><tr><th>this</th><th>list</th><th>Environment</th></tr>";
      cerr << "<tr><td>";
      this->print(cerr);
      cerr << "</td><td>";
      list->print(cerr);
      cerr << "</td><td>";
      environment->print(cerr);
      cerr << "</td></tr></table>";
  ***/

  switch (this->type){
  case NIL:
    break;
  case ATOM:
    if (this->value->getType()==Value::VARIABLE){
      if (list){
	switch (list->getType()){
	case NIL:
	  environment->add(this->value->getBits(), Value::_nil);
	  break;
	case ATOM:
	  environment->add(this->value->getBits(), list->getValue());
	  break;
	case PAIRP:
	  environment->add(this->value->getBits(), Value::create(Value::LIST, list));
	  break;
	}
      }
      else {
	FATAL_ERROR;
      }
    }
    else if (!list){
      ret=false;
    }
    else if (list->getType()==ATOM){
      if (list->value->getType()==Value::VARIABLE)
	environment->add(list->value->getBits(), this->getValue());
      else if (!this->value->buildEnvironment(environment, list->value, acceptToFilterNULLVariables, root))
	ret=false;
    }
    else
      ret=false;
    break;
  case PAIRP:
    if (list->getType()==PAIRP){
      if (!this->car()->buildEnvironment(environment, list->car(), acceptToFilterNULLVariables, root)){
	ret=false;
	break;
      }
      if (!this->cdr()->buildEnvironment(environment, list->cdr(), acceptToFilterNULLVariables, root)){
	ret=false;
      }
    }
    else
      ret=false;
    break;
  }
  /***
      cerr << "<H4>Result List::buildEnvironment</H4>" << endl;
      cerr << "<table border=\"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
      cerr << "<tr><td>" << (ret?"TRUE":"FALSE") << "</td><td>";
      environment->print(cerr);
      cerr << "</td></tr></table>";
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
  bool effect=false;
  switch (type){
  case NIL:
    break;
  case ATOM:
    if (value)
      if (value->renameVariables(i)) effect=true;
    break;
  case PAIRP:
    if (car()->renameVariables(i)) effect=true;
    if (cdr()->renameVariables(i)) effect = true;
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
  xmlNodePtr l=xmlNewChild(nodeRoot, NULL, (const xmlChar*)"LIST", NULL);
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
List::clone()
{
  switch (type){
  case NIL:
    return nil;
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
 *                                                            *
 ************************************************************ */
bool 
List::compare_values (valuePtr v1, valuePtr v2)
{
  if ((v1->getType()==Value::FEATURES)
      &&(v2->getType()==Value::FEATURES)){
    valuePtr va1=v1->getFeatures()->find(gwith);
    valuePtr va2=v2->getFeatures()->find(gwith);
    if ((va1->getType()==Value::CONSTANT)
	&& (va2->getType()==Value::CONSTANT)){
      if (va1->getBits()->toString() < va2->getBits()->toString())
	return true;
      else
	return false;
    }
    else
      FATAL_ERROR;
  }
  else if ((v1->getType()==Value::DOUBLE)
	   &&(v2->getType()==Value::DOUBLE)){
    if (v1->getDouble() < v2->getDouble())
      return true;
    else
      return false;
  }
  else
    FATAL_ERROR;
  return false;
}

/* **************************************************
 *
 ************************************************** */
void
List::sort(bitsetPtr with)
{
  /***
      cerr << "<H4>List::sort</H4>" << endl;
      cerr << "<table border=\"1\"><tr><th>this</th><th>with</th></tr>";
      cerr << "<tr><td>";
      this->print(cerr);
      cerr << "</td><td>";
      cerr << Vartable::bitsToStr(*with);
      cerr << "</td></tr></table>";
  ***/
  std::list<valuePtr >lst;
  listPtr l=shared_from_this();
  while(l
	&& l->getType()==PAIRP
	&& l->car()->getType()==ATOM){
    lst.push_back(l->car()->getValue());
    l=l->cdr();
  }
  gwith=with;
  lst.sort(compare_values);
  l=shared_from_this();
  while(l
	&& l->getType()==PAIRP
	&& l->car()->getType()==ATOM){
    l->car()->setValue(lst.front());
    lst.pop_front();
    l=l->cdr();
  }
  /***
      cerr << "<H4>List::sort result</H4>" << endl;
      cerr << "<table border=\"1\"><tr><th>this</th></tr>";
      cerr << "<tr><td>";
      this->print(cerr);
      cerr << "</td></tr></table>";
  ***/
}

/* **************************************************
 *
 ************************************************** */
void
List::reverse()
{
  std::list<valuePtr >lst;
  listPtr l=shared_from_this();
  while(l
	&& l->getType()==PAIRP
	&& l->car()->getType()==ATOM){
    lst.push_back(l->car()->getValue());
    l=l->cdr();
  }
  lst.reverse();
  l=shared_from_this();
  while(l
	&& l->getType()==PAIRP
	&& l->car()->getType()==ATOM){
    l->car()->setValue(lst.front());
    lst.pop_front();
    l=l->cdr();
  }
}

/* ************************************************************
 * this < o
 ************************************************************ */
bool
List::subsumes(listPtr o, environmentPtr environment)
{
  /***
      BUG;
      this->print(cerr);
      cerr << " ";
      o->print(cerr);
      cerr << endl;
  ***/
  switch (type){
    // NIL < L
  case NIL:
    if (o->getType()!=NIL)
      return false;
    break;
    // atom < L
  case ATOM:
    if (o->getType()!=ATOM)
      return false;
    else if (!value->subsumes(o->getValue(), environment))
      return false;
    break;
    // (a1::a2) < L
  case PAIRP:
    if (o->getType()!=PAIRP)
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
      listPtr n=create(create(value), shared_from_this());
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
      listPtr m=this->clone();
      listPtr n=m;
      while (n->cdr()!=List::nil)
	n=n->cdr();
      n->pairp.cdr=create(create(value), List::nil);
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
