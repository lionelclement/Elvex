#!/usr/bin/env python3
from __future__ import annotations

import argparse, csv, json, re, shutil, unicodedata
from decimal import Decimal, InvalidOperation, ROUND_HALF_UP
from pathlib import Path
import sys
from typing import Any

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from lib.webnlg_utils import read_jsonl, elvex_atom, write_jsonl, parse_rdf_literal, parse_number_value, quote_form


DATE_LITERAL_RE = re.compile(r"^\d{4}-\d{2}-\d{2}$")


def _decimal_text(value: Decimal, places: int | None = None) -> str:
    """Return a compact decimal string, optionally rounded."""
    if places is not None:
        q = Decimal("1") if places == 0 else Decimal("1").scaleb(-places)
        value = value.quantize(q, rounding=ROUND_HALF_UP)
    text = format(value, "f")
    if "." in text:
        text = text.rstrip("0").rstrip(".")
    return text or "0"


def _number_fs(value: str, datatype: str, unit: str | None = None) -> str:
    if unit:
        return f"[value:{quote_form(value)}, unit:{quote_form(unit)}, datatype:number_unit]"
    return f"[value:{quote_form(value)}, datatype:{datatype}]"


def predicate_aware_numeric_value(predicate: str | None, value: str) -> str | None:
    """Normalize frequent WebNLG predicate-specific numeric conventions.

    Some WebNLG single-triple objects are bare numbers even though the
    references verbalize a conventional unit or scaled value.  The generator
    does not infer these meanings at runtime; this conversion makes the
    benchmark-specific input representation explicit before realization.
    """
    if not predicate:
        return None
    pred = elvex_atom(predicate, "P")
    raw = str(value).strip().strip('"')
    if DATE_LITERAL_RE.match(raw):
        return f"[FORM:{quote_form(raw)}, datatype:string]"
    number = parse_number_value(value)
    if not number:
        return None
    val = str(number.get("value", raw))
    unit = number.get("unit")
    datatype = number.get("datatype", "number")
    try:
        dec = Decimal(val)
    except InvalidOperation:
        dec = None

    # WebNLG uses square kilometres in references for these area predicates,
    # while some RDF objects are bare square-metre values.
    if pred in {"area_Total", "areaTotal", "area_Metro", "areaMetro", "area_Water", "areaWater", "area_Land", "areaLand"}:
        if unit is None and dec is not None and abs(dec) >= Decimal("10000"):
            return _number_fs(_decimal_text(dec / Decimal("1000000"), 2),
                              "number_unit", "square kilometres")
        if unit is None:
            return _number_fs(val, "number_unit", "square kilometres")

    if pred in {"floor_Area", "floorArea", "Building_floor_Area", "Building_floorArea"}:
        if unit is None:
            return _number_fs(val, "number_unit", "square metres")

    if pred in {"population_Density", "populationDensity"}:
        if unit is None:
            return _number_fs(val, "number_unit",
                              "inhabitants per square kilometre")

    # Many asteroid speed values are given in kilometres per hour in the data
    # but are verbalized by WebNLG as kilometres per second.
    if pred in {"average_Speed", "avg_Speed", "escape_Velocity"}:
        if unit is None and dec is not None:
            return _number_fs(_decimal_text(dec / Decimal("3600"), 4),
                              "number_unit", "kilometres per second")
        if unit is None:
            return _number_fs(val, "number_unit", "kilometres per second")

    if pred in {"mass", "density"}:
        if unit is None and dec is not None and abs(dec) >= Decimal("1000"):
            return _number_fs(_decimal_text(dec / Decimal("1000"), 2),
                              "number_unit", "kilograms")
        if unit is None:
            return _number_fs(val, "number_unit", "kilograms")

    if pred in {"height", "Person_height", "personHeight"}:
        if unit is None:
            return _number_fs(val, "number_unit", "metres")


    if pred in {"budget"}:
        if unit is None:
            return _number_fs(val, "number_unit", "dollars")

    if pred in {"serving_Size", "servingSize"}:
        if unit is None:
            return _number_fs(val, "number_unit", "grams")

    if pred in {"length", "MeanOfTransportation_length"}:
        if unit is None:
            return _number_fs(val, "number_unit", "metres")

    if pred == "runtime":
        if unit is None and dec is not None and dec >= Decimal("1000"):
            return _number_fs(_decimal_text(dec / Decimal("60"), 1),
                              "number_unit", "minutes")
        if unit is None:
            return _number_fs(val, "number_unit", "minutes")

    return None




