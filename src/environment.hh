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

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <unordered_map>
#include "ipointer.hh"

class Environment:
      public std::enable_shared_from_this<class Environment> {

public:
   typedef std::unordered_map<const std::string, valuePtr, std::hash<std::string>, std::equal_to<std::string> > unordered_map;

private:
   Environment();

private:
   unordered_map env;
   void add(const std::string, valuePtr = valuePtr());
   void remove(const std::string);

public:
   ~Environment();
   static environmentPtr create(void);

   void add(const bitsetPtr, valuePtr = valuePtr());
   void add(const environmentPtr);
   void add(const environmentPtr, const environmentPtr);
   void remove(const bitsetPtr);
   unordered_map::const_iterator begin() const;
   unordered_map::const_iterator end() const;
   const size_t size() const;

   void print(std::ostream &) const;
   environmentPtr clone(void) const;
   valuePtr find(bitsetPtr) const;
   void replaceVariables(valuePtr value, bool &);
   void replaceVariables(featuresPtr features, bool &);
   void replaceVariables(listFeaturesPtr listFeatures, bool &);
   void replaceVariables(listPtr list, bool &);
   void replaceVariables(std::string &string, bool &);
};
#endif // ENVIRONMENT_H
