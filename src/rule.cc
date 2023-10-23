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
#include <sstream>
#include "rule.hpp"
#include "terms.hpp"
#include "statements.hpp"
#include "messages.hpp"
#include "generator.hpp"
#include "vartable.hpp"

/* ************************************************************
 *
 ************************************************************ */
Rule::Rule(uint32_t id, uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint32_t lhs, std::vector<termsPtr> &rhs,
           statementsPtr statements)
    : Facade(id)
{
    this->lineno = lineno;
    this->filename = filename;
    this->withSpaces = withSpaces;
    this->bidirectional = bidirectional;
    this->permutable = permutable;
    this->lhs = lhs;
    this->rhs = rhs;
    this->statements = statements;
    this->usages = 0;
    this->trace = false;
    NEW;
}

/* ************************************************************
 *
 ************************************************************ */
Rule::Rule(uint32_t id, uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint32_t lhs, statementsPtr statements)
    : Facade(id)
{
    this->lineno = lineno;
    this->filename = filename;
    this->withSpaces = withSpaces;
    this->bidirectional = bidirectional;
    this->permutable = permutable;
    this->lhs = lhs;
    this->statements = statements;
    this->usages = 0;
    this->trace = false;
    NEW;
}

/* ************************************************************
 *
 ************************************************************ */
Rule::Rule(uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint32_t lhs, std::vector<termsPtr> &rhs, statementsPtr statements)
    : Rule(0, lineno, filename, withSpaces, bidirectional, permutable, lhs, rhs, statements)
{
}

/* ************************************************************
 *
 ************************************************************ */
Rule::Rule(uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint32_t lhs, statementsPtr statements)
    : Rule(0, lineno, filename, withSpaces, bidirectional, permutable, lhs, statements)
{
}

/* ************************************************************
 *
 ************************************************************ */
rulePtr Rule::create(uint32_t id, uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint32_t lhs, std::vector<termsPtr> &rhs,
                     statementsPtr statements)
{
    return std::make_shared<Rule>(id, lineno, filename, withSpaces, bidirectional, permutable, lhs, rhs, statements);
}

/* ************************************************************
 *
 ************************************************************ */
rulePtr Rule::create(uint32_t id, uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint32_t lhs, statementsPtr statements)
{
    return std::make_shared<Rule>(id, lineno, filename, withSpaces, bidirectional, permutable, lhs, statements);
}

/* ************************************************************
 *
 ************************************************************ */
rulePtr Rule::create(uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint32_t lhs, std::vector<termsPtr> &rhs,
                     statementsPtr statements)
{
    return std::make_shared<Rule>(lineno, filename, withSpaces, bidirectional, permutable, lhs, rhs, statements);
}

/* ************************************************************
 *
 ************************************************************ */
rulePtr Rule::create(uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint32_t lhs, statementsPtr statements)
{
    return std::make_shared<Rule>(lineno, filename, withSpaces, bidirectional, permutable, lhs, statements);
}

/* ************************************************************
 *
 ************************************************************ */
Rule::~Rule()
{
    DELETE;
    for (std::vector<termsPtr>::iterator term = rhs.begin(); term != rhs.end(); term++)
        if (*term)
            term->reset();
    if (statements)
    {
        statements.reset();
    }
}

/* ************************************************************
 *
 ************************************************************ */
uint32_t Rule::getLhs(void) const
{
    return lhs;
}

/* ************************************************************
 *
 ************************************************************ */
std::vector<termsPtr> &Rule::getRhs(void)
{
    return this->rhs;
}

/* ************************************************************
 *
 ************************************************************ */
termsPtr Rule::getTerms(size_t index) const
{
    return this->rhs[index];
}

/* ************************************************************
 *
 ************************************************************ */
statementsPtr Rule::getStatements(void) const
{
    return statements;
}

/* ************************************************************
 *
 ************************************************************ */
bool Rule::getWithSpaces(void) const
{
    return withSpaces;
}

/* ************************************************************
 *
 ************************************************************ */
bool Rule::getBidirectional(void) const
{
    return bidirectional;
}

