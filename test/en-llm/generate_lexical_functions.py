#!/usr/bin/env python3
"""Generate scalable lexical-function entries for the Elvex English grammar.

Sources: en-lexical-functions.tsv and en-lexical-function-families.tsv.
Lexicographic metadata is stored in en-predicative-nouns.tsv and
en-support-verb-profiles.tsv. Generated blocks are appended to en.pattern and
en.morpho and replaced idempotently on each run.
"""
from __future__ import annotations

import argparse
import csv
from pathlib import Path

ROOT = Path(__file__).resolve().parent
SOURCE = ROOT / "en-lexical-functions.tsv"
FAMILY_SOURCE = ROOT / "en-lexical-function-families.tsv"
PREDICATE_PROFILE_SOURCE = ROOT / "en-predicative-nouns.tsv"
SUPPORT_PROFILE_SOURCE = ROOT / "en-support-verb-profiles.tsv"
PATTERN = ROOT / "en.pattern"
MORPHO = ROOT / "en.morpho"
BEGIN = "// BEGIN GENERATED LEXICAL FUNCTIONS"
END = "// END GENERATED LEXICAL FUNCTIONS"

IRREGULAR_VERBS = {
    "UNDERGO": ("undergo", "undergoes", "underwent", "undergone", "undergoing"),
    "DO": ("do", "does", "did", "done", "doing"),
    "BEAR": ("bear", "bears", "bore", "borne", "bearing"),
    "SUBMIT": ("submit", "submits", "submitted", "submitted", "submitting"),
    "FEEL": ("feel", "feels", "felt", "felt", "feeling"),
}

# These uppercase atoms are tokens in the Elvex lexer and therefore cannot be
# used as identifier values such as HEAD:FORM.  Keep distinct semantic heads
# while preserving their ordinary English surface forms in morphology.
RESERVED_FEATURE_ATOMS = {"HEAD", "LEMMA", "FORM", "TRUE", "FALSE", "NIL"}
PREDICATE_ALIASES = {
    "FORM": "FORM_NOUN",
    "TRUE": "TRUE_ADJ",
    "FALSE": "FALSE_ADJ",
}
PREDICATE_SURFACES = {alias: source.lower() for source, alias in PREDICATE_ALIASES.items()}


def semantic_predicate(name: str) -> str:
    return PREDICATE_ALIASES.get(name.upper(), name.upper())


def predicate_surface(head: str) -> str:
    return PREDICATE_SURFACES.get(head, head.lower())


def strip_block(text: str) -> str:
    if BEGIN not in text:
        return text.rstrip() + "\n"
    before, rest = text.split(BEGIN, 1)
    if END not in rest:
        raise SystemExit(f"{BEGIN!r} found without {END!r}")
    _, after = rest.split(END, 1)
    return (before.rstrip() + "\n" + after.lstrip("\n")).rstrip() + "\n"


