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

#include <string.h>
#include "synthesizer.hh"
#include "entries.hh"
#include "term.hh"
#include "terms.hh"
#include "vartable.hh"
#include "statements.hh"
#include "statement.hh"
#include "messages.hh"
#include "entry.hh"
#include "environment.hh"
#include "forest.hh"
#include "item.hh"
#include "itemset.hh"
#include "infobuff.hh"
#include "lex.hh"
#include "listfeatures.hh"
#include "node.hh"
#include "forestidentifier.hh"
#include "forestmap.hh"

extern unsigned int rulesparse(void);
extern FILE *rulesin;
extern void init_buffer(void);
extern void push_buffer(void);
extern void delete_buffer(void);
extern void scan_string(std::string);

/* **************************************************
 *
 ************************************************** */
Synthesizer::Synthesizer(void) {
  NEW;
  this->compactLexicon = NULL;
  this->maxLength = MAXLENGTH;
  this->maxUsages = MAXUSAGES;
  this->maxCardinal = MAXCARDINAL;
  this->maxLengthMsg = false;
  this->maxUsagesMsg = false;
  this->maxCardinalMsg = false;
  this->nodeRoot = nodePtr();
  this->startFeatures = featuresPtr();
  this->startTerm = NULL;
  this->localEntry = entryPtr();
  this->lexiconFileName = std::string();
  this->grammarFileName = std::string();
  this->inputFileName = std::string();
#ifdef OUTPUT_XML
  this->outXML = NULL;
#endif
  this->reduceAll = false;
  this->trace = false;
  this->warning = false;
  this->random = false;
}

/* **************************************************
 *
 ************************************************** */
Synthesizer::~Synthesizer(void) {
  //DELETE;
}

/* **************************************************
 *
 ************************************************** */
