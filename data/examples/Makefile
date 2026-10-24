# ============================================================
# ELVEX - shared example Makefile (GNU Make >= 4.3)
# Usage: make DATA=english-sentences random SEED=42 MAX_TIME=30
# ============================================================

# Run from data/examples, e.g. make -C data/examples DATA=french-animal-calls run
PROJECT_ROOT := $(abspath $(CURDIR)/../..)
ELVEX ?= $(PROJECT_ROOT)/build/bin/elvex
ELVEXLEXICON ?= $(PROJECT_ROOT)/build/bin/elvexlexicon
DATA ?= english-sentences
DIR := $(patsubst %/,%,$(DATA))

.DEFAULT_GOAL := help
.PHONY: all run lexicon exhaustive sample beam random first \
        sample-random beam-random reduce-all output trace debug xml \
        info check clean rebuild help

# Files are checked only by targets that actually use them.
# Thus help, check, and clean do not require a valid DATA directory.
define require_one
$(if $(filter 1,$(words $(2))),$(firstword $(2)),$(error Expected exactly one $(1) in $(DIR); found: $(2)))
endef

# An optional .macros file: no argument if absent.
define optional_one
$(if $(filter 0 1,$(words $(2))),$(firstword $(2)),$(error Expected at most one $(1) in $(DIR); found: $(2)))
endef

