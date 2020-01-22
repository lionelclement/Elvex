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
(cd data/lefff ; make -s -j7)

cd data

echo "--------------------------------------------------------"

../src/elvex -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon "letter [PRED:letter, from:[FORM:\"Lionel Clément\"], to:[FORM:\"`whoami`\", number:sg, gender:ms], body:[PRED:_installer, i:[PRED:__pro, number:pl, person:two], ii:[FORM:\"Elvex\"], tense:recent_past ]]" |tr '@' "\n" |../src/elvexpostedition |sed -e 's/^ *//'

#../src/elvex -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon -inputFile fr-1.0.4.input | ../src/elvexpostedition |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n" |../src/elvexpostedition |sed -e 's/^ *//'

#../src/elvex -t -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon -inputFile fr-1.0.4.input

#../src/elvexdebug --traceShift -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.4.grammar -lexiconFile fr-1.0.4.local-lexicon -inputFile fr-1.0.4.input

#../src/elvex -r -grammarFile antonio-1.grammar -lexiconFile antonio-1.lexicon -inputFile antonio-1.input | ../src/elvexpostedition |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n" |../src/elvexpostedition |sed -e 's/^ *//'

#../src/elvex -t -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input

#../src/elvex -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input 

#../src/elvex -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input | ../src/elvexpostedition |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n" |../src/elvexpostedition |sed -e 's/^ *//'

#../src/elvex -r -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input | ../src/elvexpostedition |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n" |../src/elvexpostedition |sed -e 's/^ *//'

#../src/elvexdebug -t --traceClose --traceShift --traceAction -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input -xml fr-1.0.3.xml > fr-1.0.3.html ; open fr-1.0.3.html

#../src/elvexbuildlexicon build -compactLexiconDirectory . -compactLexiconFile adj -patternFile adj.pattern adj.lexicon
#../src/elvex -t -grammarFile adj.grammar -compactLexiconDirectory . -compactLexiconFile adj -inputFile adj.input
#../src/elvexdebug -t --traceShift -grammarFile adj.grammar -compactLexiconDirectory . -compactLexiconFile adj -inputFile adj.input > adj.html ; open adj.html

#../src/elvexdebug --traceAction -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input -xml fr-1.0.3.xml > fr-1.0.3.html ; open fr-1.0.3.html

#../src/elvex -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input 2> /dev/null

#../src/elvexdebug -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input -xml fr-1.0.3.xml > fr-1.0.3.html

#../src/elvex -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon -inputFile fr-1.0.3.input | ../src/elvexpostedition |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n" |../src/elvexpostedition |sed -e 's/^ *//'

#../src/elvex -maxCardinal 1000000 -maxUsages 100000 -maxLength 10000 -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon "letter [PRED:letter, i:[FORM:\"`whoami`\", number:sg, gender:ms], ii:[PRED:_installer, i:[PRED:__pro, number:pl, person:two], ii:[FORM:\"Elvex\"], tense:\$recent_past], iii:[FORM:\"Lionel Clément\"]]" |tr '@' "\n" |../src/elvexpostedition | sed -e 's/^ *//'

#../src/elvex -t -maxCardinal 1000000 -maxUsages 100000 -maxLength 10000 -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon "letter [PRED:letter, greeting:[FORM:\"`whoami`\", number:sg, gender:ms], body:[PRED:_installer, i:[PRED:__pro, number:pl, person:two], ii:[FORM:\"Elvex\"], tense:recent_past], closing:[FORM:\"Lionel Clément\"], ps:[PRED:_écrire, i:[PRED:_ordinateur, number:sg], ii:[PRED:_lettre, dem:yes, number:sg], tense:past, diathesis:passive]]" |tr '@' "\n" |../src/elvexpostedition | sed -e 's/^ *//'

#../src/elvexdebug --traceStage --traceClose --traceShift --traceReduce --traceAction -grammarFile p2.grammar -lexiconFile p2.lexicon "S [i:<[id:v1], [id:v2]>]"

#../src/elvexdebug --traceAction -grammarFile p2.grammar -lexiconFile p2.lexicon "S [i:<[id:_]>]"

#../src/elvex -grammarFile p2.grammar -lexiconFile p2.lexicon "S [i:<[id:v1], [id:v2]>]"
#../src/elvexdebug --traceInit --traceAction --traceShift --traceReduce --traceClose --traceStage -grammarFile p2.grammar -lexiconFile p2.lexicon "S [i:<[id:v1], [id:v2]>]" > p2.html ; open p2.html

cd ..
