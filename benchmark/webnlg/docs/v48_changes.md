# V48 stabilization

This version starts from V47 and makes a conservative singleton-frame stabilization pass.

Changes:

- Keep `city` distinct from `cityServed` in generated inputs, so city triples are no longer realized as “serves”.
- Remove remaining risky/telegraphic genre and engine alternatives.
- Add robust terminal-based frames for `fullName` and spelling variants, `floorArea`, `status`, `abbreviation`, and `density`.
- Add a `musicSubgenre` frame to avoid raw label-like fallbacks such as “music music subgenre”.
- Add minimal lexical entries needed by those frames.

This version intentionally does not reintroduce the strong shared normalization from the rejected V46.
