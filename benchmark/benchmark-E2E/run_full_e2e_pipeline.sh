#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-elvex}"
PREFIX="grammar/e2e/e2e"

python3 bench/e2e/download_gem_e2e.py --out-dir bench/data --trust-remote-code

if [ -f bench/data/gem_e2e_validation.jsonl ]; then
  SPLIT_FILE="bench/data/gem_e2e_validation.jsonl"
elif [ -f bench/data/gem_e2e_dev.jsonl ]; then
  SPLIT_FILE="bench/data/gem_e2e_dev.jsonl"
else
  SPLIT_FILE="$(ls bench/data/gem_e2e_*.jsonl | head -n 1)"
fi

python3 bench/e2e/select_e2e_fragment.py \
  --input "$SPLIT_FILE" \
  --out bench/e2e/e2e_fragment_100.jsonl \
  --n 100 \
  --seed 13

python3 bench/e2e/make_elvex_inputs.py \
  --items bench/e2e/e2e_fragment_100.jsonl \
  --input-dir bench/e2e/inputs \
  --manifest bench/e2e/e2e_manifest_100.jsonl \
  --head DESCRIBE_RESTAURANT \
  --symbol Axiom

bash grammar/e2e/build_lexicon.sh "$PREFIX"

python3 bench/e2e/run_elvex_benchmark.py \
  --manifest bench/e2e/e2e_manifest_100.jsonl \
  --prefix "$PREFIX" \
  --elvex-bin "$ELVEX_BIN" \
  --out bench/results/e2e_outputs_100_all.jsonl \
  --all-outputs

python3 bench/e2e/evaluate_slots.py \
  --outputs bench/results/e2e_outputs_100_all.jsonl \
  --metrics bench/results/e2e_metrics_100_best.json \
  --details bench/results/e2e_details_100_best.jsonl \
  --best-output

python3 bench/e2e/make_latex_table.py \
  --metrics bench/results/e2e_metrics_100_best.json \
  --out bench/results/e2e_table_100.tex
