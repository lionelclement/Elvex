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

#ifndef ELVEX_RULE_H
#define ELVEX_RULE_H

#include <climits>
#include <string>
#include <vector>

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "facade.hpp"
#include "shared_ptr.hpp"

class Rule : public Facade,
             public std::enable_shared_from_this<class Rule>
{

private:
    unsigned int lhs;
    std::vector<termsPtr> rhs;
    statementsPtr statements;
    unsigned int usages;
    std::string filename;
    unsigned int lineno;
    bool trace;
    bool withSpaces;
    bool bidirectional;
    bool permutable;

    Rule(size_t id, unsigned int lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, unsigned int lhs, statementsPtr statements = statementsPtr());

    Rule(unsigned int lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, unsigned int lhs, statementsPtr statements = statementsPtr());

    Rule(unsigned int lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, unsigned int lhs, std::vector<termsPtr> &rhs,
         statementsPtr statements = statementsPtr());

    Rule(size_t id, unsigned int lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, unsigned int lhs, std::vector<termsPtr> &rhs,
         statementsPtr statements = statementsPtr());

public:
    static rulePtr create(size_t id, unsigned int lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, unsigned int lhs,
                          statementsPtr statements = statementsPtr());

    static rulePtr
    create(unsigned int lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, unsigned int lhs, statementsPtr statements = statementsPtr());

    static rulePtr create(unsigned int lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, unsigned int lhs, std::vector<termsPtr> &rhs,
                          statementsPtr statements = statementsPtr());

    static rulePtr create(size_t id, unsigned int lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, unsigned int lhs, std::vector<termsPtr> &rhs,
                          statementsPtr statements = statementsPtr());

    ~Rule();

    unsigned int getLhs(void) const;

    std::vector<termsPtr> &getRhs(void);

    unsigned int getCurrentTerm(void) const;

    termsPtr getCurrentTerms() const;

    termsPtr getTerms(unsigned int) const;

    void setCurrentTerms(termsPtr);

    statementsPtr getStatements(void) const;

    void incUsages(class Generator *);

    void resetUsages(void);

    unsigned int getLineno(void);

    bool getWithSpaces(void) const;

    bool getBidirectional(void) const;

    bool getPermutable(void) const;

    const std::string &getFilename(void) const;

    bool getTrace(void) const;

    void setTrace(bool trace);

    rulePtr clone() const;

    void print(std::ostream &, unsigned int index = UINT_MAX, bool withSemantic = false, bool html = true) const;

    std::string toString() const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

    void addDefaults(void);
};

#endif // ELVEX_RULE_H
