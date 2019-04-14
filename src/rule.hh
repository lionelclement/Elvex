/* **************************************************
 *
 * CNRS (UMRPtr 5800), the University of Bordeaux,

Ptr * Author: Lionel Clément,
 * Labri -- 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef RULE_H
#define RULE_H

#include <climits>
#include <vector>
#include <ostream>
#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif
#include "id.hh"
#include "ipointer.hh"
#include "serializable.hh"

class Rule:
  public Id::Id,
  public Serializable {
  
private:
  class Term *lhs;
  std::vector<class Terms *> rhs;
  statementsPtr statements;
  unsigned int usages;
  std::string filename;
  unsigned int lineno;

private:
  const std::string makeSerializationId(void);

public:
  Rule(unsigned int, std::string, class Term *, std::vector<class Terms *> &rhs, statementsPtr statements=statementsPtr());
  Rule(unsigned int, std::string, class Term *lhs, statementsPtr statements=statementsPtr());
  ~Rule();
  void setId(idType);
  

  class Term *getLhs(void) const;
  std::vector <class Terms *> &getRhs(void);

  class Term *getCurrentTerm(void) const;
  class Terms *getCurrentTerms() const;
  class Terms *getTerms(unsigned int) const;
  void setCurrentTerms(class Terms *);

  statementsPtr getStatements(void) const;
  const unsigned int getUsages(void) const;
  const unsigned int incUsages(void);
  void resetUsages(void);

  const unsigned int getLineno(void) const;
  const std::string &getFilename(void) const;
  
  class Rule *clone() const;
  void print(std::ostream &, unsigned int=UINT_MAX, bool=false, bool=true) const;

#ifdef OUTPUT_XML
  void toXML(const xmlNodePtr);
#endif
  void addDefaults(void);
  
  struct Less {
    const bool operator()(const class Rule *r1, const class Rule *r2) const;
  };

};

#endif // RULE_H
