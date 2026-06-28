#!/usr/bin/env bash
set -euo pipefail

# Smoke test on 3 distinct MRs. Requires elvex on PATH.
python rerun_e2e_gem.py \
  --scripts-dir scripts \
  --work-dir runs/e2e_gem_smoke \
  --max-items 3 \
  --run-generation \
  --elvex-bin "${ELVEX_BIN:-elvex}" \
  --max-time "${ELVEX_MAX_TIME:-30}"
