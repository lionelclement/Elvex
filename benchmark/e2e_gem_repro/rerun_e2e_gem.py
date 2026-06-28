#!/usr/bin/env python3
"""Re-run the E2E/GEM grammar scalability experiment.

This script downloads GEM/e2e_nlg from Hugging Face, extracts the distinct MRs
in a split (default: test), builds the full E2E items/manifest/input files,
optionally builds the Elvex grammar files, optionally runs Elvex, and computes
first-output and best-in-forest slot-preservation metrics.

Typical use from the directory containing the existing e2e scripts:

  python rerun_e2e_gem.py \
    --scripts-dir ./e2e \
    --work-dir ./runs/e2e_gem_full \
    --elvex-bin elvex \
    --grammar-prefix grammar/e2e/e2e_full \
    --run-generation

Without --run-generation, the script stops after downloading, deduplicating,
and building the inputs/manifest/grammar, which is useful for checking the
1,847 inputs and 11,428 slots claim.
"""
from __future__ import annotations

import argparse
import csv
import importlib.util
import json
import re
import shutil
import subprocess
import sys
import time
from collections import OrderedDict
from pathlib import Path
from typing import Any, Iterable

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
    "rating": "customerRating",
}
SUPPORTED_SLOTS = {
    "name", "eatType", "food", "priceRange", "area",
    "familyFriendly", "near", "customerRating",
}


def clean_value(s: Any) -> str:
    s = str(s).replace("_", " ").strip()
    s = re.sub(r"\s+", " ", s)
    if len(s) >= 2 and ((s[0] == s[-1] == '"') or (s[0] == s[-1] == "'")):
        s = s[1:-1].strip()
    return s


def normalize_slot_name(s: str) -> str:
    key = re.sub(r"\s+", " ", s.strip().lower())
    key_no_space = key.replace(" ", "")
    return SLOT_NORMALIZATION.get(key, SLOT_NORMALIZATION.get(key_no_space, s.strip().replace(" ", "")))


def parse_e2e_mr(mr: Any) -> dict[str, str]:
    if not isinstance(mr, str):
        raise ValueError(f"MR is not a string: {type(mr).__name__}")
    slots: dict[str, str] = {}
    for part in mr.split(","):
        part = part.strip()
        if not part:
            continue
        m = MR_RE.fullmatch(part)
        if not m:
            raise ValueError(f"Cannot parse MR component: {part!r} in MR {mr!r}")
        slot = normalize_slot_name(m.group(1))
        if slot not in SUPPORTED_SLOTS:
            raise ValueError(f"Unsupported slot {slot!r} in MR {mr!r}")
        slots[slot] = clean_value(m.group(2))
    return slots


def load_hf_split(dataset_name: str, split: str) -> list[dict[str, Any]]:
    try:
        from datasets import load_dataset  # type: ignore
    except ImportError as e:
        raise SystemExit(
            "Missing dependency: datasets. Install with `pip install datasets` "
            "or run in an environment where Hugging Face datasets is available."
        ) from e

    # Newer versions of datasets may require trust_remote_code for older loaders.
    try:
        ds = load_dataset(dataset_name, split=split)
    except Exception:
        ds = load_dataset(dataset_name, split=split, trust_remote_code=True)
    return [dict(row) for row in ds]


def get_mr(row: dict[str, Any]) -> str:
    for key in ("input", "mr", "meaning_representation"):
        val = row.get(key)
        if isinstance(val, str) and "[" in val and "]" in val:
            return val
    raise KeyError(f"Could not find an MR field in row keys: {sorted(row)}")


def get_reference(row: dict[str, Any]) -> str | None:
    for key in ("target", "ref", "reference", "output"):
        val = row.get(key)
        if isinstance(val, str) and val.strip():
            return val
    return None


def get_row_id(row: dict[str, Any], fallback: str) -> str:
    for key in ("gem_id", "id", "eid", "example_id"):
        val = row.get(key)
        if val is not None and str(val).strip():
            return str(val)
    return fallback


def distinct_mr_items(rows: Iterable[dict[str, Any]], split: str) -> list[dict[str, Any]]:
    """Aggregate repeated references under each distinct MR, preserving order."""
    by_mr: "OrderedDict[str, dict[str, Any]]" = OrderedDict()
    for i, row in enumerate(rows, 1):
        mr = get_mr(row)
        ref = get_reference(row)
        if mr not in by_mr:
            slots = parse_e2e_mr(mr)
            by_mr[mr] = {
                "id": get_row_id(row, f"{split}-{i}"),
                "fragment_id": f"e2e_full_{len(by_mr) + 1:05d}",
                "split": split,
                "mr": mr,
                "expected_slots": slots,
                "n_slots": len(slots),
                "references": [],
            }
        if ref is not None:
            by_mr[mr]["references"].append(ref)
    return list(by_mr.values())


