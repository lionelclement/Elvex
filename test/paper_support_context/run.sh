#!/usr/bin/env bash
set -uo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

ELVEX="${1:-./bin/elvex}"

MAX_N="${MAX_N:-7}"
MAX_ITEMS="${MAX_ITEMS:-50000}"

FULL_RULES="$HERE/support_full.rules"
NOCTX_RULES="$HERE/support_no_context.rules"
LEXICON="$HERE/support.lexicon"

if [[ ! -x "$ELVEX" ]]; then
    echo "ERROR: Elvex binary not executable: $ELVEX" >&2
    exit 1
fi

for f in "$FULL_RULES" "$NOCTX_RULES" "$LEXICON"; do
    if [[ ! -f "$f" ]]; then
        echo "ERROR: missing file: $f" >&2
        exit 1
    fi
done

# Bash's built-in time is used so that Elvex stderr can remain in
# the .metrics file while timing information is written separately.
#
# Values are in seconds.
TIMEFORMAT=$'real\t%R\nuser\t%U\nsys\t%S'

echo "Elvex:      $ELVEX"
echo "MAX_N:      $MAX_N"
echo "MAX_ITEMS:  $MAX_ITEMS"
echo

failures=0

for mode in full no_context; do
    if [[ "$mode" == "full" ]]; then
        RULES="$FULL_RULES"
    else
        RULES="$NOCTX_RULES"
    fi

    for n in $(seq 1 "$MAX_N"); do
        INPUT="$HERE/support_N${n}.input"
        OUT="$HERE/${mode}_N${n}.out"
        METRICS="$HERE/${mode}_N${n}.metrics"
        TIMEFILE="$HERE/${mode}_N${n}.time"
        STATUS="$HERE/${mode}_N${n}.status"

        if [[ ! -f "$INPUT" ]]; then
            echo "ERROR: missing input: $INPUT" >&2
            echo "missing_input" > "$STATUS"
            failures=1
            continue
        fi

        echo "Running $mode N=$n (max-items=$MAX_ITEMS) ..."

        : > "$OUT"
        : > "$METRICS"
        : > "$TIMEFILE"

        if {
            time env ELVEX_METRIC_ID="${mode}_N${n}" \
                "$ELVEX" \
                    --max-items "$MAX_ITEMS" \
                    --rules-file "$RULES" \
                    --lexicon-file "$LEXICON" \
                    --input-file "$INPUT" \
                    > "$OUT" \
                    2> "$METRICS"
        } 2> "$TIMEFILE"
        then
            echo "ok" > "$STATUS"
        else
            rc=$?
            echo "failed:$rc" > "$STATUS"
            failures=1
            echo "  FAILED ($mode N=$n, exit=$rc)" >&2
            tail -5 "$METRICS" >&2 || true
        fi
    done
done

echo
python3 "$HERE/analyze.py" "$MAX_N"

echo
echo "Done. Results: $HERE/results.tsv"

if [[ "$failures" -ne 0 ]]; then
    echo "Some runs failed; see *.status, *.metrics and *.time files." >&2
    exit 2
fi
