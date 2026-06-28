#!/usr/bin/env python3
from __future__ import annotations

import argparse
from collections import defaultdict
from pathlib import Path
import sys
from typing import Any

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from lib.webnlg_utils import read_jsonl, write_jsonl


def atomic_rows(rows: list[dict[str, Any]]) -> list[dict[str, Any]]:
    """Create a 1-triple view from all observed triples.

    Some WebNLG dumps do not contain documentary entries of size 1,
    but we still want to work on single triples. This function
    therefore expands each individual triple into a standalone row.
    """
    out: list[dict[str, Any]] = []
    seen: set[tuple[str, str, str]] = set()
    for row in rows:
        for idx, triple in enumerate(row.get("triples", []), start=1):
            key = (triple.get("subject", ""), triple.get("predicate", ""), triple.get("object", ""))
            if key in seen:
                continue
            seen.add(key)
            out.append({
                "id": f"{row.get('id', 'entry')}#t{idx}",
                "source_entry_id": row.get("id"),
                "source_file": row.get("source_file"),
                "category": row.get("category"),
                "split": row.get("split"),
                "size": 1,
                "triples": [triple],
                "lexicalizations": row.get("lexicalizations", []),
            })
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description="Select entries by number of triples")
    ap.add_argument("--triples", default=str(ROOT / "data/processed/triples.jsonl"))
    ap.add_argument("--out-dir", default=str(ROOT / "build/sequences"))
    ap.add_argument("--atomic", action=argparse.BooleanOptionalAction, default=True,
                    help="Write build/sequences/1.jsonl by expanding all individual triples")
    args = ap.parse_args()

    source_rows = list(read_jsonl(Path(args.triples)))
    groups: dict[int, list[dict[str, Any]]] = defaultdict(list)
    for row in source_rows:
        groups[len(row.get("triples", []))].append(row)

    out = Path(args.out_dir)
    out.mkdir(parents=True, exist_ok=True)

    if args.atomic:
        one_rows = atomic_rows(source_rows)
        n = write_jsonl(out / "1.jsonl", one_rows)
        print(f"1 atomic triple(s): {n} -> {out / '1.jsonl'}")
    elif 1 in groups:
        n = write_jsonl(out / "1.jsonl", groups[1])
        print(f"1 triple(s): {n} -> {out / '1.jsonl'}")

    for size, rows in sorted(groups.items()):
        if size == 1:
            # Already written above, either as an atomic view or as a native group.
            continue
        n = write_jsonl(out / f"{size}.jsonl", rows)
        print(f"{size} triple(s): {n} -> {out / f'{size}.jsonl'}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
