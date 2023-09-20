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

#include "lexicon.hpp"
#include <unordered_map>
#include <sstream>
#include "messages.hpp"

// std::vector<std::string>* Lexicon::emptyList = new std::vector<std::string>();
std::vector<std::string> Lexicon::emptyList = std::vector<std::string>();

/* **************************************************
 *
 ************************************************** */
Lexicon::Lexicon(void)
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
void Lexicon::add(std::string key, const std::string value)
{
    unordered_map::iterator it = the_map.find(key);
    if (it != the_map.end())
        (*it).second.push_back(value);
    else
    {
        std::vector<std::string> list = std::vector<std::string>();
        list.push_back(value);
        the_map[key] = list;
    }
}

/* **************************************************
 *
 ************************************************** */
std::vector<std::string> Lexicon::find(const std::string key)
{
    unordered_map::const_iterator it = the_map.find(key);
    if (it != the_map.end())
    {
        return (*it).second;
    }
    else
    {
        return emptyList;
    }
}

/* **************************************************
 *
 ************************************************** */
std::size_t Lexicon::count(const std::string key)
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