def write_jsonl(path: Path, rows: Iterable[dict[str, Any]]) -> int:
    path.parent.mkdir(parents=True, exist_ok=True)
    n = 0
    with path.open("w", encoding="utf-8") as f:
        for row in rows:
            f.write(json.dumps(row, ensure_ascii=False) + "\n")
            n += 1
    return n


def read_jsonl(path: Path) -> list[dict[str, Any]]:
    with path.open("r", encoding="utf-8") as f:
        return [json.loads(line) for line in f if line.strip()]


def run(cmd: list[str], cwd: Path | None = None) -> None:
    print("$ " + " ".join(map(str, cmd)))
    subprocess.run(cmd, cwd=str(cwd) if cwd else None, check=True)


def copy_or_locate_script(scripts_dir: Path, name: str) -> Path:
    p = scripts_dir / name
    if not p.exists():
        raise FileNotFoundError(f"Missing required helper script: {p}")
    return p


def summarize_items(items: list[dict[str, Any]]) -> dict[str, Any]:
    slot_counts: dict[str, int] = {s: 0 for s in sorted(SUPPORTED_SLOTS)}
    total_slots = 0
    for item in items:
        slots = item["expected_slots"]
        total_slots += len(slots)
        for s in slots:
            slot_counts[s] = slot_counts.get(s, 0) + 1
    return {
        "inputs": len(items),
        "total_slots": total_slots,
        "slot_counts": slot_counts,
        "avg_slots_per_input": total_slots / len(items) if items else 0.0,
        "references": sum(len(x.get("references", [])) for x in items),
    }


