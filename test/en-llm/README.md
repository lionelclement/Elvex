# Elvex English Grammar

English sentence-generation grammar for **Elvex**, organized as a set of rule modules with generated lexical resources, regression corpora, and validation tools.

The repository is intended for two main tasks:

1. generating English sentences from Elvex feature structures;
2. extending the grammar and lexicon while keeping the existing behavior covered by regression tests.

## 1. Requirements

You need:

- `elvex`;
- `elvexlexicon`;
- Python 3;
- all files in this repository in the same working directory.

The commands below assume that `elvex` and `elvexlexicon` are available in `PATH`.

The included `Makefile` provides the common maintenance commands:

```bash
make check       # static and generator consistency checks
make generate    # regenerate vocabulary/function resources and generated tests
make lexicon     # build en.fsa/en.tbl
make test        # run all regression corpora
make audit       # regenerate the lexical-function QA reports
make clean       # remove local/generated artifacts not meant for version control
```

Override tool locations when needed, for example:

```bash
make test ELVEX=../../bin/elvex ELVEXLEXICON=../../bin/elvexlexicon
```

## 2. Quick start

### Static validation

```bash
python3 validate_static.py
```

### Build the compacted lexicon

```bash
elvexlexicon \
  --clf en \
  --macros-file en.macros \
  --pattern-file en.pattern \
  --morpho-file en.morpho \
  build
```

### Run the main regression corpus

```bash
elvex \
  --macros-file en.macros \
  --compacted-lexicon-file en \
  --rules-file en.rules \
  --lexicon-file en.lexicon \
  < en.stdin
```

When running several `Axiom` entries, use standard input as above rather than `--input-file`.

## 3. Repository layout

### Rule files

| File | Purpose |
|---|---|
| `en.rules` | Master rule file; includes all grammar modules |
| `en-sentence.rules` | Sentence structure, punctuation, declaratives and interrogatives |
| `en-normalize.rules` | Feature normalization and `vtense` compatibility |
| `en-noun.rules` | Noun phrases, proper nouns and adjectives |
| `en-verb.rules` | Ordinary verbal valencies |
| `en-complex.rules` | Support verbs, lexical functions and idioms |
| `en-copula.rules` | Copular `BE` constructions |
| `en-tense.rules` | Tense, aspect, negation and interrogation |
| `en-modal.rules` | English modal verbs |

### Lexical resources

| File | Purpose |
|---|---|
| `en.pattern` | Lexical entries and feature structures |
| `en.morpho` | Morphological forms |
| `en.lexicon` | Additional Elvex lexicon |
| `en.macros` | Elvex macros |
| `en-vocab-large.tsv` | Source data for the extended vocabulary |
| `en-lexical-functions.tsv` | Explicit lexical-function definitions |
| `en-lexical-function-families.tsv` | Large lexical-function families |

### Generators and QA tools

| File | Purpose |
|---|---|
| `generate_large_vocab.py` | Generates the extended vocabulary |
| `generate_lexical_functions.py` | Generates lexical-function entries |
| `generate_support_verb_tense_tests.py` | Generates morphology tests for support verbs |
| `validate_static.py` | Performs repository-level structural checks |
| `audit_lexical_functions.py` | Produces a lexicographic QA report |

### Regression corpora

Files ending in `*.stdin` contain Elvex `Axiom` structures. Matching `*.expected.txt` files contain the expected output.

Important corpora include:

- `en.stdin`: general regression corpus;
- `en-large-vocab.stdin`: extended vocabulary;
- `en-complex.stdin`: idioms and complex lexemes;
- `en-support.stdin`: `Oper1` / `Oper2` support-verb constructions;
- `en-lexical-functions.stdin`: core lexical functions;
- `en-lexical-functions-massive.stdin`: large lexical-function coverage;
- `en-support-verbs-tenses.stdin`: systematic support-verb conjugation tests;
- `en-incepoper2.stdin`: `IncepOper2`;
- `en-causoper1.stdin`: `CausOper1`.

