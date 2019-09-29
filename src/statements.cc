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

#include "statements.hh"
#include "environment.hh"
#include "messages.hh"
#include "item.hh"
#include "statement.hh"
#include "synthesizer.hh"
#include "listfeatures.hh"

/* **************************************************
 *
 ************************************************** */
Statements::Statements(statementPtr statement)
{
  NEW;
  if (statement)
    statements.push_front(statement);
}

/* **************************************************
 *
 ************************************************** */
Statements::~Statements()
{ 
  for (std::list<statementPtr >::iterator i = statements.begin(); i != statements.end(); ++i)
    i->reset();
  DELETE;
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Statements::create (statementPtr statement)
{
  return statementsPtr( new Statements(statement) );
}

/* **************************************************
 *
 ************************************************** */
std::list<statementPtr >&  Statements::getStatements(void)
{
  return this->statements;
}


/* **************************************************
 *
 ************************************************** */
size_t Statements::size(void)
{
  return this->statements.size();
}

/* **************************************************
 *
 ************************************************** */
std::list<statementPtr >::const_iterator Statements::begin(void) const 
{
  return this->statements.begin();
}

/* **************************************************
 *
 ************************************************** */
std::list<statementPtr >::const_iterator Statements::end(void) const 
{
  return this->statements.end();
}

/* **************************************************
 *
 ************************************************** */
void 
Statements::addStatement(statementPtr statement)
{
  if (statement->isGuard())
    this->guard = statement;
  else
    this->statements.push_back(statement);
}

/* **************************************************
 *
 ************************************************** */
void 
Statements::print(std::ostream& outStream, int left) const 
{
  for (int j=1 ; j<=left ; ++j)
    outStream << "&nbsp;";
  outStream << "{<DIV>";
  left+=3;
  if (guard)
    guard->print(outStream, left);
  for (std::list<statementPtr >::const_iterator i = statements.begin(); i != statements.end(); ++i)
    (*i)->print(outStream, left);
  left-=3;
  for (int j=1 ; j<=left ; ++j)
    outStream << "&nbsp;";
  outStream << "}</DIV>";
}

/* **************************************************
 *
 ************************************************** */
const std::string
Statements::makeSerializationId()
{
  serialId = '{';
  if (guard)
    serialId += guard->serialize() + ';';
  for (std::list<statementPtr >::const_iterator i = statements.begin(); i != statements.end(); ++i)
    serialId += (*i)->serialize() + ';';
  serialId += '}';
  return serialId;
}

/* **************************************************
 *
 ************************************************** */
statementsPtr  
Statements::clone(const std::bitset<NBRFLAGS>& savedFlags) const 
{
  statementsPtr statements = Statements::create();
  statements->guard = (guard) ? guard->clone(savedFlags) : statementPtr();
  for (std::list<statementPtr >::const_iterator i = this->statements.begin(); i != this->statements.end(); ++i)
    statements->addStatement((*i)->clone(savedFlags));
  return statements;
}

/* **************************************************
 *
 ************************************************** */
void
Statements::renameVariables(unsigned int i)
{
  if (guard)
    guard->renameVariables(i);
  for (std::list<statementPtr >::const_iterator j = this->statements.begin(); j != this->statements.end(); ++j)
    (*j)->renameVariables(i);
}

/* **************************************************
 * Applique l'ensemble des instructions
 ************************************************** */
void
Statements::apply(itemPtr item, bool &effect, bool trace)
{
  if (item->isSetFlags(Flags::BOTTOM))
    return;

  if (guard){
    // Look for guard
    bool change = false;
    guard->enable(guard, item, change, false);
    if (change)
      guard->enable(guard, item, change, true);
    if (!guard->isSetFlags(Flags::SEEN | DISABLED)){
      bool result = true;
      guard->apply(item, result, effect, trace);
      if (!result){
	guard->addFlags(Flags::BOTTOM);
	item->addFlags(Flags::BOTTOM);
      }
    }
  }
  
  if (item->isUnsetFlags(Flags::BOTTOM)){
    // continue
    for (std::list<statementPtr >::iterator statement = statements.begin();
	 statement != statements.end();
	 ++statement){
      if (isUnsetFlags(Flags::SEEN)){
	bool change = false;
	(*statement)->enable(*statement, item, change, false);
	if (change)
	  (*statement)->enable(*statement, item, change, true);
	if ((*statement)->isSetFlags(Flags::SEEN | DISABLED))
	  continue;
	if (item->getEnvironment() && item->getEnvironment()->size()==0){
	  item->getEnvironment().reset();
	  item->setEnvironment(environmentPtr());
	  }
	bool result = true;
	(*statement)->apply(item, result, effect, trace);
	if (!result){
	  (*statement)->addFlags(Flags::BOTTOM);
	  item->addFlags(Flags::BOTTOM);
	  break;
	}
      }
    }
  }
}

/* **************************************************
 *
 ************************************************** */
void
Statements::lookingForAssignedInheritedSonFeatures(std::vector< bool > &assignedInheritedSonFeatures)
{
  FATAL_ERROR;
  for (std::list<statementPtr >::const_iterator i = statements.begin(); i != statements.end(); ++i){
    std::cerr << '.';
    (*i)->lookingForAssignedInheritedSonFeatures(assignedInheritedSonFeatures);
  }
}

/* **************************************************
 *
 ************************************************** */
void 
Statements::enable(itemPtr item, bool &effect, bool on)
{
  if (guard)
    guard->enable(guard, item, effect, on);
  for (std::list<statementPtr >::const_iterator i = statements.begin(); i != statements.end(); ++i){
    //std::cerr << '.';
    (*i)->enable(*i, item, effect, on);
  }
}

/* **************************************************
 *
 ************************************************** */
bool
Statements::findVariableElsewhere(statementPtr o, bitsetPtr variable){
  FATAL_ERROR;
  for (std::list<statementPtr >::const_iterator i = statements.begin(); i != statements.end(); ++i){
    if ((*i) == o)
      continue;
    if ((*i)->findVariable(variable))
      return true;
  }
  return false;
}

