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
    uint16_t lhs;
    std::vector<termsPtr> rhs;
    statementsPtr statements;
    uint32_t usages;
    std::string filename;
    uint32_t lineno;
    bool trace;
    bool withSpaces;
    bool bidirectional;
    bool permutable;

    Rule(uint32_t id, uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint16_t lhs, statementsPtr statements = statementsPtr());

    Rule(uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint16_t lhs, statementsPtr statements = statementsPtr());

    Rule(uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint16_t lhs, std::vector<termsPtr> &rhs,
         statementsPtr statements = statementsPtr());

    Rule(uint32_t id, uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint16_t lhs, std::vector<termsPtr> &rhs,
         statementsPtr statements = statementsPtr());

public:
    static rulePtr create(uint32_t id, uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint16_t lhs,
                          statementsPtr statements = statementsPtr());

    static rulePtr
    create(uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint16_t lhs, statementsPtr statements = statementsPtr());

    static rulePtr create(uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint16_t lhs, std::vector<termsPtr> &rhs,
                          statementsPtr statements = statementsPtr());

    static rulePtr create(uint32_t id, uint32_t lineno, std::string filename, bool withSpaces, bool bidirectional, bool permutable, uint16_t lhs, std::vector<termsPtr> &rhs,
                          statementsPtr statements = statementsPtr());

    ~Rule();

    uint16_t getLhs(void) const;

    std::vector<termsPtr> &getRhs(void);

    //uint16_t getCurrentTerm(void) const;

    //termsPtr getCurrentTerms() const;

    termsPtr getTerms(size_t) const;

    //void setCurrentTerms(termsPtr);

    statementsPtr getStatements(void) const;

    void incUsages(class Generator *);

    void resetUsages(void);

    uint32_t getLineno(void);

    bool getWithSpaces(void) const;

    bool getBidirectional(void) const;

    bool getPermutable(void) const;

    const std::string &getFilename(void) const;

    bool getTrace(void) const;

    void setTrace(bool trace);

    rulePtr clone() const;

    void print(std::ostream &, uint8_t index = UINT8_MAX, bool withSemantic = false, bool html = true) const;

    std::string toString() const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

};

#endif // ELVEX_RULE_H