/* ************************************************************
 *
 ************************************************************ */
bool Rule::getPermutable(void) const
{
    return permutable;
}

/* ************************************************************
 *
 ************************************************************ */
void Rule::incUsages(class Generator *synthesizer)
{
    if (++usages > synthesizer->getMaxUsages())
    {
        throw fatal_exception("too much usages of the same rule: " + this->toString());
    }
}

/* ************************************************************
 *
 ************************************************************ */
void Rule::resetUsages(void)
{
    usages = 0;
}

/* ************************************************************
 *
 ************************************************************ */
uint32_t Rule::getLineno(void)
{
    return lineno;
}

/* ************************************************************
 *
 ************************************************************ */
const std::string &Rule::getFilename(void) const
{
    return filename;
}

/* **************************************************
 *
 ************************************************** */
bool Rule::getTrace(void) const
{
    return trace;
}

/* **************************************************
 *
 ************************************************** */
void Rule::setTrace(bool _trace)
{
    this->trace = _trace;
}

/***************************
 *
 ***************************/
rulePtr Rule::clone() const
{
    std::vector<termsPtr> rhsCopy;
    for (size_t i = 0; i < rhs.size(); ++i){
        rhsCopy.push_back(rhs[i]->clone());
        //rhsCopy.push_back(rhs[i]);
    }
    rulePtr rule = Rule::create(this->getId(), this->lineno, this->filename, this->withSpaces, this->bidirectional, this->permutable, lhs, rhsCopy, statements);
    rule->usages = usages;
    rule->trace = trace;
    return rule;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void Rule::toXML(xmlNodePtr nodeRoot)
{
    xmlNodePtr r = xmlNewChild(nodeRoot, NULL, (const xmlChar *)"RULE", NULL);
    // xmlNodePtr hs =
    xmlNewChild(r, NULL, (const xmlChar *)"LHS", NULL);
    /*
    lhs->toXML(hs);
    hs = xmlNewChild(r, NULL, (const xmlChar*)"RHS", NULL);
    for(size_t i = 0; i < rhs.size(); ++i){
     for (featuresVector<termsPtr>::const_iterator term=rhs[i]->begin();
     term != rhs[i]->end();
     term++) {
    (*term)->toXML(hs);
       }
    }
    */
}
#endif

/* ************************************************************
 *
 ************************************************************ */
void Rule::print(std::ostream &outStream, uint8_t index, bool withSemantic, bool html) const
{
    std::string space = (html ? "&nbsp;" : " ");
    bool first = true;
    outStream << Vartable::codeToName(lhs) << space << "→" << space;
    for (size_t i = 0; i < rhs.size(); i++)
    {
        if (first)
            first = false;
        else
            outStream << space;
        if (index == i)
            outStream << "•" << space;
        rhs[i]->print(outStream);
    }
    if (index == rhs.size())
        outStream << space << "•";
    if (withSemantic)
    {
        statementsPtr stms = getStatements();
        if (stms)
            stms->print(outStream, 5, 0, 0x000000u, 0xFFFFFFu, true, "{", "}", "");
        outStream << (html ? "<BR>" : "\n");
    }
}

/* ************************************************************
 *
 ************************************************************ */
void Rule::makeSerialString() 
{
    std::ostringstream stream;
    stream << std::hex << (int)lhs << ' ' ;
    for (size_t i = 0; i < rhs.size(); ++i){
        termsPtr terms = rhs[i];
        if (terms->isOptional())
            stream << '[';
        for (auto term = terms->begin(); term != terms->end(); ++term){
            stream << '|' << std::hex << (int)*term;
        }
    }
    // statementsPtr stms = getStatements();
    // if (stms){
    //     stream << stms->peekSerialString();
    // } else {
    //     stream << '#';
    // }
    // stream.flush();
    serialString = stream.str();
    
}

/* **************************************************
 *
 ************************************************** */
std::string Rule::toString() const
{
    std::stringstream s;
    print(s, UINT8_MAX, false, false);
    return s.str();
}
