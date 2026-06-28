# v34 targeted WebNLG score-oriented frames

This version starts from `webnlg_overwrite_v33_numeric_units_fix3_user_frames.zip`.
It remains a WebNLG pilot patch rather than a change to the Elvex generation
algorithm.

Main changes:

- Predicate-aware numeric input normalization in `scripts/generate_inputs.py`:
  - `areaTotal`, `areaWater`, `areaLand`: bare large values are converted from
    square metres to square kilometres.
  - `populationDensity`: bare numbers receive the unit `inhabitants per square
    kilometre`.
  - `averageSpeed`, `avgSpeed`, `escapeVelocity`: bare values are divided by
    3600 and rendered as kilometres per second.
  - `mass`: bare gram-like values are converted to kilograms.
  - `runtime`: bare second-like values are converted to minutes.
  - `height`: bare numeric values receive metres.
  - `floorArea` and `Building/floorArea`: bare values receive square metres.
  - ISO dates are kept as literal values rather than split as entity names.

- Added predicate frames for frequent low BLEU/chrF families:
  `creator`, `creators`, `ingredient`, `mainIngredient`, `hasVariant`,
  `dishVariation`, `engine`, `relatedMeanOfTransportation`, `subsequentWork`,
  `previousWork`, `starring`, `region`, `city`, `club`, `team`, `season`,
  `areaTotal`, `areaWater`, `populationDensity`, `leaderTitle`, `birthDate`,
  `dateOfBirth`, `height`, `capacity`, `award`, `ethnicGroups`, `manufacturer`,
  `party`, `nationality`, and `class`.

- Added postprocessing cleanup for possessive spacing, common WebNLG DBpedia
  disambiguation suffixes such as `(comics)` and `(novel)`, and remaining
  placeholder noun leaks such as `TOTAL AREA NOUN`.

Static checks run here:

- `python3 -m py_compile scripts/*.py lib/*.py`
- balanced brace counts for `user/rules/frames.rules`

Elvex itself was not run in this environment.
