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

#ifndef ELVEX_ENTRY_H
#define ELVEX_ENTRY_H

#include "uniq-id.hpp"
#include "serializable.hpp"
#include "shared_ptr.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Entry :
        public UniqId, public Serializable, public std::enable_shared_from_this<class Entry> {

private:
    unsigned int pos;
    unsigned int pred;
    std::string form;
    featuresPtr features;

    Entry(unsigned int, unsigned int, std::string, featuresPtr);

    Entry(unsigned int, std::string, std::string, featuresPtr);

    void makeSerialString(void);

public:
    ~Entry();

    static entryPtr create(unsigned int term, unsigned int pred, std::string form = std::string(),
                           featuresPtr features = featuresPtr());

    static entryPtr create(unsigned int term, std::string pred = std::string(), std::string form = std::string(),
                           featuresPtr features = featuresPtr());

    unsigned int getPos(void) const;

    void setPos(const unsigned int pos);

    unsigned int getPred() const;

    void setForm(const std::string form);

    std::string &getForm();

    featuresPtr getFeatures() const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr nodeRoot) const;
#endif

    void print(std::ostream &) const;

};

#endif // ELVEX_ENTRY_H