def make_table(metrics_first: dict[str, Any], metrics_best: dict[str, Any]) -> str:
    def pct(x: float) -> str:
        return f"{100.0 * x:.1f}"
    inp = metrics_first["total_inputs"]
    slots = metrics_first["total_slots"]
    out = metrics_first["avg_outputs_per_input"]
    return "\n".join([
        r"\begin{tabular}{@{}lrrrrrr@{}}",
        r"\toprule",
        r"Mode & Inp. & Cov. & Slots & Acc. & SER & Out. \\",
        r"\midrule",
        f"First output & {inp} & {pct(metrics_first['coverage'])} & {slots} & {pct(metrics_first['slot_accuracy'])} & {pct(metrics_first['slot_omission_rate'])} & {out:.1f} \\",
        f"Best in forest & {metrics_best['total_inputs']} & {pct(metrics_best['coverage'])} & {metrics_best['total_slots']} & {pct(metrics_best['slot_accuracy'])} & {pct(metrics_best['slot_omission_rate'])} & {metrics_best['avg_outputs_per_input']:.1f} \\",
        r"\bottomrule",
        r"\end{tabular}",
        "",
    ])


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--dataset", default="GEM/e2e_nlg")
    ap.add_argument("--split", default="test")
    ap.add_argument("--scripts-dir", default="scripts", help="Directory containing build_full_e2e_grammar.py, make_full_e2e_inputs.py, run_elvex_benchmark.py, evaluate_slots.py")
    ap.add_argument("--work-dir", default="runs/e2e_gem_full")
    ap.add_argument("--grammar-prefix", default=None, help="Prefix used by Elvex: .rules and .lexicon. Default: <work-dir>/grammar/e2e_full")
    ap.add_argument("--elvex-bin", default="elvex")
    ap.add_argument("--run-generation", action="store_true", help="Run Elvex and compute first/best metrics. If absent, only prepare data and grammar.")
    ap.add_argument("--max-items", type=int, default=None, help="Limit the number of MRs after deduplication, for smoke tests.")
    ap.add_argument("--max-length", default="80")
    ap.add_argument("--max-time", default=None)
    ap.add_argument("--max-items-elvex", default=None, help="Forwarded to Elvex as --max-items during generation.")
    ap.add_argument("--expect-inputs", type=int, default=1847)
    ap.add_argument("--expect-slots", type=int, default=11428)
    args = ap.parse_args()

    scripts_dir = Path(args.scripts_dir).resolve()
    work_dir = Path(args.work_dir).resolve()
    work_dir.mkdir(parents=True, exist_ok=True)
    if args.grammar_prefix is None:
        args.grammar_prefix = str(work_dir / "grammar" / "e2e_full")

    print(f"Downloading/loading {args.dataset!r}, split={args.split!r}")
    rows = load_hf_split(args.dataset, args.split)
    raw_path = work_dir / f"{args.split}_raw_rows.jsonl"
    write_jsonl(raw_path, rows)

    items = distinct_mr_items(rows, args.split)
    if args.max_items is not None:
        items = items[: args.max_items]
    items_path = work_dir / f"e2e_gem_{args.split}_distinct_mrs.jsonl"
    write_jsonl(items_path, items)

    summary = summarize_items(items)
    summary_path = work_dir / "dataset_summary.json"
    summary_path.write_text(json.dumps(summary, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    print(json.dumps(summary, indent=2, ensure_ascii=False))

    if args.max_items is None:
        if summary["inputs"] != args.expect_inputs:
            print(f"WARNING: expected {args.expect_inputs} distinct inputs, got {summary['inputs']}", file=sys.stderr)
        if summary["total_slots"] != args.expect_slots:
            print(f"WARNING: expected {args.expect_slots} slots, got {summary['total_slots']}", file=sys.stderr)

    make_inputs = copy_or_locate_script(scripts_dir, "make_full_e2e_inputs.py")
    build_grammar = copy_or_locate_script(scripts_dir, "build_full_e2e_grammar.py")
    run_bench = copy_or_locate_script(scripts_dir, "run_elvex_benchmark.py")
    eval_slots = copy_or_locate_script(scripts_dir, "evaluate_slots.py")

    input_dir = work_dir / "inputs_full_test"
    manifest_path = work_dir / "manifest_full_test.jsonl"
    run([sys.executable, str(make_inputs), "--items", str(items_path), "--input-dir", str(input_dir), "--manifest", str(manifest_path)])

    # build_full_e2e_grammar.py writes .rules and .lexicon.
    # This pipeline intentionally does not pass --macros-file to Elvex.
    prefix = Path(args.grammar_prefix)
    rules_out = prefix.with_suffix(".rules")
    lexicon_out = prefix.with_suffix(".lexicon")
    rules_out.parent.mkdir(parents=True, exist_ok=True)
    run([sys.executable, str(build_grammar), "--items", str(items_path), "--rules-out", str(rules_out), "--lexicon-out", str(lexicon_out)])

    if not args.run_generation:
        print("Prepared data, manifest, inputs, grammar rules, and lexicon. Add --run-generation to run Elvex and metrics.")
        return

    if shutil.which(args.elvex_bin) is None:
        raise SystemExit(f"Cannot find Elvex binary {args.elvex_bin!r} on PATH. Pass --elvex-bin or install it.")

    outputs_path = work_dir / "outputs_full_test_all.jsonl"
    bench_cmd = [
        sys.executable, str(run_bench),
        "--manifest", str(manifest_path),
        "--out", str(outputs_path),
        "--prefix", str(prefix.with_suffix("")),
        "--elvex-bin", args.elvex_bin,
        "--strategy", "exhaustive",
        "--max-length", str(args.max_length),
        "--all-outputs",
    ]
    if args.max_time is not None:
        bench_cmd += ["--max-time", str(args.max_time)]
    if args.max_items_elvex is not None:
        bench_cmd += ["--max-items", str(args.max_items_elvex)]
    run(bench_cmd)

    metrics_first = work_dir / "metrics_first_output.json"
    details_first = work_dir / "details_first_output.jsonl"
    run([sys.executable, str(eval_slots), "--outputs", str(outputs_path), "--metrics", str(metrics_first), "--details", str(details_first)])

    metrics_best = work_dir / "metrics_best_in_forest.json"
    details_best = work_dir / "details_best_in_forest.jsonl"
    run([sys.executable, str(eval_slots), "--outputs", str(outputs_path), "--metrics", str(metrics_best), "--details", str(details_best), "--best-output"])

    first = json.loads(metrics_first.read_text(encoding="utf-8"))
    best = json.loads(metrics_best.read_text(encoding="utf-8"))
    table = make_table(first, best)
    (work_dir / "table_e2e_gem_results.tex").write_text(table, encoding="utf-8")
    print(table)


if __name__ == "__main__":
    main()
