/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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
#include <algorithm>
#include <random>
#include <vector>
#include <limits>
#include <iostream>

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
#include "fatal_exception.hpp"

static bool mergeRefs(class Item *target, const Item::set_of_uint32_t &refs);
static bool mergeOrderSpecs(class Item *target, const OrderSpecs &orderSpecs);

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
    this->maxAttemps = MAXATTEMPTS;
    this->nodeRoot = nodePtr();
    this->lexiconFileName = "";
    this->rulesFileName = "";
    this->inputFileName = "";
#ifdef OUTPUT_XML
    this->outXML = nullptr;
#endif
    this->reduceAll = false;
    this->warning = false;
    this->randomResult = false;
    this->firstResult = false;
    this->strategy = STRATEGY_EXHAUSTIVE;
    this->maxRuleChoices = 0;
    this->beamWidth = 0;
    std::random_device rd;
    this->randomSeed = rd();
    this->randomSeedSet = false;
    this->randomEngine.seed(this->randomSeed);
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
Generator::itemSet_map::const_iterator Generator::cbeginStates() const
{
    return states.cbegin();
}

/* **************************************************
 *
 ************************************************** */
Generator::itemSet_map::const_iterator Generator::cendStates() const
{
    return states.cend();
}

/* **************************************************
 *
 ************************************************** */
