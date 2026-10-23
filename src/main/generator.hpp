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

#ifndef ELVEX_GENERATOR_H
#define ELVEX_GENERATOR_H

#include <unordered_map>
#include <string>
#include <random>
#include <cstdint>

#include "shared_ptr.hpp"
#include "forestmap.hpp"
#include "memoization-map.hpp"
#include "parser.hpp"

#ifndef MAXLENGTH
#define MAXLENGTH 3000
#endif

#ifndef MAXUSAGES
#define MAXUSAGES 3000
#endif

#ifndef MAXITEMS
#define MAXITEMS 3000
#endif

#ifndef MAXATTEMPTS
#define MAXATTEMPTS 3000
#endif

/**
 * Chart-based natural-language generator combining grammar rules, lexical
 * entries and feature constraints into a packed derivation forest.
 * Enumeration of output strings is a separate, optional final phase.
 */
class Generator
{

public:
    enum Strategy
    {
        STRATEGY_EXHAUSTIVE,
        STRATEGY_SAMPLE,
        STRATEGY_BEAM
    };

    enum Stage
    {
        STAGE_MAIN,
        STAGE_FORM,
        STAGE_HEAD
    };

    typedef std::unordered_map<uint32_t, class Item *> item_map;
    typedef std::unordered_map<uint32_t, class ItemSet *> itemSet_map;

private:
    itemSet_map states;
    ForestMap forestMap;
    item_map itemMap;
    nodePtr nodeRoot;

    std::string compactedLexiconFileName;
    class CompactedLexicon *compactedLexicon;

    // Lexical analyses are immutable templates; shift() clones each entry
    // before unification. Cache is cleared for each generation run.
    std::unordered_map<uint64_t, entriesPtr> compactedEntriesCache;

    // Chart construction steps kept separate from optional linearization.
    void resetGenerationState(class Parser &parser);
    class ItemSet *createInitialState(class Parser &parser);
    void saturateState(class Parser &parser, class ItemSet *state, uint32_t row);
    uint32_t buildChart(class Parser &parser, class ItemSet *initialState);

    // Lexical lookup decisions used by shift(); never modify cached entries.
    Stage classifyShiftStage(const featuresPtr &inheritedFeatures, uint32_t head, std::string *&form) const;
    entriesPtr findShiftEntries(class Parser &parser, Parser::entries_map *entriesMap,
                                Stage stage, uint32_t pos, uint32_t head);

    unsigned int maxLength;
    unsigned int maxUsages;
    unsigned int maxItems;
    unsigned int maxAttemps;
    std::string macrosFileName;
    std::string lexiconFileName;
    std::string rulesFileName;
    std::string inputFileName;

    std::list<std::string> inputs;

    bool reduceAll;
    bool trace;
    bool verbose;
    bool warning;
    bool randomResult;
    bool firstResult;
    bool forestOnly;
    bool progress;
    Strategy strategy;
    unsigned int maxRuleChoices;
    unsigned int beamWidth;

    std::mt19937 randomEngine;
    uint32_t randomSeed;
    bool randomSeedSet;

    MemoizationMap memoizedMap;

    bool traceInit;
    bool traceStage;
    bool traceClose;
    bool traceShift;
    bool traceReduce;
    bool traceAction;

#ifdef OUTPUT_XML
    char *outXML;
#endif

public:
    Generator();

    ~Generator();

    itemSet_map::const_iterator cbeginStates() const;

    itemSet_map::const_iterator cendStates() const;

    size_t sizeStates() const;

    bool emptyInputs(void);

    std::list<std::string>::const_iterator cbeginInputs(void);

    std::list<std::string>::const_iterator cendInputs(void);

    void addInput(const std::string &input);

    void setInputFileName(char *);

    void setMacrosFileName(char *);

    void setLexiconFileName(char *);

    void setRulesFileName(char *);

    void setCompactedLexiconFileName(char *);

    std::string getInputFileName() const;

    std::string getLexiconFileName() const;

    std::string getMacrosFileName() const;

    std::string getCompactedLexiconFileName() const;

    std::string getRulesFileName() const;

    void setMaxLength(unsigned int);

    void setMaxUsages(unsigned int);

    unsigned int getMaxUsages() const;

    void setMaxItems(unsigned int);

    void setMaxAttemps(unsigned int);

    unsigned int getMaxItems() const;

    void setCompactedLexicon(class CompactedLexicon *);

#ifdef OUTPUT_XML
    void setOutXML(char *);
    char *getOutXML() const;
#endif

