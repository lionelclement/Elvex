#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-/usr/local/bin/elvex}"
SPLIT="${SPLIT:-test}"

bash run_real_benchmark_profile.sh
SPLIT="$SPLIT" N="${E2E_N:-0}" bash run_e2e_real_supported_pipeline.sh "$ELVEX_BIN"
SPLIT="$SPLIT" N="${WEBNLG_N:-0}" MAX_TRIPLES="${MAX_TRIPLES:-3}" bash run_webnlg_real_supported_pipeline.sh "$ELVEX_BIN"

echo "Profile: bench/results/real_benchmark_profile.json"
echo "E2E supported metrics: bench/results/e2e_metrics_real_supported_${SPLIT}_best.json"
echo "WebNLG supported metrics: bench/results/webnlg_metrics_real_supported_${SPLIT}_best.json"
