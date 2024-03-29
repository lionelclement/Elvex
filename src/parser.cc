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
uint32_t Parser::getStartTerm() const {
    return startTerm;
}

/* **************************************************
 *
 ************************************************** */
void Parser::setStartTerm(uint32_t _startTerm) {
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
Parser::entry_map::const_iterator Parser::findMapLocalEntry(std::string& key) const {
        return mapLocalEntry.find(key);
}

/* **************************************************
 *
 ************************************************** */
Parser::entry_map::const_iterator Parser::cendMapLocalEntry() const {
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
Parser::entries_map_map::const_iterator Parser::findCacheLexicon(uint32_t key) const {
    return cacheLexicon.find(key);
}

/* **************************************************
 *
 ************************************************** */
Parser::entries_map_map::const_iterator Parser::cbeginCacheLexicon() const {
    return cacheLexicon.cbegin();
}

/* **************************************************
 *
 ************************************************** */
Parser::entries_map_map::const_iterator Parser::cendCacheLexicon() const {
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
void Parser::pushLineno(uint32_t i) {
    linenos.push_front(i);
}

/* **************************************************
 *
 ************************************************** */
uint32_t Parser::popLineno() {
    uint32_t i = linenos.front();
    linenos.pop_front();
    return i;
}

/* **************************************************
 *
 ************************************************** */
uint32_t Parser::getTopLineno() {
    return linenos.front();
}

/* **************************************************
 *
 ************************************************** */
void Parser::printCacheLexicon(std::ostream &out) const {
    out << "<ul>";
    for (entries_map_map::const_iterator i = cbeginCacheLexicon(); i != cendCacheLexicon(); ++i) {
        out << "<li>";
        out << Vartable::codeToName((*i).first);
        out << "<ul>";
        for (entries_map::iterator j = (*i).second->begin(); j != (*i).second->end(); ++j) {
            out << "<li>";
            out << Vartable::codeToName((*j).first) << " -&gt; ";
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
    macro_map::const_iterator found;
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
void Parser::parseFile(std::string prefix, std::string suffix, std::string fileName) {
    pushBufferName(fileName);
    parseString(prefix + "\n#include " + fileName + "\n" + suffix);
}

/* **************************************************
 *
 ************************************************** */
void Parser::parseBuffer(std::string prefix, std::string suffix, std::string buffer, std::string bufferName) {
    pushBufferName(bufferName);
    parseString(prefix + "\n" + buffer + "\n" + suffix);
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
void Parser::printMacros() {
    for (auto iterator : macros) {
        std::cout << '@' << iterator.first << " => ";
        iterator.second->flatPrint(std::cout);
        std::cout << std::endl;
    }
}

/* **************************************************
 *
 ************************************************** */
void Parser::insertCacheLexicon(std::pair<uint32_t, entries_map*> pair){
  cacheLexicon.insert(pair);
}