    void setTraceInit(bool);
    void setTraceStage(bool);
    void setTraceClose(bool);
    void setTraceShift(bool);
    void setTraceReduce(bool);
    void setTraceAction(bool);
    bool getTraceInit();
    bool getTraceStage();
    bool getTraceClose();
    bool getTraceShift();
    bool getTraceReduce();
    bool getTraceAction();

    nodePtr getNodeRoot();

    bool insertItemMap(class Item *);

    void eraseItemMap(uint32_t);

    class Item *getItemMap(uint32_t);

    bool getTrace() const;

    void setTrace(bool);

    void setReduceAll(bool);

    void setRandomResult(bool);

    bool getRandomResult(void) const;

    bool getRandomResultDuringGeneration(void) const;

    void setFirstResult(bool);

    bool getFirstResult(void) const;

    /**
     * Build the packed forest without expanding it into output sentences.
     * Useful for inspecting complexity and serializing shared derivations.
     */
    void setForestOnly(bool value);
    bool getForestOnly() const;

    /**
     * Emit periodic chart-building progress records on standard error.
     * Does not change the generated sentence stream on standard output.
     */
    void setProgress(bool value);
    bool getProgress() const;

    /** Select exhaustive, sampled or beam search for this generation run. */
    void setStrategy(Strategy);

    /** Parse a strategy name; report whether the name was recognized. */
    bool setStrategy(const std::string &);

    Strategy getStrategy(void) const;

    bool isStrategyExhaustive(void) const;

    bool isStrategySample(void) const;

    bool isStrategyBeam(void) const;

    void setMaxRuleChoices(unsigned int);

    unsigned int getMaxRuleChoices(void) const;

    unsigned int getEffectiveMaxRuleChoices(void) const;

    void setBeamWidth(unsigned int);

    unsigned int getBeamWidth(void) const;

    unsigned int getEffectiveBeamWidth(void) const;

    /**
     * Insert a chart item, subject to configured resource limits.
     * A failed insertion can be treated as fatal at the caller's request.
     */
    bool insertStateItem(class ItemSet *, class Item *, bool fatalOnFailure = false);

    /** Merge equivalent chart items or insert a previously unseen one. */
    bool insertOrMergeStateItem(class ItemSet *, class Item *);

    /** Make sampling and random selection reproducible with a fixed seed. */
    void seedRandom(uint32_t seed);

    uint32_t getRandomSeed(void) const;

    bool hasRandomSeed(void) const;

    uint32_t randomUInt(void);

    size_t randomIndex(size_t size);

    double randomDouble01(void);

    std::mt19937 &getRandomEngine(void);

    void toHTMLState(std::ostream &, class ItemSet *);

    /**
     * Propagate rule features and semantic actions within a chart row.
     * Returns whether processing changed the row.
     */
    bool normalize(class Parser &, class ItemSet *, uint32_t);

    void traceState(class ItemSet *);

    /**
     * Expand predicted nonterminals in the current chart row.
     * Returns whether new information was added.
     */
    bool close(class Parser &, class ItemSet *, uint32_t);

    /**
     * Advance terminal expectations using matching lexical entries.
     * Lexical feature subsumption is evaluated in a cloned environment.
     */
    bool shift(class Parser &, class ItemSet *, uint32_t);

    /** Release generation state before processing a new input. */
    void clear();

    static class Item *createItem(class Item *, uint32_t);

    /**
     * Run chart construction and assemble the shared derivation forest.
     * Unless forest-only mode is set, linearize the forest into output strings.
     */
    void generate(class Parser &);

    /**
     * Fetch lexical analyses for a part-of-speech/head pair.
     * The optional cache stores reusable templates; shift() clones them before
     * applying context-dependent variable bindings.
     */
    entriesPtr findCompactedLexicon(class Parser &parser, uint32_t pos, uint32_t head);

    std::string keyMemoization(class Item *, class Item *);

    void setVerbose(bool);

    bool getVerbose();

    entriesPtr findByHead(Parser::entries_map *map, uint32_t head);

    /**
     * Combine local and compacted-lexicon analyses for the same head
     * without altering the parser-owned list of local entries.
     */
    entriesPtr findByHeadThenCompactedLexicon(Parser &parser, Parser::entries_map *map, uint32_t pos, uint32_t head);

    entriesPtr findMain(Parser::entries_map *map);

    entriesPtr findByForm(Parser::entries_map *map);
};

#endif // ELVEX_GENERATOR_H
