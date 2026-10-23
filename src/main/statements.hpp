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

#ifndef ELVEX_STATEMENTS_H
#define ELVEX_STATEMENTS_H

#include <list>
#include <vector>
#include "facade.hpp"
#include "serializable.hpp"
#include "shared_ptr.hpp"
#include "parser.hpp"
#include "generator.hpp"

/**
 * Ordered block of grammar statements attached to a rule or item.
 * A block can be enabled, evaluated and cloned for an alternative.
 */
class Statements : public Facade,
                   public Serializable,
                   public std::enable_shared_from_this<class Statements>
{

public:
    typedef std::list<statementPtr> list_statement;

private:
    statementPtr guard;

    list_statement statements;

    Statements(const statementPtr &);

    /** Keep the original HTML indentation in diagnostic output. */
    static void printIndent(std::ostream &out, uint8_t tabulation, bool enabled);

    /** Render an item only when action tracing is enabled. */
    static void traceItem(Item *item, Generator *synthesizer, const char *heading);

    /** Apply the guard once; return true if it rejects the item. */
    bool applyGuard(Item *item, Parser &parser, Generator *synthesizer,
                    bool &effect, bool verbose);

    /** Refresh enablement of pending statements before each application pass. */
    void refreshEnablement(Item *item, Generator *synthesizer);

    /** Run enabled statements; return true when a statement rejects the item. */
    bool applyEnabled(Item *item, Parser &parser, Generator *synthesizer,
                      bool &effect, bool verbose, bool &localEffect);

    /** Mark the block SEEN only once every contained statement is SEEN. */
    void markSeenWhenComplete();

public:
    ~Statements();

    void makeCoreSerialString(void);

    static statementsPtr create(const statementPtr & = statementPtr());

    size_t size(void);

    list_statement::const_iterator begin(void);

    list_statement::const_iterator end(void);

    list_statement::const_iterator cbegin(void) const;

    list_statement::const_iterator cend(void) const;

    void addStatement(const statementPtr &);

    void renameVariables(uint32_t code);

    void print(std::ostream &outStream, uint8_t tabulationLenght, uint8_t tabulation, uint32_t color, uint32_t bgcolor, bool ln, std::string leftSep, std::string rightSep, std::string sep) const;

    /** Copy the statement block while retaining the selected flags. */
    statementsPtr clone(const std::bitset<MAX_FLAGS> &savedFlags);

    /** Evaluate enabling conditions before applying statement effects. */
    void testEnable(class Item *item, class Generator *synthesizer, bool &effect, bool on);

    /**
     * Execute the statement block in order for an item.
     * The effect flag reports whether evaluation changed its state.
     */
    void apply(class Item *item, Parser &parser, Generator *synthesizer, bool &effect, bool verbose);

};

#endif // ELVEX_STATEMENTS_H
