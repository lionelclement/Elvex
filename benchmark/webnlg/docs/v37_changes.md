# v37 changes

This version starts from v36 and targets the most frequent empty-output
predicate families observed on simple WebNLG triples, while preserving the v36
sequence canonicalisation.

Main additions:

- sport frames: ground, manager, coach, chairman;
- office frames: office and office(workedAt, workedAs);
- name frames: fullname, full_Name, long_Name, alternative_Name, alias, aka,
  alter_Ego, nickname, birth_Name;
- education and location frames: alma_Mater, location, location_City,
  location_Country, foundation_Place, subdivision_Name, country, region;
- building / bibliographic / technical frames: floor_Area, address,
  ISSN/ISBN/CODEN variants, ICAO/IATA identifiers, media_Type, publisher,
  transmission, wheelbase, assembly, density, course, UTC offset;
- date and vehicle/ship/space frames: active_Years_Start_Date,
  active_Years_End_Date, date_Of_Ret, death_Date, maiden/final flight,
  ship launch, christening, release, inauguration, commander, crew member,
  mission, discoverer/discovered, creator, preceded_By.

The intent is not to copy individual WebNLG references, but to encode recurring
predicate families as explicit symbolic lexical frames.
