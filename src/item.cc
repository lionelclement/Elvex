/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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
#include "item.hpp"
#include "feature.hpp"
#include "features.hpp"
#include "value.hpp"
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

uint32_t Item::TERM_NA = UINT32_MAX;
uint8_t Item::INDEX_NA = UINT8_MAX;
uint8_t Item::POSTERM_NA = UINT8_MAX;
uint8_t Item::POSTERMS_NA = UINT8_MAX - 1;

/* **************************************************
 *
 ************************************************** */
Item::Item(rulePtr rule, uint8_t index, statementsPtr statements)
{
    NEW;
    this->rule = rule;
    this->index = index;
    this->statements = statements;
    this->environment = environmentPtr();
    this->inheritedFeatures = Features::NIL;
    this->synthesizedFeatures = Features::NIL;
    this->synthesizedChildFeatures = ListFeatures::create();
    this->inheritedChildFeatures = ListFeatures::create();
}

/* **************************************************
 *
 ************************************************** */
Item::Item(const rulePtr &rule, uint8_t index, uint8_t indexTerm, statementsPtr statements)
    : Item(rule, index, statements)
{
    std::vector<termsPtr> terms = rule->getRhs();
    unsigned j = 0;
    for (std::vector<termsPtr>::const_iterator i = terms.begin(); i != terms.end(); ++i, ++j)
    {
        this->indexTerms.push_back(POSTERM_NA);
        this->seen.push_back(false);
        this->forestIdentifiers.push_back(nullptr);
        this->synthesizedChildFeatures->push_back(Features::NIL);
        this->inheritedChildFeatures->push_back(Features::NIL);
    }
    if ((terms.size() < index) && (index != INDEX_NA))
        this->indexTerms[index] = indexTerm;
}

/* **************************************************
 *
 ************************************************** */
