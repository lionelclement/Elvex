#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path

def pct(x: float) -> str:
    return f"{100*x:.1f}"

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--metrics", default="bench/results/lexical_probe_metrics.json")
    ap.add_argument("--out", default="bench/results/lexical_probe_table.tex")
    args = ap.parse_args()

    m = json.loads(Path(args.metrics).read_text(encoding="utf-8"))
    lines = [
        r"\begin{table}[t]",
        r"\centering",
        r"\footnotesize",
        r"\setlength{\tabcolsep}{4pt}",
        r"\begin{tabular}{@{}lrrrr@{}}",
        r"\toprule",
        r"Phenomenon & Items & Gen. & Acc. & Avg. out. \\",
        r"\midrule",
    ]
    labels = {
        "collocation": "Collocations",
        "support_verb": "Support verbs",
    }
    for ph, d in sorted(m["by_phenomenon"].items()):
        label = labels.get(ph, ph.replace("_", " ").title())
        lines.append(
            f"{label} & {d['items']} & {d['generated']} & {pct(d['accuracy_on_generated_items'])} & {d['avg_outputs_per_item']:.1f} \\\\"
        )
    lines.extend([
        r"\midrule",
        f"Total & {m['total_items']} & {m['generated_items']} & {pct(m['accuracy_on_generated_items'])} & {m['avg_outputs_per_item']:.1f} \\\\",
        r"\bottomrule",
        r"\end{tabular}",
        r"\caption{Targeted lexical-dependency probe. Each item specifies a",
        r"lexically licensed support-verb construction or collocation. Acc.",
        r"reports the percentage of generated items for which at least one",
        r"output matches the expected lexical realization.}",
        r"\label{tab:lexical-probe}",
        r"\end{table}",
    ])
    Path(args.out).parent.mkdir(parents=True, exist_ok=True)
    Path(args.out).write_text("\n".join(lines) + "\n", encoding="utf-8")
    print("\n".join(lines))

if __name__ == "__main__":
    main()
