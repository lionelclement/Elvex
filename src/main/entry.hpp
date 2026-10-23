/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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

/**
 * A lexical surface form together with its associated feature structure.
 * An entry acts as a template for an individual generation candidate.
 */
class Entry : public Facade,
              public Serializable,
              public std::enable_shared_from_this<class Entry>
{

private:

    std::string form;

    featuresPtr features;

    void makeCoreSerialString(void);

public:
    Entry(const std::string &form, featuresPtr features);

    Entry(featuresPtr features);

    ~Entry();

    static entryPtr create(const std::string &form, featuresPtr features);

    static entryPtr create(featuresPtr features);

    /** Editable surface form; keep its lifetime bound to this entry. */
    std::string &getForm();

    /** Shared feature template; callers must clone it before unification. */
    featuresPtr getFeatures() const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr nodeRoot) const;
#endif

    void print(std::ostream &) const;
    
    /** Give variables in this entry a fresh scope. */
    void _renameVariables(uint32_t);

    /**
     * Clone lexical features before matching against a particular item.
     * The compacted-lexicon cache must retain its unmodified templates.
     */
    entryPtr clone(void) const;

};

#endif // ELVEX_ENTRY_H
