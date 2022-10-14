/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI, 
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

#ifndef ELVEX_LISTFEATURES_H
#define ELVEX_LISTFEATURES_H

#include <vector>
#include "shared_ptr.hpp"
#include "flags.hpp"
#include "uniq-id.hpp"

class ListFeatures :
        public UniqId, public Flags, public std::enable_shared_from_this<class ListFeatures> {

private:
    std::vector<featuresPtr> listFeatures;

    ListFeatures(void);

public:
    ~ListFeatures();

    static listFeaturesPtr create(void);

    void push_back(const featuresPtr&);

    void add(unsigned int, featuresPtr);

    void clear(void);

    std::vector<featuresPtr>::const_iterator begin() const;

    std::vector<featuresPtr>::const_iterator end() const;

    size_t size() const;

    listFeaturesPtr clone(void);

    featuresPtr operator[](unsigned int);
};

#endif // ELVEX_LISTFEATURES_H
