#!/usr/bin/env bash
set -euo pipefail

ELVEX_BIN="${1:-/usr/local/bin/elvex}"

echo "== E2E factorized controlled benchmark =="
N=5000 bash run_e2e_serious_pipeline.sh "$ELVEX_BIN"

echo
echo "== WebNLG relational controlled benchmark =="
N=6420 MAX_TRIPLES=3 SEED=23 bash run_webnlg_relational_pipeline.sh "$ELVEX_BIN"

echo
echo "Results:"
echo "  bench/results/e2e_metrics_serious_5000_best.json"
echo "  bench/results/e2e_table_serious_5000.tex"
echo "  bench/results/webnlg_metrics_relational_6420_best.json"
echo "  bench/results/webnlg_table_relational_6420.tex"
