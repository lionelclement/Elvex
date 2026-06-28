#!/usr/bin/env bash
set -euo pipefail

python3 bench/real/download_real_benchmarks.py --out-dir bench/data
python3 bench/real/profile_real_benchmarks.py \
  --data-dir bench/data \
  --out bench/results/real_benchmark_profile.json
