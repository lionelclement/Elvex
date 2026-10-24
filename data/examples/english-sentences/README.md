# English sentence generation

English sentence realization with morphology, agreement, and adjective ordering.

Build ELVEX from the repository root; see [installation](../../../INSTALL.md).

Run this example from the repository root:

```sh
make -C data/examples DATA=english-sentences run
make -C data/examples DATA=english-sentences info
```

The main source files are named `english-sentences.rules`, `english-sentences.lexicon`, and `english-sentences.input` or `english-sentences.stdin`. Optional `english-sentences.macros`, `english-sentences.morpho`, and `english-sentences.pattern` files are used when present.

Generated lexicon files and outputs belong in `.elvex-build/` and are not source files.
