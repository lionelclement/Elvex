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

#include <climits>
#include "feature.h"
#include "features.h"
#include "environment.h"
#include "value.h"
#include "messages.h"
#include "bitset.h"
#include "synthesizer.h"

featuresPtr Features::BOTTOM = createBottom();
featuresPtr Features::NIL = createNil();

/* **************************************************
 *
 ************************************************** */
Features::Features(featurePtr feature)
      : Id(0) {
   if (feature)
      features.push_front(feature);
   this->pred = 0;
   this->form = "";
   NEW;
}

/* **************************************************
 *
 ************************************************** */
Features::~Features() {
   DELETE;
   for (list::iterator j = features.begin(); j != features.end(); ++j) {
      featurePtr tmp = *j;
      if (tmp)
         tmp.reset();
   }
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr Features::create(featurePtr feature) {
   return featuresPtr(new Features(feature));
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr Features::createBottom(void) {
   featuresPtr fs = create();
   fs->addFlags(Flags::BOTTOM);
   return fs;
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr Features::createNil(void) {
   featuresPtr fs = create();
   fs->addFlags(Flags::NIL);
   return fs;
}

/* **************************************************
 *
 ************************************************** */
void Features::add(featurePtr feature, bool front) {
   if (front)
      this->features.push_front(feature);
   else
      this->features.push_back(feature);
}

/* **************************************************
 *
 ************************************************** */
void Features::add(featuresPtr features, bool front) {
   for (list::const_iterator j = features->begin(); j != features->end(); ++j)
      if (front)
         this->features.push_front(*j);
      else
         this->features.push_back(*j);
}

/* **************************************************
 *
 ************************************************** */
Features::list::iterator Features::erase(Features::list::iterator i) {
   return features.erase(i);
}

/* **************************************************
 *
 ************************************************** */
size_t Features::size(void) const {
   return features.size();
}

/* **************************************************
 *
 ************************************************** */
Features::list::iterator Features::begin(void) {
   return features.begin();
}

/* **************************************************
 *
 ************************************************** */
Features::list::iterator Features::end(void) {
   return features.end();
}

/* **************************************************
 *
 ************************************************** */
featurePtr Features::front(void) const {
   return *(features.begin());
}

/* **************************************************
 *
 ************************************************** */
bool Features::isNil(void) const {
   return isSetFlags(Flags::NIL);
}

/* **************************************************
 *
 ************************************************** */
bool Features::isBottom(void) const {
   return isSetFlags(Flags::BOTTOM);
}

/* **************************************************
 *
 ************************************************** */
void Features::print(std::ostream& outStream) const {
   if (isNil())
      outStream << "NIL";
   else if (isBottom())
      outStream << "⊥";
   else {
      outStream << "<TABLE border = \"1\">";
      outStream << "<TBODY align = \"left\"><TR><TD><TABLE border = \"0\">";
      if (features.size()) {
         for (int t = Feature::first_type; t <= Feature::last_type; ++t) {
            for (Features::list::const_iterator f = features.begin(); f != features.end(); ++f) {
               if ((*f)->getType() == t) {
                  outStream << "<TR>";
                  (*f)->print(outStream);
                  outStream << "</TR>";
               }
            }
         }
      }
      else {
         outStream << "<TR><TD></TD></TR>";
      }
      outStream << "</TABLE></TD></TR></TBODY>";
      outStream << "</TABLE>";
   }
}

/* **************************************************
 *
 ************************************************** */
void Features::flatPrint(std::ostream& outStream, bool par) const {
   if (isNil())
      outStream << "NIL";
   else if (isBottom())
      outStream << "⊥";
   else {
      if (par)
         outStream << '[';
      bool first = true;
      for (int t = Feature::first_type; t <= Feature::last_type; ++t) {
         for (Features::list::const_iterator f = features.begin(); f != features.end(); ++f) {
            if ((*f)->getType() == t) {
               if (first)
                  first = false;
               else
                  outStream << ',';
               (*f)->flatPrint(outStream);
            }
         }
      }
   }
   if (par)
      outStream << ']';
}

/* **************************************************
 *
 ************************************************** */
void Features::makeSerialString() {
   if (isNil())
      serialString = '#';
   else if (isBottom())
      serialString = '&';
   else {
      serialString = '[';
      if (features.size()) {
         bool first = true;
         for (Features::list::const_iterator f = features.begin(); f != features.end(); ++f) {
            if (first)
               first = false;
            else
               serialString += ',';
            serialString += (*f)->peekSerialString();
         }
      }
   }
}

/* **************************************************
 *
 ************************************************** */
unsigned int Features::assignPred() {
   unsigned int ret = UINT_MAX;
   if (this->pred)
      return this->pred;
   for (Features::list::const_iterator f = features.begin(); f != features.end(); ++f) {
      // […, PRED = …, …]
      if ((*f)->getType() == Feature::PRED) {
         ret = (*f)->getValue()->getIdentifier();
         break;
      }
   }
   this->pred = ret;
   return ret;
}

/* **************************************************
 *
 ************************************************** */
std::string Features::assignForm() {
   if (form.size() > 0)
      return form;
   for (Features::list::const_iterator f = features.begin(); f != features.end(); ++f) {
      if ((*f)->getType() == Feature::FORM) {
         form = (*f)->getValue()->getStr();
         return form;
      }
   }
   return std::string();
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Features::toXML(xmlNodePtr nodeRoot)
{
   xmlNodePtr f = xmlNewChild(nodeRoot, NULL, (const xmlChar*)"FS", NULL);
   xmlSetProp(f, (xmlChar*)"id", (xmlChar*)std::to_string(this->getId()).c_str());
   if (features.size())
   for (Features::list::const_iterator i = features.begin();
         i != features.end();
         ++i)
   (*i)->toXML(f);
}
#endif

/* **************************************************
 *
 ************************************************** */
featuresPtr Features::clone(void) const {
   if (isNil())
      return NIL;
   if (isBottom())
      return BOTTOM;
   featuresPtr result = Features::create();
   for (Features::list::const_iterator i = features.begin(); i != features.end(); ++i)
      result->features.push_back((*i)->clone());
   result->pred = pred;
   result->form = form;
   return result;
}

/* **************************************************
 *
 ************************************************** */
valuePtr Features::find(bitsetPtr code) const {
   for (Features::list::const_iterator i1 = features.begin(); i1 != features.end(); ++i1) {
      if (((*(*i1)->getAttribute()) & *code).any()) {
         return (*i1)->getValue();
      }
   }
   return valuePtr();
}

/* **************************************************
 *
 ************************************************** */
bool Features::buildEnvironment(environmentPtr environment, featuresPtr features, bool acceptToFilterNULLVariables, bool root) {
   bool ret = true;
   //	if (environment){
   //		bool effect  =  false;
   //		CERR_LINE;
   //		//environment->replaceVariables(shared_from_this(), effect);
   //		//environment->replaceVariables(features, effect);
   //	}

   /***
    if (root) {
    CERR_LINE;
    std::cerr << "<H4>Features::buildEnvironment</H4>" << std::endl;
    std::cerr << "<table border = \"1\"><tr><th>this</th><th>features</th><th>Environment</th></tr>";
    std::cerr << "<tr><td>";
    print(std::cerr);
    std::cerr << "</td><td>";
    if (features)
    features->print(std::cerr);
    else
    std::cerr << "NULL";
    std::cerr << "</td><td>";
    environment->print(std::cerr);
    std::cerr << "</td></tr></table>";
    }
    ***/

   // Traite tous les attributs constants
   for (Features::list::const_iterator i1 = begin(); i1 != end(); ++i1) {
      if (((*i1)->getType() == Feature::PRED) || ((*i1)->getType() == Feature::CONSTANT)) {
         Features::list::const_iterator i2 = features->begin();
         while (i2 != features->end()) {
            // Si deux constantes matchent
            // ou deux PRED matchent
            if ((((*i2)->getType() == Feature::CONSTANT) && ((*i1)->getType() == Feature::CONSTANT) && ((*(*i1)->getAttribute() & *(*i2)->getAttribute()).any()))
                  || (((*i1)->getType() == Feature::PRED) && ((*i2)->getType() == Feature::PRED))) {
               (*i2)->addFlags(Flags::SEEN);
               // Si les deux valeurs sont NIL
               if (((*i1)->getValue()->isNil()) && ((*i2)->getValue()->isNil())) {
               }
               // Si les deux valeurs sont TRUE
               else if (((*i1)->getValue()->isTrue()) && ((*i2)->getValue()->isTrue())) {
               }
               // Si l'une des deux est ANONYMOUS
               //else if (((*i1)->getValue()->isAnonymous()) || ((*i2)->getValue()->isAnonymous())) {
               //}
               // Sinon on construit l'environnement avec les deux valeurs
               else if (!(*i1)->getValue()->buildEnvironment(environment, (*i2)->getValue(), acceptToFilterNULLVariables, false)) {
                  ret = false;
               }
               break;
            }
            ++i2;
         }
         // Trait i1 inexistant
         if (i2 == features->end()) {
            // i1: a = $X
            if (((*i1)->getType() == Feature::CONSTANT) || (*i1)->getType() == Feature::PRED) {
               if ((*i1)->getValue()->getType() == Value::VARIABLE) {
                  //  = > $X = NIL
                  if (acceptToFilterNULLVariables) {
                     environment->add((*i1)->getValue()->getBits(), Value::ANONYMOUS_VALUE);
                  }
                  else {
                     ret = false;
                  }
               }
               else if ((*i1)->getValue()->isNil()) {
               }
               // i1: a = ...
               else {
                  if (!acceptToFilterNULLVariables) {
                     ret = false;
                  }
                  else {
                     if (!(*i1)->getValue()->buildEnvironment(environment, Value::ANONYMOUS_VALUE, acceptToFilterNULLVariables, false)) {
                        ret = false;
                     }
                  }
               }
            }
         }
      }
   }

   // traite les variables de structures
   for (Features::list::const_iterator i1 = begin(); i1 != end(); ++i1) {
      // i1: X
      if ((*i1)->getType() == Feature::VARIABLE) {
         if ((*i1)->getValue()) {
            throw "*** error: A variable attribute is not allowed in this context: " + (*i1)->getAttribute()->toString();
            //if (!(*i1)->getValue()->buildEnvironment(environment, (*i2)->getValue(), acceptToFilterNULLVariables, false)){
            //ret = false;
            //}
            featuresPtr nFeatures = Features::create();
            Features::list::const_iterator i2 = features->begin();
            while (i2 != features->end()) {
               if ((*i2)->isUnsetFlags(Flags::SEEN)) {
                  (*i2)->addFlags(Flags::SEEN);
                  nFeatures->add(*i2);
               }
               ++i2;
            }
            //environment->add((*i1)->getAttribute(), new Value(nFeatures, Value::FEATURES));
         }
         else {
            featuresPtr nFeatures = Features::create();
            Features::list::const_iterator i2 = features->begin();
            while (i2 != features->end()) {
               if ((*i2)->isUnsetFlags(Flags::SEEN)) {
                  (*i2)->addFlags(Flags::SEEN);
                  nFeatures->add(*i2);
               }
               ++i2;
            }
            environment->add((*i1)->getAttribute(), Value::create(Value::FEATURES, nFeatures));
         }
      }
   }
   features->subFlags(Flags::SEEN);

   /*** 
    if (root) {
    std::cerr << "<H4>Result Features::buildEnvironment</H4>" << std::endl;
    std::cerr << "<table border = \"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
    std::cerr << "<tr><td>" << (ret?"TRUE":"FALSE") << "</td><td>";
    environment->print(std::cerr);
    std::cerr << "</td></tr></table>";
    }
    ***/
   return ret;
}

/* **************************************************
 *true if this subsumes o
 *if it does, change variables in this
 ************************************************** */
bool Features::subsumes(featuresPtr o, environmentPtr environment) {
   /***
    CERR_LINE;
    cerr << "<DIV>";
    cerr << "Subsumes (" << this << ")";
    cst	err << "<TABLE><TR>";
    cerr << "<TD>";
    this->print(cerr);
    cerr << "</TD><TD>&lt;</TD><TD>";
    o->print(cerr);
    cerr << "</TD>";
    cerr << "</TR></TABLE>";
    cerr << "</DIV>";
    ***/

   bool ret = true;
   // NIL < NIL
   if (isNil() && o->isNil()) {
      // OK
   }

   // NIL < […]
   // […] < NIL
   else if (isNil() || o->isNil()) {
      ret = false;
   }
   // ⊥ < […]
   // […] < ⊥
   else if (isBottom() || o->isBottom()) {
      ret = false;
   }
   else {
      Features::list::const_iterator i1;
      Features::list::const_iterator i2;
      for (i1 = begin(); i1 != end(); ++i1) {
         for (i2 = o->begin(); i2 != o->end(); ++i2) {
            // [PRED:X]  < [PRED:Y]
            // [att:X] < [att:Y]
            // X < Y
            if ((((*i1)->getType() == Feature::PRED) && ((*i2)->getType() == Feature::PRED))
                  || (((*i1)->getType() == Feature::CONSTANT) && ((*i2)->getType() == Feature::CONSTANT) && ((*(*i1)->getAttribute() & *(*i2)->getAttribute()).any()))) {
               valuePtr v1 = (*i1)->getValue();
               valuePtr v2 = (*i2)->getValue();
               if (!v1->subsumes(v2, environment)) {
                  ret = false;
               }
               break;
            }
         }
      }
   }
   /***
    cerr << "<DIV>";
    cerr << "result: (" << shared_from_this() << ")";
    cerr << (ret?"true":"false") << endl;
    //environment->print(cerr);
    cerr << "</DIV>";
    ***/
   return ret;
}

/* **************************************************
 *
 ************************************************** */
void Features::subFlags(const std::bitset<FLAGS>& flags) {
   for (Features::list::const_iterator i = begin(); i != end(); ++i)
      (*i)->subFlags(flags);
}

/* **************************************************
 *
 ************************************************** */
bool Features::renameVariables(size_t i) {
   bool effect = false;
   for (Features::list::iterator feature = features.begin(); feature != features.end(); ++feature) {
      if ((*feature)->renameVariables(i))
         effect = true;
   }
   if (effect)
      resetSerial();
   return effect;
}

/* **************************************************
 *
 ************************************************** */
void Features::enable(statementPtr root, itemPtr item, Synthesizer *synthesizer, bool &effect, bool on) {
   for (Features::list::iterator feature = features.begin(); feature != features.end(); ++feature)
      (*feature)->enable(root, item, synthesizer, effect, on);
}

/* **************************************************
 *
 ************************************************** */
void Features::deleteAnonymousVariables() {
   redo: for (Features::list::iterator feature = features.begin(); feature != features.end(); ++feature) {
      switch ((*feature)->getType()) {
         case Feature::FORM:
         case Feature::PRED:
         case Feature::VARIABLE:
         case Feature::CONSTANT:
            if ((*feature)->getValue()) {
               (*feature)->getValue()->deleteAnonymousVariables();
               if ((*feature)->getValue() && ((*feature)->getValue()->isAnonymous())) {
                  features.erase(feature);
                  goto redo;
                  return;
               }
            }
            break;
      }
   }
}

/* **************************************************
 *
 ************************************************** */
bool Features::findVariable(bitsetPtr variable) {
   for (Features::list::iterator feature = features.begin(); feature != features.end(); ++feature)
      if ((*feature)->findVariable(variable))
         return true;
   return false;
}

/* **************************************************
 *
 ************************************************** */
bool Features::containsVariable(void) {
   bool result = false;
   if (variableFlag.containsVariable())
      return true;
   for (Features::list::const_iterator iterator = features.begin(); iterator != features.end(); ++iterator) {
      if ((*iterator)->containsVariable()) {
         result = true;
      }
   }
   if (result)
      variableFlag.setFlag(VariableFlag::DOES_CONTAIN);
   else
      variableFlag.setFlag(VariableFlag::DOES_NOT_CONTAIN);
   return result;
}

/* **************************************************
 *
 ************************************************** */
void Features::setVariableFlag(enum VariableFlag::flagValues flag) {
   this->variableFlag.setFlag(flag);
}
