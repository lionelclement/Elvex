# Build all Elvex .input files into LilyPond .ly, .pdf and .midi outputs.
#
# Usage:
#   make            build all .pdf and .midi outputs
#   make -k         keep going after errors
#   make ly         generate only .ly files
#   make pdf        generate .pdf files
#   make midi       generate .midi files when LilyPond produces them
#   make list       show input classification
#   make check      show obsolete/experimental inputs if any are present
#   make clean      remove generated outputs
#   make rebuild    clean then build

ELVEX    ?= elvex
LILYPOND ?= lilypond

RULES       ?= music.rules
SCALE_RULES ?= scale.rules
LEXICON     ?= music.lexicon
# Fichiers inclus par music.rules/music.lexicon qui ne sont pas vus automatiquement par make.
EXTRA_RULES    ?= $(wildcard circus.rules)
EXTRA_LEXICONS ?= $(wildcard circus.lexicon)
RULE_DEPS       := $(RULES) $(LEXICON) $(EXTRA_RULES) $(EXTRA_LEXICONS)
SCALE_RULE_DEPS := $(SCALE_RULES) $(LEXICON) $(EXTRA_RULES) $(EXTRA_LEXICONS)
LOG         ?= log.txt

INPUTS := $(wildcard *.input)

# Scale inputs are selected by filename.  The selected rule file currently
# delegates to music.rules, but keeping the variable separate makes the build
# layout explicit and future-proof.
SCALE_INPUTS := $(foreach f,$(INPUTS),$(if $(findstring scales,$(f)),$(f)))
MUSIC_INPUTS := $(filter-out $(SCALE_INPUTS),$(INPUTS))

LY     := $(INPUTS:.input=.ly)
PDF    := $(INPUTS:.input=.pdf)
MIDI   := $(INPUTS:.input=.midi)
STAMPS := $(INPUTS:.input=.lilypond.stamp)

SCALE_LY := $(SCALE_INPUTS:.input=.ly)
MUSIC_LY := $(MUSIC_INPUTS:.input=.ly)

# Sous-ensemble pratique pour les exemples de cirque.
CIRCUS_INPUTS := $(foreach f,$(INPUTS),$(if $(findstring circus,$(f)),$(f)))
CIRCUS_LY     := $(CIRCUS_INPUTS:.input=.ly)
CIRCUS_PDF    := $(CIRCUS_INPUTS:.input=.pdf)
CIRCUS_MIDI   := $(CIRCUS_INPUTS:.input=.midi)

OBSOLETE_INPUTS := \
	500_roles_flute_piano.input \
	501_roles_string_quartet.input \
	502_roles_custom_mixed.input

PRESENT_OBSOLETE_INPUTS := $(wildcard $(OBSOLETE_INPUTS))

.PHONY: all ly pdf midi circus circus-ly circus-pdf circus-midi clean distclean rebuild list check
.SECONDARY: $(STAMPS)
.DELETE_ON_ERROR:

all: check pdf midi

ly: check $(LY)

pdf: check $(PDF)

midi: check $(MIDI)

circus: circus-pdf circus-midi

circus-ly: check $(CIRCUS_LY)

circus-pdf: check $(CIRCUS_PDF)

circus-midi: check $(CIRCUS_MIDI)

rebuild: clean all

check:
	@if test -n "$(PRESENT_OBSOLETE_INPUTS)"; then \
		echo "WARNING: obsolete/experimental inputs are still present:"; \
		printf "  %s\n" $(PRESENT_OBSOLETE_INPUTS); \
		echo "They are not part of the cleaned archive and may produce empty or invalid .ly files."; \
		echo "Remove them or move them outside this directory."; \
	fi

ifneq ($(strip $(SCALE_LY)),)
$(SCALE_LY): %.ly: %.input $(SCALE_RULE_DEPS)
	@echo "ELVEX-SCALE $< -> $@"
	@$(ELVEX) --rules-file $(SCALE_RULES) --lexicon-file $(LEXICON) --input-file $< -f > $@ 2>> $(LOG)
	@test -s $@ || { echo "ERROR: Elvex produced an empty file: $@"; echo "Last log lines:"; tail -80 $(LOG); exit 1; }
	@grep -q '\\score' $@ || { echo "WARNING: no \\score found in $@"; }
endif

ifneq ($(strip $(MUSIC_LY)),)
$(MUSIC_LY): %.ly: %.input $(RULE_DEPS)
	@echo "ELVEX $< -> $@"
	@$(ELVEX) --rules-file $(RULES) --lexicon-file $(LEXICON) --input-file $< -f > $@ 2>> $(LOG)
	@test -s $@ || { echo "ERROR: Elvex produced an empty file: $@"; echo "Last log lines:"; tail -80 $(LOG); exit 1; }
	@grep -q '\\score' $@ || { echo "WARNING: no \\score found in $@"; }
endif

%.lilypond.stamp: %.ly
	@echo "LILYPOND $<"
	@$(LILYPOND) $< >> $(LOG) 2>&1 || { \
		echo "ERROR: LilyPond failed for $<"; \
		echo "Last log lines:"; \
		tail -80 $(LOG); \
		exit 1; \
	}
	@touch $@

%.pdf: %.lilypond.stamp
	@test -f $@ || { echo "ERROR: LilyPond did not produce $@"; echo "Last log lines:"; tail -80 $(LOG); exit 1; }

%.midi: %.lilypond.stamp
	@if test -f $@; then \
		true; \
	else \
		echo "WARNING: LilyPond did not produce $@"; \
	fi

list:
	@echo "Scale inputs:"
	@printf "  %s\n" $(SCALE_INPUTS)
	@echo
	@echo "Music inputs:"
	@printf "  %s\n" $(MUSIC_INPUTS)
	@echo
	@echo "Circus inputs:"
	@printf "  %s\n" $(CIRCUS_INPUTS)
	@echo
	@echo "Generated .ly:"
	@printf "  %s\n" $(LY)

clean:
	rm -f $(LY) $(PDF) $(MIDI) $(STAMPS)
	rm -f *.ps *.eps *.count
	rm -f *.log

distclean: clean
	rm -f $(LOG)
