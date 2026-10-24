# English adjective ordering

English adjective ordering from semantic features.

Build ELVEX from the repository root; see [installation](../../../INSTALL.md).

Run this example from the repository root:

```sh
make -C data/examples DATA=english-adjectives run
make -C data/examples DATA=english-adjectives info
```

The main source files are named `english-adjectives.rules`, `english-adjectives.lexicon`, and `english-adjectives.input` or `english-adjectives.stdin`. Optional `english-adjectives.macros`, `english-adjectives.morpho`, and `english-adjectives.pattern` files are used when present.

Generated lexicon files and outputs belong in `.elvex-build/` and are not source files.
