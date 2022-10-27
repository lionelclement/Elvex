/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI, 
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
#include <fstream>
#include <sstream>

#include "synthesizer.hpp"
#include "compacted-lexicon.hpp"
#include "compacted-lexicon-buffer.hpp"
#include "statements.hpp"
#include "statement.hpp"
#include "messages.hpp"
#include "environment.hpp"
#include "forest.hpp"
#include "item.hpp"
#include "itemset.hpp"
#include "listfeatures.hpp"
#include "terms.hpp"
#include "rule.hpp"
#include "node.hpp"
#include "vartable.hpp"
#include "parser_exception.hpp"

/* **************************************************
 *
 ************************************************** */
Synthesizer::Synthesizer() {
    NEW
    this->compactedLexicon = nullptr;
    this->maxLength = MAXLENGTH;
    this->maxUsages = MAXUSAGES;
    this->maxItems = MAXITEMS;
    this->nodeRoot = nodePtr();
    this->lexiconFileName = std::string();
    this->rulesFileName = std::string();
    this->inputFileName = std::string();
#ifdef OUTPUT_XML
    this->outXML = nullptr;
#endif
    this->reduceAll = false;
    this->warning = false;
    this->random = false;
    this->one = false;
    this->attempsRandom = 1000;
    this->trace = false;
    this->verbose = false;
}

/* **************************************************
 *
 ************************************************** */
