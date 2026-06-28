#!/usr/bin/env python3
from __future__ import annotations
import argparse, json, re
from pathlib import Path
from typing import Any

MR_RE = re.compile(r"\s*([A-Za-z][A-Za-z0-9_]*)\s*\[([^\]]*)\]\s*")
SLOT_ORDER = ["eatType", "food", "priceRange", "area", "familyFriendly", "near", "customerRating"]

def parse_mr(mr: str) -> dict[str, Any]:
    slots = {}
    for part in mr.split(","):
        part = part.strip()
        if not part:
            continue
        m = MR_RE.fullmatch(part)
        if not m:
            raise ValueError(f"Cannot parse MR part: {part!r}")
        slots[m.group(1)] = m.group(2).strip()
    return slots

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
        elif k in {"HEAD", "slot"}:
            parts.append(f"{k}:{v}")
        else:
            parts.append(f"{k}:{atom(v)}")
    return "[" + ", ".join(parts) + "]"

def slots_to_features(slots: dict[str, Any], head: str) -> dict[str, Any]:
    fs: dict[str, Any] = {"HEAD": head, "name": slots["name"]}
    i = 1
    for slot in SLOT_ORDER:
        if slot in slots:
            fs[f"slot{i}"] = {"slot": slot, "value": slots[slot]}
            i += 1
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
            item_id = row.get("fragment_id") or row.get("id") or f"e2e_{idx:05d}"
            slots = row.get("expected_slots")
            if not isinstance(slots, dict):
                slots = parse_mr(row["mr"])
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
