# Partial word order

Language-neutral partial-order constraints over grammatical constituents.

Build ELVEX from the repository root; see [installation](../../../INSTALL.md).

Run this example from the repository root:

```sh
make -C data/examples DATA=partial-word-order run
make -C data/examples DATA=partial-word-order info
```

The main source files are named `partial-word-order.rules`, `partial-word-order.lexicon`, and `partial-word-order.input` or `partial-word-order.stdin`. Optional `partial-word-order.macros`, `partial-word-order.morpho`, and `partial-word-order.pattern` files are used when present.

Generated lexicon files and outputs belong in `.elvex-build/` and are not source files.