def _canonical_seq_predicate(predicate: str) -> str:
    """Canonical predicate name used only for local sequence cleaning.

    The goal is conservative: collapse alternative WebNLG predicate spellings
    that express the same fact when subject and object also match after
    normalization.  This reduces repeated triples before Elvex realization,
    without asking the grammar to infer RDF equivalence at runtime.
    """
    pred = elvex_atom(predicate, "P")
    direct = {
        # airport/runway aliases
        "runwayDesignation": "runwayName",
        "runway_Designation": "runwayName",
        "faa": "locationIdentifier",
        "icao_Location_Identifier": "icaoLocationIdentifier",
        "ICAO_Location_Identifier": "icaoLocationIdentifier",
        "iata_Location_Identifier": "iataLocationIdentifier",
        "IATA_Location_Identifier": "iataLocationIdentifier",
        "operatingOrganisation": "operator",
        "operating_Organisation": "operator",
        "city": "city_Served",
        "cityServed": "city_Served",
        "city_Served": "city_Served",
        "location_City": "city_Served",
        "location_Country": "location",
        "elevation": "elevationM",
        "elevationM": "elevationM",
        "elevation_M": "elevationM",
        "elevation_Above_Sea_Level": "elevationM",
        "elevationAboveTheSeaLevel_in_metres": "elevationM",
        "elevationAboveTheSeaLevel_(in_metres)": "elevationM",
        "targetAirport": "hubAirport",
        # names and identifiers
        "fullname": "fullName",
        "full_Name": "fullName",
        "long_Name": "fullName",
        "longName": "fullName",
        "fullName": "fullName",
        "alternative_Name": "alternativeName",
        "alias": "alternativeName",
        "aka": "alternativeName",
        "alter_Ego": "alternativeName",
        "nickname": "alternativeName",
        "issn": "issnNumber",
        "ISSN_number": "issnNumber",
        "issn_Number": "issnNumber",
        "isbn": "isbnNumber",
        "ISBN_number": "isbnNumber",
        "isbn_Number": "isbnNumber",
        "coden": "codenCode",
        "CODEN_code": "codenCode",
        "coden_Code": "codenCode",
        # people / organizations
        "manager": "manager",
        "coach": "manager",
        "chairman": "chairman",
        "leader": "leader_Name",
        "leaderName": "leader_Name",
        "leader_Name": "leader_Name",
        "club": "club",
        "clubs": "club",
        "associatedBand": "associatedMusicalArtist",
        "associatedMusicalArtist": "associatedMusicalArtist",
        "performer": "associatedMusicalArtist",
        "status": "status",

        "musicsubgenre": "musicSubgenre",
        "music_subgenre": "musicSubgenre",
        "subgenre": "musicSubgenre",
        "chairman": "chairman",
        "address": "address",
        "abbreviation": "abbreviation",
        "date_Of_Birth": "birthDate",
        "dateOfBirth": "birthDate",
        "birth_Date": "birthDate",
        "placeOfBirth": "birthPlace",
        "death_Date": "deathDate",
        "date_Of_Death": "deathDate",
        "date_Of_Ret": "retirementDate",
        "date_Of_Retirement": "retirementDate",
        "alma_Mater": "almaMater",
        "office_worked_At_worked_As": "office",
        # books/journals/works
        "media_Type": "mediaType",
        "number_Of_Pages": "numberOfPages",
        "release_Date": "releaseDate",
        "preceded_By": "precededBy",
        # places and measurements
        "floor_Area": "floorArea",
        "floorArea": "floorArea",
        "foundation_Place": "foundationPlace",
        "founding_Date": "foundingDate",
        "founding_Year": "foundingDate",
        "density": "density",
        "population_Total": "populationTotal",
        "populationTotal": "populationTotal",
        "area_Total": "areaTotal",
        "areaTotal": "areaTotal",
        "area_Metro": "areaMetro",
        "areaMetro": "areaMetro",
        "number_Of_Locations": "numberOfLocations",
        "numberOfLocations": "numberOfLocations",
        "known_For": "knownFor",
        "knownFor": "knownFor",
        "iso6391Code": "iso6391Code",
        "iso6392Code": "iso6392Code",
        "serving_Size": "servingSize",
        "servingSize": "servingSize",
        "utc_Offset": "utcOffset",
        "music_Subgenre": "musicSubgenre",
        "musicSubgenre": "musicSubgenre",
        "subgenre": "musicSubgenre",
        "abbreviation": "abbreviation",
        "address": "address",
        "shipChristened": "christening_Date",
        "ship_Christened": "christening_Date",
        "christening_Date": "christening_Date",
        "christeningDate": "christening_Date",
        "shipMaidenVoyage": "maiden_Voyage",
        "ship_Maiden_Voyage": "maiden_Voyage",
        "shipCompleted": "completionDate",
        "ship_Completed": "completionDate",
        "completion_Date": "completionDate",
        "faculty": "facultySize",
        "facultySize": "facultySize",
        "academicStaffSize": "facultySize",
        "academic_Staff_Size": "facultySize",
        "first": "maidenFlight",
        "maiden_Flight": "maidenFlight",
        "maidenFlight": "maidenFlight",
        "runwaySurface": "runway_Surface_Type",
        "runway_Surface": "runway_Surface_Type",
        "runwaySurfaceType": "runway_Surface_Type",
        "runway_Surface_Type": "runway_Surface_Type",
        "r1Surface": "P_1st_runway_Surface_Type",
        "r2Surface": "P_2nd_runway_Surface_Type",
        "r3Surface": "P_3rd_runway_Surface_Type",
        "r4Surface": "P_4th_runway_Surface_Type",
        "r5Surface": "P_5th_runway_Surface_Type",
    }
    if pred in direct:
        return direct[pred]

    norm = re.sub(r"[^a-z0-9]+", "", pred.lower())
    normalized_direct = {
        "mediatype": "mediaType",
        "issnnumber": "issnNumber",
        "isbnnumber": "isbnNumber",
        "codencode": "codenCode",
        "fulllname": "fullName",
        "fullname": "fullName",
        "alternativename": "alternativeName",
        "alterego": "alternativeName",
        "altermativeego": "alternativeName",
        "almamater": "almaMater",
        "activeyearsstartdate": "activeYearsStartDate",
        "activeyearsenddate": "activeYearsEndDate",
        "finalflight": "finalFlight",
        "maidenflight": "maidenFlight",
        "maidenvoyage": "maiden_Voyage",
        "foundationplace": "foundationPlace",
        "foundingdate": "foundingDate",
        "foundingyear": "foundingDate",
        "locationcity": "city_Served",
        "locationcountry": "location",
        "cityserved": "city_Served",
        "city": "city_Served",
        "operatingorganisation": "operator",
        "operatingorganization": "operator",
        "icaoLocationidentifier": "icaoLocationIdentifier",
        "iatalocationidentifier": "iataLocationIdentifier",
        "locationidentifier": "locationIdentifier",
        "elevationabovesealevel": "elevationM",
        "elevationabovethesealevelinmetres": "elevationM",
        "floorarea": "floorArea",
        "populationtotal": "populationTotal",
        "populationdensity": "populationDensity",
        "areatotal": "areaTotal",
        "areametro": "areaMetro",
        "metropolitanarea": "areaMetro",
        "budget": "budget",
        "distributor": "distributor",
        "knownfor": "knownFor",
        "numberoflocations": "numberOfLocations",
        "iso6391code": "iso6391Code",
        "iso6392code": "iso6392Code",
        "servingsize": "servingSize",
        "length": "length",
        "selectedbynasa": "was_selected_by_NASA",
        "wasselectedbynasa": "was_selected_by_NASA",
        "youthclubs": "youthclubs",
        "arealand": "areaLand",
        "areawater": "areaWater",
        "associatedband": "associatedMusicalArtist",
        "associatedmusicalartist": "associatedMusicalArtist",
        "performedby": "performer",
        "dateofbirth": "birthDate",
        "birthdate": "birthDate",
        "birthplace": "birthPlace",
        "placeofbirth": "birthPlace",
        "dateofdeath": "deathDate",
        "deathdate": "deathDate",
        "dateofretirement": "retirementDate",
        "dateofret": "retirementDate",
        "numberofpages": "numberOfPages",
        "releasedate": "releaseDate",
        "precededby": "precededBy",
        "longname": "fullName",
        "floorarea": "floorArea",
        "status": "status",

        "musicsubgenre": "musicSubgenre",
        "music_subgenre": "musicSubgenre",
        "subgenre": "musicSubgenre",
        "chairman": "chairman",
        "address": "address",
        "abbreviation": "abbreviation",
        "density": "density",
        "utcOffset": "utcOffset",
        "utcoffset": "utcOffset",
        "buildingtype": "buildingType",
        "servingtemperature": "servingTemperature",
        "latinname": "latinName",
        "nativename": "nativeName",
        "motto": "motto",
        "material": "material",
        "architect": "architect",
        "state": "state",
        "ispartofmilitaryconflict": "isPartOfMilitaryConflict",
        "ispartof": "subdivisionName",
        "subdivisionname": "subdivisionName",
        "addedtothenationalregisterofhistoricplaces": "addedToNationalRegister",
        "added": "addedToNationalRegister",
        "crew1up": "commander",
        "crew2up": "backupPilot",
        "backuppilot": "backupPilot",
        "ribbon": "award",
        "wasawarded": "award",


        "elevationm": "elevationM",
        "leader": "leader_Name",
        "leadername": "leader_Name",
        "leader_name": "leader_Name",
        "runwaysurface": "runway_Surface_Type",
        "runwaysurfacetype": "runway_Surface_Type",
        "r1surface": "P_1st_runway_Surface_Type",
        "r2surface": "P_2nd_runway_Surface_Type",
        "r3surface": "P_3rd_runway_Surface_Type",
        "r4surface": "P_4th_runway_Surface_Type",
        "r5surface": "P_5th_runway_Surface_Type",
        "p1strunwaysurfacetype": "P_1st_runway_Surface_Type",
        "p2ndrunwaysurfacetype": "P_2nd_runway_Surface_Type",
        "p3rdrunwaysurfacetype": "P_3rd_runway_Surface_Type",
        "p4thrunwaysurfacetype": "P_4th_runway_Surface_Type",
        "p5thrunwaysurfacetype": "P_5th_runway_Surface_Type",
        "shipchristened": "christening_Date",
        "christeningdate": "christening_Date",
        "shipmaidenvoyage": "maiden_Voyage",
        "maidenvoyage": "maiden_Voyage",
        "shipcompleted": "completionDate",
        "completiondate": "completionDate",
        "faculty": "facultySize",
        "facultysize": "facultySize",
        "academicstaffsize": "facultySize",
        "first": "maidenFlight",
        "maidenflight": "maidenFlight",
        "buildingfloorarea": "floorArea",
        "buildingfloor_area": "floorArea",
        "floorarea": "floorArea",
        "chairman": "chairman",
        "address": "address",
        "servingtemperature": "servingTemperature",
        "buildingtype": "buildingType",
        "latinname": "latinName",
        "nativename": "nativeName",
        "author": "author",
        "title": "title",
        "state": "state",
        "r1number": "_1st_runway_Number",
        "r2number": "_2nd_runway_Number",
        "r3number": "_3rd_runway_Number",
        "r4number": "_4th_runway_Number",
        "r5number": "_5th_runway_Number",
    }
    if norm in normalized_direct:
        return normalized_direct[norm]

    # Runway aliases: r1LengthF <-> 1st_runway_LengthFeet, etc.
    direct_runway = {
        "P_1st_Runway_Length_Metre": "1st_runway_LengthMetre",
        "P_2nd_Runway_Length_Metre": "2nd_runway_LengthMetre",
        "P_3rd_Runway_Length_Metre": "3rd_runway_LengthMetre",
        "P_4th_Runway_Length_Metre": "4th_runway_LengthMetre",
        "P_5th_Runway_Length_Metre": "5th_runway_LengthMetre",
        "P_1st_Runway_Length_Feet": "1st_runway_LengthFeet",
        "P_2nd_Runway_Length_Feet": "2nd_runway_LengthFeet",
        "P_3rd_Runway_Length_Feet": "3rd_runway_LengthFeet",
        "P_4th_Runway_Length_Feet": "4th_runway_LengthFeet",
        "P_5th_Runway_Length_Feet": "5th_runway_LengthFeet",
        "P_1st_runway_Length_Feet": "1st_runway_LengthFeet",
        "P_2nd_runway_Length_Feet": "2nd_runway_LengthFeet",
        "P_3rd_runway_Length_Feet": "3rd_runway_LengthFeet",
        "P_4th_runway_Length_Feet": "4th_runway_LengthFeet",
        "P_5th_runway_Length_Feet": "5th_runway_LengthFeet",
        "P_1st_runway_Length_Metre": "1st_runway_LengthMetre",
        "P_2nd_runway_Length_Metre": "2nd_runway_LengthMetre",
        "P_3rd_runway_Length_Metre": "3rd_runway_LengthMetre",
        "P_4th_runway_Length_Metre": "4th_runway_LengthMetre",
        "P_5th_runway_Length_Metre": "5th_runway_LengthMetre",
        "P_1st_runway_SurfaceType": "P_1st_runway_Surface_Type",
        "P_2nd_runway_SurfaceType": "P_2nd_runway_Surface_Type",
        "P_3rd_runway_SurfaceType": "P_3rd_runway_Surface_Type",
        "P_4th_runway_SurfaceType": "P_4th_runway_Surface_Type",
        "P_5th_runway_SurfaceType": "P_5th_runway_Surface_Type",
        "P_1st_Runway_SurfaceType": "P_1st_runway_Surface_Type",
        "P_2nd_Runway_SurfaceType": "P_2nd_runway_Surface_Type",
        "P_3rd_Runway_SurfaceType": "P_3rd_runway_Surface_Type",
        "P_4th_Runway_SurfaceType": "P_4th_runway_Surface_Type",
        "P_5th_Runway_SurfaceType": "P_5th_runway_Surface_Type",
        "P__1st_runway_Number": "_1st_runway_Number",
        "P__2nd_runway_Number": "_2nd_runway_Number",
        "P__3rd_runway_Number": "_3rd_runway_Number",
        "P__4th_runway_Number": "_4th_runway_Number",
        "P__5th_runway_Number": "_5th_runway_Number",
        "P__1st_Runway_Number": "_1st_runway_Number",
        "P__2nd_Runway_Number": "_2nd_runway_Number",
        "P__3rd_Runway_Number": "_3rd_runway_Number",
        "P__4th_Runway_Number": "_4th_runway_Number",
        "P__5th_Runway_Number": "_5th_runway_Number",
    }
    if pred in direct_runway:
        return direct_runway[pred]
    m = re.fullmatch(r"r([1-5])(?:_)?Length(?:_)?F", pred)
    if m:
        ords = {"1": "1st", "2": "2nd", "3": "3rd", "4": "4th", "5": "5th"}
        return f"{ords[m.group(1)]}_runway_LengthFeet"
    m = re.fullmatch(r"r([1-5])(?:_)?Length(?:_)?M", pred)
    if m:
        ords = {"1": "1st", "2": "2nd", "3": "3rd", "4": "4th", "5": "5th"}
        return f"{ords[m.group(1)]}_runway_LengthMetre"
    m = re.fullmatch(r"r([1-5])(?:_)?Surface", pred)
    if m:
        ords = {"1": "1st", "2": "2nd", "3": "3rd", "4": "4th", "5": "5th"}
        return f"{ords[m.group(1)]}_runway_SurfaceType"
    m = re.fullmatch(r"r([1-5])(?:_)?Number", pred)
    if m:
        ords = {"1": "1st", "2": "2nd", "3": "3rd", "4": "4th", "5": "5th"}
        return f"{ords[m.group(1)]}_runway_Number"
    return pred


