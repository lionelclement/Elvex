# French syntax

A French syntax and morphology generation example.

Build ELVEX from the repository root; see [installation](../../../INSTALL.md).

Run this example from the repository root:

```sh
make -C data/examples DATA=french-syntax run
make -C data/examples DATA=french-syntax info
```

The main source files are named `french-syntax.rules`, `french-syntax.lexicon`, and `french-syntax.input` or `french-syntax.stdin`. Optional `french-syntax.macros`, `french-syntax.morpho`, and `french-syntax.pattern` files are used when present.

Generated lexicon files and outputs belong in `.elvex-build/` and are not source files.

## A compositional conditional sentence

Semantic input (`french-syntax.stdin`):

```text
text [HEAD:cause, i:[HEAD:rain], ii:[HEAD:umbrella, i:[HEAD:_you]]]
```

The `text` production combines a subordinate clause, a comma, a main
clause (`S`), and a period. `CONDITIONAL_CLAUSE → conj S` treats `si` as
an independent conjunction, defined in the ordinary lexicon. Both clauses
use the generic categories `S`, `NP`, and `VP`; there is no syntactic
category named after `rain`, `umbrella`, or an advice scenario.

`rain` and `umbrella` are semantic keys used by the lexicon and morphological
patterns. The verb forms `pleut` and `prendras` come from the compacted
lexicon. The noun `parapluie` is an ordinary `noun` lexical entry with
`HEAD:umbrella`, composed with the determiner `un` by the existing `NP` rules.
For this small demonstration, the personal-clause rule realizes the semantic
head as an indefinite object, while the impersonal-clause rule provides the
weather subject `il`. These are still simplified clause semantics, not a
complete treatment of arbitrary event frames.

Run from the repository root:

```sh
make -s -C data/examples DATA=french-syntax first \
  | python3 src/main/elvexpostedition_fr.py
```

Expected output:

```text
S'il pleut, tu prendras un parapluie.
```

The French post-editor applies `si il` → `s'il` and fixes punctuation
spacing. The existing subject–verb–object example remains available in
`french-syntax.stdin` as a comment.
