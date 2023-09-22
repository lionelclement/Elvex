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

#ifndef ELVEX_ENTRY_H
#define ELVEX_ENTRY_H

#include "facade.hpp"
#include "serializable.hpp"
#include "shared_ptr.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Entry : public Facade,
              public Serializable,
              public std::enable_shared_from_this<class Entry>
{

public:
    static uint16_t FORM_HEAD;

private:

    uint16_t pos;
    uint16_t head;
    std::string form;
    featuresPtr features;

    Entry(uint16_t pos, uint16_t head, std::string form, featuresPtr features);

    Entry(uint16_t pos, uint16_t head, featuresPtr features);

    Entry(uint16_t pos, std::string head, std::string form, featuresPtr features);

    Entry(uint16_t pos, featuresPtr features);

    Entry(uint16_t pos);

    void makeSerialString(void);

public:
    ~Entry();

    static entryPtr create(uint16_t pos, uint16_t head, std::string form,
                            featuresPtr features = featuresPtr());

    static entryPtr create(uint16_t pos, uint16_t head, featuresPtr features = featuresPtr());

    static entryPtr create(uint16_t pos, std::string head, std::string form,
                            featuresPtr features = featuresPtr());

    static entryPtr create(uint16_t pos, featuresPtr features);

    static entryPtr create(uint16_t pos);

    uint16_t getPos(void) const;

    void setPos(const uint16_t pos);

    uint16_t getHead() const;

    void setForm(const std::string form);

    std::string &getForm();

    featuresPtr getFeatures() const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr nodeRoot) const;
#endif

    void print(std::ostream &) const;
    
    void renameVariables(size_t);

    entryPtr clone(void) const;

};

#endif // ELVEX_ENTRY_H
