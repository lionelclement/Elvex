#!/bin/sh
# ##################################################
#
# ELVEX
#
# Copyright 2014-2022 LABRI,
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

##################################################
# en-1.1.0.fsa
make en-1.1.0.fsa
../bin/elvex -cld . -clf en-1.1.0 -rulesFile en-1.1.0.rules -lexiconFile en-1.1.0.lexicon "Text[PRED:_TO_APPRECIATE, i:[PRED:_YOU], ii:[PRED:_ELVEX], vtense:future]" | ../bin/elvexpostedition_en
#../bin/elvex --trace -cld . -clf en-1.1.0 -rulesFile en-1.1.0.rules -lexiconFile en-1.1.0.lexicon "Text[PRED:TO_APPRECIATE, i:[PRED:_YOU], ii:[PRED:ELVEX], vtense:future]" | ../bin/elvexpostedition_en
#../bin/elvex --traceAll -cld . -clf en-1.1.0 -rulesFile en-1.1.0.rules -lexiconFile en-1.1.0.lexicon "Text[PRED:TO_APPRECIATE, i:[PRED:_YOU], ii:[PRED:ELVEX], vtense:future]" | ../bin/elvexpostedition_en
#../bin/elvex -r -maxItems 10000 -cld . -clf en-1.1.0 -rulesFile en-1.1.0.rules -lexiconFile en-1.1.0.lexicon -inputFile en-1.1.0.input | ../bin/elvexpostedition_en
#../bin/elvex -cld . -clf en-1.1.0 -rulesFile en-1.1.0.rules -lexiconFile en-1.1.0.lexicon -inputFile en-1.1.0.input | ../bin/elvexpostedition_en
#../bin/elvex --trace -cld . -clf en-1.1.0 -rulesFile en-1.1.0.rules -lexiconFile en-1.1.0.lexicon -inputFile en-1.1.0.input

cd ..
