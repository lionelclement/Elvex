# ELVEX regression tests

Run from the repository root:

```sh
test/run-regression.sh ./bin/elvex
```

The script compares generated output as a set: empty lines are ignored and
remaining lines are sorted before comparison. This keeps the tests stable when
valid generation order changes.

Covered cases:

- required sequence generation;
- optional terms in middle and final position;
- rules whose RHS is entirely optional;
- `#i` presence tests;
- `#i.j` alternative selection tests;
- optional alternatives;
- cross-dependencies between optional terms;
- hyphenated identifiers such as `foo-123`;
- optionals around a required term without duplicate `↓i` definitions.
