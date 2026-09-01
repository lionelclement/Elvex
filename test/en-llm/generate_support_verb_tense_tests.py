#!/usr/bin/env python3
from __future__ import annotations

import argparse
import re
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PATTERN = ROOT / "en.pattern"
MORPHO = ROOT / "en.morpho"
STDIN = ROOT / "en-support-verbs-tenses.stdin"
EXPECTED = ROOT / "en-support-verbs-tenses.expected.txt"

# One unambiguous predicative noun per support-verb lemma.  These cases are
# intentionally simple (no free oblique actant and no Magn/AntiMagn) because
# this suite tests verbal morphology, not lexical-function coverage.
CASES = {
    "ACCEPT": ("INVITATION", "oper1"),
    "ACHIEVE": ("RESULT", "oper1"),
    "ASK": ("FAVOR", "oper1"),
    "ASSUME": ("OFFICE", "oper1"),
    "ATTRACT": ("INTEREST", "oper2"),
    "BEAR": ("WEIGHT", "oper1"),
    "CONDUCT": ("SURVEY", "oper1"),
    "DO": ("HOMEWORK", "oper1"),
    "DRAW": ("DISTINCTION", "oper1"),
    "EARN": ("MONEY", "incepoper2"),
    "ENJOY": ("FREEDOM", "oper2"),
    "EXERCISE": ("CAUTION", "oper1"),
    "EXERT": ("FORCE", "oper1"),
    "EXPERIENCE": ("PRESSURE", "oper2"),
    "EXPRESS": ("REGRET", "oper1"),
    "FACE": ("CHALLENGE", "oper2"),
    "FILE": ("LAWSUIT", "oper1"),
    "GAIN": ("KNOWLEDGE", "incepoper2"),
    "GET": ("JOB", "incepoper2"),
    "GIVE": ("ADVICE", "oper1"),
    "HAVE": ("CONVERSATION", "oper1"),
    "HOLD": ("HEARING", "oper1"),
    "IMPOSE": ("BAN", "oper1"),
    "MAKE": ("MISTAKE", "oper1"),
    "MEET": ("REQUIREMENT", "oper2"),
    "OBTAIN": ("VISA", "incepoper2"),
    "OFFER": ("DISCOUNT", "oper1"),
    "PAY": ("ATTENTION", "oper1"),
    "PERFORM": ("PROCEDURE", "oper1"),
    "PLACE": ("BET", "oper1"),
    "PLAY": ("ROLE", "oper1"),
    "POSE": ("THREAT", "oper1"),
    "PROVIDE": ("PROTECTION", "oper1"),
    "PUT": ("PRESSURE", "oper1"),
    "RAISE": ("POINT", "oper1"),
    "REACH": ("CONCLUSION", "oper1"),
    "RECEIVE": ("GUIDANCE", "oper2"),
    "SECURE": ("CONTRACT", "incepoper2"),
    "SET": ("GOAL", "oper1"),
    "SHOW": ("CONCERN", "oper1"),
    "SUBMIT": ("BID", "oper1"),
    "SUFFER": ("SETBACK", "oper2"),
    "TAKE": ("WALK", "oper1"),
    "UNDERGO": ("THERAPY", "oper2"),
    "WIN": ("PRIZE", "incepoper2"),
}

FORMS = [
    ("present", "simple", "positive", "declarative", "present"),
    ("past", "simple", "positive", "declarative", "preterite"),
    ("present", "perfect", "positive", "declarative", "past_participle"),
    ("present", "continuous", "positive", "declarative", "present_participle"),
    ("present", "simple", "negative", "declarative", "infinitive"),
    ("present", "simple", "positive", "interrogative", "infinitive"),
]


def parse_pattern():
    entries = []
    for raw in PATTERN.read_text().splitlines():
        if not raw or raw.startswith("//"):
            continue
        cols = raw.split("\t")
        if len(cols) != 4 or cols[1] != "verb":
            continue
        head, _, lemma, features = cols
        lf = re.search(r"lexical_function:((?:incep)?oper[12])", features)
        val = re.search(r"valency:([^,\]]+)", features)
        obj = re.search(r"fixed_object:\[HEAD:([^,\]]+)(.*?)\]", features)
        if not (lf and val and obj):
            continue
        entries.append({
            "head": head,
            "lemma": lemma,
            "lf": lf.group(1),
            "valency": val.group(1),
            "object_head": obj.group(1),
            "object_tail": obj.group(2),
            "features": features,
        })
    return entries


def parse_morpho():
    verbs = defaultdict(list)
    nouns = defaultdict(list)
    for raw in MORPHO.read_text().splitlines():
        if not raw or raw.startswith("//"):
            continue
        cols = raw.split("\t")
        if len(cols) != 4:
            continue
        surface, pos, lemma, features = cols
        if pos == "verb":
            verbs[lemma].append((surface, features))
        elif pos == "common_noun":
            nouns[lemma].append((surface, features))
    return verbs, nouns


