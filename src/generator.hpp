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
        MORPHO_FEATURES,
        FORM_FEATURES,
        HEAD_FEATURES
    };

    typedef std::unordered_map<unsigned int, class Item *> item_map;
    typedef std::unordered_map<unsigned int, class ItemSet *> itemSet_map;
    typedef itemSet_map::const_iterator itemSet_map_const_iterator;

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
    int randomAttemps;

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

    itemSet_map_const_iterator cbegin() const;

    itemSet_map_const_iterator cend() const;

    size_t size() const;

    std::list<std::string> &getInputs();

    void setInputFileName(char *);

    void setLexiconFileName(char *);

    void setRulesFileName(char *);

    void setCompactedLexiconFileName(char *);

    void setCompactedDirectoryName(char *);

    std::string getInputFileName() const;

    std::string getLexiconFileName() const;

    std::string getCompactedLexiconFileName() const;

    std::string getCompactedDirectoryName() const;

    std::string getRulesFileName() const;

    void setMaxLength(unsigned int);

    void setMaxUsages(unsigned int);

    unsigned int getMaxUsages() const;

    void setMaxItems(unsigned int);

    unsigned int getMaxItems() const;

    void setCompactedLexicon(class CompactedLexicon *);

    void addInput(const std::string &);

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

    void eraseItemMap(unsigned int);

    class Item *getItemMap(unsigned int);

    bool getTrace() const;

    void setTrace(bool);

    void setReduceAll(bool);

    void setRandomResult(bool);

    bool getRandomResult(void) const;

    void setFirstResult(bool);

    bool getFirstResult(void) const;

    void printState(std::ostream &, class ItemSet *);

    void close(class Parser &, class ItemSet *, uint8_t);

    bool shift(class Parser &, class ItemSet *, uint8_t);

    void clear();

    static class Item *createItem(class Item *, uint8_t);

    void generate(class Parser &);

    entriesPtr findCompactedLexicon(class Parser &parser, uint16_t pos, uint16_t head);

    std::string keyMemoization(class Item *, class Item *);

    void setVerbose(bool _verbose);

    bool getVerbose();

    entriesPtr findByPos(Parser &parser, Parser::entries_map *, uint16_t pos);

    entriesPtr findByForm(Parser::entries_map *);

    entriesPtr findByHead(Parser &parser, Parser::entries_map *, uint16_t pos, uint16_t head);
};

#endif // ELVEX_GENERATOR_H