def _plain_text_key(value: str) -> str:
    """Canonical surface key for conservative WebNLG duplicate filtering."""
    raw = str(value).strip().strip('"').lower()
    raw = raw.replace("_", " ")
    raw = unicodedata.normalize("NFKD", raw)
    raw = "".join(ch for ch in raw if not unicodedata.combining(ch))
    raw = re.sub(r"\([^)]*\)", " ", raw)
    raw = re.sub(r"\bthe\b", " ", raw)
    raw = re.sub(r"[^a-z0-9.+-]+", " ", raw)
    raw = re.sub(r"\s+", " ", raw).strip()
    aliases = {
        "u s": "united states",
        "us": "united states",
        "usa": "united states",
        "u s a": "united states",
        "united states of america": "united states",
        "america": "united states",
        "uk": "united kingdom",
        "u k": "united kingdom",
        "great britain": "united kingdom",
        "republic of ireland": "ireland",
        "republic of turkey": "turkey",
        "french republic": "france",
        "republic of india": "india",
        "republic of philippines": "philippines",
        "the philippines": "philippines",
    }
    return aliases.get(raw, raw)


def _sequence_value_key(predicate: str | None, value: str) -> tuple[str, str]:
    """Predicate-aware equality key for sequence-level fact cleaning."""
    # First use any explicit predicate-aware conversion, because this makes
    # units comparable for values such as elevation or floor area.
    converted = predicate_aware_numeric_value(predicate, value) if predicate else None
    if converted:
        m_val = re.search(r"value:([^,\]]+)", converted)
        m_unit = re.search(r"unit:([^,\]]+)", converted)
        val = m_val.group(1).strip('"') if m_val else _plain_text_key(value)
        unit = m_unit.group(1).strip('"').lower() if m_unit else ""
        try:
            dec = Decimal(str(val))
            # For elevation/length measurements, WebNLG references often round
            # nearby values.  This is only an equality key for repeated facts;
            # the chosen surface value still comes from one original triple.
            pred = _canonical_seq_predicate(predicate or "")
            if pred in {"elevationAboveSeaLevel", "elevationM"}:
                val = _decimal_text(dec, 0)
            else:
                val = _decimal_text(dec)
        except Exception:
            pass
        return ("numunit", f"{val}:{unit}")

    # Treat typed numeric RDF literals and bare numeric values identically.
    # This is crucial for sequence-only cleaning, e.g.
    #   "2777.0"^^xsd:double  vs  2777.0
    # which should not be realized twice.
    number = parse_number_value(value)
    if number:
        try:
            dec = Decimal(str(number.get("value")))
            pred = _canonical_seq_predicate(predicate or "")
            if pred in {"elevationAboveSeaLevel", "elevationM"}:
                val = _decimal_text(dec, 0)
            else:
                val = _decimal_text(dec)
            return ("num", val + ":" + str(number.get("unit", "")).lower())
        except Exception:
            return ("num", str(number.get("value", value)))

    lit = parse_rdf_literal(value)
    if lit:
        form = str(lit.get("form", ""))
        # Some RDF literals are strings around numbers even when the datatype
        # is not recognized by parse_number_value.  Normalize them as numbers
        # when possible, otherwise fall back to a textual literal key.
        try:
            dec = Decimal(form)
            pred = _canonical_seq_predicate(predicate or "")
            if pred in {"elevationAboveSeaLevel", "elevationM"}:
                form = _decimal_text(dec, 0)
            else:
                form = _decimal_text(dec)
            return ("num", form + ":")
        except Exception:
            return ("lit", _plain_text_key(form))
    return ("raw", _plain_text_key(value))


