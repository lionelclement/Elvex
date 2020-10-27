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
#(cd data/lefff ; make -s -j7)
#elvex -compactedLexiconDirectory lefff -compactedLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.lexicon "letter [PRED:letter, from:[FORM:\"Lionel Clément\"], to:[FORM:\"`whoami`\", number:sg, gender:ms], body:[PRED:_installer, i:[PRED:__pro, number:pl, person:two], ii:[FORM:\"elvex\"], tense:recent_past ]]" |tr '@' "\n" | elvexpostedition_fr | sed -e 's/^ *//' -e 's/  */ /g'

##elvex -r -compactedLexiconDirectory lefff -compactedLexiconFile lefff -grammarFile fr-slang.grammar -lexiconFile fr-slang.local-lexicon -inputFile fr-slang.input | elvexpostedition_fr |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n"
#elvex -t -compactedLexiconDirectory lefff -compactedLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.lexicon -inputFile fr-1.0.4.input
#elvexdebug --traceShift --traceInit --traceStage --traceClose --traceReduce --traceAction -compactedLexiconDirectory lefff -compactedLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.lexicon -inputFile fr-1.0.4.input
#elvex -compactedLexiconDirectory lefff -compactedLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.lexicon -inputFile fr-1.0.4.input | elvexpostedition_fr |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n"
##elvex -grammarFile greg.grammar -lexiconFile greg.lexicon -inputFile greg.input
#elvex -t -grammarFile greg.grammar -lexiconFile greg.lexicon -inputFile greg.input
#elvexdebug --traceInit --traceStage --traceClose --traceShift --traceReduce --traceAction -grammarFile greg.grammar -lexiconFile greg.lexicon -inputFile greg.input

make en-1.1.0.fsa
../bin/elvex -compactedLexiconDirectory . -compactedLexiconFile en-1.1.0 -grammarFile en-1.1.0.grammar -lexiconFile en-1.1.0.lexicon 'Text[PRED:_TO_APPRECIATE, i:[PRED:__YOU], ii:[PRED:_ELVEX], vtense:future]' | ../bin/elvexpostedition | sed 's/^ *//'
#../bin/elvexdebug --traceShift --traceInit --traceStage --traceClose --traceReduce --traceAction -compactedLexiconDirectory . -compactedLexiconFile en-1.1.0 -grammarFile en-1.1.0.grammar -lexiconFile en-1.1.0.lexicon 'Text[PRED:_TO_APPRECIATE, i:[PRED:__YOU], ii:[PRED:_ELVEX], vtense:future]'

cd ..
