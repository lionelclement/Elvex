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

.PHONY: all output debug check

SUBDIRS = lefff
ELVEX = ../bin/elvex
ELVEXDEBUG = ../bin/elvexdebug --traceStage --traceClose --traceShift --traceReduce --traceAction
BUILDLEXICON = ../bin/elvexbuildlexicon
POSTEDITION_FR = ../bin/elvexpostedition_fr
XSL = ../xsl/xml2dot.xsl
CLEANFILES = $(patsubst %.input, %.output, $(wildcard *.input)) $(patsubst %.input, %.xml, $(wildcard *.input)) $(patsubst %.input, %.err, $(wildcard *.input)) $(patsubst %.input, %.html, $(wildcard *.input)) $(patsubst %.input, %.jpg, $(wildcard *.input))

.SUFFIXES: .xml .dot .jpg

all: $(patsubst %.input, %.output, $(wildcard *.input))

check: lefff/lefff.fsa
	@$(ELVEX) -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile fr-1.0.4.rules -lexiconFile fr-1.0.4.lexicon "noun [PRED:ARBRE, mod:<[PRED:CREUX], [PRED:PETIT]>]" | $(POSTEDITION_FR)

clean:
	rm $(CLEANFILES)

adj.output: adj.input adj.lexicon adj.rules
	@$(ELVEX) -rulesFile adj.rules -lexiconFile adj.lexicon -inputFile adj.input 2> adj.err > $@
	@cat $@

%.output: %.input %.lexicon %.rules $(ELVEX) $(POSTEDITION_FR) lefff/lefff.fsa Makefile
	@$(ELVEX) -maxTime 300 -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile $*.rules -lexiconFile $*.lexicon -inputFile $*.input 2> $*.err | $(POSTEDITION_FR) | sed -e 's/^ //' > $@
	@cat $@

%.xml: %.input %.lexicon %.rules $(ELVEX) $(POSTEDITION_FR) lefff/lefff.fsa Makefile
	$(ELVEXDEBUG) -compactedLexiconDirectory lefff -compactedLexiconFile lefff -rulesFile $*.rules -lexiconFile $*.lexicon -inputFile $*.input -xml $*.xml &> $*.html

%.dot: %.xml $(XSL)
	xsltproc $(XSL) $*.xml > $@

%.jpg: %.dot
	dot -T jpg -o $@ $<

%.fsa: %.tmp-morpho %.tmp-pattern
	@echo "build $@ from $*.tmp-morpho $*.tmp-pattern"
	$(BUILDLEXICON) -cld . -clf $* -patternFile $*.tmp-pattern -morphoFile $*.tmp-morpho build

%.tmp-morpho: %.tmp-form %.tmp-pos %.tmp-lemma %.tmp-features
	@echo "build $@ from $^"
	@paste $*.tmp-form $*.tmp-pos $*.tmp-lemma $*.tmp-features > $@

%.tmp-form: %.tmp-fplf
	@echo "build $@ from $^"
	@grep -v '^//' < $< | cut -f1 > $@

%.tmp-pos: %.tmp-fplf
	@echo "build $@ from $^"
	@grep -v '^//' < $< | cut -f2 > $@

%.tmp-lemma: %.tmp-fplf
	@echo "build $@ from $^"
	@cut -f3 < $< | tr '\-/\.' '____' > $@

%.tmp-features: %.tmp-fplf
	@echo "build $@ from $^"
	@cut -f4 < $< | tr '\-/\.' '____' > $@

%.tmp-pattern: %.pattern
	@echo "build $@ from $^"
	@sed -e '/^#/d' -e '/^\/\//d' -e '/^[ 	]*$$/d' < $< | tr '\-/\.' '____' | sort -u > $@

%.tmp-fplf: %.morpho
	@echo "build $@ from $^"
	@sed -e '/^#/d' -e '/^\/\//d' -e '/^[ 	]*$$/d' < $< | sort -u > $@
