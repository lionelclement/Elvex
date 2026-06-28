#!/usr/bin/env bash
set -euo pipefail

# Full exhaustive run. Requires elvex on PATH.
# This may be expensive because it collects all compatible outputs for every input.
cmd=(
  python rerun_e2e_gem.py
  --scripts-dir scripts
  --work-dir runs/e2e_gem_full
  --run-generation
  --elvex-bin "${ELVEX_BIN:-elvex}"
  --max-length "${ELVEX_MAX_LENGTH:-80}"
)

if [[ -n "${ELVEX_MAX_TIME:-}" ]]; then
  cmd+=(--max-time "$ELVEX_MAX_TIME")
fi
if [[ -n "${ELVEX_MAX_ITEMS:-}" ]]; then
  cmd+=(--max-items-elvex "$ELVEX_MAX_ITEMS")
fi

"${cmd[@]}"
