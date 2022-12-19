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
.SUFFIXES: .fsa .morpho .pattern .morpho.gz .pattern.gz .general.pattern .sem.pattern .slang.pattern .weather.pattern .weather.slang.pattern .weather.inhouse.pattern .20210328.pattern .phraseology.pattern .general.morpho .slang.morpho
CLEANFILES = lefff.fsa lefff.tbl
BUILDLEXICON = ../../bin/elvexbuildlexicon

all: lefff.fsa

lefff.fsa: lefff.morpho lefff.pattern
	@echo "build $@ from $*.formPosLemmaFeatures $*.pattern"
	$(BUILDLEXICON) -compactedLexiconDirectory . -compactedLexiconFile $* -patternFile $*.pattern -morphoFile $*.morpho build

lefff.general.morpho: lefff.general.morpho.gz
	@echo "build $@ from $^"
	@gunzip < $^ |sed -e '/^#/d' -e '/^\/\//d' -e '/^[ 	]*$$/d' | sort -u > $@

lefff.general.pattern: lefff.general.pattern.gz
	@echo "build $@ from $^"
	@gunzip < $^ |sed -e '/^#/d' -e '/^\/\//d' -e '/^[ 	]*$$/d' | sort -u > $@

lefff.pattern: lefff.general.pattern lefff.sem.pattern lefff.slang.pattern lefff.weather.pattern lefff.weather.slang.pattern lefff.weather.inhouse.pattern lefff.20210328.pattern lefff.phraseology.pattern
	@echo "build $@ from $^"
	@cat $^ | sed -e '/^#/d' -e '/^\/\//d' | sort -u > $@

lefff.morpho:  lefff.general.morpho lefff.slang.morpho
	@echo "build $@ from $^"
	@cat $*.macro | sed -e '/^#/d' -e '/^\/\//d' > $@
	@cat $^ | sed -e '/^#/d' -e '/^\/\//d' | sort -u >> $@
