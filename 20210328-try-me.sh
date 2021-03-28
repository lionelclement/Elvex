#!/bin/sh
# ##################################################
#
# ELVEX
#
# Copyright 2014-2020 LABRI,
# CNRS (UMR 5800), the University of Bordeaux,
# and the Bordeaux INP
#
# Author: 
# Lionel Clément
# LaBRI -- Université Bordeaux 
# 351, cours de la Libération
# 33405 Talence Cedex - France
# lionel.clement@labri.fr
# 
# This file is part of ELVEX.
#
################################################## #

cd data

#echo "--------------------------------------------------------"
(cd lefff ; make -s)

elvex -cld lefff -clf lefff -grammarFile fr-20210328.grammar -lexiconFile fr-20210328.lexicon -inputFile fr-20210328.input| elvexpostedition_fr | sed 's/^ *//' | sort -u
#elvex -t -cld lefff -clf lefff -grammarFile fr-20210328.grammar -lexiconFile fr-20210328.lexicon -inputFile fr-20210328.input| elvexpostedition_fr
#elvexdebug --traceShift -cld lefff -clf lefff -grammarFile fr-20210328.grammar -lexiconFile fr-20210328.lexicon -inputFile fr-20210328.input

cd ..
