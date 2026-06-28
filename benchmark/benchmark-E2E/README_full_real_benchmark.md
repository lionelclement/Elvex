# Full real benchmark scripts

These scripts report full-split coverage while keeping the existing supported-subset generation pipelines.

The key distinction is:

- `Source`: all inputs in the selected real GEM split.
- `Covered`: inputs kept by the current support filter and actually passed to Elvex.
- `Pres.`: preservation on the covered/generated subset.
- `Global`: lower-bound unit preservation over the full source split, computed as preserved covered units divided by all source units. Unsupported inputs therefore count as not preserved.

This is not a leaderboard-style E2E/WebNLG evaluation. It is a full-split coverage plus preservation report for the current grammar, lexicon, and conversion scripts.

## Setup

From the `benchmark/` directory:

```bash
python3.12 -m venv .venv312
source .venv312/bin/activate
python -m pip install -U pip
python -m pip install 'datasets>=2.0.0'
```

Elvex must also be installed or available as a binary. The examples below assume `/usr/local/bin/elvex`.

## Download and profile the real GEM datasets

```bash
bash run_download_real_datasets.sh
```

This creates normalized JSONL files under `bench/data/` and a profile under:

```text
bench/results/real_benchmark_profile.json
```

## Run the full real benchmark summary

```bash
SPLIT=test bash run_full_real_benchmark.sh /usr/local/bin/elvex
```

Useful options:

```bash
# Limit for quick debugging
SPLIT=test E2E_N=50 WEBNLG_N=50 bash run_full_real_benchmark.sh /usr/local/bin/elvex

# Change the WebNLG support filter
SPLIT=test MAX_TRIPLES=3 bash run_full_real_benchmark.sh /usr/local/bin/elvex
```

Outputs:

```text
bench/results/full_real_benchmark_test.json
bench/results/full_real_benchmark_test.tex
bench/results/e2e_metrics_real_supported_test_best.json
bench/results/webnlg_metrics_real_supported_test_best.json
bench/results/e2e_details_real_supported_test_best.jsonl
bench/results/webnlg_details_real_supported_test_best.jsonl
```

## Existing supported-subset pipelines

The existing scripts are still available:

```bash
SPLIT=test bash run_e2e_real_supported_pipeline.sh /usr/local/bin/elvex
SPLIT=test bash run_webnlg_real_supported_pipeline.sh /usr/local/bin/elvex
SPLIT=test bash run_real_supported_benchmarks.sh /usr/local/bin/elvex
```

Use the new `run_full_real_benchmark.sh` when you want full-split coverage numbers in addition to preservation on the covered subset.
