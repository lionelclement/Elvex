#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

def safe_id(s: str) -> str:
    return re.sub(r"[^A-Za-z0-9_.-]", "_", s)

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--items", default="bench/lexical_probe/items.jsonl")
    ap.add_argument("--out-dir", default="bench/lexical_probe/inputs")
    ap.add_argument("--manifest", default="bench/lexical_probe/manifest.jsonl")
    args = ap.parse_args()

    items = [json.loads(line) for line in Path(args.items).open(encoding="utf-8") if line.strip()]
    out_dir = Path(args.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    Path(args.manifest).parent.mkdir(parents=True, exist_ok=True)

    with Path(args.manifest).open("w", encoding="utf-8") as mf:
        for item in items:
            item_id = item["id"]
            input_file = out_dir / f"{safe_id(item_id)}.input"
            input_file.write_text(item["input"].strip() + "\n", encoding="utf-8")
            row = dict(item)
            row["input_file"] = str(input_file)
            mf.write(json.dumps(row, ensure_ascii=False) + "\n")

    print(f"wrote {len(items)} inputs to {out_dir}")
    print(f"manifest: {args.manifest}")

if __name__ == "__main__":
    main()
