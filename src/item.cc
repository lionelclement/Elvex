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

#include "item.hh"
#include "environment.hh"
#include "messages.hh"
#include "forest.hh"
#include "entry.hh"
#include "forestidentifier.hh"
#include "itemset.hh"
#include "ipointer.hh"
#include "listfeatures.hh"
#include "rule.hh"
#include "statement.hh"
#include "statements.hh"
#include "synthesizer.hh"
#include "term.hh"
#include "terms.hh"

/* **************************************************
 *
 ************************************************** */
Item::Item (class Rule *rule, 
	      unsigned int index,
	      unsigned int indexTerm,
	      statementsPtr statements)//: Item(rule, index, indexTerm, statements)
{
  NEW;
  this->rule=rule;
  this->index=index;
  this->statements=statements;
  this->environment = environmentPtr();
  this->statements = statements;
  this->inheritedFeatures = Features::_nil;
  this->synthesizedFeatures = Features::_nil;
  this->synthesizedSonFeatures = ListFeatures::create();
  this->inheritedSonFeatures = ListFeatures::create();

  std::vector<class Terms*> terms = rule->getRhs();
  unsigned j=0;
  for (std::vector<class Terms*>::const_iterator i = terms.begin();
       i != terms.end();
       ++i, ++j){
    this->indexTerms.push_back(0);
    this->seen.push_back(false);
    this->forestIdentifiers.push_back(forestIdentifierPtr());
    this->synthesizedSonFeatures->push_back(Features::_nil);
    this->inheritedSonFeatures->push_back(Features::_nil);
  }

  if ((terms.size() < index) && (index != UINT_MAX))
    this->indexTerms[index]=indexTerm;

}

/* **************************************************
 *
 ************************************************** */
Item::Item (class Rule *rule, 
	      unsigned int index,
	      std::vector<unsigned int>& indexTerms,
	      statementsPtr statements)
{
  NEW;
  this->rule=rule;
  this->index=index;
  this->indexTerms=indexTerms;
  this->statements=statements;
  this->environment = environmentPtr();
  this->statements = statements;
  this->inheritedFeatures = Features::_nil;
  this->synthesizedFeatures = Features::_nil;
  synthesizedSonFeatures = ListFeatures::create();
  inheritedSonFeatures = ListFeatures::create();
  
  std::vector<class Terms*> terms = rule->getRhs();
  unsigned j=0;
  for (std::vector< class Terms * >::iterator i = terms.begin();
       i != terms.end();
       ++i, ++j){
    this->indexTerms.push_back(0);
    this->seen.push_back(false);
    this->forestIdentifiers.push_back(forestIdentifierPtr());
    this->synthesizedSonFeatures->push_back(Features::_nil);
    this->inheritedSonFeatures->push_back(Features::_nil);
  }
}

/* **************************************************
 *
 ************************************************** */
Item::~Item ()
{
  refs.clear();
  seen.clear();
  ranges.clear();
  if (inheritedFeatures)
    inheritedFeatures.reset();
  if (inheritedSonFeatures)
  inheritedSonFeatures.reset();
  if (synthesizedFeatures)
    synthesizedFeatures.reset();
  if (synthesizedSonFeatures)
    synthesizedSonFeatures.reset();
  for(std::vector<forestIdentifierPtr >::iterator it = forestIdentifiers.begin();
      it != forestIdentifiers.end();
      ++it){
    forestIdentifierPtr tmp = *it;
    if (tmp)
      (tmp).reset();
  }
  forestIdentifiers.clear();
  if (statements)
    statements.reset();
  if (environment)
    environment.reset();
  DELETE;
}

/* **************************************************
 *
 ************************************************** */
itemPtr Item::create (class Rule *rule, 
			unsigned int index,
			unsigned int indexTerm,
			statementsPtr statements)
{
  return itemPtr( new Item(rule, index, indexTerm, statements) );
}

/* **************************************************
 *
 ************************************************** */
itemPtr Item::create (class Rule *rule, 
			unsigned int index,
			std::vector<unsigned int>& indexTerms,
			statementsPtr statements)
{
  return itemPtr( new Item(rule, index, indexTerms, statements) );
}

/* **************************************************
 *
 ************************************************** */
class Rule *Item::getRule(void) const 
{
  return rule;
}

/* **************************************************
 *
 ************************************************** */
void Item::setRule(class Rule *rule)
{
  this->rule = rule;
}

/* **************************************************
 *
 ************************************************** */
const unsigned int Item::getLineno(void) const 
{
  return rule->getLineno();
}

