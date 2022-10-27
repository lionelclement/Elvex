/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI, 
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
#include <utility>
#include "item.hpp"
#include "environment.hpp"
#include "messages.hpp"
#include "forest.hpp"
#include "forestidentifier.hpp"
#include "itemset.hpp"
#include "shared_ptr.hpp"
#include "listfeatures.hpp"
#include "rule.hpp"
#include "statement.hpp"
#include "statements.hpp"
#include "synthesizer.hpp"
#include "terms.hpp"
#include "vartable.hpp"

/* **************************************************
 *
 ************************************************** */
Item::Item(const rulePtr& rule, statementsPtr statements) {
    this->rule = std::move(rule);
    this->index = UINT_MAX;
    this->statements = std::move(statements);
    this->environment = environmentPtr();
    this->inheritedFeatures = Features::NIL;
    this->synthesizedFeatures = Features::NIL;
    this->synthesizedSonFeatures = ListFeatures::create();
    this->inheritedSonFeatures = ListFeatures::create();
    for (std::vector<termsPtr>::const_iterator term = this->rule->getRhs().cbegin(); 
            term != this->rule->getRhs().cend(); 
            ++term) {
        this->indexTerms.push_back(0);
        this->seen.push_back(false);
        this->forestIdentifiers.push_back(forestIdentifierPtr());
        this->synthesizedSonFeatures->push_back(Features::NIL);
        this->inheritedSonFeatures->push_back(Features::NIL);
     }
    NEW
}

/* **************************************************
 *
 ************************************************** */
Item::~Item() {
    DELETE
    refs.clear();
    seen.clear();
    ranges.clear();
    if (inheritedFeatures)
        inheritedFeatures.reset();
    if (inheritedSonFeatures)
        inheritedSonFeatures.reset();
    if (synthesizedFeatures)
        synthesizedFeatures.reset();
    if (synthesizedSonFeatures)
        synthesizedSonFeatures.reset();
    for (auto it : forestIdentifiers) {
        forestIdentifierPtr tmp = it;
        if (tmp)
            (tmp).reset();
    }
    forestIdentifiers.clear();
    if (statements)
        statements.reset();
    if (environment)
        environment.reset();
}

/* **************************************************
 *
 ************************************************** */
itemPtr Item::create(const rulePtr& rule, statementsPtr statements) {
    return itemPtr(new Item(rule, std::move(statements)));
}

/* **************************************************
 *
 ************************************************** */
rulePtr Item::getRule() const {
    return rule;
}

/* **************************************************
 *
 ************************************************** */
void Item::setRule(rulePtr _rule) {
    this->rule = _rule;
}

/* **************************************************
 *
 ************************************************** */
bool Item::getRuleTrace() const {
    return rule->getTrace();
}

/* **************************************************
 *
 ************************************************** */
unsigned int Item::getRuleLineno() const {
    return rule->getLineno();
}

/* **************************************************
 *
 ************************************************** */
void Item::rulePrint(std::ostream &os, unsigned int index, bool withSemantic, bool html) const {
    rule->print(os, index, withSemantic, html);
}

/* **************************************************
 *
 ************************************************** */
unsigned int Item::getRuleId() const {
    return rule->getId();
}

/* **************************************************
 *
 ************************************************** */
void Item::ruleResetUsages(void) {
    rule->resetUsages();
}
    
/* **************************************************
 *
 ************************************************** */
const std::string& Item::getRuleFilename() const {
    return rule->getFilename();
}

/* **************************************************
 *
 ************************************************** */
unsigned int Item::getIndex() const {
    return index;
}

/* **************************************************
 *
 ************************************************** */
