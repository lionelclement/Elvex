#!/bin/sh
# ##################################################
#
# ELVEX
#
# Copyright 2014-2023 LABRI,
# CNRS (UMR 5800), the University of Bordeaux,
# and the Bordeaux INP
#
# Author:
# Lionel Clément
# LaBRI - Université Bordeaux
# 351, cours de la Libération
# 33405 Talence Cedex - France
# lionel.clement@labri.fr
#
# This file is part of ELVEX.
#
################################################## #

#!/bin/bash

##################################################
make -C data en-1.1.0.fsa
bin/elvex -cld data -clf en-1.1.0 -rulesFile data/en-1.1.0.rules -lexiconFile data/en-1.1.0.lexicon -inputFile data/en-1.1.0.input
