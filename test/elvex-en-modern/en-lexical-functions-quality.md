# Elvex English lexical-function quality audit

This report is a deterministic QA pass over the current resolved lexical-function inventory. It does **not** modify the grammar or TSV sources. Flags are review priorities, not automatic linguistic verdicts.

## Summary

- Resolved relations: **1512**
- Critical: **8**
- High: **28**
- Medium: **450**
- Low: **911**
- No automatic flag: **115**
- Relations requiring some review: **1397**

## Highest-priority observations

1. **Actant-role conflicts**: a few identical `HEAD + function` keys encode constructions with different grammatical subjects (notably `PERMISSION`, `PROBLEM`, `RISK`). These should be split by lexical function and/or semantic sense before allowing free variants.
2. **Phase/result semantics inside plain Oper2**: acquisition/result verbs still encoded as `Oper2` remain candidates for `IncepOper`/`Real`-type functions. `GAIN`, `GET`, `OBTAIN`, `SECURE`, `WIN`, and `EARN` are now migrated to `IncepOper2`; this first acquisition/result migration set is complete.
3. **Causative readings inside Oper1/Oper2**: families such as `ATTRACT interest`, `RAISE awareness`, and `POSE a threat` deserve `Caus*`-type functions instead of being flattened into `Oper`.
4. **Determiner/countability issues**: the first obvious determiner errors have been corrected; remaining family entries should still be reviewed individually for countability and article choice.
5. **Semantic-head polysemy**: several orthographic nouns (`CHARGE`, `ORDER`, `CASE`, `INTEREST`, etc.) conflate senses that select different support verbs and actant structures. The family fallback can therefore choose the wrong sense even when every individual collocation is English.

## High / critical relations

