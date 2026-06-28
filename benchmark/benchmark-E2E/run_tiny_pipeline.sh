#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-elvex}"
PREFIX="grammar/e2e/e2e"

python3 bench/e2e/make_elvex_inputs.py \
  --items bench/e2e/tiny_items.jsonl \
  --input-dir bench/e2e/inputs \
  --manifest bench/e2e/tiny_manifest.jsonl \
  --head DESCRIBE_RESTAURANT \
  --symbol Axiom

bash grammar/e2e/build_lexicon.sh "$PREFIX"

python3 bench/e2e/run_elvex_benchmark.py \
  --manifest bench/e2e/tiny_manifest.jsonl \
  --prefix "$PREFIX" \
  --elvex-bin "$ELVEX_BIN" \
  --out bench/results/tiny_outputs_all.jsonl \
  --all-outputs

python3 bench/e2e/evaluate_slots.py \
  --outputs bench/results/tiny_outputs_all.jsonl \
  --metrics bench/results/tiny_metrics_best.json \
  --details bench/results/tiny_details_best.jsonl \
  --best-output
