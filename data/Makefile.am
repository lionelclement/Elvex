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

.PHONY: all output debug

SUBDIRS = lefff kalaba
ELVEX = ../src/elvex
ELVEXDEBUG = ../src/elvexdebug --traceStage --traceClose --traceShift --traceReduce --traceAction 
BUILDLEXICON = ../src/elvexbuildlexicon
POSTEDITION = ../src/elvexpostedition
CLEANFILES = $(patsubst %.input, %.output, $(wildcard *.input)) $(patsubst %.input, %.xml, $(wildcard *.input)) $(patsubst %.input, %.err, $(wildcard *.input)) $(patsubst %.input, %.html, $(wildcard *.input)) $(patsubst %.input, %.jpg, $(wildcard *.input))

all:

check: $(ELVEX) $(POSTEDITION) lefff/lefff.fsa Makefile
	@$(ELVEX) -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile fr-1.0.3.grammar -lexiconFile fr-1.0.3.local-lexicon "letter [PRED:letter, i:[FORM:\"`whoami`\", number:sg, gender:ms], ii:[PRED:_installer, i:[PRED:__pro, number:pl, person:two], ii:[FORM:\"Elvex\"], tense:recent_past], iii:[FORM:\"Lionel Clément\"]]" |tr '@' "\n" | $(POSTEDITION) | sed -e 's/^ *//'

clean:
	rm $(CLEANFILES)

adj: $(patsubst %.input, %.output, $(wildcard adj.input)) $(patsubst %.input, %.xml, $(wildcard adj.input))

p1: $(patsubst %.input, %.output, $(wildcard p1.input)) $(patsubst %.input, %.xml, $(wildcard p1.input))

%.output: %.input %.lexicon %.grammar $(ELVEX) $(POSTEDITION) lefff/lefff.fsa Makefile
	@echo $@ ':'
	@$(ELVEX) -maxTime 300 -compactDirectory lefff -compactLexiconFile lefff -grammarFile $*.grammar -lexiconFile $*.lexicon -inputFile $*.input 2> $*.err | $(POSTEDITION) | sed -e 's/^ //' > $@
	@cat $@
	@echo "\n"

%.xml: %.input %.lexicon %.grammar $(ELVEX) $(POSTEDITION) lefff/lefff.fsa Makefile
	$(ELVEXDEBUG) -compactLexiconDirectory lefff -compactLexiconFile lefff -grammarFile $*.grammar -lexiconFile $*.lexicon -inputFile $*.input -xml $*.xml &> $*.html

%.dot: %.xml ../xsl/xml2dot.xsl
	xsltproc ../xsl/xml2dot.xsl $*.xml > $@

%.jpg: %.dot
	dot -T jpg -o $@ $<

%.fsa: %.formPosLemmaFeatures %.tmp-pattern
	@echo "build $@ from $*.formPosLemmaFeatures $*.pattern"
	$(BUILDLEXICON) -compactLexiconDirectory . -compactLexiconFile $* -patternFile $*.pattern -morphoFile $*.formPosLemmaFeatures build

%.formPosLemmaFeatures: %.form %.pos %.lemma %.features
	@echo "build $@ from $^"
	@paste $*.form $*.pos $*.lemma $*.features > $@

%.form: %.tmp-morpho
	@echo "build $@ from $^"
	@grep -v '^//' < $< | cut -f1 > $@

%.pos: %.tmp-morpho
	@echo "build $@ from $^"
	@grep -v '^//' < $< | cut -f2 > $@

%.lemma: %.tmp-morpho
	@echo "build $@ from $^"
	@cut -f3 < $< | tr '\-/\.' '____' > $@

%.features: %.tmp-morpho
	@echo "build $@ from $^"
	@cut -f4 < $< | tr '\-/\.' '____' > $@

%.tmp-pattern: %.pattern
	@echo "build $@ from $^"
	@sed -e '/^\/\//d' -e '/^[ 	]*$$/d' < $< | tr '\-/\.' '____' | sort -u > $@

%.tmp-morpho: %.morpho
	@echo "build $@ from $^"
	@sed -e '/^#/d' -e '/^\/\//d' -e '/^[ 	]*$$/d' < $< | sort -u > $@