| Sev. | Predicate | LF | Realizer | Skeleton | Main issue |
|---|---|---|---|---|---|
| critical | `PROBLEM` | `oper1` | `POSE` | `pose a/an problem for NP` | review competing support/modifier families and sense distinctions / confirm whether multiple outputs are intended / 'have a problem' and 'pose a problem' have different subject roles / candidate for CausOper/CausFunc-type LF |
| critical | `RISK` | `oper1` | `POSE` | `pose a/an risk to NP` | review competing support/modifier families and sense distinctions / confirm whether multiple outputs are intended / 'take a risk' and 'pose a risk' have different subject roles / candidate for CausOper/CausFunc-type LF |
| critical | `PERMISSION` | `oper1` | `ASK` | `ask permission` | review competing support/modifier families and sense distinctions / confirm whether multiple outputs are intended / 'give permission' and 'ask permission' have different subject roles |
| critical | `PERMISSION` | `oper1` | `GIVE` | `give permission to NP` | review competing support/modifier families and sense distinctions / confirm whether multiple outputs are intended / 'give permission' and 'ask permission' have different subject roles |
| critical | `PROBLEM` | `oper1` | `HAVE` | `have a/an problem with NP` | review competing support/modifier families and sense distinctions / confirm whether multiple outputs are intended / 'have a problem' and 'pose a problem' have different subject roles |
| critical | `RISK` | `oper1` | `TAKE` | `take a/an risk` | review competing support/modifier families and sense distinctions / confirm whether multiple outputs are intended / 'take a risk' and 'pose a risk' have different subject roles |
| critical | `INTEREST` | `oper2` | `ATTRACT` | `attract interest` | manual collocation check / candidate for CausOper/CausFunc-type LF / curiosity vs financial interest senses should be separated |
| critical | `INITIATIVE` | `oper1` | `TAKE` | `take a/an initiative in NP` | manual collocation check / review competing support/modifier families and sense distinctions / idiomatic reading is normally 'take the initiative'; current form=indef |
| high | `DANGER` | `oper1` | `POSE` | `pose a/an danger to NP` | manual collocation check / review competing support/modifier families and sense distinctions / candidate for CausOper/CausFunc-type LF |
| high | `HAZARD` | `oper1` | `POSE` | `pose a/an hazard to NP` | manual collocation check / review competing support/modifier families and sense distinctions / candidate for CausOper/CausFunc-type LF |
| high | `CONTRACT` | `incepoper2` | `SECURE` | `secure a/an contract from NP` | manual collocation check / review competing support/modifier families and sense distinctions / 'from NP' is possible for the awarder/source, but 'with NP' is the usual counterpart relation; actant role must be explicit |
| high | `POINT` | `magn` | `CRITICAL` | `critical point` | manual collocation check / review competing support/modifier families and sense distinctions / importance/threshold semantics rather than pure degree |
| high | `REQUIREMENT` | `magn` | `CRITICAL` | `critical requirement` | manual collocation check / review competing support/modifier families and sense distinctions / importance/threshold semantics rather than pure degree |
| high | `ADOPTION` | `magn` | `RAPID` | `rapid adoption` | manual collocation check / review competing support/modifier families and sense distinctions / rate/tempo rather than degree |
| high | `ADVANCE` | `magn` | `RAPID` | `rapid advance` | manual collocation check / review competing support/modifier families and sense distinctions / rate/tempo rather than degree |
| high | `FALL` | `magn` | `SHARP` | `sharp fall` | manual collocation check / review competing support/modifier families and sense distinctions / shape/rate of change rather than pure degree |
| high | `RISE` | `magn` | `SHARP` | `sharp rise` | manual collocation check / review competing support/modifier families and sense distinctions / shape/rate of change rather than pure degree |
| high | `REVENUE` | `magn` | `TOTAL` | `total revenue` | manual collocation check / review competing support/modifier families and sense distinctions / quantification/completeness rather than degree |
| high | `FORM_NOUN` | `oper1` | `FILE` | `file a/an form` | manual collocation check / review competing support/modifier families and sense distinctions / document/form vs shape/form senses should remain separated if both are added |
| high | `POSITION` | `incepoper2` | `GET` | `get a/an position` | manual collocation check / review competing support/modifier families and sense distinctions / job/role vs stance/location senses may need distinct semantic predicates |
| high | `CHARGE` | `oper1` | `IMPOSE` | `impose a/an charge on NP` | manual collocation check / review competing support/modifier families and sense distinctions / fee/accusation/command senses should not share one semantic HEAD |
| high | `CHALLENGE` | `oper1` | `POSE` | `pose a/an challenge to NP` | review competing support/modifier families and sense distinctions / candidate for CausOper/CausFunc-type LF |
| high | `THREAT` | `oper1` | `POSE` | `pose a/an threat to NP` | review competing support/modifier families and sense distinctions / candidate for CausOper/CausFunc-type LF |
| high | `AWARENESS` | `oper1` | `RAISE` | `raise awareness of NP` | review competing support/modifier families and sense distinctions / candidate for CausOper/CausFunc-type LF |
| high | `MEASURE` | `oper1` | `TAKE` | `take a/an measure` | manual collocation check / bare singular 'take measure' is not the intended collocation; current form=indef |
| high | `POSITION` | `oper1` | `TAKE` | `take a/an position` | manual collocation check / review competing support/modifier families and sense distinctions / job/role vs stance/location senses may need distinct semantic predicates |
| high | `PRECAUTION` | `oper1` | `TAKE` | `take a/an precaution` | manual collocation check / bare singular 'take precaution' is not the intended collocation; current form=indef |
| high | `CONCERN` | `oper2` | `ATTRACT` | `attract concern` | manual collocation check / candidate for CausOper/CausFunc-type LF |
| high | `CONTROVERSY` | `oper2` | `ATTRACT` | `attract controversy` | manual collocation check / candidate for CausOper/CausFunc-type LF |
| high | `SUSPICION` | `oper2` | `ATTRACT` | `attract suspicion` | manual collocation check / candidate for CausOper/CausFunc-type LF |
| high | `NOTICE` | `oper1` | `GIVE` | `give notice` | review competing support/modifier families and sense distinctions / notification vs attention/notice senses should be separated |
| high | `ORDER` | `oper1` | `PLACE` | `place a/an order` | review competing support/modifier families and sense distinctions / purchase order vs command/order senses need distinct semantic predicates |
| high | `CAPITAL` | `oper1` | `RAISE` | `raise capital` | manual collocation check / candidate for CausOper/CausFunc-type LF |
| high | `AGREEMENT` | `incepoper2` | `SECURE` | `secure a/an agreement from NP` | manual collocation check / 'from NP' selects a source reading; agreement counterpart is normally 'with NP' |
| high | `DEAL` | `incepoper2` | `SECURE` | `secure a/an deal from NP` | manual collocation check / 'from NP' selects a source reading; deal counterpart is normally 'with NP' |
| high | `INTEREST` | `oper1` | `TAKE` | `take a/an interest in NP` | review competing support/modifier families and sense distinctions / curiosity vs financial interest senses should be separated |

