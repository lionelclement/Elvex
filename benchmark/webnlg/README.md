# WebNLG → Elvex starter project

This project downloads WebNLG, extracts RDF triples, builds starter Elvex resources, selects entries by triple count, and creates one Elvex input file per test.

The project is intentionally conservative. It is a first grammar and lexicon bootstrap, not a complete WebNLG realizer.

## macOS / Homebrew

```bash
brew install python git
unzip webnlg_elvex_format_v5.zip
cd webnlg
./run setup
./run all
```

`./run` never calls `python` directly. It detects `python3`, creates a local `.venv/`, and runs scripts with `.venv/bin/python`.

The Elvex commands `elvex` and `elvexlexicon` are expected to be available in `PATH`.

## Elvex file layout

Elvex is called with six resource inputs:

```text
user/main.macros
user/main.input
user/main.rules
user/main.lexicon
build/lexicon/main.tbl
build/lexicon/main.fsa
```

Important: `elvex` must receive exactly one generation input per command. Therefore `user/main.input` is only the current sample input. The complete WebNLG test sets are split into individual `.input` files.

For atomic triples:

```text
build/inputs/simple_triples/
build/inputs/simple_triples.index.tsv
```

For WebNLG entries with 2 triples:

```text
build/inputs/2_triples/
build/inputs/2_triples.index.tsv
```

The same pattern is used for 3, 4, 6, ... triples, according to the files available in `build/sequences/`.

`user/main.macros` contains feature macros used by rules, local lexicon entries, pattern entries and morphology entries. It is not empty, so `./run compact` and `./run elvex-sample` pass it through `--macros-file`.

`user/main.input` contains one generation input only. `./run inputs <n>` copies the first generated test file into this file as a convenient sample unless `--no-copy-first-to-user` is passed.

`user/main.rules` is only an include file:

```elvex
#include user/rules/simple_triples.rules
```

Edit the actual grammar in `user/rules/simple_triples.rules`.

`user/main.lexicon` is also only an include file:

```elvex
#include user/lexicon/base.lexicon
#include user/lexicon/generated_determiners.lexicon
```

Edit closed-class or functional entries in `user/lexicon/base.lexicon`. Generated determiners are written to `user/lexicon/generated_determiners.lexicon`.

Open-class lexical material is written to:

```text
user/main.pattern
user/main.morpho
```

All lemmas in `user/main.pattern` and `user/main.morpho` are uppercased and prefixed with `_`, for example `order` becomes `_ORDER`, to avoid collisions with Elvex keywords.

`./run compact` runs:

```bash
elvexlexicon \
  --compacted-lexicon-file build/lexicon/main \
  --macros-file user/main.macros \
  --pattern-file user/main.pattern \
  --morpho-file user/main.morpho \
  build
```

This creates:

```text
build/lexicon/main.tbl
build/lexicon/main.fsa
```

## Commands

```bash
./run download       # download WebNLG sources into data/raw/
./run extract        # write data/processed/triples.jsonl
./run lexicon        # write user/main.pattern, user/main.morpho and generated local lexicon files
./run compact        # build build/lexicon/main.tbl and .fsa with elvexlexicon
./run select         # write build/sequences/<n>.jsonl
./run inputs         # same as ./run inputs 1
./run inputs 2       # write one .input file per WebNLG entry with 2 triples
./run validate       # check the expected files
./run all            # run download, extract, lexicon, compact, select, inputs 1, validate
./run elvex-sample   # call elvex on user/main.input
./run elvex-one PATH # call elvex on a single .input file
./run elvex-tests 2 20  # call elvex on 20 generated tests with 2 triples
./run compare-one 1 1   # show Elvex output beside WebNLG references for one atomic test
./run compare-one 2 1   # same for the first 2-triple test
./run compare 1 20      # write a comparison report for 20 atomic tests
./run compare 2 20      # write a comparison report for 20 two-triple tests
```

## Inputs by number of triples

The selector step writes entries by triple count:

```text
build/sequences/1.jsonl   # atomic view: one row per distinct triple
build/sequences/2.jsonl   # original WebNLG entries containing 2 triples
build/sequences/3.jsonl
...
```

`./run inputs <n>` consumes `build/sequences/<n>.jsonl` and writes one `.input` file per row.

Examples:

```bash
./run inputs 1
./run inputs 2
./run inputs 3 --limit 100
```

Output directories:

