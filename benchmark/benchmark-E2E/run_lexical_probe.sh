#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-/usr/local/bin/elvex}"
PREFIX="grammar/lexical_probe/lexical_probe"

python3 bench/lexical_probe/make_probe_inputs.py \
  --items bench/lexical_probe/items.jsonl \
  --out-dir bench/lexical_probe/inputs \
  --manifest bench/lexical_probe/manifest.jsonl

touch "${PREFIX}.macros" "${PREFIX}.pattern" "${PREFIX}.morpho"

elvexlexicon \
  --compacted-lexicon-file "$PREFIX" \
  --macros-file "${PREFIX}.macros" \
  --pattern-file "${PREFIX}.pattern" \
  --morpho-file "${PREFIX}.morpho" \
  build

python3 bench/lexical_probe/run_probe.py \
  --manifest bench/lexical_probe/manifest.jsonl \
  --prefix "$PREFIX" \
  --elvex-bin "$ELVEX_BIN" \
  --out bench/results/lexical_probe_outputs.jsonl

python3 bench/lexical_probe/evaluate_probe.py \
  --outputs bench/results/lexical_probe_outputs.jsonl \
  --metrics bench/results/lexical_probe_metrics.json \
  --details bench/results/lexical_probe_details.jsonl

python3 bench/lexical_probe/make_probe_table.py \
  --metrics bench/results/lexical_probe_metrics.json \
  --out bench/results/lexical_probe_table.tex

echo
echo "Manifest: bench/lexical_probe/manifest.jsonl"
echo "Outputs:  bench/results/lexical_probe_outputs.jsonl"
echo "Metrics:  bench/results/lexical_probe_metrics.json"
echo "Details:  bench/results/lexical_probe_details.jsonl"
echo "Table:    bench/results/lexical_probe_table.tex"
