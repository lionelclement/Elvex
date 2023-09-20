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
 * LaBRI - Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#include "grammar.hpp"
#include "terms.hpp"
#include "vartable.hpp"
#include "messages.hpp"
#include "parser.hpp"
#include "entries.hpp"
#include "rule.hpp"

/* **************************************************
 *
 ************************************************** */
Grammar::Grammar(void)
{
    this->firstRule = nullptr;
    this->startTerm = 0;
    this->idMax = 0;
    NEW
}

/* **************************************************
 *
 ************************************************** */
Grammar::~Grammar(void)
{
    DELETE
    terminals.clear();
    nonTerminals.clear();
    for (ruleList::const_iterator iterRules = rulesBegin(); iterRules != rulesEnd(); ++iterRules)
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
std::set<unsigned int> &Grammar::getTerminals(void)
{
    return terminals;
}

/* **************************************************
 *
 ************************************************** */
std::set<unsigned int> &Grammar::getNonTerminals(void)
{
    return nonTerminals;
}

/* **************************************************
 *
 ************************************************** */
const Grammar::ruleList &Grammar::getRules(void) const
{
    return rules;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Grammar::getStartTerm(void) const
{
    return startTerm;
}

/* **************************************************
 *
 ************************************************** */
rulePtr Grammar::getFirstRule(void) const
{
    return firstRule;
}

/* **************************************************
 *
 ************************************************** */
const unsigned int *Grammar::getRefIdMax(void) const
{
    return &idMax;
}

/* **************************************************
 *
 ************************************************** */
void Grammar::setStartTerm(unsigned int _startTerm)
{
    this->startTerm = _startTerm;
}

/* **************************************************
 *
 ************************************************** */
Grammar::ruleList::const_iterator Grammar::rulesBegin(void) const
{
    return rules.begin();
}

/* **************************************************
 *
 ************************************************** */
Grammar::ruleList::const_iterator Grammar::rulesEnd(void) const
{
    return rules.end();
}

/* **************************************************
 *
 ************************************************** */
void Grammar::addRule(rulePtr rule)
{
    rules.push_back(rule);
    // std::pair<ruleList::iterator, bool> result = rules.insert(rule);
    // return result.second;
}

/* **************************************************
 *
 ************************************************** */
void Grammar::addNewStartTerm(bool addENDTerminal)
{
    rulePtr r;
    std::vector<termsPtr> rhs;

    if (addENDTerminal)
    {
        terminals.insert(Vartable::END_);
    }

    Vartable::insertCodeMap(Vartable::STARTTERM_, "_STARTTERM_");
    nonTerminals.insert(Vartable::STARTTERM_);

    rhs.push_back(Terms::create(getStartTerm()));
    if (addENDTerminal)
    {
        rhs.push_back(Terms::create(Vartable::END_));
    }

    std::string fileName = "";
    r = Rule::create(0, fileName, Vartable::STARTTERM_, rhs);
    setStartTerm(startTerm);
    rules.push_back(r);
    firstRule = r;
}

/* **************************************************
 *
 ************************************************** */
void Grammar::print(std::ostream &outStream) const
{
    outStream << "<table border=\"1\"><tr><td>";
    outStream << "Terminals</td><td>";
    std::set<unsigned int>::const_iterator iter;
    bool first = true;
    for (iter = terminals.begin(); iter != terminals.end(); ++iter)
    {
        if (first)
            first = false;
        else
            outStream << ", ";
        outStream << Vartable::codeToIdentifier(*iter);
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
        outStream << Vartable::codeToIdentifier(*iter);
    }
    outStream << "</td></tr><tr><td>";
    outStream << "StartTerm</td><td>";
    if (startTerm)
        outStream << Vartable::codeToIdentifier(startTerm);
    else
        outStream << "NULL";
    outStream << std::endl;
    outStream << "</td></tr><tr><td>Rules</td><td><table>";
    for (ruleList::const_iterator iterRules = rulesBegin(); iterRules != rulesEnd(); ++iterRules)
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
void Grammar::addNonTerminal(unsigned int s)
{
    nonTerminals.insert(s);
}

/* **************************************************
 *
 ************************************************** */
void Grammar::addTerminal(unsigned int s)
{
    terminals.insert(s);
}

/* **************************************************
 *
 ************************************************** */
bool Grammar::isTerminal(unsigned int t) const
{
    std::set<unsigned int>::const_iterator iter = terminals.find(t);
    return (iter != terminals.end());
}

/* **************************************************
 *
 ************************************************** */
bool Grammar::isNonTerminal(unsigned int t) const
{
    std::set<unsigned int>::const_iterator iter = nonTerminals.find(t);
    return (iter != nonTerminals.end());
}

/* **************************************************
 *
 ************************************************** */
void Grammar::analyseTerms(class Parser &parser)
{
    nonTerminals.clear();
    terminals.clear();
    ruleList::const_iterator iterRules;
    for (iterRules = rulesBegin(); iterRules != rulesEnd(); ++iterRules)
    {
        nonTerminals.insert((*iterRules)->getLhs());
    }
    for (iterRules = rulesBegin(); iterRules != rulesEnd(); ++iterRules)
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

                    Parser::entries_map *predToEntries;
                    Parser::entries_map_map::iterator foundCode = parser.getLexicon().find(code);
                    if (foundCode == parser.getLexicon().end())
                    {
                        predToEntries = new std::map<unsigned int, entriesPtr>;
                        predToEntries->insert(std::make_pair(code, Entries::create()));
                        parser.getLexicon().insert(std::make_pair(code, predToEntries));
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
void Grammar::toXML(xmlNodePtr nodeRoot)
{
    xmlNodePtr g = xmlNewChild(nodeRoot, NULL, (const xmlChar *)"GRAMMAR", NULL);
    xmlNodePtr t = xmlNewChild(g, NULL, (const xmlChar *)"TERMINALS", NULL);
    std::set<unsigned int>::const_iterator iter;
    for (iter = terminals.begin(); iter != terminals.end(); ++iter)
    {
        xmlNewChild(t, NULL, (const xmlChar *)"TERM", (const xmlChar *)(Vartable::codeToIdentifier(*iter).c_str()));
    }
    t = xmlNewChild(g, NULL, (const xmlChar *)"NON-TERMINALS", NULL);
    for (iter = nonTerminals.begin(); iter != nonTerminals.end(); ++iter)
    {
        xmlNewChild(t, NULL, (const xmlChar *)"TERM", (const xmlChar *)(Vartable::codeToIdentifier(*iter).c_str()));
    }
    // xmlNodePtr r = xmlNewChild(g, NULL, (const xmlChar*)"RULES", NULL);
    ruleList::const_iterator iterRules;
    for (iterRules = rulesBegin(); iterRules != rulesEnd(); ++iterRules)
    {
        (*iterRules)->toXML(/*r*/);
    }
}
#endif

/* **************************************************
 *
 % ************************************************** */
std::list<rulePtr> *
Grammar::findRules(unsigned int lhs)
{
    std::list<rulePtr> *result = new std::list<rulePtr>;
    ruleList::const_iterator iterRules;
    for (iterRules = rulesBegin(); iterRules != rulesEnd(); iterRules++)
    {
        if (lhs == (*iterRules)->getLhs())
        {
            result->push_back(*iterRules);
        }
    }
    return result;
}
