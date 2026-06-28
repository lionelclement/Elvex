# v33 changes: numeric DBpedia units and missing numeric frames

This version focuses on numeric/unit literals and the missing frames observed in the 2001-3000 log block.

## Numeric literal parsing

Typed DBpedia literals are now parsed when the datatype is written as a URI, for example:

- `"62145.25893504"^^<http://dbpedia.org/datatype/squareMetre>` -> `NUMBER_UNIT [value:"62145.25893504", unit:"square metres"]`
- `"1.1E8"^^<http://dbpedia.org/datatype/usDollar>` -> `NUMBER_UNIT [value:"110 million", unit:"dollars"]`
- `"4.7"^^<http://dbpedia.org/datatype/kilometrePerSecond>` -> `NUMBER_UNIT [value:"4.7", unit:"kilometres per second"]`

The dynamic numeric entries remain:

```elvex
"$NUMBER"          NUMBER         [value:$NUMBER];
"$NUMBER $UNIT"    NUMBER_UNIT    [value:$NUMBER, unit:$UNIT];
"$NUMBER meters"   NUMBER_METERS  [value:$NUMBER];
```

## Added frames

The following high-frequency missing predicates now have explicit frames:

- `buildingStartDate`, `startDate`
  - `X opened in Y.`
  - `The construction of X began in Y.`
- `completionDate`, `buildingEndDate`
  - `X was completed in Y.`
- `architect`
  - `Y designed X.`
  - `X was designed by Y.`
  - `The architect of X is Y.`
- `cost`
  - `X cost Y.`
  - `The cost of X is Y.`
- `floorArea`, `floorCount`
  - `X has a floor area of Y.`
  - `X has a floor count of Y.`
- astronomy/area numeric predicates
  - `averageSpeed`, `escapeVelocity`, `orbitalPeriod`, `periapsis`, `apoapsis`, `mass`, `temperature`, `areaTotal`, `areaWater`, `populationDensity`
  - `X has a <property> of Y.`
- nominal predicates
  - `areaCode`, `formerName`, `largestCity`
  - `The <property> of X is Y.`

## Validation

Python compilation was checked in the sandbox. Elvex execution was not available here; run `./run all` locally for full validation.


## v33 fix2

- Added `@past= [tense:past];` to `user/main.macros`.
- Restored past lexical entries for building frames using `[@past]` rather than bare entries:
  - `completed`
  - `opened`
  - `designed`

## fix3: user-requested strict-low-score frames

Added focused frames for `creator/creators`, `epoch`, `leaderTitle`, `averageSpeed/avgSpeed`, and `height/Person/height`:

- `X is the creator of Y.`
- `The epoch date of X is Y.`
- `The leader title of X is Y.`
- `X has an average speed of Y.`
- `X is Y high.`

No Elvex runtime execution was performed in the assistant sandbox.
