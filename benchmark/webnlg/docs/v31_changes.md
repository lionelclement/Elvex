# v31 changes

This version is based on v30 and adds targeted frames from the low BLEU/chrF diagnosis on the first 1000 simple triples.

## Added predicate families

### origin / hometown
- `X comes from Y.`
- `X is from Y.`
- `The origin of X is Y.`

### ethnicGroup
- `An ethnic group of X is Y.`
- `Y is an ethnic group in X.`
- `Y is an ethnic group of X.`
- `X has an ethnic group called the Y.`

### taxonomy predicates
For `division`, `order`, `class`, and `family`:
- `X belongs to the division/order/class/family of Y.`

### aircraft predicates
For `aircraftTransport`:
- `Y is a transport aircraft in X.`
- `The transport aircraft for X is Y.`

For `aircraftAttack` and `attackAircraft`:
- `Y is an attack aircraft of X.`

### headquarter
- `The headquarters of X are in Y.`
- `The headquarters of X are located in Y.`

### anthem
- `The national anthem of X is called Y.`

### associated musical predicates
- `The singer X is associated with the band Y.`
- `X performed for Y.`

### genre
- `X is an exponent of Y.`
- `X is a performer of the musical genre Y.`
- `X sings Y music.`

## Notes

The v31 changes are intentionally targeted. They avoid broad fallback rules that would create visibly wrong outputs, especially for music/instrument cases where the subject may be a person, genre, or musical work.


Fix: the taxonomy `order` predicate is represented internally as `P_order` to avoid the Elvex reserved word `order` in feature values.
