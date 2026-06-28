#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-/usr/local/bin/elvex}"
SPLIT="${SPLIT:-test}"
N="${N:-0}"
PREFIX="grammar/e2e/e2e"
DATA="bench/data/real_gem_e2e_${SPLIT}.jsonl"
ITEMS="bench/e2e/e2e_real_supported_${SPLIT}.jsonl"

if [ ! -f "$DATA" ]; then
  echo "Missing $DATA. Run: bash run_real_benchmark_profile.sh" >&2
  exit 1
fi

python3 bench/real/select_supported_real_items.py \
  --dataset e2e \
  --input "$DATA" \
  --out "$ITEMS" \
  --n "$N" \
  --summary "bench/results/e2e_real_supported_${SPLIT}_selection.json"

python3 bench/e2e/build_real_e2e_grammar.py \
  --items "$ITEMS" \
  --lexicon-out grammar/e2e/e2e.lexicon \
  --rules-out grammar/e2e/e2e.rules

python3 bench/e2e/make_e2e_factorized_inputs.py \
  --items "$ITEMS" \
  --input-dir "bench/e2e/inputs_real_supported_${SPLIT}" \
  --manifest "bench/e2e/e2e_manifest_real_supported_${SPLIT}.jsonl" \
  --symbol Axiom

bash grammar/e2e/build_lexicon.sh "$PREFIX"

python3 bench/e2e/run_elvex_benchmark.py \
  --manifest "bench/e2e/e2e_manifest_real_supported_${SPLIT}.jsonl" \
  --prefix "$PREFIX" \
  --elvex-bin "$ELVEX_BIN" \
  --out "bench/results/e2e_outputs_real_supported_${SPLIT}_all.jsonl" \
  --all-outputs

python3 bench/e2e/evaluate_slots.py \
  --outputs "bench/results/e2e_outputs_real_supported_${SPLIT}_all.jsonl" \
  --metrics "bench/results/e2e_metrics_real_supported_${SPLIT}_best.json" \
  --details "bench/results/e2e_details_real_supported_${SPLIT}_best.jsonl" \
  --best-output

python3 bench/e2e/make_latex_table.py \
  --metrics "bench/results/e2e_metrics_real_supported_${SPLIT}_best.json" \
  --out "bench/results/e2e_table_real_supported_${SPLIT}.tex" \
  --dataset-name "E2E/GEM supported subset"
