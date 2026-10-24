# Animal-sound generation with ELVEX

This example generates French sentences about animal sounds from an input feature structure. It demonstrates agreement and lexical choice across traditional and compacted morphological resources.

## Prerequisites

Build ELVEX first, following [INSTALL.md](../../../INSTALL.md). The shared example Makefile is intended for GNU Make 4.3 or newer; LilyPond is **not** required.

## Run from the repository root

```sh
make -C data/examples DATA=french-animal-calls run
make -C data/examples DATA=french-animal-calls lexicon
make -C data/examples DATA=french-animal-calls debug
make -C data/examples DATA=french-animal-calls info
```

The `run` target builds the compacted lexicon when necessary and prints generated sentences. `debug` saves an HTML trace under `data/examples/french-animal-calls/.elvex-build/`. Build products (`lexicon.fsa`, `lexicon.tbl`, and traces) are generated and not tracked by Git.

To remove only this example's generated files:

```sh
make -C data/examples DATA=french-animal-calls clean
```

## Source files

| File | Role |
| --- | --- |
| `french-animal-calls.stdin` | Feature-structure input (uses `HEAD:BRUIT`, `HEAD:DINDON`, `TENSE:present`) |
| `french-animal-calls.rules` | Grammar and agreement constraints |
| `french-animal-calls.lexicon` | Traditional lexical entries |
| `french-animal-calls.macros` | Feature-structure macros |
| `french-animal-calls.morpho` and `french-animal-calls.pattern` | Morphology and patterns compiled by `elvexlexicon` |

The local `Makefile` has also been updated to use `french-animal-calls.stdin`. The shared `data/examples/Makefile` is preferred because it keeps compiled lexicons in `.elvex-build/`.

If generation fails, check the macros and confirm the `.fsa` and `.tbl` files were created under `.elvex-build/`. Use the `debug` target to inspect the execution trace.
