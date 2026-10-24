# French noun phrases

A small French determiner–noun agreement example.

Build ELVEX from the repository root; see [installation](../../../INSTALL.md).

Run this example from the repository root:

```sh
make -C data/examples DATA=french-noun-phrases run
make -C data/examples DATA=french-noun-phrases info
```

The main source files are named `french-noun-phrases.rules`, `french-noun-phrases.lexicon`, and `french-noun-phrases.input` or `french-noun-phrases.stdin`. Optional `french-noun-phrases.macros`, `french-noun-phrases.morpho`, and `french-noun-phrases.pattern` files are used when present.

Generated lexicon files and outputs belong in `.elvex-build/` and are not source files.
