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

#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <list>
#include <vector>
#include "flags.hh"
#include "id.hh"
#include "serializable.hh"
#include "ipointer.hh"

class Statements:
      public Id, public Flags, public Serializable, public std::enable_shared_from_this<class Statements> {

public:
   typedef std::list<statementPtr> list;

private:
   statementPtr guard;
   list statements;
   Statements(statementPtr);
   void makeSerialString(void);

public:
   ~Statements();
   static statementsPtr create(statementPtr = statementPtr());

   size_t size(void);
   list::const_iterator begin(void) const;
   list::const_iterator end(void) const;

   void addStatement(statementPtr);
   void renameVariables(size_t);
   void print(std::ostream &, unsigned int tabulation = 0, int yetColored = 0) const;
   statementsPtr clone(const std::bitset<Flags::FLAGS> &savedFlags);
  void apply(itemPtr item, class Parser &parser, class Synthesizer *synthesizer, bool &effect);
   void lookingForAssignedInheritedSonFeatures(std::vector<bool> &);
   void enable(itemPtr item, class Synthesizer *synthesizer, bool &effect, bool on);
   bool findVariableElsewhere(statementPtr, bitsetPtr);
};

#endif // STATEMENTS_H
