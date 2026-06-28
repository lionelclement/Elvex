#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import re
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from lib.webnlg_utils import parse_number_value


def read_tsv(path: Path):
    with path.open(encoding="utf-8", newline="") as f:
        for line_no, line in enumerate(f, start=1):
            line = line.rstrip("\n")
            if not line or line.lstrip().startswith("//"):
                continue
            parts = line.split("\t")
            if len(parts) >= 4:
                yield line_no, parts[0], parts[1], parts[2], parts[3]


def classify_numeric_label(form: str) -> str:
    if parse_number_value(form):
        return "dynamic_number_or_measure"
    if re.match(r"^\d{4}\s+\d{2}\s+\d{2}$", form):
        return "date_like_kept_as_entity"
    if re.match(r"^\s*[+-]?(?:\d+(?:\.\d*)?|\.\d+)", form):
        return "numeric_initial_entity"
    return "other"


def main() -> int:
    ap = argparse.ArgumentParser(description="Report numeric-looking entries in an Elvex morphology file")
    ap.add_argument("morpho", nargs="?", default=str(ROOT / "user/main.morpho"))
    ap.add_argument("--show", type=int, default=80, help="Maximum number of sample lines to print")
    args = ap.parse_args()

    path = Path(args.morpho)
    if not path.exists():
        raise SystemExit(f"Not found: {path}")

    counts: Counter[str] = Counter()
    samples: dict[str, list[tuple[int, str, str, str]]] = {}
    for line_no, form, pos, lemma, features in read_tsv(path):
        if pos != "proper_noun":
            continue
        if not re.match(r"^\s*[\"+-]?(?:\d+(?:\.\d*)?|\.\d+|\d)", form):
            continue
        cls = classify_numeric_label(form)
        counts[cls] += 1
        samples.setdefault(cls, [])
        if len(samples[cls]) < args.show:
            samples[cls].append((line_no, form, lemma, features))

    print(f"Numeric-looking proper_noun entries in {path}:")
    if not counts:
        print("  none")
        return 0
    for cls, count in counts.most_common():
        print(f"  {cls}: {count}")
    print()
    for cls, rows in samples.items():
        print(f"[{cls}]")
        for line_no, form, lemma, features in rows[: args.show]:
            print(f"  line {line_no}: {form}\tproper_noun\t{lemma}\t{features}")
        print()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
