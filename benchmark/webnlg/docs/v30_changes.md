# v30 changes

This version targets the remaining low BLEU/chrF families found after v29 on the first 1,000 one-triple inputs.

## Added frame families

### associatedMusicalArtist / associatedBand / associatedActs

- `X is a member of Y.`
- `X is part of Y.`
- `X was a member of the Y band.`

These complement the existing `associated with` and `plays with the band` frames.

### instrument

- `X is a singer and also plays Y.`
- `X uses the voice.` for `Singing`-like objects.

### genre

- `X is associated with the Y.`
- `The main genre of music of X is Y.`
- `X has the music genre Y.`

### derivative / derivatives

- `X derives from Y.`
- `X is a derivative of Y.`

### battle / battles

- `X was involved in Y.`
- `One of the noted X battles was Y.`

### runway surface leftovers

- `The fourth runway at X has a surface of Y.` for `r4Surface` / `4th_runway_SurfaceType`.

## Postproduction

- Added a conservative mojibake repair for strings such as `bodhrÃ¡n` -> `bodhrán`.
- Added `the Singing` -> `the voice` cleanup for instrument-related outputs.

## Notes

The frames are still family-level frames, not sentence-specific hacks. Complex tense/aspect/modal behavior should remain in reusable rules rather than in predicate-specific one-off frames.
