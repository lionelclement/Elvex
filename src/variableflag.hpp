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

#ifndef ELVEX_VARIABLE_FLAG_H
#define ELVEX_VARIABLE_FLAG_H

class VariableFlag
{

public:
    enum flagValues
    {
        CONTAINS,
        DOES_NOT_CONTAIN,
        NONE
    };

private:
    enum flagValues flag;

public:
    VariableFlag(void) noexcept;

    bool containsVariable(void);

    void setFlag(enum flagValues flag);
};

#endif // ELVEX_VARIABLE_FLAG_H
