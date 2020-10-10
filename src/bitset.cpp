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

#include <bitset>
#include <sstream>

#include "bitset.h"
#include "vartable.h"
#include "messages.h"
#include "shared_ptr.h"

//const std::bitset<MAXBITS> Bitset::LEXBITSET = 1ul;
//const std::bitset<MAXBITS> Bitset::ARGBITSET = 2ul;
//const std::bitset<MAXBITS> Bitset::SYSBITSET = 4ul;
//const std::bitset<MAXBITS> Bitset::FIRSTBITSET = 8ul;

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(unsigned int data)
        : std::bitset<MAXBITS>(data) {
    NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(std::bitset<MAXBITS> &data)
        : std::bitset<MAXBITS>(data) {
    NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(bitsetPtr bitset)
        : std::bitset<MAXBITS>(*bitset) {
    NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::~Bitset() {
    DELETE;
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
bitsetPtr Bitset::create(bitsetPtr bs) {
    return bitsetPtr(new Bitset(bs));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
std::string Bitset::toString() const {
    std::stringstream s;
    size_t c = this->count();
    size_t sz = this->size();
    bool first = true;
    for (size_t i = 0; i < sz && c > 0; ++i) {
        if ((*this)[i]) {
            --c;
            if (first)
                first = false;
            else
                s << '|';
            s << Vartable::bitToVariable(i);
        }
    }
    return s.str();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Bitset::makeSerialString() {
    serialString = std::string();
    std::stringstream s;
    size_t c = this->count();
    size_t sz = this->size();
    for (size_t i = 0; i < sz && c > 0; ++i) {
        if ((*this)[i]) {
            --c;
            serialString += std::to_string(i);
            if (c > 0)
                serialString += ',';
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
