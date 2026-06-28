#!/usr/bin/env bash
set -euo pipefail

PREFIX="${1:-grammar/e2e/e2e}"

elvexlexicon \
  --compacted-lexicon-file "$PREFIX" \
  --macros-file "${PREFIX}.macros" \
  --pattern-file "${PREFIX}.pattern" \
  --morpho-file "${PREFIX}.morpho" \
  build

echo "Built compacted lexicon: ${PREFIX}.fsa and ${PREFIX}.tbl"