def rows():
    """Load curated rows plus broad coverage families.

    The explicit TSV is authoritative and may intentionally contain several
    realizations for the same lexical function. The family TSV is a fallback
    coverage layer: it supplies only predicate/function pairs that have not
    already been defined explicitly.

    When several broad families cover the same semantic key, a row carrying
    an oblique preposition is preferred because the generator emits both the
    no-oblique and oblique lexical patterns from that one row. This preserves
    optional actant realization without adding a second competing support verb.
    """
    explicit = []
    with SOURCE.open(newline="", encoding="utf-8") as fh:
        rd = csv.DictReader(fh, delimiter="\t")
        required = {"kind", "predicate", "function", "realizer", "form", "prep", "note"}
        if set(rd.fieldnames or ()) != required:
            raise SystemExit(f"bad TSV header in {SOURCE.name}: {rd.fieldnames}")
        for r in rd:
            if not r.get("kind"):
                continue
            row = dict(r)
            row["predicate"] = semantic_predicate(row["predicate"])
            explicit.append(row)

    exact_seen = set()
    for r in explicit:
        key = tuple(r[k] for k in ("kind", "predicate", "function", "realizer", "form", "prep"))
        if key in exact_seen:
            raise SystemExit(f"duplicate explicit lexical-function row: {key}")
        exact_seen.add(key)

    out = list(explicit)
    explicit_keys = {(r["kind"], r["predicate"], r["function"]) for r in explicit}

    if FAMILY_SOURCE.exists():
        candidates = {}
        order = []
        with FAMILY_SOURCE.open(newline="", encoding="utf-8") as fh:
            rd = csv.DictReader(fh, delimiter="\t")
            required = {"kind", "function", "realizer", "form", "prep", "predicates", "note"}
            if set(rd.fieldnames or ()) != required:
                raise SystemExit(f"bad TSV header in {FAMILY_SOURCE.name}: {rd.fieldnames}")
            for fam in rd:
                if not fam.get("kind"):
                    continue
                predicates = [semantic_predicate(p.strip()) for p in fam["predicates"].split(",") if p.strip()]
                if not predicates:
                    raise SystemExit(f"empty predicate family: {fam}")
                for pred in predicates:
                    semantic_key = (fam["kind"], pred, fam["function"])
                    if semantic_key in explicit_keys:
                        continue
                    row = {
                        "kind": fam["kind"],
                        "predicate": pred,
                        "function": fam["function"],
                        "realizer": fam["realizer"],
                        "form": fam["form"],
                        "prep": fam["prep"],
                        "note": fam["note"],
                    }
                    if semantic_key not in candidates:
                        candidates[semantic_key] = row
                        order.append(semantic_key)
                    else:
                        current = candidates[semantic_key]
                        # Prefer optional oblique coverage, then bare mass-noun
                        # realization when a family explicitly marks it.
                        # Phase-function families may overlap (e.g. GAIN/GET + ACCESS).
                        # Keep a deterministic lexical preference so a semantic
                        # predicate/function pair still resolves to one support verb.
                        incep_priority = {"GAIN": 60, "GET": 50, "OBTAIN": 40, "SECURE": 30, "WIN": 20, "EARN": 10}
                        score = (
                            incep_priority.get(row["realizer"], 0) if row["function"] == "incepoper2" else 0,
                            bool(row["prep"]),
                            row["form"] == "bare",
                        )
                        current_score = (
                            incep_priority.get(current["realizer"], 0) if current["function"] == "incepoper2" else 0,
                            bool(current["prep"]),
                            current["form"] == "bare",
                        )
                        if score > current_score:
                            candidates[semantic_key] = row
        out.extend(candidates[k] for k in order)
    return out



def load_predicate_profiles():
    """Load descriptive lexical profiles for predicative nouns.

    These profiles document semantic valency, selectional restrictions,
    countability and lexical fixedness.  They are intentionally kept separate
    from the surface-realization TSV so the metadata can grow without changing
    the current rule interface.
    """
    if not PREDICATE_PROFILE_SOURCE.exists():
        return {}
    required = [
        "predicate", "class", "aktionsart", "semantic_valency",
        "arg1_role", "arg1_restriction", "arg2_role", "arg2_restriction",
        "default_prep", "countability", "fixedness", "note",
    ]
    out = {}
    with PREDICATE_PROFILE_SOURCE.open(newline="", encoding="utf-8") as fh:
        rd = csv.DictReader(fh, delimiter="\t")
        if list(rd.fieldnames or ()) != required:
            raise SystemExit(f"bad TSV header in {PREDICATE_PROFILE_SOURCE.name}: {rd.fieldnames}")
        for raw in rd:
            if not raw.get("predicate"):
                continue
            row = dict(raw)
            pred = semantic_predicate(row.pop("predicate"))
            if pred in out:
                raise SystemExit(f"duplicate predicative-noun profile: {pred}")
            out[pred] = row
    return out


def load_support_profiles():
    """Load default aspectual/discourse profiles for support verbs."""
    if not SUPPORT_PROFILE_SOURCE.exists():
        return {}
    required = [
        "realizer", "lexical_aspect", "phase", "causativity", "agency",
        "stance", "subjectivity", "register", "note",
    ]
    out = {}
    with SUPPORT_PROFILE_SOURCE.open(newline="", encoding="utf-8") as fh:
        rd = csv.DictReader(fh, delimiter="\t")
        if list(rd.fieldnames or ()) != required:
            raise SystemExit(f"bad TSV header in {SUPPORT_PROFILE_SOURCE.name}: {rd.fieldnames}")
        for raw in rd:
            if not raw.get("realizer"):
                continue
            row = dict(raw)
            realizer = row.pop("realizer").upper()
            if realizer in out:
                raise SystemExit(f"duplicate support-verb profile: {realizer}")
            out[realizer] = row
    return out