def _sequence_subject_key(value: str) -> tuple[str, str]:
    return _sequence_value_key(None, value)


def _sequence_preferred_object(a: str, b: str, predicate: str | None = None) -> str:
    """Choose a stable object spelling for merged sequence triples."""
    # Prefer plain values over typed/lang-tagged spellings; for numeric variants,
    # prefer the shorter surface unless predicate conversion supplies a unit.
    for x in (a, b):
        sx = str(x)
        if "^^" not in sx and "@" not in sx:
            return x
    return a


def _numeric_key_number(key: tuple[str, str]) -> Decimal | None:
    if key[0] not in {"num", "numunit"}:
        return None
    text = key[1].split(":", 1)[0]
    try:
        return Decimal(text)
    except Exception:
        return None


def _sequence_objects_equivalent(predicate: str, key1: tuple[str, str], key2: tuple[str, str]) -> bool:
    if key1 == key2:
        return True
    # Same canonical textual aliases after normalization.
    if key1[1] == key2[1] and key1[0] in {"raw", "lit"} and key2[0] in {"raw", "lit"}:
        return True
    pcanon = _canonical_seq_predicate(predicate)
    n1 = _numeric_key_number(key1)
    n2 = _numeric_key_number(key2)
    if n1 is not None and n2 is not None:
        # Only use loose numeric equivalence for predicates where WebNLG often
        # alternates rounded and precise spellings of the same measurement.
        loose = {
            "elevationAboveSeaLevel", "elevationM", "floorArea", "areaTotal", "areaLand",
            "areaWater", "populationDensity", "1st_runway_LengthFeet",
            "1st_runway_LengthMetre", "2nd_runway_LengthFeet",
            "2nd_runway_LengthMetre", "3rd_runway_LengthFeet",
            "3rd_runway_LengthMetre", "4th_runway_LengthFeet",
            "4th_runway_LengthMetre", "5th_runway_LengthFeet",
            "5th_runway_LengthMetre",
        }
        if pcanon in loose:
            return abs(n1 - n2) <= Decimal("0.5") or _decimal_text(n1, 0) == _decimal_text(n2, 0)
    return False