/* **************************************************
 *
 ************************************************** */
const std::string &Item::getFilename(void) const 
{
  return rule->getFilename();
}

/* **************************************************
 *
 ************************************************** */
unsigned int Item::getIndex(void) const 
{
  return index;
}

/* **************************************************
 *
 ************************************************** */
void Item::setIndex(unsigned int index)
{
  this->index = index;
}

/* **************************************************
 *
 ************************************************** */
std::vector<unsigned int> &Item::getIndexTerms(void)
{
  return indexTerms;
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Item::getStatements(void) 
{
  return statements;
}

/* **************************************************
 *
 ************************************************** */
class Terms *
Item::getTerms(const unsigned int index) const
{
  return rule->getRhs()[index];
}

/* **************************************************
 *
 ************************************************** */
class Terms *
Item::getCurrentTerms() const
{
  if ((this->index == UINT_MAX) || (this->index >= this->getRhs().size()))
    return NULL;
  return rule->getRhs()[this->index];
}

/* **************************************************
 *
 ************************************************** */
void
Item::setCurrentTerms(class Terms *terms)
{
  this->rule->getRhs()[this->index] = terms;
}

/* **************************************************
 *
 ************************************************** */
class Term *
Item::getCurrentTerm(void) const 
{
  class Terms *terms = getCurrentTerms();
  if ((terms == NULL) || (terms->size() == 0))
    return NULL;
  return (*terms)[0];
}

/* **************************************************
 *
 ************************************************** */
class Term *
Item::getLhs(void) const 
{
  return rule->getLhs();
}

/* **************************************************
 *
 ************************************************** */
std::vector<class Terms *> &
Item::getRhs(void) const
{
  return rule->getRhs();
}

/* **************************************************
 *
 ************************************************** */
std::set<unsigned int> &Item::getRefs(void)
{
  return refs;
}

/* **************************************************
 *
 ************************************************** */
void Item::setRefs(std::set<unsigned int> &refs)
{
  this->refs = refs;
}

/* **************************************************
 *
 ************************************************** */
void Item::addRef(unsigned int ref)
{
  this->refs.insert(ref);
}

/* **************************************************
 *
 ************************************************** */
void Item::addRefs(std::set<unsigned int> &refs)
{
  for(std::set<unsigned int>::const_iterator i = refs.begin(); i!=refs.end(); ++i)
    addRef(*i);
}

/* **************************************************
 *
 ************************************************** */
std::vector< bool > &Item::getSeen(void)
{
  return this->seen;
}

/* **************************************************
 *
 ************************************************** */
void Item::setSeen(std::vector< bool > & seen)
{
  this->seen = seen;
}

/* **************************************************
 *
 ************************************************** */
bool Item::isSeen(unsigned int index) const
{
  return seen[index];
}

/* **************************************************
 *
 ************************************************** */
void Item::setSeen(unsigned int index, bool b)
{
  this->seen[index] = b;
}

/* **************************************************
 *
 ************************************************** */
void Item::addItem(std::map<int, itemPtr >&table, int key, itemPtr item)
{
  table.insert(std::make_pair(key, item));
}

/* **************************************************
 *
 ************************************************** */
std::vector<unsigned int>& Item::getRanges(void)
{
  return ranges;
}

/* **************************************************
 *
 ************************************************** */
void Item::addRanges(unsigned int k)
{
  ranges.push_back(k);
}

/* **************************************************
 *
 ************************************************** */
void Item::addRanges(std::vector<unsigned int>&l)
{
  for(std::vector<unsigned int>::const_iterator i = l.begin(); i!=l.end(); ++i)
    addRanges(*i);
}

/* **************************************************
 *
 ************************************************** */
std::vector<forestIdentifierPtr > &Item::getForestIdentifiers(void)
{
  return forestIdentifiers;
}

/* **************************************************
 *
 ************************************************** */
void Item::addForestIdentifiers(unsigned int i, forestIdentifierPtr k)
{
  forestIdentifiers[i]=k;
}

/* **************************************************
 *
 ************************************************** */
void Item::addForestIdentifiers(std::vector<forestIdentifierPtr > &l)
{
  for(unsigned int i=0 ; i<l.size(); ++i)
    forestIdentifiers[i]=l[i];
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr Item::getSynthesizedSonFeatures(void)
{
  return synthesizedSonFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setSynthesizedSonFeatures(listFeaturesPtr l)
{
  synthesizedSonFeatures = l;
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr Item::getInheritedSonFeatures(void)
{
  return inheritedSonFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setInheritedSonFeatures(listFeaturesPtr l)
{
  inheritedSonFeatures = l;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Item::getSynthesizedFeatures(void) const 
{
  return synthesizedFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setSynthesizedFeatures(featuresPtr synthesizedFeatures)
{
  this->synthesizedFeatures = synthesizedFeatures;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Item::getInheritedFeatures(void) const 
{
  return inheritedFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setInheritedFeatures(featuresPtr inheritedFeatures)
{
  this->inheritedFeatures = inheritedFeatures;
}

/* **************************************************
 *
 ************************************************** */
environmentPtr Item::getEnvironment(void) const 
{
  return this->environment;
}

/* **************************************************
 *
 ************************************************** */
void Item::setEnvironment(environmentPtr e)
{
  this->environment = e;
}

/* **************************************************
 *
 ************************************************** */
bool Item::isStarted(void)
{
  return ranges.size()==1;
}

/* **************************************************
 *
 ************************************************** */
void 
Item::addStatements(statementsPtr statements)
{
  if (!this->statements)
    this->statements = Statements::create();
  for (std::list<statementPtr >::const_iterator i = statements->begin();
       i!=statements->end();
       ++i){
    this->statements->addStatement(*i);
  }
  if (this->statements->size()==0){
    FATAL_ERROR;
  }
}

/* **************************************************
 *
 ************************************************** */
bool 
Item::isCompleted(void)
{
  return ranges.size() == (this->getRhs().size()+1);
}

/* **************************************************
 *
 ************************************************** */
void
Item::addEnvironment(environmentPtr e)
{
  if (!this->environment)
    this->environment = Environment::create();
  this->environment->add(e);
}

/* **************************************************
 *
 ************************************************** */
void
Item::addEnvironment(environmentPtr e, environmentPtr where)
{
  if (!this->environment)
    this->environment = Environment::create();
  this->environment->add(e, where);
}

/* **************************************************
 *
 ************************************************** */
void Item::defaultInheritedSonFeatures (){
  std::vector<class Terms*> terms = this->getRhs();
  std::vector< bool > assignedInheritedSonFeatures;
  for (std::vector<class Terms*>::const_iterator it = terms.begin();
       it != terms.end();
       ++it)
    assignedInheritedSonFeatures.push_back(false);
  if (statements)
    for (std::list<statementPtr >::const_iterator statement = this->statements->begin();
	 statement!=this->statements->end();
	 ++statement)
      (*statement)->lookingForAssignedInheritedSonFeatures(assignedInheritedSonFeatures);
  unsigned int j=0;
  for (std::vector< bool >::const_iterator it = assignedInheritedSonFeatures.begin();
       it != assignedInheritedSonFeatures.end();
       ++it, ++j)
    if (!(*it))
      (*inheritedSonFeatures).add (j, Features::create());
}

/* **************************************************
 *
 ************************************************** */
void
Item::print(std::ostream& out) const
{
  out << "<table border=\"1\" style=\"color:black; ";
  if (isSetFlags(Flags::BOTTOM)){
    out << " background-color:Pink;";
  }
  else if (isSetFlags(Flags::SEEN))
    out << " background-color:PaleTurquoise;";
  out << "\">";
  out << "<tr>";
  if (s_id)
    out << "<th>ID</th>";
  if (s_ruleId)
    out << "<th>RuleId</th>";
  if (s_rule)
    out << "<th>Rule</th>";
  if (s_flags)
    out << "<th>Flags</th>";
  if (s_refs)
    out << "<th>Refs</th>";
  if (s_seen)
    out << "<th>Seen</th>";
  if (s_item)
    out << "<th>Item</th>";
  if (s_index)
    out << "<th>Index</th>";
  if (s_indexTerms)
    out << "<th>IndexTerms</th>";
  if (s_terms)
    out << "<th>Terms</th>";
  if (s_ranges)
    out << "<th>Ranges</th>";
  if (s_forestIdentifiers)
    out << "<th>ForestIdentifiers</th>";
  if (s_inheritedFeatures)
    out << "<th bgcolor=\"lightyellow\"><center>↑</center></th>";
  if (s_inheritedSonFeatures)
    out << "<th bgcolor=\"lightyellow\"><center>↓i</center></th>";
  if (s_synthesizedFeatures)
    out << "<th bgcolor=\"lightcyan\"><center>⇑</center></th>";
  if (s_synthesizedSonFeatures)
    out << "<th bgcolor=\"lightcyan\"><center>⇓i</center></th>";
  if (s_statements)
    out << "<th bgcolor=\"white\"><center>Statements</center></th>";
  if (s_environment && environment)
    out << "<th align = center>Environment</th>";
  out << "<tr>";
  if (s_id){
    out << "<td>";
    out << '#' << this->getId();
    out << "</td>";
  }
  if (s_ruleId){
    out << "<td>";
    out << this->getRule()->getId();
    out << "</td>";
  }
  if (s_rule){
    out << "<td>";
    this->getRule()->print(out);
    out << "</td>";
  }
  if (s_flags){
    out << "<td>";
    Flags::printFlags(out);
    out << "</td>";

  }
  if (s_refs){
    out << "<td>(";
    std::set<unsigned int>::const_iterator ref = refs.begin();
    while (ref!=refs.end()){
      out << '#' << *ref;
      if (++ref!=refs.end())
	out << ' ';
    }
    out << ")</td>";
  }
  if (s_seen){
    out << "<td>(";
    std::vector<bool>::const_iterator s = seen.begin();
    while (s!=seen.end()){
      out << *s;
      if (++s!=seen.end())
	out << ' ';
    }
    out << ")</td>";
  }
  if (s_item){
    out << "<td>";
    rule->print(out, index, false);
    out << "</td>";
  }
  if (s_index){
    out << "<td>";
    if (getIndex()==UINT_MAX)
      out << "UINT_MAX";
    else
      out << getIndex();
    out << "</td>";
  }
  if (s_indexTerms){
    out << "<td>";
    for (std::vector<unsigned int>::const_iterator i = indexTerms.begin() ; i != indexTerms.end() ; ++i)
      if ((*i) == UINT_MAX)
	out << "UINT_MAX" << "&nbsp;";
      else
	out << (*i) << "&nbsp;";
    out << "</td>";
  }
  if (s_terms){
    out << "<td>";
    class Terms *terms = getCurrentTerms();
    if (terms)
      terms->print(out);
    else
      out << "NULL";
    out << "</td>";

  }
  if (s_ranges){
    out << "<td>";//<center>Ranges</center><br>";
    int old = -1;
    bool first = true;
    for (std::vector<unsigned int>::const_iterator i = ranges.begin();
	 i!=ranges.end();
	 i++) {
      if (old != -1) {
	if (first)
	  first = false;
	else
	  out << "&nbsp;";
	out << '[' << old << '-' << *i << ']';
      }
      old = *i;
    }
    out << "</td>";
  }
  if (s_forestIdentifiers){
    out << "<td>";//<center>ForestIdentifiers</center><br>";
    for(std::vector<forestIdentifierPtr >::const_iterator i = forestIdentifiers.begin() ; i!=forestIdentifiers.end() ; ){
      if (*i)
	(*i)->print(out);
      if (++i != forestIdentifiers.end()){
	out << ", ";
      }
    }
    out << "</td>";
  }
  if (s_inheritedFeatures){
    out << "<td bgcolor=\"lightyellow\">";//<center>↑</center><br>";
    inheritedFeatures->print(out);
    out << "</td>";
  }
  if (s_inheritedSonFeatures){
    out << "<td bgcolor=\"lightyellow\"><table>";//<center>↓i</center><br>";
    for(std::vector<featuresPtr >::const_iterator i = inheritedSonFeatures->begin(); i!=inheritedSonFeatures->end(); ++i){
      out << "<tr><td>";
      if (*i)
	(*i)->print(out);
      out << "</td></tr>";
    }
    out << "</table></td>";
  }
  if (s_synthesizedFeatures){
    out << "<td bgcolor=\"lightcyan\">";//<center>⇑</center><br>";
    if (synthesizedFeatures){
      synthesizedFeatures->print(out);
    }
    out << "</td>";
  }
  if (s_synthesizedSonFeatures){
    out << "<td bgcolor=\"lightcyan\"><table border=\"1\">";//<center>⇓i</center><br>";
    for(std::vector<featuresPtr >::const_iterator i = synthesizedSonFeatures->begin(); i!=synthesizedSonFeatures->end(); ++i){
      out << "<tr><td>";
      if (*i)
	(*i)->print(out);
      out << "</td></tr>";
    }
    out << "</table></td>";
  }
  if (s_statements){
    out << "<td bgcolor=\"white\">";
    if (statements)
      statements->print(out);
    else
      out << "&nbsp;";
    out << "</td>";
  }
  if (s_environment && environment){
    out << "<td align=\"center\">";
    if (environment)
      environment->print(out);
    else
      out << "&nbsp;";
    out << "</td>";
  }
  out << "</tr></table>";
  out << std::endl;
}

/* **************************************************
 *
 ************************************************** */
itemPtr 
Item::clone(const std::bitset<NBRFLAGS> &savedFlags)
{
  itemPtr it = Item::create(this->rule,
			      this->index,
			      this->indexTerms,
			    this->statements ? this->statements->clone(savedFlags) : statementsPtr()
			      );
  it->environment = (this->environment) ? this->environment->clone() : environmentPtr();
  it->addRanges(this->ranges);
  it->addForestIdentifiers(this->forestIdentifiers);
  it->refs = this->refs;
  it->seen = this->seen;
  it->inheritedFeatures = this->inheritedFeatures->clone();
  it->inheritedSonFeatures = this->inheritedSonFeatures->clone();
  it->synthesizedSonFeatures = this->synthesizedSonFeatures->clone();
  it->synthesizedFeatures = this->synthesizedFeatures->clone();
  return it;
}

/* **************************************************
 *
 ************************************************** */
void
Item::successor(itemSetPtr state, class Synthesizer *synthesizer, bool &effect)
{
#ifdef TRACE_SUCCESSOR
  std::cout << "<H3>####################### SUCCESSOR #######################</H3>" << std::endl;
  this->print(std::cout);
  std::cout << std::endl;
#endif
    for(unsigned int i = 0; i < this->getRhs().size(); ++i){
      if ((i == index)
	  || ((*this->getInheritedSonFeatures())[i]->isNil() && !this->getTerms(i)->isOptional() && this->getTerms(i)->size() == 1))
	continue;
      if (!this->forestIdentifiers[i]){
	this->index = i;
	effect = true;
	break;
      }
    }
    
    if (!effect && (index == UINT_MAX) && isCompleted()){
      this->index = this->getRhs().size();
    }
    if (this->index != UINT_MAX)
      this->setSeen(this->index, true);
    
#ifdef TRACE_SUCCESSOR
  std::cout << "<H3>####################### SUCCESSOR DONE #######################</H3>" << std::endl;
  this->print(std::cout);
  std::cout << std::endl;
#endif
}

/* **************************************************
 *
 ************************************************** */
void
Item::apply(itemSetPtr state, class Synthesizer *synthesizer)
{
  if (statements){
    int k=1;
    bool effect = true;
    while(effect){
#ifdef TRACE
      if (synthesizer->getTraceAction()){
	std::cout << "<H3>####################### ACTION #######################</H3>" << std::endl;
	print(std::cout);
	std::cout << std::endl;
      }
#endif
      if (isSetFlags(Flags::BOTTOM))
	return;
      effect = false;
      statements->apply(shared_from_this(), synthesizer, effect, synthesizer->getTrace());
      ++k;
#ifdef TRACE
      if (synthesizer->getTraceAction()){
	std::cout << "<H3>####################### ACTION DONE #######################</H3>" << std::endl;
	print(std::cout);
	std::cout << std::endl;
      }
#endif
    }
  }
}

/* **************************************************
 *
 ************************************************** */
void
Item::makeSerialString()
{
  serialString = std::to_string(getRule()->getId());
  
  if (getIndex()==UINT_MAX)
    serialString += '+';
  else
    serialString += std::to_string(getIndex());
  
  serialString += '|';
  std::vector<unsigned int>::const_iterator ind = indexTerms.begin();
  while (ind != indexTerms.end())
    serialString += std::to_string(*(ind++)) + '-';
    
  serialString += '|';
  std::set<unsigned int>::const_iterator ref = refs.begin();
  while (ref != refs.end())
    serialString += std::to_string(*(ref++)) + '-';
  
  serialString += '|';
  std::vector< forestIdentifierPtr >::const_iterator fi = forestIdentifiers.begin();
  while (fi != forestIdentifiers.end()){
    if (*fi)
      serialString += (*fi)->peekSerialString() + '-';
    else
      serialString += '.';
    ++fi;
  }
  
  serialString += '|';
  serialString += inheritedFeatures->peekSerialString();
}
 
 /* **************************************************
  *
  ************************************************** */
size_t Item::hash::operator() (itemPtr const i) const
{
  return i->hashCode();
}

 /* **************************************************
  *
  ************************************************** */
bool Item::equal_to::operator() (itemPtr const i1, itemPtr const i2) const
{
  return i1->peekSerialString() == i2->peekSerialString();
}