def validate_profiles(data, predicate_profiles, support_profiles):
    pred_classes = {
        "volition", "cognition", "epistemic", "communication", "emotion",
        "deontic", "attitude", "evaluation", "social_relation",
        "social_action", "event", "change", "legal", "economic", "medical",
    }
    aktionsarts = {"state", "activity", "achievement", "accomplishment", "event", "process"}
    valencies = {"one", "two", "three"}
    restrictions = {"", "human", "animate", "institution", "entity", "proposition", "event", "location", "resource", "any"}
    countabilities = {"count", "mass", "either"}
    fixedness = {"free", "collocational", "strong"}
    for pred, r in predicate_profiles.items():
        if r["class"] not in pred_classes:
            raise SystemExit(f"unknown predicate class {r['class']!r} for {pred}")
        if r["aktionsart"] not in aktionsarts:
            raise SystemExit(f"unknown aktionsart {r['aktionsart']!r} for {pred}")
        if r["semantic_valency"] not in valencies:
            raise SystemExit(f"unknown semantic valency {r['semantic_valency']!r} for {pred}")
        if r["arg1_restriction"] not in restrictions or r["arg2_restriction"] not in restrictions:
            raise SystemExit(f"unknown selectional restriction for {pred}")
        if r["countability"] not in countabilities:
            raise SystemExit(f"unknown countability {r['countability']!r} for {pred}")
        if r["fixedness"] not in fixedness:
            raise SystemExit(f"unknown fixedness {r['fixedness']!r} for {pred}")
    support_realisers = {r["realizer"] for r in data if r["kind"] == "support"}
    for realizer, r in support_profiles.items():
        if realizer not in support_realisers:
            raise SystemExit(f"support profile without lexical-function relation: {realizer}")
        if r["subjectivity"] not in {"low", "medium", "high", "neutral"}:
            raise SystemExit(f"unknown subjectivity {r['subjectivity']!r} for {realizer}")
        if r["register"] not in {"neutral", "formal", "informal"}:
            raise SystemExit(f"unknown register {r['register']!r} for {realizer}")
    return {
        "profiled_predicates": len(predicate_profiles),
        "profiled_supports": len(support_profiles),
        "relations_with_predicate_profile": sum(1 for r in data if r["predicate"] in predicate_profiles),
        "relations_with_support_profile": sum(1 for r in data if r["kind"] != "support" or r["realizer"] in support_profiles),
    }

def plural_noun(word: str) -> str:
    w = word.lower()
    if len(w) > 1 and w.endswith("y") and w[-2] not in "aeiou":
        return w[:-1] + "ies"
    if w.endswith(("s", "x", "z", "ch", "sh")):
        return w + "es"
    return w + "s"


def regular_verb_forms(lemma: str):
    u = lemma.upper()
    if u in IRREGULAR_VERBS:
        base, third, past, pp, ing = IRREGULAR_VERBS[u]
        return base, third, past, pp, ing
    w = lemma.lower()
    if len(w) > 1 and w.endswith("y") and w[-2] not in "aeiou":
        third = w[:-1] + "ies"
        past = w[:-1] + "ied"
    else:
        third = w + ("es" if w.endswith(("s", "x", "z", "ch", "sh", "o")) else "s")
        past = w + ("d" if w.endswith("e") else "ed")
    if w.endswith("ie"):
        ing = w[:-2] + "ying"
    elif w.endswith("e") and not w.endswith(("ee", "ye")):
        ing = w[:-1] + "ing"
    else:
        ing = w + "ing"
    return w, third, past, past, ing


def feature_object(pred: str, form: str) -> str:
    if form == "bare":
        return f"[HEAD:{pred}, number:sg]"
    if form == "indef":
        return f"[HEAD:{pred}, def:indefinite, number:sg]"
    if form == "def":
        return f"[HEAD:{pred}, def:true, number:sg]"
    raise SystemExit(f"unsupported nominal form {form!r} for {pred}")


