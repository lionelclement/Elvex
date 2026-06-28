# E2E/GEM reproducibility package for the Elvex scalability experiment

This archive contains a self-contained Python pipeline for re-running the E2E/GEM
scalability and slot-preservation experiment with Elvex.

The pipeline downloads `GEM/e2e_nlg` from Hugging Face, takes the `test` split,
groups repeated references by distinct meaning representation (MR), builds
Elvex input files and a full E2E grammar, runs Elvex, and computes the two
reported diagnostic modes:

- `First output`: evaluates the first output returned by Elvex for each input.
- `Best in forest`: evaluates the generated output that preserves the largest
  number of explicit input slots.

`Best in forest` is a diagnostic upper-bound condition. It searches the generated
forest after generation; it is not a runtime ranking model.

## Requirements

Install Python dependencies:

```bash
pip install -r requirements.txt
```

You also need the `elvex` binary available on `PATH`, or provide its path via
`--elvex-bin` or the `ELVEX_BIN` environment variable used by the shell wrappers.

The Elvex command used by the runner has the following shape:

```bash
elvex \
  --macros-file <prefix>.macros \
  --rules-file <prefix>.rules \
  --lexicon-file <prefix>.lexicon \
  --input-file <input-file> \
  --strategy exhaustive \
  --max-length 80
```

The package creates an empty `<prefix>.macros` file automatically if none exists.

## Quick smoke test

Run only 3 distinct MRs through the full pipeline:

```bash
./run_smoke.sh
```

or explicitly:

```bash
python rerun_e2e_gem.py \
  --scripts-dir scripts \
  --work-dir runs/e2e_gem_smoke \
  --max-items 3 \
  --run-generation \
  --elvex-bin elvex \
  --max-time 30
```

## Prepare the full E2E/GEM test split without running Elvex

This downloads the data, deduplicates by MR, writes inputs and manifest, and
builds `.rules`, `.lexicon`, and `.macros` files:

```bash
./prepare_full.sh
```

Expected summary for the full test split:

- 1,847 distinct MRs / inputs
- 11,428 explicit input slots

The summary is written to:

```text
runs/e2e_gem_full/dataset_summary.json
```

## Full exhaustive Elvex run

```bash
./run_full.sh
```

or explicitly:

```bash
python rerun_e2e_gem.py \
  --scripts-dir scripts \
  --work-dir runs/e2e_gem_full \
  --run-generation \
  --elvex-bin elvex \
  --max-length 80
```

Useful environment variables for the wrapper:

```bash
ELVEX_BIN=/path/to/elvex ./run_full.sh
ELVEX_MAX_TIME=60 ./run_full.sh
ELVEX_MAX_LENGTH=80 ./run_full.sh
ELVEX_MAX_ITEMS=100000 ./run_full.sh
```

## Main output files

After a full run, the important files are:

```text
runs/e2e_gem_full/e2e_gem_test_distinct_mrs.jsonl
runs/e2e_gem_full/manifest_full_test.jsonl
runs/e2e_gem_full/inputs_full_test/
runs/e2e_gem_full/grammar/e2e_full.macros
runs/e2e_gem_full/grammar/e2e_full.rules
runs/e2e_gem_full/grammar/e2e_full.lexicon
runs/e2e_gem_full/outputs_full_test_all.jsonl
runs/e2e_gem_full/metrics_first_output.json
runs/e2e_gem_full/details_first_output.jsonl
runs/e2e_gem_full/metrics_best_in_forest.json
runs/e2e_gem_full/details_best_in_forest.jsonl
runs/e2e_gem_full/table_e2e_gem_results.tex
```

## Notes on the scripts

- `scripts/build_full_e2e_grammar.py` builds a slot-specific grammar for the
  E2E restaurant slots.
- `scripts/make_full_e2e_inputs.py` creates one Elvex input file per distinct MR.
- `scripts/run_elvex_benchmark.py` calls Elvex once per input and stores all
  stdout/stderr, the command, and parsed outputs in JSONL.
- `scripts/evaluate_slots.py` computes coverage, slot accuracy, SER, and average
  outputs per input. With `--best-output`, it selects the output with the fewest
  omitted slots for each input.

## Reproducibility cautions

The experiment depends on the installed Elvex version and its enumeration order.
The `Best in forest` metric should be stable if the same complete output forest is
produced. The `First output` metric may change if Elvex changes the order in which
it enumerates derivations.


Notes: the runner does not pass `--macros-file` or `--compacted-lexicon-file`; the generated lexicon does not use the old `@_3s` macro.
