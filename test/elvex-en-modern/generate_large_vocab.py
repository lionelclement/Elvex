#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import re
from pathlib import Path

BEGIN = "// BEGIN GENERATED LARGE VOCABULARY"
END = "// END GENERATED LARGE VOCABULARY"

def read_rows(path: Path):
    with path.open(newline="", encoding="utf-8") as f:
        for row in csv.reader(f, delimiter="\t"):
            if not row or row[0].startswith("#"):
                continue
            yield row + [""] * (9 - len(row))

def without_generated_block(text: str) -> str:
    if BEGIN in text and END in text:
        before, rest = text.split(BEGIN, 1)
        _, after = rest.split(END, 1)
        return before + after
    return text

def replace_block(path: Path, body: str):
    text = path.read_text(encoding="utf-8")
    block = BEGIN + "\n" + body.rstrip() + "\n" + END
    if BEGIN in text and END in text:
        before, rest = text.split(BEGIN, 1)
        _, after = rest.split(END, 1)
        text = before.rstrip() + "\n\n" + block + after
    else:
        text = text.rstrip() + "\n\n" + block + "\n"
    path.write_text(text, encoding="utf-8")

def base_morpho_lemmas(path: Path):
    text = without_generated_block(path.read_text(encoding="utf-8"))
    lemmas = set()
    for line in text.splitlines():
        if not line or line.startswith("//"):
            continue
        parts = line.split("\t")
        if len(parts) >= 3:
            lemmas.add(parts[2])
    return lemmas

def base_proper_heads(path: Path):
    """Return semantic HEADs already reserved by non-generated proper nouns."""
    text = without_generated_block(path.read_text(encoding="utf-8"))
    heads = set()
    for line in text.splitlines():
        if " proper_noun " not in line:
            continue
        m = re.search(r"\bHEAD:([A-Za-z0-9_]+)", line)
        if m:
            heads.add(m.group(1))
    return heads

def build(data: Path, existing_morpho: set[str]):
    pattern = []
    morpho = []
    lexicon = []
    seen_morph_lemmas = set(existing_morpho)

    for row in read_rows(data):
        kind, lexeme, lemma, a1, a2, a3, a4, a5, a6 = row[:9]

        if kind == "noun":
            plural = a1
            pattern.append(f"{lexeme}\tcommon_noun\t{lemma.upper()}\t[]")
            morpho.append(f"{lemma}\tcommon_noun\t{lemma.upper()}\t[@s]")
            morpho.append(f"{plural}\tcommon_noun\t{lemma.upper()}\t[@p]")

        elif kind == "adj":
            pattern.append(f"{lexeme}\tadj\t{lemma.upper()}\t[]")
            morpho.append(f"{lemma}\tadj\t{lemma.upper()}\t[]")

        elif kind == "verb":
            valency, pcase, third, past, pp, ing = a1, a2, a3, a4, a5, a6
            features = f"[valency:{valency}"
            if pcase:
                features += f", pcase:_{pcase}_"
            features += "]"
            pattern.append(f"{lexeme}\tverb\t{lemma.upper()}\t{features}")
            key = lemma.upper()
            if key not in seen_morph_lemmas:
                seen_morph_lemmas.add(key)
                morpho.extend([
                    f"{lemma}\tverb\t{key}\t[vtense:present, SUBJECT:[@_12s]]",
                    f"{lemma}\tverb\t{key}\t[vtense:present, SUBJECT:[@p]]",
                    f"{third}\tverb\t{key}\t[vtense:present, SUBJECT:[@_3s]]",
                    f"{past}\tverb\t{key}\t[vtense:preterite]",
                    f"{pp}\tverb\t{key}\t[vtense:past_participle, tensed:false]",
                    f"{ing}\tverb\t{key}\t[vtense:present_participle, tensed:false]",
                    f"{lemma}\tverb\t{key}\t[vtense:infinitive, tensed:false]",
                ])

        elif kind == "proper":
            gender = a1
            macro = "@m" if gender == "ms" else "@f"
            lexicon.append(f"{lemma} proper_noun [HEAD:{lexeme}, @_3s, {macro}, @human];")

        elif kind == "prep":
            lexicon.append(f"{lemma} prep [pcase:{a1}];")

    return "\n".join(pattern), "\n".join(morpho), "\n".join(lexicon)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", default=".", help="grammar directory")
    ap.add_argument("--data", default="en-vocab-large.tsv")
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()

    root = Path(args.root)
    data = root / args.data
    rows = list(read_rows(data))
    lexical_rows = [r for r in rows if r[0] in {"noun", "adj", "verb"}]
    if len(lexical_rows) < 1000:
        raise SystemExit(f"expected >=1000 lexical rows, got {len(lexical_rows)}")

    # Semantic HEAD identifiers must not accidentally cross lexical categories.
    # In particular, a proper name such as WILLIAM must not also be generated
    # as a common noun, or NP realization can produce "the william".
    by_lexeme = {}
    for row in rows:
        if row[0] not in {"noun", "adj", "verb", "proper"}:
            continue
        by_lexeme.setdefault(row[1], set()).add(row[0])
    collisions = {k: v for k, v in by_lexeme.items() if len(v) > 1}

    # Also protect semantic HEADs already used by proper nouns in the hand-written
    # base lexicon (e.g. JOHN). Generated common nouns must use a distinct HEAD
    # such as JOHN_NOUN even when their surface lemma is the same word.
    reserved_proper_heads = base_proper_heads(root / "en.lexicon")
    generated_nonproper_heads = {
        row[1] for row in rows if row[0] in {"noun", "adj", "verb"}
    }
    base_collisions = sorted(reserved_proper_heads & generated_nonproper_heads)

    if collisions or base_collisions:
        details = [
            f"{lexeme}={'+'.join(sorted(kinds))}"
            for lexeme, kinds in sorted(collisions.items())
        ]
        details.extend(f"{lexeme}=base_proper+generated" for lexeme in base_collisions)
        raise SystemExit(f"lexeme category collision(s): {', '.join(details)}")

    if args.check:
        print(
            f"OK: {len(lexical_rows)} lexical rows in {data}; "
            "no semantic HEAD category collisions"
        )
        return

    existing = base_morpho_lemmas(root / "en.morpho")
    p, m, l = build(data, existing)
    replace_block(root / "en.pattern", p)
    replace_block(root / "en.morpho", m)
    replace_block(root / "en.lexicon", l)
    print(f"generated {len(lexical_rows)} lexical rows")

if __name__ == "__main__":
    main()
