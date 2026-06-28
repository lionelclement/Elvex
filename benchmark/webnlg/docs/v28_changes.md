# v28 changes

This version keeps Elvex outputs as an unordered set.

## Comparison report

`compare-one`, `compare`, and `score` no longer print or report `first exact match`, because Elvex output order is not a preference order.

The visible summary keeps:

- best exact match
- best exact rank
- best normalized match
- best normalized rank
- matched output/reference
- best-of-N sentence-level sacreBLEU BLEU
- best-of-N sentence-level sacreBLEU chrF

The TSV report also includes `best_bleu`, `best_chrf`, and their corresponding output/rank fields.

## sacreBLEU

`sacrebleu>=2.4,<3` is installed through the local `.venv` by `./run setup`, `./run all`, `./run compare`, or `./run score`.

These are development best-of-N sentence-level metrics over the unordered Elvex output set. They are not the official single-output WebNLG metric.

## New frame families

Additional v28 frames target common no-normalized-match groups in the 1-1000 diagnostic log:

- genre: `X performs Y music`, `X plays Y music`, `X uses the genre Y`, `The musical genre of X is Y`.
- instrument: `X plays Y`.
- background: `X has a background as Y`.
- stylisticOrigin(s): `X originated from Y`, `X has stylistic origins in Y`.
- recordLabel/label: `X is signed to Y`.
- associatedBand/associatedMusicalArtist/associatedActs: inverse `Y is associated with X` variants.
- runway surface lexical variants include `1st runway` and `4th runway`.

The diagnostic normalizer also maps `metres/meters`, `organisation/organization`, and ordinal digit/word variants such as `1st/first` and `4th/fourth`.
