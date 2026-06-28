#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path
from typing import Any

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

def clean_value(s: Any) -> str:
    s = str(s).replace("_", " ").strip()
    s = re.sub(r"\s+", " ", s)
    if len(s) >= 2 and ((s[0] == s[-1] == '"') or (s[0] == s[-1] == "'")):
        s = s[1:-1].strip()
    return s

def norm(s: str) -> str:
    return re.sub(r"\s+", " ", clean_value(s).lower().strip())

def split_camel(s: str) -> str:
    return re.sub(r"(?<!^)([A-Z])", r" \1", s).replace("_", " ").lower()

def relation_forms(pred: str, obj: str) -> list[str]:
    p = pred.strip()
    o = clean_value(obj)
    ol = o.lower()
    rel = RELATION_FORMS.get(p, "has " + split_camel(p))
    forms = {ol, f"{rel} {ol}"}
    if p in {"country", "location", "region", "city", "isPartOf"}:
        forms |= {f"in {ol}", f"located in {ol}", f"is part of {ol}"}
    elif p == "capital":
        forms |= {f"capital {ol}", f"capital is {ol}", f"has capital {ol}"}
    elif p == "birthPlace":
        forms |= {f"born in {ol}", f"was born in {ol}"}
    elif p == "birthDate":
        forms |= {f"born on {ol}", f"was born on {ol}"}
    elif p == "deathPlace":
        forms |= {f"died in {ol}"}
    elif p == "occupation":
        forms |= {f"works as {ol}", f"is a {ol}", f"was a {ol}"}
    elif p in {"author", "creator", "publisher", "manufacturer", "builder", "architect"}:
        forms |= {f"by {ol}"}
    return sorted(forms, key=len, reverse=True)

def triple_present(output: str, triple: dict[str, Any]) -> bool:
    t = norm(output)
    pred = str(triple.get("pred", ""))
    obj = str(triple.get("obj", ""))
    return any(norm(form) in t for form in relation_forms(pred, obj))

def missing_triples_for_output(output: str, triples: list[dict[str, Any]]) -> list[dict[str, Any]]:
    return [tr for tr in triples if not triple_present(output, tr)]

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--outputs", required=True)
    ap.add_argument("--metrics", required=True)
    ap.add_argument("--details", default=None)
    ap.add_argument("--best-output", action="store_true")
    args = ap.parse_args()

    rows = [json.loads(line) for line in Path(args.outputs).open("r", encoding="utf-8") if line.strip()]
    total = len(rows)
    covered = valid_items = total_triples = omitted_triples = 0
    outputs_per_item = []
    runtimes = []
    details = []

    for row in rows:
        outputs = row.get("outputs", [])
        triples = row.get("triples", [])
        outputs_per_item.append(len(outputs))
        runtimes.append(row.get("runtime_ms", 0.0))
        if row.get("ok") and outputs:
            covered += 1
        if outputs:
            if args.best_output:
                scored = [
                    (len(missing_triples_for_output(out, triples)), i, out, missing_triples_for_output(out, triples))
                    for i, out in enumerate(outputs)
                ]
                scored.sort(key=lambda x: (x[0], x[1]))
                miss_count, selected_idx, selected_output, missing = scored[0]
            else:
                selected_idx = 0
                selected_output = outputs[0]
                missing = missing_triples_for_output(selected_output, triples)
                miss_count = len(missing)
            selected_outputs = [selected_output]
            item_valid = miss_count == 0
        else:
            selected_idx = None
            selected_outputs = []
            missing = triples
            item_valid = False
        total_triples += len(triples)
        omitted_triples += len(missing)
        if item_valid:
            valid_items += 1
        details.append({
            "id": row.get("id"),
            "covered": bool(row.get("ok") and outputs),
            "valid": item_valid,
            "missing_triples": missing,
            "triples": triples,
            "outputs": selected_outputs,
            "selected_output_index": selected_idx,
            "all_outputs_count": len(outputs),
            "runtime_ms": row.get("runtime_ms"),
        })

    metrics = {
        "total_inputs": total,
        "coverage": covered / total if total else 0.0,
        "item_validity": valid_items / total if total else 0.0,
        "triple_omission_rate": omitted_triples / total_triples if total_triples else 0.0,
        "triple_accuracy": 1.0 - (omitted_triples / total_triples) if total_triples else 0.0,
        "total_triples": total_triples,
        "omitted_triples": omitted_triples,
        "avg_outputs_per_input": sum(outputs_per_item) / total if total else 0.0,
        "avg_runtime_ms": sum(runtimes) / total if total else 0.0,
        "mode": "best_output" if args.best_output else "first_output",
    }
    Path(args.metrics).parent.mkdir(parents=True, exist_ok=True)
    Path(args.metrics).write_text(json.dumps(metrics, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    if args.details:
        with Path(args.details).open("w", encoding="utf-8") as f:
            for d in details:
                f.write(json.dumps(d, ensure_ascii=False) + "\n")
    print(json.dumps(metrics, indent=2, ensure_ascii=False))

if __name__ == "__main__":
    main()
