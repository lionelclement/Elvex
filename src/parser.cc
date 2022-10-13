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

#include <climits>
#include <stack>
#include <string>
#include <iostream>
#include "parser.hpp"
#include "vartable.hpp"
#include "messages.hpp"

extern unsigned int rulesparse();

extern void init_buffer();

extern void delete_buffer();

extern void scan_string(std::string);

/* **************************************************
 *
 ************************************************** */
Parser::Parser() {
    this->startFeatures = featuresPtr();
    this->localFeatures = featuresPtr();
    this->verbose = false;
    NEW
}

/* **************************************************
 *
 ************************************************** */
Parser::~Parser() {
    DELETE
}

/* **************************************************
 *
 ************************************************** */
class Rules &
Parser::getRules() {
    return this->rules;
}

/* **************************************************
 *
 ************************************************** */
void Parser::setStartFeatures(featuresPtr f) {
    this->startFeatures = f;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Parser::getStartFeatures() const {
    return this->startFeatures;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Parser::getStartTerm() const {
    return startTerm;
}

/* **************************************************
 *
 ************************************************** */
void Parser::setStartTerm(unsigned int _startTerm) {
    this->startTerm = _startTerm;
}

/* **************************************************
 *
 ************************************************** */
void Parser::setVerbose(const bool _verbose) {
    this->verbose = _verbose;
}

/* **************************************************
 *
 ************************************************** */
bool Parser::getVerbose() const {
    return this->verbose;
}

/* **************************************************
 *
 ************************************************** */
Parser::entry_map_const_iterator Parser::findMapLocalEntry(std::string& key) const {
        return mapLocalEntry.find(key);
}

/* **************************************************
 *
 ************************************************** */
Parser::entry_map_const_iterator Parser::cendMapLocalEntry() const {
    return mapLocalEntry.cend();
}

/* **************************************************
 *
 ************************************************** */
void Parser::insertMapLocalEntry(std::pair<std::string, entryPtr> pair){
    mapLocalEntry.insert(pair);
}

/* **************************************************
 *
 ************************************************** */
Parser::entries_map_map_const_iterator Parser::findCacheLexicon(unsigned int i) const {
    return cacheLexicon.find(i);
}

/* **************************************************
 *
 ************************************************** */
Parser::entries_map_map_const_iterator Parser::cbeginCacheLexicon() const {
    return cacheLexicon.cbegin();
}

/* **************************************************
 *
 ************************************************** */
Parser::entries_map_map_const_iterator Parser::cendCacheLexicon() const {
    return cacheLexicon.cend();
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Parser::getLocalFeatures() const {
    return localFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Parser::setLocalFeatures(featuresPtr _localFeatures) {
    this->localFeatures = _localFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Parser::pushBufferName(std::string name) {
    bufferNames.push_front(name);
}

/* **************************************************
 *
 ************************************************** */
std::string Parser::popBufferName() {
    std::string str = bufferNames.front();
    this->bufferNames.pop_front();
    return str;
}

/* **************************************************
 *
 ************************************************** */
std::string Parser::getTopBufferName() {
    return bufferNames.front();
}

/* **************************************************
 *
 ************************************************** */
void Parser::pushLineno(unsigned int i) {
    linenos.push_front(i);
}

/* **************************************************
 *
 ************************************************** */
unsigned int Parser::popLineno() {
    unsigned int i = linenos.front();
    linenos.pop_front();
    return i;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Parser::getTopLineno() {
    return linenos.front();
}

/* **************************************************
 *
 ************************************************** */
void Parser::printCacheLexicon(std::ostream &out) const {
    out << "<ul>";
    for (entries_map_map_const_iterator i = cbeginCacheLexicon(); i != cendCacheLexicon(); ++i) {
        out << "<li>";
        out << Vartable::codeToString((*i).first);
        out << "<ul>";
        for (entries_map::iterator j = (*i).second->begin(); j != (*i).second->end(); ++j) {
            out << "<li>";
            if ((*j).first == 0)
                out << "0 = &gt; ";
            else if ((*j).first == UINT_MAX)
                out << "UINT_MAX = &gt; ";
            else
                out << Vartable::codeToString((*j).first) << " = &gt; ";

            (*j).second->print(out);
            out << "</li>";

        }
        out << "</ul>";
        out << "</il>";

    }
    out << "</ul>";
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Parser::addMacros(std::string key, featuresPtr features) {
    macros.insert(std::pair<std::string, featuresPtr>(key, features));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
featuresPtr Parser::findMacros(const std::string& str) {
    //std::cerr << "find @" << str << ":";
    macro_map_const_iterator found;
    found = macros.find(str);
    if (found == macros.end()) {
        return featuresPtr();
    } else {
        return found->second;
    }
}

/* **************************************************
 *
 ************************************************** */
void Parser::parseFile(std::string prefix, std::string fileName) {
    parseString(prefix + "\n#include " + fileName);
}

/* **************************************************
 *
 ************************************************** */
void Parser::parseBuffer(std::string prefix, std::string buffer, std::string bufferName) {
    pushBufferName(bufferName);
    parseString(prefix + "\n" + buffer);
}

/* **************************************************
 *
 ************************************************** */
void Parser::parseString(std::string buffer) {
    init_buffer();
    scan_string(buffer);
    rulesparse();
    delete_buffer();
}

/* **************************************************
 *
 ************************************************** */
void Parser::listMacros() {
    for (auto iterator : macros) {
        std::cerr << "\"" << iterator.first << "\"" << std::endl;
    }
}

/* **************************************************
 *
 ************************************************** */
void Parser::insertCacheLexicon(std::pair<unsigned int, entries_map*> pair){
  cacheLexicon.insert(pair);
}

/* **************************************************
 *
 ************************************************** */
/*
void Parser::printCacheLexicon(){
  for (auto i = cacheLexicon.begin(); i != cacheLexicon.end(); ++i){
    std::cerr << Vartable::codeToIdentifier((*i).first) << "=>\n";
    entries_map* v = (*i).second;
      for (auto j = v->begin(); j != v->end(); ++j){
        std::cerr << "\t" << Vartable::codeToIdentifier((*j).first) << "=>";
        entriesPtr cddr = (*j).second;
        cddr->print(std::cerr);
        std::cerr << std::endl;
    }
    std::cerr << std::endl;
  }
  CERR_LINE;
}
*/
