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
#echo 'bin/elvex -cld data -clf en-1.1.0 -rulesFile data/en-1.1.0.rules -lexiconFile data/en-1.1.0.lexicon "Text[PRED:TO_APPRECIATE, i:[PRED:_YOU], ii:[PRED:ELVEX], vtense:future]" | bin/elvexpostedition_en'
../bin/elvex -cld . -clf en-1.1.0 -rulesFile en-1.1.0.rules -lexiconFile en-1.1.0.lexicon "Text[PRED:TO_APPRECIATE, i:[PRED:_YOU], ii:[PRED:ELVEX], vtense:future]" | ../bin/elvexpostedition_en
#../bin/elvexdebug --traceShift --traceInit --traceStage --traceClose --traceReduce --traceAction -compactedLexiconDirectory . -compactedLexiconFile en-1.1.0 -rulesFile en-1.1.0.rules -lexiconFile en-1.1.0.lexicon 'Text[PRED:TO_APPRECIATE, i:[PRED:_YOU], ii:[PRED:ELVEX], vtense:future]'
#../bin/elvexdebug --traceShift --traceInit --traceStage --traceClose --traceReduce -compactedLexiconDirectory . -compactedLexiconFile en-1.1.0 -rulesFile en-1.1.0.rules -lexiconFile en-1.1.0.lexicon 'Text[PRED:TO_APPRECIATE, i:[PRED:_YOU], ii:[PRED:ELVEX], vtense:future]'

##################################################
# slang
#(cd lefff ; make -s)
#(cd .. ; make -j 7)
#../bin/elvexdebug --traceInit --traceStage --traceClose --traceShift --traceReduce -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-slang.rules -lexiconFile fr-slang.lexicon -inputFile fr-slang.input| ../bin/elvexpostedition_fr
#echo "##################################################"
#/Users/clement/tmp/Elvex/bin/elvexdebug --traceInit --traceStage --traceClose --traceShift --traceReduce -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-slang.rules -lexiconFile fr-slang.lexicon -inputFile fr-slang.input
#../bin/elvex -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-slang.rules -lexiconFile fr-slang.lexicon -inputFile fr-slang.input
#echo "##################################################"
#/Users/clement/tmp/Elvex/bin/elvex -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-slang.rules -lexiconFile fr-slang.lexicon -inputFile fr-slang.input

#../bin/elvex -t -V -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-slang.rules -lexiconFile fr-slang.lexicon -inputFile fr-slang.input
#../bin/elvexdebug -t -V --traceInit --traceStage --traceClose --traceShift --traceReduce --traceAction -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-slang.rules -lexiconFile fr-slang.lexicon -inputFile fr-slang.input
#../bin/elvexdebug --traceInit --traceStage --traceClose --traceShift --traceReduce -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-slang.rules -lexiconFile fr-slang.lexicon -inputFile fr-slang.input
#../bin/elvexdebug --traceInit --traceStage --traceClose --traceShift --traceReduce -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-slang.rules -lexiconFile fr-slang.lexicon -inputFile fr-slang.input > ../bad.html
#/Users/clement/tmp/Elvex/bin/elvexdebug --traceInit --traceStage --traceClose --traceShift --traceReduce -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-slang.rules -lexiconFile fr-slang.lexicon -inputFile fr-slang.input > ../good.html

##################################################
# fr-1.0.4
#(cd lefff ; make -s)
#../bin/elvex -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-1.0.4.rules -lexiconFile fr-1.0.4.lexicon -inputFile fr-1.0.4.input | ../bin/elvexpostedition_fr |tr '@' "\n" |sed -e 's/^ *//' |tr '@' "\n"
#../bin/elvexdebug -t -V --traceInit --traceStage --traceClose --traceShift --traceReduce --traceAction -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-1.0.4.rules -lexiconFile fr-1.0.4.lexicon -inputFile fr-1.0.4.input
#../bin/elvexdebug --traceAction --traceInit --traceClose --traceShift --traceReduce --traceStage -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-1.0.4.rules -lexiconFile fr-1.0.4.lexicon -inputFile fr-1.0.4.input
#/Users/clement/tmp/Elvex/bin/elvexdebug --traceClose --traceShift --traceReduce --traceStage -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-1.0.4.rules -lexiconFile fr-1.0.4.lexicon -inputFile fr-1.0.4.input

##################################################
# essai-20221012
#make essai-20221012.fsa
#../bin/elvex -cld . -clf essai-20221012 -rulesFile essai-20221012.rules -lexiconFile essai-20221012.lexicon -inputFile essai-20221012.input
#../bin/elvexdebug --traceInit --traceStage --traceClose --traceShift --traceReduce --traceAction -cld . -clf essai-20221012 -rulesFile essai-20221012.rules -lexiconFile essai-20221012.lexicon -inputFile essai-20221012.input

##################################################
# test1
#../bin/elvexdebug --traceAction --traceInit --traceStage --traceClose --traceShift --traceReduce --traceAction -rulesFile test1.rules -lexiconFile test1.lexicon -inputFile test1.input
#../bin/elvex -rulesFile test1.rules -lexiconFile test1.lexicon -inputFile test1.input
#echo "_____"
#/Users/clement/tmp/Elvex/bin/elvex -rulesFile test1.rules -lexiconFile test1.lexicon -inputFile test1.input

##################################################
# test2
#../bin/elvexdebug --traceAction --traceInit --traceStage --traceClose --traceShift --traceReduce --traceAction -rulesFile test2.rules -lexiconFile test2.lexicon -inputFile test2.input
#../bin/elvex -rulesFile test2.rules -lexiconFile test2.lexicon -inputFile test2.input
#echo "_____"
#/Users/clement/tmp/Elvex/bin/elvex -rulesFile test2.rules -lexiconFile test2.lexicon -inputFile test2.input

cd ..
