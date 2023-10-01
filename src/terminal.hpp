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

#ifndef ELVEX_TERMINAL_H
#define ELVEX_TERMINAL_H

#include "facade.hpp"
#include "serializable.hpp"
#include "shared_ptr.hpp"

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

class Terminal : public Facade,
              public Serializable,
              public std::enable_shared_from_this<class Terminal>
{

private:

    uint16_t code;
    std::string form;
    featuresPtr features;

    Terminal(uint16_t code);

    Terminal(uint16_t code, const std::string &form);

    Terminal(uint16_t code, const std::string &form, featuresPtr features);

    void makeSerialString(void);

public:
    ~Terminal();

    static terminalPtr create(uint16_t code);

    static terminalPtr create(uint16_t code, const std::string &form);

    static terminalPtr create(uint16_t code, const std::string &form, featuresPtr features);

    std::string &getForm();

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr nodeRoot) const;
#endif

    void print(std::ostream &) const;
    
};

#endif // ELVEX_TERMINAL_H
