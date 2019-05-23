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

#include <climits>
#include "feature.hh"
#include "features.hh"
#include "environment.hh"
#include "value.hh"
#include "messages.hh"
#include "bitset.hh"

featuresPtr Features::_bottom = createBottom();
featuresPtr Features::_nil = createNil();

/* **************************************************
 *
 ************************************************** */
Features::Features(featurePtr feature)
{
  NEW;
  if (feature)
    features.push_front(feature);
  this->pred=0;
  this->form="";
}

/* **************************************************
 *
 ************************************************** */
Features::~Features()
{
   for (listFeatures::iterator j = features.begin();
        j != features.end();
        ++j) {
     featurePtr tmp = *j;
     if (tmp)
       tmp.reset();
   }
   DELETE;
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr Features::create(featurePtr feature)
{
  return featuresPtr(new Features(feature));
}

/* **************************************************
 *
 ************************************************** */
void Features::setId(idType id)
{
  FATAL_ERROR;
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr Features::createBottom(void)
{
  featuresPtr fs = create();
  fs->setFlags(Flags::BOTTOM);
  return fs;
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr Features::createNil(void)
{
  featuresPtr fs = create();
  fs->setFlags(Flags::NIL);
  return fs;
}

/* **************************************************
 *
 ************************************************** */
void Features::addFeature(featurePtr feature, bool front)
{
  if (front)
    this->features.push_front(feature);
  else
    this->features.push_back(feature);
}

/* **************************************************
 *
 ************************************************** */
void Features::addFeatures(featuresPtr features, bool front)
{
  for (listFeatures::const_iterator j=features->begin();
       j!=features->end();
       j++)
    if (front)
      this->features.push_front(*j);
    else
      this->features.push_back(*j);
}

/* **************************************************
 *
 ************************************************** */
Features::listFeatures::iterator Features::erase(Features::listFeatures::iterator i)
{
  return features.erase(i);
}

/* **************************************************
 *
 ************************************************** */
const size_t Features::size(void) const
{
  return features.size();
}

/* **************************************************
 *
 ************************************************** */
Features::listFeatures::iterator Features::begin(void)
{
  return features.begin();
}

/* **************************************************
 *
 ************************************************** */
Features::listFeatures::iterator Features::end(void)
{
  return features.end();
}

/* **************************************************
 *
 ************************************************** */
featurePtr Features::front(void) const
{
  return *(features.begin());
}

/* **************************************************
 *
 ************************************************** */
const bool Features::isNil(void) const
{
  return isSetFlags(Flags::NIL);
}

/* **************************************************
 *
 ************************************************** */
const bool Features::isBottom(void) const
{
  return isSetFlags(Flags::BOTTOM);
}

/* **************************************************
 *
 ************************************************** */
void
Features::print(std::ostream& outStream, bool par, bool flat) const
{
  if (isNil())
    outStream << "NIL";
  else if (isBottom())
    outStream << "⊥";
  else {
    if (flat && par)
      outStream << "[";
    else if (par) {
      outStream << "<TABLE border=\"1\">";
      outStream << "<TBODY align=\"left\"><TR><TD><TABLE border=\"0\">";
    }
    if (features.size()){
      bool first=true;
      for (int t=Feature::first_type ; t <= Feature::last_type ; t++){
	for (Features::listFeatures::const_iterator f=features.begin();
	     f!=features.end();
	     f++){
	  if ((*f)->getType()==t){
	    if (flat){
	      if (first) first=false; else outStream << ", ";
	    }
	    else if (par) {
	      outStream << "<TR>";
	    }
	    (*f)->print(outStream, flat);
	    if (!flat && par){
	      outStream << "</TR>";
	    }
	  }
	}
      }
    }
    else {
      if (!flat && par)
	outStream << "<TR><TD></TD></TR>";
    }
    if (flat && par)
      outStream << "]";
    else if (par) 
      outStream << "</TABLE></TD></TR></TBODY></TABLE>";
  }
}

/* **************************************************
 *
 ************************************************** */
const std::string
Features::makeSerializationId()
{
  if (isNil())
    serialId = '#';
  else if (isBottom())
    serialId = '&';
  else {
    serialId = '[';
    if (features.size()){
      bool first=true;
      for (Features::listFeatures::const_iterator f = features.begin();
	   f != features.end();
	   ++f){
	if (first) first=false; else serialId += ',';
	serialId += (*f)->serialize();
      }
    }
  }
  return serialId;
}

/* **************************************************
 *
 ************************************************** */
const unsigned int
Features::assignPred()
{
  int ret = UINT_MAX;
  if (this->pred)
    return this->pred;
  for (Features::listFeatures::const_iterator f = features.begin();
       f != features.end();
       ++f) {
    // […, PRED=…, …]
    if ((*f)->getType()==Feature::PRED) {
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
std::string
Features::assignForm()
{
  if (form.size()>0)
    return form;
  for (Features::listFeatures::const_iterator f=features.begin();
       f!=features.end();
       f++){
    if ((*f)->getType()==Feature::FORM){
      form=(*f)->getValue()->getStr();
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
  xmlNodePtr f=xmlNewChild(nodeRoot, NULL, (const xmlChar*)"FS", NULL);
  xmlSetProp(f, (xmlChar*)"id", (xmlChar*)std::to_string(this->getId()).c_str());
  if (features.size())
    for (Features::listFeatures::const_iterator i=features.begin();
	 i!=features.end();
	 i++)
      (*i)->toXML(f);
}
#endif

/* **************************************************
 *
 ************************************************** */
featuresPtr
Features::clone(void)
{
  if (isNil() || isBottom())
    return shared_from_this();
  featuresPtr result=Features::create();
  for (Features::listFeatures::const_iterator i=features.begin();
       i!=features.end();
       i++)
    result->features.push_back((*i)->clone());
  result->pred=pred;
  result->form=form;
  return result;
}

/* **************************************************
 *
 ************************************************** */
valuePtr 
Features::find(bitsetPtr code) const
{
  for (Features::listFeatures::const_iterator i1=features.begin();
       i1!=features.end();
       i1++){
    if (((*(*i1)->getAttribute()) & *code).any()){
      return (*i1)->getValue();
    }
  }
  return valuePtr();
}

/* **************************************************
 *
 ************************************************** */
const bool
Features::buildEnvironment(environmentPtr environment, featuresPtr features, bool acceptToFilterNULLVariables, bool root)
{
  bool ret=true;
  if (environment){
    bool effect = false;
    environment->replaceVariables(shared_from_this(), effect);
    environment->replaceVariables(features, effect);
  }

  /*** 
  if (root) {
    CERR_LINE;
    std::cerr << "<H4>Features::buildEnvironment</H4>" << std::endl;
    std::cerr << "<table border=\"1\"><tr><th>this</th><th>features</th><th>Environment</th></tr>";
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
  for (Features::listFeatures::const_iterator i1=begin();
       i1!=end();
       ++i1){
    if (((*i1)->getType()==Feature::PRED)
	|| ((*i1)->getType()==Feature::CONSTANT)){
      Features::listFeatures::const_iterator i2=features->begin();
      while(i2!=features->end()){
	// Si deux constantes matchent
	// ou deux PRED matchent
	if ((((*i2)->getType()==Feature::CONSTANT) && ((*i1)->getType()==Feature::CONSTANT) && ((*(*i1)->getAttribute() & *(*i2)->getAttribute()).any()))
	    || (((*i1)->getType()==Feature::PRED) && ((*i2)->getType()==Feature::PRED))){
	  (*i2)->addFlags(SEEN);
	  // Si les deux valeurs sont NIL
	  if (((*i1)->getValue()->isNil()) && ((*i2)->getValue()->isNil())){
	  }
	  // Si les deux valeurs sont TRUE
	  else if (((*i1)->getValue()->isTrue()) && ((*i2)->getValue()->isTrue())){
	  }
	  // Si l'une des deux est ANONYMOUS
	  else if (((*i1)->getValue()->isAnonymous()) || ((*i2)->getValue()->isAnonymous())){
	  }
	  // Sinon on construit l'environnement avec les deux valeurs
	  else if (!(*i1)->getValue()->buildEnvironment(environment, (*i2)->getValue(), acceptToFilterNULLVariables, false)){
	    ret=false;
	  }
	  break;
	}
	i2++;
      }
      // Trait i1 inexistant
      if (i2==features->end()){
	// i1: a=$X
	if (((*i1)->getType()==Feature::CONSTANT) || (*i1)->getType()==Feature::PRED) {
	  if ((*i1)->getValue()->getType()==Value::VARIABLE){
	    // => $X=NIL
	    if (acceptToFilterNULLVariables){
	      environment->add((*i1)->getValue()->getBits(), Value::_anonymous);
	    }
	    else {
	      ret=false;
	    }
	  }
	  else if ((*i1)->getValue()->isNil()){
	  }
	  // i1: a=...
	  else {
	    if (!acceptToFilterNULLVariables){
	      ret=false;
	    }
	  }
	}
      }
    }
  }

  // traite les variables de structures
  for (Features::listFeatures::const_iterator i1=begin();
       i1!=end();
       ++i1){
    // i1: X
    if ((*i1)->getType()==Feature::VARIABLE){
      if ((*i1)->getValue()){
	throw "A variable attribute is not allowed in this context";
	//if (!(*i1)->getValue()->buildEnvironment(environment, (*i2)->getValue(), acceptToFilterNULLVariables, false)){
	//ret=false;
	//}
	featuresPtr nFeatures=Features::create();
	Features::listFeatures::const_iterator i2=features->begin();
	while(i2!=features->end()){
	  if ((*i2)->isUnsetFlags(Flags::SEEN)){
	    (*i2)->addFlags(Flags::SEEN);
	    nFeatures->addFeature(*i2);
	  }
	  i2++;
	}
	//environment->add((*i1)->getAttribute(), new Value(nFeatures, Value::FEATURES));
      }
      else {
	featuresPtr nFeatures=Features::create();
	Features::listFeatures::const_iterator i2=features->begin();
	while(i2!=features->end()){
	  if ((*i2)->isUnsetFlags(Flags::SEEN)){
	    (*i2)->addFlags(Flags::SEEN);
	    nFeatures->addFeature(*i2);
	  }
	  i2++;
	}
	environment->add((*i1)->getAttribute(), Value::create(Value::FEATURES, nFeatures));
      }
    }
  }
  features->subFlags(SEEN);

  /***
  if (root) {
    std::cerr << "<H4>Result Features::buildEnvironment</H4>" << std::endl;
    std::cerr << "<table border=\"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
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
const bool
Features::subsumes(featuresPtr o, environmentPtr environment)
{
  /***
      CERR_LINE;
      cerr << "<DIV>";
      cerr << "Subsumes (" << this << ")";
      cerr << "<TABLE><TR>";
      cerr << "<TD>";
      this->print(cerr);
      cerr << "</TD><TD>&lt;</TD><TD>";
      o->print(cerr);
      cerr << "</TD>";
      cerr << "</TR></TABLE>";
      cerr << "</DIV>";
  ***/

  bool ret=true;
  // NIL < NIL
  if (isNil() && o->isNil()){
    // OK
  }

  // NIL < […]
  // […] < NIL
  else if (isNil() || o->isNil()){
    ret=false;
  }
  // ⊥ < […]
  // […] < ⊥
  else if (isBottom() || o->isBottom()){
    ret=false;
  }
  else {
    Features::listFeatures::const_iterator i1;
    Features::listFeatures::const_iterator i2;
    for (i1=begin(); i1!=end(); i1++){
      for (i2=o->begin(); i2!=o->end(); i2++){
	// [PRED:X]  < [PRED:Y]
	// [att:X] < [att:Y]
	// X < Y
	if ((((*i1)->getType()==Feature::PRED) && ((*i2)->getType()==Feature::PRED))
	    || (((*i1)->getType()==Feature::CONSTANT) && ((*i2)->getType()==Feature::CONSTANT) && ((*(*i1)->getAttribute() & *(*i2)->getAttribute()).any()))){
	  valuePtr v1=(*i1)->getValue();
	  valuePtr v2=(*i2)->getValue();
	  if (!v1->subsumes(v2, environment)){
	    ret=false;
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
void
Features::subFlags(const std::bitset<NBRFLAGS>& flags)
{
  for (Features::listFeatures::const_iterator i=begin();
       i!=end();
       i++)
    (*i)->subFlags(flags);
}

/* **************************************************
 *
 ************************************************** */
const bool
Features::renameVariables(unsigned int i)
{
  bool effect=false;
  for (Features::listFeatures::iterator feature=features.begin(); feature!=features.end(); feature++)
    if ((*feature)->renameVariables(i)) effect=true;
  resetSerialId();
  return effect;
}

/* **************************************************
 *
 ************************************************** */
void
Features::enable(statementPtr root, itemPtr item, bool &effect, bool on)
{
  for (Features::listFeatures::iterator feature=features.begin(); feature!=features.end(); feature++)
    (*feature)->enable(root, item, effect, on);
}

/* **************************************************
 *
 ************************************************** */
void
Features::deleteAnonymousVariables()
{
 redo:
  for (Features::listFeatures::iterator feature=features.begin(); feature!=features.end(); feature++){
    switch ((*feature)->getType()){
    case Feature::FORM:
    case Feature::PRED:
    case Feature::VARIABLE:
    case Feature::CONSTANT:
      if ((*feature)->getValue()){
	(*feature)->getValue()->deleteAnonymousVariables();
	if ((*feature)->getValue() && ((*feature)->getValue()->isAnonymous())){
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
const bool
Features::findVariable(bitsetPtr variable)
{
  for (Features::listFeatures::iterator feature=features.begin(); feature!=features.end(); feature++)
    if ((*feature)->findVariable(variable))
      return true;
  return false;
}

