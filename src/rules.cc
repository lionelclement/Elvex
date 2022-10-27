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
Rules::Rules(void) {
    this->firstRule = nullptr;
    this->startTerm = 0;
    this->idMax = 0;
    NEW
}

/* **************************************************
 *
 ************************************************** */
Rules::~Rules(void) {
    DELETE
    terminals.clear();
    nonTerminals.clear();
    for (list_of_rule::const_iterator iterRules = cbegin(); iterRules != cend(); ++iterRules) {
        rulePtr tmp = *iterRules;
        if (tmp)
            tmp.reset();
    }
    rules.clear();
    if (firstRule) {
        firstRule.reset();
    }
}

/* **************************************************
 *
 ************************************************** */
Rules::set_of_unsigned_int& Rules::getTerminals(void) {
    return terminals;
}

/* **************************************************
 *
 ************************************************** */
Rules::set_of_unsigned_int& Rules::getNonTerminals(void) {
    return nonTerminals;
}

/* **************************************************
 *
 ************************************************** */
const Rules::list_of_rule& Rules::getRules(void) const {
    return rules;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Rules::getStartTerm(void) const {
    return startTerm;
}

/* **************************************************
 *
 ************************************************** */
rulePtr Rules::getFirstRule(void) const {
    return firstRule;
}

/* **************************************************
 *
 ************************************************** */
const unsigned int *Rules::getRefIdMax(void) const {
    return& idMax;
}

/* **************************************************
 *
 ************************************************** */
void Rules::setStartTerm(unsigned int _startTerm) {
    this->startTerm = _startTerm;
}

/* **************************************************
 *
 ************************************************** */
Rules::list_of_rule::const_iterator Rules::cbegin(void) const {
    return rules.cbegin();
}

/* **************************************************
 *
 ************************************************** */
Rules::list_of_rule::const_iterator Rules::cend(void) const {
    return rules.cend();
}

/* **************************************************
 *
 ************************************************** */
void Rules::addRule(rulePtr rule) {
    rules.push_back(rule);
    //std::pair<list_of_rule::iterator, bool> result = rules.insert(rule);
    //return result.second;
}

/* **************************************************
 *
 ************************************************** */
void Rules::addNewStartTerm(bool addENDTerminal) {
    rulePtr r;
    std::vector<termsPtr> rhs;

    if (addENDTerminal) {
        terminals.insert(Vartable::_END_);
    }

    Vartable::insertCodeMap(Vartable::_START_TERM_, "_START_TERM_");
    nonTerminals.insert(Vartable::_START_TERM_);

    rhs.push_back(Terms::create(getStartTerm()));
    if (addENDTerminal) {
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
void Rules::print(std::ostream& outStream) const {
    outStream << "<table border=\"1\"><tr><td>";
    outStream << "Terminals</td><td>";
    set_of_unsigned_int::const_iterator iter;
    bool first = true;
    for (iter = terminals.begin(); iter != terminals.end(); ++iter) {
        if (first)
            first = false;
        else
            outStream << ", ";
        outStream << Vartable::codeToString(*iter);

    }
    outStream << "</td></tr><tr><td>";
    outStream << "NonTerminals</td><td>";
    first = true;
    for (iter = nonTerminals.begin(); iter != nonTerminals.end(); ++iter) {
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
    for (list_of_rule::const_iterator iterRules = cbegin(); iterRules != cend(); ++iterRules) {
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
void Rules::addNonTerminal(unsigned int s) {
    nonTerminals.insert(s);
}

/* **************************************************
 *
 ************************************************** */
void Rules::addTerminal(unsigned int s) {
    terminals.insert(s);
}

/* **************************************************
 *
 ************************************************** */
bool Rules::isTerminal(unsigned int t) const {
    set_of_unsigned_int::const_iterator iter = terminals.find(t);
    return (iter != terminals.end());
}

/* **************************************************
 *
 ************************************************** */
bool Rules::isNonTerminal(unsigned int t) const {
    set_of_unsigned_int::const_iterator iter = nonTerminals.find(t);
    return (iter != nonTerminals.end());
}

/* **************************************************
 *
 ************************************************** */
void Rules::analyseTerms(class Parser& parser) {
    nonTerminals.clear();
    terminals.clear();
    list_of_rule::const_iterator iterRules;
    for (iterRules = cbegin(); iterRules != cend(); ++iterRules) {
        nonTerminals.insert((*iterRules)->getLhs());
    }
    for (iterRules = cbegin(); iterRules != cend(); ++iterRules) {
        unsigned int i;
        for (i = 0; i < (*iterRules)->getRhs().size(); ++i) {
            for (std::vector<unsigned int>::const_iterator term = (*iterRules)->getTerms(i)->cbegin();
                 term != (*iterRules)->getTerms(i)->cend(); ++term) {
                if (nonTerminals.find(*term) == nonTerminals.end()) {
                    unsigned long int code = (*term);
                    terminals.insert(code);

                    Parser::entries_map* predToEntries;
                    Parser::entries_map_map_const_iterator foundCode = parser.findCacheLexicon(code);
                    if (foundCode == parser.cendCacheLexicon()) {
                        predToEntries = new Parser::entries_map;
                        predToEntries->insert(std::make_pair(code, Entries::create()));
                        parser.insertCacheLexicon(std::make_pair(code, predToEntries));
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
void
Rules::toXML(xmlNodePtr nodeRoot)
{
   xmlNodePtr g = xmlNewChild(nodeRoot, NULL, (const xmlChar*)"GRAMMAR", NULL);
   xmlNodePtr t = xmlNewChild(g, NULL, (const xmlChar*)"TERMINALS", NULL);
   set_of_unsigned_int::const_iterator iter;
   for (iter = terminals.begin(); iter != terminals.end(); ++iter) {
      xmlNewChild(t, NULL, (const xmlChar*)"TERM", (const xmlChar*)(Vartable::codeToString(*iter).c_str()));
   }
   t=xmlNewChild(g, NULL, (const xmlChar*)"NON-TERMINALS", NULL);
   for (iter=nonTerminals.begin(); iter != nonTerminals.end(); ++iter) {
      xmlNewChild(t, NULL, (const xmlChar*)"TERM", (const xmlChar*)(Vartable::codeToString(*iter).c_str()));
   }
   //xmlNodePtr r = xmlNewChild(g, NULL, (const xmlChar*)"RULES", NULL);
   //list_of_rule::const_iterator iterRules;
   //for (iterRules = rulesBegin(); iterRules != rulesEnd(); ++iterRules) {
   //   (*iterRules)->toXML(g);
   //}
}
#endif

/* **************************************************
 *
 % ************************************************** */
std::list<rulePtr> *
Rules::findRules(unsigned int lhs) {
    std::list<rulePtr> *result = new std::list<rulePtr>;
    list_of_rule::const_iterator iterRules;
    for (iterRules = cbegin(); iterRules != cend(); iterRules++) {
        if (lhs == (*iterRules)->getLhs()) {
            result->push_back(*iterRules);
        }
    }
    return result;
}
