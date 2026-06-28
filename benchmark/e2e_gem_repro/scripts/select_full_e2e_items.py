#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path
from typing import Any

MR_RE = re.compile(r"\s*([A-Za-z][A-Za-z0-9_ ]*)\s*\[([^\]]*)\]\s*")

SLOT_NORMALIZATION = {
    "name": "name",
    "eattype": "eatType",
    "eat type": "eatType",
    "food": "food",
    "pricerange": "priceRange",
    "price range": "priceRange",
    "area": "area",
    "familyfriendly": "familyFriendly",
    "family friendly": "familyFriendly",
    "near": "near",
    "customerrating": "customerRating",
    "customer rating": "customerRating",
}
SUPPORTED_SLOTS = {"name", "eatType", "food", "priceRange", "area", "familyFriendly", "near", "customerRating"}

def clean_value(s: Any) -> str:
    s = str(s).replace("_", " ").strip()
    s = re.sub(r"\s+", " ", s)
    if len(s) >= 2 and ((s[0] == s[-1] == '"') or (s[0] == s[-1] == "'")):
        s = s[1:-1].strip()
    return s

def normalize_slot_name(s: str) -> str:
    key = re.sub(r"\s+", " ", s.strip().lower())
    key_no_space = key.replace(" ", "")
    if key in SLOT_NORMALIZATION:
        return SLOT_NORMALIZATION[key]
    if key_no_space in SLOT_NORMALIZATION:
        return SLOT_NORMALIZATION[key_no_space]
    return s.strip().replace(" ", "")

def parse_e2e_mr(mr: Any) -> dict[str, str] | None:
    if not isinstance(mr, str):
        return None
    slots: dict[str, str] = {}
    for part in mr.split(","):
        part = part.strip()
        if not part:
            continue
        m = MR_RE.fullmatch(part)
        if not m:
            return None
        slot = normalize_slot_name(m.group(1))
        slots[slot] = clean_value(m.group(2))
    return slots

def read_jsonl(path: Path):
    with path.open(encoding="utf-8") as f:
        for line in f:
            if line.strip():
                yield json.loads(line)

def write_jsonl(path: Path, rows: list[dict[str, Any]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as f:
        for row in rows:
            f.write(json.dumps(row, ensure_ascii=False) + "\n")

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--input", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--summary", default=None)
    ap.add_argument("--n", type=int, default=0, help="0 means keep all parseable items")
    args = ap.parse_args()

    selected = []
    total = parsed = supported = no_name = 0
    unsupported_slots: dict[str, int] = {}

    for row in read_jsonl(Path(args.input)):
        total += 1
        slots = parse_e2e_mr(row.get("mr"))
        if slots is None:
            continue
        parsed += 1
        extra = sorted(set(slots) - SUPPORTED_SLOTS)
        if extra:
            for s in extra:
                unsupported_slots[s] = unsupported_slots.get(s, 0) + 1
            continue
        supported += 1
        if "name" not in slots:
            no_name += 1
        nr = {
            "id": row["id"],
            "fragment_id": f"e2e_full_{len(selected)+1:05d}",
            "split": row.get("split"),
            "mr": row.get("mr"),
            "expected_slots": slots,
            "n_slots": len(slots),
            "references": row.get("references", []),
        }
        selected.append(nr)
        if args.n > 0 and len(selected) >= args.n:
            break

    write_jsonl(Path(args.out), selected)
    summary = {
        "total": total,
        "parsed": parsed,
        "supported_slots": supported,
        "selected": len(selected),
        "no_name": no_name,
        "unsupported_slots": unsupported_slots,
        "out": args.out,
    }
    print(json.dumps(summary, indent=2, ensure_ascii=False))
    if args.summary:
        Path(args.summary).parent.mkdir(parents=True, exist_ok=True)
        Path(args.summary).write_text(json.dumps(summary, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")

if __name__ == "__main__":
    main()
