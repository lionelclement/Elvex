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

#ifndef ELVEX_LISTFEATURES_H
#define ELVEX_LISTFEATURES_H

#include <vector>
#include "shared_ptr.hpp"
#include "facade.hpp"

class ListFeatures : public Facade,
                     public Serializable,
                     public std::enable_shared_from_this<class ListFeatures>
{

private:
    std::vector<featuresPtr> listFeatures;

    ListFeatures(void);

    void makeSerialString();

public:
    ~ListFeatures();

    static listFeaturesPtr create(void);

    void push_back(const featuresPtr &);

    void add(unsigned int, featuresPtr);

    featuresPtr get(unsigned int);

    void clear(void);

    std::vector<featuresPtr>::const_iterator cbegin() const;

    std::vector<featuresPtr>::const_iterator cend() const;

    std::vector<featuresPtr>::iterator begin() ;

    std::vector<featuresPtr>::iterator end() ;

    size_t size() const;

    listFeaturesPtr clone(void);

    featuresPtr operator[](unsigned int);

    void print(std::ostream &) const;

    void flatPrint(std::ostream &) const;

    void apply(statementPtr from, class Item *item, class Parser &parser, class Generator *synthesizer, const statementPtr &variable, statementPtr body,
          bool &effect);

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr);
#endif

};

#endif // ELVEX_LISTFEATURES_H
