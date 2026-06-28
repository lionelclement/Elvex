#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-/usr/local/bin/elvex}"
SPLIT="${SPLIT:-test}"
N="${N:-0}"
MAX_TRIPLES="${MAX_TRIPLES:-3}"
PREFIX="grammar/webnlg/webnlg"
DATA="bench/data/real_gem_webnlg_${SPLIT}.jsonl"
ITEMS="bench/webnlg/webnlg_real_supported_${SPLIT}.jsonl"

if [ ! -f "$DATA" ]; then
  echo "Missing $DATA. Run: bash run_real_benchmark_profile.sh" >&2
  exit 1
fi

python3 bench/real/select_supported_real_items.py \
  --dataset webnlg \
  --input "$DATA" \
  --out "$ITEMS" \
  --n "$N" \
  --max-webnlg-triples "$MAX_TRIPLES" \
  --summary "bench/results/webnlg_real_supported_${SPLIT}_selection.json"

python3 bench/webnlg/build_relational_lexicon.py \
  --items "$ITEMS" \
  --out grammar/webnlg/webnlg.lexicon

python3 bench/webnlg/make_webnlg_inputs_relational.py \
  --items "$ITEMS" \
  --input-dir "bench/webnlg/inputs_real_supported_${SPLIT}" \
  --manifest "bench/webnlg/webnlg_manifest_real_supported_${SPLIT}.jsonl" \
  --symbol Axiom

bash grammar/webnlg/build_lexicon.sh "$PREFIX"

python3 bench/webnlg/run_webnlg_benchmark.py \
  --manifest "bench/webnlg/webnlg_manifest_real_supported_${SPLIT}.jsonl" \
  --prefix "$PREFIX" \
  --elvex-bin "$ELVEX_BIN" \
  --out "bench/results/webnlg_outputs_real_supported_${SPLIT}_all.jsonl" \
  --all-outputs

python3 bench/webnlg/evaluate_triples.py \
  --outputs "bench/results/webnlg_outputs_real_supported_${SPLIT}_all.jsonl" \
  --metrics "bench/results/webnlg_metrics_real_supported_${SPLIT}_best.json" \
  --details "bench/results/webnlg_details_real_supported_${SPLIT}_best.jsonl" \
  --best-output

python3 bench/webnlg/make_latex_table.py \
  --metrics "bench/results/webnlg_metrics_real_supported_${SPLIT}_best.json" \
  --out "bench/results/webnlg_table_real_supported_${SPLIT}.tex" \
  --dataset-name "WebNLG/GEM supported subset"
