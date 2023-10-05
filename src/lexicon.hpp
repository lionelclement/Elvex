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

#ifndef ELVEX_LEXICON_H
#define ELVEX_LEXICON_H

#include <string>
#include <vector>
#include <unordered_map>

class Lexicon
{

public:
    typedef std::unordered_map<const std::string,
                               std::vector<std::string>,
                               std::hash<std::string>,
                               std::equal_to<std::string>,
                               std::allocator<std::pair<const std::string, std::vector<std::string> > > >
        unordered_map;

private:
    std::string name;

    unordered_map the_map;

    static std::vector<std::string> emptyList;

public:
    Lexicon(std::string name);

    unordered_map::const_iterator cbegin(void);

    unordered_map::const_iterator cend(void);

    std::size_t size(void);

    void add(std::string key, std::string value);

    std::vector<std::string> find(std::string key);

    std::size_t count(std::string key);

    std::string &toString(void) const;
};

#endif // ELVEX_LEXICON_H