MACROS  = $(call optional_one,.macros,$(wildcard $(DIR)/*.macros))
RULES   = $(call require_one,.rules,$(wildcard $(DIR)/*.rules))
LEXICON = $(call require_one,.lexicon,$(wildcard $(DIR)/*.lexicon))
MORPHO  = $(call optional_one,.morpho,$(wildcard $(DIR)/*.morpho))
PATTERN = $(call optional_one,.pattern,$(wildcard $(DIR)/*.pattern))
# Existing suites use .input; newer suites use .stdin.  Accept either, never both.
INPUT   = $(call require_one,.stdin or .input,$(wildcard $(DIR)/*.stdin $(DIR)/*.input))

# Build a compacted lexicon only if both sources exist.
# A single source is an incomplete configuration.
HAS_MORPHO = $(if $(MORPHO),1,0)
HAS_PATTERN = $(if $(PATTERN),1,0)
BUILD_LEXICON = $(if $(and $(MORPHO),$(PATTERN)),1,)
validate_lexicon_pair = $(if $(filter-out $(HAS_MORPHO),$(HAS_PATTERN)),$(error Provide .morpho and .pattern together in $(DIR)),)

# Do not validate resources while loading the Makefile.
SOURCE_DEPS := $(wildcard $(DIR)/*.macros $(DIR)/*.morpho $(DIR)/*.pattern)

BUILD_DIR := $(DIR)/.elvex-build
CLF       := $(BUILD_DIR)/lexicon
FSA       := $(CLF).fsa
TBL       := $(CLF).tbl
OUTPUT    := $(BUILD_DIR)/sentences.txt
DEBUG_FILE := $(BUILD_DIR)/debug.html
XML_FILE  := $(BUILD_DIR)/sentences.xml

# Strategy: exhaustive | sample | beam
STRATEGY ?= exhaustive
# Selection: all | first | random
MODE ?= all
SEED ?=
REDUCE_ALL ?= 0
VERBOSE ?= 0
MAX_TIME ?=
MAX_LENGTH ?=
MAX_USAGES ?=
MAX_ITEMS ?=
MAX_ATTEMPTS ?=
MAX_RULE_CHOICES ?=
BEAM_WIDTH ?=
# TRACE_MODE accepts a comma-separated list of modes.
# By default, run has no traces; debug enables all traces.
TRACE_MODE ?= none
EXTRA_OPTS ?=

VALID_STRATEGIES := exhaustive sample beam
VALID_MODES := all first random
VALID_TRACES := none rules all init stage close shift reduce action
comma := ,
empty :=
space := $(empty) $(empty)
TRACE_MODES = $(strip $(subst $(comma),$(space),$(TRACE_MODE)))
UNKNOWN_TRACES = $(filter-out $(VALID_TRACES),$(TRACE_MODES))

validate_options = $(if $(filter $(STRATEGY),$(VALID_STRATEGIES)),,$(error Invalid STRATEGY : $(STRATEGY)))  $(if $(filter $(MODE),$(VALID_MODES)),,$(error Invalid MODE : $(MODE)))  $(if $(UNKNOWN_TRACES),$(error Invalid TRACE_MODE : $(UNKNOWN_TRACES)),)  $(if $(filter none,$(TRACE_MODES)),$(if $(filter-out none,$(TRACE_MODES)),$(error TRACE_MODE=none cannot be combined with other values),),)  $(if $(filter all,$(TRACE_MODES)),$(if $(filter-out all,$(TRACE_MODES)),$(error TRACE_MODE=all cannot be combined with other values),),)

define validate_sources
$(MACROS) $(RULES) $(LEXICON) $(INPUT) $(validate_lexicon_pair)
endef

ELVEX_FILES = \
  $(if $(MACROS),--macros-file "$(MACROS)") \
  --rules-file "$(RULES)" \
  --lexicon-file "$(LEXICON)" \
  $(if $(BUILD_LEXICON),--compacted-lexicon-file "$(CLF)") \
  --input-file "$(INPUT)"

SELECTION_OPTS = \
  $(if $(filter first,$(MODE)),--first) \
  $(if $(filter random,$(MODE)),--random)

TRACE_OPTS = $(foreach t,$(TRACE_MODES),$(if $(filter none,$(t)),,$(if $(filter rules,$(t)),--trace,$(if $(filter all,$(t)),--trace-all,--trace-$(t)))))

LIMIT_OPTS = \
  $(if $(MAX_TIME),--max-time $(MAX_TIME)) \
  $(if $(MAX_LENGTH),--max-length $(MAX_LENGTH)) \
  $(if $(MAX_USAGES),--max-usages $(MAX_USAGES)) \
  $(if $(MAX_ITEMS),--max-items $(MAX_ITEMS)) \
  $(if $(MAX_ATTEMPTS),--max-attempts $(MAX_ATTEMPTS)) \
  $(if $(MAX_RULE_CHOICES),--max-rule-choices $(MAX_RULE_CHOICES)) \
  $(if $(BEAM_WIDTH),--beam-width $(BEAM_WIDTH))

RUN_OPTS = \
  --strategy $(STRATEGY) \
  $(SELECTION_OPTS) \
  $(if $(SEED),--seed $(SEED)) \
  $(if $(filter 1,$(REDUCE_ALL)),--reduce-all) \
  $(if $(filter 1,$(VERBOSE)),--verbose) \
  $(LIMIT_OPTS) $(TRACE_OPTS) $(EXTRA_OPTS)

all: run

$(BUILD_DIR):
	mkdir -p "$@"

# Compiling the compacted lexicon produces two files (.fsa and .tbl).
ifeq ($(BUILD_LEXICON),1)
$(FSA) $(TBL) &: $(SOURCE_DEPS) | $(BUILD_DIR)
	@: $(validate_sources)
	$(ELVEXLEXICON) \
	  $(if $(BUILD_LEXICON),--compacted-lexicon-file "$(CLF)") \
	  $(if $(MACROS),--macros-file "$(MACROS)") \
	  --pattern-file "$(PATTERN)" \
	  --morpho-file "$(MORPHO)" \
	  build

lexicon: $(FSA) $(TBL)
else
lexicon:
	@: $(validate_lexicon_pair)
	@echo "No .morpho/.pattern pair: skipping lexicon compilation."
endif

run: lexicon
	@: $(validate_options) $(validate_sources)
	$(ELVEX) $(ELVEX_FILES) $(RUN_OPTS)

exhaustive: STRATEGY = exhaustive
exhaustive: run
sample: STRATEGY = sample
sample: run
beam: STRATEGY = beam
beam: run
random: MODE = random
random: run
first: MODE = first
first: run
sample-random: STRATEGY = sample
sample-random: MODE = random
sample-random: run
beam-random: STRATEGY = beam
beam-random: MODE = random
beam-random: run
reduce-all: REDUCE_ALL = 1
reduce-all: run

output: lexicon | $(BUILD_DIR)
	@: $(validate_options) $(validate_sources)
	$(ELVEX) $(ELVEX_FILES) $(RUN_OPTS) > "$(OUTPUT)"
	@echo "Sentences: $(OUTPUT)"

# Trace only rules annotated with @trace to the terminal.
# Example: make DATA=english-sentences trace
trace: TRACE_MODE = rules
trace: run

debug: TRACE_MODE = all
debug: lexicon | $(BUILD_DIR)
	@: $(validate_options) $(validate_sources)
	$(ELVEX) $(ELVEX_FILES) $(RUN_OPTS) > "$(DEBUG_FILE)"
	@echo "Trace: $(DEBUG_FILE)"

xml: lexicon | $(BUILD_DIR)
	@: $(validate_options) $(validate_sources)
	$(ELVEX) $(ELVEX_FILES) $(RUN_OPTS) --xml "$(XML_FILE)"
	@echo "XML : $(XML_FILE)"

info:
	@: $(validate_options) $(validate_sources)
	@echo "Directory: $(DIR)"
	@echo "Macros: $(MACROS)"
	@echo "Rules: $(RULES)"
	@echo "Lexicon: $(LEXICON)"
	@echo "Morphology: $(MORPHO)"
	@echo "Patterns: $(PATTERN)"
	@echo "Input: $(INPUT)"
	@echo "Compiled lexicon: $(if $(BUILD_LEXICON),$(CLF),(not used))"
	@echo "Strategy: $(STRATEGY) ; selection: $(MODE) ; traces: $(TRACE_MODE)"

check:
	@command -v "$(ELVEX)" >/dev/null || { echo "Executable not found: $(ELVEX)"; exit 1; }
	$(if $(BUILD_LEXICON),	@command -v "$(ELVEXLEXICON)" >/dev/null || { echo "Executable not found: $(ELVEXLEXICON)"; exit 1; },	@echo "elvexlexicon is not required for $(DIR).")
	@echo "ELVEX executables found."

clean:
	rm -rf "$(BUILD_DIR)"

rebuild:
	$(MAKE) -f "$(firstword $(MAKEFILE_LIST))" DATA="$(DATA)" clean
	$(MAKE) -f "$(firstword $(MAKEFILE_LIST))" DATA="$(DATA)" lexicon

help:
	@printf '%s\n' \
	  'ELVEX - SHARED EXAMPLE MAKEFILE' \
	  '' \
	  'USAGE' \
	  '  make DATA=<directory> [target] [VARIABLE=value ...]' \
	  '  Example: make DATA=english-sentences random SEED=42 MAX_TIME=30' \
	  '  Default DATA=english-sentences. Exactly one .input or .stdin is required.' \
	  '  .macros is optional; .morpho and .pattern must occur together.' \
	  '' \
	  'GENERATION (print to terminal)' \
	  '  run             Default generation (exhaustive, all results).' \
	  '  exhaustive      Explore all derivations (STRATEGY=exhaustive).' \
	  '  sample          Sample derivations (STRATEGY=sample).' \
	  '  beam            Use beam search (STRATEGY=beam).' \
	  '  random          Select a random sentence (--random).' \
	  '  first           Print the first sentence (--first).' \
	  '  sample-random   Sample strategy with random selection.' \
	  '  beam-random     Beam strategy with random selection.' \
	  '  reduce-all      Enable --reduce-all.' \
	  '' \
	  'DEBUGGING AND EXPORTS' \
	  '  debug           Save trace output to .elvex-build/debug.html.' \
	  '                  Defaults to TRACE_MODE=all for this target.' \
	  '  trace           Print rule traces to the terminal (rules marked @trace).' \
	  '  output          Save sentences to .elvex-build/sentences.txt.' \
	  '  xml             Write .elvex-build/sentences.xml using --xml.' \
	  '' \
	  'TRACE_MODE (comma-separated modes)' \
	  '  none            No trace (default for run).' \
	  '  rules           --trace: grammar rules marked @trace.' \
	  '  all             --trace-all: full trace.' \
	  '  init            --trace-init: initialization.' \
	  '  stage           --trace-stage: stages.' \
	  '  close           --trace-close: closure.' \
	  '  shift           --trace-shift: shifts.' \
	  '  reduce          --trace-reduce: reductions.' \
	  '  action          --trace-action: actions.' \
	  '  Example: make DATA=english-sentences debug TRACE_MODE=shift,reduce,action' \
	  '' \
	  'GENERATION OPTIONS' \
	  '  STRATEGY=exhaustive|sample|beam   Derivation strategy.' \
	  '  MODE=all|first|random            Output selection.' \
	  '  SEED=42                          Reproducible random seed.' \
	  '  REDUCE_ALL=1                     Enable --reduce-all.' \
	  '  VERBOSE=1                        Enable --verbose.' \
	  '  MAX_TIME=30                      Maximum duration (seconds).' \
	  '  MAX_LENGTH=25                    Maximum sentence length.' \
	  '  MAX_USAGES=100                   Maximum rule uses.' \
	  '  MAX_ITEMS=1000                   Maximum items per set.' \
	  '  MAX_ATTEMPTS=100                 Maximum random selection attempts.' \
	  '  MAX_RULE_CHOICES=100             Choices in sample strategy.' \
	  '  BEAM_WIDTH=50                    Items retained in beam search.' \
	  '  EXTRA_OPTS=...                   Other elvex options.' \
	  '  ELVEX=... / ELVEXLEXICON=...    Paths to executables.' \
	  '' \
	  'MAINTENANCE' \
	  '  lexicon         Build only if both .morpho and .pattern exist.' \
	  '  info            Show detected example resource files.' \
	  '  check           Check that required executables exist.' \
	  '  clean           Remove only the local .elvex-build directory.' \
	  '  rebuild         Clean and rebuild the compacted lexicon.' \
	  '  help            Show this help, even without a valid DATA directory.' \
	  '' \
	  'EXAMPLES' \
	  '  make DATA=english-sentences first MAX_TIME=30' \
	  '  make DATA=english-sentences random SEED=42 MAX_TIME=30' \
	  '  make DATA=english-sentences sample MAX_RULE_CHOICES=100' \
	  '  make DATA=english-sentences beam BEAM_WIDTH=50' \
	  '  make DATA=english-sentences trace' \
	  '  make DATA=english-sentences debug TRACE_MODE=reduce MAX_TIME=30' \
	  '  make DATA=english-sentences debug TRACE_MODE=shift,reduce,action'
