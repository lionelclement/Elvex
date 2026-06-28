#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Any

def first_existing(ex: dict[str, Any], keys: list[str]) -> Any:
    for k in keys:
        if k in ex and ex[k] is not None:
            return ex[k]
    return None

def normalize_references(x: Any) -> list[str]:
    if x is None:
        return []
    if isinstance(x, str):
        return [x]
    if isinstance(x, list):
        out = []
        for v in x:
            if isinstance(v, str):
                out.append(v)
            elif isinstance(v, dict):
                txt = first_existing(v, ["target", "text", "value"])
                if isinstance(txt, str):
                    out.append(txt)
        return out
    if isinstance(x, dict):
        for key in ["references", "target", "targets", "text", "output"]:
            if key in x:
                return normalize_references(x[key])
    return []

def write_jsonl(path: Path, rows: list[dict[str, Any]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as f:
        for row in rows:
            f.write(json.dumps(row, ensure_ascii=False) + "\n")

def normalize_e2e_split(split_name: str, ds) -> list[dict[str, Any]]:
    rows = []
    for i, ex in enumerate(ds):
        ex = dict(ex)
        mr = first_existing(ex, ["meaning_representation", "mr", "input", "source"])
        if isinstance(mr, dict):
            mr = first_existing(mr, ["meaning_representation", "mr", "text", "value"])
        refs = normalize_references(first_existing(ex, ["references", "target", "targets", "output"]))
        rows.append({
            "id": f"gem_e2e_{split_name}_{i+1:06d}",
            "split": split_name,
            "mr": mr,
            "references": refs,
            "raw_keys": sorted(ex.keys()),
            "raw": ex,
        })
    return rows

def normalize_webnlg_split(split_name: str, ds) -> list[dict[str, Any]]:
    rows = []
    for i, ex in enumerate(ds):
        ex = dict(ex)
        source = first_existing(ex, ["input", "source", "meaning_representation", "mr", "triples", "tripleset"])
        refs = normalize_references(first_existing(ex, ["references", "target", "targets", "output"]))
        rows.append({
            "id": f"gem_webnlg_{split_name}_{i+1:06d}",
            "split": split_name,
            "source": source,
            "references": refs,
            "raw_keys": sorted(ex.keys()),
            "raw": ex,
        })
    return rows

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--out-dir", default="bench/data")
    ap.add_argument("--trust-remote-code", action="store_true")
    ap.add_argument("--e2e-name", default="GEM/e2e_nlg")
    ap.add_argument("--webnlg-name", default="GEM/web_nlg")
    args = ap.parse_args()

    try:
        from datasets import load_dataset
    except ImportError as e:
        raise SystemExit("Missing dependency. Install with: python -m pip install 'datasets>=2.0.0'") from e

    kwargs = {}
    if args.trust_remote_code:
        kwargs["trust_remote_code"] = True

    out_dir = Path(args.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)

    print(f"loading {args.e2e_name}")
    e2e = load_dataset(args.e2e_name, **kwargs)
    print("E2E splits:", list(e2e.keys()))
    for split, ds in e2e.items():
        rows = normalize_e2e_split(split, ds)
        path = out_dir / f"real_gem_e2e_{split}.jsonl"
        write_jsonl(path, rows)
        print(f"wrote {path} ({len(rows)} rows)")

    print(f"loading {args.webnlg_name}")
    webnlg = load_dataset(args.webnlg_name, "en", **kwargs)
    print("WebNLG splits:", list(webnlg.keys()))
    for split, ds in webnlg.items():
        rows = normalize_webnlg_split(split, ds)
        path = out_dir / f"real_gem_webnlg_{split}.jsonl"
        write_jsonl(path, rows)
        print(f"wrote {path} ({len(rows)} rows)")

if __name__ == "__main__":
    main()
