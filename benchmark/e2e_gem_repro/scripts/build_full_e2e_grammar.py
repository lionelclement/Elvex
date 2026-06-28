#!/usr/bin/env python3
from __future__ import annotations

import argparse
import itertools
import json
import re
from pathlib import Path
from typing import Any

SLOT_ORDER = ["eatType", "food", "priceRange", "area", "near", "familyFriendly", "customerRating"]
VAR_FOR_SLOT = {
    "eatType": "EatType",
    "food": "Food",
    "priceRange": "Price",
    "area": "Area",
    "near": "Near",
    "familyFriendly": "Family",
    "customerRating": "Rating",
}
NT_FOR_SLOT = {
    "eatType": "EATTYPE_CLAUSE",
    "food": "FOOD_CLAUSE",
    "priceRange": "PRICE_CLAUSE",
    "area": "AREA_CLAUSE",
    "near": "NEAR_CLAUSE",
    "familyFriendly": "FAMILY_CLAUSE",
    "customerRating": "RATING_CLAUSE",
}
VALUE_CAT_FOR_SLOT = {
    "eatType": "eat_type_value",
    "food": "food_value",
    "priceRange": "price_value",
    "area": "area_value",
    "near": "near_value",
    "familyFriendly": "family_value",
    "customerRating": "rating_value",
}

def q(s: Any) -> str:
    return '"' + str(s).replace("\\", "\\\\").replace('"', '\\"') + '"'

def clean_value(s: Any) -> str:
    s = str(s).replace("_", " ").strip()
    s = re.sub(r"\s+", " ", s)
    if len(s) >= 2 and ((s[0] == s[-1] == '"') or (s[0] == s[-1] == "'")):
        s = s[1:-1].strip()
    return s

def value_surface(slot: str, value: Any) -> str:
    v = clean_value(value)
    vl = v.lower()

    if slot == "eatType":
        if vl in {"pub", "restaurant"}:
            return "a " + vl
        if vl == "coffee shop":
            return "a coffee shop"
        return v

    if slot == "food":
        if vl.endswith("food"):
            return v
        return f"{v} food"

    if slot == "priceRange":
        if vl == "cheap":
            return "cheap"
        if vl == "moderate":
            return "moderately priced"
        if vl == "high":
            return "high priced"
        return v

    if slot == "area":
        if vl in {"city centre", "city center"}:
            return "in the city centre"
        if vl == "riverside":
            return "by the riverside"
        return "in " + v

    if slot == "near":
        return "near " + v

    if slot == "familyFriendly":
        if vl in {"yes", "true", "1"}:
            return "family-friendly"
        if vl in {"no", "false", "0"}:
            return "not family-friendly"
        return v

    if slot == "customerRating":
        if vl == "high":
            return "a high customer rating"
        if vl == "average":
            return "an average customer rating"
        if vl == "low":
            return "a low customer rating"
        return f"a customer rating of {v}"

    return v

def read_items(path: Path):
    with path.open(encoding="utf-8") as f:
        for line in f:
            if line.strip():
                yield json.loads(line)

