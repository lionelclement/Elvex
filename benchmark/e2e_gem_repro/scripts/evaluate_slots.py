#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path
from typing import Any

def norm(s: str) -> str:
    return re.sub(r"\s+", " ", s.lower().strip())

def value_forms(slot: str, value: Any) -> list[str]:
    v = str(value).strip()
    vl = v.lower()
    forms = {vl}

    if slot in {"familyFriendly", "kidsFriendly"}:
        if vl in {"yes", "true", "1"}:
            forms |= {
                "family-friendly", "family friendly", "kid-friendly", "kids friendly",
                "suitable for families", "suitable for children"
            }
        elif vl in {"no", "false", "0"}:
            forms |= {
                "not family-friendly", "not family friendly", "not kid-friendly",
                "not suitable for families", "not suitable for children", "no kids"
            }
    elif slot == "priceRange":
        if vl in {"cheap", "less than £20", "low"}:
            forms |= {"cheap", "low priced", "low-priced", "inexpensive", "less than £20", "less than 20"}
        elif vl in {"moderate", "£20-25", "20-25"}:
            forms |= {"moderate", "moderately priced", "mid-priced", "medium priced", "£20-25", "20-25"}
        elif vl in {"high", "more than £30", "expensive"}:
            forms |= {"high priced", "high-priced", "expensive", "more than £30", "more than 30"}
    elif slot == "customerRating":
        forms.add(vl.replace("/", " out of "))
        if vl in {"high", "average", "low"}:
            forms.add(f"{vl} customer rating")
        if re.fullmatch(r"\d\s*/\s*5", vl):
            forms.add(vl.replace("/", " out of "))
            forms.add(f"customer rating of {vl.replace('/', ' out of ')}")
    elif slot == "area":
        if vl == "riverside":
            forms |= {"riverside", "by the riverside", "by the river", "near the river"}
        elif vl in {"city centre", "city center"}:
            forms |= {"city centre", "city center", "centre of town", "center of town"}
    elif slot == "food":
        forms |= {vl, f"{vl} food", f"{vl} cuisine"}

    return sorted(forms, key=len, reverse=True)

def slot_present(text: str, slot: str, value: Any) -> bool:
    t = norm(text)
    return any(norm(form) in t for form in value_forms(slot, value))

def missing_slots_for_output(output: str, expected: dict[str, Any]) -> list[str]:
    return [slot for slot, value in expected.items() if not slot_present(output, slot, value)]

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--outputs", required=True)
    ap.add_argument("--metrics", required=True)
    ap.add_argument("--details", default=None)
    ap.add_argument("--all-outputs", action="store_true",
                    help="Evaluate every output; an item is valid only if every output is slot-complete.")
    ap.add_argument("--best-output", action="store_true",
                    help="Evaluate the generated output that covers the most expected slots.")
    args = ap.parse_args()

    rows = []
    with Path(args.outputs).open("r", encoding="utf-8") as f:
        for line in f:
            if line.strip():
                rows.append(json.loads(line))

    total = len(rows)
    covered = 0
    valid_items = 0
    total_slots = 0
    omitted_slots = 0
    runtimes = []
    outputs_per_item = []
    details = []

    for row in rows:
        outputs = row.get("outputs", [])
        expected = row.get("expected_slots", {})

        if row.get("ok") and outputs:
            covered += 1

        runtimes.append(row.get("runtime_ms", 0.0))
        outputs_per_item.append(len(outputs))

        if outputs:
            if args.best_output:
                scored = [
                    (len(missing_slots_for_output(output, expected)), i, output, missing_slots_for_output(output, expected))
                    for i, output in enumerate(outputs)
                ]
                scored.sort(key=lambda x: (x[0], x[1]))
                best_missing_count, best_index, best_output, missing_for_item = scored[0]
                selected_outputs = [best_output]
                selected_output_index = best_index
                item_valid = best_missing_count == 0
            else:
                selected_outputs = outputs if args.all_outputs else outputs[:1]
                selected_output_index = 0
                per_output_missing = [
                    missing_slots_for_output(output, expected)
                    for output in selected_outputs
                ]
                if args.all_outputs:
                    missing_for_item = sorted(set(s for missing in per_output_missing for s in missing))
                    item_valid = all(len(missing) == 0 for missing in per_output_missing)
                else:
                    missing_for_item = per_output_missing[0]
                    item_valid = len(missing_for_item) == 0
        else:
            selected_outputs = []
            selected_output_index = None
            missing_for_item = list(expected.keys())
            item_valid = False

        total_slots += len(expected)
        omitted_slots += len(missing_for_item)
        if item_valid:
            valid_items += 1

        details.append({
            "id": row.get("id"),
            "covered": bool(row.get("ok") and outputs),
            "valid": item_valid,
            "missing_slots": missing_for_item,
            "expected_slots": expected,
            "outputs": selected_outputs,
            "selected_output_index": selected_output_index,
            "all_outputs_count": len(outputs),
            "runtime_ms": row.get("runtime_ms"),
        })

    metrics = {
        "total_inputs": total,
        "coverage": covered / total if total else 0.0,
        "item_validity": valid_items / total if total else 0.0,
        "slot_omission_rate": omitted_slots / total_slots if total_slots else 0.0,
        "slot_accuracy": 1.0 - (omitted_slots / total_slots) if total_slots else 0.0,
        "total_slots": total_slots,
        "omitted_slots": omitted_slots,
        "avg_outputs_per_input": sum(outputs_per_item) / total if total else 0.0,
        "avg_runtime_ms": sum(runtimes) / total if total else 0.0,
        "mode": "best_output" if args.best_output else ("all_outputs" if args.all_outputs else "first_output"),
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
