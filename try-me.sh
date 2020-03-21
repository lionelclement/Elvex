# ##################################################
#
# ELVEX
#
# Copyright 2019 LABRI, 
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

make -s
(cd data/lefff ; make -s)

cd data

echo "--------------------------------------------------------"

../src/elvex -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon "letter [PRED:letter, from:[FORM:\"Lionel Clément\"], to:[FORM:\"`whoami`\", number:sg, gender:ms], body:[PRED:_installer, i:[PRED:__pro, number:pl, person:two], ii:[FORM:\"Elvex\"], tense:recent_past ]]" |tr '@' "\n" |../src/elvexpostedition |sed -e 's/^ *//'
#../src/elvex -r -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-slang.grammar -lexiconFile fr-slang.local-lexicon -inputFile fr-slang.input | ../src/elvexpostedition |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n"
#../src/elvex -t -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon -inputFile fr-1.0.4.input
#../src/elvexdebug --traceShift -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon -inputFile fr-1.0.4.input

cd ..
