# v29 changes

This version adds frames based on the low BLEU/chrF (< 70) analysis of the first 1000 one-triple inputs.

## Added frame families

- `associatedMusicalArtist`, `associatedBand`, `associatedActs`, `associatedBand/associatedMusicalArtist`
  - `X is associated with the musical artist Y.`
  - `X plays with the band Y.`
- `activeYearsStartYear`
  - `X became active in Y.`
  - `X started a career in Y.`
- `language`, `officialLanguage`
  - `Y is spoken in X.`
  - `One of the languages of X is Y.`
  - `The official language of X is Y.`
  - `Y is the official language of X.`
- `background`, `occupation`
  - `X is a Y.`
  - `Y is part of the background of X.`
  - `Y is the occupation of X.`
- `instrument`
  - `X plays the Y.`
  - `X uses Y.`
  - `The instruments that X plays are Y.`
- `genre`
  - `X deals with the Y genre.`
  - `X produces Y.`
- `musicFusionGenre`
  - `Y is a music fusion genre of X.`
  - `Y is a musical genre of X.`
- `capital`, `currency`, `mayor`, `hometown`, `country`
  - additional copular and prepositional frames.
- `elevationF`, `birthYear`, `leaderParty`, `demonym`, `battle/battles`
  - additional WebNLG-aligned frames.

## Postproduction

- Converts remaining underscores in literal values, e.g. `solo_singer` -> `solo singer`.
- Removes common DBpedia disambiguation suffixes in generated surface forms, e.g. `(band)` and `(singer)`.
- Normalizes `Mc Donnell` -> `McDonnell`.
- Converts `a Singing` into `a singer`.

## Logging

- `./run` now installs requirements quietly during routine commands to avoid `Requirement already satisfied...` lines being repeated in comparison logs.
