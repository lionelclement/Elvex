#!/usr/bin/env python3
"""Audit the generated English lexical-function inventory.

This is a lexicographic QA tool, not a grammar validator. It does not change
entries. It scores relations for manual review using deterministic structural
signals plus a small set of high-confidence English/Meaning-Text heuristics.

Outputs:
  en-lexical-functions-quality.tsv  all resolved relations with QA metadata
  en-lexical-functions-quality.md   prioritized human-readable report
"""
from __future__ import annotations

import csv
import importlib.util
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent
CORE = ROOT / "en-lexical-functions.tsv"
FAMILIES = ROOT / "en-lexical-function-families.tsv"
GENERATOR = ROOT / "generate_lexical_functions.py"
OUT_TSV = ROOT / "en-lexical-functions-quality.tsv"
OUT_MD = ROOT / "en-lexical-functions-quality.md"


def load_generator():
    spec = importlib.util.spec_from_file_location("elvex_lf_generator", GENERATOR)
    if not spec or not spec.loader:
        raise SystemExit(f"cannot import {GENERATOR}")
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def load_explicit(gen):
    rows = []
    with CORE.open(newline="", encoding="utf-8") as fh:
        rd = csv.DictReader(fh, delimiter="\t")
        for r in rd:
            if not r.get("kind"):
                continue
            x = dict(r)
            x["predicate"] = gen.semantic_predicate(x["predicate"])
            rows.append(x)
    return rows


def load_family_candidates(gen):
    candidates = defaultdict(list)
    if not FAMILIES.exists():
        return candidates
    with FAMILIES.open(newline="", encoding="utf-8") as fh:
        rd = csv.DictReader(fh, delimiter="\t")
        for fam in rd:
            if not fam.get("kind"):
                continue
            for pred in (p.strip() for p in fam["predicates"].split(",")):
                if not pred:
                    continue
                pred = gen.semantic_predicate(pred)
                candidates[(fam["kind"], pred, fam["function"])].append(
                    (fam["realizer"], fam["form"], fam["prep"])
                )
    return candidates


def exact_key(r):
    return tuple(r[k] for k in ("kind", "predicate", "function", "realizer", "form", "prep"))


def semantic_key(r):
    return (r["kind"], r["predicate"], r["function"])


def surface_stub(r):
    """Readable collocation skeleton, not a generated sentence."""
    realizer = r["realizer"].lower()
    pred = r["predicate"].lower().replace("_noun", "")
    if r["kind"] == "support":
        if r["form"] == "indef":
            obj = f"a/an {pred}"
        elif r["form"] == "def":
            obj = f"the {pred}"
        else:
            obj = pred
        if r["prep"]:
            return f"{realizer} {obj} {r['prep']} NP"
        return f"{realizer} {obj}"
    return f"{realizer} {pred}"


# Acquisition/result verbs typically add phase/result semantics. They are good
# collocations, but many are better candidates for IncepOper/Real-type LFs than
# for a semantically empty Oper2.
OPER2_PHASE_RESULT = set()

# Causative/change readings that deserve a separate LF once the grammar grows
# beyond the initial Oper1/Oper2 inventory.
CAUSATIVE_CASES = {
    ("ATTRACT", "INTEREST"), ("ATTRACT", "CONTROVERSY"),
    ("ATTRACT", "CONCERN"), ("ATTRACT", "SUSPICION"),
    ("RAISE", "AWARENESS"), ("RAISE", "ALARM"),
    ("RAISE", "MONEY"), ("RAISE", "CAPITAL"),
    ("RAISE", "INTEREST"), ("RAISE", "HOPE"),
    ("POSE", "THREAT"), ("POSE", "RISK"), ("POSE", "DANGER"),
    ("POSE", "CHALLENGE"), ("POSE", "PROBLEM"), ("POSE", "HAZARD"),
}

# High-confidence determiner/form problems in the broad families.
FORM_FIXES = {
    ("SET", "TABLE"): ("def", "idiomatic collocation is normally 'set the table'"),
    ("SET", "STAGE"): ("def", "idiomatic reading is normally 'set the stage'"),
    ("SET", "SCENE"): ("def", "idiomatic reading is normally 'set the scene'"),
    ("TAKE", "LEAD"): ("def", "idiomatic collocation is normally 'take the lead'"),
    ("TAKE", "INITIATIVE"): ("def", "idiomatic reading is normally 'take the initiative'"),
    ("TAKE", "MEASURE"): ("indef/plural", "bare singular 'take measure' is not the intended collocation"),
    ("TAKE", "PRECAUTION"): ("indef/plural", "bare singular 'take precaution' is not the intended collocation"),
}

