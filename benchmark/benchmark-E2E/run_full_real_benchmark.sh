#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-/usr/local/bin/elvex}"
SPLIT="${SPLIT:-test}"
MAX_TRIPLES="${MAX_TRIPLES:-3}"
E2E_N="${E2E_N:-0}"
WEBNLG_N="${WEBNLG_N:-0}"

# Download/normalize the GEM datasets if needed, then profile full splits.
if [ ! -f "bench/data/real_gem_e2e_${SPLIT}.jsonl" ] || [ ! -f "bench/data/real_gem_webnlg_${SPLIT}.jsonl" ]; then
  python3 bench/real/download_real_benchmarks.py --out-dir bench/data
fi

python3 bench/real/profile_real_benchmarks.py \
  --data-dir bench/data \
  --out bench/results/real_benchmark_profile.json \
  --max-webnlg-triples "$MAX_TRIPLES"

# Run the current supported-subset pipelines on the chosen split.
SPLIT="$SPLIT" N="$E2E_N" bash run_e2e_real_supported_pipeline.sh "$ELVEX_BIN"
SPLIT="$SPLIT" N="$WEBNLG_N" MAX_TRIPLES="$MAX_TRIPLES" bash run_webnlg_real_supported_pipeline.sh "$ELVEX_BIN"

# Aggregate into full-split coverage metrics.
python3 bench/real/compute_full_real_benchmark.py \
  --split "$SPLIT" \
  --data-dir bench/data \
  --results-dir bench/results \
  --out "bench/results/full_real_benchmark_${SPLIT}.json" \
  --tex "bench/results/full_real_benchmark_${SPLIT}.tex"

echo
echo "Full split profile: bench/results/real_benchmark_profile.json"
echo "Full split summary: bench/results/full_real_benchmark_${SPLIT}.json"
echo "LaTeX table:        bench/results/full_real_benchmark_${SPLIT}.tex"
echo "E2E details:        bench/results/e2e_details_real_supported_${SPLIT}_best.jsonl"
echo "WebNLG details:     bench/results/webnlg_details_real_supported_${SPLIT}_best.jsonl"
