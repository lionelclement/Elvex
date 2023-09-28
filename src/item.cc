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
#include "generator.hpp"
#include "terms.hpp"
#include "serializable.hpp"

uint8_t Item::NA = UCHAR_MAX;

/* **************************************************
 *
 ************************************************** */
Item::Item(rulePtr rule, uint8_t index, statementsPtr statements)
{
    NEW;
    this->rule = std::move(rule);
    this->index = index;
    this->statements = std::move(statements);
    this->environment = environmentPtr();
    this->inheritedFeatures = Features::NIL;
    this->synthesizedFeatures = Features::NIL;
    this->synthesizedSonFeatures = ListFeatures::create();
    this->inheritedSonFeatures = ListFeatures::create();
}

/* **************************************************
 *
 ************************************************** */
Item::Item(const rulePtr &rule, uint8_t index, uint8_t indexTerm, statementsPtr statements)
    : Item(rule, index, std::move(statements))
{
    std::vector<termsPtr> terms = rule->getRhs();
    unsigned j = 0;
    for (std::vector<termsPtr>::const_iterator i = terms.begin(); i != terms.end(); ++i, ++j)
    {
        this->indexTerms.push_back(NA);
        this->seen.push_back(false);
        this->forestIdentifiers.push_back(nullptr);
        this->synthesizedSonFeatures->push_back(Features::NIL);
        this->inheritedSonFeatures->push_back(Features::NIL);
    }
    if ((terms.size() < index) && (index != NA))
        this->indexTerms[index] = indexTerm;
}

/* **************************************************
 *
 ************************************************** */
Item::Item(const rulePtr &rule, uint8_t index, std::vector<uint8_t> &indexTerms, statementsPtr statements)
    : Item(rule, index, std::move(statements))
{
    this->indexTerms = indexTerms;
    std::vector<termsPtr> terms = rule->getRhs();
    unsigned j = 0;
    for (std::vector<termsPtr>::const_iterator i = terms.begin(); i != terms.end(); ++i, ++j)
    {
        // this->indexTerms.push_back(UINT_MAX);
        this->seen.push_back(false);
        this->forestIdentifiers.push_back(nullptr);
        this->synthesizedSonFeatures->push_back(Features::NIL);
        this->inheritedSonFeatures->push_back(Features::NIL);
    }
}

/* **************************************************
 *
 ************************************************** */