# Cases where the current preposition encodes one possible role but is likely
# to be confused with the more salient complement of the predicate.
ROLE_PREP_REVIEW = {
    ("SECURE", "CONTRACT", "from"): "'from NP' is possible for the awarder/source, but 'with NP' is the usual counterpart relation; actant role must be explicit",
    ("SECURE", "DEAL", "from"): "'from NP' selects a source reading; deal counterpart is normally 'with NP'",
    ("SECURE", "AGREEMENT", "from"): "'from NP' selects a source reading; agreement counterpart is normally 'with NP'",
    ("GET", "ACCESS", "from"): "'from NP' encodes provider/source; the object accessed is normally introduced by 'to'",
}

# Same HEAD but clearly different lexical senses/actant structures. These are
# especially important because family fallback picks one relation by priority.
POLYSEMY_HEADS = {
    "CHARGE": "fee/accusation/command senses should not share one semantic HEAD",
    "ORDER": "purchase order vs command/order senses need distinct semantic predicates",
    "CASE": "legal case vs instance/container senses need distinct semantic predicates",
    "POSITION": "job/role vs stance/location senses may need distinct semantic predicates",
    "INTEREST": "curiosity vs financial interest senses should be separated",
    "NOTICE": "notification vs attention/notice senses should be separated",
    "RETURN": "tax return vs return/event senses should be separated",
    "FORM_NOUN": "document/form vs shape/form senses should remain separated if both are added",
}

# Multiple explicit realizations that are not just harmless stylistic synonyms.
ROLE_CONFLICT_VARIANTS = {
    ("support", "PERMISSION", "oper1"): "'give permission' and 'ask permission' have different subject roles",
    ("support", "PROBLEM", "oper1"): "'have a problem' and 'pose a problem' have different subject roles",
    ("support", "RISK", "oper1"): "'take a risk' and 'pose a risk' have different subject roles",
}

# Modifier realizers that often encode salience, phase, rate or extent rather
# than pure intensity. Keep them, but review LF subtype before expanding Magn.
NONPURE_MAGN = {
    "KEY": "salience/importance rather than degree",
    "GROWING": "increase/phase rather than static degree",
    "RAPID": "rate/tempo rather than degree",
    "SHARP": "shape/rate of change rather than pure degree",
    "WIDESPREAD": "distribution/scope rather than degree",
    "TOTAL": "quantification/completeness rather than degree",
    "CRITICAL": "importance/threshold semantics rather than pure degree",
}


