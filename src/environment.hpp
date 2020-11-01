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

#ifndef ELVEX_ENVIRONMENT_H
#define ELVEX_ENVIRONMENT_H

#include <string>
#include <unordered_map>
#include "shared_ptr.hpp"

class Environment :
        public std::enable_shared_from_this<class Environment> {

public:
    typedef std::unordered_map<std::string, valuePtr> unordered_map;

private:
    Environment();

private:
    unordered_map env;

    void add(const std::string&, valuePtr = valuePtr());

    void remove(const std::string&);

public:
    ~Environment();

    static environmentPtr create(void);

    void add(const bitsetPtr&, valuePtr = valuePtr());

    void add(const environmentPtr&);

    void add(const environmentPtr&, const environmentPtr&);

    void remove(const bitsetPtr&);

    unordered_map::const_iterator begin() const;

    unordered_map::const_iterator end() const;

    size_t size() const;

    void print(std::ostream &) const;

    environmentPtr clone(void) const;

    valuePtr find(const bitsetPtr&) const;

    void replaceVariables(const valuePtr& value, bool &);

    void replaceVariables(const featuresPtr& features, bool &);

    void replaceVariables(const listFeaturesPtr& listFeatures, bool &);

    void replaceVariables(const listPtr& list, bool &);

    void replaceVariables(std::string &string, bool &);
};

#endif // ELVEX_ENVIRONMENT_H
