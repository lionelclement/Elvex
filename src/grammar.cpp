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

#include "grammar.h"
#include "term.h"
#include "terms.h"
#include "vartable.h"
#include "messages.h"
#include "parser.h"
#include "entries.h"
#include "rule.h"

/* **************************************************
 *
 ************************************************** */
Grammar::Grammar(void) {
    this->firstRule = NULL;
    this->startTerm = NULL;
    this->idMax = 0;
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Grammar::~Grammar(void) {
    DELETE;
    terminals.clear();
    nonTerminals.clear();
    for (ruleList::const_iterator iterRules = rulesBegin(); iterRules != rulesEnd(); ++iterRules) {
        rulePtr tmp = *iterRules;
        if (tmp)
            tmp.reset();
    }
    rules.clear();
    if (startTerm) {
        startTerm.reset();
    }
    if (firstRule) {
        firstRule.reset();
    }
}

/* **************************************************
 *
 ************************************************** */
std::set<unsigned int> &Grammar::getTerminals(void) {
    return terminals;
}

/* **************************************************
 *
 ************************************************** */
std::set<unsigned int> &Grammar::getNonTerminals(void) {
    return nonTerminals;
}

/* **************************************************
 *
 ************************************************** */
const Grammar::ruleList &Grammar::getRules(void) const {
    return rules;
}

/* **************************************************
 *
 ************************************************** */
termPtr Grammar::getStartTerm(void) const {
    return startTerm;
}

/* **************************************************
 *
 ************************************************** */
rulePtr Grammar::getFirstRule(void) const {
    return firstRule;
}

/* **************************************************
 *
 ************************************************** */
const unsigned int *Grammar::getRefIdMax(void) const {
    return &idMax;
}

/* **************************************************
 *
 ************************************************** */
void Grammar::setStartTerm(termPtr startTerm) {
    this->startTerm = startTerm;
}

/* **************************************************
 *
 ************************************************** */
Grammar::ruleList::const_iterator Grammar::rulesBegin(void) const {
    return rules.begin();
}

/* **************************************************
 *
 ************************************************** */
Grammar::ruleList::const_iterator Grammar::rulesEnd(void) const {
    return rules.end();
}

/* **************************************************
 *
 ************************************************** */
void Grammar::addRule(rulePtr rule) {
    rules.push_back(rule);
    //std::pair<ruleList::iterator, bool> result = rules.insert(rule);
    //return result.second;
}

/* **************************************************
 *
 ************************************************** */
void Grammar::addNewStartTerm(bool addENDTerminal) {
    rulePtr r;
    std::vector<termsPtr> rhs;

    if (addENDTerminal) {
        terminals.insert(Vartable::_END_);
    }

    Vartable::insertCodeMap(Vartable::_STARTTERM_, "_STARTTERM_");
    nonTerminals.insert(Vartable::_STARTTERM_);

    rhs.push_back(Terms::create(getStartTerm()));
    if (addENDTerminal) {
        rhs.push_back(Terms::create(Term::create(Vartable::_END_)));
    }

    termPtr startTerm = Term::create(Vartable::_STARTTERM_);
    std::string fileName = "";
    r = Rule::create(0, fileName, startTerm, rhs);
    setStartTerm(startTerm);
    rules.push_back(r);
    firstRule = r;
}

/* **************************************************
 *
 ************************************************** */
void Grammar::print(std::ostream &outStream) const {
    outStream << "<table border=\"1\"><tr><td>";
    outStream << "Terminals</td><td>";
    std::set<unsigned int>::const_iterator iter;
    bool first = true;
    for (iter = terminals.begin(); iter != terminals.end(); ++iter) {
        if (first)
            first = false;
        else
            outStream << ", ";
        outStream << Vartable::codeToIdentifier(*iter);

    }
    outStream << "</td></tr><tr><td>";
    outStream << "NonTerminals</td><td>";
    first = true;
    for (iter = nonTerminals.begin(); iter != nonTerminals.end(); ++iter) {
        if (first)
            first = false;
        else
            outStream << ", ";
        outStream << Vartable::codeToIdentifier(*iter);

    }
    outStream << "</td></tr><tr><td>";
    outStream << "StartTerm</td><td>";
    if (startTerm)
        startTerm->print(outStream);
    else
        outStream << "NULL";
    outStream << std::endl;
    outStream << "</td></tr><tr><td>Rules</td><td><table>";
    for (ruleList::const_iterator iterRules = rulesBegin(); iterRules != rulesEnd(); ++iterRules) {
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
void Grammar::addNonTerminal(unsigned int s) {
    nonTerminals.insert(s);
}

/* **************************************************
 *
 ************************************************** */
void Grammar::addTerminal(unsigned int s) {
    terminals.insert(s);
}

/* **************************************************
 *
 ************************************************** */
bool Grammar::isTerminal(termPtr t) const {
    std::set<unsigned int>::const_iterator iter = terminals.find(t->getCode());
    return (iter != terminals.end());
}

/* **************************************************
 *
 ************************************************** */
bool Grammar::isNonTerminal(termPtr t) const {
    std::set<unsigned int>::const_iterator iter = nonTerminals.find(t->getCode());
    return (iter != nonTerminals.end());
}

/* **************************************************
 *
 ************************************************** */
void Grammar::analyseTerms(class Parser &parser) {
    nonTerminals.clear();
    terminals.clear();
    ruleList::const_iterator iterRules;
    for (iterRules = rulesBegin(); iterRules != rulesEnd(); ++iterRules) {
        nonTerminals.insert((*iterRules)->getLhs()->getCode());
    }
    for (iterRules = rulesBegin(); iterRules != rulesEnd(); ++iterRules) {
        unsigned int i;
        for (i = 0; i < (*iterRules)->getRhs().size(); ++i) {
            for (std::vector<termPtr>::const_iterator term = (*iterRules)->getTerms(i)->begin();
                 term != (*iterRules)->getTerms(i)->end(); ++term) {
                if (nonTerminals.find((*term)->getCode()) == nonTerminals.end()) {
                    unsigned long int code = (*term)->getCode();
                    terminals.insert(code);

                    Parser::entries_map *predToEntries;
                    Parser::entries_map_map::iterator foundCode = parser.getLexicon().find(code);
                    if (foundCode == parser.getLexicon().end()) {
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
void
Grammar::toXML(xmlNodePtr nodeRoot)
{
   xmlNodePtr g=xmlNewChild(nodeRoot, NULL, (const xmlChar*)"GRAMMAR", NULL);
   xmlNodePtr t=xmlNewChild(g, NULL, (const xmlChar*)"TERMINALS", NULL);
   std::set<unsigned int>::const_iterator iter;
   for (iter=terminals.begin(); iter != terminals.end(); ++iter) {
      xmlNewChild(t, NULL, (const xmlChar*)"TERM", (const xmlChar*)(Vartable::codeToIdentifier(*iter).c_str()));
   }
   t=xmlNewChild(g, NULL, (const xmlChar*)"NON-TERMINALS", NULL);
   for (iter=nonTerminals.begin(); iter != nonTerminals.end(); ++iter) {
      xmlNewChild(t, NULL, (const xmlChar*)"TERM", (const xmlChar*)(Vartable::codeToIdentifier(*iter).c_str()));
   }
   xmlNodePtr r=xmlNewChild(g, NULL, (const xmlChar*)"RULES", NULL);
   ruleList::const_iterator iterRules;
   for (iterRules=rulesBegin(); iterRules != rulesEnd(); ++iterRules) {
      (*iterRules)->toXML(r);
   }
}
#endif

/* **************************************************
 *
 % ************************************************** */
std::list<rulePtr> *
Grammar::findRules(termPtr lhs) {
    std::list<rulePtr> *result = new std::list<rulePtr>;
    ruleList::const_iterator iterRules;
    for (iterRules = rulesBegin(); iterRules != rulesEnd(); iterRules++) {
        if (lhs->getCode() == (*iterRules)->getLhs()->getCode()) {
            result->push_back(*iterRules);
        }
    }
    return result;
}
