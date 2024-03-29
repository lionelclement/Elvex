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

#ifndef ELVEX_GENERATOR_H
#define ELVEX_GENERATOR_H

#include <unordered_map>

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

class Generator
{

public:
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
    std::string compactedDirectoryName;
    class CompactedLexicon *compactedLexicon;

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

    void addInput (const std::string &input);

    void setInputFileName(char *);

    void setMacrosFileName(char *);

    void setLexiconFileName(char *);

    void setRulesFileName(char *);

    void setCompactedLexiconFileName(char *);

    void setCompactedDirectoryName(char *);

    std::string getInputFileName() const;

    std::string getLexiconFileName() const;

    std::string getMacrosFileName() const;

    std::string getCompactedLexiconFileName() const;

    std::string getCompactedDirectoryName() const;

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

    void setFirstResult(bool);

    bool getFirstResult(void) const;

    void printState(std::ostream &, class ItemSet *);

    void close(class Parser &, class ItemSet *, uint32_t);

    bool shift(class Parser &, class ItemSet *, uint32_t);

    void clear();

    static class Item *createItem(class Item *, uint32_t);

    void generate(class Parser &);

    entriesPtr findCompactedLexicon(class Parser &parser, uint32_t pos, uint32_t head);

    std::string keyMemoization(class Item *, class Item *);

    void setVerbose(bool);

    bool getVerbose();

    entriesPtr findByHead(Parser::entries_map *map, uint32_t head);

    entriesPtr findByHeadThenCompactedLexicon(Parser &parser, Parser::entries_map *map, uint32_t pos, uint32_t head);

    entriesPtr findMain(Parser::entries_map *map);

    entriesPtr findByForm(Parser::entries_map *map);
};

#endif // ELVEX_GENERATOR_H
