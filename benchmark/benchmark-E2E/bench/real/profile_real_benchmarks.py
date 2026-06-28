#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import re
import collections
from pathlib import Path
from typing import Any

E2E_SUPPORTED_SLOTS = {"name", "eatType", "food", "priceRange", "area", "familyFriendly", "near", "customerRating"}
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

def read_jsonl(path: Path) -> list[dict[str, Any]]:
    rows = []
    with path.open(encoding="utf-8") as f:
        for line in f:
            if line.strip():
                rows.append(json.loads(line))
    return rows

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
    # Common formats include: "subj | pred | obj", "(subj | pred | obj)", "<subj> <pred> <obj>"
    chunks = re.split(r"\s*(?:\n|<br\s*/?>|;)\s*", s)
    for ch in chunks:
        ch = ch.strip()
        if not ch:
            continue
        ch = ch.strip("()[]{} ")
        if "|" in ch:
            parts = [p.strip() for p in ch.split("|")]
        elif " ||| " in ch:
            parts = [p.strip() for p in ch.split(" ||| ")]
        else:
            # Try WebNLG angle-bracket-ish triples.
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
        # Direct triple dict.
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
        # Some GEM examples store several text fields.
        triples = []
        for v in x.values():
            triples.extend(parse_webnlg_source(v))
        return triples
    return []

def profile_e2e(rows: list[dict[str, Any]], max_slots_including_name: int = 9) -> dict[str, Any]:
    total = len(rows)
    parsed = 0
    supported = 0
    unsupported_slots = collections.Counter()
    slot_counts = collections.Counter()
    nslot_dist = collections.Counter()
    for row in rows:
        slots = parse_e2e_mr(row.get("mr"))
        if slots is None:
            continue
        parsed += 1
        nslot_dist[len(slots)] += 1
        for s in slots:
            slot_counts[s] += 1
            if s not in E2E_SUPPORTED_SLOTS:
                unsupported_slots[s] += 1
        if set(slots).issubset(E2E_SUPPORTED_SLOTS) and "name" in slots and 2 <= len(slots) <= max_slots_including_name:
            supported += 1
    return {
        "total": total,
        "parsed_mr": parsed,
        "supported_by_current_factorized_grammar": supported,
        "supported_fraction_of_total": supported / total if total else 0.0,
        "slot_counts": dict(slot_counts.most_common()),
        "slot_count_distribution": dict(sorted(nslot_dist.items())),
        "unsupported_slots": dict(unsupported_slots.most_common()),
        "criteria": {
            "requires_name": True,
            "supported_slots": sorted(E2E_SUPPORTED_SLOTS),
            "max_slots_including_name": max_slots_including_name,
        },
    }

def profile_webnlg(rows: list[dict[str, Any]], max_triples: int = 3) -> dict[str, Any]:
    total = len(rows)
    parsed = 0
    supported = 0
    pred_counts = collections.Counter()
    unsupported_pred_counts = collections.Counter()
    triple_count_dist = collections.Counter()
    multi_subject = 0
    repeated_predicate = 0
    for row in rows:
        triples = parse_webnlg_source(row.get("source"))
        if not triples:
            # try raw fields, because GEM format may vary
            triples = parse_webnlg_source(row.get("raw"))
        if not triples:
            continue
        parsed += 1
        triple_count_dist[len(triples)] += 1
        preds = [t["pred"] for t in triples]
        subjs = {t["subj"] for t in triples}
        if len(subjs) > 1:
            multi_subject += 1
        if len(set(preds)) < len(preds):
            repeated_predicate += 1
        for p in preds:
            pred_counts[p] += 1
            if p not in WEBNLG_SUPPORTED_PREDS:
                unsupported_pred_counts[p] += 1
        if (
            1 <= len(triples) <= max_triples
            and len(subjs) == 1
            and len(set(preds)) == len(preds)
            and set(preds).issubset(WEBNLG_SUPPORTED_PREDS)
        ):
            supported += 1
    return {
        "total": total,
        "parsed_triples": parsed,
        "supported_by_current_relational_grammar": supported,
        "supported_fraction_of_total": supported / total if total else 0.0,
        "predicate_counts_top50": dict(pred_counts.most_common(50)),
        "triple_count_distribution": dict(sorted(triple_count_dist.items())),
        "unsupported_predicates_top50": dict(unsupported_pred_counts.most_common(50)),
        "multi_subject_items": multi_subject,
        "repeated_predicate_items": repeated_predicate,
        "criteria": {
            "max_triples": max_triples,
            "single_subject": True,
            "unique_predicates": True,
            "supported_predicate_count": len(WEBNLG_SUPPORTED_PREDS),
        },
    }

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--data-dir", default="bench/data")
    ap.add_argument("--out", default="bench/results/real_benchmark_profile.json")
    ap.add_argument("--max-e2e-slots", type=int, default=9)
    ap.add_argument("--max-webnlg-triples", type=int, default=3)
    args = ap.parse_args()

    data_dir = Path(args.data_dir)
    report = {"e2e": {}, "webnlg": {}}

    for path in sorted(data_dir.glob("real_gem_e2e_*.jsonl")):
        split = path.stem.replace("real_gem_e2e_", "")
        report["e2e"][split] = profile_e2e(read_jsonl(path), args.max_e2e_slots)

    for path in sorted(data_dir.glob("real_gem_webnlg_*.jsonl")):
        split = path.stem.replace("real_gem_webnlg_", "")
        report["webnlg"][split] = profile_webnlg(read_jsonl(path), args.max_webnlg_triples)

    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(report, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps(report, indent=2, ensure_ascii=False))

if __name__ == "__main__":
    main()
