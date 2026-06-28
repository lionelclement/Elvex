#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-elvex}"
N="${N:-6420}"
MAX_TRIPLES="${MAX_TRIPLES:-3}"
SEED="${SEED:-23}"
PREFIX="grammar/webnlg/webnlg"
PREPARED_N="6420"

mkdir -p bench/webnlg bench/results grammar/webnlg

if [ "$N" != "$PREPARED_N" ]; then
  echo "This autonomous patch ships prepared relational N=$PREPARED_N." >&2
  echo "Run with N=$PREPARED_N, or regenerate the relational fragment from source data." >&2
  exit 1
fi

if [ ! -f "bench/webnlg/webnlg_fragment_relational_${PREPARED_N}.jsonl" ]; then
  echo "ERROR: missing prepared fragment bench/webnlg/webnlg_fragment_relational_${PREPARED_N}.jsonl." >&2
  exit 1
fi

python3 bench/webnlg/build_relational_lexicon.py \
  --items "bench/webnlg/webnlg_fragment_relational_${N}.jsonl" \
  --out grammar/webnlg/webnlg.lexicon

python3 bench/webnlg/make_webnlg_inputs_relational.py \
  --items "bench/webnlg/webnlg_fragment_relational_${N}.jsonl" \
  --input-dir "bench/webnlg/inputs_relational_${N}" \
  --manifest "bench/webnlg/webnlg_manifest_relational_${N}.jsonl" \
  --symbol Axiom

bash grammar/webnlg/build_lexicon.sh "$PREFIX"

python3 bench/webnlg/run_webnlg_benchmark.py \
  --manifest "bench/webnlg/webnlg_manifest_relational_${N}.jsonl" \
  --prefix "$PREFIX" \
  --elvex-bin "$ELVEX_BIN" \
  --out "bench/results/webnlg_outputs_relational_${N}_all.jsonl" \
  --all-outputs

python3 bench/webnlg/evaluate_triples.py \
  --outputs "bench/results/webnlg_outputs_relational_${N}_all.jsonl" \
  --metrics "bench/results/webnlg_metrics_relational_${N}_best.json" \
  --details "bench/results/webnlg_details_relational_${N}_best.jsonl" \
  --best-output

python3 bench/webnlg/make_latex_table.py \
  --metrics "bench/results/webnlg_metrics_relational_${N}_best.json" \
  --out "bench/results/webnlg_table_relational_${N}.tex" \
  --dataset-name "WebNLG relational controlled fragment"