Synthesizer::~Synthesizer() {
    DELETE
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTrace() const {
    return trace;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTrace(bool _trace) {
    this->trace = _trace;
}

/* **************************************************
 *
 ************************************************** */
Synthesizer::itemSet_map_const_iterator Synthesizer::cbegin() const {
    return states.cbegin();
}

/* **************************************************
 *
 ************************************************** */
Synthesizer::itemSet_map_const_iterator Synthesizer::cend() const {
    return states.cend();
}

/* **************************************************
 *
 ************************************************** */
size_t Synthesizer::size() const {
    return states.size();
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setInputFileName(char *name) {
    inputFileName = name;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setLexiconFileName(char *name) {
    lexiconFileName = name;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setCompactedLexiconFileName(char *bufferName) {
    compactedLexiconFileName = bufferName;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setCompactedDirectoryName(char *DirectoryName) {
    compactedDirectoryName = DirectoryName;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setRulesFileName(char *name) {
    rulesFileName = name;
}

/* **************************************************
 *
 ************************************************** */
std::string Synthesizer::getInputFileName() const {
    return inputFileName;
}

/* **************************************************
 *
 ************************************************** */
std::string Synthesizer::getLexiconFileName() const {
    return lexiconFileName;
}

/* **************************************************
 *
 ************************************************** */
std::string Synthesizer::getCompactedLexiconFileName() const {
    return compactedLexiconFileName;
}

/* **************************************************
 *
 ************************************************** */
std::string Synthesizer::getCompactedDirectoryName() const {
    return compactedDirectoryName;
}

/* **************************************************
 *
 ************************************************** */
std::string Synthesizer::getRulesFileName() const {
    return rulesFileName;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setMaxLength(unsigned int _maxLength) {
    this->maxLength = _maxLength;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setMaxUsages(unsigned int _maxUsages) {
    this->maxUsages = _maxUsages;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setMaxItems(unsigned int _maxItems) {
    this->maxItems = _maxItems;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Synthesizer::getMaxItems() const {
    return this->maxItems;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Synthesizer::getMaxUsages() const {
    return this->maxUsages;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setCompactedLexicon(class CompactedLexicon* compactedLexicon) {
    this->compactedLexicon = compactedLexicon;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setReduceAll(const bool _reduceAll) {
    this->reduceAll = _reduceAll;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setRandom(const bool _random) {
    this->random = _random;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getRandom() const {
    return this->random;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setOne(const bool _one) {
    this->one = _one;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getOne() const {
    return this->one;
}

#ifdef OUTPUT_XML

/* **************************************************
 *
 ************************************************** */
void
Synthesizer::setOutXML(char *_outXML) {
    this->outXML = _outXML;
}

/* **************************************************
 *
 ************************************************** */
char *
Synthesizer::getOutXML() const {
    return this->outXML;
}

#endif

#ifdef TRACE_OPTION
/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTraceInit(bool traceInit)
{
   this->traceInit = traceInit;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTraceStage(bool traceStage)
{
   this->traceStage = traceStage;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTraceClose(bool traceClose)
{
   this->traceClose = traceClose;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTraceShift(bool traceShift)
{
   this->traceShift = traceShift;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTraceReduce(bool traceReduce)
{
   this->traceReduce = traceReduce;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTraceAction(bool traceAction)
{
   this->traceAction = traceAction;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTraceInit(void)
{
   return this->traceInit;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTraceStage(void)
{
   return this->traceStage;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTraceClose(void)
{
   return this->traceClose;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTraceShift(void)
{
   return this->traceShift;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTraceReduce(void)
{
   return this->traceReduce;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTraceAction(void)
{
   return this->traceAction;
}

#endif

/* **************************************************
 *
 ************************************************** */
std::list<std::string>& Synthesizer::getInputs() {
    return this->inputs;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::insertItemMap(const itemPtr& item) {
    if (!_itemMap.insert(std::make_pair(item->getId(), item)).second)
        FATAL_ERROR_UNEXPECTED;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::eraseItemMap(const unsigned int id) {
    if (!_itemMap.erase(id))
        FATAL_ERROR_UNEXPECTED;
}

/* **************************************************
 *
 ************************************************** */
itemPtr Synthesizer::getItemMap(const unsigned int id) {
    return this->_itemMap.at(id);
}

/* **************************************************
 *
 ************************************************** */
nodePtr Synthesizer::getNodeRoot() {
    return nodeRoot;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::addInput(const std::string& input) {
    return this->inputs.push_back(input);
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::printState(std::ostream& outStream, const itemSetPtr& state) {
    outStream << "Q" << state->getId();
    state->print(outStream);
}

/* **************************************************
 *
 ************************************************** */
std::string
Synthesizer::keyMemoization(const itemPtr& actualItem, const itemPtr& previousItem) {
    return std::to_string(actualItem->getId()) + '.' + std::to_string(previousItem->currentTerm()) +
           actualItem->getSynthesizedFeatures()->peekSerialString();
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::clear() {
    states.clear();
    forestMap.clear();
    _itemMap.clear();
    memoizedMap.clear();
}

/* **************************************************
 * erreur:
 * les items sont enregistrés dans state et sont modifiés...
 ************************************************** */
void Synthesizer::close(Parser& parser, itemSetPtr state, unsigned int row) {
    bool modification;
    do {
        modification = false;
        // Iterate through list
        for (ItemSet::set_of_item_iterator actualItem = state->begin();
             actualItem != state->end() && !modification; 
             ++actualItem) {

            if ((*actualItem)->isSetFlags(Flags::SEEN | Flags::BOTTOM)) {
                continue;
            }

#ifdef TRACE_OPTION
              if (traceClose) {
                  std::cout << "<H3>####################### LOOP #######################</H3>" << std::endl;
                  (*actualItem)->print(std::cout);
                  std::cout << std::endl;
              }
#endif

            if ((*actualItem)->isSetFlags(Flags::BOTTOM)) {
                FATAL_ERROR_UNEXPECTED;
            }

            if (verbose && trace) {
                std::cout << "*** Item: " << (*actualItem)->getId() << std::endl;
            }

            // X -> alpha • [Y] gamma
            if (((*actualItem)->sizeRuleRhs() > (*actualItem)->getIndex())
                    && !(*actualItem)->isCompleted() 
                    && !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
                    && (*actualItem)->currentTerms()->isOptional()) {

#ifdef TRACE_PASS
                std::cout << "<H3>####################### PASS : X -> alpha • [Y] gamma #######################</H3>" << std::endl;
                (*actualItem)->print(std::cout);
                std::cout << std::endl;
#endif  
                
                itemPtr it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
                it->setRule((*actualItem)->getRule()->clone());
                
                // add to Forests
                forestPtr forestFound = forestPtr();
                forestIdentifierPtr fi = ForestIdentifier::create(UINT_MAX,
                                                                  row,
                                                                  row,
                                                                  std::string());
                auto forestMapIt = forestMap.find(fi);
                if (forestMapIt != forestMap.cend()) {
                    forestFound = forestMapIt->second;
                    fi.reset();
                    it->addForestIdentifiers(it->getIndex(), forestMapIt->first);
                } else {
                    forestFound = Forest::create(Entry::create(UINT_MAX), row, row);
                    forestMap.insert(fi, forestFound);
                    it->addForestIdentifiers(it->getIndex(), fi);
                }
                
                it->setIndex((*actualItem)->getIndex() + 1);
                it->addRanges(row);

#ifdef TRACE_PASS
                std::cout << "<H3>####################### PASS: X -> alpha [Y] • gamma #######################</H3>" << std::endl;
                it->print(std::cout);
                std::cout << std::endl;
#endif
                state->insert(it, this);
                insertItemMap(it);
                
                it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
                it->setRule((*actualItem)->getRule()->clone());
                it->setIndex((*actualItem)->getIndex());
                it->currentTerms()->unsetOptional();

#ifdef TRACE_PASS
                std::cout << "<H3>####################### PASS: X -> alpha • Y gamma #######################</H3>" << std::endl;
                it->print(std::cout);
                std::cout << std::endl;
#endif
                state->insert(it, this);
                insertItemMap(it);

 #ifdef TRACE_PASS
                 std::cout << "<H3>####################### PASS: X -> alpha • Y gamma #######################</H3>" << std::endl;
                 state->print(std::cout);
                 std::cout << "<H3>#######################  #######################</H3>" << std::endl;
                 (*actualItem)->print(std::cout);
                 std::cout << std::endl;
 #endif
                state->erase(*actualItem);
                eraseItemMap((*actualItem)->getId());
#ifdef TRACE_PASS
                std::cout << "<H3>####################### PASS: CON'T #######################</H3>" << std::endl;
                state->print(std::cout);
                std::cout << std::endl;
#endif

                modification = true;
                break;
            }
            
            // X -> alpha • Y1|Y2 beta
            if (((*actualItem)->sizeRuleRhs() > (*actualItem)->getIndex()) 
                    && !(*actualItem)->isCompleted() 
                    && !(*actualItem)->currentTerms()->isOptional()
                    && (*actualItem)->currentTerms()->size() > 1) {

#ifdef TRACE_UNFOLD
                std::cout << "<H3>####################### UNFOLD #######################</H3>" << std::endl;
                (*actualItem)->print(std::cout);
                std::cout << std::endl;
#endif

                (*actualItem)->addFlags(Flags::SEEN);
             
                termsPtr terms = (*actualItem)->currentTerms();
                for (unsigned int indexTerm = 0; indexTerm < terms->size(); ++indexTerm) {
                    itemPtr it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
                    it->setRule((*actualItem)->getRule()->clone());
                    it->setCurrentTerms(Terms::create((*terms)[indexTerm]));
                    it->putIndexTerms((*actualItem)->getIndex(), indexTerm);
                    
#ifdef TRACE_PASS
                    std::cout << "<H3>####################### UNFOLD: insert #######################</H3>" << std::endl;
                    it->print(std::cout);
                    std::cout << std::endl;
#endif
                    state->insert(it, this);
                    insertItemMap(it);
                 }
                state->erase((*actualItem));
                eraseItemMap((*actualItem)->getId());
                modification = true;
                break;
            }

            (*actualItem)->apply(parser, this);

            if ((*actualItem)->isSetFlags(Flags::BOTTOM)) {
                state->erase(*actualItem);
                eraseItemMap((*actualItem)->getId());
                modification = true;
                break;
            }

            // X -> alpha • Y gamma
            if (        (*actualItem)->getIndex() != UINT_MAX
                        && (*actualItem)->sizeRuleRhs() > (*actualItem)->getIndex() 
                        && !(*actualItem)->isCompleted() 
                        && !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
                        && (*actualItem)->currentTerms()->size() == 1 
                        && !(*actualItem)->currentTerms()->isOptional()
                        && parser.getRules().isNonTerminal((*actualItem)->currentTerm()) 
                        && !(*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()]->isNil()) {

#ifdef TRACE_OPTION
                if (traceClose) {
                   std::cout << "<H3>####################### CLOSE (X -> α • Y β) #######################</H3>" << std::endl;
                   (*actualItem)->print(std::cout);
                   std::cout << std::endl;
                }
#endif
                if (verbose && trace && (*actualItem)->getRuleTrace()) {
                    std::cout << "*** Trying Close" << std::endl;
                    (*actualItem)->getRule()->print(std::cout, (*actualItem)->getIndex(), false, false);
                    std::cout << std::endl << std::endl;
                }

                (*actualItem)->addFlags(Flags::SEEN);

                featuresPtr inheritedSonFeatures = (*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()];
                if (!inheritedSonFeatures->isNil() && !inheritedSonFeatures->isBottom()) {
                    if ((*actualItem)->getEnvironment() && (*actualItem)->getEnvironment()->size() > 0) {
                        bool effect = false;
                        (*actualItem)->getEnvironment()->replaceVariables(inheritedSonFeatures, effect);
                        inheritedSonFeatures->deleteAnonymousVariables();
                    }

                    for (const auto &iterRules : parser.getRules().getRules()) {
                        if ((iterRules->getLhs() == (*actualItem)->currentTerm())) {

                            itemPtr it;
                            iterRules->incUsages(this);
                            it = Item::create(iterRules->clone(), 
                                              iterRules->getStatements() ? iterRules->getStatements()->clone(0)
                                                                         : statementsPtr());
                            it->addRanges(row);
                            it->setInheritedFeatures(inheritedSonFeatures->clone());

#ifdef TRACE_OPTION
                            if (traceClose) {
                               std::cout << "<H3>####################### CLOSE (Y -> γ) #######################</H3>" << std::endl;
                               it->print(std::cout);
                               std::cout << std::endl;
                            }
#endif

                            if (trace && (it)->getRuleTrace()) {
                                std::cout << "*** Close" << std::endl;
                                (*actualItem)->getRule()->print(std::cout, (*actualItem)->getIndex(), false, false);
                                std::cout << std::endl << "↓" << (*actualItem)->getIndex() + 1 << ':';
                                (*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()]->flatPrint(
                                        std::cout);
                                std::cout << std::endl << " => " << std::endl;
                                it->getRule()->print(std::cout, it->getIndex(), false, false);
                                std::cout << std::endl << std::endl;
                            }

                            // record the item
                            auto found = state->find(it);
                            if (found != state->cend()) {
                                itemPtr item = (*found);
                                state->erase((*found));
                                eraseItemMap((*found)->getId());
                                item->addRef((*actualItem)->getId());
                                state->insert(item, this);
                                insertItemMap(item);
                                it.reset();
                            } else {
                                it->addRef((*actualItem)->getId());
                                state->insert(it, this);
                                insertItemMap(it);
                            }
                            modification = true;
                            (*actualItem)->addFlags(Flags::SEEN);
                        }
                    }
                }
                if (!modification){
                    FATAL_ERROR_UNEXPECTED;
                }
            }

                // X -> delta •
            else if ((*actualItem)->isCompleted()) {

#ifdef TRACE_OPTION
                if (traceReduce) {
                   std::cout << "<H3>####################### REDUCE Y -> γ • (actual) #######################</H3>" << std::endl;
                   (*actualItem)->print(std::cout);
                   std::cout << std::endl;
                }
#endif
                
                if (verbose && trace && (*actualItem)->getRuleTrace()) {
                    std::cout << "*** Trying Reduce \n";
                    (*actualItem)->getRule()->print(std::cout, (*actualItem)->getIndex(), false, false);
                    std::cout << std::endl << std::endl;
                }

                (*actualItem)->addFlags(Flags::SEEN);
                if (!(*actualItem)->getSynthesizedFeatures()) {
                    FATAL_ERROR_UNEXPECTED
                } else {
                    if ((*actualItem)->getSynthesizedFeatures()->isNil()) {
                        if (warning) {
                            std::ostringstream oss;
                            oss << "null synthesized feature structure " << (*actualItem)->getRuleFilename() << '('
                                << (*actualItem)->getRuleLineno() << ')' << std::endl;
                            throw fatal_exception(oss);
                        }
                        (*actualItem)->setSynthesizedFeatures(Features::create());
                    }
                    if (!(*actualItem)->getSynthesizedFeatures()->isBottom()) {

                        // If Axiom reduced or debug Transients
                        if (reduceAll || (*actualItem)->emptyRefs()) {
#ifdef TRACE_OPTION
                            if (traceReduce) {
                               std::cout << "<H3>####################### REDUCE S -> γ • (AXIOM REDUCED) #######################</H3>" << std::endl;
                               (*actualItem)->print(std::cout);
                               std::cout << std::endl;
                            }
#endif

                            if ((*actualItem)->getEnvironment() && (*actualItem)->getEnvironment()->size() > 0) {
                                bool effect = false;
                                (*actualItem)->getEnvironment()->replaceVariables(
                                        (*actualItem)->getSynthesizedFeatures(), effect);
                                if (effect) {
#ifdef TRACE_OPTION
                                    if (traceReduce) {
                                       std::cout << "<H3>####################### REDUCE S -> γ • (AXIOM REDUCED) #######################</H3>" << std::endl;
                                       (*actualItem)->print(std::cout);
                                       std::cout << std::endl;
                                    }
#endif
                                    FATAL_ERROR_UNEXPECTED
                                }
                                (*actualItem)->getSynthesizedFeatures()->deleteAnonymousVariables();
                            }

                            forestPtr forestFound = forestPtr();
                            forestIdentifierPtr fi = ForestIdentifier::create((*actualItem)->getRuleLhs(),
                                                                              (*actualItem)->getRanges()[0],
                                                                              row, 
                                                                              ((*actualItem)->getSynthesizedFeatures()
                                                                               ? (*actualItem)->getSynthesizedFeatures()->peekSerialString()
                                                                               : std::string()));
                            auto forestMapIt = forestMap.find(fi);
                            if (forestMapIt != forestMap.cend()) {
                                forestFound = (*forestMapIt).second;
                                fi.reset();
                            } else {
                                forestFound = Forest::create(Entry::create((*actualItem)->getRuleLhs()),
                                                             (*actualItem)->getRanges()[0], 
                                                             row);
                                if (!forestMap.insert(fi, forestFound))
                                    FATAL_ERROR_UNEXPECTED;
                                nodePtr node = Node::create();
                                node->push_back(forestFound);
                                nodeRoot->push_back(forestFound);
                            }
                            nodePtr node = Node::create();
                            for (auto& forestIdentifierPtr : (*actualItem)->getForestIdentifiers()) {
                                auto _forestMapIt = forestMap.find(forestIdentifierPtr);
                                if (_forestMapIt != forestMap.cend()) {
                                    node->push_back((*_forestMapIt).second);
                                }
                            }
                            forestFound->push_back_node(node);
                        }
                        for (auto ref : (*actualItem)->getRefs()) {
                            itemPtr previousItem = getItemMap(ref);
                            if (!previousItem) {
                                FATAL_ERROR_UNEXPECTED
                            } else {

#ifdef TRACE_OPTION
                                if (traceReduce) {
                                   std::cout << "<H3>####################### REDUCE (X -> α • Y β) (previous) #######################</H3>" << std::endl;
                                   previousItem->print(std::cout);
                                   std::cout << std::endl;
                                }
#endif


                                std::string key = keyMemoization(*actualItem, previousItem);
                                auto memItem = memoizedMap.find(key);
                                // Is this already done ?
                                if (memItem != memoizedMap.cend()) {
                                    std::vector<memoizationValuePtr> result = memItem->second;
                                    for (std::vector<memoizationValuePtr>::const_iterator i = result.cbegin();
                                         i != result.cend();
                                         ++i) {
                                            CERR_LINE;
                                        // New item build
                                        itemPtr it = previousItem->clone();
                                        it->addRanges(row);
                                        it->getSynthesizedSonFeatures()->add(previousItem->getIndex(),
                                                                             (*i)->getFeatures());
                                        //...
                                        featuresPtr inheritedFeatures = it->getInheritedFeatures();
                                        if (!inheritedFeatures->isNil() && !inheritedFeatures->isBottom()) {
                                            if (it->getEnvironment() && it->getEnvironment()->size() > 0) {
                                                bool effect = false;
                                                it->getEnvironment()->replaceVariables(inheritedFeatures, effect);
                                                inheritedFeatures->deleteAnonymousVariables();
                                            }
                                        }
                                        it->addForestIdentifiers(previousItem->getIndex(), (*i)->getForestIdentifier());

#ifdef TRACE_MEMOIZATION
                                        std::cout << "<H3>####################### MEMOIZED REDUCE (X -> α Y • β) #######################</H3>" << std::endl;
                                        it->print(std::cout);
                                        std::cout << std::endl;
#endif
                                        it->setRefs(previousItem->getRefs());

                                        auto found = states[row]->find(it);
                                        if (found != states[row]->cend()) {
                                            (*found)->setRefs(previousItem->getRefs());
                                            it.reset();
                                                modification = true;
                                        } else {
                                            states[row]->insert(it, this);
                                            insertItemMap(it);
                                            modification = true;
                                        }
                                        (*actualItem)->addFlags(Flags::SEEN);
                                    }
                                }
                                    // This reduce action is new
                                else {
                                    itemPtr it = previousItem->clone();
                                    it->setIndex(previousItem->getIndex()+1);
                                    it->addRanges(row);
                                    it->getSynthesizedSonFeatures()->add(previousItem->getIndex(),
                                                                         (*actualItem)->getSynthesizedFeatures()->clone());

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
                                    for (auto &forestIdentifierPtr : (*actualItem)->getForestIdentifiers()) {
                                        auto forestMapIt = forestMap.find(forestIdentifierPtr);
                                        if (forestMapIt == forestMap.cend()) {
                                            FATAL_ERROR_UNEXPECTED
                                        }
                                        forestPtr forest = (*forestMapIt).second;
                                        node->push_back(forest);
                                    }
                                    forestPtr forestFound = forestPtr();
                                    forestIdentifierPtr fi = ForestIdentifier::create((*actualItem)->getId(),
                                                                                      (*actualItem)->getRanges()[0],
                                                                                      row,
                                                                                      std::string());
                                    auto forestMapIt = forestMap.find(fi);
                                    if (forestMapIt != forestMap.cend()) {
                                        forestFound = forestMapIt->second;
                                        it->addForestIdentifiers(previousItem->getIndex(), forestMapIt->first);
                                        modification = true;
                                        fi.reset();
                                    } else {
                                        forestFound = Forest::create(Entry::create((*actualItem)->getRuleLhs()),
                                                                     (*actualItem)->getRanges()[0], 
                                                                     row);
                                        if (!forestMap.insert(fi, forestFound))
                                            FATAL_ERROR_UNEXPECTED;
                                        it->addForestIdentifiers(previousItem->getIndex(), fi);
                                    }

                                    forestFound->push_back_node(node);
#ifdef TRACE_OPTION
                                    if (traceReduce) {
                                       std::cout << "<H3>####################### REDUCE (X -> α Y • β) #######################</H3>" << std::endl;
                                       it->print(std::cout);
                                       std::cout << std::endl;
                                    }
#endif
                                    if (trace && it->getRuleTrace()) {
                                        std::cout << "*** Reduce \n";
                                        (*actualItem)->getRule()->print(std::cout, (*actualItem)->getIndex(), false,
                                                                        false);
                                        std::cout << std::endl << "⇑:";
                                        (*actualItem)->getSynthesizedFeatures()->flatPrint(std::cout);
                                        std::cout << std::endl;
                                        it->getRule()->print(std::cout, previousItem->getIndex(), false, false);
                                        std::cout << std::endl << " => " << std::endl;
                                        it->getRule()->print(std::cout, it->getIndex(), false, false);
                                        std::cout << std::endl << std::endl;
                                    }
                                    
                                    auto found = states[row]->find(it);
                                    if (found != states[row]->cend()) {
                                        itemPtr item = *found;
                                        state->erase((*found));
                                        eraseItemMap((*found)->getId());
                                        item->setRefs(previousItem->getRefs());
                                        state->insert(item, this);
                                        insertItemMap(item);
                                        modification = true;
                                        it.reset();
                                    } else {
                                        // tabulates this result
                                        // std::string key = keyMemoization(*actualItem, previousItem);
                                        memoizedMap.insert(key,
                                                           (*it->getSynthesizedSonFeatures())[previousItem->getIndex()],
                                                           it->getForestIdentifiers()[previousItem->getIndex()]);
                                        // record the item
                                        it->setRefs(previousItem->getRefs());
                                        states[row]->insert(it, this);
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
            else if (   (*actualItem)->getIndex() != UINT_MAX
                        && (*actualItem)->sizeRuleRhs() > (*actualItem)->getIndex() 
                        && !(*actualItem)->isCompleted() 
                        && !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
                        && (*actualItem)->currentTerms()->size() == 1 
                        && !(*actualItem)->currentTerms()->isOptional()
                        && parser.getRules().isTerminal((*actualItem)->currentTerm()) 
                        && !(*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()]->isNil()) {
            } 
            
            else {

                itemPtr item = (*actualItem)->clone();
                item->next(modification);
                if (modification){
                    state->erase((*actualItem));
                    eraseItemMap((*actualItem)->getId());
                    state->insert(item, this);
                    insertItemMap(item);
                   break;
                }
            }
        }
    } while (modification);
    for (const auto& i : *state)
        i->subFlags(Flags::SEEN);
#ifdef TRACE_OPTION
        if (traceStage) {
           std::cout << "<H3>####################### STAGE " << state->getId() << " #######################</H3>" << std::endl;
           state->print(std::cout);
           std::cout << std::endl;
        }
#endif
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::shift(class Parser& parser, itemSetPtr state, unsigned int row) {
    bool modificationOnce = false;
    bool modification;
    do {
        modification = false;

        // Iterate through list
        for (auto actualItem = state->begin();
            actualItem != state->end() && !modification; 
            ++actualItem) {
            if ((*actualItem)->isSetFlags(Flags::SEEN))
                continue;
            if ((*actualItem)->isSetFlags(Flags::BOTTOM))
                continue;
            if ((*actualItem)->currentTerms()) {
                featuresPtr inheritedSonFeatures = (*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()];
                if (!(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()] 
                    && !(*actualItem)->currentTerms()->isOptional() 
                    && (*actualItem)->currentTerms()->size() == 1
                    && !inheritedSonFeatures->isNil() && !inheritedSonFeatures->isBottom()
                    && parser.getRules().getTerminals().find((*actualItem)->currentTerm()) != parser.getRules().getTerminals().end()) {

#ifdef TRACE_OPTION
                    if (traceShift) {
                       std::cout << "<H3>####################### SHIFT (X -> α • ω β) where ω ∈ ℒ #######################</H3>" << std::endl;
                       (*actualItem)->print(std::cout);
                       std::cout << std::endl;
                    }
#endif

                    if (verbose && trace && (*actualItem)->getRuleTrace()) {
                        std::cout << "*** Trying Shift " << std::endl;
                        (*actualItem)->getRule()->print(std::cout, (*actualItem)->getIndex(), false, false);
                        std::cout << std::endl << std::endl;
                    }

                    if ((*actualItem)->getEnvironment() && (*actualItem)->getEnvironment()->size() > 0) {
                        bool effect = false;
                        (*actualItem)->getEnvironment()->replaceVariables(inheritedSonFeatures, effect);
                        inheritedSonFeatures->deleteAnonymousVariables();
                    }

                    std::string* form = nullptr;
                    unsigned int pred = inheritedSonFeatures->assignPred();
                    Stage _stage;
                    if (pred == UINT_MAX) {
                        form = inheritedSonFeatures->assignForm();
                        if (form)
                            _stage = FORM_FEATURES;
                        else
                            _stage = MORPHO_FEATURES;
                    }
                    else {
                        _stage = PRED_FEATURES;
                    }

                    /*
                     std::cerr << "inheritedSonFeatures : ";
                     inheritedSonFeatures->print(std::cerr);
                     std::cerr << std::endl;
                     std::cerr << "pred:" << pred << std::endl;
                     std::cerr << "form:" << form << std::endl;
                     //std::cerr << "POS : " << Vartable::codeToString((*actualItem)->getFirstCurrentTerm()->getCode()) << std::endl;
                     */
                    auto foundCode = parser.findCacheLexicon((*actualItem)->currentTerm());
                    if (foundCode != parser.cendCacheLexicon() && (!foundCode->second->empty())) {
                        Parser::entries_map* listPred = foundCode->second;
                        if (listPred) {
                            Parser::entries_map::const_iterator found;
                            entriesPtr entries = entriesPtr();

                            /* ***** 
                            CERR_LINE;
                            std::cerr << "stage : " << _stage << std::endl;
                            std::cerr << "pred : " << Vartable::codeToString(pred) << std::endl;
                            std::cerr << "form : \"" << (form ? *form : "nullptr") << '"' << std::endl;
                            ***** */
                            switch (_stage) {

                                case MORPHO_FEATURES:
                                    entries = findByPos(parser, listPred, (*actualItem)->currentTerm());
                                    break;

                                case FORM_FEATURES:
                                    entries = findByForm(listPred);
                                    break;

                                case PRED_FEATURES:
                                    entries = findByPred(parser, listPred, (*actualItem)->currentTerm(), pred);
                                    if (!entries)
                                        entries = findByPos(parser, listPred, (*actualItem)->currentTerm());
                                    break;
                            }

                            // Found !
                            if (entries) {
                                //cont = false;
                                auto entryIt = entries->begin();
                                int tryRandom = 0;
                                while (entryIt != entries->end()) {
                                    entryPtr entry = *entryIt;
                                    if (this->getRandom()) {
                                        if (tryRandom++ > attempsRandom)
                                            break;
                                        size_t rv = std::rand() / ((RAND_MAX + 1u) / entries->size());
                                        entry = entries->get(rv);
                                    } else {
                                        entry = *entryIt;
                                        ++entryIt;
                                    }

                                    featuresPtr entryFeatures = entry->getFeatures() ? entry->getFeatures()->clone()
                                                                                     : featuresPtr();
                                    statementsPtr entryStatements = statementsPtr();
                                    environmentPtr env = (*actualItem)->getEnvironment()
                                                         ? (*actualItem)->getEnvironment()->clone()
                                                         : Environment::create();

                                    // Filter !!
                                    // entryFeatures subsumes ↑
                                    if (_stage == FORM_FEATURES ||
                                        (entryFeatures && entryFeatures->subsumes(inheritedSonFeatures, env))) {

                                        // New item build
                                        itemPtr it = (*actualItem)->clone();
                                        it->setIndex((*actualItem)->getIndex()+1);
                                        it->addRanges(row);
                                        it->setEnvironment(env);

                                        featuresPtr resultFeatures = featuresPtr();
                                        statementPtr s = Statement::create();
                                        featuresPtr inheritedSonFeaturesCopy = inheritedSonFeatures->clone();
                                        featuresPtr entryFeaturesCopy = entryFeatures->clone();
                                        if (entryFeatures) {
                                            resultFeatures = s->unif(entryFeaturesCopy, inheritedSonFeaturesCopy,
                                                                     it);
                                        } else
                                            resultFeatures = inheritedSonFeaturesCopy;
                                        s.reset();
                                        if (resultFeatures) {
                                            if (it->getEnvironment() && (it->getEnvironment()->size() > 0)) {
                                                bool effect = false;
                                                it->getEnvironment()->replaceVariables(resultFeatures, effect);
                                            }
                                            resultFeatures->renameVariables(entry->getId());
                                        }

                                        it->getSynthesizedSonFeatures()->add((*actualItem)->getIndex(),
                                                                             entryFeaturesCopy);
                                        if (entryStatements)
                                            entryStatements->renameVariables(entry->getId());
                                        entryPtr word;
                                        if (_stage == FORM_FEATURES)
                                            word = Entry::create(entry->getPos(), UINT_MAX, *form, resultFeatures);
                                        else {
                                            size_t _found = entry->getForm().find('$');
                                            if (_found != std::string::npos) {
                                                bool effect = false;
                                                std::string _form = entry->getForm();
                                                it->getEnvironment()->replaceVariables(_form, effect);

                                                word = Entry::create(entry->getPos(), entry->getPred(), _form,
                                                                     resultFeatures);
                                            } else {
                                                word = Entry::create(entry->getPos(), entry->getPred(),
                                                                     entry->getForm(), resultFeatures);
                                            }
                                        }
                                        forestIdentifierPtr fi = ForestIdentifier::create(word->getId(),
                                                                                           row - 1, 
                                                                                            row,
                                                                                            resultFeatures->peekSerialString());
                                        auto forestMapIt = forestMap.find(fi);
                                        if (forestMapIt != forestMap.cend()) {
                                            it->addForestIdentifiers((*actualItem)->getIndex(),
                                                                     (*forestMapIt).first);
                                            fi.reset();
                                            //std::cerr << "stage : " << stage! << "<BR>" << std::endl;
                                            //std::cerr << "pred : " << Vartable::codeToString(pred) << "<BR>" << std::endl;
                                            //std::cout << "form : " << form << "<BR>" << std::endl;
                                        } else {
                                            if (!forestMap.insert(fi, Forest::create(word, row - 1, row)))
                                                FATAL_ERROR_UNEXPECTED;
                                            it->addForestIdentifiers((*actualItem)->getIndex(), fi);
                                        }
                                        it->setRefs((*actualItem)->getRefs());

#ifdef TRACE_OPTION
                                        if (traceShift) {
                                            std::cout << "<H3>####################### SHIFT (X -> α ω • β) #######################</H3>" << std::endl;
                                            it->print(std::cout);
                                            std::cout << std::endl;
                                        }
#endif


                                        if (trace && it->getRuleTrace()) {
                                            std::cout << "*** Shift " << entry->getForm() << std::endl;
                                            it->getRule()->print(std::cout, (*actualItem)->getIndex(), false, false);
                                            std::cout << std::endl << "↓" << it->getIndex() << ':';
                                            (*it->getInheritedSonFeatures())[(*actualItem)->getIndex()]->flatPrint(
                                                    std::cout);
                                            std::cout << std::endl << " => " << std::endl;
                                            it->getRule()->print(std::cout, it->getIndex(), false, false);
                                            std::cout << std::endl << std::endl;
                                        }

CERR_LINE;
#ifdef TRACE_OPTION
                                        if (traceShift) {
                                            std::cout << "<H3>####################### #######################</H3>" << std::endl;
                                            it->print(std::cout);
                                            std::cout << "<H3>####################### #######################</H3>" << std::endl;
                                            states[row]->print(std::cout);
                                            std::cout << "<H3>####################### #######################</H3>" << std::endl;
                                            std::cout << std::endl;
                                        }
#endif
                                        // record the item
                                        states[row]->insert(it, this);
CERR_LINE;
                                        insertItemMap(it);
CERR_LINE;
                                        (*actualItem)->addFlags(Flags::SEEN);
CERR_LINE;
#ifdef TRACE_OPTION
                                        if (traceShift) {
                                            std::cout << "<H3>####################### #######################</H3>" << std::endl;
                                            it->print(std::cout);
                                            std::cout << "<H3>####################### #######################</H3>" << std::endl;
                                            states[row]->print(std::cout);
                                            std::cout << std::endl;
                                        }
#endif
CERR_LINE;
                                        if (this->getRandom()) {
                                            break;
                                        }
                                        modification = true;
                                        modificationOnce = true;




                                    }
                                }
                            }
                        }
                    }
                    else {
                        FATAL_ERROR_UNEXPECTED;
                    }
                }
            }
        }
    } while (modification);
    for (const auto& i : *state)
        i->subFlags(Flags::SEEN);
    return modificationOnce;
}

/* **************************************************
 * Main loop
 ************************************************** */
void Synthesizer::generate(class Parser& parser) {
#ifdef OUTPUT_XML
    extern xmlNodePtr xmlNodeRoot;
#endif
    states.clear();
    _itemMap.clear();
    forestMap.clear();
    for (const auto& iterRules : parser.getRules().getRules()) {
        iterRules->resetUsages();
    }

    std::ofstream outfile;
    nodeRoot = Node::create();
    itemSetPtr initState = ItemSet::create(0);
    std::list<rulePtr>* rules = parser.getRules().findRules(parser.getStartTerm());
    itemPtr it;
    for (std::list<rulePtr>::const_iterator rule = rules->begin(); rule != rules->end(); ++rule) {
        (*rule)->incUsages(this);
        it = Item::create((*rule)->clone(), (*rule)->getStatements() ? (*rule)->getStatements()->clone(0) : statementsPtr());
        it->addRanges(0);
        it->setInheritedFeatures(parser.getStartFeatures());
        
#ifdef TRACE_OPTION
        if (traceInit) {
           std::cout << "<H3>####################### INIT #######################</H3>" << std::endl;
           it->print(std::cout);
           std::cout << std::endl;
        }
#endif
    if (trace && it->getRuleTrace()) {
            std::cout << "*** init \n";
            it->getRule()->print(std::cout, it->getIndex(), false, false);
            std::cout << std::endl << "↑:";
            it->getInheritedFeatures()->flatPrint(std::cout);
            std::cout << std::endl << std::endl;
        }

        insertItemMap(it);
        initState->insert(it, this);
    }

    states.insert(std::make_pair(0, initState));
    close(parser, initState, 0);

    unsigned int length = 0;
    while (length <= maxLength) {
        itemSetPtr actualState = ItemSet::create(++length);
        states.insert(std::make_pair(length, actualState));

        if (!shift(parser, initState, length)) {
            break;
        }
        
        actualState->resetUsages();
        close(parser, actualState, length);
        initState = actualState;
        
    }

    if (length > maxLength) {
        throw fatal_exception("maxLength");
    }
    nodeRoot->generate(this->getRandom(), this->getOne());
 #ifdef OUTPUT_XML
    if (outXML) {
        nodeRoot->toXML(xmlNodeRoot, xmlNodeRoot);
    }
#endif
}

/* **************************************************
 * search 
 * |str(code)#str(pred)
 * |codeStr#str(pred)
 * |str(code)#_
 * |codeStr#_
 * 
 * returns entries= (entry1, entry2, ...)
 * where entryi= (unsigned int pos, unsigned int pred, std::string form, featuresPtr features)
 ************************************************** */
entriesPtr Synthesizer::findCompactedLexicon(
        Parser& parser, 
        const unsigned int code, 
        const std::string& codeStr,
        const unsigned int pred) {
    unsigned long int info = ~0UL;
    std::string str;
    if (pred) {
        if (code)
            str = Vartable::codeToString(code) + '#' + Vartable::codeToString(pred);
        else if (!codeStr.empty())
            str = codeStr + "#" + Vartable::codeToString(pred) ;
        else
            throw fatal_exception("code null");
    } 
    else {
        if (code)
            str = Vartable::codeToString(code) + "#_";
        else if (!codeStr.empty())
            str = codeStr + "#_";
        else
            throw fatal_exception("pred and code null");
    }
    if (!compactedLexicon)
        throw fatal_exception("search operator error: No compact lexicon defined.");

    //CERR_LINE;
    //std::cerr << "search " << str << " in compactedLexicon" << std::endl;
    info = compactedLexicon->search(compactedLexicon->init, str);
    // in : pos#lemma
    // out : form#fs
#ifdef TRACE_LEXICON
    std::cout << "<H3>####################### FIND IN THE COMPACT LEXICON #######################</H3>" << std::endl;
    std::cout << "<DIV>" << std::endl;
    std::cout << str << " => ";
    compactedLexicon->printResults(std::cout, info, 1);
    std::cout << "</DIV>" << std::endl;
    std::cout << std::endl;
#endif
    if (info != ~0UL) {
        entriesPtr entries = Entries::create();
        while (info != ~0UL) {
            std::string result = compactedLexicon->buffer + (compactedLexicon->info[info].getOffset());
            std::string form = result.substr(0, result.find('#'));
            std::string features = result.substr(result.find('#') + 1, -1);

            try {
                parser.parseBuffer("#", features, "features");
                if (parser.getLocalFeatures()) {
                    unsigned int _pred = parser.getLocalFeatures()->assignPred();
                    entryPtr _localEntry = Entry::create(0, _pred, std::string(), parser.getLocalFeatures());

                    _localEntry->setPos(code);
                    _localEntry->setForm(form);
                    std::string localEntrySerialString = _localEntry->peekSerialString();
                    auto found = parser.findMapLocalEntry(localEntrySerialString);
                    if (found != parser.cendMapLocalEntry()) {
                        entries->add(found->second);
                    } else {
                        parser.insertMapLocalEntry(std::make_pair(localEntrySerialString, _localEntry));
                        entries->add(_localEntry);
                    }
                }
            }
            catch (parser_exception& e) {
                std::ostringstream oss;
                oss << "illegal lexical entry: " << form << " " << Vartable::codeToString(code) << " "
                                                             << result.substr(result.find('#') + 1, -1);
                throw fatal_exception(oss);
            }
            if ((compactedLexicon->info[info].isNext()))
                info = compactedLexicon->info[info].getNext();
            else
                info = (unsigned long int) (~(0UL));
        }
        return entries;
    } else {
        return entriesPtr();
    }
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setVerbose(bool _verbose) {
    this->verbose = _verbose;
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Synthesizer::findByPos(Parser& parser, Parser::entries_map* listPred, 
        unsigned int term) {
    entriesPtr entries = entriesPtr();
    // Without pred : UINT_MAX => ...
    auto found = listPred->find(UINT_MAX);        
    if (found != listPred->end()) {
        entries = found->second;
    } 
    else if (compactedLexicon) {
        entries = findCompactedLexicon(parser,
                                       term,
                                       std::string(),
                                       UINT_MAX);
        listPred->insert(std::make_pair(UINT_MAX, entries));
    }
    return entries;

}

/* **************************************************
 *
 ************************************************** */
entriesPtr Synthesizer::findByForm(Parser::entries_map *listPred) {
    entriesPtr entries = entriesPtr();
    // FORM : 0 => ...
    auto found = listPred->find(0);        
    if (found != listPred->end())
        entries = found->second;
    return entries;
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Synthesizer::findByPred(Parser& parser, Parser::entries_map* listPred, 
        unsigned int term, unsigned int pred) {
    entriesPtr entries = entriesPtr();
    // pred => ...
    auto found = listPred->find(pred);        
    if (found != listPred->end()) {
        entries = found->second;
    } 
    else
    if (compactedLexicon) {
        // Compact lexicon
        entries = findCompactedLexicon(parser,
                                       term,
                                       std::string(),
                                       pred);
        listPred->insert(std::make_pair(pred, entries));
    }
    return entries;
}

