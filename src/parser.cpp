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
#include <utility>
#include "parser.h"
#include "vartable.h"
#include "messages.h"

extern unsigned int rulesparse();

extern void init_buffer();

extern void delete_buffer();

extern void scan_string(std::string);

/* **************************************************
 *
 ************************************************** */
Parser::Parser() {
    this->startFeatures = featuresPtr();
    this->startTerm = nullptr;
    this->localFeatures = featuresPtr();
    this->verbose = false;
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Parser::~Parser() {
    DELETE;
}

/* **************************************************
 *
 ************************************************** */
class Grammar &
Parser::getGrammar() {
    return this->grammar;
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
termPtr Parser::getStartTerm() const {
    return startTerm;
}

/* **************************************************
 *
 ************************************************** */
void Parser::setStartTerm(termPtr _startTerm) {
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
Parser::entries_map_map &
Parser::getLexicon() {
    return lexicon;
}

/* **************************************************
 *
 ************************************************** */
void Parser::setLexicon(entries_map_map &_lexicon) {
    this->lexicon = _lexicon;
}

/* **************************************************
 *
 ************************************************** */
Parser::entry_map &Parser::getMapLocalEntry() {
    return mapLocalEntry;
}

/* **************************************************
 *
 ************************************************** */
Parser::entries_map_map::const_iterator Parser::findLexicon(unsigned int i) const {
    return lexicon.find(i);
}

/* **************************************************
 *
 ************************************************** */
Parser::entries_map_map::const_iterator Parser::beginLexicon() const {
    return lexicon.begin();
}

/* **************************************************
 *
 ************************************************** */
Parser::entries_map_map::const_iterator Parser::endLexicon() const {
    return lexicon.end();
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
void Parser::setLocalFeatures(featuresPtr localFeatures) {
    this->localFeatures = localFeatures;
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
void Parser::printLexicon(std::ostream &out) const {
    out << "<ul>";
    for (entries_map_map::const_iterator i = beginLexicon(); i != endLexicon(); ++i) {
        out << "<li>";
        out << Vartable::codeToIdentifier((*i).first);
        out << "<ul>";
        for (entries_map::iterator j = (*i).second->begin(); j != (*i).second->end(); ++j) {
            out << "<li>";
            if ((*j).first == 0)
                out << "0 = &gt; ";
            else if ((*j).first == UINT_MAX)
                out << "UINT_MAX = &gt; ";
            else
                out << Vartable::codeToIdentifier((*j).first) << " = &gt; ";

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
    std::unordered_map<std::string, featuresPtr>::const_iterator found;
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
unsigned int Parser::parseFile(std::string prefix, std::string fileName) {
    unsigned int result;
    result = parseString(prefix + "\n#include " + fileName);
    return result;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Parser::parseBuffer(std::string prefix, std::string buffer, std::string bufferName) {
    unsigned int result;
    pushBufferName(bufferName);
    result = parseString(prefix + "\n" + buffer);
    return result;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Parser::parseString(std::string buffer) {
    init_buffer();
    scan_string(buffer);
    unsigned int result = rulesparse();
    delete_buffer();
    return result;
}

void Parser::listMacros() {
    for (auto iterator : macros) {
        std::cerr << "\"" << iterator.first << "\"" << std::endl;
    }
}
