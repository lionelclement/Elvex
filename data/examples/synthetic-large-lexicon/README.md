# Synthetic large lexicon

A synthetic morphology and lexicon stress test, independent of any natural language.

Build ELVEX from the repository root; see [installation](../../../INSTALL.md).

Run this example from the repository root:

```sh
make -C data/examples DATA=synthetic-large-lexicon run
make -C data/examples DATA=synthetic-large-lexicon info
```

The main source files are named `synthetic-large-lexicon.rules`, `synthetic-large-lexicon.lexicon`, and `synthetic-large-lexicon.input` or `synthetic-large-lexicon.stdin`. Optional `synthetic-large-lexicon.macros`, `synthetic-large-lexicon.morpho`, and `synthetic-large-lexicon.pattern` files are used when present.

Generated lexicon files and outputs belong in `.elvex-build/` and are not source files.
