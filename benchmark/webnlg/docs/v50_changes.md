# v50 sequence cleanup

Conservative update on top of v49.

- Strengthened sequence-only duplicate filtering for numeric RDF literals vs bare numeric objects, e.g. `"2777.0"^^xsd:double` and `2777.0` now share the same sequence equality key.
- Added a few canonical predicate aliases used in frequent 2-triple gaps, without applying the rejected full input normalization.
- Added safe singleton frames for `author`, `title`, `state`, class-qualified `Building/floorArea`, and runway-number aliases.
- Kept the single-triple generation path otherwise unchanged; the main expected gain is fewer empty or repeated 2-triple realizations.
