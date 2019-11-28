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

#include <sstream>
#include "rule.hh"
#include "term.hh"
#include "terms.hh"
#include "statements.hh"
#include "messages.hh"
#include "synthesizer.hh"

/* ************************************************************
 *
 ************************************************************ */
Rule::Rule(size_t id, unsigned int lineno, std::string filename, termPtr lhs, std::vector<termsPtr> &rhs, statementsPtr statements)
      : Id(id) {
   this->lineno = lineno;
   this->filename = filename;
   this->lhs = lhs;
   this->rhs = rhs;
   this->statements = statements;
   this->usages = 0;
   this->trace = false;
   NEW;
}

/* ************************************************************
 *
 ************************************************************ */
Rule::Rule(size_t id, unsigned int lineno, std::string filename, termPtr lhs, statementsPtr statements)
      : Id(id) {
   this->lineno = lineno;
   this->filename = filename;
   this->lhs = lhs;
   this->statements = statements;
   this->usages = 0;
   this->trace = false;
   NEW;
}

/* ************************************************************
 *
 ************************************************************ */
Rule::Rule(unsigned int lineno, std::string filename, termPtr lhs, std::vector<termsPtr> &rhs, statementsPtr statements)
      : Rule(0, lineno, filename, lhs, rhs, statements) {
}

/* ************************************************************
 *
 ************************************************************ */
Rule::Rule(unsigned int lineno, std::string filename, termPtr lhs, statementsPtr statements)
      : Rule(0, lineno, filename, lhs, statements) {
}

/* ************************************************************
 *
 ************************************************************ */
rulePtr Rule::create(size_t id, unsigned int lineno, std::string filename, termPtr lhs, std::vector<termsPtr> &rhs, statementsPtr statements) {
   return rulePtr(new Rule(id, lineno, filename, lhs, rhs, statements));
}

/* ************************************************************
 *
 ************************************************************ */
rulePtr Rule::create(size_t id, unsigned int lineno, std::string filename, termPtr lhs, statementsPtr statements) {
   return rulePtr(new Rule(id, lineno, filename, lhs, statements));
}

/* ************************************************************
 *
 ************************************************************ */
rulePtr Rule::create(unsigned int lineno, std::string filename, termPtr lhs, std::vector<termsPtr> &rhs, statementsPtr statements) {
   return rulePtr(new Rule(lineno, filename, lhs, rhs, statements));
}

/* ************************************************************
 *
 ************************************************************ */
rulePtr Rule::create(unsigned int lineno, std::string filename, termPtr lhs, statementsPtr statements) {
   return rulePtr(new Rule(lineno, filename, lhs, statements));
}

/* ************************************************************
 *
 ************************************************************ */
Rule::~Rule() {
   DELETE;
   for (std::vector<termsPtr>::iterator term = rhs.begin(); term != rhs.end(); term++)
      if (*term)
         term->reset();
   if (lhs) {
      lhs.reset();
   }
   if (statements) {
      statements.reset();
   }
}

/* ************************************************************
 *
 ************************************************************ */
termPtr Rule::getLhs(void) const {
   return lhs;
}

/* ************************************************************
 *
 ************************************************************ */
std::vector<termsPtr> &Rule::getRhs(void) {
   return this->rhs;
}

/* ************************************************************
 *
 ************************************************************ */
termsPtr Rule::getTerms(unsigned int index) const {
   return this->rhs[index];
}

/* ************************************************************
 *
 ************************************************************ */
statementsPtr Rule::getStatements(void) const {
   return statements;
}

/* ************************************************************
 *
 ************************************************************ */
void Rule::incUsages(class Synthesizer *synthesizer) {
   if (++usages > synthesizer->getMaxUsages()) {
      throw "*** error: too much usages of the same rule: " + this->toString();
      exit(EXIT_FAILURE);
   }
}

/* ************************************************************
 *
 ************************************************************ */
void Rule::resetUsages(void) {
   usages = 0;
}

/* ************************************************************
 *
 ************************************************************ */
const unsigned int Rule::getLineno(void) const {
   return lineno;
}

/* ************************************************************
 *
 ************************************************************ */
const std::string &Rule::getFilename(void) const {
   return filename;
}

/* **************************************************
 *
 ************************************************** */
bool Rule::getTrace(void) const {
   return trace;
}

/* **************************************************
 *
 ************************************************** */
void Rule::setTrace(bool trace) {
   this->trace = trace;
}

/***************************
 *
 ***************************/
rulePtr Rule::clone() const {
   std::vector<termsPtr> rhsCopy;
   for (unsigned int i = 0; i < rhs.size(); ++i)
      rhsCopy.push_back(rhs[i]->clone());
   rulePtr rule = Rule::create(this->getId(), this->lineno, this->filename, lhs, rhsCopy, statements);
   rule->usages = usages;
   rule->trace = trace;
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
   //   for (vector <termsPtr >::const_iterator term=rhs[i]->begin();
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
void Rule::addDefaults() {
   std::vector<unsigned int> downs;
   for (unsigned int i = 0; i < rhs.size(); i++)
      downs.push_back(0);
}

/* ************************************************************
 *
 ************************************************************ */
void Rule::print(std::ostream& outStream, unsigned int index, bool withSemantic, bool html) const {
   std::string space = (html ? "&nbsp;" : " ");
   bool first = true;
   lhs->print(outStream);
   outStream << space << "→" << space;
   for (unsigned int i = 0; i < rhs.size(); i++) {
      if (first)
         first = false;
      else
         outStream << space;
      if (index == i)
         outStream << "•" << space;
      rhs[i]->print(outStream);
   }
   if (index == rhs.size())
      outStream << space << "•";
   if (withSemantic) {
      statementsPtr stms = getStatements();
      if (stms)
         stms->print(outStream);
      outStream << (html ? "<BR>" : "\n");
   }
}

/* **************************************************
 *
 ************************************************** */
std::string Rule::toString() const {
   std::stringstream s;
   print(s, UINT_MAX, false, false);
   return s.str();
}