def write_rules(path: Path) -> None:
    lines: list[str] = [
"/************************************************************",
"* Full E2E-style grammar.",
"* This grammar realizes a closed-domain restaurant MR as a subject followed",
"* by slot-specific clauses.  It is intentionally simple, but it is no longer",
"* a generic slot-marker/value verbalizer.",
"************************************************************/",
"",
"@withoutSpaces",
"Axiom → RestaurantDescription {",
"  ↓1 = ↑;",
"  ⇑ = ⇓1;",
"}",
"",
]

    all_slots = SLOT_ORDER
    for has_name in [True, False]:
        for r in range(0, len(all_slots) + 1):
            for subset in itertools.combinations(all_slots, r):
                if not has_name and not subset:
                    continue
                rhs = ["SUBJECT"]
                for i, slot in enumerate(subset):
                    if i > 0:
                        rhs.append("COORD")
                    rhs.append(NT_FOR_SLOT[slot])

                lines += ["", f"/*** {'name' if has_name else 'generic subject'} + {','.join(subset) or 'no slot'} ***/"]
                lines.append("RestaurantDescription → " + " ".join(rhs) + " {")
                lines.append("  [HEAD:DESCRIBE_RESTAURANT,")
                feat_lines = []
                if has_name:
                    feat_lines.append("   name:$Name")
                for slot in subset:
                    feat_lines.append(f"   {slot}:${VAR_FOR_SLOT[slot]}")
                for i, fl in enumerate(feat_lines):
                    comma = "," if i < len(feat_lines)-1 else ""
                    lines.append(fl + comma)
                lines.append("  ];")
                lines.append("")
                if has_name:
                    lines.append("  ↓1 = [name:$Name];")
                else:
                    lines.append("  ↓1 = [];")
                pos = 2
                for i, slot in enumerate(subset):
                    if i > 0:
                        lines.append(f"  ↓{pos} = [];")
                        pos += 1
                    lines.append(f"  ↓{pos} = [{slot}:${VAR_FOR_SLOT[slot]}];")
                    pos += 1
                lines.append("")
                lines.append("  ⇑ = ↑;")
                lines.append("}")

    lines += [
"",
"/************************************************************",
"* Slot-specific clauses",
"************************************************************/",
"",
"SUBJECT → name { ↓1 = ↑; ⇑ = ⇓1; }",
"SUBJECT → generic_subject { ↓1 = ↑; ⇑ = ⇓1; }",
"",
"EATTYPE_CLAUSE → copula EATTYPE_VALUE {",
"  [eatType:$Value];",
"  ↓1 = [];",
"  ↓2 = [eatType:$Value];",
"  ⇑ = ↑;",
"}",
"",
"FOOD_CLAUSE → serve_marker FOOD_VALUE {",
"  [food:$Value];",
"  ↓1 = [];",
"  ↓2 = [food:$Value];",
"  ⇑ = ↑;",
"}",
"",
"PRICE_CLAUSE → copula PRICE_VALUE {",
"  [priceRange:$Value];",
"  ↓1 = [];",
"  ↓2 = [priceRange:$Value];",
"  ⇑ = ↑;",
"}",
"",
"AREA_CLAUSE → copula AREA_VALUE {",
"  [area:$Value];",
"  ↓1 = [];",
"  ↓2 = [area:$Value];",
"  ⇑ = ↑;",
"}",
"",
"NEAR_CLAUSE → NEAR_VALUE {",
"  [near:$Value];",
"  ↓1 = [near:$Value];",
"  ⇑ = ↑;",
"}",
"",
"FAMILY_CLAUSE → copula FAMILY_VALUE {",
"  [familyFriendly:$Value];",
"  ↓1 = [];",
"  ↓2 = [familyFriendly:$Value];",
"  ⇑ = ↑;",
"}",
"",
"RATING_CLAUSE → have_marker RATING_VALUE {",
"  [customerRating:$Value];",
"  ↓1 = [];",
"  ↓2 = [customerRating:$Value];",
"  ⇑ = ↑;",
"}",
"",
"EATTYPE_VALUE → eat_type_value { ↓1 = ↑; ⇑ = ⇓1; }",
"FOOD_VALUE → food_value { ↓1 = ↑; ⇑ = ⇓1; }",
"PRICE_VALUE → price_value { ↓1 = ↑; ⇑ = ⇓1; }",
"AREA_VALUE → area_value { ↓1 = ↑; ⇑ = ⇓1; }",
"NEAR_VALUE → near_value { ↓1 = ↑; ⇑ = ⇓1; }",
"FAMILY_VALUE → family_value { ↓1 = ↑; ⇑ = ⇓1; }",
"RATING_VALUE → rating_value { ↓1 = ↑; ⇑ = ⇓1; }",
"COORD → coord { ↓1 = ↑; ⇑ = ⇓1; }",
]
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--items", required=True)
    ap.add_argument("--lexicon-out", default="grammar/e2e/e2e_full.lexicon")
    ap.add_argument("--rules-out", default="grammar/e2e/e2e_full.rules")
    args = ap.parse_args()

    names = set()
    values: dict[str, set[str]] = {s: set() for s in SLOT_ORDER}
    no_name = 0

    for row in read_items(Path(args.items)):
        slots = row["expected_slots"]
        if "name" in slots:
            names.add(clean_value(slots["name"]))
        else:
            no_name += 1
        for slot in SLOT_ORDER:
            if slot in slots:
                values[slot].add(clean_value(slots[slot]))

    lex: list[str] = [
"/************************************************************",
"* Full E2E lexicon generated from the selected E2E split.",
"* Restaurant and near-place names are treated as domain constants.",
"************************************************************/",
"",
"FORM form;",
"",
"/*** Subject forms ***/",
'"The restaurant" generic_subject [];',
]
    for n in sorted(names):
        lex.append(f"{q(n)} name [name:{q(n)}];")

    lex += [
"",
"/*** Clause markers ***/",
'"is" copula [];',
'"serves" serve_marker [];',
'"has" have_marker [];',
'"and" coord [];',
"",
"/*** Slot values ***/",
]
    for slot in SLOT_ORDER:
        cat = VALUE_CAT_FOR_SLOT[slot]
        if values[slot]:
            lex.append(f"/** {slot} **/")
            for v in sorted(values[slot]):
                lex.append(f"{q(value_surface(slot, v))} {cat} [{slot}:{q(v)}];")
            lex.append("")

    Path(args.lexicon_out).parent.mkdir(parents=True, exist_ok=True)
    Path(args.lexicon_out).write_text("\n".join(lex) + "\n", encoding="utf-8")
    Path(args.rules_out).parent.mkdir(parents=True, exist_ok=True)
    write_rules(Path(args.rules_out))

    print(json.dumps({
        "names": len(names),
        "no_name_items": no_name,
        "slot_values": {s: len(values[s]) for s in SLOT_ORDER},
        "rule_combinations": 2 ** len(SLOT_ORDER) * 2 - 1,
        "lexicon_out": args.lexicon_out,
        "rules_out": args.rules_out,
    }, indent=2, ensure_ascii=False))

if __name__ == "__main__":
    main()