## 4. Sentence semantic interface

A basic input looks like this:

```text
Axiom [
  HEAD:TO_READ,
  i:[HEAD:JOHN],
  ii:[HEAD:BOOK, number:sg, def:true],
  iii:NIL,
  tense:present,
  aspect:simple,
  modality:none,
  polarity:positive,
  illocution:declarative
]
```

Output:

```text
John reads the book.
```

### Main features

`HEAD` identifies the lexical predicate.

Semantic actants are represented as:

- `i`: first actant;
- `ii`: second actant;
- `iii`: third actant.

When an actant is absent, explicitly using `ii:NIL` or `iii:NIL` is recommended.

### Tense and aspect

Supported `tense` values:

```text
present | past | future
```

Supported `aspect` values:

```text
simple | continuous | perfect | perfect_continuous
```

Examples:

```text
tense:present, aspect:simple
→ John reads the book.

tense:past, aspect:continuous
→ John was reading the book.

tense:present, aspect:perfect
→ John has read the book.

tense:future, aspect:perfect_continuous
→ John will have been reading the book.
```

The grammar also accepts compact `vtense` values, including:

```text
present
present_continuous
present_perfect
present_perfect_continuous
preterite
past_continuous
past_perfect
past_perfect_continuous
future
future_continuous
future_perfect
future_perfect_continuous
```

### Polarity and illocution

```text
polarity:positive | negative
illocution:declarative | interrogative
```

Examples:

```text
John reads the book.
John does not read the book.
does John read the book?
does John not read the book?
```

### Modals

Currently supported modal values:

```text
can could may might must shall should will would
```

Modals combine with aspect:

```text
can read
can be reading
can have read
can have been reading
```

## 5. Verb valencies

The grammar includes general patterns for:

- intransitive verbs: `John sleeps.`;
- transitive verbs: `John reads the book.`;
- ditransitive verbs: `John gives Mary the book.`;
- prepositional complements: `John listens to the music.`;
- transitive + prepositional complement: `John puts the book on the table.`;
- copula + adjective: `John is happy.`.

For prepositional valencies, the lexical entry normally specifies the preposition through `pcase`.

## 6. Lexical functions

The grammar currently uses:

```text
Oper1
Oper2
IncepOper2
CausOper1
Magn
AntiMagn
```

They are represented in Elvex feature structures as:

```text
lexical_function:oper1
lexical_function:oper2
lexical_function:incepoper2
lexical_function:causoper1
modifier_function:magn
modifier_function:antimagn
```

### Oper1

```text
Axiom [HEAD:DECISION, i:[HEAD:JOHN], ii:NIL, iii:NIL,
       lexical_function:oper1,
       tense:present, aspect:simple,
       modality:none, polarity:positive, illocution:declarative]
```

Output:

```text
John makes a decision.
```

### Oper1 / Oper2 actant mapping

For the same semantic predicate:

```text
ATTENTION(i=John, ii=Mary) + Oper1
→ John pays attention to Mary.

ATTENTION(i=John, ii=Mary) + Oper2
→ Mary receives attention from John.
```

`Oper2` therefore promotes semantic actant II to surface subject position.

### IncepOper2

`IncepOper2` is used for support verbs that express acquisition or the beginning of a state:

```text
KNOWLEDGE + IncepOper2
→ Mary gains knowledge.
```

Current realization families include verbs such as:

```text
GAIN
GET
OBTAIN
SECURE
WIN
EARN
```

When families overlap, the lexical-function generator applies deterministic priorities.

### CausOper1

Example:

```text
AWARENESS(i=John, ii=Problem) + CausOper1
→ John raises awareness of the problem.
```

### Magn and AntiMagn

`Magn` and `AntiMagn` are independent from the main support-verb function.

Examples:

