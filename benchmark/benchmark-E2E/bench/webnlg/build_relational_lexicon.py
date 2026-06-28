#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

RELATION_FORMS = {
  "country": "is in",
  "birthPlace": "was born in",
  "birthDate": "was born on",
  "deathPlace": "died in",
  "deathDate": "died on",
  "nationality": "has nationality",
  "occupation": "works as",
  "almaMater": "studied at",
  "office": "held the office of",
  "party": "is affiliated with",
  "location": "is located in",
  "isPartOf": "is part of",
  "region": "is in the region of",
  "city": "is in the city of",
  "capital": "has capital",
  "leader": "is led by",
  "leaderTitle": "has leader title",
  "language": "uses language",
  "genre": "has genre",
  "author": "was written by",
  "creator": "was created by",
  "publisher": "was published by",
  "mediaType": "has media type",
  "club": "plays for",
  "league": "plays in",
  "ground": "plays at",
  "manager": "is managed by",
  "successor": "was succeeded by",
  "precededBy": "was preceded by",
  "followedBy": "was followed by",
  "ingredient": "contains",
  "mainIngredient": "has main ingredient",
  "dishVariation": "has variation",
  "owner": "is owned by",
  "operatingOrganisation": "is operated by",
  "manufacturer": "was manufactured by",
  "builder": "was built by",
  "architect": "was designed by",
  "completionDate": "was completed on",
  "alternativeName": "is also known as",
  "areaTotal": "has total area"
}
PREDICATE_ORDER = ["country", "birthPlace", "birthDate", "deathPlace", "nationality", "occupation", "almaMater", "office", "party", "location", "isPartOf", "region", "city", "capital", "leader", "leaderTitle", "language", "genre", "author", "creator", "publisher", "mediaType", "club", "league", "ground", "manager", "successor", "precededBy", "followedBy", "ingredient", "mainIngredient", "dishVariation", "owner", "operatingOrganisation", "manufacturer", "builder", "architect", "completionDate", "alternativeName", "areaTotal"]

def q(s: str) -> str:
    return '"' + str(s).replace("\\", "\\\\").replace('"', '\\"') + '"'

def feature_name(pred: str) -> str:
    pred = pred.strip().replace("-", "_")
    pred = re.sub(r"[^A-Za-z0-9_]", "_", pred)
    if pred and pred[0].isdigit():
        pred = "rel_" + pred
    return pred or "relation"

def clean_value(s) -> str:
    s = str(s).replace("_", " ").strip()
    s = re.sub(r"\s+", " ", s)
    if len(s) >= 2 and ((s[0] == s[-1] == '"') or (s[0] == s[-1] == "'")):
        s = s[1:-1].strip()
    return s

def split_camel(s: str) -> str:
    return re.sub(r"(?<!^)([A-Z])", r" \1", s).replace("_", " ").lower()

def relation_lexeme(pred: str) -> str:
    return RELATION_FORMS.get(pred, "has " + split_camel(pred))

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--items", required=True)
    ap.add_argument("--out", required=True)
    args = ap.parse_args()

    entities = set()
    objects = set()
    preds = set()
    with Path(args.items).open(encoding="utf-8") as f:
        for line in f:
            if not line.strip():
                continue
            row = json.loads(line)
            for tr in row["triples"]:
                entities.add(clean_value(tr["subj"]))
                objects.add(clean_value(tr["obj"]))
                preds.add(feature_name(tr["pred"]))

    order = {p: i for i, p in enumerate(PREDICATE_ORDER)}
    lines = []
    lines += ["/************************************************************", "* Auto-generated relational WebNLG lexicon", "************************************************************/", "", "FORM form;", ""]
    lines += ["/************************************************************", "* Entities", "************************************************************/"]
    for ent in sorted(entities):
        lines.append(f"{q(ent)} entity_name [entity:{q(ent)}, @_3s];")
    lines += ["", "/************************************************************", "* Objects", "************************************************************/"]
    for obj in sorted(objects):
        lines.append(f"{q(obj)} object_name [obj:{q(obj)}];")
    lines += ["", "/************************************************************", "* Relation markers", "************************************************************/"]
    for pred in sorted(preds, key=lambda p: order.get(p, 999)):
        lines.append(f"{q(relation_lexeme(pred))} relation_marker [pred:{pred}];")
    lines.append('"and" coord [];')
    lines.append("")

    Path(args.out).write_text("\n".join(lines), encoding="utf-8")
    print(f"wrote {args.out}")
    print(f"entities: {len(entities)}")
    print(f"objects: {len(objects)}")
    print(f"predicates: {len(preds)}")

if __name__ == "__main__":
    main()
