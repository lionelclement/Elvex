/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2020 LABRI, 
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

#include <bitset>
#include <sstream>

#include "bitset.hpp"
#include "vartable.hpp"
#include "messages.hpp"
#include "shared_ptr.hpp"

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(unsigned int data)
        : std::bitset<MAXBITS>(data) {
    NEW
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(std::bitset<MAXBITS> &data)
        : std::bitset<MAXBITS>(data) {
    NEW
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(const bitsetPtr& bitset)
        : std::bitset<MAXBITS>(*bitset) {
    NEW
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::~Bitset() {
    DELETE
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr Bitset::create(unsigned int data) {
    return bitsetPtr(new Bitset(data));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr Bitset::create(std::bitset<MAXBITS> data) {
    return bitsetPtr(new Bitset(data));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr Bitset::create(const bitsetPtr& bs) {
    return bitsetPtr(new Bitset(bs));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
std::string Bitset::toString() const {
    std::stringstream s;
    size_t c = this->count();
    size_t sz = this->size();
    for (size_t i = 0; i < sz && c > 0; ++i) {
        if ((*this)[i]) {
            --c;
            s << Vartable::bitToVariable(i);
            if (c > 0)
                s << '|';
        }
    }
    return s.str();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Bitset::makeSerialString() {
serialString = std::string();
    size_t c = this->count();
    size_t sz = this->size();
    for (size_t i = 0; i < sz && c > 0; ++i) {
        if ((*this)[i]) {
            --c;
            serialString += std::to_string(i);
            if (c > 0)
                serialString += '|';
        }
    }
}

#ifdef OUTPUT_XML
/* ************************************************************
 *                                                            *
 ************************************************************ */
void Bitset::toXML(xmlNodePtr nodeRoot)
{
   xmlNodePtr f = xmlNewChild(nodeRoot, NULL, (const xmlChar*)"ALT", NULL);
   std::unordered_map<unsigned int, std::string>::const_iterator varTableIt;
   size_t c=this->count();
   size_t sz=this->size();
   for(unsigned int i = 0; i < sz && c > 0; ++i)
   if (this->test(i)) {
      --c;
      varTableIt = Vartable::bitMapFind(i);
      if (varTableIt != Vartable::bitMapEnd())
      xmlNewChild(f, NULL, (const xmlChar*)"OPT", (const xmlChar*)varTableIt->second.c_str());
   }
}
#endif
