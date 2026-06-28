#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path
from typing import Any

def atom(v: Any) -> str:
    if isinstance(v, bool):
        return "true" if v else "false"
    if isinstance(v, (int, float)):
        return str(v)
    s = str(v)
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"') + '"'

def feature_name(pred: str) -> str:
    pred = pred.strip().replace("-", "_")
    pred = re.sub(r"[^A-Za-z0-9_]", "_", pred)
    if pred and pred[0].isdigit():
        pred = "rel_" + pred
    return pred or "relation"

def clean_value(s: Any) -> str:
    s = str(s).replace("_", " ").strip()
    s = re.sub(r"\s+", " ", s)
    if len(s) >= 2 and ((s[0] == s[-1] == '"') or (s[0] == s[-1] == "'")):
        s = s[1:-1].strip()
    return s

def render_feature_structure(d: dict[str, Any]) -> str:
    parts = []
    for k, v in d.items():
        if isinstance(v, dict):
            parts.append(f"{k}:{render_feature_structure(v)}")
        elif k in {"HEAD", "pred"}:
            parts.append(f"{k}:{v}")
        else:
            parts.append(f"{k}:{atom(v)}")
    return "[" + ", ".join(parts) + "]"

def triples_to_features(triples: list[dict[str, str]]) -> dict[str, Any]:
    fs: dict[str, Any] = {"HEAD": "DESCRIBE_ENTITY"}
    if triples:
        fs["entity"] = clean_value(triples[0]["subj"])
    for i, t in enumerate(triples, 1):
        fs[f"rel{i}"] = {
            "pred": feature_name(t["pred"]),
            "obj": clean_value(t["obj"]),
        }
    return fs

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--items", required=True)
    ap.add_argument("--input-dir", required=True)
    ap.add_argument("--manifest", required=True)
    ap.add_argument("--symbol", default="Axiom")
    args = ap.parse_args()

    input_dir = Path(args.input_dir)
    input_dir.mkdir(parents=True, exist_ok=True)
    manifest = Path(args.manifest)
    manifest.parent.mkdir(parents=True, exist_ok=True)

    with Path(args.items).open(encoding="utf-8") as f, manifest.open("w", encoding="utf-8") as mf:
        for line in f:
            if not line.strip():
                continue
            row = json.loads(line)
            fs = triples_to_features(row["triples"])
            input_path = input_dir / f"{row['id']}.input"
            input_path.write_text(args.symbol + " " + render_feature_structure(fs) + "\n", encoding="utf-8")

            expected = {}
            for tr in row["triples"]:
                expected.setdefault(feature_name(tr["pred"]), []).append(clean_value(tr["obj"]))

            out_row = dict(row)
            out_row["input_file"] = str(input_path)
            out_row["expected_relations"] = expected
            mf.write(json.dumps(out_row, ensure_ascii=False) + "\n")

    print(f"wrote input files in {input_dir}")
    print(f"wrote manifest: {manifest}")

if __name__ == "__main__":
    main()
