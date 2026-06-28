#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-elvex}"
PREFIX="grammar/webnlg/webnlg"

python3 bench/webnlg/make_webnlg_inputs.py \
  --items bench/webnlg/tiny_items.jsonl \
  --input-dir bench/webnlg/inputs \
  --manifest bench/webnlg/tiny_manifest.jsonl \
  --symbol Axiom

bash grammar/webnlg/build_lexicon.sh "$PREFIX"

python3 bench/webnlg/run_webnlg_benchmark.py \
  --manifest bench/webnlg/tiny_manifest.jsonl \
  --prefix "$PREFIX" \
  --elvex-bin "$ELVEX_BIN" \
  --out bench/results/webnlg_tiny_outputs_all.jsonl \
  --all-outputs

python3 bench/webnlg/evaluate_triples.py \
  --outputs bench/results/webnlg_tiny_outputs_all.jsonl \
  --metrics bench/results/webnlg_tiny_metrics_best.json \
  --details bench/results/webnlg_tiny_details_best.jsonl \
  --best-output
