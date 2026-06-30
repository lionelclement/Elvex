# ELVEX regression tests 11-20

Additional regression tests to add under `test/regression/`.
They are picked up automatically by `test/run-regression.sh` because the script runs every `*.rules` file in that directory.

Covered cases:

- order chain (`order 3 < 1 < 2;`)
- first/last order constraints (`order << 3;`, `order >> 1;`)
- field-based ordering (`order 1, 2, 3 by ⇓.rank;`)
- unordered rules (`@unordered`)
- order projected over absent optionals
- guard feature filtering
- inherited-feature subsumption and variable propagation
- arithmetic with hyphenated variables
- `@withoutSpaces` generation
- `attest TRUE`
