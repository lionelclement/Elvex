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

echo "--------------------------------------------------------"

elvex -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon "letter [PRED:letter, from:[FORM:\"Lionel Clément\"], to:[FORM:\"`whoami`\", number:sg, gender:ms], body:[PRED:_installer, i:[PRED:__pro, number:pl, person:two], ii:[FORM:\"Elvex\"], tense:recent_past ]]" |tr '@' "\n" |../src/elvexpostedition |sed -e 's/^ *//'
#elvex -r -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-slang.grammar -lexiconFile fr-slang.local-lexicon -inputFile fr-slang.input | ../src/elvexpostedition |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n"
#elvex -t -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon -inputFile fr-1.0.4.input
#elvexdebug --traceShift -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon -inputFile fr-1.0.4.input
#elvex -grammarFile greg.grammar -lexiconFile greg.lexicon -inputFile greg.input
#elvex -t -grammarFile greg.grammar -lexiconFile greg.lexicon -inputFile greg.input
#elvexdebug --traceInit --traceStage --traceClose --traceShift --traceReduce --traceAction -grammarFile greg.grammar -lexiconFile greg.lexicon -inputFile greg.input

cd ..
