#!/usr/bin/env bash
set -euo pipefail
ELVEX_BIN="${1:-elvex}"
N="${N:-6420}"
MAX_TRIPLES="${MAX_TRIPLES:-3}"
SEED="${SEED:-23}"
PREFIX="grammar/webnlg/webnlg"
PREPARED_N="6420"
PREDICATES=(country birthPlace birthDate deathPlace nationality occupation almaMater office party location isPartOf region city capital leader leaderTitle language genre author creator publisher mediaType club league ground manager successor precededBy followedBy ingredient mainIngredient dishVariation owner operatingOrganisation manufacturer builder architect completionDate alternativeName areaTotal)
mkdir -p bench/webnlg bench/results grammar/webnlg

WEBNLG_FILES=(
  bench/data/gem_webnlg_train.jsonl
  bench/data/gem_webnlg_validation.jsonl
  bench/data/gem_webnlg_test.jsonl
  bench/data/gem_webnlg_challenge_train_sample.jsonl
  bench/data/gem_webnlg_challenge_validation_sample.jsonl
  bench/data/gem_webnlg_challenge_test_numbers.jsonl
  bench/data/gem_webnlg_challenge_test_scramble.jsonl
)

MISSING=0
for f in "${WEBNLG_FILES[@]}"; do
  if [ ! -f "$f" ]; then MISSING=1; fi
done

if [ "$MISSING" -eq 0 ]; then
  python3 bench/webnlg/combine_webnlg_splits.py --inputs "${WEBNLG_FILES[@]}" --out bench/data/gem_webnlg_combined_local.jsonl
  python3 bench/webnlg/select_webnlg_fragment.py \
    --input bench/data/gem_webnlg_combined_local.jsonl \
    --out "bench/webnlg/webnlg_fragment_rich_${N}.jsonl" \
    --n "$N" --seed "$SEED" --max-triples "$MAX_TRIPLES" \
    --supported-only --single-subject-only --unique-predicates \
    --predicates "${PREDICATES[@]}"
else
  echo "Local GEM/WebNLG source files not found; using prepared rich fragment bench/webnlg/webnlg_fragment_rich_${PREPARED_N}.jsonl."
  if [ "$N" != "$PREPARED_N" ]; then
    echo "ERROR: source data are missing and only prepared N=$PREPARED_N is available." >&2
    exit 1
  fi
  if [ ! -f "bench/webnlg/webnlg_fragment_rich_${PREPARED_N}.jsonl" ]; then
    echo "ERROR: missing prepared fragment bench/webnlg/webnlg_fragment_rich_${PREPARED_N}.jsonl." >&2
    exit 1
  fi
fi

python3 bench/webnlg/generate_observed_webnlg_rules.py \
  --fragment "bench/webnlg/webnlg_fragment_rich_${N}.jsonl" \
  --out grammar/webnlg/webnlg.rules \
  --predicate-order "${PREDICATES[@]}"

python3 bench/webnlg/build_fragment_lexicon.py --items "bench/webnlg/webnlg_fragment_rich_${N}.jsonl" --out grammar/webnlg/webnlg.lexicon
python3 bench/webnlg/make_webnlg_inputs.py --items "bench/webnlg/webnlg_fragment_rich_${N}.jsonl" --input-dir "bench/webnlg/inputs_rich_${N}" --manifest "bench/webnlg/webnlg_manifest_rich_${N}.jsonl" --symbol Axiom
bash grammar/webnlg/build_lexicon.sh "$PREFIX"

python3 bench/webnlg/run_webnlg_benchmark.py --manifest "bench/webnlg/webnlg_manifest_rich_${N}.jsonl" --prefix "$PREFIX" --elvex-bin "$ELVEX_BIN" --out "bench/results/webnlg_outputs_rich_${N}_all.jsonl" --all-outputs
python3 bench/webnlg/evaluate_triples.py --outputs "bench/results/webnlg_outputs_rich_${N}_all.jsonl" --metrics "bench/results/webnlg_metrics_rich_${N}_best.json" --details "bench/results/webnlg_details_rich_${N}_best.jsonl" --best-output
python3 bench/webnlg/make_latex_table.py --metrics "bench/results/webnlg_metrics_rich_${N}_best.json" --out "bench/results/webnlg_table_rich_${N}.tex" --dataset-name "WebNLG richer controlled fragment"
