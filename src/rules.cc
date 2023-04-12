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
 * LaBRI -- Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#include "rules.hpp"
#include "terms.hpp"
#include "vartable.hpp"
#include "messages.hpp"
#include "generator.hpp"
#include "application.hpp"
#include "entries.hpp"
#include "rule.hpp"

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
Rules::Rules(void) {
=======
Rules::Rules(void)
{
    NEW;
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    this->firstRule = nullptr;
    this->startTerm = 0;
    this->idMax = 0;
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
Rules::~Rules(void) {
    DELETE
=======
Rules::~Rules(void)
{
    DELETE;
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    terminals.clear();
    nonTerminals.clear();
    for (list_of_rule::const_iterator iterRules = cbegin(); iterRules != cend(); ++iterRules)
    {
        rulePtr tmp = *iterRules;
        if (tmp)
            tmp.reset();
    }
    rules.clear();
    if (firstRule)
    {
        firstRule.reset();
    }
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
std::set<unsigned int> &Rules::getTerminals(void) {
=======
Rules::set_of_unsigned_int &Rules::getTerminals(void)
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    return terminals;
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
std::set<unsigned int> &Rules::getNonTerminals(void) {
=======
Rules::set_of_unsigned_int &Rules::getNonTerminals(void)
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    return nonTerminals;
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
const Rules::ruleList &Rules::getRules(void) const {
=======
const Rules::list_of_rule &Rules::getRules(void) const
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    return rules;
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
unsigned int Rules::getStartTerm(void) const {
=======
unsigned int Rules::getStartTerm(void) const
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    return startTerm;
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
rulePtr Rules::getFirstRule(void) const {
=======
rulePtr Rules::getFirstRule(void) const
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    return firstRule;
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
const unsigned int *Rules::getRefIdMax(void) const {
=======
const unsigned int *Rules::getRefIdMax(void) const
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    return &idMax;
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
void Rules::setStartTerm(unsigned int _startTerm) {
=======
void Rules::setStartTerm(unsigned int _startTerm)
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    this->startTerm = _startTerm;
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
Rules::ruleList::const_iterator Rules::rulesBegin(void) const {
    return rules.begin();
=======
Rules::list_of_rule::const_iterator Rules::cbegin(void) const
{
    return rules.cbegin();
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
Rules::ruleList::const_iterator Rules::rulesEnd(void) const {
    return rules.end();
=======
Rules::list_of_rule::const_iterator Rules::cend(void) const
{
    return rules.cend();
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
void Rules::addRule(rulePtr rule) {
=======
void Rules::addRule(rulePtr rule)
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    rules.push_back(rule);
    // std::pair<list_of_rule::iterator, bool> result = rules.insert(rule);
    // return result.second;
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
void Rules::addNewStartTerm(bool addENDTerminal) {
=======
void Rules::addNewStartTerm(bool addENDTerminal)
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    rulePtr r;
    std::vector<termsPtr> rhs;

    if (addENDTerminal)
    {
        terminals.insert(Vartable::_END_);
    }

    Vartable::insertCodeMap(Vartable::_START_TERM_, "_START_TERM_");
    nonTerminals.insert(Vartable::_START_TERM_);

    rhs.push_back(Terms::create(getStartTerm()));
    if (addENDTerminal)
    {
        rhs.push_back(Terms::create(Vartable::_END_));
    }

    std::string fileName = "";
    r = Rule::create(0, fileName, Vartable::_START_TERM_, rhs);
    setStartTerm(startTerm);
    rules.push_back(r);
    firstRule = r;
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
void Rules::print(std::ostream &outStream) const {
=======
void Rules::print(std::ostream &outStream) const
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    outStream << "<table border=\"1\"><tr><td>";
    outStream << "Terminals</td><td>";
    set_of_unsigned_int::const_iterator iter;
    bool first = true;
    for (iter = terminals.begin(); iter != terminals.end(); ++iter)
    {
        if (first)
            first = false;
        else
            outStream << ", ";
        outStream << Vartable::codeToString(*iter);
    }
    outStream << "</td></tr><tr><td>";
    outStream << "NonTerminals</td><td>";
    first = true;
    for (iter = nonTerminals.begin(); iter != nonTerminals.end(); ++iter)
    {
        if (first)
            first = false;
        else
            outStream << ", ";
        outStream << Vartable::codeToString(*iter);
    }
    outStream << "</td></tr><tr><td>";
    outStream << "StartTerm</td><td>";
    if (startTerm)
        outStream << Vartable::codeToString(startTerm);
    else
        outStream << "NULL";
    outStream << std::endl;
    outStream << "</td></tr><tr><td>Rules</td><td><table>";
    for (list_of_rule::const_iterator iterRules = cbegin(); iterRules != cend(); ++iterRules)
    {
        outStream << "<tr><td>";
        (*iterRules)->print(outStream, -1, true);
        outStream << "</td></tr>";
    }
    outStream << "</table></td></tr></td></table>";
    outStream << std::endl;
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
void Rules::addNonTerminal(unsigned int s) {
=======
void Rules::addNonTerminal(unsigned int s)
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    nonTerminals.insert(s);
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
void Rules::addTerminal(unsigned int s) {
=======
void Rules::addTerminal(unsigned int s)
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    terminals.insert(s);
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
bool Rules::isTerminal(unsigned int t) const {
    std::set<unsigned int>::const_iterator iter = terminals.find(t);
=======
bool Rules::isTerminal(unsigned int t) const
{
    set_of_unsigned_int::const_iterator iter = terminals.find(t);
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    return (iter != terminals.end());
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
bool Rules::isNonTerminal(unsigned int t) const {
    std::set<unsigned int>::const_iterator iter = nonTerminals.find(t);
=======
bool Rules::isNonTerminal(unsigned int t) const
{
    set_of_unsigned_int::const_iterator iter = nonTerminals.find(t);
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    return (iter != nonTerminals.end());
}

/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
void Rules::analyseTerms(class Application &application) {
=======
void Rules::analyseTerms(class Parser &parser)
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    nonTerminals.clear();
    terminals.clear();
    list_of_rule::const_iterator iterRules;
    for (iterRules = cbegin(); iterRules != cend(); ++iterRules)
    {
        nonTerminals.insert((*iterRules)->getLhs());
    }
    for (iterRules = cbegin(); iterRules != cend(); ++iterRules)
    {
        unsigned int i;
        for (i = 0; i < (*iterRules)->getRhs().size(); ++i)
        {
            for (std::vector<unsigned int>::const_iterator term = (*iterRules)->getTerms(i)->begin();
                 term != (*iterRules)->getTerms(i)->end(); ++term)
            {
                if (nonTerminals.find(*term) == nonTerminals.end())
                {
                    unsigned long int code = (*term);
                    terminals.insert(code);

<<<<<<< HEAD
                    Generator::entries_map *predToEntries;
                    Generator::entries_map_map::iterator foundCode = application.generator.getLexicon().find(code);
                    if (foundCode == application.generator.getLexicon().end()) {
                        predToEntries = new std::map<unsigned int, entriesPtr>;
                        predToEntries->insert(std::make_pair(code, Entries::create()));
                        application.generator.getLexicon().insert(std::make_pair(code, predToEntries));
=======
                    Parser::entries_map *predToEntries;
                    Parser::entries_map_map_const_iterator foundCode = parser.findCacheLexicon(code);
                    if (foundCode == parser.cendCacheLexicon())
                    {
                        predToEntries = new Parser::entries_map;
                        predToEntries->insert(std::make_pair(code, Entries::create()));
                        parser.insertCacheLexicon(std::make_pair(code, predToEntries));
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
                    }
                }
            }
        }
    }
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
<<<<<<< HEAD
void
Rules::toXML(xmlNodePtr nodeRoot)
{
   xmlNodePtr g=xmlNewChild(nodeRoot, NULL, (const xmlChar*)"Rules", NULL);
   xmlNodePtr t=xmlNewChild(g, NULL, (const xmlChar*)"TERMINALS", NULL);
   std::set<unsigned int>::const_iterator iter;
   for (iter=terminals.begin(); iter != terminals.end(); ++iter) {
      xmlNewChild(t, NULL, (const xmlChar*)"TERM", (const xmlChar*)(Vartable::codeToIdentifier(*iter).c_str()));
   }
   t=xmlNewChild(g, NULL, (const xmlChar*)"NON-TERMINALS", NULL);
   for (iter=nonTerminals.begin(); iter != nonTerminals.end(); ++iter) {
      xmlNewChild(t, NULL, (const xmlChar*)"TERM", (const xmlChar*)(Vartable::codeToIdentifier(*iter).c_str()));
   }
   //xmlNodePtr r = xmlNewChild(g, NULL, (const xmlChar*)"RULES", NULL);
   ruleList::const_iterator iterRules;
   for (iterRules=rulesBegin(); iterRules != rulesEnd(); ++iterRules) {
      (*iterRules)->toXML(/*r*/);
   }
=======
void Rules::toXML(xmlNodePtr nodeRoot)
{
    xmlNodePtr g = xmlNewChild(nodeRoot, NULL, (const xmlChar *)"GRAMMAR", NULL);
    xmlNodePtr t = xmlNewChild(g, NULL, (const xmlChar *)"TERMINALS", NULL);
    set_of_unsigned_int::const_iterator iter;
    for (iter = terminals.begin(); iter != terminals.end(); ++iter)
    {
        xmlNewChild(t, NULL, (const xmlChar *)"TERM", (const xmlChar *)(Vartable::codeToString(*iter).c_str()));
    }
    t = xmlNewChild(g, NULL, (const xmlChar *)"NON-TERMINALS", NULL);
    for (iter = nonTerminals.begin(); iter != nonTerminals.end(); ++iter)
    {
        xmlNewChild(t, NULL, (const xmlChar *)"TERM", (const xmlChar *)(Vartable::codeToString(*iter).c_str()));
    }
    // xmlNodePtr r = xmlNewChild(g, NULL, (const xmlChar*)"RULES", NULL);
    // list_of_rule::const_iterator iterRules;
    // for (iterRules = rulesBegin(); iterRules != rulesEnd(); ++iterRules) {
    //    (*iterRules)->toXML(g);
    // }
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
}
#endif

/* **************************************************
 *
 % ************************************************** */
std::list<rulePtr> *
<<<<<<< HEAD
Rules::findRules(unsigned int lhs) {
=======
Rules::findRules(unsigned int lhs)
{
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
    std::list<rulePtr> *result = new std::list<rulePtr>;
    list_of_rule::const_iterator iterRules;
    for (iterRules = cbegin(); iterRules != cend(); iterRules++)
    {
        if (lhs == (*iterRules)->getLhs())
        {
            result->push_back(*iterRules);
        }
    }
    return result;
}
