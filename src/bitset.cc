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

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Bitset::makeSerialString()
{
    std::ostringstream stream;
    size_t c = this->count();
    size_t sz = this->size();
    for (size_t i = 0; i < sz && c > 0; ++i)
    {
        if ((*this)[i])
        {
            --c;
            stream << std::hex << i;
            if (c > 0)
                stream << '\x0';
        }
    }
    serialString = stream.str();
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
