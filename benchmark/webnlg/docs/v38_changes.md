# v38: ID-based sequence rules and local two-fact planning

This version assumes the Elvex guard-binding fix: repeated variables in guards
are equality constraints and do not overwrite earlier bindings.

Changes:

- `generate_inputs.py` now adds row-local typed `ID` features to every subject,
  predicate, and object feature structure.  Entity/literal IDs and predicate IDs
  use separate namespaces (`e*`, `l*`/`n*`, `p*`).
- Exact duplicate detection in `webnlg_sequence.rules` no longer depends on
  Python-side `distinct:true`; it is expressed directly by repeated variables in
  guards over `s`, `p`, and `o`.
- Added same-subject VP coordination rules:
  `X VP1 and VP2` instead of `X VP1 and X VP2` when both triples share the same
  subject and their predicates/objects differ.
- Added object-subject chain rules for simple relative attachments:
  `SENT, which ...` for relations such as location/country and copular nominal
  predicates.
- Added a small, class-based set of VP fragments for productive WebNLG frame
  families (`location`, `country`, `operator`, `ground`, `manager`, `coach`,
  `fullname`, `alternative_Name`, `floor_Area`).  The independent `SENT and SENT`
  rule remains the fallback when a predicate has no local VP fragment.

Pronouns and possessives:

- `its` is added as a determiner, but v38 deliberately does not yet use full
  pronominalisation.  Proper pronominalisation should wait until NP lexical
  entries synthesize reliable traits such as `human`, `animate`, `gender`,
  `number`, and a `pronoun`/`possessive` form.  The ID machinery introduced here
  is the structural precondition for that step.