std::vector<unsigned int>& Item::getIndexTerms() {
    return indexTerms;
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Item::getStatements() const {
    return statements;
}

/* **************************************************
 *
 ************************************************** */
size_t Item::sizeRuleRhs() const noexcept {
    return rule->getRhs().size();
}

/* **************************************************
 *
 ************************************************** */
termsPtr Item::getTerms(unsigned int index) const {
    return rule->getRhs()[index];
}

/* **************************************************
 *
 ************************************************** */
termsPtr Item::currentTerms() const {
    if ((this->index == UINT_MAX) || (this->index >= this->getRule()->getRhs().size())) {
        return nullptr;
    }
    return rule->getRhs()[this->index];
}

 /* **************************************************
  *
  ************************************************** */
 void Item::setCurrentTerms(termsPtr terms) {
    this->rule->getRhs()[this->index] = std::move(terms);
 }

 /* **************************************************
  *
  ************************************************** */
void Item::putIndexTerms(unsigned int index, unsigned int indexTerm){
    indexTerms[index] = indexTerm;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Item::currentTerm() {
    termsPtr terms = currentTerms();
    if ((terms == nullptr)){
        this->print(std::cout);
        FATAL_ERROR_UNEXPECTED;
    }
    if ((terms->size() != 1)){
        this->print(std::cout);
        FATAL_ERROR_UNEXPECTED;
    }
    return (*terms)[0];
}

/* **************************************************
 *
 ************************************************** */
unsigned int Item::getRuleLhs() const {
    return rule->getLhs();
}

/* **************************************************
 *
 ************************************************** */
std::vector<termsPtr>& Item::getRuleRhs() {
    return rule->getRhs();
}

/* **************************************************
 *
 ************************************************** */
Item::set_of_unsigned_int& Item::getRefs() {
    return refs;
}

/* **************************************************
 *
 ************************************************** */
bool Item::emptyRefs() const noexcept{
    return refs.empty();
}

/* **************************************************
 *
 ************************************************** */
void Item::setRefs(set_of_unsigned_int _refs)  {
    this->refs = _refs;
}

/* **************************************************
 *
 ************************************************** */
void Item::addRef(unsigned int ref) {
    this->refs.insert(ref);
}

/* **************************************************
 *
 ************************************************** */
std::vector<bool>& Item::getSeen() {
    return this->seen;
}

/* **************************************************
 *
 ************************************************** */
void Item::setSeen(std::vector<bool>& _seen) {
    this->seen = _seen;
}

/* **************************************************
 *
 ************************************************** */
bool Item::isSeen(unsigned int _index) const {
    return seen[_index];
}

/* **************************************************
 *
 ************************************************** */
void Item::setSeen(unsigned int _index, bool b) {
    this->seen[_index] = b;
}

/* **************************************************
 *
 ************************************************** */
std::vector<unsigned int>& Item::getRanges() {
    return ranges;
}

/* **************************************************
 *
 ************************************************** */
void Item::addRanges(unsigned int k) {
    ranges.push_back(k);
}

/* **************************************************
 *
 ************************************************** */
void Item::setRanges(std::vector<unsigned int>& ranges) {
    this->ranges = ranges;
}

/* **************************************************
 *
 ************************************************** */
std::vector<forestIdentifierPtr>& Item::getForestIdentifiers() {
    return forestIdentifiers;
}

/* **************************************************
 *
 ************************************************** */
void Item::addForestIdentifiers(unsigned int key, forestIdentifierPtr forestIdentifier) {
    forestIdentifiers[key] = std::move(forestIdentifier);
}

/* **************************************************
 *
 ************************************************** */
void Item::setForestIdentifiers(std::vector<forestIdentifierPtr>& forestIdentifiers) {
    this->forestIdentifiers = forestIdentifiers;
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr Item::getSynthesizedSonFeatures() {
    return synthesizedSonFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setSynthesizedSonFeatures(listFeaturesPtr _synthesizedSonFeatures) {
    this->synthesizedSonFeatures = std::move(_synthesizedSonFeatures);
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr Item::getInheritedSonFeatures() {
    return inheritedSonFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setInheritedSonFeatures(listFeaturesPtr _inheritedSonFeatures) {
    this->inheritedSonFeatures = std::move(_inheritedSonFeatures);
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Item::getSynthesizedFeatures() {
    return synthesizedFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setSynthesizedFeatures(featuresPtr _synthesizedFeatures) {
    this->synthesizedFeatures = std::move(_synthesizedFeatures);
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Item::getInheritedFeatures() const {
    return inheritedFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setInheritedFeatures(featuresPtr _inheritedFeatures) {
    this->inheritedFeatures = std::move(_inheritedFeatures);
}

/* **************************************************
 *
 ************************************************** */
environmentPtr Item::getEnvironment() const {
    return this->environment;
}

/* **************************************************
 *
 ************************************************** */
void Item::setEnvironment(environmentPtr _environment) {
    this->environment = std::move(_environment);
}

/* **************************************************
 *
 ************************************************** */
bool Item::isStarted() const noexcept {
    return ranges.size() == 1;
}

/* **************************************************
 *
 ************************************************** */
bool Item::isCompleted() const noexcept {
    return ranges.size() == (getRule()->getRhs().size() + 1);
}

/* **************************************************
 *
 ************************************************** */
void Item::setStatements(const statementsPtr& statements) {
    this->statements = statements;
}

/* **************************************************
 *
 ************************************************** */
void Item::addEnvironment(environmentPtr _environment) {
    if (!this->environment)
        this->environment = Environment::create();
    this->environment->add(std::move(_environment));
}

/* **************************************************
 *
 ************************************************** */
void Item::defaultInheritedSonFeatures() {
    std::vector<termsPtr> terms = this->getRule()->getRhs();
    std::vector<bool> assignedInheritedSonFeatures;
    for (std::vector<termsPtr>::const_iterator it = terms.begin(); it != terms.end(); ++it)
        assignedInheritedSonFeatures.push_back(false);
    if (statements)
        for (const auto&  statement : *this->statements)
            statement->lookingForAssignedInheritedSonFeatures(assignedInheritedSonFeatures);
    unsigned int j = 0;
    for (std::vector<bool>::const_iterator it = assignedInheritedSonFeatures.begin();
         it != assignedInheritedSonFeatures.end(); ++it, ++j)
        if (!(*it))
            (*inheritedSonFeatures).add(j, Features::create());
}

/* **************************************************
 *
 ************************************************** */
void Item::print(std::ostream& out) {
    out << "<table border=\"1\" style=\"color:black; ";
    if (isSetFlags(Flags::BOTTOM)) {
        out << " background-color:Pink;";
    } else if (isSetFlags(Flags::SEEN))
        out << " background-color:PaleTurquoise;";
    out << "\">";
    out << "<tr>";
    if (s_id){
        out << "<th>ID</th>";
        out << "<th>INFO</th>";
    }
    if (s_ruleId)
        out << "<th>RuleId</th>";
    if (s_rule)
        out << "<th>Rule</th>";
    if (s_flags)
        out << "<th>Flags</th>";
    if (s_refs)
        out << "<th>Refs</th>";
    if (s_seen)
        out << "<th>Seen</th>";
    if (s_item)
        out << "<th>Item</th>";
    if (s_index)
        out << "<th>Index</th>";
    if (s_indexTerms)
        out << "<th>IndexTerms</th>";
    if (s_currentTerm)
        out << "<th>Current term</th>";
    if (s_ranges)
        out << "<th>Ranges</th>";
    if (s_forestIdentifiers)
        out << "<th>ForestIdentifiers</th>";
    if (s_inheritedFeatures)
        out << "<th bgcolor=\"lightyellow\"><center>↑</center></th>";
    if (s_inheritedSonFeatures)
        out << "<th bgcolor=\"lightyellow\"><center>↓i</center></th>";
    if (s_synthesizedFeatures)
        out << "<th bgcolor=\"lightcyan\"><center>⇑</center></th>";
    if (s_synthesizedSonFeatures)
        out << "<th bgcolor=\"lightcyan\"><center>⇓i</center></th>";
    if (s_statements)
        out << "<th bgcolor=\"white\"><center>Statements</center></th>";
    if (s_environment && environment)
        out << "<th align = center>Environment</th>";
    out << "<tr>";
    if (s_id) {
        out << "<td>";
        out << '#' << this->getId();
        out << "</td>";
        out << "<td>";
        out << '#' << this->peekSerialString();
        out << "</td>";
    }
    if (s_ruleId) {
        out << "<td>";
        out << this->getRuleId();
        out << "</td>";
    }
    if (s_rule) {
        out << "<td>";
        this->rulePrint(out);
        out << "</td>";
    }
    if (s_flags) {
        out << "<td>";
        Flags::printFlags(out);
        out << "</td>";

    }
    if (s_refs) {
        out << "<td>(";
        auto ref = refs.begin();
        while (ref != refs.end()) {
            out << '#' << *ref;
            if (++ref != refs.end())
                out << ' ';
        }
        out << ")</td>";
    }
    if (s_seen) {
        out << "<td>(";
        auto s = seen.begin();
        while (s != seen.end()) {
            out << *s;
            if (++s != seen.end())
                out << ' ';
        }
        out << ")</td>";
    }
    if (s_item) {
        out << "<td>";
        rule->print(out, index, false);
        out << "</td>";
    }
    if (s_index) {
        out << "<td>";
        if (index == UINT_MAX)
            out << "NONE";
        else
            out << index;
        out << "</td>";
    }
    if (s_indexTerms) {
        out << "<td>";
        for (unsigned int indexTerm : indexTerms)
            if (indexTerm == UINT_MAX)
                out << "UINT_MAX" << "&nbsp;";
            else
                out << indexTerm << "&nbsp;";
        out << "</td>";
    }
    if (s_currentTerm) {
        out << "<td>";
        if (index == UINT_MAX || indexTerms[index] == UINT_MAX)
            out << "NONE";
        else {
            out << Vartable::codeToString(currentTerm());
        }
        out << "</td>";
    }
    if (s_ranges) {
        out << "<td>"; //<center>Ranges</center><br>";
        unsigned int previous = UINT_MAX;
        bool first = true;
        for (unsigned int range : ranges) {
            if (first) {
                first = false;
            }
            else {
                    out << "&nbsp;[" << previous << '-' << range << ']';
            }
            previous = range;
        }
        out << "</td>";
    }
    if (s_forestIdentifiers) {
        out << "<td>"; //<center>ForestIdentifiers</center><br>";
        for (auto i = forestIdentifiers.begin();
             i != forestIdentifiers.end();) {
            if (*i)
                out << (*i)->peekSerialString();
            else
                out << "NULL";
            if (++i != forestIdentifiers.end()) {
                out << ", ";
            }
        }
        out << "</td>";
    }
    if (s_inheritedFeatures) {
        out << "<td bgcolor=\"lightyellow\">"; //<center>↑</center><br>";
        //out << inheritedFeatures->hashCode() << "<BR>" <<std::endl;
        //out << inheritedFeatures->peekSerialString() << "<BR>" << std::endl;
        inheritedFeatures->print(out);
        out << "</td>";
    }
    if (s_inheritedSonFeatures) {
        out << "<td bgcolor=\"lightyellow\"><table>"; //<center>↓i</center><br>";
        int k = 1;
	for (const auto&  i : *inheritedSonFeatures) {
	  out << "<tr><td>" << k++ << "</td><td>";
            if (i)
                i->print(out);
            out << "</td></tr>";
        }
        out << "</table></td>";
    }
    if (s_synthesizedFeatures) {
        out << "<td bgcolor=\"lightcyan\">"; //<center>⇑</center><br>";
        if (synthesizedFeatures) {
            synthesizedFeatures->print(out);
        }
        out << "</td>";
    }
    if (s_synthesizedSonFeatures) {
        out << "<td bgcolor=\"lightcyan\"><table>"; //<center>⇓i</center><br>";
        int k = 1;
	for (const auto&  i : *synthesizedSonFeatures) {
	  out << "<tr><td>" << k++ << "</td><td>";
            if (i)
                i->print(out);
            out << "</td></tr>";
        }
        out << "</table></td>";
    }
    if (s_statements) {
        out << "<td bgcolor=\"white\">";
        if (statements)
            statements->print(out);
        else
            out << "&nbsp;";
        out << "</td>";
    }
    if (s_environment && environment) {
        out << "<td align=\"center\">";
        if (environment)
            environment->print(out);
        else
            out << "&nbsp;";
        out << "</td>";
    }
    out << "</tr></table>";
    out << std::endl;
}

/* **************************************************
 *
 ************************************************** */
itemPtr Item::clone(const std::bitset<FLAGS>& protectedFlags) {
    itemPtr it = Item::create(this->rule,
                               this->statements ? this->statements->clone(protectedFlags) : statementsPtr());
    it->index = this->index;
    it->indexTerms = this->indexTerms;
    it->environment = (this->environment) ? this->environment->clone() : environmentPtr();
    it->ranges = this->ranges;
    it->forestIdentifiers = this->forestIdentifiers;
    it->refs = this->refs;
    it->seen = this->seen;
    it->inheritedFeatures = this->inheritedFeatures->clone();
    it->inheritedSonFeatures = this->inheritedSonFeatures->clone();
    it->synthesizedSonFeatures = this->synthesizedSonFeatures->clone();
    it->synthesizedFeatures = this->synthesizedFeatures->clone();
    return it;
}

/* **************************************************
 *
 ************************************************** */
void Item::setIndex(unsigned int index) {
    this->index = index;
    termsPtr terms = currentTerms();
    if (!terms || terms->isOptional() || (terms->size() > 1)) {
        this->indexTerms[index] = UINT_MAX;
    }
    else {
        this->indexTerms[index] = 0;
    }
}

/* **************************************************
 *
 ************************************************** */
void Item::next(bool& modification) {
#ifdef TRACE_NEXT
    std::cout << "<H3>####################### NEXT #######################</H3>" << std::endl;
    this->print(std::cout);
    std::cout << std::endl;
#endif
    for (unsigned int i = 0; i < this->getRule()->getRhs().size(); ++i) {
        if ((*this->inheritedSonFeatures)[i]->isNil() 
            && !this->getTerms(i)->isOptional() 
            && this->getTerms(i)->size() == 1) {
            continue;
        }
        if (!this->forestIdentifiers[i]) {
            setIndex(i);
            modification = true;
            break;
        }
    }
    if (!modification && (index == UINT_MAX) && isCompleted()) {
        this->index = this->getRule()->getRhs().size();
        modification = true;
    }
    if (this->index != UINT_MAX){
        this->setSeen(this->index, true);
    }
    
#ifdef TRACE_NEXT
    std::cout << "<H3>####################### NEXT DONE #######################</H3>" << std::endl;
    this->print(std::cout);
    std::cout << std::endl;
#endif
}


/* **************************************************
 *
 ************************************************** */
void Item::apply(Parser& parser, Synthesizer* synthesizer) {
    if (statements) {
        bool effect = true;
        if (isUnsetFlags(Flags::BOTTOM)
            && statements->isUnsetFlags(Flags::SEEN)) {

#ifdef TRACE_OPTION
            if (synthesizer->getTraceAction()) {
          std::cout << "<H3>####################### ACTION #######################</H3>" << std::endl;
          print(std::cout);
          std::cout << std::endl;
            }
#endif
            effect = false;
            statements->apply(shared_from_this(), parser, synthesizer, effect);
#ifdef TRACE_OPTION
            if (synthesizer->getTraceAction()) {
          std::cout << "<H3>####################### ACTION DONE #######################</H3>" << std::endl;
          print(std::cout);
          std::cout << std::endl;
            }
#endif
        }
    }
}

/* **************************************************
 *
 ************************************************** */
void Item::makeSerialString() {
    
    serialString = std::to_string(rule->getId());

    serialString += '/';
    if (index == UINT_MAX)
        serialString += '.';
    else {
        serialString += std::to_string(index);
        if (rule->getTerms(index)->isOptional())
            serialString += '?';
        if (rule->getTerms(index)->size() > 1){
            serialString += '#';
            serialString += std::to_string(rule->getTerms(index)->size());
        }
    }
   
    serialString += '/';
    for (std::vector<unsigned int>::const_iterator i = indexTerms.cbegin();
        i != indexTerms.cend();
        ++i)
        serialString += std::to_string(*i) + '-';

    serialString += '/';
    for (auto ref = refs.cbegin(); ref != refs.cend() ; ++ref)
        serialString += std::to_string(*ref) + '-';

    serialString += '/';
    for (auto fi = forestIdentifiers.cbegin(); fi != forestIdentifiers.cend(); ++fi){
        if (*fi)
            serialString += (*fi)->peekSerialString();
        else
            serialString += '.';
        serialString += '-';
    }
    serialString += '/';
    serialString += inheritedFeatures->peekSerialString();
}

/* **************************************************
 *
 ************************************************** */
size_t Item::hash::operator()(itemPtr const& item) const {
    // defined in serialisable.hpp : std::hash<std::string>{}(serialString)
    return item->hashCode();
}

/* **************************************************
 *
 ************************************************** */
bool Item::equal_to::operator()(itemPtr const& i1, itemPtr const& i2) const {
    return i1->peekSerialString() == i2->peekSerialString();
}

/* **************************************************
 *
 ************************************************** */
void Item::renameVariables(size_t k) {
    this->statements->renameVariables(k);
}

