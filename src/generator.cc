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
#include "generator.hpp"
#include "vartable.hpp"
#include "messages.hpp"

extern unsigned int rulesparse();

extern void init_buffer();

extern void delete_buffer();

extern void scan_string(std::string);

/* **************************************************
 *
 ************************************************** */
Generator::Generator() {
    this->startFeatures = featuresPtr();
    this->localFeatures = featuresPtr();
    this->verbose = false;
    NEW
}

/* **************************************************
 *
 ************************************************** */
Generator::~Generator() {
    DELETE
}

/* **************************************************
 *
 ************************************************** */
class Rules &
Generator::getRules() {
    return this->rules;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setStartFeatures(featuresPtr f) {
    this->startFeatures = f;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Generator::getStartFeatures() const {
    return this->startFeatures;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Generator::getStartTerm() const {
    return startTerm;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setStartTerm(unsigned int _startTerm) {
    this->startTerm = _startTerm;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setVerbose(const bool _verbose) {
    this->verbose = _verbose;
}

/* **************************************************
 *
 ************************************************** */
bool Generator::getVerbose() const {
    return this->verbose;
}

/* **************************************************
 *
 ************************************************** */
Generator::entries_map_map &
Generator::getLexicon() {
    return lexicon;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setLexicon(entries_map_map &_lexicon) {
    this->lexicon = _lexicon;
}

/* **************************************************
 *
 ************************************************** */
Generator::entry_map &Generator::getMapLocalEntry() {
    return mapLocalEntry;
}

/* **************************************************
 *
 ************************************************** */
Generator::entries_map_map::const_iterator Generator::findLexicon(unsigned int i) const {
    return lexicon.find(i);
}

/* **************************************************
 *
 ************************************************** */
Generator::entries_map_map::const_iterator Generator::beginLexicon() const {
    return lexicon.begin();
}

/* **************************************************
 *
 ************************************************** */
Generator::entries_map_map::const_iterator Generator::endLexicon() const {
    return lexicon.end();
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Generator::getLocalFeatures() const {
    return localFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Generator::setLocalFeatures(featuresPtr _localFeatures) {
    this->localFeatures = _localFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Generator::pushBufferName(std::string name) {
    bufferNames.push_front(name);
}

/* **************************************************
 *
 ************************************************** */
std::string Generator::popBufferName() {
    std::string str = bufferNames.front();
    this->bufferNames.pop_front();
    return str;
}

/* **************************************************
 *
 ************************************************** */
std::string Generator::getTopBufferName() {
    return bufferNames.front();
}

/* **************************************************
 *
 ************************************************** */
void Generator::pushLineno(unsigned int i) {
    linenos.push_front(i);
}

/* **************************************************
 *
 ************************************************** */
unsigned int Generator::popLineno() {
    unsigned int i = linenos.front();
    linenos.pop_front();
    return i;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Generator::getTopLineno() {
    return linenos.front();
}

/* **************************************************
 *
 ************************************************** */
void Generator::printLexicon(std::ostream &out) const {
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
void Generator::addMacros(std::string key, featuresPtr features) {
    macros.insert(std::pair<std::string, featuresPtr>(key, features));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
featuresPtr Generator::findMacros(const std::string& str) {
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
unsigned int Generator::parseFile(std::string prefix, std::string fileName) {
    unsigned int result;
    result = parseString(prefix + "\n#include " + fileName);
    return result;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Generator::parseBuffer(std::string prefix, std::string buffer, std::string bufferName) {
    unsigned int result;
    pushBufferName(bufferName);
    result = parseString(prefix + "\n" + buffer);
    return result;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Generator::parseString(std::string buffer) {
    init_buffer();
    scan_string(buffer);
    unsigned int result = rulesparse();
    delete_buffer();
    return result;
}

void Generator::listMacros() {
    for (auto iterator : macros) {
        std::cerr << "\"" << iterator.first << "\"" << std::endl;
    }
}
