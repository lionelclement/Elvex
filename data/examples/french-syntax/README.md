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
