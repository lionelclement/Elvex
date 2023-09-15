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
 * LaBRI -- Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#include <utility>
#include "listfeatures.hpp"
#include "features.hpp"
#include "shared_ptr.hpp"
#include "messages.hpp"
#include "statement.hpp" 

/* **************************************************
 *
 ************************************************** */
ListFeatures::ListFeatures()
{
    NEW;
}

/* **************************************************
 *
 ************************************************** */
ListFeatures::~ListFeatures()
{
    DELETE;
    for (auto &listFeature : listFeatures)
        listFeature.reset();
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr ListFeatures::create()
{
    return listFeaturesPtr(new ListFeatures());
}

/* **************************************************
 *
 ************************************************** */
featuresPtr ListFeatures::operator[](unsigned int j)
{
    return listFeatures[j];
}

/* **************************************************
 *
 ************************************************** */
void ListFeatures::push_back(const featuresPtr &fs)
{
    listFeatures.push_back(fs);
}

/* **************************************************
 *
 ************************************************** */
void ListFeatures::add(unsigned int j, featuresPtr fs)
{
    listFeatures[j] = std::move(fs);
}

/* **************************************************
 *
 ************************************************** */
featuresPtr ListFeatures::get(unsigned int j)
{
    return listFeatures[j];
}

/* **************************************************
 *
 ************************************************** */
void ListFeatures::clear()
{
    listFeatures.clear();
}

/* **************************************************
 *
 ************************************************** */
std::vector<featuresPtr>::const_iterator ListFeatures::cbegin() const
{
    return listFeatures.cbegin();
}

/* **************************************************
 *
 ************************************************** */
std::vector<featuresPtr>::const_iterator ListFeatures::cend() const
{
    return listFeatures.cend();
}

/* **************************************************
 *
 ************************************************** */
std::vector<featuresPtr>::iterator ListFeatures::begin()
{
    return listFeatures.begin();
}

/* **************************************************
 *
 ************************************************** */
std::vector<featuresPtr>::iterator ListFeatures::end()
{
    return listFeatures.end();
}

/* **************************************************
 *
 ************************************************** */
size_t ListFeatures::size() const
{
    return listFeatures.size();
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr ListFeatures::clone()
{
    listFeaturesPtr lf = ListFeatures::create();
    for (auto &listFeature : listFeatures)
        lf->push_back(listFeature->clone());
    return lf;
}

/* **************************************************
 *
 ************************************************** */
void ListFeatures::print(std::ostream &outStream) const
{
    outStream << R"(<TABLE border = "1">)";
    outStream << R"(<TBODY align = "left"><TR>)";
    for (auto &listFeature : listFeatures)
        listFeature->print(outStream);
    outStream << "</TR></TBODY>";
    outStream << "</TABLE>";
}

/* **************************************************
 *
 ************************************************** */
void ListFeatures::flatPrint(std::ostream &outStream) const
{
    outStream << '(';
    bool first = true;
    for (auto &listFeature : listFeatures){
        if (first) first=false; else outStream << ", ";
        listFeature->flatPrint(outStream);
    }
    outStream << ')';
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void ListFeatures::apply(statementPtr from, class Item *item, Parser &parser, Generator *synthesizer, const statementPtr &variable, statementPtr statement,
                         bool &effect)
{
    for (auto &features : listFeatures) {
        features->apply(from, item, parser, synthesizer, variable, statement->clone(0), effect);
    }
}

/* **************************************************
 *
 ************************************************** */
void ListFeatures::makeSerialString()
{
    serialString = '\x10';
    for (auto &features : listFeatures)
    {
        serialString += '\x11' + features->peekSerialString();
    }
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void ListFeatures::toXML(xmlNodePtr nodeRoot)
{
    xmlNodePtr lfs = xmlNewChild(nodeRoot, nullptr, (const xmlChar *)"LFS", nullptr);
    xmlSetProp(lfs, (xmlChar *)"id", (xmlChar *)std::to_string(this->getId()).c_str());
    for (auto &features : listFeatures){
            features->toXML(lfs);
    }
}
#endif

