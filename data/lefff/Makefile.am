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

SUFFIXES: .fsa .tbl .pattern .lefff.bz2 .manual.pattern .manual.pattern.bz2

CLEANFILES = lefff.fsa lefff.tbl
BUILDLEXICON = ../../src/elvexbuildlexicon

all: lefff.pattern lefff.fsa

%.fsa: %.lefff %.manual.pattern
	@echo "build $@ with $^"
	@$(BUILDLEXICON) -compactLexiconDirectory . -compactLexiconFile $* -patternFile $*.manual.pattern build $<

%.form: %.lefff
	@echo "build $@ with $^"
	@grep -v '^//' < $< | cut -f1 > $@

%.pos: %.lefff
	@echo "build $@ with $^"
	@grep -v '^//' < $< | cut -f2 > $@

%.lemma: %.lefff
	@echo "build $@ with $^"
	@grep -v '^//' < $< | cut -f3 > $@

%.morpho: %.lefff
	@echo "build $@ with $^"
	@grep -v '^//' < $< | cut -f4 > $@

%.complete: %.lefff %.pattern completeLefff.pl 
	@echo "build $@ with $^"
	@perl completeLefff.pl $*.lefff $*.pattern > $@

%.lefff: %.lefff.bz2
	@echo "unzip $@"
	@bunzip2 -c $< > $@

%.manual.pattern: %.manual.pattern.bz2
	@echo "unzip $@"
	@bunzip2 -c $< > $@

%.lemma2: %.lemma
	@echo "build $@ with $^"
	@tr '-' '_' < $< > $@

%.pattern: %.form %.pos %.lemma2 %.morpho
	@echo "build $@ with $^"
	@paste $*.form $*.pos $*.lemma2 $*.morpho | grep -v '#' | sed 's/^\([^	]*\)	\([^	]*\)	\([^	]*\)	\([^	]*\)/\2	\3	\3	PRED:_\3]/' | grep '^\(n\|v\|adj\|adv\)	' | grep '_[[:alpha:]][[:alpha:]]*\]' | sed 's/\]//' | sort -u > $@
	@paste $*.form $*.pos $*.lemma2 $*.morpho | grep -v '#' | sed 's/^\([^	]*\)	\([^	]*\)	\([^	]*\)	\([^	]*\)/\2	\3	\3	/' | grep -v '^\(n\|v\|adj\|adv\)	' | sort -u >> $@

