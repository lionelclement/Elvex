# v32 missing-output frames

This version focuses on missing Elvex coverage rather than adding broad paraphrase families.

Added targeted frames for:

- `deathPlace` / `placeOfDeath`
- `alias` / `alternativeName`
- `birthDate` / `dateOfBirth`
- sport predicates: `club`, `clubs`, `team`, `league`, `manager`, `coach`, `position`, `ground`, `youthclub`
- space/NASA predicates: `mission`, `crew1Up`, `crew2Up`, `commander`, `selection`, `was selected by NASA`, `timeInSpace`, `awards`
- other nominal fallbacks: `chairman`, `floorArea`, `address`, `status`, `almaMater`, `birthName`

Also changed `birthPlace` / `placeOfBirth` frames to accept both entity NPs and literal values via `ARG`, so values such as `"Istanbul, Turkey"@en` can be generated.

Postprocessing now repairs a few dangling unit fragments such as `square Metre>` and `minute>`.