class Grammar &
Synthesizer::getGrammar(void) {
  return grammar;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setGrammar(class Grammar &grammar) {
  this->grammar = grammar;
}

/* **************************************************
 *
 ************************************************** */
std::map<unsigned int, itemSetPtr>::const_iterator 
Synthesizer::begin(void) const {
  return states.begin();
}

/* **************************************************
 *
 ************************************************** */
std::map<unsigned int, itemSetPtr>::const_iterator 
Synthesizer::end(void) const {
  return states.end();
}

/* **************************************************
 *
 ************************************************** */
int 
Synthesizer::size(void) const {
  return states.size();
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setInputFileName(char *name) {
  inputFileName = name;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setLexiconFileName(char *name) {
  lexiconFileName = name;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setCompactLexiconFileName(char *bufferName) {
  compactLexiconFileName = bufferName;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setCompactDirectoryName(char *DirectoryName) {
  compactDirectoryName = DirectoryName;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setGrammarFileName(char *name) {
  grammarFileName = name;
}

/* **************************************************
 *
 ************************************************** */
std::string 
Synthesizer::getInputFileName(void) const {
  return inputFileName;
}

/* **************************************************
 *
 ************************************************** */
std::string 
Synthesizer::getLexiconFileName(void) const {
  return lexiconFileName;
}

/* **************************************************
 *
 ************************************************** */
std::string 
Synthesizer::getCompactLexiconFileName(void) const {
  return compactLexiconFileName;
}

/* **************************************************
 *
 ************************************************** */
std::string 
Synthesizer::getCompactDirectoryName(void) const {
  return compactDirectoryName;
}

/* **************************************************
 *
 ************************************************** */
std::string 
Synthesizer::getGrammarFileName(void) const {
  return grammarFileName;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setInputString(std::string str) {
  inputString = str;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setLexiconString(std::string str) {
  lexiconString = str;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setGrammarString(std::string str) {
  grammarString = str;
}

/* **************************************************
 *
 ************************************************** */
std::string 
Synthesizer::getInputString(void) const {
  return inputString;
}

/* **************************************************
 *
 ************************************************** */
std::string 
Synthesizer::getLexiconString(void) const {
  return lexiconString;
}

/* **************************************************
 *
 ************************************************** */
std::string 
Synthesizer::getGrammarString(void) const {
  return grammarString;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setMaxLength(unsigned int maxLength) {
  this->maxLength = maxLength;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setMaxUsages(unsigned int maxUsages) {
  this->maxUsages = maxUsages;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setMaxCardinal(unsigned int maxCardinal) {
  this->maxCardinal = maxCardinal;
}

/* **************************************************
 *
 ************************************************** */
unsigned int 
Synthesizer::getMaxCardinal(void) {
  return this->maxCardinal;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setMaxLengthMsg(bool b) {
  this->maxLengthMsg = b;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setMaxUsagesMsg(bool b) {
  this->maxUsagesMsg = b;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setMaxCardinalMsg(bool b) {
  this->maxCardinalMsg = b;
}

/* **************************************************
 *
 ************************************************** */
bool 
Synthesizer::getMaxCardinalMsg(void) const {
  return this->maxCardinalMsg;
}

/* **************************************************
 *
 ************************************************** */
bool 
Synthesizer::getMaxUsagesMsg(void) const {
  return this->maxUsagesMsg;
}

/* **************************************************
 *
 ************************************************** */
class Lex *
Synthesizer::getCompactLexicon(void) const {
  return compactLexicon;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setCompactLexicon(class Lex *compactLexicon) {
  this->compactLexicon = compactLexicon;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setStartFeatures(featuresPtr f) {
  this->startFeatures = f;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr 
Synthesizer::getStartFeatures(void) const {
  return this->startFeatures;
}

/* **************************************************
 *
 ************************************************** */
class Term *
Synthesizer::getStartTerm(void) const {
  return startTerm;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setStartTerm(class Term *startTerm) {
  this->startTerm = startTerm;
}

/* **************************************************
 *
 ************************************************** */
const bool
Synthesizer::getTrace(void) const {
  return trace;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setTrace(const bool trace) {
  this->trace = trace;
}

/* **************************************************
 *
 ************************************************** */
const bool
Synthesizer::getReduceAll(void) const {
  return reduceAll;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setReduceAll(const bool reduceAll) {
  this->reduceAll = reduceAll;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setRandom(const bool random) {
  this->random = random;
}

/* **************************************************
 *
 ************************************************** */
bool
Synthesizer::getRandom(void) const {
  return this->random;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setOutXML(char *outXML)
{
  this->outXML = outXML;
}

/* **************************************************
 *
 ************************************************** */
char *
Synthesizer::getOutXML(void) const
{
  return this->outXML;
}
#endif

/* **************************************************
 *
 ************************************************** */
Synthesizer::lexiconType &
Synthesizer::getLexicon(void) {
  return lexicon;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setLexicon(lexiconType &lexicon) {
  this->lexicon = lexicon;
}

/* **************************************************
 *
 ************************************************** */
Synthesizer::lexiconType::const_iterator 
Synthesizer::findLexicon(unsigned int i) const {
  return lexicon.find(i);
}

/* **************************************************
 *
 ************************************************** */
Synthesizer::lexiconType::const_iterator 
Synthesizer::beginLexicon(void) const {
  return lexicon.begin();
}

/* **************************************************
 *
 ************************************************** */
Synthesizer::lexiconType::const_iterator 
Synthesizer::endLexicon(void) const {
  return lexicon.end();
}

/* **************************************************
 *
 ************************************************** */
entryPtr 
Synthesizer::getLocalEntry(void) const {
  return localEntry;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::setLocalEntry(entryPtr localEntry) {
  this->localEntry = localEntry;
}

/* **************************************************
 *
 ************************************************** */
const bool 
Synthesizer::insertItemMap(const itemPtr item) {
  return this->itemMap.insert(std::pair<unsigned int, itemPtr>(item->getId(), item)).second;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::eraseItemMap(const unsigned int id) {
  this->itemMap.erase(id);
}

/* **************************************************
 *
 ************************************************** */
itemPtr 
Synthesizer::getItemMap(const unsigned int id) {
  return this->itemMap[id];
}

/* **************************************************
 *
 ************************************************** */
nodePtr 
Synthesizer::getNodeRoot(void) {
  return nodeRoot;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::pushBufferName(std::string name) {
  bufferNames.push(name);
}

/* **************************************************
 *
 ************************************************** */
std::string 
Synthesizer::popBufferName(void) {
  std::string str = bufferNames.top();
  this->bufferNames.pop();
  return str; 
}

/* **************************************************
 *
 ************************************************** */
std::string 
Synthesizer::getTopBufferName(void) {
  return bufferNames.top();
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::pushLineno(int i) {
  linenos.push(i);
}

/* **************************************************
 *
 ************************************************** */
int  
Synthesizer::popLineno(void) {
  int i = linenos.top();
  linenos.pop();
  return i;
}

/* **************************************************
 *
 ************************************************** */
int 
Synthesizer::getTopLineno(void) {
  return linenos.top();
}

/* **************************************************
 *
 ************************************************** */
class ForestMap
Synthesizer::getForestMap(void) {
  return this->forestMap;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::printLexicon(std::ostream& out) const {
  out << "<ul>";
  for (lexiconType::const_iterator i = beginLexicon(); i != endLexicon(); ++i) {
    out << "<li>";
    out << Vartable::intToStr((*i).first);
    out << "<ul>";
    for (std::map<unsigned int, entriesPtr>::iterator j = (*i).second->begin(); j != (*i).second->end(); ++j) {
      out << "<li>";
      if ((*j).first == 0)
	out << "0 = &gt; ";
      else if ((*j).first == UINT_MAX)
	out << "UINT_MAX = &gt; ";
      else
	out << Vartable::intToStr((*j).first) << " = &gt; ";

      (*j).second->print(out);
      out << "</li>";

    }
    out << "</ul>";
    out << "</il>";

  }
  out << "</ul>";
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::printState(std::ostream& outStream, itemSetPtr state)
{
  outStream << "Q" << state->getId();
  state->print(outStream);
}

/* **************************************************
 *
 ************************************************** */
itemPtr Synthesizer::createItem(itemPtr item, unsigned int row) {
  itemPtr it = Item::create(item->getRule(), 
			    item->getIndex() + 1, 
			    item->getIndexTerms(), 
			    item->getStatements() ? item->getStatements()->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED) : statementsPtr());
  it->addRanges(item->getRanges());
  it->addRanges(row);
  it->addForestIdentifiers(item->getForestIdentifiers());
  it->setInheritedFeatures(item->getInheritedFeatures()->clone());
  it->setInheritedSonFeatures(item->getInheritedSonFeatures()->clone());
  it->setSynthesizedFeatures(item->getSynthesizedFeatures()->clone());
  it->setSynthesizedSonFeatures(item->getSynthesizedSonFeatures()->clone());
  it->setSeen(item->getSeen());
  return it;
}

#ifdef MEMOIZATION
/* **************************************************
 *
 ************************************************** */
std::string
Synthesizer::keyMemoization(itemPtr item)
{
  return std::to_string(item->getCurrentTerm()->getCode()) + (*item->getInheritedSonFeatures())[item->getIndex()]->serialize();
}

/* **************************************************
 *
 ************************************************** */
std::string
Synthesizer::keyMemoization(itemPtr actualItem, itemPtr previousItem)
{
  return std::to_string(actualItem->getId()) + '.' + std::to_string(previousItem->getCurrentTerm()->getCode()) + actualItem->getSynthesizedFeatures()->serialize();
}

#endif

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::close(itemSetPtr state, unsigned int row) {
  bool modification;
  do {
  loop:
    //if (getMaxCardinalMsg()) {
    //FATAL_ERROR_MSG("maxCardinal");
    //}
    modification = false;

    // Iterate through list
    for (ItemSet::iterator actualItem = state->begin();
	 actualItem != state->end() && !modification;
	 ++actualItem) {
      
      if ((*actualItem)->isSetFlags(Flags::SEEN | Flags::BOTTOM))
	continue;
      
#ifdef TRACE_CLOSE
      std::cerr << "####################### CLOSE #######################" << std::endl;
      (*actualItem)->print(std::cerr);
      std::cerr << std::endl;
#endif
      
      // X -> alpha • [Y] gamma
      if ((*actualItem)->getRhs().size() > (*actualItem)->getIndex()
	  && !(*actualItem)->isCompleted()
	  && !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
	  && (*actualItem)->getCurrentTerms()->isOptional()) {

#ifdef TRACE_UNHIDE
	std::cerr << "####################### UNHIDE #######################" << std::endl;
	(*actualItem)->print(std::cerr);
	std::cerr << std::endl;
#endif

	(*actualItem)->addFlags(Flags::SEEN);
	
	itemPtr it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
	forestPtr forestFound = forestPtr();
	forestIdentifierPtr fi = ForestIdentifier::create(it->getCurrentTerm()->getCode(), std::string(), row, row);
	ForestMap::mapForestIdentifierForest::const_iterator forestMapIt = forestMap.find(fi);
	if (forestMapIt != forestMap.end()) {
	  forestFound = forestMapIt->second;
	  fi.reset();
	  it->addForestIdentifiers(it->getIndex(), forestMapIt->first);
	} else {
	  forestFound = Forest::create(Entry::create(it->getCurrentTerm()->getCode()), row, row);
	  forestMap.insert(std::make_pair(fi, forestFound));
	  it->addForestIdentifiers(it->getIndex(), fi);
	}
	it->setIndex((*actualItem)->getIndex()+1);
	it->addRanges(row);
#ifdef TRACE_UNHIDE
	std::cerr << "####################### UNHIDE: X -> alpha [Y] • gamma #######################" << std::endl;
	it->print(std::cerr);
	std::cerr << std::endl;
#endif
	if (!state->insert(it, this)){
	  break;
	  //FATAL_ERROR;
	}
	insertItemMap(it);
	it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
	it->setRule((*actualItem)->getRule()->clone());
	it->setIndex((*actualItem)->getIndex());
	it->getCurrentTerms()->unsetOptional();
#ifdef TRACE_UNHIDE
	std::cerr << "####################### UNHIDE: X -> alpha • Y gamma #######################" << std::endl;
	it->print(std::cerr);
	std::cerr << std::endl;
#endif
	if (!state->insert(it, this)){
	  //break;
	  FATAL_ERROR;
	}
	insertItemMap(it);
	state->erase((*actualItem));
	eraseItemMap((*actualItem)->getId());
	goto loop;
      }
      
      // X -> alpha • Y1|Y2 beta
      if ((*actualItem)->getRhs().size() > (*actualItem)->getIndex()
	  && !(*actualItem)->isCompleted()
	  && !(*actualItem)->getCurrentTerms()->isOptional()
	  && (*actualItem)->getCurrentTerms()->size() > 1) {
	
#ifdef TRACE_UNFOLD
	std::cerr << "####################### UNFOLD #######################" << std::endl;
	(*actualItem)->print(std::cerr);
	std::cerr << std::endl;
#endif

	(*actualItem)->addFlags(Flags::SEEN);
	class Terms *terms = (*actualItem)->getCurrentTerms();
	for (unsigned int indexTerm1 = 0;
	     indexTerm1 < terms->size();
	     ++indexTerm1){
	  itemPtr it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
	  it->setRule((*actualItem)->getRule()->clone());
	  it->setIndex((*actualItem)->getIndex());
	  it->setCurrentTerms(new Terms((*terms)[indexTerm1]));
	  it->getIndexTerms()[(*actualItem)->getIndex()] = indexTerm1;

#ifdef TRACE_UNHIDE
	  std::cerr << "####################### UNFOLD: insert #######################" << std::endl;
	  it->print(std::cerr);
	  std::cerr << std::endl;
#endif
	  if (state->insert(it, this))
	    insertItemMap(it);
	}
	state->erase((*actualItem));
	eraseItemMap((*actualItem)->getId());
	goto loop;
      }
      
      (*actualItem)->apply(state, this);
#ifdef TRACE_CLOSE
      std::cerr << "####################### APPLIED #######################" << std::endl;
      (*actualItem)->print(std::cerr);
      std::cerr << std::endl;
#endif
      if ((*actualItem)->isSetFlags(Flags::BOTTOM)) {
	state->erase((*actualItem));
	eraseItemMap((*actualItem)->getId());
	goto loop;
      }
      
      // X -> alpha • Y gamma
      else if ((*actualItem)->getRhs().size() > (*actualItem)->getIndex()
	       && !(*actualItem)->isCompleted()
	       && !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
	       && (*actualItem)->getCurrentTerms()->size() == 1
	       && !(*actualItem)->getCurrentTerms()->isOptional()
	       && grammar.isNonTerminal((*actualItem)->getCurrentTerm())
	       && !(*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()]->isNil()) {

#ifdef TRACE_CLOSE
	std::cerr << "####################### CLOSE (X -> α • Y β) #######################" << std::endl;
	(*actualItem)->print(std::cerr);
	std::cerr << std::endl;
#endif
	(*actualItem)->addFlags(Flags::SEEN);

	featuresPtr inheritedSonFeatures = (*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()];
	if (!inheritedSonFeatures->isNil() && !inheritedSonFeatures->isBottom()) {
	  if ((*actualItem)->getEnvironment() && (*actualItem)->getEnvironment()->size() > 0) {
	    bool effect = false;
	    (*actualItem)->getEnvironment()->replaceVariables(inheritedSonFeatures, effect);
	    inheritedSonFeatures->deleteAnonymousVariables();
	  }
	  
	  for (ruleSet::const_iterator iterRules = grammar.getRules().begin();
	       iterRules != grammar.getRules().end();
	       ++iterRules) {
	    if (((*iterRules)->getLhs()->getCode() == (*actualItem)->getCurrentTerm()->getCode())) {
	      
	      itemPtr it;
	      unsigned int i = (*iterRules)->incUsages();
	      if (i > maxUsages) {
		setMaxUsagesMsg(true);
	      } else {
		it = Item::create((*iterRules)->clone(), 0, 0, (*iterRules)->getStatements() ? (*iterRules)->getStatements()->clone(0) : statementsPtr());
		it->addRanges(row);
		it->setInheritedFeatures(inheritedSonFeatures->clone());

#ifdef TRACE_CLOSE
		std::cerr << "####################### CLOSE (Y -> • γ) #######################" << std::endl;
		it->print(std::cerr);
		std::cerr << std::endl;
#endif

		// record the item
		ItemSet::iterator found = state->find(it);
		if (found != state->end()) {
		  (*found)->addRef((*actualItem)->getId());
		  it.reset();
		} else {
		  it->addRef((*actualItem)->getId());
		  state->insert(it, this);
		  if (getMaxCardinalMsg()) {
		    FATAL_ERROR_MSG("maxCardinal");
		  }
		  insertItemMap(it);
		}
		modification = true;
		(*actualItem)->addFlags(Flags::SEEN);
	      }
	    }
	  }
	}
      }

      // X -> delta •
      else if ((*actualItem)->isCompleted()) {

	if (trace) {
	  std::cerr << "*** Rule reduced " << (*actualItem)->getFilename() << '(' << (*actualItem)->getLineno() << ')' << std::endl;
	}
	
#ifdef TRACE_REDUCE
	std::cerr << "####################### REDUCE Y -> γ • #######################" << std::endl;
	(*actualItem)->print(std::cerr);
	std::cerr << std::endl;
#endif
	(*actualItem)->addFlags(Flags::SEEN);
	if (!(*actualItem)->getSynthesizedFeatures()) {
	  FATAL_ERROR;
	} else {
	  if ((*actualItem)->getSynthesizedFeatures()->isNil()) {
	    if (warning){
	      std::ostringstream oss;
	      oss << "null synthesized feature structure " << (*actualItem)->getFilename() << '(' << (*actualItem)->getLineno() << ')' << std::endl;
	      WARNING_MSG(oss.str());
	    }
	    (*actualItem)->setSynthesizedFeatures(Features::create());
	  }
	  if (!(*actualItem)->getSynthesizedFeatures()->isBottom()) {
	    // If Axiom reduced or debug Transients
	    if (reduceAll || (*actualItem)->getRefs().size() == 0) {
#ifdef TRACE_REDUCE
	      std::cerr << "####################### REDUCE S -> γ • (AXIOM REDUCED) #######################" << std::endl;
	      (*actualItem)->print(std::cerr);
	      std::cerr << std::endl;
	      
#endif
	      
	      if ((*actualItem)->getEnvironment() && (*actualItem)->getEnvironment()->size() > 0){
		bool effect = false;
		(*actualItem)->getEnvironment()->replaceVariables((*actualItem)->getSynthesizedFeatures(), effect);
		if (effect){
#ifdef TRACE_REDUCE
		  std::cerr << "####################### REDUCE S -> γ • (AXIOM REDUCED) #######################" << std::endl;
		  (*actualItem)->print(std::cerr);
		  std::cerr << std::endl;
		  
#endif
		  
		  FATAL_ERROR;
		}
		(*actualItem)->getSynthesizedFeatures()->deleteAnonymousVariables();
	      }
	      
	      forestPtr forestFound = forestPtr();
	      forestIdentifierPtr fi = ForestIdentifier::create((*actualItem)->getLhs()->getCode(),
								((*actualItem)->getSynthesizedFeatures() ? (*actualItem)->getSynthesizedFeatures()->serialize() : std::string()),
								(*actualItem)->getRanges()[0],
								row);
	      ForestMap::mapForestIdentifierForest::const_iterator forestMapIt = forestMap.find(fi);
	      if (forestMapIt != forestMap.end()) {
		forestFound = (*forestMapIt).second;
		fi.reset();
	      } else {
		forestFound = Forest::create(Entry::create((*actualItem)->getLhs()->getCode()), (*actualItem)->getRanges()[0], row);
		forestMap.insert(std::make_pair(fi, forestFound));
		nodePtr node = Node::create();
		node->addForest(forestFound);
		nodeRoot->addForest(forestFound);
	      }
	      nodePtr node = Node::create();
	      for (unsigned int k = 0;
		   k < (*actualItem)->getForestIdentifiers().size();
		   ++k) {
	      	ForestMap::mapForestIdentifierForest::const_iterator forestMapIt = forestMap.find((*actualItem)->getForestIdentifiers()[k]);
		if (forestMapIt != forestMap.end()) {
		  node->getForests().push_back((*forestMapIt).second);
		}
	      }
	      forestFound->addNode(node);
	    }
	    for (std::set<unsigned int>::const_iterator ref = (*actualItem)->getRefs().begin();
		 ref != (*actualItem)->getRefs().end();
		 ++ref) {
	      itemPtr previousItem = getItemMap(*ref);
	      if (!previousItem) {
		std::cerr << "Ref:" << *ref ;
		FATAL_ERROR;
	      } else {
		
#ifdef TRACE_REDUCE
		std::cerr << "####################### REDUCE (X -> α • Y β) #######################" << std::endl;
		previousItem->print(std::cerr);
		std::cerr << std::endl;
#endif
		
#ifdef MEMOIZATION
		std::string key = keyMemoization(*actualItem, previousItem);
		memoizationMap::const_iterator memItem = memoizedItems.find(key);
		// Is this shift action already done ?
		if (memItem != memoizedItems.end()) {
		  memoizationValues result = memItem->second;
		  
		  for (memoizationValues::const_iterator i = result.begin();
		       i != result.end();
		       ++i) {

		    // New item build
		    itemPtr it = createItem(previousItem, row);
		    it->setEnvironment(previousItem->getEnvironment() ? previousItem->getEnvironment()->clone() : environmentPtr());
		    it->getSynthesizedSonFeatures()->push(previousItem->getIndex(), (*i).first);
		    //...
		    featuresPtr inheritedFeatures = it->getInheritedFeatures();
		    if (!inheritedFeatures->isNil() && !inheritedFeatures->isBottom()) {
		      if (it->getEnvironment() && it->getEnvironment()->size() > 0) {
			bool effect = false;
			it->getEnvironment()->replaceVariables(inheritedFeatures, effect);
			inheritedFeatures->deleteAnonymousVariables();
		      }
		    }		
		    
		    it->addForestIdentifiers(previousItem->getIndex(), (*i).second);
		    
#ifdef TRACE_REDUCE
		    std::cerr << "####################### MEMOIZED REDUCE (X -> α Y • β) #######################" << std::endl;
		    it->print(std::cerr);
		    std::cerr << std::endl;
#endif
		    it->setRefs(previousItem->getRefs());
		    states[row]->insert(it, this);
		    if (getMaxCardinalMsg()) {
		      FATAL_ERROR_MSG("maxCardinal");
		    }
		    insertItemMap(it);
		    modification = true;
		    (*actualItem)->addFlags(Flags::SEEN);
		  }
		}
		// This reduce action is new
		else
#endif
		  {
		    itemPtr it = createItem(previousItem, row);
		    it->setEnvironment(previousItem->getEnvironment() ? previousItem->getEnvironment()->clone() : environmentPtr());
		    it->getSynthesizedSonFeatures()->push(previousItem->getIndex(), (*actualItem)->getSynthesizedFeatures()->clone());
		    
		    //...
		    featuresPtr inheritedFeatures = it->getInheritedFeatures();
		    if (!inheritedFeatures->isNil() && !inheritedFeatures->isBottom()) {
		      if (it->getEnvironment() && it->getEnvironment()->size() > 0) {
			bool effect = false;
			it->getEnvironment()->replaceVariables(inheritedFeatures, effect);
			inheritedFeatures->deleteAnonymousVariables();
		      }
		    }		
		    
		    // On transmet le contexte de previousItem
		    nodePtr node = Node::create();
		    for (unsigned int k = 0;
			 k < (*actualItem)->getForestIdentifiers().size();
			 ++k) {
		      ForestMap::mapForestIdentifierForest::const_iterator forestMapIt = forestMap.find((*actualItem)->getForestIdentifiers()[k]);
		      forestPtr forest = (*forestMapIt).second;
		      node->getForests().push_back(forest);
		    }
		    forestPtr forestFound = forestPtr();
		    forestIdentifierPtr fi = ForestIdentifier::create((*actualItem)->getId(), std::string(), (*actualItem)->getRanges()[0], row);
		    ForestMap::mapForestIdentifierForest::const_iterator forestMapIt = forestMap.find(fi);
		    if (forestMapIt != forestMap.end()) {
		      forestFound = forestMapIt->second;
		      it->addForestIdentifiers(previousItem->getIndex(), forestMapIt->first);
		      fi.reset();
		    } else {
		      forestFound = Forest::create(Entry::create((*actualItem)->getLhs()->getCode()), (*actualItem)->getRanges()[0], row);
		      forestMap.insert(std::pair<forestIdentifierPtr, forestPtr>(fi, forestFound));
		      it->addForestIdentifiers(previousItem->getIndex(), fi);
		    }
		    if (!forestFound->addNode(node))
		      ;//FATAL_ERROR
		    ;
#ifdef TRACE_REDUCE
		    std::cerr << "####################### REDUCE (X -> α Y • β) #######################" << std::endl;
		    it->print(std::cerr);
		    std::cerr << std::endl;
#endif
		    ItemSet::iterator found = states[row]->find(it);
		    if (found != states[row]->end()) {
		      (*found)->addRefs(previousItem->getRefs());
		      it.reset();
		    } else {
#ifdef MEMOIZATION
		      // tabulates this result
		      std::string key = keyMemoization(*actualItem, previousItem);
		      featuresPtr memFeatures = (*it->getSynthesizedSonFeatures())[it->getIndex()-1];
		      forestIdentifierPtr memForestIdentifier = it->getForestIdentifiers()[it->getIndex()-1];
		      std::pair<featuresPtr, forestIdentifierPtr> memValue = std::pair<featuresPtr, forestIdentifierPtr> (memFeatures, memForestIdentifier);
		      memoizationMap::iterator memItem = memoizedItems.find(key);
		      
		      // Is this shift action already done ?
		      if (memItem != memoizedItems.end()) {
			memItem->second.push_back(memValue);
		      }
		      else {
			memoizationValues memValues;
			memValues.push_back(memValue);
			memoizedItems.insert(memoizationItem(key, memValues));
		      }
		      
#endif
		      // record the item
		      it->setRefs(previousItem->getRefs());
		      states[row]->insert(it, this);
		      if (getMaxCardinalMsg()) {
			FATAL_ERROR_MSG("maxCardinal");
		      }
		      insertItemMap(it);
		      modification = true;
		      (*actualItem)->addFlags(Flags::SEEN);
		    }
		  }
	      }
	    }
	  }
	}
      }

      // X -> alpha • t beta
      else if ((*actualItem)->getRhs().size() > (*actualItem)->getIndex()
	       && !(*actualItem)->isCompleted()
	       && !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
	       && (*actualItem)->getCurrentTerms()->size() == 1
	       && !(*actualItem)->getCurrentTerms()->isOptional()
	       && grammar.isTerminal((*actualItem)->getCurrentTerm())
	       && !(*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()]->isNil()) {
#ifdef TRACE_CLOSE
	std::cerr << "#######################  X -> alpha • t beta #######################" << std::endl;
	(*actualItem)->print(std::cerr);
	std::cerr << std::endl;
#endif
      }
      
      else {
	(*actualItem)->successor(state, this, modification);
      }
    }
  } while (modification);
  for (ItemSet::const_iterator i = state->begin(); i != state->end(); ++i)
    (*i)->subFlags(Flags::SEEN);
}

/* **************************************************
 *
 ************************************************** */
bool 
Synthesizer::shift(itemSetPtr state, unsigned int row) {
  bool modificationOnce = false;
  bool modification;
  do {
    modification = false;
    
    // Iterate through list
    for (ItemSet::iterator actualItem = state->begin();
	 actualItem != state->end() && !modification; 
	 ++actualItem) {
      if ((*actualItem)->isSetFlags(Flags::SEEN))
	continue;
      if ((*actualItem)->isSetFlags(Flags::BOTTOM))
	continue;
      if ((*actualItem)->getCurrentTerms()) {
	featuresPtr inheritedSonFeatures = (*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()];
	if (!(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
	    && !(*actualItem)->getCurrentTerms()->isOptional()
	    && (*actualItem)->getCurrentTerm()
	    && !inheritedSonFeatures->isNil()
	    && !inheritedSonFeatures->isBottom()
	    && grammar.getTerminals().find((*actualItem)->getCurrentTerm()->getCode()) != grammar.getTerminals().end()) {
	  
#ifdef TRACE_SHIFT
	  std::cerr << "####################### SHIFT (X -> α • ω β) where ω ∈ ℒ #######################" << std::endl;
	  (*actualItem)->print(std::cerr);
	  std::cerr << std::endl;
#endif
	  
	  
	  if ((*actualItem)->getEnvironment() && (*actualItem)->getEnvironment()->size() > 0) {
	    bool effect = false;
	    (*actualItem)->getEnvironment()->replaceVariables(inheritedSonFeatures, effect);
	    inheritedSonFeatures->deleteAnonymousVariables();
	  }
	  
#ifdef MEMOIZATION
	  // Is this shift action already done ?
	  std::string key = keyMemoization(*actualItem);
	  memoizationMap::const_iterator memItem = memoizedItems.find(key);
	  
	  if (memItem != memoizedItems.end()) {
	    memoizationValues result = memItem->second;

	    for (memoizationValues::const_iterator i = result.begin();
		 i != result.end();
		 ++i) {
	      // New item build
	      itemPtr it = createItem(*actualItem, row);

	      it->getSynthesizedSonFeatures()->push((*actualItem)->getIndex(), (*i).first);
	      it->setEnvironment((*actualItem)->getEnvironment() ? (*actualItem)->getEnvironment()->clone() : Environment::create());
	      it->addForestIdentifiers((*actualItem)->getIndex(), (*i).second);
	      
#ifdef TRACE_SHIFT
	      std::cerr << "####################### MEMOIZED SHIFT (X -> α ω • β) #######################" << std::endl;
	      it->print(std::cerr);
	      std::cerr << std::endl;
#endif
	      it->setRefs((*actualItem)->getRefs());
	      states[row]->insert(it, this);
	      if (getMaxCardinalMsg()) {
		FATAL_ERROR_MSG("maxCardinal");
	      }
	      insertItemMap(it);
	      modification = true;
	      modificationOnce = true;
	      (*actualItem)->addFlags(Flags::SEEN);
	    }
	  }
	  // This shift action is new
	  else
#endif
	    {
	      unsigned int pred = inheritedSonFeatures->assignPred();
	      std::string form = inheritedSonFeatures->assignForm();
	      /*
		std::cerr << "inheritedSonFeatures : ";
		inheritedSonFeatures->print(std::cerr);
		std::cerr << std::endl;
		std::cerr << "pred:" << pred << std::endl;
		std::cerr << "form:" << form << std::endl;
		//std::cerr << "POS : " << Vartable::intToStr((*actualItem)->getFirstCurrentTerm()->getCode()) << std::endl;
		*/
	      lexiconType::const_iterator foundCode = lexicon.find((*actualItem)->getCurrentTerm()->getCode());
	      if (foundCode != lexicon.end()
		  && (foundCode->second->size() != 0)) {
		std::map<unsigned int, entriesPtr> *listPred = foundCode->second;
		if (listPred) {
		std::map<unsigned int, entriesPtr>::const_iterator found;
		// stages : // 1) : without PRED or FORM
		// 2) : with FORM
		// 3) : with PRED
		bool cont = true;
		for (int stage = 1; cont && (stage <= 3); ++stage) {
		  entriesPtr entries = entriesPtr();
		  
		  // With FORM
		  if ((stage == 2) && (form.size() == 0))
		    continue;
		  
		  // With PRED
		  if ((stage == 3) && (pred == UINT_MAX))
		    continue;
		  
		  /*****
			std::cerr << "stage : " << stage << "<BR>" << std::endl;
			std::cerr << "pred : " << Vartable::intToStr(pred) << "<BR>" << std::endl;
			std::cerr << "form : " << form << "<BR>" << std::endl;
			**** */
		  
		  switch (stage) {
		  case 1: 
		    found = listPred->find(UINT_MAX);// Without pred : UINT_MAX = > ...
		    if (found != listPred->end()){
		      entries = found->second;
		    } else
		      break;
		  case 2: 
		    found = listPred->find(0);// IDENTITY : 0 = > ...
		    if (found != listPred->end())
		      entries = found->second;
		    break;
		  case 3: 
		    found = listPred->find(pred);// pred = > ...
		    if (found != listPred->end())
		      // Local lexicon
		      entries = found->second;
		    else if (compactLexicon) {
		      // Compact lexicon
		      entries = findCompactLexicon((*actualItem)->getCurrentTerm()->getCode(), pred);
		    }
		    break;
		  }
		  // Found !
		  if (entries) {
		    cont = false;
		    std::list<entryPtr>::const_iterator entry = entries->begin();
		    if (random) {
		      int rv = std::rand()/((RAND_MAX + 1u)/entries->size());
		      int i = 0;
		      while (i++ < rv)
			++entry;
		    }
		    int attempts = 1;
		    while (entry != entries->end()) {
		      
		      featuresPtr entryFeatures = (*entry)->getFeatures() ? (*entry)->getFeatures()->clone() : featuresPtr();
		      statementsPtr entryStatements = statementsPtr();
		      environmentPtr env = (*actualItem)->getEnvironment() ? (*actualItem)->getEnvironment()->clone() : Environment::create();
		      
		      // Filter !!
		      // entryFeatures subsumes ↑
		      if (stage == 2
			  || (entryFeatures && entryFeatures->subsumes(inheritedSonFeatures, env))) {
			// New item build
			itemPtr it = createItem(*actualItem, row);

			it->setEnvironment(env);

			featuresPtr resultFeatures = featuresPtr();
			statementPtr s = Statement::create();
			featuresPtr inheritedSonFeaturesCopy = inheritedSonFeatures->clone();
			featuresPtr entryFeaturesCopy = entryFeatures->clone();
			if (entryFeatures) {
			  resultFeatures = s->unif(entryFeaturesCopy, inheritedSonFeaturesCopy, it);
			} else
			  resultFeatures = inheritedSonFeaturesCopy;
			s.reset();
			if (resultFeatures) {
			  if (it->getEnvironment() && (it->getEnvironment()->size() > 0)){
			    bool effect = false;
			    it->getEnvironment()->replaceVariables(resultFeatures, effect);
			  }
			  resultFeatures->renameVariables((*entry)->getId());
			}
			
			it->getSynthesizedSonFeatures()->push((*actualItem)->getIndex(), resultFeatures);
			if (entryStatements)
			  entryStatements->renameVariables((*entry)->getId());
			entryPtr word;
			if (stage == 2)
			  word = Entry::create((*entry)->getCode(), UINT_MAX, form, resultFeatures);
			else {
			  size_t found = (*entry)->getForm().find('$');
			  if (found != std::string::npos){
			    bool effect = false;
			    word = Entry::create((*entry)->getCode(), (*entry)->getCodePred(), it->getEnvironment()->replaceVariables((*entry)->getForm(), effect), resultFeatures);
			  }
			  else
			    word = Entry::create((*entry)->getCode(), (*entry)->getCodePred(), (*entry)->getForm(), resultFeatures);
			}
			forestIdentifierPtr fi = ForestIdentifier::create(word->getId(), resultFeatures->serialize(), row - 1, row);
			ForestMap::mapForestIdentifierForest::const_iterator forestMapIt = forestMap.find(fi);
			if (forestMapIt != forestMap.end()) {
			  it->addForestIdentifiers((*actualItem)->getIndex(), (*forestMapIt).first);
			  fi.reset();
			  //std::cerr << "stage : " << stage << "<BR>" << std::endl;
			  //std::cerr << "pred : " << Vartable::intToStr(pred) << "<BR>" << std::endl;
			  //std::cerr << "form : " << form << "<BR>" << std::endl;
			} else {
			  forestMap.insert(std::pair<forestIdentifierPtr, forestPtr>(fi, Forest::create(word, row - 1, row)));
			  it->addForestIdentifiers((*actualItem)->getIndex(), fi);
			}
			
#ifdef TRACE_SHIFT
			std::cerr << "####################### SHIFT (X -> α ω • β) #######################" << std::endl;
			it->print(std::cerr);
			std::cerr << std::endl;
#endif
#ifdef MEMOIZATION
			// tabulates this result
			std::string key = keyMemoization(*actualItem);
						
			featuresPtr memFeatures = (*it->getSynthesizedSonFeatures())[it->getIndex()-1];
			forestIdentifierPtr memForestIdentifier = it->getForestIdentifiers()[it->getIndex()-1];
			std::pair<featuresPtr, forestIdentifierPtr> memValue = std::pair<featuresPtr, forestIdentifierPtr> (memFeatures, memForestIdentifier);
			memoizationMap::iterator memItem = memoizedItems.find(key);
			
			// Is this shift action already done ?
			if (memItem != memoizedItems.end()) {
			  memItem->second.push_back(memValue);
			}
			else {
			  memoizationValues memValues;
			  memValues.push_back(memValue);
			  memoizedItems.insert(memoizationItem(key, memValues));
			}
#endif
			// record the item
			it->setRefs((*actualItem)->getRefs());
			states[row]->insert(it, this);
			if (getMaxCardinalMsg()) {
			  FATAL_ERROR_MSG("maxCardinal");
			}
			insertItemMap(it);
		      }
		      modification = true;
		      modificationOnce = true;
		      (*actualItem)->addFlags(Flags::SEEN);
		      
		      if (random) {
			if (modification) {
			  break;
			}
			else {
			  if (++attempts > MAXATTEMPTS) {
			    std::cerr << "*** Random error: no lexical entry matching ";
			    (*actualItem)->getCurrentTerm()->print(std::cerr);
			    inheritedSonFeatures->print(cerr, true, true);
			    std::cerr << std::endl;
			    exit(1);
			  }
			  entry = entries->begin();
			  int rv = std::rand()/((RAND_MAX + 1u)/entries->size());
			  int i = 0;
			  while (i++ < rv)
			    ++entry;
			}
		      }
		      else {
			++entry;
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  } while (modification);
  for (ItemSet::const_iterator i = state->begin(); i != state->end(); ++i)
    (*i)->subFlags(Flags::SEEN);
  return modificationOnce;
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::generate() {
#ifdef OUTPUT_XML
  extern xmlNodePtr xmlNodeRoot;
#endif
  states.clear();
  itemMap.clear();
  forestMap.clear();
  mapLocalEntry.clear();
  for (ruleSet::const_iterator iterRules = grammar.getRules().begin();
       iterRules != grammar.getRules().end();
       ++iterRules) {
    (*iterRules)->resetUsages();
  }
  
  std::ofstream outfile;
  nodeRoot = Node::create();
  itemSetPtr initState = ItemSet::create(0);
  std::list<class Rule *> *rules = this->grammar.findRules(getStartTerm());
  itemPtr it;
  for (std::list<class Rule *>::const_iterator rule = rules->begin();
       rule != rules->end();
       ++rule) {
    (*rule)->incUsages();
    it = Item::create(*rule, UINT_MAX, 0, (*rule)->getStatements() ? (*rule)->getStatements()->clone(0) : statementsPtr());
    it->addRanges(0);
    it->setInheritedFeatures(getStartFeatures());
#ifdef TRACE_INIT
    std::cerr << "####################### INIT #######################" << std::endl;
    it->print(std::cerr);
    std::cerr << std::endl;
#endif
    insertItemMap(it);
    initState->insert(it, this);
    if (getMaxCardinalMsg()) {
      FATAL_ERROR_MSG("maxCardinal");
    }
  }

  states.insert(std::pair<unsigned int, itemSetPtr>(0, initState));
  close(initState, 0);
  
  unsigned int i = 0;
  while (i <= maxLength) {

#ifdef TRACE_STAGE
    std::cerr << "####################### STAGE #######################" << std::endl;
    initState->print(std::cerr);
    std::cerr << std::endl;
#endif

    itemSetPtr actualState = ItemSet::create(++i);
    states.insert(std::pair<unsigned int, itemSetPtr>(i, actualState));
    if (!shift(initState, i))
      break;
    actualState->resetUsages();
    close(actualState, i);
    initState = actualState;
  }

  if (i > maxLength) {
    FATAL_ERROR_MSG("maxLength");
  }
  if ((i % 121) == 0) {
    std::cerr << "Length : " << i << std::endl;
  }

  if (getMaxUsagesMsg()) {
    FATAL_ERROR_MSG("maxUsages");
  }
  nodeRoot->generate(this->random);
#ifdef OUTPUT_XML
  if (outXML) {
    nodeRoot->toXML(xmlNodeRoot, xmlNodeRoot);
  }
#endif
}

/* **************************************************
 *
 ************************************************** */
void 
Synthesizer::parseFile(std::string fileName) {
  init_buffer();
  pushBufferName(fileName);
  rulesin = fopen(fileName.c_str(), "r");
  if (!rulesin) {
    std::cerr << "*** error..."
	      << fileName
	      << std::endl;
    exit(1);
  }
  push_buffer();
  rulesparse();
  delete_buffer();
  fclose(rulesin);
  popBufferName();
}

/* **************************************************
 *
 ************************************************** */
int 
Synthesizer::parseString(std::string str, std::string buffer) {
  init_buffer();
  pushBufferName(buffer);
  scan_string(str);
  int result = rulesparse();
  delete_buffer();
  popBufferName();
  return result;
}

/* **************************************************
 *
 ************************************************** */
const entriesPtr 
Synthesizer::findCompactLexicon(const unsigned int code, const unsigned int pred) {
  unsigned long int info = ~0UL;
  std::string str = Vartable::intToStr(code) + "#" + Vartable::intToStr(pred);
  info = compactLexicon->searchStatic(compactLexicon->init, str);
  // in : pos#lemma
  // out : form#fs
#ifdef TRACE_LEXICON
  std::cerr << "####################### FIND IN THE COMPACT LEXICON #######################" << std::endl;
  std::cerr << "<DIV>" << std::endl;
  std::cerr << str << " => ";
compactLexicon->printResults(std::cerr, info, 1);
  std::cerr << "</DIV>" << std::endl;
  std::cerr << std::endl;
#endif
  if (info != ~0UL) {
    entriesPtr entries = Entries::create();
    while (info != ~0UL) {
      std::string result = compactLexicon->buffer + (compactLexicon->info[info].offset);
      std::string form = result.substr(0, result.find("#"));
      std::string data = result.substr(result.find("#"), -1);
      int rulesresult = parseString(data, std::string("Lexicon"));
      if (rulesresult == 0) {
	if (localEntry) {
	  localEntry->setCode(code);
	  localEntry->setForm(form);
	  std::string localEntrySignature = localEntry->serialize();
	  std::map<std::string, entryPtr>::iterator found = mapLocalEntry.find(localEntrySignature);
	  if (found != mapLocalEntry.end()) {
	    entries->add(found->second);
	  } else {
	    mapLocalEntry.insert(std::pair<std::string, entryPtr>(localEntrySignature, localEntry));
	    entries->add(localEntry);
	  }
	}
      } else {
	std::cerr << "Illegal lexical entry: " << form << " " << Vartable::intToStr(code) << " " << result.substr(result.find("#")+1, -1) << std::endl;
	FATAL_ERROR;
      }
      if ((compactLexicon->info[info].next) != (unsigned long int) (~(0UL)))
	info = compactLexicon->info[info].next;
      else
	info = (unsigned long int) (~(0UL));
    }
    return entries;
  } else
    return entriesPtr();
}