```text
build/inputs/simple_triples/      # n = 1
build/inputs/2_triples/           # n = 2
build/inputs/3_triples/           # n = 3
```

Each `.input` file contains exactly one Elvex input. The `.index.tsv` file beside each input directory stores metadata, source triples, and WebNLG references.

A diagnostic concatenation is also written, for example:

```text
build/inputs/2_triples.input
```

This concatenated file is for inspection only. Do not pass it to `elvex` directly.

## Comparing Elvex output with WebNLG references

Generate inputs first:

```bash
./run inputs 1
./run inputs 2
```

Compare one test:

```bash
./run compare-one 1 1
./run compare-one 2 1
```

The output contains:

```text
INPUT FILE
ENTRY
TRIPLE(S)
ELVEX OUTPUT
WEBNLG REFERENCE(S)
ELVEX STDERR, when present
```

Batch comparison:

```bash
./run compare 1 20
./run compare 2 20
```

Reports are written to:

```text
build/reports/comparison_1_triples.tsv
build/reports/comparison_2_triples.tsv
```

Raw Elvex outputs and logs are written to:

```text
build/outputs/compare/
build/logs/elvex/
```

## Generated input examples

A single-triple input has this form:

```elvex
// Alfa Romeo 164 | assembly | Milan
S [HEAD:webnlg_simple, pattern:svo, s:[HEAD:Alfa_Romeo_164], p:[HEAD:assembly], o:[HEAD:Milan]]
```

A two-triple input has this form:

```elvex
// Aarhus | leaderName | Jacob Bundsgaard
// Aarhus | country | Denmark
S [HEAD:webnlg_sequence, size:2, triples:<[pattern:cop_nom, s:[HEAD:Aarhus], p:[HEAD:leader_Name], o:[HEAD:Jacob_Bundsgaard]], [pattern:svo, s:[HEAD:Aarhus], p:[HEAD:country], o:[HEAD:Denmark]]>]
```

The initial grammar focuses on `webnlg_simple`. Multi-triple inputs are generated so they can be tested and progressively supported by new grammar rules.

## Generated pattern format

`user/main.pattern` uses tab-separated fields:

```text
LEXEME<TAB>POS<TAB>LEMMA<TAB>features_1
```

Example:

```text
CHAUVE_SOURIS	noun	_CHAUVE_SOURIS	[@f]
```

## Generated morphology format

`user/main.morpho` uses tab-separated fields:

```text
FORM<TAB>POS<TAB>LEMMA<TAB>features_2
```

Example:

```text
chauve souris	noun	_CHAUVE_SOURIS	[@s]
chauves souris	noun	_CHAUVE_SOURIS	[@p]
```

The compacted lexicon combines entries that share `POS` and `LEMMA`:

```text
POS#LEXEME => FORM features_1 unified with features_2
```

## First grammar scope

The first grammar handles single triples with three patterns:

```text
svo       subject verb object
cop_adj   subject copula adjective
cop_nom   subject copula noun
```

Generated atomic inputs have this form:

```elvex
S [HEAD:webnlg_simple, pattern:svo, s:[HEAD:...], p:[HEAD:...], o:[HEAD:...]]
```

Predicate pattern guesses are written to:

```text
user/lexicon/predicate_suggestions.tsv
```

Correct them by editing:

```text
user/lexicon/predicate_overrides.tsv
```

Then rerun:

```bash
./run lexicon
./run compact
./run inputs 1
./run inputs 2
```

## Direct Elvex command

After `./run all`, the equivalent direct command for the current sample is:

```bash
elvex \
  --macros-file user/main.macros \
  --rules-file user/main.rules \
  --lexicon-file user/main.lexicon \
  --compacted-lexicon-file build/lexicon/main \
  --input-file user/main.input \
  --max-length 40 --first
```

To run a generated WebNLG test directly, replace `user/main.input` with one file from `build/inputs/simple_triples/` or `build/inputs/2_triples/`.

### Nominal relation overrides

Predicate-specific lexicalisations can be edited in `user/lexicon/predicate_overrides.tsv`.
For example, `leaderName` is configured as a nominal relation:

```tsv
predicate	pattern	lexeme	form	prep
leaderName	rel_nom	leader_Name	leader	of
```

This generates compacted-lexicon entries where the predicate is selected through
`HEAD:leader_Name`, but the produced noun is `leader`. The grammar then has two
realisation patterns:

```text
The leader of X is Y.
Y is the leader of X.
```

