#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Any

SLOT_ORDER = ["eatType", "food", "priceRange", "area", "near", "familyFriendly", "customerRating"]

def atom(v: Any) -> str:
    if isinstance(v, bool):
        return "true" if v else "false"
    if isinstance(v, (int, float)):
        return str(v)
    s = str(v)
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"') + '"'

def render_feature_structure(d: dict[str, Any]) -> str:
    parts = []
    for k, v in d.items():
        if isinstance(v, dict):
            parts.append(f"{k}:{render_feature_structure(v)}")
        elif k == "HEAD":
            parts.append(f"{k}:{v}")
        else:
            parts.append(f"{k}:{atom(v)}")
    return "[" + ", ".join(parts) + "]"

def slots_to_features(slots: dict[str, Any], head: str) -> dict[str, Any]:
    fs: dict[str, Any] = {"HEAD": head}
    if "name" in slots:
        fs["name"] = slots["name"]
    for slot in SLOT_ORDER:
        if slot in slots:
            fs[slot] = slots[slot]
    return fs

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--items", required=True)
    ap.add_argument("--input-dir", required=True)
    ap.add_argument("--manifest", required=True)
    ap.add_argument("--head", default="DESCRIBE_RESTAURANT")
    ap.add_argument("--symbol", default="Axiom")
    args = ap.parse_args()

    input_dir = Path(args.input_dir)
    input_dir.mkdir(parents=True, exist_ok=True)
    manifest_path = Path(args.manifest)
    manifest_path.parent.mkdir(parents=True, exist_ok=True)

    count = 0
    with Path(args.items).open("r", encoding="utf-8") as f, manifest_path.open("w", encoding="utf-8") as out:
        for idx, line in enumerate(f, 1):
            if not line.strip():
                continue
            row = json.loads(line)
            item_id = row.get("fragment_id") or row.get("id") or f"e2e_full_{idx:05d}"
            slots = row["expected_slots"]
            fs = slots_to_features(slots, args.head)
            input_path = input_dir / f"{item_id}.input"
            input_path.write_text(args.symbol + " " + render_feature_structure(fs) + "\n", encoding="utf-8")
            manifest = {
                "id": item_id,
                "source_id": row.get("id"),
                "split": row.get("split"),
                "mr": row.get("mr"),
                "input_file": str(input_path),
                "expected_slots": slots,
                "references": row.get("references", []),
                "n_slots": len(slots),
                "symbol": args.symbol,
                "head": args.head,
            }
            out.write(json.dumps(manifest, ensure_ascii=False) + "\n")
            count += 1

    print(f"wrote {count} input files in {input_dir}")
    print(f"wrote manifest: {manifest_path}")

if __name__ == "__main__":
    main()
