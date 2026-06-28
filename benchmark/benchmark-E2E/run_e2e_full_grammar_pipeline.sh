#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-/usr/local/bin/elvex}"
SPLIT="${SPLIT:-test}"
N="${N:-0}"
PREFIX="grammar/e2e/e2e_full"
DATA="bench/data/real_gem_e2e_${SPLIT}.jsonl"
ITEMS="bench/e2e/e2e_full_${SPLIT}.jsonl"

if [ ! -f "$DATA" ]; then
  echo "Missing $DATA. Run: bash run_download_real_datasets.sh" >&2
  exit 1
fi

python3 bench/e2e/select_full_e2e_items.py \
  --input "$DATA" \
  --out "$ITEMS" \
  --n "$N" \
  --summary "bench/results/e2e_full_${SPLIT}_selection.json"

python3 bench/e2e/build_full_e2e_grammar.py \
  --items "$ITEMS" \
  --lexicon-out grammar/e2e/e2e_full.lexicon \
  --rules-out grammar/e2e/e2e_full.rules


# Reuse the static morphology, pattern, and macro files from the existing E2E grammar.
cp grammar/e2e/e2e.macros grammar/e2e/e2e_full.macros
cp grammar/e2e/e2e.pattern grammar/e2e/e2e_full.pattern
cp grammar/e2e/e2e.morpho grammar/e2e/e2e_full.morpho

python3 bench/e2e/make_full_e2e_inputs.py \
  --items "$ITEMS" \
  --input-dir "bench/e2e/inputs_full_${SPLIT}" \
  --manifest "bench/e2e/e2e_manifest_full_${SPLIT}.jsonl" \
  --symbol Axiom

bash grammar/e2e/build_lexicon.sh "$PREFIX"

python3 bench/e2e/run_elvex_benchmark.py \
  --manifest "bench/e2e/e2e_manifest_full_${SPLIT}.jsonl" \
  --prefix "$PREFIX" \
  --elvex-bin "$ELVEX_BIN" \
  --out "bench/results/e2e_outputs_full_${SPLIT}_all.jsonl" \
  --all-outputs

python3 bench/e2e/evaluate_slots.py \
  --outputs "bench/results/e2e_outputs_full_${SPLIT}_all.jsonl" \
  --metrics "bench/results/e2e_metrics_full_${SPLIT}_best.json" \
  --details "bench/results/e2e_details_full_${SPLIT}_best.jsonl" \
  --best-output

python3 bench/e2e/make_latex_table.py \
  --metrics "bench/results/e2e_metrics_full_${SPLIT}_best.json" \
  --out "bench/results/e2e_table_full_${SPLIT}.tex" \
  --dataset-name "E2E/GEM full grammar"

echo
echo "Selection: bench/results/e2e_full_${SPLIT}_selection.json"
echo "Metrics:   bench/results/e2e_metrics_full_${SPLIT}_best.json"
echo "Details:   bench/results/e2e_details_full_${SPLIT}_best.jsonl"
echo "Table:     bench/results/e2e_table_full_${SPLIT}.tex"
