#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-elvex}"
N="${N:-5000}"
PREFIX="grammar/e2e/e2e"

if [ "$N" != "5000" ]; then
  echo "This autonomous patch ships the prepared E2E serious fragment with N=5000." >&2
  echo "Run with N=5000, or regenerate bench/e2e/e2e_serious_5000_items.jsonl." >&2
  exit 1
fi

mkdir -p bench/e2e bench/results grammar/e2e

python3 bench/e2e/make_e2e_factorized_inputs.py \
  --items bench/e2e/e2e_serious_5000_items.jsonl \
  --input-dir bench/e2e/inputs_serious_5000 \
  --manifest bench/e2e/e2e_manifest_serious_5000.jsonl \
  --symbol Axiom

bash grammar/e2e/build_lexicon.sh "$PREFIX" 2>/dev/null || true

python3 bench/e2e/run_elvex_benchmark.py \
  --manifest bench/e2e/e2e_manifest_serious_5000.jsonl \
  --prefix "$PREFIX" \
  --elvex-bin "$ELVEX_BIN" \
  --out bench/results/e2e_outputs_serious_5000_all.jsonl \
  --all-outputs

python3 bench/e2e/evaluate_slots.py \
  --outputs bench/results/e2e_outputs_serious_5000_all.jsonl \
  --metrics bench/results/e2e_metrics_serious_5000_best.json \
  --details bench/results/e2e_details_serious_5000_best.jsonl \
  --best-output

python3 bench/e2e/make_latex_table.py \
  --metrics bench/results/e2e_metrics_serious_5000_best.json \
  --out bench/results/e2e_table_serious_5000.tex \
  --dataset-name "E2E factorized controlled fragment"