def audit():
    gen = load_generator()
    resolved = gen.rows()
    predicate_profiles = gen.load_predicate_profiles()
    support_profiles = gen.load_support_profiles()
    explicit = load_explicit(gen)
    explicit_exact = {exact_key(r) for r in explicit}
    fam_candidates = load_family_candidates(gen)

    variants = defaultdict(list)
    for r in resolved:
        variants[semantic_key(r)].append(r)

    audited = []
    for r in resolved:
        score = 0
        issues = []
        suggestions = []
        origin = "explicit" if exact_key(r) in explicit_exact else "family"
        skey = semantic_key(r)
        fam_opts = sorted(set(fam_candidates.get(skey, [])))

        if origin == "family":
            score += 1
            issues.append("family_generated")
            suggestions.append("manual collocation check")

        if len(fam_opts) > 1:
            score += 2
            issues.append(f"family_competition:{len(fam_opts)}")
            suggestions.append("review competing support/modifier families and sense distinctions")

        if len(variants[skey]) > 1:
            score += 2
            issues.append(f"resolved_variants:{len(variants[skey])}")
            suggestions.append("confirm whether multiple outputs are intended")

        if skey in ROLE_CONFLICT_VARIANTS:
            score += 5
            issues.append("actant_role_conflict")
            suggestions.append(ROLE_CONFLICT_VARIANTS[skey])

        if r["kind"] == "support":
            if r["function"] == "oper2" and r["realizer"] in OPER2_PHASE_RESULT:
                score += 4
                issues.append("lf_phase_or_result")
                suggestions.append("candidate for IncepOper/Real-type LF instead of plain Oper2")

            if (r["realizer"], r["predicate"]) in CAUSATIVE_CASES and not r["function"].startswith("caus"):
                score += 4
                issues.append("lf_causative")
                suggestions.append("candidate for CausOper/CausFunc-type LF")

            ffix = FORM_FIXES.get((r["realizer"], r["predicate"]))
            if ffix and r["form"] != ffix[0]:
                score += 5
                issues.append("determiner_or_countability")
                suggestions.append(ffix[1] + f"; current form={r['form']}")

            prep_issue = ROLE_PREP_REVIEW.get((r["realizer"], r["predicate"], r["prep"]))
            if prep_issue:
                score += 4
                issues.append("actant_preposition")
                suggestions.append(prep_issue)

            if r["predicate"] in POLYSEMY_HEADS:
                score += 3
                issues.append("semantic_head_polysemy")
                suggestions.append(POLYSEMY_HEADS[r["predicate"]])

        if r["kind"] in {"noun_modifier", "adj_modifier"} and r["function"] == "magn":
            if r["realizer"] in NONPURE_MAGN:
                score += 3
                issues.append("magn_semantic_subtype")
                suggestions.append(NONPURE_MAGN[r["realizer"]])

        if score >= 8:
            severity = "critical"
        elif score >= 5:
            severity = "high"
        elif score >= 3:
            severity = "medium"
        elif score:
            severity = "low"
        else:
            severity = "ok"

        pp = predicate_profiles.get(r["predicate"], {})
        sp = support_profiles.get(r["realizer"], {}) if r["kind"] == "support" else {}
        audited.append({
            "severity": severity,
            "score": score,
            "kind": r["kind"],
            "predicate": r["predicate"],
            "function": r["function"],
            "realizer": r["realizer"],
            "form": r["form"],
            "prep": r["prep"],
            "origin": origin,
            "pred_class": pp.get("class", ""),
            "aktionsart": pp.get("aktionsart", ""),
            "semantic_valency": pp.get("semantic_valency", ""),
            "arg1_restriction": pp.get("arg1_restriction", ""),
            "arg2_restriction": pp.get("arg2_restriction", ""),
            "fixedness": pp.get("fixedness", ""),
            "support_aspect": sp.get("lexical_aspect", ""),
            "support_phase": sp.get("phase", ""),
            "support_stance": sp.get("stance", ""),
            "support_subjectivity": sp.get("subjectivity", ""),
            "surface_stub": surface_stub(r),
            "issues": ";".join(issues),
            "suggestion": " | ".join(dict.fromkeys(suggestions)),
            "family_candidates": " | ".join(f"{a}/{b}/{c or '-'}" for a,b,c in fam_opts),
        })

    severity_order = {"critical": 0, "high": 1, "medium": 2, "low": 3, "ok": 4}
    audited.sort(key=lambda x: (severity_order[x["severity"]], -x["score"], x["kind"], x["realizer"], x["predicate"]))

    fields = ["severity", "score", "kind", "predicate", "function", "realizer", "form", "prep", "origin", "pred_class", "aktionsart", "semantic_valency", "arg1_restriction", "arg2_restriction", "fixedness", "support_aspect", "support_phase", "support_stance", "support_subjectivity", "surface_stub", "issues", "suggestion", "family_candidates"]
    with OUT_TSV.open("w", newline="", encoding="utf-8") as fh:
        wr = csv.DictWriter(fh, fieldnames=fields, delimiter="\t", lineterminator="\n")
        wr.writeheader()
        wr.writerows(audited)

    sev = Counter(r["severity"] for r in audited)
    cat = Counter()
    support_by_realizer = defaultdict(lambda: Counter())
    for r in audited:
        for issue in filter(None, r["issues"].split(";")):
            cat[issue.split(":",1)[0]] += 1
        if r["kind"] == "support":
            support_by_realizer[r["realizer"]][r["severity"]] += 1

    review = [r for r in audited if r["severity"] != "ok"]
    top = [r for r in audited if r["severity"] in {"critical", "high"}]

    lines = []
    lines.append("# Elvex English lexical-function quality audit")
    lines.append("")
    lines.append("This report is a deterministic QA pass over the current resolved lexical-function inventory. It does **not** modify the grammar or TSV sources. Flags are review priorities, not automatic linguistic verdicts.")
    lines.append("")
    lines.append("## Summary")
    lines.append("")
    lines.append(f"- Resolved relations: **{len(audited)}**")
    lines.append(f"- Critical: **{sev['critical']}**")
    lines.append(f"- High: **{sev['high']}**")
    lines.append(f"- Medium: **{sev['medium']}**")
    lines.append(f"- Low: **{sev['low']}**")
    lines.append(f"- No automatic flag: **{sev['ok']}**")
    lines.append(f"- Relations requiring some review: **{len(review)}**")
    lines.append(f"- Predicative-noun profiles: **{len(predicate_profiles)}**")
    lines.append(f"- Support-verb discourse/aspect profiles: **{len(support_profiles)}**")
    lines.append("")
    lines.append("## Highest-priority observations")
    lines.append("")
    lines.append("1. **Actant-role conflicts**: a few identical `HEAD + function` keys encode constructions with different grammatical subjects (notably `PERMISSION`, `PROBLEM`, `RISK`). These should be split by lexical function and/or semantic sense before allowing free variants.")
    lines.append("2. **Phase/result semantics inside plain Oper2**: acquisition/result verbs still encoded as `Oper2` remain candidates for `IncepOper`/`Real`-type functions. `GAIN`, `GET`, `OBTAIN`, `SECURE`, `WIN`, and `EARN` are now migrated to `IncepOper2`; this first acquisition/result migration set is complete.")
    lines.append("3. **Causative readings inside Oper1/Oper2**: families such as `ATTRACT interest`, `RAISE awareness`, and `POSE a threat` deserve `Caus*`-type functions instead of being flattened into `Oper`.")
    lines.append("4. **Determiner/countability issues**: the first obvious determiner errors have been corrected; remaining family entries should still be reviewed individually for countability and article choice.")
    lines.append("5. **Semantic-head polysemy**: several orthographic nouns (`CHARGE`, `ORDER`, `CASE`, `INTEREST`, etc.) conflate senses that select different support verbs and actant structures. The family fallback can therefore choose the wrong sense even when every individual collocation is English.")
    lines.append("")
    lines.append("## High / critical relations")
    lines.append("")
    lines.append("| Sev. | Predicate | LF | Realizer | Skeleton | Main issue |")
    lines.append("|---|---|---|---|---|---|")
    for r in top[:120]:
        issue = r["suggestion"].replace("|", "/")
        lines.append(f"| {r['severity']} | `{r['predicate']}` | `{r['function']}` | `{r['realizer']}` | `{r['surface_stub']}` | {issue} |")
    if len(top) > 120:
        lines.append(f"\n_{len(top)-120} additional high/critical rows are in the TSV report._")

    lines.append("")
    lines.append("## Support-verb families")
    lines.append("")
    lines.append("| Support | Critical | High | Medium | Low | OK |")
    lines.append("|---|---:|---:|---:|---:|---:|")
    for realizer in sorted(support_by_realizer):
        c = support_by_realizer[realizer]
        lines.append(f"| `{realizer}` | {c['critical']} | {c['high']} | {c['medium']} | {c['low']} | {c['ok']} |")

    lines.append("")
    lines.append("## Flag categories")
    lines.append("")
    for name, count in sorted(cat.items(), key=lambda kv: (-kv[1], kv[0])):
        lines.append(f"- `{name}`: {count}")

    lines.append("")
    lines.append("## Recommended correction order")
    lines.append("")
    lines.append("1. Fix determiner/countability errors and obvious actant-preposition mismatches.")
    lines.append("2. Split polysemous semantic heads where the collocations belong to different senses.")
    lines.append("3. Keep the validated `GAIN` + `GET` + `OBTAIN` + `SECURE` + `WIN` + `EARN` `IncepOper2` families under regression while introducing the next lexical-function class.")
    lines.append("4. Introduce and validate one `CausOper/CausFunc` example, then migrate causative families.")
    lines.append("5. Review lower-priority family-generated collocations by support verb; keep the explicit curated TSV authoritative.")
    lines.append("")
    lines.append("The complete row-level audit, including all family alternatives considered by the fallback resolver, is in `en-lexical-functions-quality.tsv`.")

    OUT_MD.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return audited, sev, cat


def main():
    audited, sev, cat = audit()
    print(f"audited {len(audited)} relations: critical={sev['critical']} high={sev['high']} medium={sev['medium']} low={sev['low']} ok={sev['ok']}")
    print(f"wrote {OUT_TSV.name} and {OUT_MD.name}")


if __name__ == "__main__":
    main()
