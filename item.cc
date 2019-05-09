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
  return shared_ptr< class Item >( new Item(rule, index, indexTerm, statements) );
}

/* **************************************************
 *
 ************************************************** */
itemPtr Item::create (class Rule *rule, 
			unsigned int index,
			std::vector<unsigned int>& indexTerms,
			statementsPtr statements)
{
  return shared_ptr< class Item >( new Item(rule, index, indexTerms, statements) );
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
void Item::setId(idType id)
{
  FATAL_ERROR;
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
void Item::addItem(std::map<int, itemPtr >&table, int clef, itemPtr item)
{
  table.insert(std::pair<int, itemPtr >(clef, item));
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
 * compare deux items
 ************************************************** */
const bool Item::Less::operator() (const itemPtr i1, const itemPtr i2) const
{

  if (i1->getRule()->getId() != i2->getRule()->getId())
    return (i1->getRule()->getId() < i2->getRule()->getId());
  
  if (i1->getRule()->serialize() != i2->getRule()->serialize())
      return  (i1->getRule()->serialize() < i2->getRule()->serialize());
  
  if (i1->getIndex() != i2->getIndex())
      return  (i1->getIndex() < i2->getIndex());

  if (i1->indexTerms.size() != i2->indexTerms.size())
      return  (i1->indexTerms.size() < i2->indexTerms.size());
  
  if (i1->forestIdentifiers.size() != i2->forestIdentifiers.size())
      return  (i1->forestIdentifiers.size() < i2->forestIdentifiers.size());
  
  std::vector<unsigned int>::const_iterator ind1 = i1->indexTerms.begin();
  std::vector<unsigned int>::const_iterator ind2 = i2->indexTerms.begin();
  while (ind1 != i1->indexTerms.end()){
    if ((*ind1) != (*ind2))
      return  ((*ind1) < (*ind2));
    ++ind1; ++ind2;
  }
  
  std::vector< forestIdentifierPtr >::const_iterator t1 = i1->forestIdentifiers.begin();
  std::vector< forestIdentifierPtr >::const_iterator t2 = i2->forestIdentifiers.begin();
  while (t1 != i1->forestIdentifiers.end()){
    if (!*t1 || !*t2){
      if (*t1 != *t2)
	return  (*t1 < *t2);
    }
    else {
      if ((**t1) != (**t2)){
	return  ((**t1) < (**t2));
      }
    }
    ++t1; ++t2;
  }

  if (!(i1->inheritedFeatures) || !(i2->inheritedFeatures)){
    if (i1->inheritedFeatures != i2->inheritedFeatures)
      return  (i1->inheritedFeatures < i2->inheritedFeatures);
  } else {
    if (i1->inheritedFeatures->serialize() != i2->inheritedFeatures->serialize()) {
      return (i1->inheritedFeatures->serialize() < i2->inheritedFeatures->serialize());
    }
  }
  
  return false;
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
      (*inheritedSonFeatures).push (j, Features::create());
}

/* **************************************************
 *
 ************************************************** */
void
Item::print(std::ostream& outStream) const
{
  outStream << "<table border=\"1\" style=\"color:black; ";
  if (isSetFlags(Flags::BOTTOM)){
    outStream << " background-color:Pink;";
  }
  else if (isSetFlags(Flags::SEEN))
    outStream << " background-color:PaleTurquoise;";
  outStream << "\">";
  outStream << "<tr>";
  if (s_id)
    outStream << "<th>ID</th>";
  if (s_ruleSerialId)
    outStream << "<th>RuleSerialId</th>";
  if (s_ruleId)
    outStream << "<th>RuleId</th>";
  if (s_flags)
    outStream << "<th>Flags</th>";
  if (s_refs)
    outStream << "<th>Refs</th>";
  if (s_seen)
    outStream << "<th>Seen</th>";
  if (s_item)
    outStream << "<th>Item</th>";
  if (s_index)
    outStream << "<th>Index</th>";
  if (s_indexTerms)
    outStream << "<th>IndexTerms</th>";
  if (s_terms)
    outStream << "<th>Terms</th>";
  if (s_ranges)
    outStream << "<th>Ranges</th>";
  if (s_forestIdentifiers)
    outStream << "<th>ForestIdentifiers</th>";
  if (s_inheritedFeatures)
    outStream << "<th bgcolor=\"lightyellow\"><center>↑</center></th>";
  if (s_inheritedSonFeatures)
    outStream << "<th bgcolor=\"lightyellow\"><center>↓i</center></th>";
  if (s_synthesizedFeatures)
    outStream << "<th bgcolor=\"lightcyan\"><center>⇑</center></th>";
  if (s_synthesizedSonFeatures)
    outStream << "<th bgcolor=\"lightcyan\"><center>⇓i</center></th>";
  if (s_statements)
    outStream << "<th bgcolor=\"white\"><center>Statements</center></th>";
  if (s_environment && environment)
    outStream << "<th align = center>Environment</th>";
  outStream << "<tr>";
  if (s_id){
    outStream << "<td>";
    outStream << '#' << this->getId();
    outStream << "</td>";
  }
  if (s_ruleSerialId){
    outStream << "<td>";
    outStream << this->getRule()->serialize();
    outStream << "</td>";
  }
  if (s_ruleId){
    outStream << "<td>";
    outStream << this->getRule()->getId();
    outStream << "</td>";
  }
  if (s_flags){
    outStream << "<td>";
    Flags::printFlags(outStream);
    outStream << "</td>";

  }
  if (s_refs){
    outStream << "<td>(";
    std::set<unsigned int>::const_iterator ref = refs.begin();
    while (ref!=refs.end()){
      outStream << '#' << *ref;
      if (++ref!=refs.end())
	outStream << ' ';
    }
    outStream << ")</td>";
  }
  if (s_seen){
    outStream << "<td>(";
    std::vector<bool>::const_iterator s = seen.begin();
    while (s!=seen.end()){
      outStream << *s;
      if (++s!=seen.end())
	outStream << ' ';
    }
    outStream << ")</td>";
  }
  if (s_item){
    outStream << "<td>";
    rule->print(outStream, index, false);
    outStream << "</td>";
  }
  if (s_index){
    outStream << "<td>";
    if (getIndex()==UINT_MAX)
      outStream << "UINT_MAX";
    else
      outStream << getIndex();
    outStream << "</td>";
  }
  if (s_indexTerms){
    outStream << "<td>";
    for (std::vector<unsigned int>::const_iterator i = indexTerms.begin() ; i != indexTerms.end() ; ++i)
      if ((*i) == UINT_MAX)
	outStream << "UINT_MAX" << "&nbsp;";
      else
	outStream << (*i) << "&nbsp;";
    outStream << "</td>";
  }
  if (s_terms){
    outStream << "<td>";
    class Terms *terms = getCurrentTerms();
    if (terms)
      terms->print(outStream);
    else
      outStream << "NULL";
    outStream << "</td>";

  }
  if (s_ranges){
    outStream << "<td>";//<center>Ranges</center><br>";
    outStream << "(";
    for(std::vector<unsigned int>::const_iterator i = ranges.begin();
	i!=ranges.end();){
      outStream << (*i);
      if (++i!=ranges.end()){
	outStream << ", ";
      }
    }
    outStream << ")";
    outStream << "</td>";
  }
  if (s_forestIdentifiers){
    outStream << "<td>";//<center>ForestIdentifiers</center><br>";
    for(std::vector<forestIdentifierPtr >::const_iterator i = forestIdentifiers.begin(); i!=forestIdentifiers.end();){
      if (*i)
	(*i)->print(outStream);
      else
	outStream << "NULL";
      if (++i!=forestIdentifiers.end()){
	outStream << ", ";
      }
    }
    outStream << "</td>";
  }
  if (s_inheritedFeatures){
    outStream << "<td bgcolor=\"lightyellow\">";//<center>↑</center><br>";
    inheritedFeatures->print(outStream);
    //outStream << inheritedFeatures->serialize(); 
    outStream << "</td>";
  }
  if (s_inheritedSonFeatures){
    outStream << "<td bgcolor=\"lightyellow\"><table>";//<center>↓i</center><br>";
    for(std::vector<featuresPtr >::const_iterator i = inheritedSonFeatures->begin(); i!=inheritedSonFeatures->end(); ++i){
      outStream << "<tr><td>";
      if (*i)
	(*i)->print(outStream);
      else
	outStream << "null";
      //outStream << (*i)->serialize(); 
      outStream << "</td></tr>";
    }
    outStream << "</table></td>";
  }
  if (s_synthesizedFeatures){
    outStream << "<td bgcolor=\"lightcyan\">";//<center>⇑</center><br>";
    if (synthesizedFeatures){
      synthesizedFeatures->print(outStream);
      //outStream << synthesizedFeatures->serialize(); 
    }
    else
      outStream << "null";
    outStream << "</td>";
  }
  if (s_synthesizedSonFeatures){
    outStream << "<td bgcolor=\"lightcyan\"><table>";//<center>⇓i</center><br>";
    for(std::vector<featuresPtr >::const_iterator i = synthesizedSonFeatures->begin(); i!=synthesizedSonFeatures->end(); ++i){
      outStream << "<tr><td>";
      if (*i)
	(*i)->print(outStream);
      else
	outStream << "null";
      outStream << "</td></tr>";
    }
    outStream << "</table></td>";
  }
  if (s_statements){
    outStream << "<td bgcolor=\"white\">";
    if (statements)
      statements->print(outStream);
    else
      outStream << "&nbsp;";
    outStream << "</td>";
  }
  if (s_environment && environment){
    outStream << "<td align = center>";
    if (environment)
      environment->print(outStream);
    else
      outStream << "&nbsp;";
    outStream << "</td>";
  }
  outStream << "</tr></table>";
  outStream << std::endl;
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
  std::cerr << "####################### SUCCESSOR #######################" << std::endl;
  this->print(std::cerr);
  std::cerr << std::endl;
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
  std::cerr << "####################### SUCCESSOR DONE #######################" << std::endl;
  this->print(std::cerr);
  std::cerr << std::endl;
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
#ifdef TRACE_ACTION
      std::cerr << "####################### ACTION #######################" << '(' << k << ')' << std::endl;
      print(std::cerr);
      std::cerr << std::endl;
#endif
      if (isSetFlags(Flags::BOTTOM))
	return;
      effect = false;
      statements->apply(shared_from_this(), effect, synthesizer->getTrace());
      ++k;
#ifdef TRACE_ACTION
      std::cerr << "####################### ACTION DONE #######################" << '(' << k << ')' << std::endl;
      print(std::cerr);
      std::cerr << std::endl;
#endif
    }
  }
}