def verb_form(rows, tense):
    if tense == "present":
        wanted = "vtense:present"
        extra = "SUBJECT:[@_3s]"
        matches = [s for s, f in rows if wanted in f and extra in f]
    else:
        wanted = f"vtense:{tense}"
        matches = [s for s, f in rows if wanted in f]
    uniq = sorted(set(matches))
    if len(uniq) != 1:
        raise SystemExit(f"expected one {tense} form, got {uniq}")
    return uniq[0]


def noun_form(rows):
    # Generated/common noun singular entries use @_s.  Prefer them over any
    # plural homograph if both happen to exist.
    matches = [s for s, f in rows if "@s" in f or "number:sg" in f]
    if not matches:
        matches = [s for s, _ in rows]
    uniq = sorted(set(matches))
    if len(uniq) != 1:
        raise SystemExit(f"expected one singular noun form, got {uniq}")
    return uniq[0]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true", help="validate only")
    args = ap.parse_args()

    pattern = parse_pattern()
    verbs, nouns = parse_morpho()
    by_key = defaultdict(list)
    for e in pattern:
        by_key[(e["head"], e["lf"])].append(e)

    stdin_lines = [
        "// Automatically generated support-verb morphology regression.",
        "// Six forms per support verb: present, past, perfect, continuous, negative, interrogative.",
        "",
    ]
    expected_lines = []

    for lemma, (head, lf) in CASES.items():
        candidates = by_key[(head, lf)]
        non_oblique = [e for e in candidates if "oblique" not in e["valency"]]
        support_lemmas = {e["lemma"] for e in candidates}
        if support_lemmas != {lemma}:
            raise SystemExit(f"{head}+{lf}: expected only {lemma}, got {sorted(support_lemmas)}")
        if len(non_oblique) != 1:
            raise SystemExit(f"{head}+{lf}: expected one non-oblique entry, got {len(non_oblique)}")
        entry = non_oblique[0]
        object_head = entry["object_head"]
        noun = noun_form(nouns[object_head])
        indefinite = "def:indefinite" in entry["object_tail"]
        obj = ("a " + noun) if indefinite else noun

        vf = {
            "present": verb_form(verbs[lemma], "present"),
            "preterite": verb_form(verbs[lemma], "preterite"),
            "past_participle": verb_form(verbs[lemma], "past_participle"),
            "present_participle": verb_form(verbs[lemma], "present_participle"),
            "infinitive": verb_form(verbs[lemma], "infinitive"),
        }

        oper1_subject = lf.endswith("oper1")
        subject_head = "JOHN" if oper1_subject else "MARY"
        subject_surface = "John" if oper1_subject else "Mary"
        i = f"[HEAD:{subject_head}]" if oper1_subject else "NIL"
        ii = "NIL" if oper1_subject else f"[HEAD:{subject_head}]"

        stdin_lines.append(f"// {lemma}: {head} + {lf}")
        for tense, aspect, polarity, illocution, required_form in FORMS:
            stdin_lines.append(
                "Axiom ["
                f"HEAD:{head}, i:{i}, ii:{ii}, iii:NIL, "
                f"lexical_function:{lf}, tense:{tense}, aspect:{aspect}, "
                f"modality:none, polarity:{polarity}, illocution:{illocution}]"
            )

            base = vf[required_form]
            if (tense, aspect, polarity, illocution) == ("present", "simple", "positive", "declarative"):
                sent = f"{subject_surface} {base} {obj}."
            elif (tense, aspect, polarity, illocution) == ("past", "simple", "positive", "declarative"):
                sent = f"{subject_surface} {base} {obj}."
            elif aspect == "perfect":
                sent = f"{subject_surface} has {base} {obj}."
            elif aspect == "continuous":
                sent = f"{subject_surface} is {base} {obj}."
            elif polarity == "negative":
                sent = f"{subject_surface} does not {base} {obj}."
            elif illocution == "interrogative":
                sent = f"does {subject_surface} {base} {obj}?"
            else:
                raise AssertionError("unhandled form")
            expected_lines.append(sent)
        stdin_lines.append("")

    if len(CASES) != 45 or len(expected_lines) != 270:
        raise SystemExit(f"unexpected coverage: {len(CASES)} support verbs / {len(expected_lines)} sentences")

    if args.check:
        print(f"OK: {len(CASES)} support verbs; {len(expected_lines)} tense/aspect/polarity/illocution tests")
        return

    STDIN.write_text("\n".join(stdin_lines).rstrip() + "\n")
    EXPECTED.write_text("\n".join(expected_lines) + "\n")
    print(f"generated {len(expected_lines)} tests for {len(CASES)} support verbs")


if __name__ == "__main__":
    main()
