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

#ifndef ELVEX_ENVIRONMENT_H
#define ELVEX_ENVIRONMENT_H

#include <string>
#include <unordered_map>
#include "shared_ptr.hpp"

class Environment : public std::enable_shared_from_this<class Environment>
{

public:
    typedef std::unordered_map<std::string, valuePtr> unordered_map;

private:
    Environment();

private:
    unordered_map env;

    bool add(statementPtr from, const std::string &, valuePtr, bool verbose);

    bool remove(const std::string &);

public:
    ~Environment();

    static environmentPtr create(void);

    bool add(statementPtr from, uint32_t, valuePtr, bool verbose);

    bool add(statementPtr from, const environmentPtr &, bool verbose);

    bool add(statementPtr from, const environmentPtr &, const environmentPtr &, bool verbose);

    bool remove(uint32_t);

    unordered_map::const_iterator begin() const;

    unordered_map::const_iterator end() const;

    bool empty() const;

    void print(std::ostream &) const;

    environmentPtr clone(statementPtr from, bool verbose) const;

    valuePtr find(const uint32_t) const;

    void replaceVariables(const valuePtr &, bool &);

    void replaceVariables(const featuresPtr &, bool &);

    //void replaceVariables(const listFeaturesPtr &, bool &);

    void replaceVariables(const pairpPtr &, bool &);

    void replaceVariables(std::string &, bool &);
};

#endif // ELVEX_ENVIRONMENT_H