def _sequence_triples_equivalent(a: dict[str, str], b: dict[str, str]) -> bool:
    if _sequence_subject_key(a.get("subject", "")) != _sequence_subject_key(b.get("subject", "")):
        return False
    pa = _canonical_seq_predicate(a.get("predicate", ""))
    pb = _canonical_seq_predicate(b.get("predicate", ""))
    if pa != pb:
        return False
    ka = _sequence_value_key(a.get("predicate", ""), a.get("object", ""))
    kb = _sequence_value_key(b.get("predicate", ""), b.get("object", ""))
    return _sequence_objects_equivalent(pa, ka, kb)


def canonicalize_sequence_triples(triples: list[dict[str, str]]) -> list[dict[str, str]]:
    """Clean repeated or near-repeated WebNLG triples before realization.

    The filter is conservative but no longer purely hash-based: within one
    input, a new triple is removed if an earlier triple has the same normalized
    subject, the same canonical predicate, and an equivalent normalized object.
    This catches exact duplicates, predicate spelling aliases, common
    subject/object spelling variants, and rounded-vs-precise measurement
    duplicates before the facts reach Elvex.
    """
    cleaned: list[dict[str, str]] = []
    for t in triples:
        nt = dict(t)
        found = None
        for idx, prev in enumerate(cleaned):
            if _sequence_triples_equivalent(prev, nt):
                found = idx
                break
        if found is not None:
            prev = cleaned[found]
            # Prefer a canonical predicate spelling only when an alias has been
            # proven equivalent in the same input.  This makes later ID/CANON
            # matching easier without changing singleton predicate heads.
            prev["predicate"] = _canonical_seq_predicate(prev.get("predicate", ""))
            prev["object"] = _sequence_preferred_object(prev.get("object", ""), nt.get("object", ""), prev.get("predicate", ""))
            continue
        cleaned.append(nt)
    return cleaned


