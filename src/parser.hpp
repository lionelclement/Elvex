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

#ifndef ELVEX_PARSER_H
#define ELVEX_PARSER_H

#include <unordered_map>
#include <deque>
#include "shared_ptr.hpp"
#include "rules.hpp"
#include "entry.hpp"
#include "entries.hpp"
#include "features.hpp"

class Parser
{

public:
  typedef std::unordered_map<std::string, entryPtr> entry_map;

  typedef std::unordered_map<uint32_t, entriesPtr> entries_map;

  // POS => (LEMMA => ENTRY)
  // i.e.: verb => (MANGER => (mangions[…], mange|mange[…]))
  typedef std::unordered_map<uint32_t, entries_map *> entries_map_map;

  // macro => featuresPtr
  typedef std::unordered_map<std::string, featuresPtr> macro_map;

private:
  Rules rules;
  entries_map_map cacheLexicon;
  entry_map mapLocalEntry;
  macro_map macros;
  featuresPtr startFeatures;
  uint32_t startTerm;
  bool verbose;
  featuresPtr localFeatures;
  std::deque<std::string> bufferNames;
  std::deque<uint32_t> linenos;

public:
  Parser();

  ~Parser();

  void pushBufferName(std::string);

  std::string popBufferName();

  void pushLineno(uint32_t);

  uint32_t popLineno();

  uint32_t getTopLineno();

  class Rules &getRules();

  std::string getTopBufferName();

  uint32_t getStartTerm() const;

  void setStartTerm(uint32_t);

  void setStartFeatures(featuresPtr);

  featuresPtr getStartFeatures() const;

  featuresPtr getLocalFeatures() const;

  void setLocalFeatures(featuresPtr);

  void insertCacheLexicon(std::pair<uint32_t, entries_map *>);

  entries_map_map::const_iterator findCacheLexicon(uint32_t) const;

  entries_map_map::const_iterator cbeginCacheLexicon() const;

  entries_map_map::const_iterator cendCacheLexicon() const;

  void printCacheLexicon(std::ostream &) const;

  void setVerbose(bool);

  bool getVerbose() const;

  entry_map::const_iterator findMapLocalEntry(std::string &) const;

  entry_map::const_iterator cendMapLocalEntry() const;

  void insertMapLocalEntry(std::pair<std::string, entryPtr>);

  void addMacros(std::string, featuresPtr);

  featuresPtr findMacros(const std::string &);

  void parseFile(std::string prefix, std::string suffix, std::string fileName);

  void parseBuffer(std::string prefix, std::string suffix, std::string buffer, std::string bufferName);

  void printMacros();

private:
  void parseString(std::string buffer);
};

#endif // ELVEX_PARSER_H
