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

listPtr List::NIL_LIST = List::create();

/* **************************************************
 *
 ************************************************** */
List::List(enum List::Type type, valuePtr value, listPtr car, listPtr cdr)
      : Id(0) {
   this->type = type;
   this->value = value;
   this->pairp.car = car;
   this->pairp.cdr = cdr;
   //this->variable = 0;
   NEW;
}

/* **************************************************
 *
 ************************************************** */
List::~List() {
   DELETE;
   if (pairp.car)
      pairp.car.reset();
   if (pairp.cdr)
      pairp.cdr.reset();
}

/* **************************************************
 *
 ************************************************** */
listPtr List::create() {
   return listPtr(new List(List::NIL));
}

/* **************************************************
 *
 ************************************************** */
listPtr List::create(valuePtr value) {
   return listPtr(new List(List::ATOM, value));
}

/* **************************************************
 *
 ************************************************** */
listPtr List::create(listPtr car, listPtr cdr) {
   return listPtr(new List(List::PAIRP, valuePtr(), car, cdr));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
List::Type List::getType(void) const {
   return type;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void List::setType(Type type) {
   this->type = type;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
valuePtr List::getValue(void) const {
   return value;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void List::setValue(valuePtr value) {
   this->value = value;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
listPtr List::getCar(void) const {
   return this->pairp.car;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void List::setCar(listPtr car) {
   this->pairp.car = car;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
listPtr List::getCdr(void) const {
   return pairp.cdr;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void List::setCdr(listPtr cdr) {
   this->pairp.cdr = cdr;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
listPtr List::getCadr(void) const {
   return pairp.cdr->pairp.car;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
listPtr List::getCddr(void) const {
   return pairp.cdr->pairp.cdr;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
listPtr List::getCaar(void) const {
   return pairp.car->pairp.car;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
listPtr List::getCdar(void) const {
   return pairp.car->pairp.cdr;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool List::isNil(void) const {
   return (this->type == List::NIL);
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool List::isAtomic(void) const {
   return (this->type == List::ATOM);
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool List::isVariable(void) const {
   return (this->type == List::ATOM) && (this->value->isVariable());
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool List::isPairp(void) const {
   return (this->type == PAIRP);
}

/* **************************************************
 *
 ************************************************** */
void List::makeSerialString(void) {
   switch (type) {
      case NIL:
         serialString = 'N';
         break;
      case ATOM:
         serialString = value->peekSerialString();
         break;
      case PAIRP:
         serialString = '<' + pairp.car->peekSerialString();
         if (pairp.cdr->isAtomic()) {
            serialString += ':' + pairp.cdr->peekSerialString();
         }
         else if (pairp.cdr->isNil()) {
         }
         else {
            serialString += ',' + pairp.cdr->peekSerialString();
         }
         serialString += '>';
         break;
   }
}

/* **************************************************
 *
 ************************************************** */
void List::print(std::ostream& outStream) const {
   switch (type) {
      case NIL:
         outStream << "<>";
         break;
      case ATOM:
         value->print(outStream);
         break;
      case PAIRP:
         pairp.car->print(outStream);
         if (pairp.cdr->isAtomic()) {
            outStream << "::";
            pairp.cdr->print(outStream);
         }
         else if (!pairp.cdr->isNil()) {
            pairp.cdr->print(outStream);
         }
         break;
   }
}

/* **************************************************
 *
 ************************************************** */
void List::flatPrint(std::ostream& outStream, bool par) const {
   switch (type) {
      case NIL:
         outStream << "<>";
         break;

      case ATOM:
         value->flatPrint(outStream);
         break;

      case PAIRP:
         if (par || pairp.cdr->isAtomic()) {
            outStream << '<';
         }
         pairp.car->flatPrint(outStream, true);
         if (pairp.cdr->isAtomic()) {
            outStream << "::";
            pairp.cdr->flatPrint(outStream, true);
         }
         else if (!pairp.cdr->isNil()) {
            outStream << ",";
            pairp.cdr->flatPrint(outStream, false);
         }
         if (par || pairp.cdr->isAtomic()) {
            outStream << '>';
         }
         break;
   }
}

/* **************************************************
 *
 ************************************************** */
bool List::buildEnvironment(environmentPtr environment, listPtr otherList, bool acceptToFilterNULLVariables, bool root) {
   bool ret = true;
   /***
    std::cerr << "<H4>List::buildEnvironment</H4>" << std::endl;
    std::cerr << "<table border = \"1\"><tr><th>this</th><th>otherList</th><th>Environment</th></tr>";
    std::cerr << "<tr><td>";
    this->flatPrint(std::cerr, true);
    std::cerr << "</td><td>";
    otherList->flatPrint(std::cerr, true);
    std::cerr << "</td><td>";
    environment->print(std::cerr);
    std::cerr << "</td></tr></table>";
    ***/

   switch (this->type) {

      case NIL:
         if (otherList->isNil()) {
            ret = true;
         }
         else if ((otherList->isAtomic()) && (otherList->value->isVariable())) {
            environment->add(otherList->value->getBits(), Value::NIL_VALUE);
         }
         else {
            ret = false;
         }
         break;

      case ATOM:
         if (this->value->isVariable()) {
            if (!otherList) {
               UNEXPECTED
            }
            else {
               switch (otherList->getType()) {
                  case NIL:
                     environment->add(this->value->getBits(), Value::NIL_VALUE);
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
         else if (!otherList) {
            ret = false;
         }
         else if (otherList->isAtomic()) {
            if (otherList->value->isVariable())
               environment->add(otherList->value->getBits(), this->getValue());
            else if (!this->value->buildEnvironment(environment, otherList->value, acceptToFilterNULLVariables, root))
               ret = false;
         }
         else
            ret = false;
         break;

      case PAIRP:
         if (otherList->isPairp()) {
            if ((this->pairp.car->isNil()) && (otherList->pairp.car->isNil())) {
               ret = true;
            }
            else if (!this->pairp.car->buildEnvironment(environment, otherList->pairp.car, acceptToFilterNULLVariables, root)) {
               ret = false;
            }
            else if ((this->pairp.cdr->isNil()) && (otherList->pairp.cdr->isNil())) {
               ret = true;
            }
            else if (!this->pairp.cdr->buildEnvironment(environment, otherList->pairp.cdr, acceptToFilterNULLVariables, root)) {
               ret = false;
            }
         }
         else if (otherList->isAtomic()) {
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
void List::deleteAnonymousVariables() {
   switch (type) {
      case NIL:
         break;
      case ATOM:
         if (value)
            value->deleteAnonymousVariables();
         break;
      case PAIRP:
         pairp.car->deleteAnonymousVariables();
         pairp.cdr->deleteAnonymousVariables();
         break;
   }
}

/* **************************************************
 *
 ************************************************** */
bool List::_renameVariables(size_t i) {
   bool effect = false;
   switch (type) {
      case NIL:
         break;
      case ATOM:
         if (value)
            if (value->_renameVariables(i))
               effect = true;
         break;
      case PAIRP:
         if (pairp.car->_renameVariables(i))
            effect = true;
         if (pairp.cdr->_renameVariables(i))
            effect = true;
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
   switch (type) {
      case NIL:
      break;
      case ATOM:
      value->toXML(l);
      break;
      case PAIRP:
      pairp.car->toXML(l);
      pairp.cdr->toXML(l);
      break;
   }
}
#endif

/* **************************************************
 *
 ************************************************** */
listPtr List::clone() const {
   switch (type) {
      case NIL:
         return NIL_LIST;
         break;
      case ATOM:
         if (value)
            return create(value->clone());
         break;
      case PAIRP:
         return create(pairp.car->clone(), pairp.cdr->clone());
         break;
   }
   return listPtr();
}

/* ************************************************************
 * this < o
 ************************************************************ */
bool List::subsumes(listPtr o, environmentPtr environment) {
   /***
    BUG;
    this->print(std::cerr);
    std::cerr << " ";
    o->print(std::cerr);
    std::cerr << std::endl;
    ***/
   switch (type) {
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
         else if (!pairp.car->subsumes(o->pairp.car, environment))
            return false;
         else if (!pairp.cdr->subsumes(o->pairp.cdr, environment))
            return false;
         break;
   }
   return true;
}

/* **************************************************
 *
 ************************************************** */
listPtr List::pushFront(valuePtr value) {
   switch (type) {
      case NIL:
         WARNING("pushFront fails")
         break;
      case ATOM:
         WARNING("pushFront fails")
         break;
      case PAIRP: {
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
listPtr List::pushBack(valuePtr value) {
   switch (type) {
      case NIL:
         WARNING("pushBack fails")
         break;
      case ATOM:
         WARNING("pushBack fails")
         break;
      case PAIRP: {
         listPtr m = this->clone();
         listPtr n = m;
         while (n->pairp.cdr != List::NIL_LIST)
            n = n->pairp.cdr;
         n->pairp.cdr = create(create(value), List::NIL_LIST);
         return m;
         break;
      }
   }
   return listPtr();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void List::enable(statementPtr root, itemPtr item, Synthesizer *synthesizer, bool &effect, bool on) {
   switch (type) {
      case NIL:
         break;
      case ATOM:
         value->enable(root, item, synthesizer, effect, on);
         break;
      case PAIRP:
         if (pairp.car)
            pairp.car->enable(root, item, synthesizer, effect, on);
         if (pairp.cdr)
            pairp.cdr->enable(root, item, synthesizer, effect, on);
         break;
   }
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool List::findVariable(bitsetPtr variable) {
   switch (type) {
      case NIL:
         break;
      case ATOM:
         if (value->findVariable(variable))
            return true;
         break;
      case PAIRP:
         if (pairp.car && pairp.car->findVariable(variable))
            return true;
         if (pairp.cdr && pairp.cdr->findVariable(variable))
            return true;
         break;
   }
   return false;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void List::apply(itemPtr item, Parser &parser, Synthesizer *synthesizer, statementPtr variable, statementPtr body) {
   switch (type) {
      case NIL:
         break;
      case ATOM:
         value->apply(item, parser, synthesizer, variable, body->clone(0));
         break;
      case PAIRP:
         if (pairp.car)
            pairp.car->apply(item, parser, synthesizer, variable, body);
         if (pairp.cdr)
            pairp.cdr->apply(item, parser, synthesizer, variable, body);
         break;
   }
}

/* **************************************************
 *
 ************************************************** */
bool List::containsVariable(void) {
   /***
    std::cerr << "<H4>List::containsVariable</H4>" << std::endl;
    std::cerr << "<table border = \"1\"><tr><th>this</th></tr>";
    std::cerr << "<tr><td>";
    this->flatPrint(std::cerr, true);
    std::cerr << "</td><td>";
    std::cerr << "</td></tr></table>";
    ***/
   if (this->variableFlag.containsVariable())
      return true;
   bool result = false;
   switch (type) {
      case NIL:
         result = false;
         break;
      case ATOM:
         if (isVariable()) {
            result = true;
         }
         else if (this->getValue()->getFeatures()->containsVariable()) {
            result = true;
         }
         else {
            result = false;
         }
         break;
      case PAIRP:
         if (pairp.car->containsVariable() || pairp.cdr->containsVariable()) {
            result = true;
         }
         else {
            result = false;
         }
         break;
   }
   if (result)
      this->variableFlag.setFlag(VariableFlag::DOES_CONTAIN);
   else
      this->variableFlag.setFlag(VariableFlag::DOES_NOT_CONTAIN);
   /***
    std::cerr << "<H4>List::containsVariable done</H4>" << std::endl;
    std::cerr << (result ? "TRUE" : "FALSE");
    ***/
   return result;
}

/* **************************************************
 *
 ************************************************** */
void List::setVariableFlag(enum VariableFlag::flagValues flag) {
   this->variableFlag.setFlag(flag);
}
