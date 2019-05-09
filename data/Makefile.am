.PHONY: all output debug

SUBDIRS = lefff
ELVEX = ../src/elvex
ELVEXDEBUG = ../src/elvexdebug
POSTEDITION = ../src/elvexpostedition
CLEANFILES = $(patsubst %.input, %.output, $(wildcard *.input)) $(patsubst %.input, %.xml, $(wildcard *.input)) $(patsubst %.input, %.err, $(wildcard *.input)) $(patsubst %.input, %.html, $(wildcard *.input)) $(patsubst %.input, %.jpg, $(wildcard *.input))

all: output

clean:
	rm $(CLEANFILES)

output: $(patsubst %.input, %.output, $(wildcard *.input))

debug: $(patsubst %.input, %.jpg, $(wildcard *.input))

%.output: %.input %.lexicon %.grammar $(ELVEX) $(POSTEDITION) lefff/lefff.fsa Makefile
	$(ELVEX) -compactDirectory lefff -compactLexiconFile lefff -grammarFile $*.grammar -lexiconFile $*.lexicon -inputFile $*.input 2> $*.err | $(POSTEDITION) | sed -e 's/^ //' > $@
	@echo "\n\n\n";
	@cat $@
	@echo "\n";

%.xml: %.input %.lexicon %.grammar $(ELVEX) $(POSTEDITION) lefff/lefff.fsa Makefile
	$(ELVEXDEBUG) -compactDirectory lefff -compactLexiconFile lefff -grammarFile $*.grammar -lexiconFile $*.lexicon -inputFile $*.input -xml $*.xml 2> $*.html > /dev/null

%.dot: %.xml ../xsl/xml2dot.xsl
	xsltproc ../xsl/xml2dot.xsl $*.xml > $@

%.jpg: %.dot
	dot -T jpg -o $@ $<
