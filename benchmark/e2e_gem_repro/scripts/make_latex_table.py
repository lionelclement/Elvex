#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path

def pct(x: float) -> str:
    return f"{100*x:.1f}"

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--metrics", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--dataset-name", default="E2E/GEM fragment")
    args = ap.parse_args()

    m = json.loads(Path(args.metrics).read_text(encoding="utf-8"))
    tex = rf"""
\begin{{table}}[t]
\small
\centering
\begin{{tabular}}{{lrrrr}}
\hline
Dataset & Inputs & Coverage & Slot accuracy & SER \\
\hline
{args.dataset_name} & {m['total_inputs']} & {pct(m['coverage'])} & {pct(m['slot_accuracy'])} & {pct(m['slot_omission_rate'])} \\
\hline
\end{{tabular}}
\caption{{Benchmark-style data-to-text evaluation on a cleaned E2E/GEM fragment. SER reports slot omissions in the selected output.}}
\label{{tab:e2e-gem-results}}
\end{{table}}
""".strip() + "\n"

    Path(args.out).parent.mkdir(parents=True, exist_ok=True)
    Path(args.out).write_text(tex, encoding="utf-8")
    print(tex)

if __name__ == "__main__":
    main()
