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

#ifndef ELVEX_ENVIRONMENT_H
#define ELVEX_ENVIRONMENT_H

#include <string>
#include <unordered_map>
#include "serializable.hpp"
#include "shared_ptr.hpp"

/**
 * Bindings of grammar variables to values during feature evaluation.
 * Unification updates an environment, so alternatives must use independent copies.
 */
class Environment : public Serializable,
                    public std::enable_shared_from_this<class Environment>
{

public:
    typedef std::unordered_map<std::string, valuePtr> unordered_map;

private:
    unordered_map env;

    bool add(statementPtr from, const std::string &, valuePtr, bool verbose, bool override);

    bool remove(const std::string &);

    /** Emit the existing verbose diagnostic for an incompatible variable binding. */
    void warnBindingConflict(statementPtr statementRoot, const std::string &key) const;

public:
    Environment();

    ~Environment();

    static environmentPtr create(void);

    /** Bind a variable code; override controls replacement of a binding. */
    bool add(statementPtr from, uint32_t, valuePtr, bool verbose, bool override);

    /** Merge another environment into this one. */
    bool add(statementPtr from, const environmentPtr &, bool verbose, bool override);

    bool add(statementPtr from, const environmentPtr &, const environmentPtr &, bool verbose, bool override);

    bool remove(uint32_t);

    unordered_map::const_iterator begin() const;

    unordered_map::const_iterator end() const;

    bool empty() const;

    void toHTML(std::ostream &) const;

    /** Clone bindings before exploring an alternative that may mutate them. */
    environmentPtr clone(statementPtr from, bool verbose) const;

    valuePtr get(const uint32_t) const;

    /**
     * Substitute known bindings into a feature structure in place.
     * The bool reference reports whether a substitution changed it.
     */
    void replaceVariables(const featuresPtr &, bool &);

    /** Resolve bound variables in a value; update the change flag. */
    void replaceVariables(const valuePtr &, bool &);

    void replaceVariables(const pairpPtr &, bool &);

    void replaceVariables(std::string &, bool &);

protected:
    void makeCoreSerialString() override;
};

#endif // ELVEX_ENVIRONMENT_H
