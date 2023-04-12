/* **************************************************
 *
 * ELVEX
 *
<<<<<<< HEAD
 * Copyright 2014-2020 LABRI,
=======
 * Copyright 2014-2023 LABRI,
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI -- Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
<<<<<<< HEAD
 * lionel.clement@labri.fr
=======
 * lionel.clement@u-bordeaux.fr
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef ELVEX_USAGE_EXCEPTION_HPP
#define ELVEX_USAGE_EXCEPTION_HPP

<<<<<<< HEAD

#include <string>
#include <exception>
=======
#include <string>
#include <exception>
#include <sstream>
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723

class usage_exception :
    public std::exception {

<<<<<<< HEAD
public:
    usage_exception(std::string);
    usage_exception();
=======
private:
    std::string message;

public:
    usage_exception(std::string);
    usage_exception(std::ostringstream& oss);
    std::string getMessage();
>>>>>>> 71ab82fc49d0d601ec20c4c5edee41e89e638723
};


#endif //ELVEX_USAGE_EXCEPTION_HPP
