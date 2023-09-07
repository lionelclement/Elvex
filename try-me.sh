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

#for i in 0 1 2 3
#do
    #./bin/elvex --trace -rulesFile data/test$i.rules -lexiconFile data/test$i.lexicon -inputFile data/test$i.input
    #./bin/elvex -rulesFile data/test$i.rules -lexiconFile data/test$i.lexicon -inputFile data/test$i.input
#done

#(cd data ; ../bin/elvex -V -rulesFile fr-slang.rules)

##################################################
make -C data en-1.1.0.fsa
./bin/elvex -cld data -clf en-1.1.0 -rulesFile data/en-1.1.0.rules -lexiconFile data/en-1.1.0.lexicon -inputFile data/en-1.1.0.input
#./bin/elvex --trace -cld data -clf en-1.1.0 -rulesFile data/en-1.1.0.rules -lexiconFile data/en-1.1.0.lexicon -inputFile data/en-1.1.0.input > data/en-1.1.0.html ; open data/en-1.1.0.html
#./bin/elvex --traceAction -cld data -clf en-1.1.0 -rulesFile data/en-1.1.0.rules -lexiconFile data/en-1.1.0.lexicon -inputFile data/en-1.1.0.input > data/en-1.1.0.html ; open data/en-1.1.0.html
#./bin/elvex --trace -cld data -clf en-1.1.0 -rulesFile data/en-1.1.0.rules -lexiconFile data/en-1.1.0.lexicon -inputFile data/en-1.1.0.input > data/en-1.1.0.html ; open data/en-1.1.0.html
#lldb bin/elvex -- -cld data -clf en-1.1.0 -rulesFile data/en-1.1.0.rules -lexiconFile data/en-1.1.0.lexicon -inputFile data/en-1.1.0.input

#make -C data br-1.0.0.fsa
#./bin/elvex --traceAll -cld data -clf br-1.0.0 -rulesFile data/br-1.0.0.rules -lexiconFile data/br-1.0.0.lexicon -inputFile data/br-1.0.0.input > data/br-1.0.0.html ; cat data/br-1.0.0.html
#./bin/elvex --trace -cld data -clf br-1.0.0 -rulesFile data/br-1.0.0.rules -lexiconFile data/br-1.0.0.lexicon -inputFile data/br-1.0.0.input > data/br-1.0.0.html ; cat data/br-1.0.0.html
#./bin/elvex -cld data -clf br-1.0.0 -rulesFile data/br-1.0.0.rules -lexiconFile data/br-1.0.0.lexicon -inputFile data/br-1.0.0.input

#lldb ./bin/elvex -- -cld data -clf br-1.0.0 -rulesFile data/br-1.0.0.rules -lexiconFile data/br-1.0.0.lexicon -inputFile data/br-1.0.0.input
#./bin/elvex -cld data -clf br-1.0.0 -rulesFile data/br-1.0.0.rules -lexiconFile data/br-1.0.0.lexicon -inputFile data/br-1.0.0.input