Item::Item(const rulePtr &rule, uint8_t index, std::vector<uint8_t> &indexTerms, statementsPtr statements)
    : Item(rule, index, statements)
{
    this->indexTerms = indexTerms;
    std::vector<termsPtr> terms = rule->getRhs();
    unsigned j = 0;
    for (std::vector<termsPtr>::const_iterator i = terms.begin(); i != terms.end(); ++i, ++j)
    {
        this->seen.push_back(false);
        this->forestIdentifiers.push_back(nullptr);
        this->synthesizedChildFeatures->push_back(Features::NIL);
        this->inheritedChildFeatures->push_back(Features::NIL);
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
    if (inheritedChildFeatures)
        inheritedChildFeatures.reset();
    if (synthesizedFeatures)
        synthesizedFeatures.reset();
    if (synthesizedChildFeatures)
        synthesizedChildFeatures.reset();
    for (auto it : forestIdentifiers)
    {
        class ForestIdentifier *tmp = it;
        if (tmp)
            free(tmp);
    }
    forestIdentifiers.clear();
    if (statements)
        statements.reset();
    // if (environment)
    //     environment.reset();
}

/* **************************************************
 *
 ************************************************** */
class Item *Item::create(const rulePtr &rule, uint8_t index, uint8_t indexTerm, statementsPtr statements)
{
    return new Item(rule, index, indexTerm, statements);
}

/* **************************************************
 *
 ************************************************** */
class Item *
Item::create(const rulePtr &rule, uint8_t index, std::vector<uint8_t> &indexTerms, statementsPtr statements)
{
    return new Item(rule, index, indexTerms, statements);
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
uint32_t Item::getRuleLineno() const
{
    return rule->getLineno();
}

/* **************************************************
 *
 ************************************************** */
void Item::printRule(std::ostream &os, uint8_t index, bool withSemantic, bool html) const
{
    rule->print(os, index, withSemantic, html);
}

/* **************************************************
 *
 ************************************************** */
uint32_t Item::getRuleId() const
{
    return rule->getId();
}

/* **************************************************
 *
 ************************************************** */
std::string Item::getRuleIdStr() const
{
    return rule->getIdStr();
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
bool Item::getUnordered() const
{
    return rule->getUnordered();
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
termsPtr Item::getTerms(const uint32_t _index) const
{
    return rule->getRhs()[_index];
}

/* **************************************************
 *
 ************************************************** */
termsPtr Item::getCurrentTerms() const
{
    if ((this->index == INDEX_NA) || (this->index >= this->getRuleRhs().size()))
        return nullptr;
    return rule->getRhs()[this->index];
}

/* **************************************************
 *
 ************************************************** */
void Item::setCurrentTerms(termsPtr terms)
{
    this->rule->getRhs()[this->index] = (terms);
}

/* **************************************************
 *
 ************************************************** */
uint32_t Item::getCurrentTerm() const
{
    termsPtr terms = getCurrentTerms();
    if ((terms == nullptr) || (terms->size() == 0))
        return 0;
    return (*terms)[0];
}

/* **************************************************
 *
 ************************************************** */
uint32_t Item::getRuleLhs() const
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
Item::set_of_uint32_t &Item::getRefs()
{
    return refs;
}

/* **************************************************
 *
 ************************************************** */
void Item::setRefs(const set_of_uint32_t &_refs)
{
    this->refs = _refs;
}

/* **************************************************
 *
 ************************************************** */
void Item::addRef(const uint32_t ref)
{
    this->refs.insert(ref);
}

/* **************************************************
 *
 ************************************************** */
void Item::addRefs(const set_of_uint32_t &_refs)
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
void Item::addItem(std::unordered_map<uint32_t, class Item *> &table, unsigned int key, class Item *item)
{
    table.insert(std::make_pair(key, item));
}

/* **************************************************
 *
 ************************************************** */
std::vector<uint32_t> &Item::getRanges()
{
    return ranges;
}

/* **************************************************
 *
 ************************************************** */
void Item::addRange(uint32_t range)
{
    ranges.push_back(range);
}

/* **************************************************
 *
 ************************************************** */
void Item::addRanges(std::vector<uint32_t> &ranges)
{
    for (std::vector<uint32_t>::const_iterator i = ranges.begin(); i != ranges.end(); ++i)
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
    forestIdentifiers[key] = (forestIdentifier);
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
listFeaturesPtr Item::getSynthesizedChildFeatures() const
{
    return synthesizedChildFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setSynthesizedChildFeatures(listFeaturesPtr _synthesizedChildFeatures)
{
    this->synthesizedChildFeatures = _synthesizedChildFeatures;
    // this->synthesizedChildFeatures = /*std::move*/(_synthesizedChildFeatures);
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr Item::getInheritedChildFeatures()
{
    return inheritedChildFeatures;
}

/* **************************************************
 *
 ************************************************** */
void Item::setInheritedChildFeatures(listFeaturesPtr _inheritedChildFeatures)
{
    this->inheritedChildFeatures = (_inheritedChildFeatures);
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
    this->synthesizedFeatures = _synthesizedFeatures;
    // this->synthesizedFeatures = /*std::move*/(_synthesizedFeatures);
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
    this->inheritedFeatures = (_inheritedFeatures);
}

/* **************************************************
 *
 ************************************************** */
void Item::_setEnvironment(environmentPtr environment)
{
    this->environment = environment;
    // resetSerial();
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
bool Item::addEnvironment(statementPtr from, environmentPtr _environment, bool verbose)
{
#ifdef TRACE_ENVIRONMENT
    COUT_LINE;
    std::cout << "<H4>Item::addEnvironment</H4>" << std::endl;
    std::cout << "<table border = \"1\"><tr><th>this</th><th>Environment</th></tr>";
    std::cout << "<tr><td>";
    this->toHTML(std::cout);
    std::cout << "</td><td>";
    environment->toHTML(std::cout);
    std::cout << "</td></tr></table>";
#endif
    if (!this->environment)
        this->environment = Environment::create();
    return this->environment->add(from, (_environment), verbose);
}

/* **************************************************
 *
 ************************************************** */
bool Item::addEnvironment(statementPtr from, environmentPtr _environment, environmentPtr where, bool verbose)
{
#ifdef TRACE_ENVIRONMENT
    COUT_LINE;
    std::cout << "<H4>Item::addEnvironment</H4>" << std::endl;
    std::cout << "<table border = \"1\"><tr><th>this</th><th>Environment</th></tr>";
    std::cout << "<tr><td>";
    this->toHTML(std::cout);
    std::cout << "</td><td>";
    environment->toHTML(std::cout);
    std::cout << "</td></tr></table>";
#endif
    if (!this->environment)
        this->environment = Environment::create();
    return this->environment->add(from, _environment, where, verbose);
}

/* **************************************************
 *
 ************************************************** */
void Item::defaultInheritedChildFeatures()
{
    std::vector<termsPtr> terms = this->getRuleRhs();
    std::vector<bool> assignedInheritedChildFeatures;
    for (std::vector<termsPtr>::const_iterator it = terms.begin(); it != terms.end(); ++it)
        assignedInheritedChildFeatures.push_back(false);
    if (statements)
        for (const auto &statement : *this->statements)
            statement->lookingForAssignedInheritedChildFeatures(assignedInheritedChildFeatures);
    unsigned int j = 0;
    for (std::vector<bool>::const_iterator it = assignedInheritedChildFeatures.begin();
         it != assignedInheritedChildFeatures.end(); ++it, ++j)
        if (!(*it))
            (*inheritedChildFeatures).add(j, Features::create());
}

/* **************************************************
 *
 ************************************************** */
void Item::toHTML(std::ostream &out) /*const*/
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
    if (s_inheritedChildFeatures)
        out << "<th bgcolor=\"lightyellow\"><center>↓i</center></th>";
    if (s_synthesizedFeatures)
        out << "<th bgcolor=\"lightcyan\"><center>⇑</center></th>";
    if (s_synthesizedChildFeatures)
        out << "<th bgcolor=\"lightcyan\"><center>⇓i</center></th>";
    if (s_statements)
        out << "<th bgcolor=\"white\"><center>Statements</center></th>";
    if (s_environment && environment)
        out << "<th align = center>Environment</th>";
    out << "</tr><tr>";
    if (s_id)
    {
        out << "<td>";
        out << '#' << std::hex << getId();
        // out << peekSerialString();
        out << "</td>";
    }
    if (s_ruleId)
    {
        out << "<td>";
        out << this->getRuleIdStr();
        out << "</td>";
    }
    if (s_rule)
    {
        out << "<td>";
        printRule(out);
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
        if (index == INDEX_NA)
            out << "NA";
        else
            out << '#' << (int)index;
        out << "</td>";
    }
    if (s_indexTerms)
    {
        out << "<td>";
        for (uint8_t indexTerm : indexTerms)
            if (indexTerm == POSTERM_NA)
                out << "NA"
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
        uint8_t old = INT8_MAX;
        bool first = true;
        for (uint8_t range : ranges)
        {
            if (old != INT8_MAX)
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
                out << (*i)->peekCoreSerialString();
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
        inheritedFeatures->toHTML(out);
        out << "</td>";
    }
    if (s_inheritedChildFeatures)
    {
        out << "<td bgcolor=\"lightyellow\"><table>"; //<center>↓i</center><br>";
        int k = 1;
        for (const auto &i : *inheritedChildFeatures)
        {
            out << "<tr><td>" << k++ << "</td><td>";
            if (i)
                i->toHTML(out);
            out << "</td></tr>";
        }
        out << "</table></td>";
    }
    if (s_synthesizedFeatures)
    {
        out << "<td bgcolor=\"lightcyan\">"; //<center>⇑</center><br>";
        if (synthesizedFeatures)
        {
            synthesizedFeatures->toHTML(out);
        }
        out << "</td>";
    }
    if (s_synthesizedChildFeatures)
    {
        out << "<td bgcolor=\"lightcyan\"><table>"; //<center>⇓i</center><br>";
        int k = 1;
        for (const auto &i : *synthesizedChildFeatures)
        {
            out << "<tr><td>" << k++ << "</td><td>";
            if (i)
                i->toHTML(out);
            out << "</td></tr>";
        }
        out << "</table></td>";
    }
    if (s_statements)
    {
        auto r = rand();
        /*
        out << R"(
        <td><table>
        <tr><td><button onclick="toggleVisibility('cell_)"
            << std::hex << r << getId() << R"(') ">Toggle</button></td></tr>
        <tr><td bgcolor="white">
        <div class="hidden" id="cell_)"
            << std::hex << r << getId() << "\">";
        */
       out << R"(
        <td><table>
        <tr><td bgcolor="white">
        <div class="text" id="cell_)"
            << std::hex << r << getId() << "\">";
        if (statements)
            statements->print(out, 5, 0, 0x000000u, 0xFFFFFFu, true, "{", "}", "");
        else
            out << "&nbsp;";
        out << R"(
        </div>
        </td></tr>
        </table></td>)";
    }
    if (s_environment && environment)
    {
        out << "<td align=\"center\">";
        environment->toHTML(out);
        out << "</td>";
    }
    out << "</tr></table>";
    out << std::endl;
}

/* **************************************************
 *
 ************************************************** */
class Item *Item::clone(const std::bitset<MAX_FLAGS> &protectedFlags, bool verbose)
{
    class Item *it = Item::create(this->rule, this->index, this->indexTerms,
                                  this->statements ? this->statements->clone(protectedFlags) : statementsPtr());
    it->environment = (this->environment) ? this->environment->clone(nullptr, verbose) : environmentPtr();
    it->addRanges(this->ranges);
    it->addForestIdentifiers(this->forestIdentifiers);
    it->refs = this->refs;
    it->seen = this->seen;
    it->inheritedFeatures = this->inheritedFeatures->clone();
    it->inheritedChildFeatures = this->inheritedChildFeatures->clone();
    it->synthesizedChildFeatures = this->synthesizedChildFeatures->clone();
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
    this->toHTML(std::cout);
    std::cout << std::endl;
#endif
    for (uint8_t i = 0; i < this->getRuleRhs().size(); ++i)
    {
        if ((i == index) || ((*this->inheritedChildFeatures)[i]->isNil() && !this->getTerms(i)->isOptional() &&
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

    if (!effect && (index == INDEX_NA) && isCompleted())
    {
        this->index = this->getRuleRhs().size();
    }
    if (this->index != INDEX_NA)
        this->setSeen(this->index, true);

#ifdef TRACE_STEP
    std::cout << "<H3>####################### STEP DONE #######################</H3>" << std::endl;
    this->toHTML(std::cout);
    std::cout << std::endl;
#endif
}

/* **************************************************
 *
 ************************************************** */
void Item::apply(Parser &parser, Generator *generator, bool verbose)
{
    bool effect = false;
    statements->apply(this, parser, generator, effect, verbose);
    if (statements->isSetFlags(Flags::BOTTOM))
        addFlags(Flags::BOTTOM);
}

/* **************************************************
 *
 ************************************************** */
void Item::makeCoreSerialString()
{
    std::ostringstream stream;
    stream << std::hex << (int)getRuleId() << '#' << (int)index << '#';

    for (auto ind = indexTerms.cbegin(); ind != indexTerms.cend(); ++ind)
    {
        stream << std::hex << (int)*ind << '/';
    }

    stream << '#';
    for (auto ref = refs.cbegin(); ref != refs.cend(); ++ref)
    {
        stream << std::hex << (int)*ref << '/';
    }
    
    stream << '#';
    for (auto fi = forestIdentifiers.cbegin();
         fi != forestIdentifiers.cend();
         ++fi)
    {
        stream << '/' << ((*fi) ? (*fi)->peekCoreSerialString() : "0") << '/';
    }
    
    stream << '#';
    stream << (inheritedFeatures ? inheritedFeatures->peekCoreSerialString() : "0");

    stream.flush();
    coreSerialString = stream.str();
}

/* **************************************************
 *
 ************************************************** */
size_t Item::Hash::operator()(class Item *item) const
{
    // defined in serialisable.hpp
    return item->coreHash();
}

/* **************************************************
 *
 ************************************************** */
bool Item::KeyEqual::operator()(class Item *item1, class Item *item2) const
{
    return item1->peekCoreSerialString() == item2->peekCoreSerialString();
}

/* **************************************************
 *
 ************************************************** */
void Item::renameVariables(uint32_t code)
{
    if (inheritedFeatures)
        inheritedFeatures->renameVariables(code);
    if (statements)
        statements->renameVariables(code);
}

/* **************************************************
 *
 ************************************************** */
void Item::replaceSynthesizedChildFeaturesValue(featuresPtr features)
{
    for (auto it = features->begin(); it != features->end(); ++it)
    {
        featurePtr feature = *it;
        switch (feature->getType())
        {
        case Feature::_VARIABLE_:
            break;
        case Feature::_HEAD_:
        case Feature::_LEMMA_:
        case Feature::_FORM_:
        case Feature::_CONSTANT_:
            if (feature->getValue() && (feature->getValue()->isSynthesizedChildFeatures()))
                replaceSynthesizedChildFeaturesValue(feature->getValue());
            break;
        }
    }
}

/* **************************************************
 *
 ************************************************** */
void Item::replaceSynthesizedChildFeaturesValue(valuePtr value)
{
    if (!value->isNil() && !value->isAnonymous())
    {
        switch (value->getType())
        {
        case Value::SYNTHESIZED_CHILD_FEATURES_VALUE:
        {
            featuresPtr features = synthesizedChildFeatures->get(value->getCode());

            if (features)
            {
                *value = *Value::createFeatures(features);
            }
        }
        break;
        default:
            break;
        }
    }
}

/* **************************************************
 *
 ************************************************** */
void Item::environmentAdd(statementPtr statementRoot, uint32_t code, valuePtr value, bool verbose)
{
    if (!environment)
        FATAL_ERROR_UNEXPECTED;
    environment->add(statementRoot, code, value, verbose);
}

/* **************************************************
 *
 ************************************************** */
void Item::environmentRemove(uint32_t code)
{
    if (!environment)
        FATAL_ERROR_UNEXPECTED;
    environment->remove(code);
}

/* **************************************************
 *
 ************************************************** */
valuePtr Item::environmentGet(uint32_t code)
{
    if (!environment)
        FATAL_ERROR_UNEXPECTED;
    return environment->get(code);
}

/* **************************************************
 *
 ************************************************** */
bool Item::environmentIsEmpty()
{
    if (!environment)
        FATAL_ERROR_UNEXPECTED;
    return environment->empty();
}

/* **************************************************
 *
 ************************************************** */
void Item::environmentReplaceVariables(const valuePtr &value, bool &effect)
{
    if (!environment)
        FATAL_ERROR_UNEXPECTED;
    environment->replaceVariables(value, effect);
}

/* **************************************************
 *
 ************************************************** */
void Item::environmentReplaceVariables(const pairpPtr &pair, bool &effect)
{
    if (!environment)
        FATAL_ERROR_UNEXPECTED;
    environment->replaceVariables(pair, effect);
}

/* **************************************************
 *
 ************************************************** */
void Item::environmentReplaceVariables(const featuresPtr &features, bool &effect)
{
    if (!environment)
        FATAL_ERROR_UNEXPECTED;
    environment->replaceVariables(features, effect);
}

/* **************************************************
 *
 ************************************************** */
void Item::environmentReplaceVariables(std::string &str, bool &effect)
{
    if (!environment)
        FATAL_ERROR_UNEXPECTED;
    environment->replaceVariables(str, effect);
}

/* **************************************************
 *
 ************************************************** */
void Item::cloneEnvironment(const class Item *from)
{
    if (!from->environment)
        FATAL_ERROR_UNEXPECTED;
    this->environment = from->environment->clone(nullptr, false);
}

/* **************************************************
 *
 ************************************************** */
environmentPtr Item::_getEnvironment() const
{
    return environment;
}
