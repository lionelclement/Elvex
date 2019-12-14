/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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

#ifndef PATTERN_H
#define LEXICON_H

#include <string>
#include <list>
#include <unordered_map>

class Lexicon {

public:
   typedef std::unordered_map<const std::string,
			      std::list<std::string> *,
			      std::hash<std::string>,
			      std::equal_to<std::string>,
         std::allocator<std::pair<const std::string, std::list<std::string> *>>> Unordered_map;
   Unordered_map unordered_map;
   static std::list<std::string> *emptyList;

   Lexicon(void);
   void add(const std::string key, std::string value);
   std::list<std::string> *find(const std::string key);
   std::string &toString(void) const;

};

#endif // PATTERN_H

