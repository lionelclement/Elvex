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

#ifndef ELVEX_PARSER_H
#define ELVEX_PARSER_H

#include <functional>
#include <string>
#include <map>
#include <unordered_map>
#include <deque>
#include "shared_ptr.hpp"
#include "rules.hpp"
#include "entry.hpp"
#include "entries.hpp"
#include "features.hpp"

class Parser {

public:
    typedef std::unordered_map<std::string, entryPtr> entry_map;
    // POS => (LEMMA => ENTRIES)
    // i.e.: verb => (manger => (mangions, mange|mange))
    typedef std::map<unsigned int, entriesPtr> entries_map;
    typedef std::map<unsigned int, entries_map *> entries_map_map;

    void listMacros();

private:
    Rules rules;
    entries_map_map lexicon;
    entry_map mapLocalEntry;
    std::unordered_map<std::string, featuresPtr> macros;
    featuresPtr startFeatures;
    unsigned int startTerm;
    bool verbose;
    featuresPtr localFeatures;
    std::deque<std::string> bufferNames;
    std::deque<unsigned int> linenos;

public:
    Parser();

    ~Parser();

    void pushBufferName(std::string);

    std::string popBufferName();

    void pushLineno(unsigned int);

    unsigned int popLineno();

    unsigned int getTopLineno();

    class Rules &getRules();

    std::string getTopBufferName();

    unsigned int getStartTerm() const;

    void setStartTerm(unsigned int);

    void setStartFeatures(featuresPtr);

    featuresPtr getStartFeatures() const;

    featuresPtr getLocalFeatures() const;

    void setLocalFeatures(featuresPtr);

    entries_map_map &getLexicon();

    void setLexicon(entries_map_map &);

    entries_map_map::const_iterator findLexicon(unsigned int i) const;

    entries_map_map::const_iterator beginLexicon() const;

    entries_map_map::const_iterator endLexicon() const;

    void setVerbose(bool);

    bool getVerbose() const;

    entry_map &getMapLocalEntry();

    void printLexicon(std::ostream &) const;

    void addMacros(std::string, featuresPtr);

    featuresPtr findMacros(const std::string&);

    void parseFile(std::string prefix, std::string fileName);

    void parseBuffer(std::string prefix, std::string buffer, std::string bufferName);

private:
    void parseString(std::string buffer);

};

#endif // ELVEX_PARSER_H
