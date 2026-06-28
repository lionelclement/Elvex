from __future__ import annotations

import json
import re
from decimal import Decimal, InvalidOperation
from pathlib import Path
from typing import Any, Iterable

CAMEL_RE = re.compile(r"(?<=[a-z0-9])(?=[A-Z])")
BAD_ID_RE = re.compile(r"[^A-Za-z0-9_]+")
DET_RE = re.compile(r"\b(the|a|an|this|that|these|those|some|any|no|each|every|all|many|few|several)\b", re.I)

def repo_root() -> Path:
    return Path(__file__).resolve().parents[1]

def read_jsonl(path: Path) -> Iterable[dict[str, Any]]:
    with path.open(encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if line:
                yield json.loads(line)

def write_jsonl(path: Path, rows: Iterable[dict[str, Any]]) -> int:
    path.parent.mkdir(parents=True, exist_ok=True)
    n = 0
    with path.open("w", encoding="utf-8") as f:
        for row in rows:
            f.write(json.dumps(row, ensure_ascii=False, sort_keys=True) + "\n")
            n += 1
    return n

def strip_uri(value: str) -> str:
    value = str(value).strip()
    if value.startswith("<") and value.endswith(">"):
        value = value[1:-1]
    if "/" in value or "#" in value:
        value = re.split(r"[/#]", value)[-1]
    return value

def label_from_rdf(value: str) -> str:
    value = strip_uri(value)
    value = value.replace("_", " ").replace("-", " ")
    value = CAMEL_RE.sub(" ", value)
    value = re.sub(r"\s+", " ", value).strip()
    return value or str(value)

ELVEX_RESERVED = {
    "attest", "deferred", "else", "if", "order",
    "print", "println", "eprint", "eprintln",
    "NIL", "FORM", "HEAD", "LEMMA",
    "true", "false",
}

def elvex_atom(value: str, prefix: str = "x") -> str:
    raw = strip_uri(value)
    raw = CAMEL_RE.sub("_", raw).replace("-", "_").replace(" ", "_")
    raw = BAD_ID_RE.sub("_", raw)
    raw = re.sub(r"_+", "_", raw).strip("_")
    if not raw:
        raw = prefix
    if raw[0].isdigit() or raw in ELVEX_RESERVED:
        raw = f"{prefix}_{raw}"
    return raw


def elvex_lemma(value: str, prefix: str = "_") -> str:
    """Return a safe Elvex lemma identifier.

    Lemmas are always uppercase and start with an underscore, for example
    ``order`` becomes ``_ORDER``. This avoids collisions with Elvex keywords.
    """
    atom = elvex_atom(value, "X")
    atom = atom.upper()
    atom = atom.lstrip("_")
    if not atom:
        atom = "X"
    return f"{prefix}{atom}"

def quote_form(value: str) -> str:
    return '"' + value.replace("\\", "\\\\").replace('"', '\\"') + '"'

def split_predicate(predicate: str) -> list[str]:
    lab = label_from_rdf(predicate)
    return [w.lower() for w in re.findall(r"[A-Za-z0-9]+", lab)]

def parse_triple_text(text: str) -> tuple[str, str, str] | None:
    text = re.sub(r"\s+", " ", str(text)).strip()
    if " | " in text:
        parts = [p.strip() for p in text.split(" | ")]
    elif "|" in text:
        parts = [p.strip() for p in text.split("|")]
    else:
        parts = re.split(r"\s*<SEP>\s*", text)
    if len(parts) == 3:
        return parts[0], parts[1], parts[2]
    return None

def find_determiners(texts: Iterable[str]) -> set[str]:
    out: set[str] = set()
    for text in texts:
        out.update(m.group(1).lower() for m in DET_RE.finditer(text or ""))
    return out

def predicate_guess(predicate: str) -> dict[str, str]:
    words = split_predicate(predicate)
    if not words:
        words = [elvex_atom(predicate)]
    joined = " ".join(words)
    pred_atom = elvex_atom(predicate, "p")
    if words[-1:] in (["place"], ["location"], ["country"], ["city"]):
        return {"predicate": predicate, "pattern": "svo", "lexeme": f"be_{pred_atom}", "form": "is in", "prep": ""}
    if "birth" in words and ("place" in words or "date" in words):
        form = "was born in" if "place" in words else "was born on"
        return {"predicate": predicate, "pattern": "svo", "lexeme": "be_born", "form": form, "prep": ""}
    if words[-1:] == ["type"] or words[-1:] == ["genre"] or words[-1:] == ["class"]:
        return {"predicate": predicate, "pattern": "cop_nom", "lexeme": pred_atom, "form": joined, "prep": ""}
    if words[-1:] in (["name"], ["title"]):
        return {"predicate": predicate, "pattern": "cop_nom", "lexeme": pred_atom, "form": joined, "prep": ""}
    if words[0] in {"is", "was", "are"} and len(words) > 1:
        return {"predicate": predicate, "pattern": "cop_adj", "lexeme": pred_atom, "form": " ".join(words[1:]), "prep": ""}
    return {"predicate": predicate, "pattern": "svo", "lexeme": pred_atom, "form": joined, "prep": ""}

RDF_TYPED_LITERAL_RE = re.compile(r'^"((?:[^"\\]|\\.)*)"\^\^(?:<([^>]+)>|([A-Za-z_][A-Za-z0-9_:-]*))$')
RDF_LANG_LITERAL_RE = re.compile(r'^"((?:[^"\\]|\\.)*)"@[A-Za-z-]+$')
RDF_PLAIN_LITERAL_RE = re.compile(r'^"((?:[^"\\]|\\.)*)"$')

def _unescape_rdf_string(value: str) -> str:
    return bytes(value, "utf-8").decode("unicode_escape")

def parse_rdf_literal(value: str) -> dict[str, str] | None:
    """Parse common RDF literal notations used in WebNLG.

    Examples:
      "2777.0"^^xsd:double -> {"form":"2777.0", "datatype":"xsd_double"}
      "A string"@en        -> {"form":"A string", "lang":"en"} is simplified
                                to a literal form for generation.
    """
    raw = str(value).strip()
    m = RDF_TYPED_LITERAL_RE.match(raw)
    if m:
        dtype_raw = m.group(2) or m.group(3) or "literal"
        dtype = elvex_atom(dtype_raw.replace(":", "_"), "dtype")
        return {"form": _unescape_rdf_string(m.group(1)), "datatype": dtype, "datatype_raw": dtype_raw}
    m = RDF_LANG_LITERAL_RE.match(raw)
    if m:
        return {"form": _unescape_rdf_string(m.group(1)), "datatype": "string"}
    m = RDF_PLAIN_LITERAL_RE.match(raw)
    if m:
        return {"form": _unescape_rdf_string(m.group(1)), "datatype": "string"}
    return None

def is_rdf_literal(value: str) -> bool:
    return parse_rdf_literal(value) is not None

RAW_NUMBER_RE = re.compile(r"^[+-]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?$")
# Numeric expressions seen in WebNLG entity/object fields, for example:
#   1.2 (litres)
#   "100305.0"(minutes)
#   3.8 m
#   1513.722 (days)
#   -4.5 km
# These must not be compacted as proper_noun entries.  We deliberately do
# not treat every "NUMBER Word" as a measurement, because WebNLG also has
# proper names such as "1089 Tama", "3 Arena", and "1. FC Köln".
_NUMBER_TOKEN = r'"?([+-]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?)"?'
NUMBER_WITH_PAREN_UNIT_RE = re.compile(rf"^\s*{_NUMBER_TOKEN}\s*\(([^()]+)\)\s*$")
NUMBER_WITH_UNIT_RE = re.compile(rf"^\s*{_NUMBER_TOKEN}\s+(.+?)\s*$")

KNOWN_MEASURE_UNITS = {
    # length / distance
    "m", "metre", "metres", "meter", "meters",
    "mm", "millimetre", "millimetres", "millimeter", "millimeters",
    "cm", "centimetre", "centimetres", "centimeter", "centimeters",
    "km", "kilometre", "kilometres", "kilometer", "kilometers",
    "inch", "inches",
    # area / volume
    "square metre", "square metres", "square meter", "square meters",
    "square kilometre", "square kilometres", "square kilometer", "square kilometers",
    "cubic centimetre", "cubic centimetres", "cubic centimeter", "cubic centimeters",
    "cubic inch", "cubic inches",
    "litre", "litres", "liter", "liters", "l", "ml",
    # mass / density
    "g", "gram", "grams", "kg", "kilogram", "kilograms",
    "tonne", "tonnes", "ton", "tons",
    "gram per cubic centimetre", "gram per cubic centimetres",
    "gram per cubic centimeter", "gram per cubic centimeters",
    "kilogram per cubic metre", "kilogram per cubic metres",
    "kilogram per cubic meter", "kilogram per cubic meters",
    # time / temperature / speed / population density
    "day", "days", "minute", "minutes", "second", "seconds",
    "kelvin", "kelvins", "degree celsius", "degrees celsius",
    "kilometre per second", "kilometre per seconds",
    "kilometer per second", "kilometer per seconds",
    "inhabitants per square kilometre", "inhabitants per square kilometer",
    "dollar", "dollars", "euro", "euros",
    "kilometre per hour", "kilometre per hours", "kilometer per hour", "kilometer per hours",
}

# Units that are safely usable as bare compact symbols after a number.  This
# prevents "1089 Tama" or "3 Arena" from being treated as measurements.
KNOWN_SYMBOL_UNITS = {"m", "g", "kg", "km", "mm", "cm", "l", "ml", "s", "ms", "h", "%"}

def is_measure_unit(unit: str) -> bool:
    u = _clean_unit(unit)
    ul = u.lower()
    ul = re.sub(r"\s+", " ", ul)
    return ul in KNOWN_MEASURE_UNITS or u in KNOWN_SYMBOL_UNITS

def is_raw_number(value: str) -> bool:
    return RAW_NUMBER_RE.match(str(value).strip().strip('"')) is not None

def _clean_unit(unit: str) -> str:
    unit = str(unit).strip().strip('"')
    unit = re.sub(r"\s+", " ", unit)
    return unit


DBPEDIA_DATATYPE_UNITS = {
    "usDollar": "dollars",
    "euro": "euros",
    "squareMetre": "square metres",
    "squareMeter": "square meters",
    "squareKilometre": "square kilometres",
    "squareKilometer": "square kilometers",
    "kilometre": "kilometres",
    "kilometer": "kilometers",
    "metre": "metres",
    "meter": "meters",
    "centimetre": "centimetres",
    "centimeter": "centimeters",
    "millimetre": "millimetres",
    "millimeter": "millimeters",
    "kilogram": "kilograms",
    "gram": "grams",
    "kelvin": "kelvins",
    "day": "days",
    "second": "seconds",
    "minute": "minutes",
    "kilometrePerSecond": "kilometres per second",
    "kilometerPerSecond": "kilometers per second",
    "kilometrePerHour": "kilometres per hour",
    "kilometerPerHour": "kilometers per hour",
    "inhabitantsPerSquareKilometre": "inhabitants per square kilometre",
    "inhabitantsPerSquareKilometer": "inhabitants per square kilometer",
}

def dbpedia_unit_from_datatype(dtype_raw: str | None) -> str | None:
    if not dtype_raw:
        return None
    tail = strip_uri(dtype_raw)
    return DBPEDIA_DATATYPE_UNITS.get(tail)

def normalize_number_for_unit(value: str, unit: str | None) -> str:
    """Normalize a small set of DBpedia numeric surfaces for generation."""
    text = str(value).strip().strip('"')
    if unit in {"dollars", "euros"}:
        try:
            dec = Decimal(text)
            million = Decimal("1000000")
            if dec == dec.to_integral_value() and dec % million == 0:
                n = int(dec / million)
                return f"{n} million"
            if dec == dec.to_integral_value():
                return str(int(dec))
        except InvalidOperation:
            pass
    return text

def parse_number_value(value: str) -> dict[str, str] | None:
    """Return an Elvex-ready numeric value.

    Numeric values are dynamic lexical forms, not compacted proper nouns.
    Supported inputs include RDF typed literals, raw numbers, and numbers
    followed by a recognized measurement unit either bare or parenthesized.

    Examples:
      "2777.0"^^xsd:double -> {"value":"2777.0", "datatype":"xsd_double"}
      2777.0                -> {"value":"2777.0", "datatype":"number"}
      3.8 m                 -> {"value":"3.8", "unit":"m", "datatype":"number_unit"}
      1.2 (litres)          -> {"value":"1.2", "unit":"litres", "datatype":"number_unit"}
      "100305.0"(minutes)  -> {"value":"100305.0", "unit":"minutes", "datatype":"number_unit"}
    """
    lit = parse_rdf_literal(value)
    if lit:
        unit = dbpedia_unit_from_datatype(lit.get("datatype_raw"))
        if unit and is_raw_number(lit.get("form", "")):
            return {"value": normalize_number_for_unit(lit["form"], unit), "unit": unit, "datatype": "number_unit"}
        if lit.get("datatype") in {"xsd_double", "xsd_decimal", "xsd_float", "xsd_integer", "integer", "double", "decimal", "float"}:
            return {"value": lit["form"], "datatype": lit["datatype"]}
    raw = str(value).strip()
    if is_raw_number(raw):
        return {"value": raw.strip('"'), "datatype": "number"}
    m = NUMBER_WITH_PAREN_UNIT_RE.match(raw)
    if m:
        unit = _clean_unit(m.group(2))
        if is_measure_unit(unit):
            return {"value": m.group(1), "unit": unit, "datatype": "number_unit"}
    m = NUMBER_WITH_UNIT_RE.match(raw)
    if m:
        unit = _clean_unit(m.group(2))
        if is_measure_unit(unit):
            return {"value": m.group(1), "unit": unit, "datatype": "number_unit"}
    return None

def is_number_expression(value: str) -> bool:
    return parse_number_value(value) is not None

def iter_text_values(obj: Any) -> Iterable[str]:
    if isinstance(obj, str):
        yield obj
    elif isinstance(obj, list):
        for x in obj:
            yield from iter_text_values(x)
    elif isinstance(obj, dict):
        for k, v in obj.items():
            if k.lower() in {"lex", "text", "template", "comment", "value", "original", "modifiedtripleset", "otriple", "mtriple"}:
                yield from iter_text_values(v)
            elif isinstance(v, (dict, list)):
                yield from iter_text_values(v)