The `prep` column is used as the `pcas` feature for the relational noun phrase.

## Predicate-specific frames

The project now distinguishes direct verbal predicates from predicates that
need a paraphrastic frame.

Direct predicates can remain in the generic fallback grammar. For example, a
predicate that behaves like `eat(X,Y) -> X eats Y` can use the generic SVO
path.

Predicates that do not correspond to an immediate subject-verb-object lexical
entry should get an explicit frame in:

```text
user/rules/frames.rules
```

The lexical material required by the frame should be added in pure
`elvexlexicon` format:

```text
user/override.pattern
user/override.morpho
```

These files are appended to the generated files during `./run lexicon`:

```text
user/override.pattern + generated entries -> user/main.pattern
user/override.morpho  + generated entries -> user/main.morpho
```

Example for `leaderName(X,Y)`:

```text
user/override.pattern:
_LEADER<TAB>noun<TAB>_LEADER<TAB>[HEAD:_LEADER, frame_for:leader_Name]

user/override.morpho:
leader<TAB>noun<TAB>_LEADER<TAB>[@s]
```

The frame itself is written in Elvex rules:

```elvex
SENT -> NP cop NP {
  [HEAD:leader_Name, i:$I, ii:$II] <<< ↑;
  ↓1 = [HEAD:_LEADER, @def, @s, ofObj:$I];
  ↓2 = [@present, @indicative, @_3s];
  ↓3 = $II;
  ⇑ = ⇓3;
}
```

When `./run inputs 1` sees a predicate that has a frame in
`user/rules/frames.rules`, it generates a direct frame input such as:

```elvex
S [HEAD:leader_Name, i:[HEAD:Aarhus], ii:[HEAD:Jacob_Bundsgaard]]
```

For all other predicates, it keeps the older generic fallback input:

```elvex
S [HEAD:webnlg_simple, pattern:svo, s:[HEAD:X], p:[HEAD:P], o:[HEAD:Y]]
```

## Elvex item limit during comparisons

The wrapper now passes `--max-items` to Elvex for sample, single-input and batch comparison commands. The default is:

```bash
ELVEX_MAX_ITEMS=200000
```

Override it when needed:

```bash
ELVEX_MAX_ITEMS=500000 ./run compare-one 1 1
```

The `leader_Name` frame also avoids a recursive `N -> N PP` construction for `the leader of X`; it uses a direct NP rule for `ofObj` to reduce the number of generated items.

### Debugging a hanging Elvex comparison

`./run compare-one <n> <id>` prints the input file, WebNLG triple(s), and WebNLG reference(s) before launching `elvex`. This makes it possible to see which example is being tested even if the grammar search is too broad.

Elvex is run with bounded search parameters. You can override them:

```bash
ELVEX_MAX_TIME=3 ELVEX_PROCESS_TIMEOUT=5 ./run compare-one 1 1
ELVEX_MAX_ITEMS=50000 ./run compare-one 1 1
```

`ELVEX_MAX_TIME` is passed to `elvex --max-time`. `ELVEX_PROCESS_TIMEOUT` is a Python-side safety timeout that kills the process if it does not return.

## Predicate-specific direct frames

For predicates that are not immediate verbal relations, prefer direct Elvex frames in `user/rules/frames.rules`.

For example, `leaderName(X,Y)` is handled as a dedicated frame rather than as a generic copular nominal relation:

```elvex
SENT -> det noun prep noun cop noun {
  [HEAD:leader_Name, i:$I, ii:$II] <<< ↑;
  ↓1 = [@def];
  ↓2 = [HEAD:_LEADER, @s];
  ↓3 = [pcas:of];
  ↓4 = $I;
  ↓5 = [@present, @indicative, @_3s];
  ↓6 = $II;
  ⇑ = ⇓6;
}
```

This direct form avoids unnecessary exploration through generic NP recursion and keeps the WebNLG-scoring variant first: `The leader of X is Y`.

### v11 note: definite determiner in `leaderName` frames

The `leaderName` frame now uses the normal `det` category. The base determiner lexicon explicitly marks determiners with `def:true` or `def:false`, so unification excludes indefinite determiners when a frame requires `[def:true]`. This prevents outputs such as `an leader` while avoiding ad-hoc determiner categories:

```text
The leader of Aarhus is Jacob Bundsgaard.
Jacob Bundsgaard is the leader of Aarhus.
```

## Comparing all Elvex outputs with WebNLG references

