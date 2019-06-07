/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2018 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: Lionel Clément,
 * Labri -- 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#include "rule.hh"
#include "term.hh"
#include "terms.hh"
#include "statements.hh"
#include "messages.hh"
#include "synthesizer.hh"

/* ************************************************************
 *
 ************************************************************ */
Rule::Rule(unsigned int lineno, std::string filename, class Term *lhs, std::vector<class Terms *> &rhs, statementsPtr statements)
{
  NEW;
  this->lhs = lhs;
  this->rhs = rhs;
  this->statements = statements;
  this->usages = 0;
  this->lineno = lineno;
  this->filename = filename;
}

/* ************************************************************
 *
 ************************************************************ */
Rule::Rule(unsigned int lineno, std::string filename, class Term *lhs, statementsPtr statements)
{
  NEW;
  this->lhs = lhs;
  this->statements = statements;
  this->usages = 0;
  this->lineno = lineno;
  this->filename = filename;
}

/* ************************************************************
 *
 ************************************************************ */
Rule::~Rule()
{
  /*
  for (std::vector <class Terms *>::iterator term=rhs.begin();
       term != rhs.end();
       term++)
    if (*term)
      delete *term;
  rhs.clear();
  if(lhs){
    delete lhs;
    lhs=NULL;

  }
  if (statements){
    delete statements;
    statements=NULL;

  }
  */
  //DELETE;
}

/* **************************************************
 *
 ************************************************** */
void Rule::setId(idType id)
{
  this->id = id;
}

/* ************************************************************
 *
 ************************************************************ */
class Term *Rule::getLhs(void) const 
{
  return lhs;
}

/* ************************************************************
 *
 ************************************************************ */
std::vector<class Terms *> &Rule::getRhs(void)
{
  return this->rhs;
}

/* ************************************************************
 *
 ************************************************************ */
class Terms *
Rule::getTerms(unsigned int index) const
{
  return this->rhs[index];
}

/* ************************************************************
 *
 ************************************************************ */
statementsPtr Rule::getStatements(void) const
{
  return statements;
}

/* ************************************************************
 *
 ************************************************************ */
void Rule::incUsages(class Synthesizer *synthesizer)
{
  if (++usages > synthesizer->getMaxUsages()) {
    FATAL_ERROR_MSG("maxUsages");
  }
}

/* ************************************************************
 *
 ************************************************************ */
void Rule::resetUsages(void)
{
  usages = 0;
}

/* ************************************************************
 *
 ************************************************************ */
const unsigned int Rule::getLineno(void) const 
{
  return lineno;
}

/* ************************************************************
 *
 ************************************************************ */
const std::string &Rule::getFilename(void) const 
{
  return filename;
}

/************************************************************
 *
 ************************************************************ */
const bool Rule::Less::operator()(const class Rule *r1, const class Rule *r2) const
{
  if (r1->getId() != r2->getId())
    return r1->getId() < r2->getId();
  else
    return false;
}

/* ************************************************************
 *
 ************************************************************ */
void
Rule::print(std::ostream& outStream, unsigned int index, bool withSemantic, bool html) const
{
  std::string space = (html ? "&nbsp;" : " ");
  bool first = true;
  lhs->print(outStream);
  outStream << space << (html?"→":"->") << space;
  for(unsigned int i=0; i<rhs.size(); i++){
    if (first)
      first=false;
    else
      outStream << space;
    if (index==i)
      outStream << (html?"•":".") << space;
    rhs[i]->print(outStream);
  }
  if (index==rhs.size())
    outStream << space << (html?"•":".");
  if (withSemantic){
    statementsPtr stms=getStatements();
    if (stms)
      stms->print(outStream);
    outStream << (html?"<BR>":"\n");
  }
}

/***************************
 *
 ***************************/
class Rule * 
Rule::clone() const 
{
  std::vector<class Terms *> rhsCopy;
  for(unsigned int i=0; i<rhs.size(); ++i)
    rhsCopy.push_back(rhs[i]->clone());
  class Rule *rule = new Rule(this->lineno, this->filename, lhs, rhsCopy, statements);
  rule->usages = usages;
  rule->setId(this->getId());
  return rule;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Rule::toXML(xmlNodePtr nodeRoot)
{
  // xmlNodePtr r=xmlNewChild(nodeRoot, NULL, (const xmlChar*)"RULE", NULL);
  // xmlSetProp(r, (xmlChar*)"id", (xmlChar*)(toStr(id)).c_str());
  // xmlNodePtr hs=xmlNewChild(r, NULL, (const xmlChar*)"LHS", NULL);
  // lhs->toXML(hs);
  // hs=xmlNewChild(r, NULL, (const xmlChar*)"RHS", NULL);
  // for(unsigned int i=0; i<rhs.size(); i++){
  //   for (vector <class Terms *>::const_iterator term=rhs[i]->begin();
  // 	 term != rhs[i]->end();
  // 	 term++) {
  //     (*term)->toXML(hs);
  //   }
  // }
}
#endif

/* **************************************************
 *
 ************************************************** */
const std::string
Rule::makeSerializationId()
{
  bool firstTerms = true;
  serialId = std::to_string(lhs->getCode()) + ':';
  for(unsigned int i = 0; i < rhs.size(); ++i){
    if (rhs[i]->isOptional())
      serialId += '[';
    if (firstTerms) firstTerms = false; else serialId += '-';
    bool firstTerm = true;
    for (std::vector< class Term * >::const_iterator term = rhs[i]->begin();
	 term != rhs[i]->end();
	 ++term){
      if (firstTerm) firstTerm = false; else serialId += '|';
      serialId += std::to_string((*term)->getCode());
    }
    if (rhs[i]->isOptional())
      serialId += ']';
  }
  statementsPtr stms = getStatements();
  if (stms)
    serialId += stms->serialize();
  return serialId;
}

/* **************************************************
 *
 ************************************************** */
void
Rule::addDefaults()
{
  std::vector<unsigned int> downs;
  for(unsigned int i=0; i<rhs.size(); i++)
    downs.push_back(0);
}

