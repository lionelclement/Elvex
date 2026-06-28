#!/usr/bin/env python3
from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REQUIRED = [
    "user/main.macros",
    "user/main.input",
    "user/main.rules",
    "user/main.lexicon",
    "user/main.pattern",
    "user/main.morpho",
    "user/rules/frames.rules",
    "user/rules/simple_triples.rules",
    "user/override.pattern",
    "user/override.morpho",
    "user/lexicon/base.lexicon",
    "user/lexicon/generated_determiners.lexicon",
    "user/lexicon/predicate_overrides.tsv",
    "data/processed/triples.jsonl",
    "build/sequences/1.jsonl",
    "build/inputs/simple_triples.index.tsv",
]
OPTIONAL_BUILT = [
    "build/lexicon/main.tbl",
    "build/lexicon/main.fsa",
]


def main() -> int:
    missing = [p for p in REQUIRED if not (ROOT / p).exists()]
    input_dir = ROOT / "build/inputs/simple_triples"
    if not input_dir.is_dir() or not any(input_dir.glob("*.input")):
        missing.append("build/inputs/simple_triples/*.input")
    if missing:
        print("Missing files:")
        for p in missing:
            print(" -", p)
        print("Run ./run all, or at least: ./run extract && ./run lexicon && ./run compact && ./run select && ./run inputs")
        return 1

    empty_macros = (ROOT / "user/main.macros").stat().st_size == 0
    if empty_macros:
        print("user/main.macros is empty. Either add macros or omit --macros-file when calling Elvex tools.")
        return 1

    missing_built = [p for p in OPTIONAL_BUILT if not (ROOT / p).exists()]
    if missing_built:
        print("Project files are present, but compacted lexicon files are missing:")
        for p in missing_built:
            print(" -", p)
        print("Run ./run compact to create them with elvexlexicon.")
        return 1

    n_inputs = sum(1 for _ in input_dir.glob("*.input"))
    print(f"Project structure looks good. Single-input Elvex tests: {n_inputs}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
