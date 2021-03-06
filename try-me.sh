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
#elvex -compactedLexiconDirectory lefff -compactedLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.lexicon "\
#letter [\
#       from:[FORM:\"Lionel Clément\"], \
#       to:[FORM:\"`whoami`\", number:sg, gender:ms], \
#       body:[PRED:ESSAYER, i:[PRED:_pro, number:pl, person:two], ii:[FORM:\"`which elvex` `elvex --version`\"], tense:recent_past ]\
#]"\
#     |tr '@' "\n" | elvexpostedition_fr | sed -e 's/^ *//' -e 's/  */ /g'

#make en-1.1.0.fsa
#elvex -compactedLexiconDirectory . -compactedLexiconFile en-1.1.0 -grammarFile en-1.1.0.grammar -lexiconFile en-1.1.0.lexicon "\
#Text[PRED:TO_APPRECIATE, i:[PRED:_YOU], ii:[PRED:ELVEX], vtense:future]"\
# | elvexpostedition_en | sed 's/^ *//'
#elvexdebug --traceShift --traceInit --traceStage --traceClose --traceReduce --traceAction -compactedLexiconDirectory . -compactedLexiconFile en-1.1.0 -grammarFile en-1.1.0.grammar -lexiconFile en-1.1.0.lexicon 'Text[PRED:_TO_APPRECIATE, i:[PRED:__YOU], ii:[PRED:_ELVEX], vtense:future]'

../bin/elvex -compactedLexiconDirectory lefff -compactedLexiconFile lefff -grammarFile fr-slang.grammar -lexiconFile fr-slang.lexicon -inputFile fr-slang.input| ../bin/elvexpostedition_fr | sed 's/^ *//'
#../bin/elvex -t -V -compactedLexiconDirectory lefff -compactedLexiconFile lefff -grammarFile fr-slang.grammar -lexiconFile fr-slang.lexicon -inputFile fr-slang.input
#../bin/elvexdebug --traceShift -compactedLexiconDirectory lefff -compactedLexiconFile lefff -grammarFile fr-slang.grammar -lexiconFile fr-slang.lexicon -inputFile fr-slang.input

#elvex -compactedLexiconDirectory lefff -compactedLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.lexicon -inputFile fr-1.0.4.input | elvexpostedition_fr |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n"
##elvex -grammarFile greg.grammar -lexiconFile greg.lexicon -inputFile greg.input
#elvex -t -grammarFile greg.grammar -lexiconFile greg.lexicon -inputFile greg.input
#elvexdebug --traceInit --traceStage --traceClose --traceShift --traceReduce --traceAction -grammarFile greg.grammar -lexiconFile greg.lexicon -inputFile greg.input

cd ..
