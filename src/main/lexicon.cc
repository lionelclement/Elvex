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

#include "lexicon.hpp"
#include <utility>
#include <unordered_map>
#include <sstream>
#include "messages.hpp"

std::vector<std::string> Lexicon::emptyList = std::vector<std::string>();

/* **************************************************
 *
 ************************************************** */
Lexicon::Lexicon(std::string name)
    : name(std::move(name))
{
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Lexicon::unordered_map::const_iterator Lexicon::cbegin(void)
{
    return the_map.cbegin();
}

/* **************************************************
 *
 ************************************************** */
Lexicon::unordered_map::const_iterator Lexicon::cend(void)
{
    return the_map.cend();
}

/* **************************************************
 *
 ************************************************** */
std::size_t Lexicon::size(void)
{
    return the_map.size();
}

/* **************************************************
 *
 ************************************************** */
void Lexicon::add(std::string key, std::string value)
{
    // operator[] creates an empty list on the first insertion for a key.
    // Later insertions preserve the order of alternative lexical analyses.
    the_map[key].push_back(std::move(value));
}

/* **************************************************
 *
 ************************************************** */
std::vector<std::string> Lexicon::find(std::string key)
{
    const auto it = the_map.find(key);
    // Return a copy, so callers cannot modify the indexed lexical template.
    return it != the_map.end() ? it->second : emptyList;
}

/* **************************************************
 *
 ************************************************** */
std::size_t Lexicon::count(std::string key)
{
    return the_map.count(key);
}

/* **************************************************
 *
 ************************************************** */
std::string &Lexicon::toString(void) const
{
    static std::string result;
    std::ostringstream oss;
    oss << the_map.size();
    result = oss.str();
    return result;
}
