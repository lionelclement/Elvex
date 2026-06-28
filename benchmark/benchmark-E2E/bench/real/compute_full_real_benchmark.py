#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path
from typing import Any

MR_RE = re.compile(r"\s*([A-Za-z][A-Za-z0-9_ ]*)\s*\[([^\]]*)\]\s*")

def read_jsonl(path: Path) -> list[dict[str, Any]]:
    if not path.exists():
        return []
    return [json.loads(line) for line in path.open(encoding="utf-8") if line.strip()]

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
        slot = m.group(1).strip().replace(" ", "")
        if slot == "customerrating":
            slot = "customerRating"
        slots[slot] = clean_value(m.group(2))
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

def unit_count(dataset: str, row: dict[str, Any]) -> int:
    if dataset == "e2e":
        slots = parse_e2e_mr(row.get("mr"))
        return len(slots or {})
    triples = parse_webnlg_source(row.get("source")) or parse_webnlg_source(row.get("raw"))
    return len(triples)

def pct(x: float) -> float:
    return round(100.0 * x, 1)

def load_metrics(path: Path) -> dict[str, Any]:
    if not path.exists():
        raise SystemExit(f"Missing metrics file: {path}")
    return json.loads(path.read_text(encoding="utf-8"))

def make_report(args: argparse.Namespace, dataset: str) -> dict[str, Any]:
    split = args.split
    data_path = Path(args.data_dir) / f"real_gem_{dataset}_{split}.jsonl"
    if dataset == "e2e":
        supported_path = Path("bench/e2e") / f"e2e_real_supported_{split}.jsonl"
        metrics_path = Path(args.results_dir) / f"e2e_metrics_real_supported_{split}_best.json"
        unit_name = "slots"
        unit_metric = "total_slots"
        omitted_metric = "omitted_slots"
    else:
        supported_path = Path("bench/webnlg") / f"webnlg_real_supported_{split}.jsonl"
        metrics_path = Path(args.results_dir) / f"webnlg_metrics_real_supported_{split}_best.json"
        unit_name = "triples"
        unit_metric = "total_triples"
        omitted_metric = "omitted_triples"

    source_rows = read_jsonl(data_path)
    supported_rows = read_jsonl(supported_path)
    supported_metrics = load_metrics(metrics_path)

    source_inputs = len(source_rows)
    covered_inputs = int(supported_metrics.get("total_inputs", len(supported_rows)))
    generated_inputs = int(round(float(supported_metrics.get("coverage", 0.0)) * covered_inputs))
    valid_items = int(round(float(supported_metrics.get("item_validity", 0.0)) * covered_inputs))

    source_units = sum(unit_count(dataset, row) for row in source_rows)
    covered_units = int(supported_metrics.get(unit_metric, 0))
    omitted_units_covered = int(supported_metrics.get(omitted_metric, 0))
    preserved_units_covered = covered_units - omitted_units_covered

    return {
        "dataset": dataset,
        "split": split,
        "unit_name": unit_name,
        "source_inputs": source_inputs,
        "covered_inputs": covered_inputs,
        "generated_inputs": generated_inputs,
        "valid_items_on_covered": valid_items,
        "coverage_of_source": covered_inputs / source_inputs if source_inputs else 0.0,
        "generation_success_on_covered": generated_inputs / covered_inputs if covered_inputs else 0.0,
        "validity_on_covered": valid_items / covered_inputs if covered_inputs else 0.0,
        "source_units": source_units,
        "covered_units": covered_units,
        "preserved_units_on_covered": preserved_units_covered,
        "preservation_on_covered": preserved_units_covered / covered_units if covered_units else 0.0,
        "global_unit_preservation_lower_bound": preserved_units_covered / source_units if source_units else 0.0,
        "avg_outputs_per_covered_input": supported_metrics.get("avg_outputs_per_input", 0.0),
        "avg_runtime_ms_on_covered": supported_metrics.get("avg_runtime_ms", 0.0),
        "mode": supported_metrics.get("mode", "unknown"),
        "paths": {
            "source": str(data_path),
            "supported": str(supported_path),
            "supported_metrics": str(metrics_path),
        },
    }

def write_tex_table(reports: list[dict[str, Any]], out: Path) -> None:
    labels = {"e2e": "E2E/GEM", "webnlg": "WebNLG/GEM"}
    lines = [
        r"\begin{tabular}{@{}lrrrrrr@{}}",
        r"\toprule",
        r"Data & Source & Covered & Cov. & Units & Pres. & Global \\",
        r"\midrule",
    ]
    for r in reports:
        lines.append(
            f"{labels.get(r['dataset'], r['dataset'])} {r['split']} & "
            f"{r['source_inputs']} & {r['covered_inputs']} & {pct(r['coverage_of_source'])} & "
            f"{r['covered_units']} {r['unit_name']} & {pct(r['preservation_on_covered'])} & "
            f"{pct(r['global_unit_preservation_lower_bound'])} \\\\"
        )
    lines += [
        r"\bottomrule",
        r"\end{tabular}",
        "",
        r"% Cov. = covered/source inputs.",
        r"% Pres. = unit preservation on the covered subset.",
        r"% Global = preserved covered units / all source units; unsupported inputs are counted as not preserved.",
    ]
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text("\n".join(lines) + "\n", encoding="utf-8")

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--split", default="test")
    ap.add_argument("--data-dir", default="bench/data")
    ap.add_argument("--results-dir", default="bench/results")
    ap.add_argument("--out", default=None)
    ap.add_argument("--tex", default=None)
    args = ap.parse_args()

    reports = [make_report(args, "e2e"), make_report(args, "webnlg")]
    summary = {"split": args.split, "reports": reports}

    out = Path(args.out or f"bench/results/full_real_benchmark_{args.split}.json")
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(summary, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")

    tex = Path(args.tex or f"bench/results/full_real_benchmark_{args.split}.tex")
    write_tex_table(reports, tex)

    print(json.dumps(summary, indent=2, ensure_ascii=False))
    print(f"wrote {out}")
    print(f"wrote {tex}")

if __name__ == "__main__":
    main()
