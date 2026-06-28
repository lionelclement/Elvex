#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import random
import re
from pathlib import Path
from typing import Any

E2E_SUPPORTED_SLOTS = ["name", "eatType", "food", "priceRange", "area", "familyFriendly", "near", "customerRating"]
WEBNLG_SUPPORTED_PREDS = {
    "country","birthPlace","birthDate","deathPlace","nationality","occupation","almaMater","office","party",
    "location","isPartOf","region","city","capital","leader","leaderTitle","language",
    "genre","author","creator","publisher","mediaType",
    "club","league","ground","manager","successor","precededBy","followedBy",
    "ingredient","mainIngredient","dishVariation",
    "owner","operatingOrganisation","manufacturer","builder","architect",
    "completionDate","alternativeName","areaTotal"
}
MR_RE = re.compile(r"\s*([A-Za-z][A-Za-z0-9_]*)\s*\[([^\]]*)\]\s*")

def clean_value(s: Any) -> str:
    s = str(s).replace("_", " ").strip()
    s = re.sub(r"\s+", " ", s)
    if len(s) >= 2 and ((s[0] == s[-1] == '"') or (s[0] == s[-1] == "'")):
        s = s[1:-1].strip()
    return s

def feature_name(pred: str) -> str:
    pred = str(pred).strip().replace("-", "_")
    pred = re.sub(r"[^A-Za-z0-9_]", "_", pred)
    if pred and pred[0].isdigit():
        pred = "rel_" + pred
    return pred or "relation"

def parse_e2e_mr(mr: Any) -> dict[str, str] | None:
    if not isinstance(mr, str):
        return None
    slots = {}
    for part in mr.split(","):
        part = part.strip()
        if not part:
            continue
        m = MR_RE.fullmatch(part)
        if not m:
            return None
        slots[m.group(1)] = clean_value(m.group(2))
    return slots

def parse_triple_string(s: str) -> list[dict[str, str]]:
    triples = []
    chunks = re.split(r"\s*(?:\n|<br\s*/?>|;)\s*", s)
    for ch in chunks:
        ch = ch.strip().strip("()[]{} ")
        if not ch:
            continue
        if "|" in ch:
            parts = [p.strip() for p in ch.split("|")]
        else:
            m = re.match(r"^\s*<([^>]*)>\s*<([^>]*)>\s*<([^>]*)>\s*$", ch)
            if not m:
                continue
            parts = [m.group(1), m.group(2), m.group(3)]
        if len(parts) == 3:
            triples.append({"subj": clean_value(parts[0]), "pred": feature_name(parts[1]), "obj": clean_value(parts[2])})
    return triples

def parse_webnlg_source(x: Any) -> list[dict[str, str]]:
    if x is None:
        return []
    if isinstance(x, str):
        return parse_triple_string(x)
    if isinstance(x, list):
        triples = []
        for item in x:
            triples.extend(parse_webnlg_source(item))
        return triples
    if isinstance(x, dict):
        subj = x.get("subj") or x.get("subject") or x.get("s")
        pred = x.get("pred") or x.get("predicate") or x.get("property") or x.get("p")
        obj = x.get("obj") or x.get("object") or x.get("o")
        if subj is not None and pred is not None and obj is not None:
            return [{"subj": clean_value(subj), "pred": feature_name(pred), "obj": clean_value(obj)}]
        for key in ["triples", "triple_set", "tripleset", "modified_triple_sets", "input"]:
            if key in x:
                triples = parse_webnlg_source(x[key])
                if triples:
                    return triples
        triples = []
        for v in x.values():
            triples.extend(parse_webnlg_source(v))
        return triples
    return []

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

def select_e2e(input_path: Path, out_path: Path, n: int, seed: int, max_slots: int) -> dict[str, Any]:
    rng = random.Random(seed)
    supported = []
    total = parsed = 0
    for row in read_jsonl(input_path):
        total += 1
        slots = parse_e2e_mr(row.get("mr"))
        if slots is None:
            continue
        parsed += 1
        if "name" not in slots:
            continue
        if not set(slots).issubset(set(E2E_SUPPORTED_SLOTS)):
            continue
        if not (2 <= len(slots) <= max_slots):
            continue
        nr = {
            "id": row["id"],
            "split": row.get("split"),
            "mr": row.get("mr"),
            "expected_slots": slots,
            "n_slots": len(slots),
            "references": row.get("references", []),
        }
        supported.append(nr)
    rng.shuffle(supported)
    selected = supported[:n] if n > 0 else supported
    for i, row in enumerate(selected, 1):
        row["fragment_id"] = f"e2e_real_{i:05d}"
    write_jsonl(out_path, selected)
    return {"total": total, "parsed": parsed, "supported": len(supported), "selected": len(selected), "out": str(out_path)}

def select_webnlg(input_path: Path, out_path: Path, n: int, seed: int, max_triples: int) -> dict[str, Any]:
    rng = random.Random(seed)
    supported = []
    total = parsed = 0
    for row in read_jsonl(input_path):
        total += 1
        triples = parse_webnlg_source(row.get("source")) or parse_webnlg_source(row.get("raw"))
        if not triples:
            continue
        parsed += 1
        if not (1 <= len(triples) <= max_triples):
            continue
        subjs = {t["subj"] for t in triples}
        preds = [t["pred"] for t in triples]
        if len(subjs) != 1:
            continue
        if len(set(preds)) != len(preds):
            continue
        if not set(preds).issubset(WEBNLG_SUPPORTED_PREDS):
            continue
        nr = {
            "id": row["id"],
            "split": row.get("split"),
            "triples": triples,
            "predicates": sorted(set(preds)),
            "references": row.get("references", []),
        }
        supported.append(nr)
    rng.shuffle(supported)
    selected = supported[:n] if n > 0 else supported
    for i, row in enumerate(selected, 1):
        row["id"] = f"webnlg_real_{i:05d}"
    write_jsonl(out_path, selected)
    return {"total": total, "parsed": parsed, "supported": len(supported), "selected": len(selected), "out": str(out_path)}

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--dataset", choices=["e2e", "webnlg"], required=True)
    ap.add_argument("--input", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--n", type=int, default=0, help="0 means keep all supported items")
    ap.add_argument("--seed", type=int, default=23)
    ap.add_argument("--max-e2e-slots", type=int, default=9)
    ap.add_argument("--max-webnlg-triples", type=int, default=3)
    ap.add_argument("--summary", default=None)
    args = ap.parse_args()

    if args.dataset == "e2e":
        summary = select_e2e(Path(args.input), Path(args.out), args.n, args.seed, args.max_e2e_slots)
    else:
        summary = select_webnlg(Path(args.input), Path(args.out), args.n, args.seed, args.max_webnlg_triples)
    print(json.dumps(summary, indent=2, ensure_ascii=False))
    if args.summary:
        Path(args.summary).parent.mkdir(parents=True, exist_ok=True)
        Path(args.summary).write_text(json.dumps(summary, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")

if __name__ == "__main__":
    main()
