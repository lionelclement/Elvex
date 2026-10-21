# Animal — Elvex language-generation experiment

This small French-language experiment demonstrates natural-language generation using **Elvex**. A feature structure in `animal.input` is realized as sentences by a grammar, a lexicon, and compiled morphological resources. The experiment shows agreement in gender and number and different verbs for animal sounds.

## Requirements

- `elvex` (Elvex sentence generator)
- `elvexlexicon` (Elvex morphological lexicon compiler)
- `make` and a POSIX-compatible shell

Both Elvex executables should be available on your `PATH`. The experiment does not require LilyPond.

## Run

In this directory:

```sh
make          # compile the lexicon and print generated sentences
make run      # same as make
make lexicon  # compile morphology and patterns only
make trace    # create animal-trace.html
make clean    # remove generated lexicon files and diagnostic outputs
make help     # list targets
```

`make run` first runs **elvexlexicon**, then **elvex**. The trailing `build` is a **positional argument**, not an output redirection:

```sh
elvexlexicon \
  --compacted-lexicon-file animal \
  --macros-file animal.macros \
  --pattern-file animal.pattern \
  --morpho-file animal.morpho \
  build

elvex \
  --macros-file animal.macros \
  --rules-file animal.rules \
  --lexicon-file animal.lexicon \
  --compacted-lexicon-file animal \
  --input-file animal.input
```

All generated sentences are printed to the terminal (not saved to `animal.out`). A successful run can produce sentences such as:

```text
le chien hurle .
la chienne hurle .
les chiens aboient .
les chiennes jappent .
```

The actual set and order depend on the grammar, lexical resources and generator options. To capture the text when desired, run `make run > sentences.txt` (Make's command echoes will also appear unless you suppress them).

## Project files

| File | Purpose |
| --- | --- |
| `animal.input` | Initial semantic / feature-structure request |
| `animal.rules` | Syntactic and agreement rules |
| `animal.macros` | Reusable feature macros, loaded with `--macros-file` |
| `animal.lexicon` | Direct lexical entries |
| `animal.pattern` | Lexical patterns for compilation |
| `animal.morpho` | Morphological data for compilation |
| `animal.fsa`, `animal.tbl` | Generated compacted lexicon files (rebuild with `make lexicon`) |
| `Makefile` | Reproducible build commands |

The compacted lexicon must be built before generation: `animal.lexicon` alone does not supply all the morphological entries needed by the grammar.

## Troubleshooting

If you see `unknown macro`, confirm that Elvex is invoked with `--macros-file animal.macros`. If no sentence is generated, first run `make lexicon` and verify that both compacted lexicon files were produced, then retry `make run`. Use `make trace` for a detailed HTML derivation trace.

The Makefile was checked against the working command sequence, but has not been run with Elvex in this environment.