def parse_inventory(pattern_text: str, morpho_text: str):
    noun_heads, adj_heads, adv_heads, verb_lemmas = set(), set(), set(), set()
    pattern_lines = set()
    for line in pattern_text.splitlines():
        if not line.strip() or line.lstrip().startswith(("#", "//")):
            continue
        pattern_lines.add(line)
        parts = line.split("\t")
        if len(parts) < 3:
            continue
        head, pos, lemma = parts[:3]
        if pos == "common_noun": noun_heads.add(head)
        elif pos == "adj": adj_heads.add(head)
        elif pos == "adv": adv_heads.add(head)
        elif pos == "verb": verb_lemmas.add(lemma)
    morpho_lemmas = set()
    for line in morpho_text.splitlines():
        parts = line.split("\t")
        if len(parts) >= 3 and not line.lstrip().startswith(("#", "//")):
            morpho_lemmas.add((parts[1], parts[2]))
    return noun_heads, adj_heads, adv_heads, verb_lemmas, morpho_lemmas, pattern_lines


def generate(check_only=False):
    data = rows()
    predicate_profiles = load_predicate_profiles()
    support_profiles = load_support_profiles()
    profile_stats = validate_profiles(data, predicate_profiles, support_profiles)
    base_pattern = strip_block(PATTERN.read_text(encoding="utf-8"))
    base_morpho = strip_block(MORPHO.read_text(encoding="utf-8"))
    noun_heads, adj_heads, adv_heads, verb_lemmas, morpho_lemmas, existing_patterns = parse_inventory(base_pattern, base_morpho)

    # Validate source fields and duplicate rows.
    seen = set()
    allowed_kinds = {"support", "noun_modifier", "adj_modifier"}
    allowed_functions = {"oper1", "oper2", "incepoper2", "causoper1", "magn", "antimagn"}
    allowed_preps = {"", "to", "on", "in", "at", "for", "with", "about", "of", "from", "into", "against"}
    for r in data:
        key = tuple(r[k] for k in ("kind", "predicate", "function", "realizer", "form", "prep"))
        if key in seen:
            raise SystemExit(f"internal duplicate after source expansion: {key}")
        seen.add(key)
        if r["kind"] not in allowed_kinds:
            raise SystemExit(f"unknown kind: {r['kind']}")
        if r["function"] not in allowed_functions:
            raise SystemExit(f"unknown function: {r['function']}")
        if r["prep"] not in allowed_preps:
            raise SystemExit(f"unknown preposition: {r['prep']}")
        if r["kind"] == "support" and r["function"] not in {"oper1", "oper2", "incepoper2", "causoper1"}:
            raise SystemExit(f"support row must use oper1/oper2/incepoper2/causoper1: {key}")
        if r["kind"] != "support" and r["function"] not in {"magn", "antimagn"}:
            raise SystemExit(f"modifier row must use magn/antimagn: {key}")
        if r["predicate"] in RESERVED_FEATURE_ATOMS:
            raise SystemExit(f"reserved Elvex atom used as semantic predicate: {r['predicate']}")
        if r["kind"] in {"noun_modifier", "adj_modifier"} and r["realizer"].upper() in RESERVED_FEATURE_ATOMS:
            raise SystemExit(f"reserved Elvex atom used as modifier HEAD: {r['realizer']}")

    patt = []
    morph = []

    # Add missing predicate nouns/adjectives and modifier realizers.
    needed_nouns = {r["predicate"] for r in data if r["kind"] in {"support", "noun_modifier"}}
    needed_adjs = {r["predicate"] for r in data if r["kind"] == "adj_modifier"}
    modifier_adjs = {r["realizer"] for r in data if r["kind"] == "noun_modifier"}
    modifier_advs = {r["realizer"] for r in data if r["kind"] == "adj_modifier"}
    support_verbs = {r["realizer"] for r in data if r["kind"] == "support"}

    for head in sorted(needed_nouns - noun_heads):
        patt.append(f"{head}\tcommon_noun\t{head}\t[]")
        if ("common_noun", head) not in morpho_lemmas:
            surface = predicate_surface(head)
            morph += [
                f"{surface}\tcommon_noun\t{head}\t[@s]",
                f"{plural_noun(surface)}\tcommon_noun\t{head}\t[@p]",
            ]

    for head in sorted((needed_adjs | modifier_adjs) - adj_heads):
        patt.append(f"{head}\tadj\t{head}\t[]")
        if ("adj", head) not in morpho_lemmas:
            morph.append(f"{predicate_surface(head)}\tadj\t{head}\t[]")

    for head in sorted(modifier_advs - adv_heads):
        patt.append(f"{head}\tadv\t{head}\t[]")
        if ("adv", head) not in morpho_lemmas:
            morph.append(f"{head.lower()}\tadv\t{head}\t[]")

    for lemma in sorted(support_verbs - verb_lemmas):
        if ("verb", lemma) in morpho_lemmas:
            continue
        base, third, past, pp, ing = regular_verb_forms(lemma)
        morph += [
            f"{base}\tverb\t{lemma}\t[vtense:present, SUBJECT:[@_12s]]",
            f"{base}\tverb\t{lemma}\t[vtense:present, SUBJECT:[@p]]",
            f"{third}\tverb\t{lemma}\t[vtense:present, SUBJECT:[@_3s]]",
            f"{past}\tverb\t{lemma}\t[vtense:preterite]",
            f"{pp}\tverb\t{lemma}\t[vtense:past_participle, tensed:false]",
            f"{ing}\tverb\t{lemma}\t[vtense:present_participle, tensed:false]",
            f"{base}\tverb\t{lemma}\t[vtense:infinitive, tensed:false]",
        ]

    # Lexical-function relations.
    for r in data:
        kind, pred, func, real = r["kind"], r["predicate"], r["function"], r["realizer"]
        form, prep = r["form"], r["prep"]
        if kind == "support":
            obj = feature_object(pred, form)
            base_val = "support_nominal_bare" if form == "bare" else "support_nominal"
            line = f"{pred}\tverb\t{real}\t[valency:{base_val}, lexical_function:{func}, fixed_object:{obj}]"
            if line not in existing_patterns and line not in patt:
                patt.append(line)
            if prep:
                oval = "support_nominal_bare_oblique" if form == "bare" else "support_nominal_oblique"
                line = f"{pred}\tverb\t{real}\t[valency:{oval}, lexical_function:{func}, fixed_object:{obj}, pcase:_{prep}_]"
                if line not in existing_patterns and line not in patt:
                    patt.append(line)
        elif kind == "noun_modifier":
            line = f"{pred}\tcommon_noun\t{pred}\t[lexical_function:{func}, fixed_adj:[HEAD:{real}]]"
            if line not in existing_patterns and line not in patt:
                patt.append(line)
        elif kind == "adj_modifier":
            line = f"{pred}\tadj\t{pred}\t[lexical_function:{func}, fixed_adv:[HEAD:{real}]]"
            if line not in existing_patterns and line not in patt:
                patt.append(line)

    if check_only:
        from collections import Counter
        by_function = Counter(r["function"] for r in data)
        by_kind = Counter(r["kind"] for r in data)
        predicates = {r["predicate"] for r in data}
        fn = ", ".join(f"{k}={v}" for k, v in sorted(by_function.items()))
        kn = ", ".join(f"{k}={v}" for k, v in sorted(by_kind.items()))
        print(
            f"OK: {len(data)} lexical-function relations over {len(predicates)} predicates; "
            f"{fn}; {kn}; {profile_stats['profiled_predicates']} predicative-noun profiles; "
            f"{profile_stats['profiled_supports']} support-verb profiles; "
            f"{len(patt)} pattern lines and {len(morph)} morphology lines would be generated"
        )
        return

    pblock = BEGIN + "\n" + "\n".join(patt) + "\n" + END + "\n"
    mblock = BEGIN + "\n" + "\n".join(morph) + "\n" + END + "\n"
    PATTERN.write_text(base_pattern.rstrip() + "\n\n" + pblock, encoding="utf-8")
    MORPHO.write_text(base_morpho.rstrip() + "\n\n" + mblock, encoding="utf-8")
    print(f"generated {len(data)} lexical-function relations: {len(patt)} pattern lines, {len(morph)} morphology lines")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    generate(args.check)

if __name__ == "__main__":
    main()
