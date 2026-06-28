# v35 sequence rules changes

Adds `user/rules/webnlg_sequence.rules` for WebNLG multi-triple inputs.

- `size:2` inputs are normally realized as two coordinated clauses with `and`.
- Exact duplicate `size:2` pairs with `i:$T1, ii:$T1` are realized only once, before the general coordination rule applies.
- `size:3`, `size:4`, and `size:5` inputs are realized as comma-separated coordinated sequences.

This is deliberately simple document planning: each atomic triple is passed to the existing single-triple realization rules after adding `HEAD:webnlg_simple`.
