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
    this->maxCardinal = MAXCARDINAL;
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
void Synthesizer::setMaxCardinal(unsigned int _maxCardinal) {
    this->maxCardinal = _maxCardinal;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Synthesizer::getMaxCardinal() const {
    return this->maxCardinal;
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
bool Synthesizer::insertItemMap(const itemPtr& item) {
    return this->itemMap.insert(std::make_pair(item->getId(), item)).second;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::eraseItemMap(const unsigned int id) {
    this->itemMap.erase(id);
}

/* **************************************************
 *
 ************************************************** */
itemPtr Synthesizer::getItemMap(const unsigned int id) {
    return this->itemMap[id];
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
itemPtr Synthesizer::createItem(const itemPtr& item, unsigned int row) {
    itemPtr it = Item::create(item->getRule(), item->getIndex() + 1, item->getIndexTerms(),
                              item->getStatements() ? item->getStatements()->clone(
                                      Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED) : statementsPtr());
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

/* **************************************************
 *
 ************************************************** */
std::string
Synthesizer::keyMemoization(const itemPtr& actualItem, const itemPtr& previousItem) {
    return std::to_string(actualItem->getId()) + '.' + std::to_string(previousItem->getCurrentTerm()) +
           actualItem->getSynthesizedFeatures()->peekSerialString();
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::clear() {
    states.clear();
    forestMap.clear();
    itemMap.clear();
    memoizedMap.clear();
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::close(Parser& parser, const itemSetPtr& state, unsigned int row) {
    bool modification;
    do {
        loop:
        modification = false;

        // Iterate through list
        for (auto actualItem = state->cbegin();
             actualItem != state->cend() && !modification; ++actualItem) {

            if ((*actualItem)->isSetFlags(Flags::SEEN | Flags::BOTTOM))
                continue;

            // X -> alpha • [Y] gamma
            if ((*actualItem)->getRuleRhs().size() > (*actualItem)->getIndex() && !(*actualItem)->isCompleted() &&
                !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
                && (*actualItem)->getCurrentTerms()->isOptional()) {

#ifdef TRACE_UNHIDE
                std::cout << "<H3>####################### UNHIDE #######################</H3>" << std::endl;
                (*actualItem)->print(std::cout);
                std::cout << std::endl;
#endif

                (*actualItem)->addFlags(Flags::SEEN);

                itemPtr it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
                forestPtr forestFound = forestPtr();
                forestIdentifierPtr fi = ForestIdentifier::create(it->getCurrentTerm(),
                                                                  row,
                                                                  row,
                                                                  std::string());
                auto forestMapIt = forestMap.find(fi);
                if (forestMapIt != forestMap.cend()) {
                    forestFound = forestMapIt->second;
                    fi.reset();
                    it->addForestIdentifiers(it->getIndex(), forestMapIt->first);
                } else {
                    forestFound = Forest::create(Entry::create(it->getCurrentTerm()), row, row);
                    forestMap.insert(fi, forestFound);
                    it->addForestIdentifiers(it->getIndex(), fi);
                }
                it->setIndex((*actualItem)->getIndex() + 1);
                it->addRanges(row);
#ifdef TRACE_UNHIDE
                std::cout << "<H3>####################### UNHIDE: X -> alpha [Y] • gamma #######################</H3>" << std::endl;
                it->print(std::cout);
                std::cout << std::endl;
#endif
                if (!state->insert(it, this)) {
                    FATAL_ERROR_UNEXPECTED
                } else {
                    insertItemMap(it);
                }
                it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
                it->setRule((*actualItem)->getRule()->clone());
                it->setIndex((*actualItem)->getIndex());
                it->getCurrentTerms()->unsetOptional();
#ifdef TRACE_UNHIDE
                std::cout << "<H3>####################### UNHIDE: X -> alpha • Y gamma #######################</H3>" << std::endl;
                it->print(std::cout);
                std::cout << std::endl;
#endif
                if (!state->insert(it, this)) {
                    FATAL_ERROR_UNEXPECTED
                } else {
                    insertItemMap(it);
                }
                state->erase(*actualItem);
                eraseItemMap((*actualItem)->getId());
                goto loop;
            }

            // X -> alpha • Y1|Y2 beta
            if ((*actualItem)->getRuleRhs().size() > (*actualItem)->getIndex() && !(*actualItem)->isCompleted() &&
                !(*actualItem)->getCurrentTerms()->isOptional()
                && (*actualItem)->getCurrentTerms()->size() > 1) {

#ifdef TRACE_UNFOLD
                std::cout << "<H3>####################### UNFOLD #######################</H3>" << std::endl;
                (*actualItem)->print(std::cout);
                std::cout << std::endl;
#endif

                (*actualItem)->addFlags(Flags::SEEN);
                termsPtr terms = (*actualItem)->getCurrentTerms();
                for (unsigned int indexTerm1 = 0; indexTerm1 < terms->size(); ++indexTerm1) {
                    itemPtr it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
                    it->setRule((*actualItem)->getRule()->clone());
                    it->setIndex((*actualItem)->getIndex());
                    it->setCurrentTerms(Terms::create((*terms)[indexTerm1]));
                    it->getIndexTerms()[(*actualItem)->getIndex()] = indexTerm1;

#ifdef TRACE_UNHIDE
                    std::cout << "<H3>####################### UNFOLD: insert #######################</H3>" << std::endl;
                    it->print(std::cout);
                    std::cout << std::endl;
#endif
                    if (!state->insert(it, this)) {
                        FATAL_ERROR_UNEXPECTED
                    } else {
                        insertItemMap(it);
                    }
                }
                state->erase((*actualItem));
                eraseItemMap((*actualItem)->getId());
                goto loop;
            }

            (*actualItem)->apply(/*state, */parser, this);
            if ((*actualItem)->isSetFlags(Flags::BOTTOM)) {
                state->erase((*actualItem));
                eraseItemMap((*actualItem)->getId());
                goto loop;
            }
                // X -> alpha • Y gamma
            else if ((*actualItem)->getRuleRhs().size() > (*actualItem)->getIndex() && !(*actualItem)->isCompleted() &&
                     !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
                     && (*actualItem)->getCurrentTerms()->size() == 1 && !(*actualItem)->getCurrentTerms()->isOptional()
                     && parser.getRules().isNonTerminal((*actualItem)->getCurrentTerm()) &&
                     !(*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()]->isNil()) {

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
                        if ((iterRules->getLhs() == (*actualItem)->getCurrentTerm())) {

                            itemPtr it;
                            iterRules->incUsages(this);
                            it = Item::create(iterRules->clone(), 0, 0,
                                              iterRules->getStatements() ? iterRules->getStatements()->clone(0)
                                                                         : statementsPtr());
                            it->addRanges(row);
                            //it->renameVariables(it->getId());
                            it->setInheritedFeatures(inheritedSonFeatures->clone());

#ifdef TRACE_OPTION
                            if (traceClose) {
                               std::cout << "<H3>####################### CLOSE (Y -> • γ) #######################</H3>" << std::endl;
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
                                (*found)->addRef((*actualItem)->getId());
                                it.reset();
                            } else {
                                it->addRef((*actualItem)->getId());
                                if (!state->insert(it, this)) {
                                    FATAL_ERROR_UNEXPECTED
                                } else {
                                    insertItemMap(it);
                                }
                            }
                            modification = true;
                            (*actualItem)->addFlags(Flags::SEEN);
                        }
                    }
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
                        if (reduceAll || (*actualItem)->getRefs().empty()) {
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
                                                             (*actualItem)->getRanges()[0], row);
                                forestMap.insert(fi, forestFound);
                                nodePtr node = Node::create();
                                node->push_back(forestFound);
                                nodeRoot->push_back(forestFound);
                            }
                            nodePtr node = Node::create();
                            for (auto &forestIdentifierPtr : (*actualItem)->getForestIdentifiers()) {
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
                                        // New item build
                                        itemPtr it = createItem(previousItem, row);
                                        it->setEnvironment(
                                                previousItem->getEnvironment() ? previousItem->getEnvironment()->clone()
                                                                               : environmentPtr());
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
                                            (*found)->addRefs(previousItem->getRefs());
                                            it.reset();
                                        } else {
                                            if (!states[row]->insert(it, this)) {
                                                FATAL_ERROR_UNEXPECTED
                                            } else {
                                                insertItemMap(it);
                                                modification = true;
                                            }
                                        }
                                        (*actualItem)->addFlags(Flags::SEEN);
                                    }
                                }
                                    // This reduce action is new
                                else {
                                    itemPtr it = createItem(previousItem, row);
                                    it->setEnvironment(
                                            previousItem->getEnvironment() ? previousItem->getEnvironment()->clone()
                                                                           : environmentPtr());
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
                                        fi.reset();
                                    } else {
                                        forestFound = Forest::create(Entry::create((*actualItem)->getRuleLhs()),
                                                                     (*actualItem)->getRanges()[0], row);
                                        forestMap.insert(fi, forestFound);
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
                                        it->getRule()->print(std::cout, it->getIndex() - 1, false, false);
                                        std::cout << std::endl << " => " << std::endl;
                                        it->getRule()->print(std::cout, it->getIndex(), false, false);
                                        std::cout << std::endl << std::endl;
                                    }

                                    auto found = states[row]->find(it);
                                    if (found != states[row]->cend()) {
                                        (*found)->addRefs(previousItem->getRefs());
                                        it.reset();
                                    } else {

                                        // tabulates this result
                                        // std::string key = keyMemoization(*actualItem, previousItem);
                                        memoizedMap.insert(key,
                                                           (*it->getSynthesizedSonFeatures())[it->getIndex() - 1],
                                                           it->getForestIdentifiers()[it->getIndex() - 1]);
                                        // record the item
                                        it->setRefs(previousItem->getRefs());
                                        if (!states[row]->insert(it, this)) {
                                            FATAL_ERROR_UNEXPECTED
                                        } else {
                                            insertItemMap(it);
                                            modification = true;
                                        }
                                        (*actualItem)->addFlags(Flags::SEEN);
                                    }
                                }
                            }
                        }
                    }
                }
            }

                // X -> alpha • t beta
            else if ((*actualItem)->getRuleRhs().size() > (*actualItem)->getIndex() && !(*actualItem)->isCompleted() &&
                     !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
                     && (*actualItem)->getCurrentTerms()->size() == 1 && !(*actualItem)->getCurrentTerms()->isOptional()
                     && parser.getRules().isTerminal((*actualItem)->getCurrentTerm()) &&
                     !(*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()]->isNil()) {
            } else {
                (*actualItem)->successor(modification);
            }
        }
    } while (modification);
    for (const auto& i : *state)
        i->subFlags(Flags::SEEN);
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::shift(class Parser& parser, const itemSetPtr& state, unsigned int row) {
    bool modificationOnce = false;
    bool modification;
    do {
        modification = false;

        // Iterate through list
        for (auto actualItem = state->begin();
             actualItem != state->end() && !modification; ++actualItem) {
            if ((*actualItem)->isSetFlags(Flags::SEEN))
                continue;
            if ((*actualItem)->isSetFlags(Flags::BOTTOM))
                continue;
            if ((*actualItem)->getCurrentTerms()) {
                featuresPtr inheritedSonFeatures = (*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()];
                if (!(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()] &&
                    !(*actualItem)->getCurrentTerms()->isOptional() && (*actualItem)->getCurrentTerm()
                    && !inheritedSonFeatures->isNil() && !inheritedSonFeatures->isBottom()
                    && parser.getRules().getTerminals().find((*actualItem)->getCurrentTerm()) !=
                       parser.getRules().getTerminals().end()) {

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

                    std::string *form = nullptr;
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
                    auto foundCode = parser.findCacheLexicon((*actualItem)->getCurrentTerm());
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
                                    entries = findByPos(parser, listPred, (*actualItem)->getCurrentTerm());
                                    break;

                                case FORM_FEATURES:
                                    entries = findByForm(listPred);
                                    break;

                                case PRED_FEATURES:
                                    entries = findByPred(parser, listPred, (*actualItem)->getCurrentTerm(), pred);
                                    if (!entries)
                                        entries = findByPos(parser, listPred, (*actualItem)->getCurrentTerm());
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
                                        itemPtr it = createItem(*actualItem, row);

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
                                            forestMap.insert(fi, Forest::create(word, row - 1, row));
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
                                            it->getRule()->print(std::cout, it->getIndex() - 1, false, false);
                                            std::cout << std::endl << "↓" << it->getIndex() << ':';
                                            (*it->getInheritedSonFeatures())[it->getIndex() - 1]->flatPrint(
                                                    std::cout);
                                            std::cout << std::endl << " => " << std::endl;
                                            it->getRule()->print(std::cout, it->getIndex(), false, false);
                                            std::cout << std::endl << std::endl;
                                        }

                                        // record the item
                                        if (!states[row]->insert(it, this)) {
                                            FATAL_ERROR_UNEXPECTED
                                        }
                                        insertItemMap(it);
                                        modification = true;
                                        modificationOnce = true;
                                        (*actualItem)->addFlags(Flags::SEEN);
                                        if (this->getRandom()) {
                                            break;
                                        }
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
    for (
        const auto& i
            : *state)
        i->
                subFlags(Flags::SEEN);
    return modificationOnce;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::generate(class Parser& parser) {
#ifdef OUTPUT_XML
    extern xmlNodePtr xmlNodeRoot;
#endif
    states.clear();
    itemMap.clear();
    forestMap.clear();
    for (const auto& iterRules : parser.getRules().getRules()) {
        iterRules->resetUsages();
    }

    std::ofstream outfile;
    nodeRoot = Node::create();
    itemSetPtr initState = ItemSet::create(0);
    std::list<rulePtr> *rules = parser.getRules().findRules(parser.getStartTerm());
    itemPtr it;
    for (std::list<rulePtr>::const_iterator rule = rules->begin(); rule != rules->end(); ++rule) {
        (*rule)->incUsages(this);
        it = Item::create(*rule, UINT_MAX, 0,
                          (*rule)->getStatements() ? (*rule)->getStatements()->clone(0) : statementsPtr());
        it->addRanges(0);
        it->setInheritedFeatures(parser.getStartFeatures());
        //it->renameVariables(it->getId());
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

    unsigned int i = 0;
    while (i <= maxLength) {

        itemSetPtr actualState = ItemSet::create(++i);
        states.insert(std::make_pair(i, actualState));
        if (!shift(parser, initState, i))
            break;
#ifdef TRACE_OPTION
        if (traceStage) {
           std::cout << "<H3>####################### STAGE " << initState->getId() << " #######################</H3>" << std::endl;
           initState->print(std::cout);
           std::cout << std::endl;
        }
#endif

        actualState->resetUsages();
        close(parser, actualState, i);
        initState = actualState;
    }

    if (i > maxLength) {
        throw fatal_exception("maxLength");
    }
    if ((i % 121) == 0) {
        std::cerr << "Length : " << i << std::endl;
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

