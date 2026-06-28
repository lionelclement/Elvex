# Lexical-dependency probe

This benchmark folder contains a targeted positive probe for two phenomena:

1. collocations, e.g. `heavy rain`, `strong coffee`, `heavy traffic`;
2. support-verb constructions, e.g. `make a decision`, `pay attention`, `do damage`.

The probe is intentionally small and explicit.  It is not a broad data-to-text
benchmark.  It tests whether an Elvex grammar can realize lexically licensed
dependencies from structured inputs.

## Layout

```text
benchmark/bench/lexical_probe/
  items.jsonl
  make_probe_inputs.py
  run_probe.py
  evaluate_probe.py
  make_probe_table.py

benchmark/grammar/lexical_probe/
  lexical_probe.rules
  lexical_probe.lexicon
  lexical_probe.macros
  lexical_probe.pattern
  lexical_probe.morpho

benchmark/run_lexical_probe.sh
```

## Run

From the `benchmark/` directory:

```bash
bash run_lexical_probe.sh /usr/local/bin/elvex
```

## Inputs

Example collocation item:

```text
text [HEAD:RAIN, mod:<[HEAD:HEAVY]>, lexical_function:magn]
```

Expected realization:

```text
heavy rain
```

Example support-verb item:

```text
text [HEAD:DECISION, support:<[HEAD:MAKE]>, tense:past]
```

Expected realization:

```text
made a decision
```

## Metrics

The evaluator reports:

- `generation_rate`
- `accuracy_on_all_items`
- `accuracy_on_generated_items`
- `avg_outputs_per_item`
- `avg_runtime_ms`
- per-phenomenon breakdowns

The generated LaTeX table is written to:

```text
bench/results/lexical_probe_table.tex
```

## Notes

The included grammar is an executable skeleton.  It can be replaced by a more
realistic grammar that uses synthesized structures to pass lexical requirements
between rule applications.  The scripts and metrics do not assume a particular
grammar implementation; they only check whether generated outputs match the
expected lexical realizations.
