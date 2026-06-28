# v35: WebNLG multi-triple sequence rules

This version starts support for WebNLG inputs with more than one triple.

Changes:

- Added `user/rules/webnlg_sequence.rules`.
- Included it from `user/main.rules`.
- Added a closed-class comma entry to `user/lexicon/base.lexicon`.
- Added sequence rules for `size:2`, `size:3`, and `size:4` inputs.

The new rules realize each atomic triple by reusing the existing single-triple
`SENT` rules after adding `HEAD:webnlg_simple`, then join the clauses with
coordination:

- `T1 and T2`
- `T1, T2 and T3`
- `T1, T2, T3 and T4`

This is intentionally a simple realization baseline for multi-triple examples;
it does not yet perform graph planning, aggregation, duplicate removal, or
anaphoric/discourse-based referring expression choice.

## v35 sequence guard fix 2

- `simple_triples.rules`: `S -> SENT dot` is now guarded by `HEAD:webnlg_simple`, so it no longer catches `webnlg_sequence` inputs.
- `webnlg_sequence.rules`: added a sequence-specific `S -> SENT dot` rule guarded by `HEAD:webnlg_sequence`.
- Converted inherited-structure tests in `simple_triples.rules` from `[...] <<< ↑` to guards `[...]` where the rule should be selected by the mother inherited structure.
- Added a `pattern:frame` dispatch rule so sequence triples such as `p:[HEAD:leader_Name]` can be passed to predicate-specific frames as `HEAD:leader_Name, i:..., ii:...`.
- `generate_inputs.py`: single triples with explicit frames are now emitted as `HEAD:webnlg_simple, pattern:frame, ...`, matching the guarded start rule.