`compare-one` and `compare` now run Elvex without `--first` by default. This keeps every generated realization and compares all of them with the WebNLG references.

```bash
./run compare-one 1 1
./run compare 1 100
```

The comparison reports both a strict first-output score and a best-of-N diagnostic score:

- `first_exact_match`: whether the first Elvex output exactly matches a WebNLG reference.
- `best_exact_match`: whether any Elvex output exactly matches a WebNLG reference.
- `best_normalized_match`: whether any Elvex output matches a reference after light normalization of case, whitespace and spaces before punctuation. This is only a development diagnostic, not an official WebNLG metric.

The batch report is written to:

```text
build/reports/comparison_<n>_triples.tsv
```

For each input, all generated outputs are also stored in:

```text
build/outputs/compare/<input-stem>.out
build/outputs/compare/<input-stem>.all.tsv
```

To force the old first-output behavior for diagnosis:

```bash
.venv/bin/python scripts/compare_elvex.py one 1 1 --first-only
```

### Final surface post-processing

Elvex lexical resources now keep function words lowercase. Proper nouns keep their own capitalization. Final sentence capitalization and punctuation spacing are applied after generation by:

```bash
./run postprocess < raw-elvex-output.txt
```

The comparison commands apply this post-processing automatically before matching WebNLG references. Raw Elvex outputs are still saved as `build/outputs/compare/*.raw.out`; finalized outputs are saved as `build/outputs/compare/*.out`.

For definite descriptions, demonstratives are not selected by default. A frame asking for a plain definite description should pass features such as `@def, dem:false, poss:false, part:false`; this excludes `this/that/these/those` while keeping `the`.


### Predicate frame: runwayLength

`runwayLength(X,Y)` is handled by an explicit frame in `user/rules/frames.rules`:

```text
The runway length at X is Y meters.
```

Numeric values are normalized when inputs are generated. Both typed RDF literals and raw numeric objects are converted to Elvex value features:

```elvex
ii:[value:"2777.0", datatype:xsd_double]   // from "2777.0"^^xsd:double
ii:[value:"2777.0", datatype:number]       // from 2777.0
```

Numbers are not added to the compacted lexicon as `proper_noun` entries. The local lexicon realizes them with variable lexical entries:

```elvex
"$NUMBER"        NUMBER         [value:$NUMBER];
"$NUMBER meters" NUMBER_METERS  [value:$NUMBER];
```


### Numeric values and units

Numeric WebNLG objects are no longer compacted as `proper_noun` entries. The input generator recognizes RDF typed numbers, raw numbers, and compact number-unit strings such as `3.8 m` or `1.2 (litres)`. These are passed to Elvex as dynamic features, for example `[value:"3.8", unit:"m", datatype:number_unit]`, and realized by local lexicon entries such as `"$NUMBER" NUMBER [value:$NUMBER];` and `"$NUMBER $UNIT" NUMBER_UNIT [value:$NUMBER, unit:$UNIT];`.


## Numeric lexical entries are guarded

Numeric local entries such as `"$NUMBER" NUMBER [value:$NUMBER];` and `"$NUMBER $UNIT" NUMBER_UNIT [value:$NUMBER, unit:$UNIT];` are only available to `NP` when the inherited feature structure already contains `value` (and `unit` for `NUMBER_UNIT`). This prevents unconstrained variables from producing `?` outputs in ordinary named-entity positions.

### v21 note

Numeric NP rules now use true Elvex guards (`[value:$Value];` and `[value:$Value, unit:$Unit];`) rather than subsumption statements, so `NUMBER` and `NUMBER_UNIT` cannot realize non-numeric noun phrases.

### v22 predicate frames

This version adds explicit Elvex frames for the first empty-output predicates seen in the one-triple comparison log:

- `location(X,Y)` and `country(X,Y)` -> `X is located in Y.`
- `runwayName(X,Y)` and `runwayDesignation(X,Y)` -> `The runway name of X is Y.`
- `faa(X,Y)` and `locationIdentifier(X,Y)` -> `The location identifier of X is Y.`
- `1st_runway_LengthFeet(X,Y)` and `r1LengthF(X,Y)` -> `The first runway length in feet of X is Y.`
- `city(X,Y)` -> `X serves Y.`

The additions are in `user/rules/frames.rules`, with the corresponding lexical resources in `user/override.pattern`, `user/override.morpho`, and `user/lexicon/base.lexicon`. No new `./run` command is introduced.
