#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-elvex}"
PREFIX="grammar/webnlg/webnlg"

python3 bench/webnlg/download_gem_webnlg.py \
  --out-dir bench/data \
  --trust-remote-code

if [ -f bench/data/gem_webnlg_validation.jsonl ]; then
  SPLIT_FILE="bench/data/gem_webnlg_validation.jsonl"
elif [ -f bench/data/gem_webnlg_dev.jsonl ]; then
  SPLIT_FILE="bench/data/gem_webnlg_dev.jsonl"
else
  SPLIT_FILE="$(ls bench/data/gem_webnlg_*.jsonl | head -n 1)"
fi

python3 bench/webnlg/select_webnlg_fragment.py \
  --input "$SPLIT_FILE" \
  --out bench/webnlg/webnlg_fragment_50.jsonl \
  --n 50 \
  --seed 17 \
  --max-triples 3 \
  --supported-only

python3 bench/webnlg/make_webnlg_inputs.py \
  --items bench/webnlg/webnlg_fragment_50.jsonl \
  --input-dir bench/webnlg/inputs \
  --manifest bench/webnlg/webnlg_manifest_50.jsonl \
  --symbol Axiom

bash grammar/webnlg/build_lexicon.sh "$PREFIX"

python3 bench/webnlg/run_webnlg_benchmark.py \
  --manifest bench/webnlg/webnlg_manifest_50.jsonl \
  --prefix "$PREFIX" \
  --elvex-bin "$ELVEX_BIN" \
  --out bench/results/webnlg_outputs_50_all.jsonl \
  --all-outputs

python3 bench/webnlg/evaluate_triples.py \
  --outputs bench/results/webnlg_outputs_50_all.jsonl \
  --metrics bench/results/webnlg_metrics_50_best.json \
  --details bench/results/webnlg_details_50_best.jsonl \
  --best-output

python3 bench/webnlg/make_latex_table.py \
  --metrics bench/results/webnlg_metrics_50_best.json \
  --out bench/results/webnlg_table_50.tex