```text
ATTENTION + Oper1 + Magn
→ John pays close attention to Mary.

SUPPORT + Oper2 + Magn
→ Mary receives strong support from John.

INTEREST + Oper1 + AntiMagn
→ John takes a slight interest in Mary.
```

They can also apply directly to adjectives:

```text
COLD + Magn
→ very cold

DIFFICULT + AntiMagn
→ somewhat difficult
```

## 7. Idioms and complex lexemes

Complex lexemes are described in `en-complex.rules` and `en.pattern`.

Examples:

```text
TO_FEEL_BLUE
→ John feels blue.

TO_KEEP_AN_EYE_ON(i=John, ii=Mary)
→ John keeps an eye on Mary.
```

A complex lexeme may therefore combine fixed lexical material with one or more free semantic actants.

## 8. Extending the general vocabulary

Large-vocabulary source data lives in:

```text
en-vocab-large.tsv
```

Do not edit generated blocks directly in `en.pattern`, `en.morpho` or `en.lexicon`.

Generated vocabulary blocks are delimited by markers such as:

```text
BEGIN GENERATED LARGE VOCABULARY
END GENERATED LARGE VOCABULARY
```

After editing `en-vocab-large.tsv`, run:

```bash
python3 generate_large_vocab.py --check
python3 generate_large_vocab.py
```

Then rebuild the compacted lexicon:

```bash
elvexlexicon \
  --clf en \
  --macros-file en.macros \
  --pattern-file en.pattern \
  --morpho-file en.morpho \
  build
```

### `en-vocab-large.tsv` entry types

Currently supported entry types include:

```text
noun
adj
verb
proper
prep
```

Example verb row:

```text
verb	TO_APPEAR	appear	intransitive		appears	appeared	appeared	appearing
```

Provide irregular forms explicitly when required.

## 9. Extending lexical functions

Lexical-function data has two layers.

### `en-lexical-functions.tsv`

This is the explicit, high-priority layer. Use it for precise collocations and exceptions to general families.

Columns:

```text
kind  predicate  function  realizer  form  prep  note
```

Example:

```text
support  DECISION  oper1  MAKE  indef
```

### `en-lexical-function-families.tsv`

This file defines broad lexical families.

Columns:

```text
kind  function  realizer  form  prep  predicates  note
```

A family entry does not override an explicit entry already defined in `en-lexical-functions.tsv`.

### `kind` values

```text
support
noun_modifier
adj_modifier
```

### `form` values

For predicative nouns:

```text
bare
indef
def
```

These represent respectively no determiner, an indefinite article, or a definite article.

### Regeneration

After changing lexical-function TSV files:

```bash
python3 generate_lexical_functions.py --check
python3 generate_lexical_functions.py
```

Then rebuild the compacted lexicon:

```bash
elvexlexicon \
  --clf en \
  --macros-file en.macros \
  --pattern-file en.pattern \
  --morpho-file en.morpho \
  build
```

Do not manually edit the block delimited by:

```text
BEGIN GENERATED LEXICAL FUNCTIONS
...
END GENERATED LEXICAL FUNCTIONS
```

The generator replaces this block idempotently.

## 10. Running regression tests

A convenient shell helper is:

```bash
run_test () {
  stem="$1"
  elvex \
    --macros-file en.macros \
    --compacted-lexicon-file en \
    --rules-file en.rules \
    --lexicon-file en.lexicon \
    < "${stem}.stdin" \
    > actual.txt && \
  diff -u "${stem}.expected.txt" actual.txt
}
```

Examples:

```bash
run_test en
run_test en-complex
run_test en-support
run_test en-lexical-functions
run_test en-lexical-functions-massive
run_test en-incepoper2
run_test en-causoper1
run_test en-large-vocab
```

An empty `diff` means that the generated output exactly matches the expected regression output.

### Support-verb morphology tests

Regenerate the support-verb tense/aspect tests with:

```bash
python3 generate_support_verb_tense_tests.py --check
python3 generate_support_verb_tense_tests.py
```