## Support-verb families

| Support | Critical | High | Medium | Low | OK |
|---|---:|---:|---:|---:|---:|
| `ACCEPT` | 0 | 0 | 0 | 1 | 0 |
| `ACHIEVE` | 0 | 0 | 0 | 1 | 3 |
| `ASK` | 1 | 0 | 1 | 0 | 1 |
| `ASSUME` | 0 | 0 | 1 | 0 | 0 |
| `ATTRACT` | 1 | 3 | 0 | 2 | 0 |
| `BEAR` | 0 | 0 | 0 | 4 | 0 |
| `CONDUCT` | 0 | 0 | 9 | 4 | 0 |
| `DO` | 0 | 0 | 0 | 8 | 0 |
| `DRAW` | 0 | 0 | 0 | 9 | 0 |
| `EARN` | 0 | 0 | 0 | 4 | 0 |
| `ENJOY` | 0 | 0 | 1 | 17 | 0 |
| `EXERCISE` | 0 | 0 | 1 | 3 | 0 |
| `EXERT` | 0 | 0 | 1 | 0 | 0 |
| `EXPERIENCE` | 0 | 0 | 4 | 19 | 1 |
| `EXPRESS` | 0 | 0 | 1 | 13 | 0 |
| `FACE` | 0 | 0 | 2 | 14 | 0 |
| `FILE` | 0 | 1 | 3 | 2 | 0 |
| `GAIN` | 0 | 0 | 14 | 17 | 0 |
| `GET` | 0 | 1 | 23 | 14 | 0 |
| `GIVE` | 1 | 1 | 24 | 28 | 3 |
| `HAVE` | 1 | 0 | 31 | 38 | 6 |
| `HOLD` | 0 | 0 | 8 | 16 | 0 |
| `IMPOSE` | 0 | 1 | 11 | 4 | 0 |
| `MAKE` | 0 | 0 | 14 | 46 | 17 |
| `MEET` | 0 | 0 | 4 | 14 | 0 |
| `OBTAIN` | 0 | 0 | 1 | 5 | 0 |
| `OFFER` | 0 | 0 | 0 | 5 | 0 |
| `PAY` | 0 | 0 | 8 | 6 | 1 |
| `PERFORM` | 0 | 0 | 4 | 3 | 0 |
| `PLACE` | 0 | 1 | 0 | 4 | 0 |
| `PLAY` | 0 | 0 | 0 | 1 | 3 |
| `POSE` | 2 | 4 | 1 | 1 | 0 |
| `PROVIDE` | 0 | 0 | 7 | 10 | 0 |
| `PUT` | 0 | 0 | 0 | 2 | 2 |
| `RAISE` | 0 | 2 | 3 | 5 | 1 |
| `REACH` | 0 | 0 | 0 | 9 | 1 |
| `RECEIVE` | 0 | 0 | 3 | 28 | 26 |
| `SECURE` | 0 | 3 | 2 | 3 | 0 |
| `SET` | 0 | 0 | 7 | 23 | 0 |
| `SHOW` | 0 | 0 | 12 | 6 | 0 |
| `SUBMIT` | 0 | 0 | 1 | 1 | 0 |
| `SUFFER` | 0 | 0 | 7 | 15 | 1 |
| `TAKE` | 2 | 4 | 11 | 24 | 3 |
| `UNDERGO` | 0 | 0 | 0 | 28 | 4 |
| `WIN` | 0 | 0 | 2 | 13 | 0 |

## Flag categories

- `family_generated`: 1185
- `family_competition`: 617
- `magn_semantic_subtype`: 37
- `resolved_variants`: 28
- `lf_causative`: 13
- `semantic_head_polysemy`: 13
- `actant_role_conflict`: 6
- `actant_preposition`: 3
- `determiner_or_countability`: 3

## Recommended correction order

1. Fix determiner/countability errors and obvious actant-preposition mismatches.
2. Split polysemous semantic heads where the collocations belong to different senses.
3. Keep the validated `GAIN` + `GET` + `OBTAIN` + `SECURE` + `WIN` + `EARN` `IncepOper2` families under regression while introducing the next lexical-function class.
4. Introduce and validate one `CausOper/CausFunc` example, then migrate causative families.
5. Review lower-priority family-generated collocations by support verb; keep the explicit curated TSV authoritative.

The complete row-level audit, including all family alternatives considered by the fallback resolver, is in `en-lexical-functions-quality.tsv`.
