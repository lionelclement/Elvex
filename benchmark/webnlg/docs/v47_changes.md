# V47 targeted semantic frame cleanup

V47 starts from the V46 semantic-frame-cleanup branch and makes a smaller,
more conservative pass before moving back to two- and three-triple sequences.

Changes:

- removes remaining risky `genre` paraphrases such as `produces`, `sings`,
  `deals with`, `associated with the ... genre`, and performer/exponent forms;
- keeps only neutral `genre` frames such as `The musical genre of X is Y` and
  `X has the music genre Y`;
- adds safer phrased frames for low-score single-triple predicates:
  `areaMetro`, `areaTotal`, `engine`, `budget`, `distributor`, `knownFor`,
  `numberOfLocations`, `iso6391Code`, `iso6392Code`, `length`, `servingSize`,
  `youthclubs`, and `was selected by NASA`;
- adds the corresponding lexical terminals to `base.lexicon`;
- extends predicate canonicalization for these predicate names and common
  camel-case variants;
- adds limited predicate-aware numeric units for `budget`, `servingSize`,
  `length`, and `areaMetro`.

The goal is not to maximize WebNLG BLEU by adding many paraphrases, but to
remove semantically risky alternatives and replace label-like outputs by simple
sentential frames.