def _canon_atom(text: str, prefix: str = "C") -> str:
    return elvex_atom(text, prefix)

def read_patterns(path: Path) -> dict[str, str]:
    patterns: dict[str, str] = {}
    for candidate in [path / "predicate_overrides.tsv", path / "predicate_suggestions.tsv"]:
        if candidate.exists():
            with candidate.open(encoding="utf-8", newline="") as f:
                for row in csv.DictReader(f, delimiter="\t"):
                    if row.get("predicate") and row.get("pattern"):
                        patterns[row["predicate"]] = row["pattern"]
    return patterns


def read_frame_heads(user_dir: Path) -> set[str]:
    """Return predicate heads that have an explicit Elvex frame.

    Frames are detected directly from user/rules/frames.rules by looking for
    guards such as [HEAD:leader_Name, i:$I, ii:$II]. This keeps the mapping in
    Elvex rule files rather than in a separate TSV file.
    """
    frames_path = user_dir / "rules" / "frames.rules"
    if not frames_path.exists():
        return set()
    text = frames_path.read_text(encoding="utf-8")
    return set(re.findall(r"\[\s*HEAD\s*:\s*([A-Za-z_][A-Za-z0-9_]*)\s*,\s*i\s*:", text))


def _norm_literal_key(value: str) -> str:
    """Stable local identity key for a WebNLG subject/object value."""
    lit = parse_rdf_literal(value)
    if lit:
        return "lit:" + str(lit.get("form", "")).strip().lower()
    number = parse_number_value(value)
    if number:
        try:
            return "num:" + _decimal_text(Decimal(str(number.get("value")))) + ":" + str(number.get("unit", ""))
        except Exception:
            return "num:" + str(number.get("value", value)) + ":" + str(number.get("unit", ""))
    return "ent:" + str(value).strip().strip('"').lower()


def _add_features_to_fs(fs: str, ident: str | None = None, canon: str | None = None) -> str:
    extras = []
    if ident:
        extras.append(f"ID:{ident}")
    if canon:
        extras.append(f"CANON:{_canon_atom(canon)}")
    if extras and fs.startswith("[") and fs.endswith("]"):
        return fs[:-1] + ", " + ", ".join(extras) + "]"
    return fs


def _id_allocator():
    """Return a row-local allocator for typed IDs.

    IDs are intentionally local to one generated input.  They are used only by
    Elvex guards to detect co-reference inside a sequence.  Prefixes keep RDF
    entities/literals and predicates disjoint even if their surface strings
    happen to be identical.
    """
    counters = {"e": 0, "p": 0, "l": 0, "n": 0}
    table: dict[tuple[str, str], str] = {}

    def get(kind: str, key: str) -> str:
        k = (kind, key)
        if k not in table:
            counters[kind] += 1
            table[k] = f"{kind}{counters[kind]}"
        return table[k]

    return get


def fs_value(value: str, entity_prefix: str = "E", predicate: str | None = None,
             role: str = "arg", get_id=None) -> str:
    id_kind = "e"
    id_key = _norm_literal_key(value)
    if role == "object" and predicate:
        pred_num = predicate_aware_numeric_value(predicate, value)
        if pred_num:
            if get_id:
                return _add_features_to_fs(pred_num, get_id("n", id_key), "obj:" + _sequence_value_key(predicate, value)[1])
            return pred_num
    number = parse_number_value(value)
    if number:
        if "unit" in number:
            fs = f"[value:{quote_form(number['value'])}, unit:{quote_form(number['unit'])}, datatype:{number['datatype']}]"
        else:
            fs = f"[value:{quote_form(number['value'])}, datatype:{number['datatype']}]"
        if get_id:
            return _add_features_to_fs(fs, get_id("n", id_key), "obj:" + _sequence_value_key(predicate, value)[1])
        return fs
    raw = str(value).strip().strip('"')
    if DATE_LITERAL_RE.match(raw):
        fs = f"[FORM:{quote_form(raw)}, datatype:string]"
        if get_id:
            return _add_features_to_fs(fs, get_id("l", id_key), "obj:" + _sequence_value_key(predicate, value)[1])
        return fs
    lit = parse_rdf_literal(value)
    if lit:
        fs = f"[FORM:{quote_form(lit['form'])}, datatype:{lit['datatype']}]"
        if get_id:
            return _add_features_to_fs(fs, get_id("l", id_key), "obj:" + _sequence_value_key(predicate, value)[1])
        return fs
    fs = f"[HEAD:{elvex_atom(value, entity_prefix)}]"
    if get_id:
        return _add_features_to_fs(fs, get_id(id_kind, id_key), "obj:" + _sequence_value_key(predicate, value)[1])
    return fs


