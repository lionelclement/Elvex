/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2020 LABRI, 
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

#ifndef ELVEX_SYNTHESIZER_H
#define ELVEX_SYNTHESIZER_H

#include <map>
#include <unordered_map>

#include "shared_ptr.hpp"
#include "forestmap.hpp"
#include "memoization-map.hpp"
#include "parser.hpp"

#ifndef MAXLENGTH
#define MAXLENGTH 1000
#endif

#ifndef MAXUSAGES
#define MAXUSAGES 1000
#endif

#ifndef MAXCARDINAL
#define MAXCARDINAL 1000
#endif

#ifndef MAXATTEMPTS
#define MAXATTEMPTS 3000
#endif

class Synthesizer {

public:

    enum Stage {
        MORPHO_FEATURES,
        FORM_FEATURES,
        PRED_FEATURES
    };

    typedef std::unordered_map<unsigned int, itemPtr> item_map;
    typedef std::unordered_map<unsigned int, itemSetPtr> itemSet_map;
    //typedef std::map<unsigned int, itemPtr> item_map;
    //typedef std::map<unsigned int, itemSetPtr> itemSet_map;
    typedef itemSet_map::const_iterator itemSet_map_const_iterator;

private:
    itemSet_map states;
    ForestMap forestMap;
    item_map itemMap;
    nodePtr nodeRoot;

    std::string compactedLexiconFileName;
    std::string compactedDirectoryName;
    class CompactedLexicon* compactedLexicon;

    unsigned int maxLength;
    unsigned int maxUsages;
    unsigned int maxCardinal;
    std::string lexiconFileName;
    std::string rulesFileName;
    std::string inputFileName;

    std::list<std::string> inputs;

    bool reduceAll;
    bool trace;
    bool verbose;
    bool warning;
    bool random;
    bool one;
    int attempsRandom;

    MemoizationMap memoizedMap;

    #ifdef TRACE_OPTION
    bool traceInit;
    bool traceStage;
    bool traceClose;
    bool traceShift;
    bool traceReduce;
    bool traceAction;
#endif

#ifdef OUTPUT_XML
    char* outXML;
#endif


public:

    Synthesizer();

    ~Synthesizer();

    itemSet_map_const_iterator cbegin() const;

    itemSet_map_const_iterator cend() const;

    size_t size() const;

    std::list<std::string>& getInputs();

    void setInputFileName(char*);

    void setLexiconFileName(char*);

    void setRulesFileName(char*);

    void setCompactedLexiconFileName(char *);

    void setCompactedDirectoryName(char*);

    std::string getInputFileName() const;

    std::string getLexiconFileName() const;

    std::string getCompactedLexiconFileName() const;

    std::string getCompactedDirectoryName() const;

    std::string getRulesFileName() const;

    void setMaxLength(unsigned int);

    void setMaxUsages(unsigned int);

    unsigned int getMaxUsages() const;

    void setMaxCardinal(unsigned int);

    unsigned int getMaxCardinal() const;

    void setCompactedLexicon(class CompactedLexicon*);

    void addInput(const std::string&);

#ifdef OUTPUT_XML
    void setOutXML(char*);
    char *getOutXML() const;
#endif

#ifdef TRACE_OPTION
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
#endif

    nodePtr getNodeRoot();

    bool insertItemMap(const itemPtr&);

    void eraseItemMap(unsigned int);

    itemPtr getItemMap(unsigned int);

    bool getTrace() const;

    void setTrace(bool);

    void setReduceAll(bool);

    void setRandom(bool);

    bool getRandom(void) const;

    void setOne(bool);

    bool getOne(void) const;

    void printState(std::ostream&, const itemSetPtr&);

    void close(class Parser&, const itemSetPtr&, unsigned int);

    bool shift(class Parser&, const itemSetPtr&, unsigned int);

    void clear();

    static itemPtr createItem(const itemPtr&, unsigned int);

    void generate(class Parser&);

    entriesPtr findCompactedLexicon(class Parser&, unsigned int code, const std::string& str, unsigned int pred);

    std::string keyMemoization(const itemPtr&, const itemPtr&);

    void setVerbose(bool _verbose);

    entriesPtr findByPos(Parser& parser, Parser::entries_map* pMap, unsigned int term);

    entriesPtr findByForm(Parser::entries_map* pMap);

    entriesPtr findByPred(Parser& parser, Parser::entries_map* listPred, unsigned int term, unsigned int pred);
};

#endif // ELVEX_SYNTHESIZER_H