size_t Generator::sizeStates() const
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
void Generator::setMacrosFileName(char *name)
{
    macrosFileName = name;
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
std::string Generator::getMacrosFileName() const
{
    return macrosFileName;
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
void Generator::setMaxAttemps(unsigned int _maxAttemps)
{
    this->maxAttemps = _maxAttemps;
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

/* **************************************************
 *
 ************************************************** */
void Generator::setStrategy(Strategy strategy)
{
    this->strategy = strategy;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::setStrategy(const std::string &name)
{
    if (name == "exhaustive")
    {
        setStrategy(STRATEGY_EXHAUSTIVE);
        return true;
    }

    if (name == "sample")
    {
        setStrategy(STRATEGY_SAMPLE);
        return true;
    }

    if (name == "beam")
    {
        setStrategy(STRATEGY_BEAM);
        return true;
    }

    return false;
}

/* **************************************************
 *
 ************************************************** */
Generator::Strategy Generator::getStrategy() const
{
    return this->strategy;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::isStrategyExhaustive() const
{
    return this->strategy == STRATEGY_EXHAUSTIVE;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::isStrategySample() const
{
    return this->strategy == STRATEGY_SAMPLE;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::isStrategyBeam() const
{
    return this->strategy == STRATEGY_BEAM;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setMaxRuleChoices(unsigned int value)
{
    this->maxRuleChoices = value;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Generator::getMaxRuleChoices() const
{
    return this->maxRuleChoices;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Generator::getEffectiveMaxRuleChoices() const
{
    if (this->maxRuleChoices > 0)
        return this->maxRuleChoices;

    if (this->strategy == STRATEGY_SAMPLE)
        return 2;

    return 0;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setBeamWidth(unsigned int value)
{
    this->beamWidth = value;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Generator::getBeamWidth() const
{
    return this->beamWidth;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Generator::getEffectiveBeamWidth() const
{
    if (this->beamWidth > 0)
        return this->beamWidth;

    if (this->strategy == STRATEGY_BEAM)
        return 250;

    return 0;
}

/* **************************************************
 *
 ************************************************** */
void Generator::seedRandom(uint32_t seed)
{
    this->randomSeed = seed;
    this->randomSeedSet = true;
    this->randomEngine.seed(seed);
}

/* **************************************************
 *
 ************************************************** */
uint32_t Generator::getRandomSeed(void) const
{
    return this->randomSeed;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::hasRandomSeed(void) const
{
    return this->randomSeedSet;
}

/* **************************************************
 *
 ************************************************** */
uint32_t Generator::randomUInt(void)
{
    std::uniform_int_distribution<uint32_t> distribution(
        0,
        std::numeric_limits<uint32_t>::max());

    return distribution(this->randomEngine);
}

/* **************************************************
 *
 ************************************************** */
size_t Generator::randomIndex(size_t size)
{
    if (size == 0)
    {
        throw fatal_exception("randomIndex called with size 0");
    }

    std::uniform_int_distribution<size_t> distribution(0, size - 1);
    return distribution(this->randomEngine);
}

/* **************************************************
 *
 ************************************************** */
double Generator::randomDouble01(void)
{
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(this->randomEngine);
}

/* **************************************************
 *
 ************************************************** */
std::mt19937 &Generator::getRandomEngine(void)
{
    return this->randomEngine;
}

/* **************************************************
 * Insert an item into a state, with optional pruning.
 ************************************************** */
bool Generator::insertStateItem(class ItemSet *state, class Item *item, bool fatalOnFailure)
{
    const unsigned int effectiveBeamWidth = getEffectiveBeamWidth();

    if (effectiveBeamWidth > 0 && state->size() >= effectiveBeamWidth)
    {
        free(item);
        return false;
    }

    if (!isStrategyExhaustive() && this->maxItems > 0 && state->size() >= this->maxItems)
    {
        free(item);
        return false;
    }

    bool inserted = state->insert(item, this);

    if (inserted)
    {
        insertItemMap(item);
        return true;
    }

    free(item);

    if (fatalOnFailure && isStrategyExhaustive())
    {
        throw fatal_exception("unexpected duplicate item insertion");
    }

    return false;
}

/* **************************************************
 * Insert an item unless an equivalent item is already present.
 ************************************************** */
bool Generator::insertOrMergeStateItem(class ItemSet *state, class Item *item)
{
    auto found = state->find(item);
    if (found != state->cend())
    {
        const bool refsChanged = mergeRefs(*found, item->getRefs());
        const bool orderSpecsChanged = mergeOrderSpecs(*found, item->getOrderSpecs());
        free(item);
        return refsChanged || orderSpecsChanged;
    }

    return insertStateItem(state, item, true);
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
bool Generator::emptyInputs()
{
    return inputs.empty();
}

/* **************************************************
 *
 ************************************************** */
void Generator::addInput(const std::string &input)
{
    inputs.push_back(input);
}

/* **************************************************
 *
 ************************************************** */
std::list<std::string>::const_iterator Generator::cbeginInputs()
{
    return inputs.cbegin();
}

/* **************************************************
 *
 ************************************************** */
std::list<std::string>::const_iterator Generator::cendInputs()
{
    return inputs.cend();
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
void Generator::eraseItemMap(uint32_t id)
{
    this->itemMap.erase(id);
}

/* **************************************************
 *
 ************************************************** */
class Item *Generator::getItemMap(uint32_t id)
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
void Generator::toHTMLState(std::ostream &outStream, class ItemSet *state)
{
    outStream << "Q" << state->getId();
    state->toHTML(outStream);
}

/* **************************************************
 *
 ************************************************** */
class Item *Generator::createItem(class Item *item, uint32_t row)
{
    class Item *it = Item::create(item->getRule(), item->getIndex() + 1, item->getIndexTerms(),
                                  item->getStatements() ? item->getStatements()->clone(
                                                              Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED)
                                                        : statementsPtr());
    it->addRanges(item->getRanges());
    it->addRange(row);
    it->addForestIdentifiers(item->getForestIdentifiers());
    it->setInheritedFeatures(item->getInheritedFeatures()->clone());
    it->setInheritedChildFeatures(item->getInheritedChildFeatures()->clone());
    it->setSynthesizedFeatures(item->getSynthesizedFeatures()->clone());
    it->setSynthesizedChildFeatures(item->getSynthesizedChildFeatures()->clone());
    it->setSeen(item->getSeen());
    it->setOrderSpecs(item->getOrderSpecs());
    return it;
}

/* **************************************************
 *
 ************************************************** */
std::string
Generator::keyMemoization(class Item *actualItem, class Item *previousItem)
{
    std::stringstream ss;

    ss << actualItem->peekCoreSerialString();
    ss << '\x0';
    ss << previousItem->peekCoreSerialString();

    return ss.str();
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
static bool sameNode(const nodePtr &a, const nodePtr &b)
{
    if (a->getWithSpace() != b->getWithSpace())
        return false;

    if (a->size() != b->size())
        return false;

    if (a->getRhsIndexes() != b->getRhsIndexes())
        return false;

    if (a->getOrderSpecs() != b->getOrderSpecs())
        return false;

    for (size_t i = 0; i < a->size(); ++i)
    {
        if (a->at(i)->getId() != b->at(i)->getId())
            return false;
    }

    return true;
}

/* **************************************************
 *
 ************************************************** */
static bool containsEquivalentNode(const forestPtr &forest, const nodePtr &node)
{
    for (auto it = forest->cbegin(); it != forest->cend(); ++it)
    {
        if (sameNode(*it, node))
            return true;
    }
    return false;
}

/* **************************************************
 * Merge refs and report whether this really changed the target item.
 ************************************************** */
static bool mergeRefs(class Item *target, const Item::set_of_uint32_t &refs)
{
    const size_t before = target->getRefs().size();
    target->addRefs(refs);
    return target->getRefs().size() != before;
}

/* **************************************************
 * Merge order specs and report whether this really changed the target item.
 *
 * Order specs are not part of the ItemSet key because they are produced by
 * statements after insertion.  When an equivalent item is found, keep all
 * order constraints by merging them explicitly.
 ************************************************** */
static bool mergeOrderSpecs(class Item *target, const OrderSpecs &orderSpecs)
{
    const size_t before = target->getOrderSpecs().size();

    for (const auto &orderSpec : orderSpecs.asVector())
    {
        target->addOrderSpec(orderSpec);
    }

    return target->getOrderSpecs().size() != before;
}

/* **************************************************
 * PASS/UNFOLD must only be performed by Generator::normalize().
 ************************************************** */
static bool needsNormalization(class Item *item)
{
    if (item->getRuleRhs().size() <= item->getIndex() ||
        item->isCompleted() ||
        item->getForestIdentifiers()[item->getIndex()])
    {
        return false;
    }

    termsPtr terms = item->getCurrentTerms();
    return terms->isOptional() || terms->size() > 1;
}


/* **************************************************
 * Normalize a state before closure/shift.
 ************************************************** */
bool Generator::normalize(Parser &, class ItemSet *state, uint32_t row)
{
    bool modification;
    bool modificationOnce = false;

    do
    {
        modification = false;

        for (auto actualItem = state->cbegin();
             actualItem != state->cend() && !modification;
             ++actualItem)
        {
            if ((*actualItem)->isSetFlags(Flags::SEEN | Flags::BOTTOM))
                continue;

            // X -> alpha • [Y] gamma
            if ((*actualItem)->getRuleRhs().size() > (*actualItem)->getIndex() &&
                !(*actualItem)->isCompleted() &&
                !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()] &&
                (*actualItem)->getCurrentTerms()->isOptional())
            {
                const uint8_t normalizedIndex = (*actualItem)->getIndex();
                const bool newlyMarked = !(*actualItem)->isNormalizedAt(normalizedIndex);

#ifdef TRACE_PASS
                if (newlyMarked)
                {
                    std::cout << "<H3>####################### PASS #######################</H3>" << std::endl;
                    (*actualItem)->toHTML(std::cout);
                    std::cout << std::endl;
                }
#endif

                /*
                 * Keep the source item as an idempotence witness.  It is marked
                 * as already normalized at its current dot position and is never
                 * processed by close()/shift() while it still needs normalization.
                 * If a later reduce recreates the same source item with extra refs,
                 * state->find() merges those refs into this witness and normalize()
                 * re-emits the already computed branches below.
                 */
                if (newlyMarked)
                {
                    (*actualItem)->markNormalizedAt(normalizedIndex);
                }

                class Item *absent = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED, verbose);
                absent->clearNormalizedAt(normalizedIndex);
                forestPtr forestFound = forestPtr();
                class ForestIdentifier *fi = ForestIdentifier::create(absent->getCurrentTerms()->getId(),
                                                                      row,
                                                                      row);
                auto forestMapIt = forestMap.find(fi);
                if (forestMapIt != forestMap.cend())
                {
                    forestFound = forestMapIt->second;
                    free(fi);
                    absent->addForestIdentifiers(absent->getIndex(), forestMapIt->first);
                }
                else
                {
                    forestFound = Forest::create(row, row);
                    forestMap.insert(fi, forestFound);
                    absent->addForestIdentifiers(absent->getIndex(), fi);
                }
                absent->setIndex((*actualItem)->getIndex() + 1);
                absent->getIndexTerms()[(*actualItem)->getIndex()] = 0;
                absent->addRange(row);
                absent->resetCoreSerial();

                class Item *present = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED, verbose);
                present->clearNormalizedAt(normalizedIndex);
                present->setRule((*actualItem)->getRule()->clone());
                present->setIndex((*actualItem)->getIndex());
                if (present->getCurrentTerms()->size() == 1)
                {
                    present->getIndexTerms()[(*actualItem)->getIndex()] = 0;
                }
                else
                {
                    present->getIndexTerms()[(*actualItem)->getIndex()] = Item::POSTERMS_NA;
                }
                present->getCurrentTerms()->unsetOptional();
                present->resetCoreSerial();

#ifdef TRACE_PASS
                if (newlyMarked)
                {
                    std::cout << "<H3>####################### PASS: X -> alpha [Y] • gamma #######################</H3>" << std::endl;
                    absent->toHTML(std::cout);
                    std::cout << std::endl;
                }
#endif
                if (insertOrMergeStateItem(state, absent))
                {
                    modification = true;
                }

#ifdef TRACE_PASS
                if (newlyMarked)
                {
                    std::cout << "<H3>####################### PASS: X -> alpha • Y gamma #######################</H3>" << std::endl;
                    present->toHTML(std::cout);
                    std::cout << std::endl;
                }
#endif
                if (insertOrMergeStateItem(state, present))
                {
                    modification = true;
                }

                if (newlyMarked)
                {
                    modification = true;
                }

                if (modification)
                {
                    modificationOnce = true;
                }
            }

            // X -> alpha • Y1|Y2 beta
            else if ((*actualItem)->getRuleRhs().size() > (*actualItem)->getIndex() &&
                     !(*actualItem)->isCompleted() &&
                     !(*actualItem)->getCurrentTerms()->isOptional() &&
                     (*actualItem)->getCurrentTerms()->size() > 1)
            {
                const uint8_t normalizedIndex = (*actualItem)->getIndex();
                const bool newlyMarked = !(*actualItem)->isNormalizedAt(normalizedIndex);

#ifdef TRACE_UNFOLD
                if (newlyMarked)
                {
                    std::cout << "<H3>####################### UNFOLD #######################</H3>" << std::endl;
                    (*actualItem)->toHTML(std::cout);
                    std::cout << std::endl;
                }
#endif

                if (newlyMarked)
                {
                    (*actualItem)->markNormalizedAt(normalizedIndex);
                }

                termsPtr terms = (*actualItem)->getCurrentTerms();

                std::vector<uint8_t> candidateTermIndexes;

                for (uint8_t indexTerm1 = 0; indexTerm1 < terms->size(); ++indexTerm1)
                {
                    candidateTermIndexes.push_back(indexTerm1);
                }

                const unsigned int maxRuleChoices = getEffectiveMaxRuleChoices();

                if (isStrategySample() && candidateTermIndexes.size() > 1)
                {
                    std::shuffle(candidateTermIndexes.begin(),
                                 candidateTermIndexes.end(),
                                 this->getRandomEngine());
                }

                if (maxRuleChoices > 0 && candidateTermIndexes.size() > maxRuleChoices)
                {
                    candidateTermIndexes.resize(maxRuleChoices);
                    WARNING("unfolding: too many choices, only the first " << maxRuleChoices << " will be considered");
                }

                for (uint8_t indexTerm1 : candidateTermIndexes)
                {
                    class Item *it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED, verbose);
                    it->clearNormalizedAt(normalizedIndex);
                    it->setRule((*actualItem)->getRule()->clone());
                    it->setIndex((*actualItem)->getIndex());
                    it->setCurrentTerms(Terms::create((*terms)[indexTerm1]));
                    it->getIndexTerms()[(*actualItem)->getIndex()] = indexTerm1;
                    it->resetCoreSerial();

#ifdef TRACE_UNFOLD
                    if (newlyMarked)
                    {
                        std::cout << "<H3>####################### UNFOLD: insert #######################</H3>" << std::endl;
                        it->toHTML(std::cout);
                        std::cout << std::endl;
                    }
#endif

                    if (insertOrMergeStateItem(state, it))
                    {
                        modification = true;
                    }
                }

                if (newlyMarked)
                {
                    modification = true;
                }

                if (modification)
                {
                    modificationOnce = true;
                }
            }
        }
    } while (modification);

    for (const auto &i : *state)
        i->subFlags(Flags::SEEN);

    return modificationOnce;
}


/* **************************************************
 *
 ************************************************** */
void Generator::traceState(class ItemSet *state)
{
    if (!traceStage)
    {
        return;
    }

    std::cout << "<H3>####################### STAGE "
              << state->getId()
              << " #######################</H3>" << std::endl;
    state->toHTML(std::cout);
    std::cout << std::endl;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::close(Parser &parser, class ItemSet *state, uint32_t row)
{
    bool modification;
    bool modificationOnce = false;

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

            if (false)
            {
                // PASS and UNFOLD are handled by normalize().
            }

            else
            {

                /*
                 * Leave PASS/UNFOLD to the central normalize() phase. close()
                 * must not apply statements, step, close or reduce an item whose
                 * dot is still on an unresolved optional/alternative term.
                 */
                if (needsNormalization(*actualItem))
                {
                    continue;
                }

                if ((*actualItem)->getStatements() && (*actualItem)->isUnsetFlags(Flags::BOTTOM) && (*actualItem)->getStatements()->isUnsetFlags(Flags::SEEN))
                {
                    if (getTraceAction() || ((getTrace() && (*actualItem)->getRuleTrace())))
                    {
                        std::cout << "<H3>####################### ACTION #######################</H3>" << std::endl;
                        (*actualItem)->toHTML(std::cout);
                        std::cout << std::endl;
                    }

                    if (!(*actualItem)->getEnvironment())
                    {
                        (*actualItem)->_setEnvironment(Environment::create());
                    }

                    (*actualItem)->apply(parser, this, verbose);
                    if (getTraceAction() || ((getTrace() && (*actualItem)->getRuleTrace())))
                    {
                        std::cout << "<H3>####################### ACTION DONE #######################</H3>" << std::endl;
                        (*actualItem)->toHTML(std::cout);
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
                else if ((*actualItem)->getRuleRhs().size() > (*actualItem)->getIndex() &&
                         !(*actualItem)->isCompleted() &&
                         !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()] &&
                         (*actualItem)->getCurrentTerms()->size() == 1 &&
                         !(*actualItem)->getCurrentTerms()->isOptional() &&
                         parser.getRules().isNonTerminal((*actualItem)->getCurrentTerm()) &&
                         !(*(*actualItem)->getInheritedChildFeatures())[(*actualItem)->getIndex()]->isNil())
                {

                    if (traceClose || (trace && (*actualItem)->getRuleTrace()))
                    {
                        std::cout << "<H3>####################### CLOSE (X -> α • Y β) #######################</H3>" << std::endl;
                        (*actualItem)->toHTML(std::cout);
                        std::cout << std::endl;
                    }

                    (*actualItem)->addFlags(Flags::SEEN);

                    featuresPtr inheritedChildFeatures = (*(*actualItem)->getInheritedChildFeatures())[(*actualItem)->getIndex()];
                    if (!inheritedChildFeatures->isNil() && !inheritedChildFeatures->isBottom())
                    {

                        std::vector<rulePtr> candidateRules;

                        for (const auto &iterRules : parser.getRules().getRules())
                        {
                            if (iterRules->getLhs() == (*actualItem)->getCurrentTerm())
                            {
                                candidateRules.push_back(iterRules);
                            }
                        }

                        const unsigned int maxRuleChoices = getEffectiveMaxRuleChoices();

                        if (isStrategySample() && candidateRules.size() > 1)
                        {
                            std::shuffle(
                                candidateRules.begin(),
                                candidateRules.end(),
                                this->getRandomEngine());
                        }

                        if (maxRuleChoices > 0 && candidateRules.size() > maxRuleChoices)
                        {
                            candidateRules.resize(maxRuleChoices);
                        }

                        for (const auto &iterRules : candidateRules)
                        {
                            class Item *it = Item::create(iterRules->clone(), 0, Item::POSTERM_NA,
                                                          iterRules->getStatements() ? iterRules->getStatements()->clone(0)
                                                                                     : statementsPtr());
                            it->addRange(row);
                            it->setInheritedFeatures(inheritedChildFeatures->clone());
                            it->renameVariables(it->getId());

                            /*
                             * Refs are reverse links only.  They are not part of
                             * the item identity; if an equivalent item already
                             * exists, we merge the new parent ref into it.
                             */
                            it->addRef((*actualItem)->getId());

                            if (traceClose || (trace && it->getRuleTrace()))
                            {
                                std::cout << "<H3>####################### CLOSE CON'T (Y -> • γ) #######################</H3>" << std::endl;
                                it->toHTML(std::cout);
                                std::cout << std::endl;
                                std::flush(std::cout);
                            }

                            // record the item
                            auto found = state->find(it);
                            if (found != state->cend())
                            {
                                const bool refsChanged = mergeRefs(*found, it->getRefs());
                                const bool orderSpecsChanged = mergeOrderSpecs(*found, it->getOrderSpecs());
                                if (refsChanged || orderSpecsChanged)
                                {
                                    iterRules->incUsages(this);
                                    modification = true;
                                }
                                free(it);
                            }
                            else
                            {
                                iterRules->incUsages(this);

                                if (insertStateItem(state, it, true))
                                {
                                    modification = true;
                                }
                                else if (isStrategyExhaustive())
                                {
                                    FATAL_ERROR_UNEXPECTED
                                }
                            }
                            (*actualItem)->addFlags(Flags::SEEN);
                        }
                    }
                }

                // X -> delta •
                else if ((*actualItem)->isCompleted())
                {

                    if (traceReduce || (trace && (*actualItem)->getRuleTrace()))
                    {
                        std::cout << "<H3>####################### REDUCE Y -> γ • (actual) #######################</H3>" << std::endl;
                        (*actualItem)->toHTML(std::cout);
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
                                    (*actualItem)->toHTML(std::cout);
                                    std::cout << std::endl;
                                }

                                forestPtr forestFound = forestPtr();
                                class ForestIdentifier *fi = ForestIdentifier::create((*actualItem)->getRuleLhs(),
                                                                                      (*actualItem)->getRanges()[0],
                                                                                      row);
                                auto forestMapIt = forestMap.find(fi);
                                if (forestMapIt != forestMap.cend())
                                {
                                    forestFound = (*forestMapIt).second;
                                    free(fi);
                                }
                                else
                                {
                                    forestFound = Forest::create((*actualItem)->getRanges()[0], row);
                                    forestMap.insert(fi, forestFound);
                                    nodePtr node = Node::create((*actualItem)->getWithSpaces(), (*actualItem)->getUnordered());
                                    // The axiom forest is a possible root even when it is empty
                                    // ([row,row]), e.g. S -> (A) (B) (C) (D) with every
                                    // optional branch skipped.  Do not make it a child of
                                    // itself when it is empty, but still expose it through
                                    // nodeRoot so generation can emit the empty result.
                                    nodeRoot->push_back(forestFound);
                                    if (forestFound->getFrom() != forestFound->getTo())
                                    {
                                        node->push_back(forestFound);
                                    }
                                }
                                nodePtr node = Node::create((*actualItem)->getWithSpaces(), (*actualItem)->getUnordered());

                                uint32_t rhsIndex = 0;
                                for (auto forestIdentifier : (*actualItem)->getForestIdentifiers())
                                {
                                    auto _forestMapIt = forestMap.find(forestIdentifier);
                                    if (_forestMapIt != forestMap.cend())
                                    {
                                        forestPtr forest = (*_forestMapIt).second;

                                        if (forest->getFrom() != forest->getTo())
                                        {
                                            node->push_back(rhsIndex, forest);
                                        }
                                    }

                                    ++rhsIndex;
                                }

                                node->setOrderSpecs((*actualItem)->getOrderSpecs());

                                if (!containsEquivalentNode(forestFound, node))
                                {
                                    forestFound->push_node(node);
                                }
                            }
                            for (auto ref : (*actualItem)->getRefs())
                            {
                                class Item *previousItem = getItemMap(ref);
                                if (!previousItem)
                                {
                                    // No item for this reference
                                    FATAL_ERROR_UNEXPECTED;
                                }
                                else
                                {

                                    if (traceReduce || (trace && previousItem->getRuleTrace()))
                                    {
                                        std::cout << "<H3>####################### REDUCE CON'T (X -> α • Y β) #######################</H3>" << std::endl;
                                        previousItem->toHTML(std::cout);
                                        std::cout << std::endl;
                                    }

                                    std::string key = keyMemoization(*actualItem, previousItem);
                                    auto memItem = memoizedMap.find(key);
                                    // Is this already done ?
                                    if (memItem != memoizedMap.cend())
                                    {

                                        std::vector<class MemoizationValue *> result = memItem->second;
                                        for (std::vector<class MemoizationValue *>::const_iterator memoizationValue = result.cbegin();
                                             memoizationValue != result.cend();
                                             ++memoizationValue)
                                        {

                                            //(*memoizationValue)->getItem()->addRef(previousItem->getId());

                                            // New item build
                                            class Item *it = createItem(previousItem, row);
                                            it->cloneEnvironment(previousItem);
                                            //...
                                            featuresPtr inheritedFeatures = it->getInheritedFeatures();

                                            it->addForestIdentifiers(previousItem->getIndex(), (*memoizationValue)->getForestIdentifier());

                                            /*
                                             * The memoized REDUCE path must restore the synthesized
                                             * features of the daughter just reduced.  They are stored
                                             * in the MemoizationValue when the non-memoized REDUCE path
                                             * records the reduction.
                                             *
                                             * Without this, statements depending on ⇓i may remain pending
                                             * on the reconstructed item.  In particular,
                                             *
                                             *     order 1, 2, 3 by ⇓.rank;
                                             *
                                             * can be skipped on a completed item reconstructed from
                                             * memoization, which then inserts an unconstrained node in
                                             * the forest in addition to the ordered one.
                                             */
                                            featuresPtr memoizedFeatures = (*memoizationValue)->getFeatures();
                                            if (memoizedFeatures)
                                            {
                                                it->getSynthesizedChildFeatures()->add(previousItem->getIndex(),
                                                                                       memoizedFeatures->clone());
                                            }

#ifdef TRACE_MEMOIZATION
                                            std::cout << "<H3>####################### MEMOIZED REDUCE (X -> α Y • β) #######################</H3>" << std::endl;
                                            it->toHTML(std::cout);
                                            std::cout << std::endl;
#endif
                                            it->setRefs(previousItem->getRefs());

                                            auto found = states[row]->find(it);
                                            if (found != states[row]->cend())
                                            {
                                                const bool refsChanged = mergeRefs(*found, previousItem->getRefs());
                                                const bool orderSpecsChanged = mergeOrderSpecs(*found, it->getOrderSpecs());
                                                if (refsChanged || orderSpecsChanged)
                                                {
                                                    modification = true;
                                                }
                                                free(it);
                                            }
                                            else
                                            {
                                                if (insertOrMergeStateItem(states[row], it))
                                                {
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
                                        it->cloneEnvironment(previousItem);
                                        it->getSynthesizedChildFeatures()->add(previousItem->getIndex(),
                                                                               (*actualItem)->getSynthesizedFeatures()->clone());

                                        //...
                                        featuresPtr inheritedFeatures = it->getInheritedFeatures();

                                        // On transmet le contexte de previousItem
                                        nodePtr node = Node::create((*actualItem)->getWithSpaces(), (*actualItem)->getUnordered());

                                        uint32_t rhsIndex = 0;
                                        for (auto forestIdentifier : (*actualItem)->getForestIdentifiers())
                                        {
                                            auto forestMapIt = forestMap.find(forestIdentifier);
                                            if (forestMapIt == forestMap.cend())
                                            {
                                                FATAL_ERROR_UNEXPECTED
                                            }

                                            forestPtr forest = (*forestMapIt).second;

                                            if (forest->getFrom() != forest->getTo())
                                            {
                                                node->push_back(rhsIndex, forest);
                                            }

                                            ++rhsIndex;
                                        }

                                        node->setOrderSpecs((*actualItem)->getOrderSpecs());
                                        forestPtr forestFound = forestPtr();
                                        class ForestIdentifier *fi = ForestIdentifier::create((*actualItem)->getId(),
                                                                                              (*actualItem)->getRanges()[0],
                                                                                              row);
                                        auto forestMapIt = forestMap.find(fi);
                                        if (forestMapIt != forestMap.cend())
                                        {
                                            forestFound = forestMapIt->second;
                                            it->addForestIdentifiers(previousItem->getIndex(), forestMapIt->first);
                                            free(fi);
                                        }
                                        else
                                        {
                                            forestFound = Forest::create((*actualItem)->getRanges()[0], row);
                                            forestMap.insert(fi, forestFound);
                                            it->addForestIdentifiers(previousItem->getIndex(), fi);
                                        }
                                        if (!containsEquivalentNode(forestFound, node))
                                        {
                                            forestFound->push_node(node);
                                        }
                                        if (traceReduce || (trace && it->getRuleTrace()))
                                        {
                                            std::cout << "<H3>####################### REDUCE CON'T (X -> α Y • β) #######################</H3>" << std::endl;
                                            it->toHTML(std::cout);
                                            std::cout << std::endl;
                                        }
                                        auto found = states[row]->find(it);
                                        if (found != states[row]->cend())
                                        {
                                            const bool refsChanged = mergeRefs(*found, previousItem->getRefs());
                                            const bool orderSpecsChanged = mergeOrderSpecs(*found, it->getOrderSpecs());
                                            if (refsChanged || orderSpecsChanged)
                                            {
                                                modification = true;
                                            }
                                            free(it);
                                        }
                                        else
                                        {

                                            // tabulates this result
                                            int index = it->getIndex() - 1;
                                            memoizedMap.insert(key,
                                                               it->getSynthesizedChildFeatures()->get(index),
                                                               it->getForestIdentifiers()[index],
                                                               it);
                                            // record the item
                                            it->setRefs(previousItem->getRefs());
                                            if (insertOrMergeStateItem(states[row], it))
                                            {
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
                else if ((*actualItem)->getRuleRhs().size() > (*actualItem)->getIndex() &&
                         !(*actualItem)->isCompleted() &&
                         !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()] &&
                         (*actualItem)->getCurrentTerms()->size() == 1 &&
                         !(*actualItem)->getCurrentTerms()->isOptional() &&
                         parser.getRules().isTerminal((*actualItem)->getCurrentTerm()) &&
                         !(*(*actualItem)->getInheritedChildFeatures())[(*actualItem)->getIndex()]->isNil())
                {
                    // shift the next time
                }

                else
                {
                    (*actualItem)->step(modification);
                }
            }
        }

        if (modification)
        {
            modificationOnce = true;
        }
    } while (modification);
    for (const auto &i : *state)
        i->subFlags(Flags::SEEN);

    return modificationOnce;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::shift(class Parser &parser, class ItemSet *state, uint32_t row)
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
            if (needsNormalization(*actualItem))
                continue;
            if ((*actualItem)->getCurrentTerms())
            {
                featuresPtr inheritedChildFeatures = (*(*actualItem)->getInheritedChildFeatures())[(*actualItem)->getIndex()];

                if (!(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()] &&
                    !(*actualItem)->getCurrentTerms()->isOptional() &&
                    (*actualItem)->getCurrentTerm() != Item::TERM_NA &&
                    !inheritedChildFeatures->isNil() &&
                    !inheritedChildFeatures->isBottom() &&
                    parser.getRules().isTerminal((*actualItem)->getCurrentTerm()))
                {

                    if (traceShift || (trace && (*actualItem)->getRuleTrace()))
                    {
                        std::cout << "<H3>####################### SHIFT (X -> α • ω β) where ω ∈ ℒ #######################</H3>" << std::endl;
                        (*actualItem)->toHTML(std::cout);
                        std::cout << std::endl;
                    }

                    std::string *form = nullptr;
                    uint32_t head = inheritedChildFeatures->assignHead();
                    Stage stage;
                    if (head != Vartable::code_for_DOES_NOT_CONTAIN_A_HEAD)
                    {
                        stage = STAGE_HEAD;
                    }
                    else
                    {
                        form = inheritedChildFeatures->assignForm();
                        if (!form)
                        {
                            stage = STAGE_MAIN;
                        }
                        else
                        {
                            stage = STAGE_FORM;
                        }
                    }

                    /*
                     std::cout << "<p>";
                     std::cout << "inheritedChildFeatures : ";
                     inheritedChildFeatures->toHTML(std::cout);
                     std::cout << std::endl;
                     std::cout << "stage:" << (stage == STAGE_HEAD ? "STAGE_HEAD" : (stage == STAGE_FORM ? "STAGE_FORM" : "STAGE_MAIN")) << std::endl;
                     std::cout << "head:" << head << std::endl;
                     std::cout << "form:" << form << std::endl;
                     std::cout << "pos : " << Vartable::codeToName((*actualItem)->getCurrentTerm()) << std::endl;
                     std::cout << "</p>";
                    */

                    auto foundpos = parser.findCacheLexicon((*actualItem)->getCurrentTerm());
                    // std::cout << "foundpos : " << (foundpos != parser.cendCacheLexicon() ? "yes" : "no") << std::endl;

                    if (foundpos != parser.cendCacheLexicon() && (!foundpos->second->empty()))
                    {
                        Parser::entries_map *entriesMap = foundpos->second;
                        // std::cout << "entriesMap : " << (entriesMap ? "yes" : "no") << std::endl;

                        if (entriesMap)
                        {
                            Parser::entries_map::const_iterator found;
                            entriesPtr entries = entriesPtr();

                            /*
                            COUT_LINE;
                            std::cout << "stage : " << (stage == STAGE_HEAD ? "STAGE_HEAD" : (stage == STAGE_FORM ? "STAGE_FORM" : "STAGE_MAIN")) << std::endl;
                            std::cout << "head : " << Vartable::codeToName(head) << std::endl;
                            std::cout << "form : \"" << (form ? *form : "nullptr") << '"' << std::endl;
                            */

                            switch (stage)
                            {

                            case STAGE_HEAD:
                                entries = findByHeadThenCompactedLexicon(parser, entriesMap, (*actualItem)->getCurrentTerm(), head);
                                /*
                                std::cout << "entries found by head : " << (entries ? entries->size() : 0) << std::endl;
                                */
                                break;

                            case STAGE_MAIN:
                                entries = findMain(entriesMap);
                                break;

                            case STAGE_FORM:
                                entries = findByForm(entriesMap);
                                break;
                            }

                            if (!entries || entries->size() == 0)
                            {
                                (*actualItem)->addFlags(Flags::BOTTOM);
                                modification = true;
                                modificationOnce = true;
                                continue;
                            }

                            // Found !
                            if (entries && entries->size() > 0)
                            {
                                // cont = false;
                                auto entryIt = entries->begin();
                                int tryRandom = 0;
                                while (entryIt != entries->end())
                                {
                                    entryPtr entry = *entryIt;

                                    if (this->randomResult)
                                    {
                                        if (tryRandom++ > maxAttemps)
                                        {
                                            WARNING("too many random attempts");
                                            break;
                                        }
                                        size_t rv = this->randomIndex(entries->size());
                                        entry = entries->get(rv);
                                    }
                                    else
                                    {
                                        entry = *entryIt;
                                        ++entryIt;
                                    }
                                    /*
                                    std::cout << "entry : " << entry->getId() << std::endl;
                                    std::cout << "<BR>" << std::endl;
                                    entry->print(std::cout);
                                    std::cout << "<BR>" << std::endl;
                                    */

                                    entryPtr entry_copy = entry->clone();
                                    featuresPtr entryFeatures = entry_copy->getFeatures() ? entry_copy->getFeatures()
                                                                                          : featuresPtr();
                                    statementsPtr entryStatements = statementsPtr();
                                    environmentPtr env = (*actualItem)->getEnvironment()
                                                             ? (*actualItem)->getEnvironment()->clone(nullptr, verbose)
                                                             : Environment::create();

                                    /*
                                    std::cout << "entry_copy : " << entry_copy->getId() << std::endl;
                                    std::cout << "<BR>" << std::endl;
                                    entry_copy->print(std::cout);
                                    std::cout << "<BR>" << std::endl;
                                    entryFeatures->toHTML(std::cout);
                                    std::cout << "<BR>" << std::endl;
                                    bool subsumes = entryFeatures->subsumes(nullptr, inheritedChildFeatures, env, verbose);
                                    std::cout << "subsumes: " << subsumes << std::endl;
                                    std::cout << "<BR>" << std::endl;
                                    */

                                    // Filter !!
                                    // entryFeatures subsumes ↑

                                    bool okSubsumes =
                                        stage == STAGE_FORM ||
                                        (entryFeatures && entryFeatures->subsumes(nullptr, inheritedChildFeatures, env, verbose));

                                    if (okSubsumes)
                                    {

                                        // New item build
                                        class Item *it = createItem(*actualItem, row);

                                        it->_setEnvironment(env);

                                        featuresPtr resultFeatures = featuresPtr();
                                        featuresPtr inheritedChildFeaturesCopy = inheritedChildFeatures->clone();
                                        featuresPtr entryFeaturesCopy = entryFeatures->clone();

                                        if (entryFeatures)
                                        {
                                            resultFeatures = entryFeaturesCopy;
                                        }
                                        else
                                        {

                                            resultFeatures = inheritedChildFeaturesCopy;
                                        }

                                        // if (resultFeatures)
                                        // {
                                        //     if (!it->environmentIsEmpty())
                                        //     {
                                        //         // replace ?
                                        //         // bool effect = false;
                                        //         // it->getEnvironment()->replaceVariables(resultFeatures, effect);
                                        //     }
                                        //     resultFeatures->renameVariables(entry_copy->getId());
                                        // }

                                        it->getSynthesizedChildFeatures()->add((*actualItem)->getIndex(),
                                                                               entryFeaturesCopy);
                                        // if (entryStatements)
                                        // {
                                        //     entryStatements->renameVariables(entry_copy->getId());
                                        // }
                                        forestPtr forest;
                                        if (stage == STAGE_FORM)
                                        {
                                            forest = Forest::create(row - 1, row, *form);
                                        }
                                        else
                                        {
                                            forest = Forest::create(row - 1, row, entry_copy->getForm());
                                        }
                                        if (forest->getForm().find('$') != std::string::npos)
                                        {
                                            //
                                            bool effect = false;
                                            it->environmentReplaceVariables(forest->getForm(), effect);
                                        }
                                        ForestIdentifier *forestIdentifier = ForestIdentifier::create(entry_copy->getId(),
                                                                                                      row - 1, row);

                                        auto forestMapIt = forestMap.find(forestIdentifier);
                                        if (forestMapIt != forestMap.cend())
                                        {
                                            it->addForestIdentifiers((*actualItem)->getIndex(),
                                                                     (*forestMapIt).first);
                                            free(forestIdentifier);
                                            // std::cout << "stage : " << stage << "<BR>" << std::endl;
                                            // std::cout << "head : " << Vartable::codeToName(head) << "<BR>" << std::endl;
                                            // std::cout << "form : " << form << "<BR>" << std::endl;
                                        }
                                        else
                                        {
                                            forestMap.insert(forestIdentifier, forest);
                                            it->addForestIdentifiers((*actualItem)->getIndex(), forestIdentifier);
                                        }
                                        it->setRefs((*actualItem)->getRefs());

                                        if (traceShift || (trace && it->getRuleTrace()))
                                        {
                                            std::cout << "<H3>####################### SHIFT CON'T (X -> α ω • β) #######################</H3>" << std::endl;
                                            it->toHTML(std::cout);
                                            std::cout << std::endl;
                                        }

                                        if (insertStateItem(states[row], it, true))
                                        {
                                            modification = true;
                                            modificationOnce = true;
                                        }

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
    nodeRoot = Node::create(false, false);
    class ItemSet *initState = ItemSet::create(0);
    std::list<rulePtr> *rules = parser.getRules().findRules(parser.getStartTerm());
    class Item *it;
    for (std::list<rulePtr>::const_iterator rule = rules->begin(); rule != rules->end(); ++rule)
    {
        (*rule)->incUsages(this);
        it = Item::create(*rule, Item::INDEX_NA, Item::POSTERM_NA,
                          (*rule)->getStatements() ? (*rule)->getStatements()->clone(0) : statementsPtr());
        it->addRange(0);
        featuresPtr startFeatures = parser.getStartFeatures();
        it->setInheritedFeatures(startFeatures);
        // inutile
        it->renameVariables(it->getId());

        if (traceInit || (trace && it->getRuleTrace()))
        {
            std::cout << "<H3>####################### INIT #######################</H3>" << std::endl;
            it->toHTML(std::cout);
            std::cout << std::endl;
        }
        insertStateItem(initState, it, true);
    }

    auto saturateState = [&](class ItemSet *state, uint32_t row)
    {
        bool modification;
        do
        {
            modification = false;
            if (normalize(parser, state, row))
            {
                modification = true;
            }
            if (close(parser, state, row))
            {
                modification = true;
            }
        } while (modification);
    };

    states.insert(std::make_pair(0, initState));
    saturateState(initState, 0);
    traceState(initState);

    uint32_t i = 0;
    while (i <= maxLength)
    {
        class ItemSet *actualState = ItemSet::create(++i);
        states.insert(std::make_pair(i, actualState));

        bool shiftProducedNextState = false;
        while (true)
        {
            saturateState(initState, i - 1);

            bool shiftOk = shift(parser, initState, i);
            if (actualState->size() > 0)
            {
                shiftProducedNextState = true;
                break;
            }
            if (!shiftOk)
            {
                break;
            }
        }

        if (!shiftProducedNextState)
        {
            break;
        }

        actualState->resetUsages();
        saturateState(actualState, i);
        traceState(actualState);
        initState = actualState;
    }

    if (i > maxLength)
    {
        throw fatal_exception("maxLength");
    }

    if (!nodeRoot->empty())
    {
        for (auto forest = nodeRoot->cbegin(); forest != nodeRoot->cend(); ++forest)
        {
            (*forest)->generate(this, this->getRandomResult(), this->getFirstResult());
        }
    }

#ifdef OUTPUT_XML
    if (outXML)
    {
        nodeRoot->toXML(xmlNodeRoot, xmlNodeRoot);
    }
#endif
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
entriesPtr Generator::findByHead(Parser::entries_map *listHead, uint32_t head)
{
    entriesPtr entries = entriesPtr();
    auto found = listHead->find(head);
    if (found != listHead->end())
    {
        entries = found->second;
    }
    return entries;
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Generator::findMain(Parser::entries_map *map)
{
    entriesPtr entries = entriesPtr();
    auto found = map->find(Vartable::code_for_DOES_NOT_CONTAIN_A_HEAD);
    if (found != map->end())
    {
        entries = found->second;
    }
    return entries;
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Generator::findByHeadThenCompactedLexicon(Parser &parser, Parser::entries_map *map,
                                                     uint32_t pos, uint32_t head)
{

    entriesPtr entries = findByHead(map, head);
    // if none entry found by head
    if (!entries)
    {
        entries = findMain(map);
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
                entries->add(localEntries);
            }
            else
            {
                entries = localEntries;
            }
        }
    }
    return entries;
}

/* **************************************************
 *
 ************************************************** */
entriesPtr Generator::findByForm(Parser::entries_map *map)
{
    entriesPtr entries = entriesPtr();
    auto found = map->find(Vartable::code_for_IS_A_FORM);
    if (found != map->end())
        entries = found->second;
    return entries;
}

/* **************************************************
 * search
 * |str(pos)#str(head)
 * |str(pos)#_
 *
 * returns entries= (entry1, entry2, ...)
 * where entryi= (uint32_t pos, uint32_t head, std::string form, featuresPtr features)
 ************************************************** */
entriesPtr Generator::findCompactedLexicon(Parser &parser, const uint32_t pos, const uint32_t head)
{
    uint32_t info = (uint32_t)~0UL;
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

    // std::cerr << "search " << str << " in compactedLexicon" << std::endl;
    info = compactedLexicon->search(compactedLexicon->init, str);
    // in : pos#lemma
    // out : form#fs
#ifdef TRACE_LEXICON
    std::cout << "<H3>####################### FIND IN THE COMPACT LEXICON #######################</H3>" << std::endl;
    std::cout << "<DIV>" << std::endl;
    std::cout << str << " => ";
    compactedLexicon->toHTMLResults(std::cout, info, 1);
    std::cout << "</DIV>" << std::endl;
    std::cout << std::endl;
#endif
    if (info != (uint32_t)~0UL)
    {
        entriesPtr entries = Entries::create();
        while (info != (uint32_t)~0UL)
        {
            std::string result = compactedLexicon->buffer + (compactedLexicon->info[info].getOffset());
            std::string form = result.substr(0, result.find('#'));
            std::string features = result.substr(result.find('#') + 1, -1);

            try
            {
                parser.parseBuffer("#(", ")", features, "features");
                if (parser.getLocalFeatures())
                {
                    // entryPtr localEntry = Entry::create(form, parser.getLocalFeatures())->clone();
                    entryPtr localEntry = Entry::create(form, parser.getLocalFeatures());

                    std::string localEntryCoreSerialString = localEntry->peekCoreSerialString();
                    auto found = parser.findMapLocalEntry(localEntryCoreSerialString);
                    if (found != parser.cendMapLocalEntry())
                    {
                        // entries->add(found->second->clone());
                        entries->add(found->second);
                    }
                    else
                    {
                        // entries->add(localEntry->clone());
                        entries->add(localEntry);
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
            if (compactedLexicon->info[info].isNext())
                info = compactedLexicon->info[info].getNext();
            else
                info = (uint32_t)(~(0UL));
        }
        return entries;
    }
    else
    {
        return entriesPtr();
    }
}
