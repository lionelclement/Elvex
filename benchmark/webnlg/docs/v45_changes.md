# V45 changes

This version normalizes predicate spellings before Elvex input generation when a canonical frame is available. The original WebNLG triples remain unchanged in comments and reports, but the generated predicate HEAD may use the canonical frame head. This reduces duplicate frame definitions and recovers variants such as fullName/fullname/longName, floorArea/floor_Area, and similar aliases.

It also changes the compact report column labels to English:

- ordinal
- n-triples
- n Elvex outputs
- n WebNLG outputs
- WebNLG triples
- WebNLG outputs
- Elvex outputs
- best exact match
- best formatted match
- best BLEU
- best CHRF

The typo `formated` was corrected to `formatted`.
