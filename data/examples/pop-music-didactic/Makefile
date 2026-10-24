ELVEX    ?= elvex
LILYPOND ?= lilypond
RULES    ?= music.rules
LEXICON  ?= music.lexicon
LOG      ?= log.txt

INPUTS := $(wildcard *.input)
LY     := $(INPUTS:.input=.ly)
PDF    := $(INPUTS:.input=.pdf)
MIDI   := $(INPUTS:.input=.midi)
STAMPS := $(INPUTS:.input=.lilypond.stamp)

RULE_DEPS := $(RULES) $(LEXICON) pop_didactic.rules common.lexicon chords.lexicon

.PHONY: all ly pdf midi list clean rebuild trace-001 trace-002 trace-003 trace-004
.SECONDARY: $(STAMPS)
.DELETE_ON_ERROR:

all: pdf midi
ly: $(LY)
pdf: $(PDF)
midi: $(MIDI)

%.ly: %.input $(RULE_DEPS)
	@echo "ELVEX $< -> $@"
	@$(ELVEX) --rules-file $(RULES) --lexicon-file $(LEXICON) --input-file $< -f > $@ 2>> $(LOG)
	@test -s $@ || { echo "ERROR: Elvex produced an empty file: $@"; echo "Last log lines:"; tail -80 $(LOG); exit 1; }
	@grep -q '\\score' $@ || { echo "WARNING: no \\score found in $@"; }

%.lilypond.stamp: %.ly
	@echo "LILYPOND $<"
	@$(LILYPOND) $< >> $(LOG) 2>&1 || { echo "ERROR: LilyPond failed for $<"; tail -80 $(LOG); exit 1; }
	@touch $@

%.pdf: %.lilypond.stamp
	@test -f $@ || { echo "ERROR: LilyPond did not produce $@"; tail -80 $(LOG); exit 1; }

%.midi: %.lilypond.stamp
	@if test -f $@; then true; else echo "WARNING: LilyPond did not produce $@"; fi

list:
	@echo "Inputs:"
	@printf "  %s\n" $(INPUTS)

trace-001:
	$(ELVEX) --trace-all --rules-file $(RULES) --lexicon-file $(LEXICON) --input-file 001_chanson_francaise_voix_guitare_djembe.input -f > log-001.html

trace-002:
	$(ELVEX) --trace-all --rules-file $(RULES) --lexicon-file $(LEXICON) --input-file 002_english_pop_piano_band.input -f > log-002.html

trace-003:
	$(ELVEX) --trace-all --rules-file $(RULES) --lexicon-file $(LEXICON) --input-file 003_couleurs_flute_clarinette_sax_violon.input -f > log-003.html

trace-004:
	$(ELVEX) --trace-all --rules-file $(RULES) --lexicon-file $(LEXICON) --input-file 004_refrain_pop_avec_cuivres.input -f > log-004.html

rebuild: clean all

clean:
	rm -f $(LY) $(PDF) $(MIDI) $(STAMPS)
	rm -f *.ps *.eps *.count *.log $(LOG) log.html log-*.html
