#!/usr/bin/env bash
set -euo pipefail

# Downloads GEM/e2e_nlg test split, deduplicates by MR, builds inputs and grammar.
# Does not run Elvex.
python rerun_e2e_gem.py \
  --scripts-dir scripts \
  --work-dir runs/e2e_gem_full
