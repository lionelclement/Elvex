# Breton morphology

Breton morphology and noun-phrase realization.

Build ELVEX from the repository root; see [installation](../../../INSTALL.md).

Run this example from the repository root:

```sh
make -C data/examples DATA=breton-morphology run
make -C data/examples DATA=breton-morphology info
```

The main source files are named `breton-morphology.rules`, `breton-morphology.lexicon`, and `breton-morphology.input` or `breton-morphology.stdin`. Optional `breton-morphology.macros`, `breton-morphology.morpho`, and `breton-morphology.pattern` files are used when present.

Generated lexicon files and outputs belong in `.elvex-build/` and are not source files.