def _generation_predicate_head(predicate: str, frame_heads: set[str] | None = None) -> str:
    """Predicate HEAD used for Elvex generation.

    WebNLG contains many spelling variants (camelCase, underscores, upper-case
    components, and legacy aliases).  The original triple is kept in comments
    and reports, but the generated Elvex input may use the canonical HEAD when
    that HEAD is implemented as a frame.  This keeps lexical coverage in one
    place instead of duplicating identical rules for every spelling variant.
    """
    original = elvex_atom(predicate, "P")
    canon = elvex_atom(_canonical_seq_predicate(predicate), "P")
    if frame_heads and canon in frame_heads:
        return canon
    return original


def fs_for_triple(t: dict[str, str], pattern: str, get_id=None, frame_heads: set[str] | None = None) -> str:
    s = fs_value(t["subject"], "E", t["predicate"], "subject", get_id=get_id)
    p_head = _generation_predicate_head(t["predicate"], frame_heads)
    p_id = f", ID:{get_id('p', 'pred:' + p_head)}" if get_id else ""
    p_canon = f", CANON:{_canon_atom('pred:' + _canonical_seq_predicate(t['predicate']))}"
    p = f"[HEAD:{p_head}{p_id}{p_canon}]"
    o = fs_value(t["object"], "E", t["predicate"], "object", get_id=get_id)
    return f"[pattern:{pattern}, s:{s}, p:{p}, o:{o}]"


def fs_for_row(row: dict[str, Any], patterns: dict[str, str], frame_heads: set[str]) -> str:
    raw_triples = row.get("triples", [])
    triples = canonicalize_sequence_triples(raw_triples) if len(raw_triples) > 1 else list(raw_triples)
    get_id = _id_allocator()
    if len(triples) == 1:
        t = triples[0]
        pred_head = _generation_predicate_head(t["predicate"], frame_heads)
        if pred_head in frame_heads:
            return f"S [HEAD:webnlg_simple, {fs_for_triple(t, 'frame', get_id=get_id, frame_heads=frame_heads)[1:]}"
        pattern = patterns.get(t["predicate"], "svo")
        return f"S [HEAD:webnlg_simple, {fs_for_triple(t, pattern, get_id=get_id, frame_heads=frame_heads)[1:]}"
    triple_fss = []
    for t in triples:
        pred_head = _generation_predicate_head(t["predicate"], frame_heads)
        pattern = "frame" if pred_head in frame_heads else patterns.get(t["predicate"], "svo")
        triple_fss.append(fs_for_triple(t, pattern, get_id=get_id, frame_heads=frame_heads))
    arg_names = ["i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix", "x"]
    if len(triple_fss) > len(arg_names):
        raise ValueError(f"webnlg_sequence supports at most {len(arg_names)} triples, got {len(triple_fss)}")
    args_parts = [f"{name}:{fs}" for name, fs in zip(arg_names, triple_fss)]
    args = ", ".join(args_parts)
    return f"S [HEAD:webnlg_sequence, size:{len(triples)}, {args}]"


def build_atomic_sequence(triples_file: Path, seq_file: Path) -> int:
    rows: list[dict[str, Any]] = []
    seen: set[tuple[str, str, str]] = set()
    for row in read_jsonl(triples_file):
        for idx, triple in enumerate(row.get("triples", []), start=1):
            key = (triple.get("subject", ""), triple.get("predicate", ""), triple.get("object", ""))
            if key in seen:
                continue
            seen.add(key)
            rows.append({
                "id": f"{row.get('id', 'entry')}#t{idx}",
                "source_entry_id": row.get("id"),
                "source_file": row.get("source_file"),
                "category": row.get("category"),
                "split": row.get("split"),
                "size": 1,
                "triples": [triple],
                "lexicalizations": row.get("lexicalizations", []),
            })
    return write_jsonl(seq_file, rows)


def safe_test_name(raw_id: str, ordinal: int) -> str:
    raw = re.sub(r"[^A-Za-z0-9_.-]+", "_", raw_id or "entry").strip("._-")
    if not raw:
        raw = "entry"
    return f"{ordinal:06d}_{raw[:80]}.input"


def input_text_for_row(row: dict[str, Any], patterns: dict[str, str], frame_heads: set[str]) -> str:
    triples = row.get("triples", [])
    comments = ["// " + " | ".join([t.get("subject", ""), t.get("predicate", ""), t.get("object", "")]) for t in triples]
    return "\n".join(comments) + "\n" + fs_for_row(row, patterns, frame_heads) + "\n"


