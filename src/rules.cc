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

#include "rules.hpp"
#include "terms.hpp"
#include "vartable.hpp"
#include "messages.hpp"
#include "parser.hpp"
#include "entries.hpp"
#include "rule.hpp"

/* **************************************************
 *
 ************************************************** */
Rules::Rules(void)
{
    NEW;
    this->firstRule = nullptr;
    this->startTerm = 0;
    this->idMax = 0;
}

/* **************************************************
 *
 ************************************************** */
Rules::~Rules(void)
{
    DELETE;
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
Rules::set_of_uint16_t &Rules::getTerminals(void)
{
    return terminals;
}

/* **************************************************
 *
 ************************************************** */
Rules::set_of_uint16_t &Rules::getNonTerminals(void)
{
    return nonTerminals;
}

/* **************************************************
 *
 ************************************************** */
const Rules::list_of_rule &Rules::getRules(void) const
{
    return rules;
}

/* **************************************************
 *
 ************************************************** */
uint16_t Rules::getStartTerm(void) const
{
    return startTerm;
}

/* **************************************************
 *
 ************************************************** */
rulePtr Rules::getFirstRule(void) const
{
    return firstRule;
}

/* **************************************************
 *
 ************************************************** */
const uint32_t *Rules::getRefIdMax(void) const
{
    return &idMax;
}

/* **************************************************
 *
 ************************************************** */
void Rules::setStartTerm(uint16_t _startTerm)
{
    this->startTerm = _startTerm;
}

/* **************************************************
 *
 ************************************************** */
Rules::list_of_rule::const_iterator Rules::cbegin(void) const
{
    return rules.cbegin();
}

/* **************************************************
 *
 ************************************************** */
Rules::list_of_rule::const_iterator Rules::cend(void) const
{
    return rules.cend();
}

/* **************************************************
 *
 ************************************************** */
void Rules::addRule(rulePtr rule)
{
    rules.push_back(rule);
}

/* **************************************************
 *
 ************************************************** */
void Rules::print(std::ostream &outStream) const
{
    outStream << "<table border=\"1\"><tr><td>";
    outStream << "Terminals</td><td>";
    set_of_uint16_t::const_iterator iter;
    bool first = true;
    for (iter = terminals.begin(); iter != terminals.end(); ++iter)
    {
        if (first)
            first = false;
        else
            outStream << ", ";
        outStream << Vartable::codeToName(*iter);
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
        outStream << Vartable::codeToName(*iter);
    }
    outStream << "</td></tr><tr><td>";
    outStream << "StartTerm</td><td>";
    if (startTerm)
        outStream << Vartable::codeToName(startTerm);
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
void Rules::addNonTerminal(uint16_t s)
{
    nonTerminals.insert(s);
}

/* **************************************************
 *
 ************************************************** */
void Rules::addTerminal(uint16_t s)
{
    terminals.insert(s);
}

/* **************************************************
 *
 ************************************************** */
bool Rules::isTerminal(uint16_t t) const
{
    set_of_uint16_t::const_iterator iter = terminals.find(t);
    return (iter != terminals.end());
}

/* **************************************************
 *
 ************************************************** */
bool Rules::isNonTerminal(uint16_t t) const
{
    set_of_uint16_t::const_iterator iter = nonTerminals.find(t);
    return (iter != nonTerminals.end());
}

/* **************************************************
 *
 ************************************************** */
void Rules::analyseTerms(class Parser &parser)
{
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
            for (std::vector<uint16_t>::const_iterator term = (*iterRules)->getTerms(i)->begin();
                 term != (*iterRules)->getTerms(i)->end(); ++term)
            {
                if (nonTerminals.find(*term) == nonTerminals.end())
                {
                    uint16_t code = (*term);
                    terminals.insert(code);

                    Parser::entries_map *headToEntries;
                    Parser::entries_map_map_const_iterator foundCode = parser.findCacheLexicon(code);
                    if (foundCode == parser.cendCacheLexicon())
                    {
                        headToEntries = new Parser::entries_map;
                        headToEntries->insert(std::make_pair(code, Entries::create()));
                        parser._insertCacheLexicon(std::make_pair(code, headToEntries));
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
void Rules::toXML(xmlNodePtr nodeRoot)
{
    xmlNodePtr g = xmlNewChild(nodeRoot, NULL, (const xmlChar *)"GRAMMAR", NULL);
    xmlNodePtr t = xmlNewChild(g, NULL, (const xmlChar *)"TERMINALS", NULL);
    set_of_uint16_t::const_iterator iter;
    for (iter = terminals.begin(); iter != terminals.end(); ++iter)
    {
        xmlNewChild(t, NULL, (const xmlChar *)"TERM", (const xmlChar *)(Vartable::codeToName(*iter).c_str()));
    }
    t = xmlNewChild(g, NULL, (const xmlChar *)"NON-TERMINALS", NULL);
    for (iter = nonTerminals.begin(); iter != nonTerminals.end(); ++iter)
    {
        xmlNewChild(t, NULL, (const xmlChar *)"TERM", (const xmlChar *)(Vartable::codeToName(*iter).c_str()));
    }
    // xmlNodePtr r = xmlNewChild(g, NULL, (const xmlChar*)"RULES", NULL);
    // list_of_rule::const_iterator iterRules;
    // for (iterRules = rulesBegin(); iterRules != rulesEnd(); ++iterRules) {
    //    (*iterRules)->toXML(g);
    // }
}
#endif

/* **************************************************
 *
 % ************************************************** */
std::list<rulePtr> *
Rules::findRules(uint16_t lhs)
{
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
