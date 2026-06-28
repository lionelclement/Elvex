# Targeted contextual probe

This adds a controlled probe for the mechanism studied in the paper: information
synthesized by one constituent is reused as inherited context for a later
constituent.

The suite contains 200 items by default:

- 50 anaphora / discourse reuse items
- 50 agreement items
- 50 support-verb licensing items
- 50 collocation items

The probe is generated from manually specified contrast schemas.  It is not a
general data-to-text benchmark; it isolates the effect of synthesized context.

## Run

From the `benchmark/` directory:

```bash
source .venv312/bin/activate
bash run_contextual_probe.sh /usr/local/bin/elvex
```

For a smaller smoke test:

```bash
N_PER_PHENOMENON=2 bash run_contextual_probe.sh /usr/local/bin/elvex
```

## Outputs

```text
bench/context/context_probe_items.jsonl
bench/context/context_probe_manifest.jsonl
bench/results/context_probe_outputs.jsonl
bench/results/context_probe_metrics_best.json
bench/results/context_probe_metrics_first.json
bench/results/context_probe_table.tex
```

## Metrics

- `generation_rate`: generated items / total items
- `context_accuracy`: generated outputs satisfying the expected contextual dependency
- `violations`: missing expected contextual forms plus forbidden forms found
- `by_phenomenon`: breakdown for anaphora, agreement, support verbs, and collocations

The `best` mode asks whether the generated forest contains a context-consistent
output.  The `first` mode asks whether the current output order returns a
context-consistent output first.
