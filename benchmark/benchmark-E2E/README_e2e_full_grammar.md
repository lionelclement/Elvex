# Full E2E grammar pipeline

This branch is an attempt to replace the earlier supported-subset E2E probe with
a more serious closed-domain E2E grammar.

The previous E2E pipeline verbalized arbitrary slot/value pairs with generic
`slot_marker slot_value` rules.  The full grammar pipeline instead uses
slot-specific clauses:

- `SUBJECT`
- `EATTYPE_CLAUSE`
- `FOOD_CLAUSE`
- `PRICE_CLAUSE`
- `AREA_CLAUSE`
- `NEAR_CLAUSE`
- `FAMILY_CLAUSE`
- `RATING_CLAUSE`

The generated rules cover all combinations of the seven non-name E2E slots,
with or without `name`.  Inputs without `name` are realized with a generic
subject (`The restaurant`).

This is still a deliberately simple grammar.  It is not a neural E2E system and
does not try to match the reference style.  Its purpose is to test full-split
coverage and semantic preservation for a manually specified closed-domain
grammar.

## Run

From the `benchmark/` directory:

```bash
source .venv312/bin/activate
SPLIT=test bash run_e2e_full_grammar_pipeline.sh /usr/local/bin/elvex
```

For a quick smoke test:

```bash
SPLIT=test N=50 bash run_e2e_full_grammar_pipeline.sh /usr/local/bin/elvex
```

## Outputs

```text
bench/results/e2e_full_test_selection.json
bench/results/e2e_metrics_full_test_best.json
bench/results/e2e_details_full_test_best.jsonl
bench/results/e2e_table_full_test.tex
bench/results/e2e_outputs_full_test_all.jsonl
```

The selection summary should report all parseable E2E test inputs, for example:

```json
{
  "total": 1847,
  "parsed": 1847,
  "supported_slots": 1847,
  "selected": 1847,
  "no_name": 3
}
```

## Caveat

The lexicon still contains domain constants for restaurant names and `near`
values.  This is unavoidable in the current Elvex setup because there is no
copy terminal for arbitrary string values in this benchmark harness.  The
grammar itself is slot-factorized and covers all slot combinations; the domain
constants are lexical resources, not full-sentence templates.
