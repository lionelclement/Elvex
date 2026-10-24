# Animal Sound Generation with Elvex

This example generates French sentences about animal sounds from feature
structures. It demonstrates grammatical agreement (including gender and number)
and the selection of lexical forms using an Elvex grammar, lexicon, and compiled
morphological resources.

## Requirements

- `elvex`, the Elvex generator.
- `elvexlexicon`, the morphological lexicon compiler.
- GNU Make 4.3 or newer and a POSIX-compatible shell.

Both Elvex executables should be on `PATH`, or their locations can be provided
through the `ELVEX` and `ELVEXLEXICON` Make variables. LilyPond is not needed.

## Running the example

Use the shared Makefile **from the repository root**:

```sh
make -C test DATA=animal run      # build morphology and generate sentences
make -C test DATA=animal lexicon  # build the compacted lexicon only
make -C test DATA=animal debug    # save a complete HTML generation trace
make -C test DATA=animal info     # display resolved input paths and options
make -C test DATA=animal clean    # remove .elvex-build/ outputs
```

The input in this archive is **`animal.stdin`**, not `animal.input`. It requests
an animal-sound realization using an input feature structure with `HEAD:BRUIT`,
`HEAD:DINDON`, and `TENSE:present`.

The shared Makefile compiles `animal.morpho` and `animal.pattern` into the
compacted lexicon under `test/animal/.elvex-build/`, then runs the generator.
Generated sentences are printed to standard output. The number, order, and
wording of sentences depend on the grammar and lexical resources.

To capture the results, redirect the command output:

```sh
make -C test DATA=animal run > animal-sentences.txt
```

Note that this also captures Make's echoed commands. The `debug` target writes
`test/animal/.elvex-build/debug.html`.

**Legacy Makefile note:** `test/animal/Makefile` still refers to
`animal.input`. Because this archive contains `animal.stdin` instead, its local
`make run` and `make trace` targets require updating before use. The commands
above use `test/Makefile`, which supports both input extensions.

## Files

| File | Purpose |
| --- | --- |
| `animal.stdin` | Initial feature-structure request |
| `animal.rules` | Syntax and agreement constraints |
| `animal.lexicon` | Direct lexical entries |
| `animal.macros` | Reusable feature-structure macros |
| `animal.morpho` | Morphological data used by `elvexlexicon` |
| `animal.pattern` | Patterns used by `elvexlexicon` |
| `Makefile` | Legacy local build commands (see note above) |
| `.elvex-build/lexicon.fsa`, `.elvex-build/lexicon.tbl` | Generated compacted lexicon files |

The direct lexicon alone does not contain all the resources needed for this
example; compile the morphological resources before generating sentences.

## Troubleshooting

If Elvex reports an unknown macro, confirm that `animal.macros` is passed to
the generator. If no sentences appear, verify that the compacted lexicon was
built successfully and that both `.fsa` and `.tbl` files are present in
`.elvex-build/`. Use the `debug` target to inspect a full generation trace.