def default_names(size: int) -> tuple[Path, Path, Path, Path]:
    if size == 1:
        out_dir = ROOT / "build/inputs/simple_triples"
        index = ROOT / "build/inputs/simple_triples.index.tsv"
        combined = ROOT / "build/inputs/simple_triples.input"
    else:
        out_dir = ROOT / f"build/inputs/{size}_triples"
        index = ROOT / f"build/inputs/{size}_triples.index.tsv"
        combined = ROOT / f"build/inputs/{size}_triples.input"
    seq = ROOT / f"build/sequences/{size}.jsonl"
    return seq, out_dir, index, combined


def main() -> int:
    ap = argparse.ArgumentParser(description="Generate one Elvex .input file per WebNLG entry of a given triple count")
    ap.add_argument("size", nargs="?", type=int, default=1, help="Number of triples per WebNLG entry. Default: 1")
    ap.add_argument("--seq", default=None, help="Source JSONL. Default: build/sequences/<size>.jsonl")
    ap.add_argument("--triples", default=str(ROOT / "data/processed/triples.jsonl"), help="Fallback used to create size=1 if missing")
    ap.add_argument("--lexicon-dir", default=str(ROOT / "user/lexicon"))
    ap.add_argument("--user-dir", default=str(ROOT / "user"))
    ap.add_argument("--out-dir", default=None, help="Directory receiving one .input file per WebNLG entry")
    ap.add_argument("--index", default=None, help="TSV index receiving metadata and WebNLG references")
    ap.add_argument("--combined-out", default=None, help="Optional diagnostic concatenation; not used by elvex")
    ap.add_argument("--main-input", default=str(ROOT / "user/main.input"), help="Current sample input copied from the first generated test")
    ap.add_argument("--limit", type=int, default=0, help="Maximum number of tests to generate. 0 means all.")
    ap.add_argument("--clean", action=argparse.BooleanOptionalAction, default=True, help="Clean the output directory before writing tests")
    ap.add_argument("--copy-first-to-user", action=argparse.BooleanOptionalAction, default=True, help="Copy first generated test to user/main.input")
    args = ap.parse_args()

    if args.size < 1:
        raise SystemExit("size must be >= 1")

    default_seq, default_out_dir, default_index, default_combined = default_names(args.size)
    seq = Path(args.seq) if args.seq else default_seq
    out_dir = Path(args.out_dir) if args.out_dir else default_out_dir
    index_path = Path(args.index) if args.index else default_index
    combined_path = Path(args.combined_out) if args.combined_out else default_combined

    if not seq.exists():
        if args.size == 1:
            triples = Path(args.triples)
            if not triples.exists():
                raise SystemExit(f"Not found: {seq}. Run ./run extract and then ./run select.")
            n = build_atomic_sequence(triples, seq)
            print(f"{seq} missing; atomic view created from {triples}: {n} triple(s)")
        else:
            raise SystemExit(f"Not found: {seq}. Run ./run select first, or choose an available size from build/sequences/.")

    patterns = read_patterns(Path(args.lexicon_dir))
    frame_heads = read_frame_heads(Path(args.user_dir))
    if args.clean and out_dir.exists():
        shutil.rmtree(out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    index_path.parent.mkdir(parents=True, exist_ok=True)
    combined_path.parent.mkdir(parents=True, exist_ok=True)

    count = 0
    first_file: Path | None = None
    combined_parts: list[str] = []

    with index_path.open("w", encoding="utf-8", newline="") as index:
        fields = ["ordinal", "input_file", "entry_id", "source_entry_id", "source_file", "split", "category", "n_triples", "triples_json", "references_json"]
        index.write("\t".join(fields) + "\n")
        for row in read_jsonl(seq):
            triples = row.get("triples", [])
            if len(triples) != args.size:
                continue
            text = input_text_for_row(row, patterns, frame_heads)
            count += 1
            path = out_dir / safe_test_name(str(row.get("id", "entry")), count)
            path.write_text(text, encoding="utf-8")
            if first_file is None:
                first_file = path
            combined_parts.append(text)
            vals = [
                str(count),
                str(path.relative_to(ROOT)),
                str(row.get("id", "")),
                str(row.get("source_entry_id", "")),
                str(row.get("source_file", "")),
                str(row.get("split", "")),
                str(row.get("category", "")),
                str(len(triples)),
                json.dumps(triples, ensure_ascii=False, separators=(",", ":")),
                json.dumps(row.get("lexicalizations", []), ensure_ascii=False, separators=(",", ":")),
            ]
            index.write("\t".join(v.replace("\n", " ").replace("\t", " ") for v in vals) + "\n")
            if args.limit and count >= args.limit:
                break

    combined_path.write_text("\n".join(combined_parts), encoding="utf-8")
    main_input = Path(args.main_input)
    if args.copy_first_to_user:
        if first_file:
            main_input.write_text(first_file.read_text(encoding="utf-8"), encoding="utf-8")
            print(f"First test copied to {main_input}")
        else:
            main_input.write_text("", encoding="utf-8")
            print(f"No test generated; {main_input} cleared")

    if frame_heads:
        print(f"Explicit predicate frames found: {len(frame_heads)}")
    print(f"{count} input test file(s) with {args.size} triple(s) written to {out_dir}")
    print(f"Index written to {index_path}")
    print(f"Diagnostic concatenation written to {combined_path}; do not pass it to elvex directly")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
