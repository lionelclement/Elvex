/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2023 LABRI,
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI - Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */
#include <fstream>
#include <sstream>

#include "generator.hpp"
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
Generator::Generator()
{
    NEW;
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
    this->randomResult = false;
    this->firstResult = false;
    this->randomAttemps = MAXATTEMPTS; // attemps to find a local random result
    this->trace = false;
    this->verbose = false;
}

/* **************************************************
 *
 ************************************************** */
Generator::~Generator()
{
    DELETE;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::getTrace() const
{
    return trace;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setTrace(bool _trace)
{
    this->trace = _trace;
}

/* **************************************************
 *
 ************************************************** */
Generator::itemSet_map_const_iterator Generator::cbegin() const
{
    return states.cbegin();
}

/* **************************************************
 *
 ************************************************** */
Generator::itemSet_map_const_iterator Generator::cend() const
{
    return states.cend();
}

/* **************************************************
 *
 ************************************************** */
size_t Generator::size() const
{
    return states.size();
}

/* **************************************************
 *
 ************************************************** */
void Generator::setInputFileName(char *name)
{
    inputFileName = name;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setLexiconFileName(char *name)
{
    lexiconFileName = name;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setCompactedLexiconFileName(char *bufferName)
{
    compactedLexiconFileName = bufferName;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setCompactedDirectoryName(char *DirectoryName)
{
    compactedDirectoryName = DirectoryName;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setRulesFileName(char *name)
{
    rulesFileName = name;
}

/* **************************************************
 *
 ************************************************** */
std::string Generator::getInputFileName() const
{
    return inputFileName;
}

/* **************************************************
 *
 ************************************************** */
std::string Generator::getLexiconFileName() const
{
    return lexiconFileName;
}

/* **************************************************
 *
 ************************************************** */
std::string Generator::getCompactedLexiconFileName() const
{
    return compactedLexiconFileName;
}

/* **************************************************
 *
 ************************************************** */
std::string Generator::getCompactedDirectoryName() const
{
    return compactedDirectoryName;
}

/* **************************************************
 *
 ************************************************** */
std::string Generator::getRulesFileName() const
{
    return rulesFileName;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setMaxLength(unsigned int _maxLength)
{
    this->maxLength = _maxLength;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setMaxUsages(unsigned int _maxUsages)
{
    this->maxUsages = _maxUsages;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setMaxItems(unsigned int _maxItems)
{
    this->maxItems = _maxItems;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Generator::getMaxItems() const
{
    return this->maxItems;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Generator::getMaxUsages() const
{
    return this->maxUsages;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setCompactedLexicon(class CompactedLexicon *compactedLexicon)
{
    this->compactedLexicon = compactedLexicon;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setReduceAll(const bool _reduceAll)
{
    this->reduceAll = _reduceAll;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setRandomResult(const bool randomResult)
{
    this->randomResult = randomResult;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::getRandomResult() const
{
    return this->randomResult;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setFirstResult(const bool firstResult)
{
    this->firstResult = firstResult;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::getFirstResult() const
{
    return this->firstResult;
}

#ifdef OUTPUT_XML

/* **************************************************
 *
 ************************************************** */
void Generator::setOutXML(char *_outXML)
{
    this->outXML = _outXML;
}

/* **************************************************
 *
 ************************************************** */
char *
Generator::getOutXML() const
{
    return this->outXML;
}

#endif

/* **************************************************
 *
 ************************************************** */
void Generator::setTraceInit(bool traceInit)
{
    this->traceInit = traceInit;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setTraceStage(bool traceStage)
{
    this->traceStage = traceStage;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setTraceClose(bool traceClose)
{
    this->traceClose = traceClose;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setTraceShift(bool traceShift)
{
    this->traceShift = traceShift;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setTraceReduce(bool traceReduce)
{
    this->traceReduce = traceReduce;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setTraceAction(bool traceAction)
{
    this->traceAction = traceAction;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::getTraceInit(void)
{
    return this->traceInit;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::getTraceStage(void)
{
    return this->traceStage;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::getTraceClose(void)
{
    return this->traceClose;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::getTraceShift(void)
{
    return this->traceShift;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::getTraceReduce(void)
{
    return this->traceReduce;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::getTraceAction(void)
{
    return this->traceAction;
}

/* **************************************************
 *
 ************************************************** */
std::list<std::string> &Generator::getInputs()
{
    return this->inputs;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::insertItemMap(class Item *item)
{
    return this->itemMap.insert(std::make_pair(item->getId(), item)).second;
}

/* **************************************************
 *
 ************************************************** */
void Generator::eraseItemMap(const unsigned int id)
{
    this->itemMap.erase(id);
}

/* **************************************************
 *
 ************************************************** */
class Item *Generator::getItemMap(const unsigned int id)
{
    return this->itemMap[id];
}

/* **************************************************
 *
 ************************************************** */
nodePtr Generator::getNodeRoot()
{
    return nodeRoot;
}

/* **************************************************
 *
 ************************************************** */
void Generator::addInput(const std::string &input)
{
    return this->inputs.push_back(input);
}

/* **************************************************
 *
 ************************************************** */
void Generator::printState(std::ostream &outStream, class ItemSet *state)
{
    outStream << "Q" << state->getId();
    state->print(outStream);
}

/* **************************************************
 *
 ************************************************** */
class Item *Generator::createItem(class Item *item, uint8_t row)
{
    class Item *it = Item::create(item->getRule(), item->getIndex() + 1, item->getIndexTerms(),
                                  item->getStatements() ? item->getStatements()->clone(
                                                              Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED)
                                                        : statementsPtr());
    it->addRanges(item->getRanges());
    it->addRange(row);
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
Generator::keyMemoization(class Item *actualItem, class Item *previousItem)
{
    return std::to_string(actualItem->getId()) + '.' + std::to_string(previousItem->getCurrentTerm()) +
           actualItem->getSynthesizedFeatures()->peekSerialString();
}

/* **************************************************
 *
 ************************************************** */
void Generator::clear()
{
    states.clear();
    forestMap.clear();
    itemMap.clear();
    memoizedMap.clear();
}

/* **************************************************
 *
 ************************************************** */
void Generator::close(Parser &parser, class ItemSet *state, uint8_t row)
{
    bool modification;
    do
    {
        modification = false;

        // Iterate through list
        for (auto actualItem = state->cbegin();
             actualItem != state->cend() && !modification;
             ++actualItem)
        {

            if ((*actualItem)->isSetFlags(Flags::SEEN | Flags::BOTTOM))
                continue;

            // X -> alpha • [Y] gamma
            if ((*actualItem)->getRuleRhs().size() > (*actualItem)->getIndex() && !(*actualItem)->isCompleted() &&
                !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()] && (*actualItem)->getCurrentTerms()->isOptional())
            {

#ifdef TRACE_PASS
                std::cout << "<H3>####################### PASS #######################</H3>" << std::endl;
                (*actualItem)->print(std::cout);
                std::cout << std::endl;
#endif

                (*actualItem)->addFlags(Flags::SEEN);

                class Item *it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
                forestPtr forestFound = forestPtr();
                class ForestIdentifier *fi = ForestIdentifier::create(it->getCurrentTerm(),
                                                                      row,
                                                                      row,
                                                                      std::string());
                auto forestMapIt = forestMap.find(fi);
                if (forestMapIt != forestMap.cend())
                {
                    forestFound = forestMapIt->second;
                    free(fi);
                    it->addForestIdentifiers(it->getIndex(), forestMapIt->first);
                }
                else
                {
                    forestFound = Forest::create(Entry::create(it->getCurrentTerm()), row, row);

                    forestMap.insert(fi, forestFound);
                    it->addForestIdentifiers(it->getIndex(), fi);
                }
                it->setIndex((*actualItem)->getIndex() + 1);
                it->getIndexTerms()[(*actualItem)->getIndex()] = 0;
                it->addRange(row);
                it->resetSerial();
#ifdef TRACE_PASS
                std::cout << "<H3>####################### PASS: X -> alpha [Y] • gamma #######################</H3>" << std::endl;
                it->print(std::cout);
                std::cout << std::endl;
#endif
                if (!state->insert(it, this))
                {
                    FATAL_ERROR_UNEXPECTED
                }
                else
                {
                    insertItemMap(it);
                }
                it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
                it->setRule((*actualItem)->getRule()->clone());
                it->setIndex((*actualItem)->getIndex());
                if (it->getCurrentTerms()->size() == 1)
                {
                    it->getIndexTerms()[(*actualItem)->getIndex()] = 0;
                }
                else
                {
                    it->getIndexTerms()[(*actualItem)->getIndex()] = Item::NA - 1;
                }
                it->getCurrentTerms()->unsetOptional();
                it->resetSerial();
#ifdef TRACE_PASS
                std::cout << "<H3>####################### PASS: X -> alpha • Y gamma #######################</H3>" << std::endl;
                it->print(std::cout);
                std::cout << std::endl;
#endif
                if (!state->insert(it, this))
                {
                    FATAL_ERROR_UNEXPECTED
                }
                else
                {
                    insertItemMap(it);
                }
                eraseItemMap((*actualItem)->getId());
                state->erase(*actualItem);
                modification = true;
            }

            // X -> alpha • Y1|Y2 beta
            else if ((*actualItem)->getRuleRhs().size() > (*actualItem)->getIndex() && !(*actualItem)->isCompleted() &&
                     !(*actualItem)->getCurrentTerms()->isOptional() && (*actualItem)->getCurrentTerms()->size() > 1)
            {

#ifdef TRACE_UNFOLD
                std::cout << "<H3>####################### UNFOLD #######################</H3>" << std::endl;
                (*actualItem)->print(std::cout);
                std::cout << std::endl;
#endif

                (*actualItem)->addFlags(Flags::SEEN);
                termsPtr terms = (*actualItem)->getCurrentTerms();
                for (uint8_t indexTerm1 = 0; indexTerm1 < terms->size(); ++indexTerm1)
                {
                    class Item *it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
                    it->setRule((*actualItem)->getRule()->clone());
                    it->setIndex((*actualItem)->getIndex());
                    it->setCurrentTerms(Terms::create((*terms)[indexTerm1]));
                    it->getIndexTerms()[(*actualItem)->getIndex()] = indexTerm1;

#ifdef TRACE_UNFOLD
                    std::cout << "<H3>####################### UNFOLD: insert #######################</H3>" << std::endl;
                    it->print(std::cout);
                    std::cout << std::endl;
#endif
                    if (!state->insert(it, this))
                    {
                        FATAL_ERROR_UNEXPECTED
                    }
                    else
                    {
                        insertItemMap(it);
                    }
                }
                eraseItemMap((*actualItem)->getId());
                state->erase((*actualItem));
                modification = true;
            }

            else
            {

                if ((*actualItem)->getStatements() && (*actualItem)->isUnsetFlags(Flags::BOTTOM) && (*actualItem)->getStatements()->isUnsetFlags(Flags::SEEN))
                {
                    if (getTraceAction() || ((getTrace() && (*actualItem)->getRuleTrace())))
                    {
                        std::cout << "<H3>####################### ACTION #######################</H3>" << std::endl;
                        (*actualItem)->print(std::cout);
                        std::cout << std::endl;
                    }
                    (*actualItem)->apply(parser, this);
                    if (getTraceAction() || ((getTrace() && (*actualItem)->getRuleTrace())))
                    {
                        std::cout << "<H3>####################### ACTION DONE #######################</H3>" << std::endl;
                        (*actualItem)->print(std::cout);
                        std::cout << std::endl;
                    }
                }

                if ((*actualItem)->isSetFlags(Flags::BOTTOM))
                {
                    eraseItemMap((*actualItem)->getId());
                    state->erase((*actualItem));
                    modification = true;
                }

                // X -> alpha • Y gamma
                else if ((*actualItem)->getRuleRhs().size() > (*actualItem)->getIndex() && !(*actualItem)->isCompleted() &&
                         !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()] && (*actualItem)->getCurrentTerms()->size() == 1 && !(*actualItem)->getCurrentTerms()->isOptional() && parser.getRules().isNonTerminal((*actualItem)->getCurrentTerm()) &&
                         !(*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()]->isNil())
                {

                    if (traceClose || (trace && (*actualItem)->getRuleTrace()))
                    {
                        std::cout << "<H3>####################### CLOSE (X -> α • Y β) #######################</H3>" << std::endl;
                        (*actualItem)->print(std::cout);
                        std::cout << std::endl;
                    }

                    (*actualItem)->addFlags(Flags::SEEN);

                    featuresPtr inheritedSonFeatures = (*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()];
                    if (!inheritedSonFeatures->isNil() && !inheritedSonFeatures->isBottom())
                    {
                        if ((*actualItem)->getEnvironment() && (*actualItem)->getEnvironment()->size() > 0)
                        {
                            bool effect = false;
                            (*actualItem)->getEnvironment()->replaceVariables(inheritedSonFeatures, effect);
                            inheritedSonFeatures->deleteAnonymousVariables();
                        }

                        for (const auto &iterRules : parser.getRules().getRules())
                        {
                            if ((iterRules->getLhs() == (*actualItem)->getCurrentTerm()))
                            {

                                class Item *it;
                                iterRules->incUsages(this);
                                it = Item::create(iterRules->clone(), 0, 0,
                                                  iterRules->getStatements() ? iterRules->getStatements()->clone(0)
                                                                             : statementsPtr());
                                it->addRange(row);
                                // it->renameVariables(it->getId());
                                it->setInheritedFeatures(inheritedSonFeatures->clone());

                                if (traceClose || (trace && it->getRuleTrace()))
                                {
                                    std::cout << "<H3>####################### CLOSE CON'T (Y -> • γ) #######################</H3>" << std::endl;
                                    it->print(std::cout);
                                    std::cout << std::endl;
                                }

                                // record the item
                                auto found = state->find(it);
                                if (found != state->cend())
                                {
                                    (*found)->addRef((*actualItem)->getId());
                                    free(it);
                                }
                                else
                                {
                                    it->addRef((*actualItem)->getId());
                                    if (!state->insert(it, this))
                                    {
                                        FATAL_ERROR_UNEXPECTED
                                    }
                                    else
                                    {
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
                else if ((*actualItem)->isCompleted())
                {

                    if (traceReduce || (trace && (*actualItem)->getRuleTrace()))
                    {
                        std::cout << "<H3>####################### REDUCE Y -> γ • (actual) #######################</H3>" << std::endl;
                        (*actualItem)->print(std::cout);
                        std::cout << std::endl;
                    }

                    (*actualItem)->addFlags(Flags::SEEN);
                    if (!(*actualItem)->getSynthesizedFeatures())
                    {
                        FATAL_ERROR_UNEXPECTED
                    }
                    else
                    {
                        if ((*actualItem)->getSynthesizedFeatures()->isNil())
                        {
                            if (warning)
                            {
                                std::ostringstream oss;
                                oss << "null synthesized feature structure " << (*actualItem)->getRuleFilename() << '('
                                    << (*actualItem)->getRuleLineno() << ')' << std::endl;
                                throw fatal_exception(oss);
                            }
                            (*actualItem)->setSynthesizedFeatures(Features::create());
                        }
                        if (!(*actualItem)->getSynthesizedFeatures()->isBottom())
                        {

                            // If Axiom reduced or debug Transients
                            if (reduceAll || (*actualItem)->getRefs().empty())
                            {
                                if (traceReduce || (trace && (*actualItem)->getRuleTrace()))
                                {
                                    std::cout << "<H3>####################### REDUCE S -> γ • (AXIOM REDUCED) #######################</H3>" << std::endl;
                                    (*actualItem)->print(std::cout);
                                    std::cout << std::endl;
                                }

                                if ((*actualItem)->getEnvironment() && (*actualItem)->getEnvironment()->size() > 0)
                                {
                                    bool effect = false;
                                    (*actualItem)->getEnvironment()->replaceVariables((*actualItem)->getSynthesizedFeatures(), effect);
                                    if (effect)
                                    {
                                        if (traceReduce || (trace && (*actualItem)->getRuleTrace()))
                                        {
                                            std::cout << "<H3>####################### REDUCE S -> γ • (AXIOM REDUCED) #######################</H3>" << std::endl;
                                            (*actualItem)->print(std::cout);
                                            std::cout << std::endl;
                                        }
                                        FATAL_ERROR_UNEXPECTED
                                    }
                                    (*actualItem)->getSynthesizedFeatures()->deleteAnonymousVariables();
                                }

                                forestPtr forestFound = forestPtr();
                                class ForestIdentifier *fi = ForestIdentifier::create((*actualItem)->getRuleLhs(),
                                                                                      (*actualItem)->getRanges()[0],
                                                                                      row,
                                                                                      ((*actualItem)->getSynthesizedFeatures()
                                                                                           ? (*actualItem)->getSynthesizedFeatures()->peekSerialString()
                                                                                           : std::string()));
                                auto forestMapIt = forestMap.find(fi);
                                if (forestMapIt != forestMap.cend())
                                {
                                    forestFound = (*forestMapIt).second;
                                    free(fi);
                                }
                                else
                                {
                                    forestFound = Forest::create(Entry::create((*actualItem)->getRuleLhs()),
                                                                 (*actualItem)->getRanges()[0], row);
                                    forestMap.insert(fi, forestFound);
                                    nodePtr node = Node::create((*actualItem)->getWithSpaces(), (*actualItem)->getBidirectional(), (*actualItem)->getPermutable());
                                    if (forestFound->getFrom() != forestFound->getTo())
                                    {
                                        node->push_back(forestFound);
                                        nodeRoot->push_back(forestFound);
                                    }
                                }
                                nodePtr node = Node::create((*actualItem)->getWithSpaces(), (*actualItem)->getBidirectional(), (*actualItem)->getPermutable());
                                for (auto forestIdentifier : (*actualItem)->getForestIdentifiers())
                                {
                                    auto _forestMapIt = forestMap.find(forestIdentifier);
                                    if (_forestMapIt != forestMap.cend())
                                    {
                                        forestPtr forest = (*_forestMapIt).second;

                                        if (forest->getFrom() != forest->getTo())
                                        {
                                            node->push_back(forest);
                                        }
                                    }
                                }
                                forestFound->push_back_node(node);
                            }
                            for (auto ref : (*actualItem)->getRefs())
                            {
                                class Item *previousItem = getItemMap(ref);
                                if (!previousItem)
                                {
                                    FATAL_ERROR_UNEXPECTED
                                }
                                else
                                {

                                    if (traceReduce || (trace && previousItem->getRuleTrace()))
                                    {
                                        std::cout << "<H3>####################### REDUCE CON'T (X -> α • Y β) #######################</H3>" << std::endl;
                                        previousItem->print(std::cout);
                                        std::cout << std::endl;
                                    }

                                    std::string key = keyMemoization(*actualItem, previousItem);
                                    auto memItem = memoizedMap.find(key);
                                    // Is this already done ?
                                    if (memItem != memoizedMap.cend())
                                    {
                                        std::vector<class MemoizationValue *> result = memItem->second;
                                        for (std::vector<class MemoizationValue *>::const_iterator i = result.cbegin();
                                             i != result.cend();
                                             ++i)
                                        {
                                            // New item build
                                            class Item *it = createItem(previousItem, row);
                                            it->setEnvironment(
                                                previousItem->getEnvironment() ? previousItem->getEnvironment()->clone(nullptr)
                                                                               : environmentPtr());
                                            it->getSynthesizedSonFeatures()->add(previousItem->getIndex(),
                                                                                 (*i)->getFeatures());
                                            //...
                                            featuresPtr inheritedFeatures = it->getInheritedFeatures();
                                            if (!inheritedFeatures->isNil() && !inheritedFeatures->isBottom())
                                            {
                                                if (it->getEnvironment() && it->getEnvironment()->size() > 0)
                                                {
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
                                            if (found != states[row]->cend())
                                            {
                                                (*found)->addRefs(previousItem->getRefs());
                                                free(it);
                                            }
                                            else
                                            {
                                                if (!states[row]->insert(it, this))
                                                {
                                                    FATAL_ERROR_UNEXPECTED
                                                }
                                                else
                                                {
                                                    insertItemMap(it);
                                                    modification = true;
                                                }
                                            }
                                            (*actualItem)->addFlags(Flags::SEEN);
                                        }
                                    }

                                    // This reduce action is new
                                    else
                                    {
                                        class Item *it = createItem(previousItem, row);
                                        it->setEnvironment(
                                            previousItem->getEnvironment() ? previousItem->getEnvironment()->clone(nullptr)
                                                                           : environmentPtr());
                                        it->getSynthesizedSonFeatures()->add(previousItem->getIndex(),
                                                                             (*actualItem)->getSynthesizedFeatures()->clone());

                                        //...
                                        featuresPtr inheritedFeatures = it->getInheritedFeatures();
                                        if (!inheritedFeatures->isNil() && !inheritedFeatures->isBottom())
                                        {
                                            if (it->getEnvironment() && it->getEnvironment()->size() > 0)
                                            {
                                                bool effect = false;
                                                it->getEnvironment()->replaceVariables(inheritedFeatures, effect);
                                                inheritedFeatures->deleteAnonymousVariables();
                                            }
                                        }

                                        // On transmet le contexte de previousItem
                                        nodePtr node = Node::create((*actualItem)->getWithSpaces(), (*actualItem)->getBidirectional(), (*actualItem)->getPermutable());
                                        for (auto forestIdentifier : (*actualItem)->getForestIdentifiers())
                                        {
                                            auto forestMapIt = forestMap.find(forestIdentifier);
                                            if (forestMapIt == forestMap.cend())
                                            {
                                                FATAL_ERROR_UNEXPECTED
                                            }
                                            forestPtr forest = (*forestMapIt).second;
                                            if (forest->getFrom() != forest->getTo())
                                                node->push_back(forest);
                                        }
                                        forestPtr forestFound = forestPtr();
                                        class ForestIdentifier *fi = ForestIdentifier::create((*actualItem)->getId(),
                                                                                              (*actualItem)->getRanges()[0],
                                                                                              row,
                                                                                              std::string());
                                        auto forestMapIt = forestMap.find(fi);
                                        if (forestMapIt != forestMap.cend())
                                        {
                                            forestFound = forestMapIt->second;
                                            it->addForestIdentifiers(previousItem->getIndex(), forestMapIt->first);
                                            free(fi);
                                        }
                                        else
                                        {
                                            forestFound = Forest::create(Entry::create((*actualItem)->getRuleLhs()),
                                                                         (*actualItem)->getRanges()[0], row);
                                            forestMap.insert(fi, forestFound);
                                            it->addForestIdentifiers(previousItem->getIndex(), fi);
                                        }
                                        forestFound->push_back_node(node);
                                        if (traceReduce || (trace && it->getRuleTrace()))
                                        {
                                            std::cout << "<H3>####################### REDUCE CON'T (X -> α Y • β) #######################</H3>" << std::endl;
                                            it->print(std::cout);
                                            std::cout << std::endl;
                                        }
                                        auto found = states[row]->find(it);
                                        if (found != states[row]->cend())
                                        {
                                            (*found)->addRefs(previousItem->getRefs());
                                            free(it);
                                        }
                                        else
                                        {

                                            // tabulates this result
                                            memoizedMap.insert(key,
                                                               (*it->getSynthesizedSonFeatures())[it->getIndex() - 1],
                                                               it->getForestIdentifiers()[it->getIndex() - 1]);
                                            // record the item
                                            it->setRefs(previousItem->getRefs());
                                            if (!states[row]->insert(it, this))
                                            {
                                                FATAL_ERROR_UNEXPECTED
                                            }
                                            else
                                            {
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
                         !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()] && (*actualItem)->getCurrentTerms()->size() == 1 && !(*actualItem)->getCurrentTerms()->isOptional() && parser.getRules().isTerminal((*actualItem)->getCurrentTerm()) &&
                         !(*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()]->isNil())
                {
                    // shift the next time
                }

                else
                {
                    (*actualItem)->step(modification);
                }
            }
        }
    } while (modification);
    for (const auto &i : *state)
        i->subFlags(Flags::SEEN);
    if (traceStage)
    {
        std::cout << "<H3>####################### STAGE " << state->getId() << " #######################</H3>" << std::endl;
        state->print(std::cout);
        std::cout << std::endl;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Generator::shift(class Parser &parser, class ItemSet *state, uint8_t row)
{
    bool modificationOnce = false;
    bool modification;
    do
    {
        modification = false;

        // Iterate through list
        for (auto actualItem = state->begin();
             actualItem != state->end() && !modification; ++actualItem)
        {
            if ((*actualItem)->isSetFlags(Flags::SEEN))
                continue;
            if ((*actualItem)->isSetFlags(Flags::BOTTOM))
                continue;
            if ((*actualItem)->getCurrentTerms())
            {
                featuresPtr inheritedSonFeatures = (*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()];
                if (!(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()] &&
                    !(*actualItem)->getCurrentTerms()->isOptional() && (*actualItem)->getCurrentTerm() && !inheritedSonFeatures->isNil() && !inheritedSonFeatures->isBottom() && parser.getRules().getTerminals().find((*actualItem)->getCurrentTerm()) != parser.getRules().getTerminals().end())
                {

                    if (traceShift || (trace && (*actualItem)->getRuleTrace()))
                    {
                        std::cout << "<H3>####################### SHIFT (X -> α • ω β) where ω ∈ ℒ #######################</H3>" << std::endl;
                        (*actualItem)->print(std::cout);
                        std::cout << std::endl;
                    }

                    if ((*actualItem)->getEnvironment() && (*actualItem)->getEnvironment()->size() > 0)
                    {
                        bool effect = false;
                        (*actualItem)->getEnvironment()->replaceVariables(inheritedSonFeatures, effect);
                        inheritedSonFeatures->deleteAnonymousVariables();
                    }

                    std::string *form = nullptr;
                    uint16_t head = inheritedSonFeatures->assignHead();
                    Stage stage;
                    if (head == UINT16_MAX)
                    {
                        form = inheritedSonFeatures->assignForm();
                        if (form)
                            stage = FORM_FEATURES;
                        else
                            stage = MORPHO_FEATURES;
                    }
                    else
                    {
                        stage = HEAD_FEATURES;
                    }

                    /*
                     std::cout << "inheritedSonFeatures : ";
                     inheritedSonFeatures->print(std::cout);
                     std::cout << std::endl;
                     std::cout << "head:" << head << std::endl;
                     std::cout << "form:" << form << std::endl;
                     std::cout << "pos : " << Vartable::codeToString((*actualItem)->getCurrentTerm()) << std::endl;
                    */
                    auto foundpos = parser.findCacheLexicon((*actualItem)->getCurrentTerm());
                    if (foundpos != parser.cendCacheLexicon() && (!foundpos->second->empty()))
                    {
                        Parser::entries_map *listHead = foundpos->second;
                        if (listHead)
                        {
                            Parser::entries_map::const_iterator found;
                            entriesPtr entries = entriesPtr();

                            /* *****
                            CERR_LINE;
                            std::cout << "stage : " << _stage << std::endl;
                            std::cout << "head : " << Vartable::codeToString(head) << std::endl;
                            std::cout << "form : \"" << (form ? *form : "nullptr") << '"' << std::endl;
                            ***** */
                            switch (stage)
                            {

                            case MORPHO_FEATURES:
                                entries = findByPos(parser, listHead, (*actualItem)->getCurrentTerm());
                                break;

                            case FORM_FEATURES:
                                entries = findByForm(listHead);
                                break;

                            case HEAD_FEATURES:
                                entries = findByHead(parser, listHead, (*actualItem)->getCurrentTerm(), head);
                                if (!entries)
                                    entries = findByPos(parser, listHead, (*actualItem)->getCurrentTerm());
                                break;
                            }

                            // Found !
                            if (entries)
                            {
                                // cont = false;
                                auto entryIt = entries->begin();
                                int tryRandom = 0;
                                while (entryIt != entries->end())
                                {
                                    entryPtr entry = *entryIt;

                                    if (this->getRandomResult())
                                    {
                                        if (tryRandom++ > randomAttemps)
                                        {
                                            WARNING("too much random trial");
                                            break;
                                        }
                                        size_t rv = std::rand() / ((RAND_MAX + 1u) / entries->size());
                                        entry = entries->get(rv);
                                    }
                                    else
                                    {
                                        entry = *entryIt;
                                        ++entryIt;
                                    }
                                    entryPtr entry_copy = entry->clone();
                                    entry_copy->renameVariables(entry->getId());

                                    featuresPtr entryFeatures = entry_copy->getFeatures() ? entry_copy->getFeatures()
                                                                                          : featuresPtr();
                                    statementsPtr entryStatements = statementsPtr();
                                    environmentPtr env = (*actualItem)->getEnvironment()
                                                             ? (*actualItem)->getEnvironment()->clone(nullptr)
                                                             : Environment::create();

                                    // Filter !!
                                    // entryFeatures subsumes ↑
                                    if (stage == FORM_FEATURES ||
                                        (entryFeatures && entryFeatures->subsumes(nullptr, inheritedSonFeatures, env)))
                                    {

                                        // New item build
                                        class Item *it = createItem(*actualItem, row);

                                        it->setEnvironment(env);

                                        featuresPtr resultFeatures = featuresPtr();
                                        featuresPtr inheritedSonFeaturesCopy = inheritedSonFeatures->clone();
                                        featuresPtr entryFeaturesCopy = entryFeatures->clone();

                                        if (entryFeatures)
                                        {
                                            resultFeatures = entryFeaturesCopy;
                                        }
                                        else
                                        {

                                            resultFeatures = inheritedSonFeaturesCopy;
                                        }

                                        if (resultFeatures)
                                        {
                                            if (it->getEnvironment() && (it->getEnvironment()->size() > 0))
                                            {
                                                bool effect = false;
                                                it->getEnvironment()->replaceVariables(resultFeatures, effect);
                                            }
                                            resultFeatures->renameVariables(entry_copy->getId());
                                        }

                                        it->getSynthesizedSonFeatures()->add((*actualItem)->getIndex(),
                                                                             entryFeaturesCopy);
                                        if (entryStatements)
                                            entryStatements->renameVariables(entry_copy->getId());
                                        entryPtr entry;
                                        if (stage == FORM_FEATURES)
                                        {
                                            entry = Entry::create(entry_copy->getPos(), 0, *form, resultFeatures);
                                        }
                                        else
                                        {
                                            size_t _found = entry_copy->getForm().find('$');
                                            if (_found != std::string::npos)
                                            {
                                                bool effect = false;
                                                std::string _form = entry_copy->getForm();
                                                it->getEnvironment()->replaceVariables(_form, effect);
                                                entry = Entry::create(entry_copy->getPos(), entry_copy->getHead(), _form,
                                                                      resultFeatures);
                                            }
                                            else
                                            {
                                                entry = Entry::create(entry_copy->getPos(), entry_copy->getHead(),
                                                                      entry_copy->getForm(), resultFeatures);
                                            }
                                        }
                                        ForestIdentifier *fi = ForestIdentifier::create(entry->hashCode(),
                                                                                        0, 0,
                                                                                        // row - 1,
                                                                                        // row,
                                                                                        resultFeatures->peekSerialString());

                                        auto forestMapIt = forestMap.find(fi);
                                        if (forestMapIt != forestMap.cend())
                                        {
                                            it->addForestIdentifiers((*actualItem)->getIndex(),
                                                                     (*forestMapIt).first);
                                            free(fi);
                                            // std::cerr << "stage : " << stage! << "<BR>" << std::endl;
                                            // std::cerr << "head : " << Vartable::codeToString(head) << "<BR>" << std::endl;
                                            // std::cout << "form : " << form << "<BR>" << std::endl;
                                        }
                                        else
                                        {
                                            forestMap.insert(fi, Forest::create(entry, row - 1, row));
                                            it->addForestIdentifiers((*actualItem)->getIndex(), fi);
                                        }
                                        it->setRefs((*actualItem)->getRefs());

                                        if (traceShift || (trace && it->getRuleTrace()))
                                        {
                                            std::cout << "<H3>####################### SHIFT CON'T (X -> α ω • β) #######################</H3>" << std::endl;
                                            it->print(std::cout);
                                            std::cout << std::endl;
                                        }

                                        // record the item
                                        if (!states[row]->insert(it, this))
                                        {
                                            FATAL_ERROR_UNEXPECTED
                                        }
                                        insertItemMap(it);
                                        modification = true;
                                        modificationOnce = true;
                                        (*actualItem)->addFlags(Flags::SEEN);
                                        if (this->getRandomResult())
                                        {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        FATAL_ERROR_UNEXPECTED;
                    }
                }
            }
        }

    } while (modification);
    for (
        const auto &i : *state)
        i->subFlags(Flags::SEEN);
    return modificationOnce;
}

/* **************************************************
 *
 ************************************************** */
void Generator::generate(class Parser &parser)
{
#ifdef OUTPUT_XML
    extern xmlNodePtr xmlNodeRoot;
#endif
    states.clear();
    itemMap.clear();
    forestMap.clear();
    for (const auto &iterRules : parser.getRules().getRules())
    {
        iterRules->resetUsages();
    }

    std::ofstream outfile;
    nodeRoot = Node::create(false, false, false);
    class ItemSet *initState = ItemSet::create(0);
    std::list<rulePtr> *rules = parser.getRules().findRules(parser.getStartTerm());
    class Item *it;
    for (std::list<rulePtr>::const_iterator rule = rules->begin(); rule != rules->end(); ++rule)
    {
        (*rule)->incUsages(this);
        it = Item::create(*rule, UCHAR_MAX, 0,
                          (*rule)->getStatements() ? (*rule)->getStatements()->clone(0) : statementsPtr());
        it->addRange(0);
        it->setInheritedFeatures(parser.getStartFeatures());
        // it->renameVariables(it->getId());
        if (traceInit || (trace && it->getRuleTrace()))
        {
            std::cout << "<H3>####################### INIT #######################</H3>" << std::endl;
            it->print(std::cout);
            std::cout << std::endl;
        }
        insertItemMap(it);
        initState->insert(it, this);
    }

    states.insert(std::make_pair(0, initState));
    close(parser, initState, 0);

    int i = 0;
    while (i <= maxLength)
    {
        class ItemSet *actualState = ItemSet::create(++i);
        states.insert(std::make_pair(i, actualState));
        if (!shift(parser, initState, i))
        {
            break;
        }
        actualState->resetUsages();
        close(parser, actualState, i);
        initState = actualState;
    }

    if (i > maxLength)
    {
        throw fatal_exception("maxLength");
    }
    if ((i % 121) == 0)
    {
        std::cerr << "Length : " << i << std::endl;
    }

    if (!nodeRoot->empty())
    {
        for (auto forest = nodeRoot->cbegin(); forest != nodeRoot->cend(); ++forest)
            (*forest)->generate(this->getRandomResult(), this->getFirstResult());
    }

#ifdef OUTPUT_XML
    if (outXML)
    {
        nodeRoot->toXML(xmlNodeRoot, xmlNodeRoot);
    }
#endif
}

/* **************************************************
 * search
 * |str(pos)#str(head)
 * |str(pos)#_
 *
 * returns entries= (entry1, entry2, ...)
 * where entryi= (uint16_t pos, uint16_t head, std::string form, featuresPtr features)
 ************************************************** */
entriesPtr Generator::findCompactedLexicon(
    Parser &parser,
    const uint16_t pos,
    const uint16_t head)
{
    unsigned long int info = ~0UL;
    std::string str;
    if (head && pos)
    {
        str = Vartable::codeToName(pos) + '#' + Vartable::codeToName(head);
    }
    else if (pos)
    {
        str = Vartable::codeToName(pos) + "#_";
    }
    else if (head)
    {
        throw fatal_exception("pos null");
    }
    else
    {
        throw fatal_exception("head and pos null");
    }
    if (!compactedLexicon)
        throw fatal_exception("search operator error: No compact lexicon defined.");

    // CERR_LINE;
    // std::cerr << "search " << str << " in compactedLexicon" << std::endl;
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
    if (info != ~0UL)
    {
        entriesPtr entries = Entries::create();
        while (info != ~0UL)
        {
            std::string result = compactedLexicon->buffer + (compactedLexicon->info[info].getOffset());
            std::string form = result.substr(0, result.find('#'));
            std::string features = result.substr(result.find('#') + 1, -1);

            try
            {
                parser.parseBuffer("#(", ")", features, "features");
                if (parser.getLocalFeatures())
                {
                    uint16_t head = parser.getLocalFeatures()->assignHead();
                    entryPtr _localEntry = Entry::create(0, head, std::string(), parser.getLocalFeatures());

                    _localEntry->setPos(pos);
                    _localEntry->setForm(form);
                    std::string localEntrySerialString = _localEntry->peekSerialString();
                    auto found = parser.findMapLocalEntry(localEntrySerialString);
                    if (found != parser.cendMapLocalEntry())
                    {
                        entries->add(found->second);
                    }
                    else
                    {
                        parser.insertMapLocalEntry(std::make_pair(localEntrySerialString, _localEntry));
                        entries->add(_localEntry);
                    }
                }
            }
            catch (parser_exception &e)
            {
                std::ostringstream oss;
                oss << "illegal lexical entry format: " << form << " " << Vartable::codeToName(pos) << " "
                    << result.substr(result.find('#') + 1, -1);
                throw fatal_exception(oss);
            }
            if ((compactedLexicon->info[info].isNext()))
                info = compactedLexicon->info[info].getNext();
            else
                info = (unsigned long int)(~(0UL));
        }
        return entries;
    }
    else
    {
        return entriesPtr();
    }
}

/* **************************************************
 *
 ************************************************** */
void Generator::setVerbose(bool _verbose)
{
    this->verbose = _verbose;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::getVerbose()
{
    return this->verbose;
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Generator::findByPos(Parser &parser, Parser::entries_map *listHead,
                                uint16_t pos)
{
    entriesPtr entries = entriesPtr();
    // Without head : UINT_MAX => ...
    auto found = listHead->find(UINT16_MAX);
    if (found != listHead->end())
    {
        entries = found->second;
    }
    else if (compactedLexicon)
    {
        entries = findCompactedLexicon(parser,
                                       pos,
                                       UINT16_MAX);
        listHead->insert(std::make_pair(UINT16_MAX, entries));
    }
    return entries;
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Generator::findByForm(Parser::entries_map *listHead)
{
    entriesPtr entries = entriesPtr();
    // FORM : 0 => ...
    auto found = listHead->find(0);
    if (found != listHead->end())
        entries = found->second;
    return entries;
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Generator::findByHead(Parser &parser, Parser::entries_map *listHead,
                                 uint16_t pos, uint16_t head)
{
    entriesPtr entries = entriesPtr();
    // head => ...
    auto found = listHead->find(head);
    if (found != listHead->end())
    {
        entries = found->second;
    }
    if (compactedLexicon)
    {
        entriesPtr localEntries = findCompactedLexicon(parser,
                                                       pos,
                                                       head);
        if (localEntries)
        {
            if (entries)
            {
                localEntries->add(entries);
            }
            entries = localEntries;
        }
    }
    return entries;
}
