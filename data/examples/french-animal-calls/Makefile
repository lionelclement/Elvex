# Animal experiment — Elvex morphology and sentence generation
ELVEX ?= elvex
ELVEXLEXICON ?= elvexlexicon

.DEFAULT_GOAL := run
.PHONY: all run lexicon trace clean help

all: run

# Build the compacted lexicon using the exact command used for this experiment.
lexicon:
	$(ELVEXLEXICON) \
	  --compacted-lexicon-file french-animal-calls \
	  --macros-file french-animal-calls.macros \
	  --pattern-file french-animal-calls.pattern \
	  --morpho-file french-animal-calls.morpho \
	  build

# Elvex writes all generated sentences directly to standard output.
run: lexicon
	$(ELVEX) \
	  --macros-file french-animal-calls.macros \
	  --rules-file french-animal-calls.rules \
	  --lexicon-file french-animal-calls.lexicon \
	  --compacted-lexicon-file french-animal-calls \
	  --input-file french-animal-calls.stdin

# Trace generation (optional; the trace is saved as HTML).
trace: lexicon
	$(ELVEX) \
	  --macros-file french-animal-calls.macros \
	  --rules-file french-animal-calls.rules \
	  --lexicon-file french-animal-calls.lexicon \
	  --compacted-lexicon-file french-animal-calls \
	  --input-file french-animal-calls.stdin \
	  --trace-all > french-animal-calls-trace.html

# Remove generated trace, diagnostics, and compiled lexicon files.
clean:
	rm -f french-animal-calls-trace.html french-animal-calls.out french-animal-calls.log .french-animal-calls-lexicon.stamp french-animal-calls.fsa french-animal-calls.tbl

help:
	@echo 'make / make run    Compile the compacted lexicon, then print all sentences'
	@echo 'make lexicon       Compile morphology and patterns using the build argument'
	@echo 'make trace         Generate french-animal-calls-trace.html'
	@echo 'make clean         Remove generated files'