Item::~Item()
{
    DELETE;
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
    for (auto it : forestIdentifiers)
    {
        class ForestIdentifier *tmp = it;
        if (tmp)
            free(tmp);
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
class Item *Item::create(const rulePtr &rule, uint8_t index, uint8_t indexTerm, statementsPtr statements)
{
    return new Item(rule, index, indexTerm, std::move(statements));
}

/* **************************************************
 *
 ************************************************** */
class Item *
Item::create(const rulePtr &rule, uint8_t index, std::vector<uint8_t> &indexTerms, statementsPtr statements)
{
    return new Item(rule, index, indexTerms, std::move(statements));
}

/* **************************************************
 *
 ************************************************** */
rulePtr Item::getRule() const
{
    return rule;
}

/* **************************************************
 *
 ************************************************** */
void Item::setRule(rulePtr _rule)
{
    this->rule = _rule;
}

/* **************************************************
 *
 ************************************************** */
bool Item::getRuleTrace() const
{
    return rule->getTrace();
}

/* **************************************************
 *
 ************************************************** */
unsigned int Item::getRuleLineno() const
{
    return rule->getLineno();
}

/* **************************************************
 *
 ************************************************** */
void Item::rulePrint(std::ostream &os, uint8_t index, bool withSemantic, bool html) const
{
    rule->print(os, index, withSemantic, html);
}

/* **************************************************
 *
 ************************************************** */
unsigned int Item::getRuleId() const
{
    return rule->getId();
}

/* **************************************************
 *
 ************************************************** */
bool Item::getWithSpaces() const
{
    return rule->getWithSpaces();
}

/* **************************************************
 *
 ************************************************** */
bool Item::getBidirectional() const
{
    return rule->getBidirectional();
}

/* **************************************************
 *
 ************************************************** */
bool Item::getPermutable() const
{
    return rule->getPermutable();
}

/* **************************************************
 *
 ************************************************** */
void Item::ruleResetUsages(void)
{
    rule->resetUsages();
}

/* **************************************************
 *
 ************************************************** */
const std::string &Item::getRuleFilename() const
{
    return rule->getFilename();
}

/* **************************************************
 *
 ************************************************** */
uint8_t Item::getIndex() const
{
    return index;
}

/* **************************************************
 *
 ************************************************** */
void Item::setIndex(uint8_t _index)
{
    this->index = _index;
}

/* **************************************************
 *
 ************************************************** */
std::vector<uint8_t> &Item::getIndexTerms()
{
    return indexTerms;
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Item::getStatements()
{
    return statements;
}

/* **************************************************
 *
 ************************************************** */
termsPtr Item::getTerms(const uint16_t _index) const
{
    return rule->getRhs()[_index];
}

/* **************************************************
 *
 ************************************************** */
termsPtr Item::getCurrentTerms() const
{
    if ((this->index == NA) || (this->index >= this->getRuleRhs().size()))
        return nullptr;
    return rule->getRhs()[this->index];
}

/* **************************************************
 *
 ************************************************** */
void Item::setCurrentTerms(termsPtr terms)
{
    this->rule->getRhs()[this->index] = std::move(terms);
}

/* **************************************************
 *
 ************************************************** */
uint16_t Item::getCurrentTerm() const
{
    termsPtr terms = getCurrentTerms();
    if ((terms == nullptr) || (terms->size() == 0))
        return 0;
    return (*terms)[0];
}

/* **************************************************
 *
 ************************************************** */
uint16_t Item::getRuleLhs() const
{
    return rule->getLhs();
}

/* **************************************************
 *
 ************************************************** */
std::vector<termsPtr> &Item::getRuleRhs() const
{
    return rule->getRhs();
}

/* **************************************************
 *
 ************************************************** */
Item::set_of_unsigned_int &Item::getRefs()
{
    return refs;
}

/* **************************************************
 *
 ************************************************** */
void Item::setRefs(set_of_unsigned_int &_refs)
{
    this->refs = _refs;
}

/* **************************************************
 *
 ************************************************** */
void Item::addRef(unsigned int ref)
{
    this->refs.insert(ref);
}

/* **************************************************
 *
 ************************************************** */
void Item::addRefs(set_of_unsigned_int &_refs)
{
    for (auto _ref : _refs)
        addRef(_ref);
}

/* **************************************************
 *
 ************************************************** */
std::vector<bool> &Item::getSeen()
{
    return this->seen;
}

/* **************************************************
 *
 ************************************************** */
void Item::setSeen(std::vector<bool> &_seen)
{
    this->seen = _seen;
}

/* **************************************************
 *
 ************************************************** */
bool Item::isSeen(uint8_t _index) const
{
    return seen[_index];
}

/* **************************************************
 *
 ************************************************** */
void Item::setSeen(uint8_t _index, bool b)
{
    this->seen[_index] = b;
}

/* **************************************************
 *
 ************************************************** */
void Item::addItem(std::unordered_map<unsigned int, class Item *> &table, unsigned int key, class Item *item)
{
    table.insert(std::make_pair(key, item));
}

/* **************************************************
 *
 ************************************************** */
std::vector<uint8_t> &Item::getRanges()
{
    return ranges;
}

/* **************************************************
 *
 ************************************************** */
void Item::addRange(uint8_t range)
{
    ranges.push_back(range);
}

/* **************************************************
 *
 ************************************************** */
void Item::addRanges(std::vector<uint8_t> &ranges)
{
    for (std::vector<uint8_t>::const_iterator i = ranges.begin(); i != ranges.end(); ++i)
        addRange(*i);
}

/* **************************************************
 *
 ************************************************** */
std::vector<class ForestIdentifier *> &Item::getForestIdentifiers()
{
    return forestIdentifiers;
}

/* **************************************************
 *
 ************************************************** */
void Item::addForestIdentifiers(unsigned int key, class ForestIdentifier *forestIdentifier)
{
    forestIdentifiers[key] = std::move(forestIdentifier);
}

/* **************************************************
 *
 ************************************************** */
void Item::addForestIdentifiers(std::vector<class ForestIdentifier *> &_forestIdentifiers)
{
    for (uint8_t it = 0; it < _forestIdentifiers.size(); ++it)
        this->forestIdentifiers[it] = _forestIdentifiers[it];
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr Item::getSynthesizedSonFeatures()
{
    return synthesizedSonFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setSynthesizedSonFeatures(listFeaturesPtr _synthesizedSonFeatures)
{
    this->synthesizedSonFeatures = std::move(_synthesizedSonFeatures);
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr Item::getInheritedSonFeatures()
{
    return inheritedSonFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setInheritedSonFeatures(listFeaturesPtr _inheritedSonFeatures)
{
    this->inheritedSonFeatures = std::move(_inheritedSonFeatures);
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Item::getSynthesizedFeatures() const
{
    return synthesizedFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setSynthesizedFeatures(featuresPtr _synthesizedFeatures)
{
    this->synthesizedFeatures = std::move(_synthesizedFeatures);
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Item::getInheritedFeatures() const
{
    return inheritedFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setInheritedFeatures(featuresPtr _inheritedFeatures)
{
    this->inheritedFeatures = std::move(_inheritedFeatures);
}

/* **************************************************
 *
 ************************************************** */
environmentPtr Item::getEnvironment() const
{
    return this->environment;
}

/* **************************************************
 *
 ************************************************** */
void Item::setEnvironment(environmentPtr _environment)
{
    this->environment = std::move(_environment);
}

/* **************************************************
 *
 ************************************************** */
bool Item::isStarted()
{
    return ranges.size() == 1;
}

/* **************************************************
 *
 ************************************************** */
void Item::addStatements(const statementsPtr &_statements)
{
    if (!this->statements)
        this->statements = Statements::create();
    for (const auto &i : *_statements)
    {
        this->statements->addStatement(i);
    }
    if (this->statements->size() == 0)
    {
        FATAL_ERROR_UNEXPECTED
    }
}

/* **************************************************
 *
 ************************************************** */
bool Item::isCompleted()
{
    return ranges.size() == (this->getRuleRhs().size() + 1);
}

/* **************************************************
 *
 ************************************************** */
bool Item::addEnvironment(statementPtr from, environmentPtr _environment)
{
#ifdef TRACE_ENVIRONMENT
    COUT_LINE;
    std::cout << "<H4>Item::addEnvironment</H4>" << std::endl;
    std::cout << "<table border = \"1\"><tr><th>this</th><th>Environment</th></tr>";
    std::cout << "<tr><td>";
    this->print(std::cout);
    std::cout << "</td><td>";
    environment->print(std::cout);
    std::cout << "</td></tr></table>";
#endif
    if (!this->environment)
        this->environment = Environment::create();
    return this->environment->add(from, std::move(_environment));
}

/* **************************************************
 *
 ************************************************** */
bool Item::addEnvironment(statementPtr from, environmentPtr _environment, environmentPtr where)
{
#ifdef TRACE_ENVIRONMENT
    COUT_LINE;
    std::cout << "<H4>Item::addEnvironment</H4>" << std::endl;
    std::cout << "<table border = \"1\"><tr><th>this</th><th>Environment</th></tr>";
    std::cout << "<tr><td>";
    this->print(std::cout);
    std::cout << "</td><td>";
    environment->print(std::cout);
    std::cout << "</td></tr></table>";
#endif
    if (!this->environment)
        this->environment = Environment::create();
    return this->environment->add(from, std::move(_environment), std::move(where));
}

/* **************************************************
 *
 ************************************************** */
void Item::defaultInheritedSonFeatures()
{
    std::vector<termsPtr> terms = this->getRuleRhs();
    std::vector<bool> assignedInheritedSonFeatures;
    for (std::vector<termsPtr>::const_iterator it = terms.begin(); it != terms.end(); ++it)
        assignedInheritedSonFeatures.push_back(false);
    if (statements)
        for (const auto &statement : *this->statements)
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
void Item::print(std::ostream &out) const
{
    out << "<table border=\"1\" style=\"color:black; ";
    if (isSetFlags(Flags::BOTTOM))
    {
        out << " background-color:DarkViolet;";
    }
    else if (isSetFlags(Flags::SEEN))
        out << " background-color:PaleTurquoise;";
    out << "\">";
    out << "<tr>";
    if (s_id)
        out << "<th>ID</th>";
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
    if (s_terms)
        out << "<th>Terms</th>";
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
    if (s_id)
    {
        out << "<td>";
        out << '#' << std::dec << getId();
        out << "</td>";
    }
    if (s_ruleId)
    {
        out << "<td>";
        out << this->getRuleId();
        out << "</td>";
    }
    if (s_rule)
    {
        out << "<td>";
        this->rulePrint(out);
        out << "</td>";
    }
    if (s_flags)
    {
        out << "<td>";
        printFlags(out);
        out << "</td>";
    }
    if (s_refs)
    {
        out << "<td>(";
        auto ref = refs.begin();
        while (ref != refs.end())
        {
            out << '#' << *ref;
            if (++ref != refs.end())
                out << ' ';
        }
        out << ")</td>";
    }
    if (s_seen)
    {
        out << "<td>(";
        auto s = seen.begin();
        while (s != seen.end())
        {
            out << *s;
            if (++s != seen.end())
                out << ' ';
        }
        out << ")</td>";
    }
    if (s_item)
    {
        out << "<td>";
        rule->print(out, index, false);
        out << "</td>";
    }
    if (s_index)
    {
        out << "<td>";
        if (index == NA)
            out << "NA";
        else
            out << index;
        out << "</td>";
    }
    if (s_indexTerms)
    {
        out << "<td>";
        for (uint8_t indexTerm : indexTerms)
            if (indexTerm == UINT8_MAX)
                out << "UINT8_MAX"
                    << "&nbsp;";
            else
                out << indexTerm << "&nbsp;";
        out << "</td>";
    }
    if (s_terms)
    {
        out << "<td>";
        termsPtr terms = getCurrentTerms();
        if (terms)
            terms->print(out);
        else
            out << "NULL";
        out << "</td>";
    }
    if (s_ranges)
    {
        out << "<td>"; //<center>Ranges</center><br>";
        uint8_t old = UINT8_MAX;
        bool first = true;
        for (uint8_t range : ranges)
        {
            if (old != UINT8_MAX)
            {
                if (first)
                    first = false;
                else
                    out << "&nbsp;";
                out << '[' << old << '-' << range << ']';
            }
            old = range;
        }
        out << "</td>";
    }
    if (s_forestIdentifiers)
    {
        out << "<td>"; //<center>ForestIdentifiers</center><br>";
        for (auto i = forestIdentifiers.begin();
             i != forestIdentifiers.end();)
        {
            if (*i)
                out << (*i)->peekSerialString();
            else
                out << "null";
            if (++i != forestIdentifiers.end())
            {
                out << ", ";
            }
        }
        out << "</td>";
    }
    if (s_inheritedFeatures)
    {
        out << "<td bgcolor=\"lightyellow\">"; //<center>↑</center><br>";
        inheritedFeatures->print(out);
        out << "</td>";
    }
    if (s_inheritedSonFeatures)
    {
        out << "<td bgcolor=\"lightyellow\"><table>"; //<center>↓i</center><br>";
        int k = 1;
        for (const auto &i : *inheritedSonFeatures)
        {
            out << "<tr><td>" << k++ << "</td><td>";
            if (i)
                i->print(out);
            out << "</td></tr>";
        }
        out << "</table></td>";
    }
    if (s_synthesizedFeatures)
    {
        out << "<td bgcolor=\"lightcyan\">"; //<center>⇑</center><br>";
        if (synthesizedFeatures)
        {
            synthesizedFeatures->print(out);
        }
        out << "</td>";
    }
    if (s_synthesizedSonFeatures)
    {
        out << "<td bgcolor=\"lightcyan\"><table>"; //<center>⇓i</center><br>";
        int k = 1;
        for (const auto &i : *synthesizedSonFeatures)
        {
            out << "<tr><td>" << k++ << "</td><td>";
            if (i)
                i->print(out);
            out << "</td></tr>";
        }
        out << "</table></td>";
    }
    if (s_statements)
    {
        out << "<td bgcolor=\"white\">";
        if (statements)
            statements->print(out, 5, 0, 0x000000u, 0xFFFFFFu, true, "{", "}", "");
        else
            out << "&nbsp;";
        out << "</td>";
    }
    if (s_environment && environment)
    {
        out << "<td align=\"center\">";
        if (environment)
            environment->print(out);
        out << "</td>";
    }
    out << "</tr></table>";
    out << std::endl;
}

/* **************************************************
 *
 ************************************************** */
class Item *Item::clone(const std::bitset<FLAGS> &protectedFlags)
{
    class Item *it = Item::create(this->rule, this->index, this->indexTerms,
                                  this->statements ? this->statements->clone(protectedFlags) : statementsPtr());
    it->environment = (this->environment) ? this->environment->clone(nullptr) : environmentPtr();
    it->addRanges(this->ranges);
    it->addForestIdentifiers(this->forestIdentifiers);
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
void Item::step(bool &effect)
{
#ifdef TRACE_STEP
    std::cout << "<H3>####################### STEP #######################</H3>" << std::endl;
    this->print(std::cout);
    std::cout << std::endl;
#endif
    for (uint8_t i = 0; i < this->getRuleRhs().size(); ++i)
    {
        if ((i == index) || ((*this->inheritedSonFeatures)[i]->isNil() && !this->getTerms(i)->isOptional() &&
                             this->getTerms(i)->size() == 1))
            continue;
        if (!this->forestIdentifiers[i])
        {
            this->index = i;
            this->getIndexTerms()[i] = 0;
            effect = true;
            break;
        }
    }

    if (!effect && (index == NA) && isCompleted())
    {
        this->index = this->getRuleRhs().size();
    }
    if (this->index != NA)
        this->setSeen(this->index, true);

#ifdef TRACE_STEP
    std::cout << "<H3>####################### STEP DONE #######################</H3>" << std::endl;
    this->print(std::cout);
    std::cout << std::endl;
#endif
}

/* **************************************************
 *
 ************************************************** */
void Item::apply(Parser &parser, Generator *synthesizer)
{
    bool effect = false;
    statements->apply(this, parser, synthesizer, effect);
    if (statements->isSetFlags(Flags::BOTTOM))
        addFlags(Flags::BOTTOM);
}

/* **************************************************
 *
 ************************************************** */
void Item::makeSerialString()
{
    std::ostringstream stream;
    stream << std::hex << getRuleId() << '\x0' << index << '\x0';
    std::vector<uint8_t>::const_iterator ind = indexTerms.cbegin();
    while (ind != indexTerms.cend()){
        stream << std::hex << *(ind++) << '\x1';
    }
    stream << '\x0';
    set_of_unsigned_int_const_iterator ref = refs.cbegin();
    while (ref != refs.cend()){
        stream << std::hex << *(ref++) << '\x1';
    }

    stream << '\x0';
    std::vector<class ForestIdentifier *>::const_iterator fi = forestIdentifiers.cbegin();
    while (fi != forestIdentifiers.cend())
    {
        if (*fi){
            stream << (*fi)->peekSerialString() << '\x1';
        }
        else{
            stream << '\x1';
        }
        ++fi;
    }

    stream << '\x0';
    stream << inheritedFeatures->peekSerialString();
    serialString = stream.str();
}

/* **************************************************
 *
 ************************************************** */
size_t Item::hash::operator()(class Item *item) const
{
    // defined in serialisable.hpp : std::hash<std::string>{}(serialString)
    return item->hashCode();
}

/* **************************************************
 *
 ************************************************** */
bool Item::equal_to::operator()(class Item *i1, class Item *i2) const
{
    return i1->peekSerialString() == i2->peekSerialString();
}

/* **************************************************
 *
 ************************************************** */
void Item::renameVariables(size_t k)
{
    this->statements->renameVariables(k);
}
