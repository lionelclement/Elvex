#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-/usr/local/bin/elvex}"
N_PER_PHENOMENON="${N_PER_PHENOMENON:-50}"
PREFIX="grammar/context/context"

python3 bench/context/make_context_probe.py \
  --out bench/context/context_probe_items.jsonl \
  --n-per-phenomenon "$N_PER_PHENOMENON" \
  --summary bench/results/context_probe_items_summary.json

python3 bench/context/build_context_grammar.py \
  --rules-out grammar/context/context.rules \
  --lexicon-out grammar/context/context.lexicon

python3 bench/context/make_context_inputs.py \
  --items bench/context/context_probe_items.jsonl \
  --input-dir bench/context/inputs \
  --manifest bench/context/context_probe_manifest.jsonl \
  --symbol Axiom

elvexlexicon \
  --compacted-lexicon-file "$PREFIX" \
  --macros-file "${PREFIX}.macros" \
  --pattern-file "${PREFIX}.pattern" \
  --morpho-file "${PREFIX}.morpho" \
  build

python3 bench/context/run_context_probe.py \
  --manifest bench/context/context_probe_manifest.jsonl \
  --prefix "$PREFIX" \
  --elvex-bin "$ELVEX_BIN" \
  --out bench/results/context_probe_outputs.jsonl \
  --all-outputs

python3 bench/context/evaluate_context_probe.py \
  --outputs bench/results/context_probe_outputs.jsonl \
  --metrics bench/results/context_probe_metrics_best.json \
  --details bench/results/context_probe_details_best.jsonl \
  --mode best

python3 bench/context/evaluate_context_probe.py \
  --outputs bench/results/context_probe_outputs.jsonl \
  --metrics bench/results/context_probe_metrics_first.json \
  --details bench/results/context_probe_details_first.jsonl \
  --mode first

python3 bench/context/make_context_table.py \
  --metrics bench/results/context_probe_metrics_best.json \
  --out bench/results/context_probe_table.tex

echo
echo "Items:   bench/context/context_probe_items.jsonl"
echo "Outputs: bench/results/context_probe_outputs.jsonl"
echo "Best:    bench/results/context_probe_metrics_best.json"
echo "First:   bench/results/context_probe_metrics_first.json"
echo "Table:   bench/results/context_probe_table.tex"
