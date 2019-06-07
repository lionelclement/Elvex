/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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

#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <bitset>
#include <list>
#include <climits>
#include <cstdint>
#include <string>

#include "id.hh"
#include "vartable.hh"
#include "ipointer.hh"

class Entry: 
  public Id,
  public Serializable,
  public enable_shared_from_this< class Entry > {
  
private:
  unsigned int code;
  unsigned int codePred;
  std::string form;
  featuresPtr features;
  
  Entry(unsigned int, unsigned int, std::string, featuresPtr);
  Entry(unsigned int, std::string, std::string, featuresPtr);
  void setId(idType);
  const std::string makeSerializationId(void);

public:
  ~Entry();
  static entryPtr create(unsigned int code, unsigned int codePred, std::string form=std::string(), featuresPtr features=featuresPtr());
  static entryPtr create(unsigned int code, std::string pred=std::string(), std::string form=std::string(), featuresPtr features=featuresPtr());

  const unsigned int getCode(void) const;
  void setCode(const unsigned int code);
  const unsigned int getCodePred(void) const;
  void setForm(const std::string form);
  const std::string getForm(void) const;
  const featuresPtr getFeatures(void) const;
  
#ifdef OUTPUT_XML
  void toXML(xmlNodePtr nodeRoot) const;
#endif
  void print(std::ostream &) const;

};

#endif // ENTRY_H
