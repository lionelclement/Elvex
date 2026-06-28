#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import re
from collections import defaultdict
from pathlib import Path

def normalize_for_regex(s: str) -> str:
    # Keep words and spaces; normalize apostrophes and case.
    s = s.replace("’", "'").lower()
    return s

def matches_any(output: str, patterns: list[str]) -> bool:
    text = normalize_for_regex(output)
    return any(re.search(p, text, flags=re.IGNORECASE | re.DOTALL) for p in patterns)

def select_best(row: dict) -> tuple[str, bool]:
    outputs = row.get("outputs", [])
    pats = row.get("expected_any_regex", [])
    if not outputs:
        return "", False
    for out in outputs:
        if matches_any(out, pats):
            return out, True
    return outputs[0], False

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--outputs", default="bench/results/lexical_probe_outputs.jsonl")
    ap.add_argument("--metrics", default="bench/results/lexical_probe_metrics.json")
    ap.add_argument("--details", default="bench/results/lexical_probe_details.jsonl")
    args = ap.parse_args()

    rows = [json.loads(line) for line in Path(args.outputs).open(encoding="utf-8") if line.strip()]
    by_ph = defaultdict(lambda: {"items": 0, "generated": 0, "correct": 0, "outputs": 0, "runtime_ms": 0.0})
    details = []
    total_items = len(rows)
    generated = 0
    correct = 0
    total_outputs = 0
    total_runtime = 0.0

    for row in rows:
        ph = row.get("phenomenon", "unknown")
        outs = row.get("outputs", [])
        selected, ok = select_best(row)
        gen = bool(outs)
        generated += int(gen)
        correct += int(ok)
        total_outputs += len(outs)
        total_runtime += float(row.get("runtime_ms") or 0.0)

        by_ph[ph]["items"] += 1
        by_ph[ph]["generated"] += int(gen)
        by_ph[ph]["correct"] += int(ok)
        by_ph[ph]["outputs"] += len(outs)
        by_ph[ph]["runtime_ms"] += float(row.get("runtime_ms") or 0.0)

        details.append({
            "id": row.get("id"),
            "phenomenon": ph,
            "input": row.get("input"),
            "description": row.get("description"),
            "selected_output": selected,
            "correct": ok,
            "generated": gen,
            "outputs_count": len(outs),
            "expected_any_regex": row.get("expected_any_regex", []),
            "outputs": outs,
            "runtime_ms": row.get("runtime_ms"),
            "stderr": row.get("stderr", ""),
        })

    metrics = {
        "total_items": total_items,
        "generated_items": generated,
        "generation_rate": generated / total_items if total_items else 0.0,
        "correct_items": correct,
        "accuracy_on_all_items": correct / total_items if total_items else 0.0,
        "accuracy_on_generated_items": correct / generated if generated else 0.0,
        "avg_outputs_per_item": total_outputs / total_items if total_items else 0.0,
        "avg_runtime_ms": total_runtime / total_items if total_items else 0.0,
        "by_phenomenon": {},
    }
    for ph, d in sorted(by_ph.items()):
        metrics["by_phenomenon"][ph] = {
            "items": d["items"],
            "generated": d["generated"],
            "generation_rate": d["generated"] / d["items"] if d["items"] else 0.0,
            "correct": d["correct"],
            "accuracy_on_all_items": d["correct"] / d["items"] if d["items"] else 0.0,
            "accuracy_on_generated_items": d["correct"] / d["generated"] if d["generated"] else 0.0,
            "avg_outputs_per_item": d["outputs"] / d["items"] if d["items"] else 0.0,
            "avg_runtime_ms": d["runtime_ms"] / d["items"] if d["items"] else 0.0,
        }

    Path(args.metrics).parent.mkdir(parents=True, exist_ok=True)
    Path(args.metrics).write_text(json.dumps(metrics, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    with Path(args.details).open("w", encoding="utf-8") as f:
        for row in details:
            f.write(json.dumps(row, ensure_ascii=False) + "\n")
    print(json.dumps(metrics, indent=2, ensure_ascii=False))

if __name__ == "__main__":
    main()
