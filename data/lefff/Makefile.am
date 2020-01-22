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
BUILDLEXICON = ../../src/elvexbuildlexicon

all: lefff.fsa

%.fsa: %.formPosLemmaFeatures %.pattern
	@echo "build $@ from $*.formPosLemmaFeatures $*.pattern"
	$(BUILDLEXICON) -compactLexiconDirectory . -compactLexiconFile $* -patternFile $*.pattern -morphoFile $*.formPosLemmaFeatures build

%.morpho: %.bz2 %.slang.bz2
	@echo "build $@ from $^"
	@bunzip2 -c $^ |sed -e '/^#/d' -e '/^\/\//d' -e '/^[ 	]*$$/d' | sort -u > $@

%.formPosLemmaFeatures: %.form %.pos %.lemma %.features
	@echo "build $@ from $^"
	@paste $*.form $*.pos $*.lemma $*.features > $@

%.form: %.morpho
	@echo "build $@ from $^"
	@grep -v '^//' < $< | cut -f1 > $@

%.pos: %.morpho
	@echo "build $@ from $^"
	@grep -v '^//' < $< | cut -f2 > $@

%.lemma: %.morpho
	@echo "build $@ from $^"
	@cut -f3 < $< | tr '\-/\.' '____' > $@

%.features: %.morpho
	@echo "build $@ from $^"
	@cut -f4 < $< | tr '\-/\.' '____' > $@

%.pattern: %.general.pattern.bz2 %.slang.pattern.bz2 %.phaseology.pattern.bz2 %.weather.pattern.bz2
	@echo "build $@ from $^"
	@bunzip2 -c $^ | sed -e '/^#/d' -e '/^\/\//d' -e '/^[ 	]*$$/d' | tr '\-/\.' '____' | sort -u > $@

%.auto.pattern: %.lemma %.pos
	@echo "build $@ from $^"
	@paste $*.lemma $*.pos | sed 's/^\([^	]*\)	\([^	]*\)/\1#\2	\1	PRED:_\1/' | grep '#\(n\|pn\|v\|adj\|adv\)	' | sort -u > $@
	@paste $*.lemma $*.pos | sed 's/^\([^	]*\)Je ce	\([^	]*\)/\1#\2	\1	/' | grep -v '#\(n\|pn\|v\|adj\|adv\)	' | sort -u >> $@