Then run:

```bash
run_test en-support-verbs-tenses
```

This corpus checks, among other things:

- present simple;
- preterite;
- present perfect;
- present continuous;
- negation;
- interrogation;
- irregular support verbs.

## 11. Lexicographic audit

Run:

```bash
python3 audit_lexical_functions.py
```

The audit produces:

```text
en-lexical-functions-quality.tsv
en-lexical-functions-quality.md
```

The report is useful for identifying:

- potentially unnatural collocations;
- suspicious determiners;
- prepositions that may need review;
- lexical functions that may be misclassified;
- semantic-head collisions or polysemy that should be split.

The audit is a QA tool. A warning does not automatically mean that an entry is incorrect.

## 12. Recommended workflow after a change

### If only `*.rules` files changed

Run:

```bash
python3 validate_static.py
```

A compacted-lexicon rebuild is normally unnecessary.

Then run the regression corpus directly related to the change and at least the large lexical-function regression.

### If `en.pattern`, `en.morpho`, or lexical TSV source files changed

Run the relevant generators first:

```bash
python3 validate_static.py
python3 generate_lexical_functions.py --check
python3 generate_lexical_functions.py
```

If `en-vocab-large.tsv` changed, also run:

```bash
python3 generate_large_vocab.py --check
python3 generate_large_vocab.py
```

Then rebuild the compacted lexicon:

```bash
elvexlexicon \
  --clf en \
  --macros-file en.macros \
  --pattern-file en.pattern \
  --morpho-file en.morpho \
  build
```

Finally, run the relevant regression corpora.

## 13. Important entry conventions

### `en.pattern` format

`en.pattern` is tab-separated:

```text
LEXEME<TAB>POS<TAB>LEMMA<TAB>FEATURES
```

Do not replace the tabs with spaces.

### Reserved semantic heads

Do not use Elvex syntax keywords directly as semantic `HEAD` atoms. In particular, avoid:

```text
FORM
TRUE
FALSE
NIL
HEAD
LEMMA
```

Use unambiguous semantic heads instead, for example:

```text
FORM_NOUN
TRUE_ADJ
FALSE_ADJ
```

The vocabulary generator already applies this convention to generated entries.

### Magn / AntiMagn ambiguity

A predicate may have a neutral lexical entry as well as `Magn` and `AntiMagn` entries.

When a modified realization is intended, specify the lexical function explicitly. Neutral realizations should remain deterministic; avoid adding several grammar paths that produce the same surface string for the same semantic input.

### Free actants in complex constructions

Free oblique actants in the current complex-support rules are realized neutrally. If a lexical function such as `Magn` must apply to the free actant itself, add a dedicated explicit pattern rather than making the general rule ambiguous.

## 14. Morphophonology handled outside the grammar

Elvex currently produces a structural surface form. Some morphophonological operations are intentionally left to a later post-processing layer, for example:

```text
a opportunity → an opportunity
can not → cannot
```

The same applies to contractions and, depending on the output context, sentence-initial capitalization of interrogatives.

Do not solve these cases by multiplying syntactic rules or lexical entries.

## 15. Common maintenance commands

### Validate repository sources

```bash
python3 validate_static.py
python3 generate_large_vocab.py --check
python3 generate_lexical_functions.py --check
python3 audit_lexical_functions.py
```

### Regenerate generated resources

```bash
python3 generate_large_vocab.py
python3 generate_lexical_functions.py
python3 generate_support_verb_tense_tests.py
```

### Rebuild the compacted lexicon

```bash
elvexlexicon \
  --clf en \
  --macros-file en.macros \
  --pattern-file en.pattern \
  --morpho-file en.morpho \
  build
```

### Run the main corpus

```bash
elvex \
  --macros-file en.macros \
  --compacted-lexicon-file en \
  --rules-file en.rules \
  --lexicon-file en.lexicon \
  < en.stdin
```
