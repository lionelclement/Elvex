# v36 sequence canonicalization

This version keeps the v35 `i`, `ii`, ... sequence input format and adds a small
pre-realization canonicalization layer in `scripts/generate_inputs.py`.

For two-triple WebNLG entries, the input builder now collapses exact or
near-equivalent pairs before writing the Elvex feature structure.  Examples:

- `runwayDesignation` + `runwayName` -> `runwayName`
- `faa` + `locationIdentifier` -> `locationIdentifier`
- `operator` + `operatingOrganisation` -> `operator`
- `city` + `cityServed` -> `cityServed`
- `r1LengthF` + `1st_runway_LengthFeet` -> `1st_runway_LengthFeet`
- `r1Surface` + `1st_runway_SurfaceType` -> `1st_runway_SurfaceType`
- `elevation` + `elevationAboveTheSeaLevel_(in_metres)` -> `elevationAboveTheSeaLevel_(in_metres)`
- `targetAirport` + `hubAirport` -> `hubAirport` when subject and object match

Non-equivalent two-triple inputs still receive `distinct:true` and are realized
by the coordination rule in `webnlg_sequence.rules`.

The version also adds explicit frames for `hubAirport` and `targetAirport`.

No Elvex run was performed in the sandbox; only Python/static checks were run.
