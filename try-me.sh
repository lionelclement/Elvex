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

cd data

echo "--------------------------------------------------------"
(cd data/lefff ; make -s -j7)
elvex -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon "letter [PRED:letter, from:[FORM:\"Lionel Clément\"], to:[FORM:\"`whoami`\", number:sg, gender:ms], body:[PRED:_installer, i:[PRED:__pro, number:pl, person:two], ii:[FORM:\"Elvex\"], tense:recent_past ]]" |tr '@' "\n" | elvexpostedition | sed -e 's/^ *//' -e 's/  */ /g'

#elvex -r -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-slang.grammar -lexiconFile fr-slang.local-lexicon -inputFile fr-slang.input | ../src/elvexpostedition |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n"
#elvex -t -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon -inputFile fr-1.0.4.input
#elvexdebug --traceShift -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon -inputFile fr-1.0.4.input
#elvex -grammarFile greg.grammar -lexiconFile greg.lexicon -inputFile greg.input
#elvex -t -grammarFile greg.grammar -lexiconFile greg.lexicon -inputFile greg.input
#elvexdebug --traceInit --traceStage --traceClose --traceShift --traceReduce --traceAction -grammarFile greg.grammar -lexiconFile greg.lexicon -inputFile greg.input

#make greg-2.fsa
#elvex -compactLexiconDirectory . -compactLexiconFile greg-2 -grammarFile greg-2.grammar -lexiconFile greg-2.lexicon -inputFile greg-2.input

cd ..
