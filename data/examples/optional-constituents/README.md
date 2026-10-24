# Optional constituents

Language-neutral optional-rule constituents and conditional features.

Build ELVEX from the repository root; see [installation](../../../INSTALL.md).

Run this example from the repository root:

```sh
make -C data/examples DATA=optional-constituents run
make -C data/examples DATA=optional-constituents info
```

The main source files are named `optional-constituents.rules`, `optional-constituents.lexicon`, and `optional-constituents.input` or `optional-constituents.stdin`. Optional `optional-constituents.macros`, `optional-constituents.morpho`, and `optional-constituents.pattern` files are used when present.

Generated lexicon files and outputs belong in `.elvex-build/` and are not source files.
