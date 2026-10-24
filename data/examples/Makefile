# ============================================================
# Elvex - Makefile generique (GNU Make >= 4.3)
# Utilisation : make DATA=english-sentences random SEED=42 MAX_TIME=30
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

# Les fichiers ne sont examines que pour les cibles qui les utilisent.
# Ainsi 'make help', 'make check' et 'make clean' restent independants de DATA.
define require_one
$(if $(filter 1,$(words $(2))),$(firstword $(2)),$(error Attendu exactement un fichier $(1) dans $(DIR) ; trouves : $(2)))
endef

# Zero ou un fichier .macros : aucun argument si absent.
define optional_one
$(if $(filter 0 1,$(words $(2))),$(firstword $(2)),$(error Attendu au plus un fichier $(1) dans $(DIR) ; trouves : $(2)))
endef

MACROS  = $(call optional_one,.macros,$(wildcard $(DIR)/*.macros))
RULES   = $(call require_one,.rules,$(wildcard $(DIR)/*.rules))
LEXICON = $(call require_one,.lexicon,$(wildcard $(DIR)/*.lexicon))
MORPHO  = $(call optional_one,.morpho,$(wildcard $(DIR)/*.morpho))
PATTERN = $(call optional_one,.pattern,$(wildcard $(DIR)/*.pattern))
# Existing suites use .input; newer suites use .stdin.  Accept either, never both.
INPUT   = $(call require_one,.stdin ou .input,$(wildcard $(DIR)/*.stdin $(DIR)/*.input))

# Le lexique compacte n'est construit que si les deux sources existent.
# Une source seule est une configuration incomplete.
HAS_MORPHO = $(if $(MORPHO),1,0)
HAS_PATTERN = $(if $(PATTERN),1,0)
BUILD_LEXICON = $(if $(and $(MORPHO),$(PATTERN)),1,)
validate_lexicon_pair = $(if $(filter-out $(HAS_MORPHO),$(HAS_PATTERN)),$(error Fournir .morpho et .pattern ensemble dans $(DIR)),)

# Pas d'erreur de recherche lors du chargement du Makefile.
SOURCE_DEPS := $(wildcard $(DIR)/*.macros $(DIR)/*.morpho $(DIR)/*.pattern)

BUILD_DIR := $(DIR)/.elvex-build
CLF       := $(BUILD_DIR)/lexicon
FSA       := $(CLF).fsa
TBL       := $(CLF).tbl
OUTPUT    := $(BUILD_DIR)/sentences.txt
DEBUG_FILE := $(BUILD_DIR)/debug.html
XML_FILE  := $(BUILD_DIR)/sentences.xml

# Strategie : exhaustive | sample | beam
STRATEGY ?= exhaustive
# Selection : all | first | random
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
# TRACE_MODE accepte une liste de modes separes par des virgules.
# Par defaut, aucune trace pour run ; toutes les traces pour debug.
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

validate_options = $(if $(filter $(STRATEGY),$(VALID_STRATEGIES)),,$(error STRATEGY invalide : $(STRATEGY)))  $(if $(filter $(MODE),$(VALID_MODES)),,$(error MODE invalide : $(MODE)))  $(if $(UNKNOWN_TRACES),$(error TRACE_MODE invalide : $(UNKNOWN_TRACES)),)  $(if $(filter none,$(TRACE_MODES)),$(if $(filter-out none,$(TRACE_MODES)),$(error TRACE_MODE=none ne se combine pas avec d'autres valeurs),),)  $(if $(filter all,$(TRACE_MODES)),$(if $(filter-out all,$(TRACE_MODES)),$(error TRACE_MODE=all ne se combine pas avec d'autres valeurs),),)

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

# Une compilation cree les deux fichiers (.fsa et .tbl).
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
	@echo "Pas de .morpho/.pattern : elvexlexicon ignore."
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
	@echo "Phrases : $(OUTPUT)"

# Trace des seules regles annotees @trace, dans le terminal.
# Exemple : make DATA=english-sentences trace
trace: TRACE_MODE = rules
trace: run

debug: TRACE_MODE = all
debug: lexicon | $(BUILD_DIR)
	@: $(validate_options) $(validate_sources)
	$(ELVEX) $(ELVEX_FILES) $(RUN_OPTS) > "$(DEBUG_FILE)"
	@echo "Trace : $(DEBUG_FILE)"

xml: lexicon | $(BUILD_DIR)
	@: $(validate_options) $(validate_sources)
	$(ELVEX) $(ELVEX_FILES) $(RUN_OPTS) --xml "$(XML_FILE)"
	@echo "XML : $(XML_FILE)"

info:
	@: $(validate_options) $(validate_sources)
	@echo "Dossier : $(DIR)"
	@echo "Macros : $(MACROS)"
	@echo "Regles : $(RULES)"
	@echo "Lexique : $(LEXICON)"
	@echo "Morphologie : $(MORPHO)"
	@echo "Patterns : $(PATTERN)"
	@echo "Entree : $(INPUT)"
	@echo "Lexique compile : $(if $(BUILD_LEXICON),$(CLF),(non utilise))"
	@echo "Strategie : $(STRATEGY) ; selection : $(MODE) ; traces : $(TRACE_MODE)"

check:
	@command -v "$(ELVEX)" >/dev/null || { echo "Introuvable : $(ELVEX)"; exit 1; }
	$(if $(BUILD_LEXICON),	@command -v "$(ELVEXLEXICON)" >/dev/null || { echo "Introuvable : $(ELVEXLEXICON)"; exit 1; },	@echo "elvexlexicon non requis pour $(DIR).")
	@echo "Executables Elvex detectes."

clean:
	rm -rf "$(BUILD_DIR)"

rebuild:
	$(MAKE) -f "$(firstword $(MAKEFILE_LIST))" DATA="$(DATA)" clean
	$(MAKE) -f "$(firstword $(MAKEFILE_LIST))" DATA="$(DATA)" lexicon

help:
	@printf '%s\n' \
	  'ELVEX - MAKEFILE GENERIQUE' \
	  '' \
	  'UTILISATION' \
	  '  make DATA=<dossier> [cible] [VARIABLE=valeur ...]' \
	  '  Exemple : make DATA=english-sentences random SEED=42 MAX_TIME=30' \
	  '  DATA=english-sentences par defaut. .input ou .stdin ; .macros facultatif ; .morpho et .pattern facultatifs ensemble.' \
	  '' \
	  'GENERATION (affichage dans le terminal)' \
	  '  run             Generation standard (exhaustive, toutes les phrases).' \
	  '  exhaustive      Explore toutes les derivations (STRATEGY=exhaustive).' \
	  '  sample          Echantillonnage des derivations (STRATEGY=sample).' \
	  '  beam            Recherche en faisceau (STRATEGY=beam).' \
	  '  random          Selectionne une phrase au hasard (--random).' \
	  '  first           Affiche la premiere phrase (--first).' \
	  '  sample-random   Strategie sample + selection aleatoire.' \
	  '  beam-random     Strategie beam + selection aleatoire.' \
	  '  reduce-all      Active --reduce-all.' \
	  '' \
	  'DEBUG ET EXPORTS' \
	  '  debug           Enregistre les traces dans .elvex-build/debug.html.' \
	  '                  TRACE_MODE=all par defaut sur cette cible.' \
	  '  trace           Affiche --trace dans le terminal (regles @trace).' \
	  '  output          Enregistre les phrases dans .elvex-build/sentences.txt.' \
	  '  xml             Produit .elvex-build/sentences.xml avec --xml.' \
	  '' \
	  'TRACE_MODE (plusieurs modes possibles, separes par des virgules)' \
	  '  none            Aucune trace (par defaut pour run).' \
	  '  rules           --trace : regles marquees @trace.' \
	  '  all             --trace-all : trace complete.' \
	  '  init            --trace-init : initialisation.' \
	  '  stage           --trace-stage : etapes.' \
	  '  close           --trace-close : fermeture.' \
	  '  shift           --trace-shift : decalages.' \
	  '  reduce          --trace-reduce : reductions.' \
	  '  action          --trace-action : actions.' \
	  '  Exemple : make DATA=english-sentences debug TRACE_MODE=shift,reduce,action' \
	  '' \
	  'OPTIONS DE GENERATION' \
	  '  STRATEGY=exhaustive|sample|beam   Methode de derivation.' \
	  '  MODE=all|first|random            Selection de la sortie.' \
	  '  SEED=42                          Graine aleatoire reproductible.' \
	  '  REDUCE_ALL=1                     Active --reduce-all.' \
	  '  VERBOSE=1                        Active --verbose.' \
	  '  MAX_TIME=30                      Duree maximale (secondes).' \
	  '  MAX_LENGTH=25                    Longueur maximale des phrases.' \
	  '  MAX_USAGES=100                   Usages maximaux de regles.' \
	  '  MAX_ITEMS=1000                   Elements max. par ensemble.' \
	  '  MAX_ATTEMPTS=100                 Tentatives de choix aleatoire.' \
	  '  MAX_RULE_CHOICES=100             Choix ouverts en mode sample.' \
	  '  BEAM_WIDTH=50                    Elements conserves en beam.' \
	  '  EXTRA_OPTS=...                   Autres options passees a elvex.' \
	  '  ELVEX=... / ELVEXLEXICON=...    Chemin des executables.' \
	  '' \
	  'MAINTENANCE' \
	  '  lexicon         Compile si .morpho ET .pattern existent ; sinon ignore.' \
	  '  info            Affiche les fichiers automatiquement trouves.' \
	  '  check           Verifie la presence des executables.' \
	  '  clean           Supprime uniquement .elvex-build.' \
	  '  rebuild         Nettoie puis recompile le lexique.' \
	  '  help            Affiche cette aide, meme sans dossier DATA.' \
	  '' \
	  'EXEMPLES' \
	  '  make DATA=english-sentences first MAX_TIME=30' \
	  '  make DATA=english-sentences random SEED=42 MAX_TIME=30' \
	  '  make DATA=english-sentences sample MAX_RULE_CHOICES=100' \
	  '  make DATA=english-sentences beam BEAM_WIDTH=50' \
	  '  make DATA=english-sentences trace' \
	  '  make DATA=english-sentences debug TRACE_MODE=reduce MAX_TIME=30' \
	  '  make DATA=english-sentences debug TRACE_MODE=shift,reduce,action'
