# French light-verb constructions

French light-verb and lexical-function constructions.

Build ELVEX from the repository root; see [installation](../../../INSTALL.md).

Run this example from the repository root:

```sh
make -C data/examples DATA=french-lightness run
make -C data/examples DATA=french-lightness info
```

The main source files are named `french-lightness.rules`, `french-lightness.lexicon`, and `french-lightness.input` or `french-lightness.stdin`. Optional `french-lightness.macros`, `french-lightness.morpho`, and `french-lightness.pattern` files are used when present.

Generated lexicon files and outputs belong in `.elvex-build/` and are not source files.
