#!/usr/bin/env bash
set -euo pipefail
ELVEX_BIN="${1:?path/to/elvex required}"
FIXTURE="${2:?path/to/data/regression required}"
tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT
"$ELVEX_BIN" \
  --rules-file "$FIXTURE/01_required_sequence.rules" \
  --lexicon-file "$FIXTURE/01_required_sequence.lexicon" \
  --input-file "$FIXTURE/01_required_sequence.input" \
  --forest-only --progress --xml "$tmp/forest.xml" \
  > "$tmp/out" 2> "$tmp/err"
if [[ -s "$tmp/out" ]]; then
  echo "FAILED: --forest-only emitted sentences" >&2
  cat "$tmp/out" >&2
  exit 1
fi
if [[ ! -s "$tmp/forest.xml" ]]; then
  echo "FAILED: --xml did not write a forest" >&2
  exit 1
fi
if ! grep -q 'ELVEX_PROGRESS.*forest-only-done' "$tmp/err"; then
  echo "FAILED: --progress missing completion event" >&2
  cat "$tmp/err" >&2
  exit 1
fi
echo '[ OK ] forest-only / XML / progress'
