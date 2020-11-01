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

CLEANFILES = lefff.fsa lefff.tbl
BUILDLEXICON = elvexbuildlexicon

all: lefff.fsa

%.fsa: %.morpho %.pattern
	@echo "build $@ from $*.formPosLemmaFeatures $*.pattern"
	$(BUILDLEXICON) -compactedLexiconDirectory . -compactedLexiconFile $* -patternFile $*.pattern -morphoFile $*.morpho build

%.morpho: %.morpho.gz
	@echo "build $@ from $^"
	@gunzip < $^ |sed -e '/^#/d' -e '/^\/\//d' -e '/^[ 	]*$$/d' | sort -u > $@

%.pattern: %.pattern.gz
	@echo "build $@ from $^"
	@gunzip < $^ |sed -e '/^#/d' -e '/^\/\//d' -e '/^[ 	]*$$/d' | sort -u > $@

%.pattern: %.general.pattern %.slang.pattern %.phaseology.pattern %.weather.pattern
	@echo "build $@ from $^"
	@cat $^ | sed -e '/^#/d' -e '/^\/\//d' | sort -u > $@

%.morpho:  %.general.morpho %.slang.morpho
	@echo "build $@ from $^"
	@cat $*.macro | sed -e '/^#/d' -e '/^\/\//d' > $@
	@cat $^ | sed -e '/^#/d' -e '/^\/\//d' | sort -u >> $@
