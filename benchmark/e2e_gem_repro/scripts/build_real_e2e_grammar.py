#!/usr/bin/env python3
from __future__ import annotations
import argparse, json, re
from pathlib import Path

SLOT_ORDER = ["eatType", "food", "priceRange", "area", "familyFriendly", "near", "customerRating"]
SLOT_MARKER_FORMS = {
    "eatType": "is a",
    "food": "serves",
    "priceRange": "has price range",
    "area": "is in",
    "familyFriendly": "is",
    "near": "is near",
    "customerRating": "has customer rating",
}
def q(s):
    return '"' + str(s).replace("\\", "\\\\").replace('"', '\\"') + '"'
def value_surface(slot, value):
    if slot == "familyFriendly":
        vl = str(value).lower()
        if vl in {"yes", "true", "1"}:
            return "family-friendly"
        if vl in {"no", "false", "0"}:
            return "not family-friendly"
    return str(value)

def read_items(path: Path):
    with path.open(encoding="utf-8") as f:
        for line in f:
            if line.strip():
                yield json.loads(line)

def write_rules(path: Path, max_non_name_slots: int) -> None:
    lines = [
"/************************************************************",
"* Auto-generated factorized E2E rules for real supported items.",
"************************************************************/",
"",
"@withoutSpaces",
"Axiom → RestaurantDescription {",
"  ↓1 = ↑;",
"  ⇑ = ⇓1;",
"}",
"",
]
    for k in range(1, max_non_name_slots + 1):
        rhs = ["NAME"]
        for i in range(k):
            if i > 0:
                rhs.append("COORD")
            rhs.append("SLOTREAL")
        lines += [
"",
f"/*** name + {k} slot(s) ***/",
"RestaurantDescription → " + " ".join(rhs) + " {",
"  [HEAD:DESCRIBE_RESTAURANT,",
"   name:$name,"
]
        for i in range(1, k + 1):
            comma = "," if i < k else ""
            lines.append(f"   slot{i}:$S{i}{comma}")
        lines += ["  ];", "", "  ↓1 = [name:$name];"]
        pos = 2
        for i in range(1, k + 1):
            if i > 1:
                lines.append(f"  ↓{pos} = [];")
                pos += 1
            lines.append(f"  ↓{pos} = $S{i};")
            pos += 1
        lines += ["", "  ⇑ = ↑;", "}"]
    lines += [
"",
"SLOTREAL → SLOT_MARKER SLOT_VALUE {",
"  [slot:$Slot, value:$Value];",
"  ↓1 = [slot:$Slot];",
"  ↓2 = [slot:$Slot, value:$Value];",
"  ⇑ = ↑;",
"}",
"",
"NAME → name { ↓1 = ↑; ⇑ = ⇓1; }",
"SLOT_MARKER → slot_marker { ↓1 = ↑; ⇑ = ⇓1; }",
"SLOT_VALUE → slot_value { ↓1 = ↑; ⇑ = ⇓1; }",
"COORD → coord { ↓1 = ↑; ⇑ = ⇓1; }",
]
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--items", required=True)
    ap.add_argument("--lexicon-out", default="grammar/e2e/e2e.lexicon")
    ap.add_argument("--rules-out", default="grammar/e2e/e2e.rules")
    ap.add_argument("--max-non-name-slots", type=int, default=8)
    args = ap.parse_args()

    names = set()
    values = {s: set() for s in SLOT_ORDER}
    max_non_name = 0
    for row in read_items(Path(args.items)):
        slots = row["expected_slots"]
        names.add(slots["name"])
        nn = 0
        for s in SLOT_ORDER:
            if s in slots:
                values[s].add(slots[s])
                nn += 1
        max_non_name = max(max_non_name, nn)
    max_non_name = min(max(max_non_name, 1), args.max_non_name_slots)

    lex = ["/************************************************************",
           "* Auto-generated E2E lexicon from real supported items.",
           "************************************************************/",
           "", "FORM form;", "", "/*** Names ***/"]
    for n in sorted(names):
        lex.append(f"{q(n)} name [name:{q(n)}, @_3s];")
    lex += ["", "/*** Slot markers ***/"]
    for s in SLOT_ORDER:
        lex.append(f"{q(SLOT_MARKER_FORMS[s])} slot_marker [slot:{s}];")
    lex += ["", "/*** Slot values ***/"]
    for s in SLOT_ORDER:
        if values[s]:
            lex.append(f"/** {s} **/")
            for v in sorted(values[s]):
                lex.append(f"{q(value_surface(s,v))} slot_value [slot:{s}, value:{q(v)}];")
    lex.append('"and" coord [];')
    Path(args.lexicon_out).parent.mkdir(parents=True, exist_ok=True)
    Path(args.lexicon_out).write_text("\n".join(lex) + "\n", encoding="utf-8")
    Path(args.rules_out).parent.mkdir(parents=True, exist_ok=True)
    write_rules(Path(args.rules_out), max_non_name)
    print(json.dumps({
        "names": len(names),
        "slot_values": {s: len(values[s]) for s in SLOT_ORDER},
        "max_non_name_slots": max_non_name,
        "lexicon_out": args.lexicon_out,
        "rules_out": args.rules_out
    }, indent=2, ensure_ascii=False))
if __name__ == "__main__":
    main()
