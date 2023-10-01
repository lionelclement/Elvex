/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2023 LABRI,
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI - Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
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
    : std::bitset<MAXBITS>(data)
{
    NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(const std::bitset<MAXBITS> &data)
    : std::bitset<MAXBITS>(data)
{
    NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::Bitset(const bitsetPtr &bitset)
    : std::bitset<MAXBITS>(*bitset)
{
    NEW;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Bitset::~Bitset()
{
    DELETE;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr Bitset::create(unsigned int data)
{
    return bitsetPtr(new Bitset(data));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr Bitset::create(std::bitset<MAXBITS> data)
{
    return bitsetPtr(new Bitset(data));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bitsetPtr Bitset::create(const bitsetPtr &bs)
{
    return bitsetPtr(new Bitset(bs));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
std::string Bitset::toString() const
{
    std::stringstream s;
    size_t c = this->count();
    size_t sz = this->size();
    for (size_t i = 0; i < sz && c > 0; ++i)
    {
        if ((*this)[i])
        {
            --c;
            s << Vartable::bitToVariable(i);
            if (c > 0)
                s << '|';
        }
    }
    return s.str();
}

std::string replaceZeroSequences(const std::string& input) {
    std::string result;
    size_t count = 0;

    for (char c : input) {
        if (c == '0') {
            count++;
        } else {
            if (count > 0) {
                result += "_#" + std::to_string(count) + "_";
                count = 0;
            }
            result += c;
        }
    }

    if (count > 0) {
        result += "_#" + std::to_string(count) + "_";
    }

    return result;
}

/* ************************************************************
 * template<size_t N>
 * serialString = std::hex numbers from right to left
 ************************************************************ */
void Bitset::makeSerialString(){
   //serialString = toString();
   serialString = replaceZeroSequences(this->to_string()); 
   /***
    std::ostringstream stream;
    std::bitset<MAXBITS> copy = *this;
    for (size_t i = 0; i <= MAXBITS/8 ; ++i){
        uint8_t sample = 0;
        for (size_t j = 0 ; j <= 7 ; ++j){
            if (copy.test(j))
                sample |= 1 << j;
        } 
        stream << std::hex << static_cast<unsigned>(sample);
        copy >>= 8;
    }
    serialString = stream.str();
   ***/
  /***
    size_t firstNonZero = serialString.find_first_not_of('0');
    if (firstNonZero != std::string::npos) {
        // Si un caractère différent de '0' est trouvé, supprime les '0' au début
        serialString.erase(0, firstNonZero);
    } else {
        // Si la chaîne est composée uniquement de '0', la vide
        serialString = " ";
    }
    ***/

   /***
   size_t i = serialString.length();
    while (i > 0 && serialString[i - 1] == '0') {
        --i;
    }
    // Remove characters '0' from position i
    serialString.erase(i);
   ***/
  
   //std::cerr << serialString << std::endl;  
}

#ifdef OUTPUT_XML
/* ************************************************************
 *                                                            *
 ************************************************************ */
void Bitset::toXML(xmlNodePtr nodeRoot)
{
    xmlNodePtr f = xmlNewChild(nodeRoot, nullptr, (const xmlChar *)"ALT", nullptr);
    Vartable::uint16_t_to_string_iterator varTableIt;
    size_t c = this->count();
    size_t sz = this->size();
    for (unsigned int i = 0; i < sz && c > 0; ++i)
        if (this->test(i))
        {
            --c;
            varTableIt = Vartable::bitMapFind(i);
            if (varTableIt != Vartable::bitMapcEnd())
                xmlNewChild(f, nullptr, (const xmlChar *)"OPT", (const xmlChar *)varTableIt->second.c_str());
        }
}
#endif

/* ************************************************************
 *                                                            *
 ************************************************************ */
//bitsetPtr Bitset::_clone()
//{
//}
