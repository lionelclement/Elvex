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

#echo "--------------------------------------------------------"
(cd lefff ; make -s)
#../bin/elvex -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-1.0.4.rules -lexiconFile fr-1.0.4.lexicon "\
#letter [\
#       from:[FORM:\"Lionel Clément\"], \
#       to:[FORM:\"`whoami`\", number:sg, gender:ms], \
#       body:[PRED:ESSAYER, i:[PRED:_pro, number:pl, person:two], ii:[FORM:\"`which elvex` `elvex --version`\"], tense:recent_past ]\
#]"\
#     |tr '@' "\n" | ../bin/elvexpostedition_fr | sed -e 's/^ *//' -e 's/  */ /g'

make en-1.1.0.fsa
echo '../bin/elvex -cld . -clf en-1.1.0 -rulesFile en-1.1.0.rules -lexiconFile en-1.1.0.lexicon "Text[PRED:TO_APPRECIATE, i:[PRED:_YOU], ii:[PRED:ELVEX], vtense:future]" | elvexpostedition_en'
../bin/elvex -cld . -clf en-1.1.0 -rulesFile en-1.1.0.rules -lexiconFile en-1.1.0.lexicon "Text[PRED:TO_APPRECIATE, i:[PRED:_YOU], ii:[PRED:ELVEX], vtense:future]" | ../bin/elvexpostedition_en'

#../bin/elvexdebug --traceShift --traceInit --traceStage --traceClose --traceReduce --traceAction -compactedLexiconDirectory . -compactedLexiconFile en-1.1.0 -rulesFile en-1.1.0.rules -lexiconFile en-1.1.0.lexicon 'Text[PRED:TO_APPRECIATE, i:[PRED:_YOU], ii:[PRED:ELVEX], vtense:future]'

#../bin/elvex -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-slang.rules -lexiconFile fr-slang.lexicon -inputFile fr-slang.input| ../bin/elvexpostedition_fr | sed 's/^ *//'
#../bin/elvex -t -V -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-slang.rules -lexiconFile fr-slang.lexicon -inputFile fr-slang.input
#../bin/elvexdebug --traceShift -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-slang.rules -lexiconFile fr-slang.lexicon -inputFile fr-slang.input

#../bin/elvex -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-1.0.4.rules -lexiconFile fr-1.0.4.lexicon -inputFile fr-1.0.4.input | ../bin/elvexpostedition_fr |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n"
##../bin/elvex -rulesFile greg.rules -lexiconFile greg.lexicon -inputFile greg.input
#../bin/elvex -t -rulesFile greg.rules -lexiconFile greg.lexicon -inputFile greg.input
#../bin/elvexdebug --traceInit --traceStage --traceClose --traceShift --traceReduce --traceAction -rulesFile greg.rules -lexiconFile greg.lexicon -inputFile greg.input

#make essai-20221012.fsa
#../bin/elvex -cld . -clf essai-20221012 -rulesFile essai-20221012.rules -lexiconFile essai-20221012.lexicon -inputFile essai-20221012.input
#../bin/elvexdebug --traceShift --traceInit --traceStage --traceClose --traceReduce --traceAction -cld . -clf essai-20221012 -rulesFile essai-20221012.rules -lexiconFile essai-20221012.lexicon -inputFile essai-20221012.input

cd ..
