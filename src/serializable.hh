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

#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <vector>

class Serializable {  

protected:
  std::string serialId;

private:
  virtual const std::string makeSerializationId(void)=0;
  
public:
  Serializable();
  virtual ~Serializable();
  const std::string serialize(void);
  void resetSerialId(void);
  
};

#endif // SERIALIZABLE_H
