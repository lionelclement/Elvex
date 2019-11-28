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

#../src/elvex -t -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input
#../src/elvexdebug --traceStage -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input -xml fr-1.0.3.xml > fr-1.0.3.html
#../src/elvex  -maxCardinal 1000000 -maxUsages 100000 -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input | ../src/elvexpostedition |tr '@' "\n" |sed -e 's/^ *//'
../src/elvex -maxCardinal 1000000 -maxUsages 100000 -maxLength 10000 -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon "letter [PRED:letter, i:[FORM:\"`whoami`\", number:sg, gender:ms], ii:[PRED:_installer, i:[PRED:__pro, number:pl, person:two], ii:[FORM:\"Elvex\"], tense:recent_past ], iii:[FORM:\"Lionel Clément\"]]" |tr '@' "\n" |../src/elvexpostedition |sed -e 's/^ *//'

cd ..
