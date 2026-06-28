#!/usr/bin/env python3
from __future__ import annotations

import argparse, csv, json, os, re, subprocess, sys
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[1]

try:
    from sacrebleu.metrics import BLEU, CHRF
except Exception:  # pragma: no cover - shown to user as metric unavailable
    BLEU = None
    CHRF = None

_BLEU = BLEU(effective_order=True) if BLEU is not None else None
_CHRF = CHRF() if CHRF is not None else None


def default_index(size: int) -> Path:
    if size == 1:
        return ROOT / "build/inputs/simple_triples.index.tsv"
    return ROOT / f"build/inputs/{size}_triples.index.tsv"


def read_index(index_path: Path) -> list[dict[str, str]]:
    if not index_path.exists():
        raise SystemExit(f"Index not found: {index_path}. Run ./run inputs {infer_size(index_path)} first.")
    with index_path.open(encoding="utf-8", newline="") as f:
        return list(csv.DictReader(f, delimiter="\t"))


def infer_size(path: Path) -> str:
    name = path.name
    if name.startswith("simple_triples"):
        return "1"
    return name.split("_", 1)[0] if "_" in name else "<n>"


def find_row(rows: list[dict[str, str]], selector: str) -> dict[str, str]:
    for row in rows:
        if row.get("ordinal") == selector:
            return row
    for row in rows:
        if row.get("input_file") == selector or Path(row.get("input_file", "")).name == selector:
            return row
    raise SystemExit(f"No input found for selector: {selector}")


def decode_json(value: str, default: Any) -> Any:
    try:
        return json.loads(value) if value else default
    except json.JSONDecodeError:
        return default


def format_triples(triples: list[dict[str, str]]) -> str:
    return "\n".join(f"  - {t.get('subject','')} | {t.get('predicate','')} | {t.get('object','')}" for t in triples)


def format_refs(refs: list[str], limit: int = 5) -> str:
    if not refs:
        return "  (no WebNLG reference found in extracted source)"
    out = []
    for i, ref in enumerate(refs[:limit], start=1):
        out.append(f"  {i}. {ref}")
    if len(refs) > limit:
        out.append(f"  ... {len(refs) - limit} more reference(s)")
    return "\n".join(out)


def one_line(value: Any) -> str:
    """Make a compact, TSV-friendly display cell."""
    if value is None:
        return ""
    text = str(value)
    text = re.sub(r"[\r\n\t]+", " ", text)
    text = re.sub(r"\s+", " ", text).strip()
    return text


def one_line_triples(triples: list[dict[str, str]]) -> str:
    return " || ".join(
        one_line(f"{t.get('subject','')} | {t.get('predicate','')} | {t.get('object','')}")
        for t in triples
    )


def one_line_list(values: list[str]) -> str:
    return " || ".join(one_line(v) for v in values)


def row_context(row: dict[str, str]) -> dict[str, str]:
    triples = decode_json(row.get("triples_json", ""), [])
    refs = decode_json(row.get("references_json", ""), [])
    return {
        "ordinal": row.get("ordinal", ""),
        "input_file": row.get("input_file", ""),
        "entry_id": row.get("entry_id", ""),
        "n_triples": row.get("n_triples", ""),
        "triples_text": format_triples(triples),
        "references_text": format_refs(refs),
        "first_reference": refs[0] if refs else "",
        "references_json": json.dumps(refs, ensure_ascii=False, separators=(",", ":")),
    }


def print_context(ctx: dict[str, str]) -> None:
    print("INPUT FILE", flush=True)
    print(f"  {ctx['input_file']}", flush=True)
    print("\nENTRY", flush=True)
    print(f"  {ctx['entry_id']} ({ctx['n_triples']} triple(s))", flush=True)
    print("\nTRIPLE(S)", flush=True)
    print(ctx["triples_text"], flush=True)
    print("\nWEBNLG REFERENCE(S)", flush=True)
    print(ctx["references_text"], flush=True)


def output_lines(stdout: str) -> list[str]:
    return [line.strip() for line in stdout.splitlines() if line.strip()]


def finalize_sentence(text: str) -> str:
    """Apply the project final surface policy to one Elvex output."""
    text = text.strip()
    text = text.replace("_", " ")
    text = re.sub(r"[ \t]+", " ", text)
    text = DBPEDIA_DISAMBIG_RE.sub("", text)
    # v34 cleanup for WebNLG pilot frames.
    text = re.sub(r"\s+'s\b", "'s", text)
    text = re.sub(r"\b([A-Za-z]+)\s*,\s*(\d{4})\b", r"\1 \2", text)
    text = text.replace("(dollars)", "dollars")
    text = re.sub(r"\bFLOOR COUNT NOUN\b", "floor count", text)
    text = re.sub(r"\bTOTAL AREA NOUN\b", "total area", text)
    text = re.sub(r"\bWATER AREA NOUN\b", "water area", text)
    text = re.sub(r"\bPOPULATION DENSITY NOUN\b", "population density", text)
    text = re.sub(r"\bAVERAGE SPEED NOUN\b", "average speed", text)
    text = re.sub(r"\bESCAPE VELOCITY NOUN\b", "escape velocity", text)
    text = re.sub(r"\bORBITAL PERIOD NOUN\b", "orbital period", text)
    text = re.sub(r"\bPERIAPSIS NOUN\b", "periapsis", text)
    text = re.sub(r"\bAPOAPSIS NOUN\b", "apoapsis", text)
    text = re.sub(r"\bMASS NOUN\b", "mass", text)
    text = re.sub(r"\bTEMPERATURE NOUN\b", "temperature", text)
    text = re.sub(r"\bAREA CODE NOUN\b", "area code", text)
    text = re.sub(r"\bFORMER NAME NOUN\b", "former name", text)
    text = re.sub(r"\bLARGEST CITY NOUN\b", "largest city", text)
    # POSS_S_REPAIR_V34

    text = MC_NAME_RE.sub(r"Mc\1", text)
    # Elvex lexicalizes the indefinite article as "a"; postproduction
    # converts it before vowel-initial forms.
    text = re.sub(r"\ba\s+([aeiouAEIOU])", r"an \1", text)
    text = re.sub(r"\ba Singing\b", "a singer", text)
    text = re.sub(r"\bSinging is\b", "A singer is", text)
    text = re.sub(r"\s+([.,;:!?])", r"\1", text)
    # Avoid turning final abbreviations like U.S. into U.S.. after dot cleanup.
    text = re.sub(r"\b((?:[A-Za-z]\.){2,})\.", r"\1", text)
    if not text:
        return text
    return text[0].upper() + text[1:]

def finalize_outputs(outputs: list[str]) -> list[str]:
    seen: set[str] = set()
    final: list[str] = []
    for out in outputs:
        f = finalize_sentence(out)
        if f and f not in seen:
            seen.add(f)
            final.append(f)
    return final


def normalize_text(text: str) -> str:
    """Small diagnostic normalizer, not an official WebNLG metric.

    It ignores case, repeated whitespace and spaces before punctuation.  It also
    normalizes a few WebNLG surface variants that are not semantically relevant
    for the current development diagnostics: British/American metres/meters and
    ordinal words/digits for runway descriptions.
    """
    text = text.strip()
    text = re.sub(r"\s+", " ", text)
    text = re.sub(r"\s+([.,;:!?])", r"\1", text)
    text = text.casefold()
    text = re.sub(r"\bmetres\b", "meters", text)
    text = re.sub(r"\borganisation\b", "organization", text)
    text = re.sub(r"\b1st\b", "first", text)
    text = re.sub(r"\b2nd\b", "second", text)
    text = re.sub(r"\b3rd\b", "third", text)
    text = re.sub(r"\b4th\b", "fourth", text)
    text = re.sub(r"\b5th\b", "fifth", text)
    return text


def exact_match(outputs: list[str], refs: list[str]) -> tuple[bool, str, str, int]:
    for i, out in enumerate(outputs, start=1):
        for ref in refs:
            if out == ref:
                return True, out, ref, i
    return False, "", "", 0


def normalized_match(outputs: list[str], refs: list[str]) -> tuple[bool, str, str, int]:
    norm_refs = [(normalize_text(ref), ref) for ref in refs]
    for i, out in enumerate(outputs, start=1):
        no = normalize_text(out)
        for nr, ref in norm_refs:
            if no == nr:
                return True, out, ref, i
    return False, "", "", 0


def sacrebleu_scores(outputs: list[str], refs: list[str]) -> dict[str, str]:
    """Return best sentence-level sacreBLEU BLEU and chrF over all outputs.

    Elvex outputs are an unordered set, so these are development best-of-N
    diagnostic scores, not official single-output corpus scores.
    """
    if not outputs or not refs or _BLEU is None or _CHRF is None:
        return {
            "sacrebleu_available": "no" if (_BLEU is None or _CHRF is None) else "yes",
            "best_bleu": "", "best_bleu_rank": "", "best_bleu_output": "",
            "best_chrf": "", "best_chrf_rank": "", "best_chrf_output": "",
        }
    best_bleu = (-1.0, 0, "")
    best_chrf = (-1.0, 0, "")
    for i, out in enumerate(outputs, start=1):
        bleu = float(_BLEU.sentence_score(out, refs).score)
        chrf = float(_CHRF.sentence_score(out, refs).score)
        if bleu > best_bleu[0]:
            best_bleu = (bleu, i, out)
        if chrf > best_chrf[0]:
            best_chrf = (chrf, i, out)
    return {
        "sacrebleu_available": "yes",
        "best_bleu": f"{best_bleu[0]:.2f}",
        "best_bleu_rank": str(best_bleu[1]),
        "best_bleu_output": best_bleu[2],
        "best_chrf": f"{best_chrf[0]:.2f}",
        "best_chrf_rank": str(best_chrf[1]),
        "best_chrf_output": best_chrf[2],
    }


def run_elvex(
    input_file: Path,
    max_length: int,
    max_items: int,
    max_time: int,
    process_timeout: int,
    first_only: bool = False,
) -> tuple[int, str, str]:
    cmd = [
        "elvex",
        "--macros-file", str(ROOT / "user/main.macros"),
        "--rules-file", str(ROOT / "user/main.rules"),
        "--lexicon-file", str(ROOT / "user/main.lexicon"),
        "--compacted-lexicon-file", str(ROOT / "build/lexicon/main"),
        "--input-file", str(input_file),
        "--max-length", str(max_length),
        "--max-items", str(max_items),
        "--max-time", str(max_time),
    ]
    if first_only:
        cmd.append("--first")
    try:
        proc = subprocess.run(cmd, cwd=ROOT, text=True, capture_output=True, timeout=process_timeout)
        return proc.returncode, proc.stdout.strip(), proc.stderr.strip()
    except subprocess.TimeoutExpired as e:
        out = (e.stdout or "")
        err = (e.stderr or "")
        if isinstance(out, bytes):
            out = out.decode("utf-8", errors="replace")
        if isinstance(err, bytes):
            err = err.decode("utf-8", errors="replace")
        err = (err.strip() + "\n" if err.strip() else "") + f"Process timeout after {process_timeout}s."
        return 124, out.strip(), err.strip()



NUMBER_RE = re.compile(r"\b\d+(?:\.\d+)?\b")
DBPEDIA_DISAMBIG_RE = re.compile(r"\s+\((?:band|singer|musician|album|song|record_label|record label|comics?|comic(?:s)? character|character|novel|film|movie|book|publication|restaurant|company)\)", re.I)
MC_NAME_RE = re.compile(r"\bMc ([A-Z])")


def predicate_heads(row: dict[str, str]) -> set[str]:
    triples = decode_json(row.get("triples_json", ""), [])
    return {str(t.get("predicate", "")) for t in triples}


def _replace_numbers(text: str, repl) -> str:
    def sub(m: re.Match[str]) -> str:
        value = m.group(0)
        try:
            return repl(value)
        except Exception:
            return value
    return NUMBER_RE.sub(sub, text)


def normalize_numeric_output_for_webnlg(text: str, row: dict[str, str]) -> str:
    """Small, predicate-aware numeric postproduction for WebNLG-style scoring.

    This is intentionally conservative and only handles patterns seen in the
    current single-triple development batch:
    - runwayLength values may be rounded to one decimal place: 2899.87 -> 2900.0;
    - elevation values may be rounded to an integer: 210.312 -> 210.
    """
    preds = predicate_heads(row)
    if "runwayLength" in preds:
        def runway_round(v: str) -> str:
            x = float(v)
            # Keep already one-decimal or integer values unchanged.
            if "." in v and len(v.split(".", 1)[1]) <= 1:
                return v
            return f"{round(x):.1f}"
        return _replace_numbers(text, runway_round)
    if preds & {"elevation", "elevationM", "elevationAboveTheSeaLevel_(in_metres)"}:
        def elevation_round(v: str) -> str:
            x = float(v)
            return str(int(round(x)))
        return _replace_numbers(text, elevation_round)
    return text


def apply_webnlg_postproduction(outputs: list[str], row: dict[str, str]) -> list[str]:
    seen: set[str] = set()
    final: list[str] = []
    for out in outputs:
        n = normalize_numeric_output_for_webnlg(out, row)
        if n and n not in seen:
            seen.add(n)
            final.append(n)
        if out and out not in seen:
            # Keep the faithful/raw-number variant as a secondary alternative.
            seen.add(out)
            final.append(out)
    return final


def compare_one(
    row: dict[str, str],
    max_length: int,
    max_items: int,
    max_time: int,
    process_timeout: int,
    first_only: bool = False,
    write_outputs: bool = True,
) -> dict[str, str]:
    input_file = ROOT / row["input_file"]
    code, stdout, err = run_elvex(input_file, max_length, max_items, max_time, process_timeout, first_only=first_only)
    ctx = row_context(row)
    refs = decode_json(ctx.get("references_json", ""), [])
    raw_outputs = output_lines(stdout)
    outputs = apply_webnlg_postproduction(finalize_outputs(raw_outputs), row)
    status = "ok" if code == 0 else "error"
    first_output = outputs[0] if outputs else ""

    exact_ok, exact_out, exact_ref, exact_rank = exact_match(outputs, refs)
    norm_ok, norm_out, norm_ref, norm_rank = normalized_match(outputs, refs)
    metric_scores = sacrebleu_scores(outputs, refs)

    if write_outputs:
        out_dir = ROOT / "build/outputs/compare"
        log_dir = ROOT / "build/logs/elvex"
        out_dir.mkdir(parents=True, exist_ok=True)
        log_dir.mkdir(parents=True, exist_ok=True)
        stem = Path(row["input_file"]).stem
        (out_dir / f"{stem}.raw.out").write_text(stdout + ("\n" if stdout else ""), encoding="utf-8")
        (out_dir / f"{stem}.out").write_text("\n".join(outputs) + ("\n" if outputs else ""), encoding="utf-8")
        (out_dir / f"{stem}.all.tsv").write_text(
            "rank\toutput\n" + "".join(f"{i}\t{o.replace(chr(9), ' ')}\n" for i, o in enumerate(outputs, start=1)),
            encoding="utf-8",
        )
        (log_dir / f"{stem}.err").write_text(err + ("\n" if err else ""), encoding="utf-8")

    triples = decode_json(row.get("triples_json", ""), [])

    return {
        **ctx,
        "status": status,
        "n_outputs": str(len(outputs)),
        "first_output": first_output,
        # Human-readable report columns requested for build/reports/comparison_*.tsv.
        "input file": row.get("input_file", ""),
        "n-triples": row.get("n_triples", ""),
        "n outputs": str(len(outputs)),  # backward-compatible internal alias
        "n Elvex outputs": str(len(outputs)),
        "n WebNLG outputs": str(len(refs)),
        "WebNLG triples": one_line_triples(triples),
        "WebNLG outputs": one_line_list(refs),
        "Elvex outputs": one_line_list(outputs),
        "best exact match": "yes" if exact_ok else "no",
        "best formatted match": "yes" if norm_ok else "no",
        "best BLEU": metric_scores.get("best_bleu", ""),
        "best CHRF": metric_scores.get("best_chrf", ""),
        # Internal/debug values used by one-mode display and downstream diagnostics.
        "raw_outputs_json": json.dumps(raw_outputs, ensure_ascii=False, separators=(",", ":")),
        "all_outputs_json": json.dumps(outputs, ensure_ascii=False, separators=(",", ":")),
        "best_exact_match": "yes" if exact_ok else "no",
        "best_exact_rank": str(exact_rank or ""),
        "best_exact_output": exact_out,
        "best_exact_reference": exact_ref,
        "best_normalized_match": "yes" if norm_ok else "no",
        "best_normalized_rank": str(norm_rank or ""),
        "best_normalized_output": norm_out,
        "best_normalized_reference": norm_ref,
        **metric_scores,
        "error": err,
    }


def print_outputs(outputs: list[str], limit: int = 20) -> None:
    if not outputs:
        print("  (empty output)", flush=True)
        return
    for i, out in enumerate(outputs[:limit], start=1):
        print(f"  {i}. {out}", flush=True)
    if len(outputs) > limit:
        print(f"  ... {len(outputs) - limit} more output(s)", flush=True)


def print_result_tail(result: dict[str, str]) -> None:
    outputs = decode_json(result.get("all_outputs_json", ""), [])
    print("\nELVEX OUTPUTS", flush=True)
    if result["status"] == "ok":
        print_outputs(outputs)
    else:
        print("  (elvex failed)", flush=True)
        if outputs:
            print("\nPARTIAL OUTPUTS", flush=True)
            print_outputs(outputs)

    print("\nMATCH SUMMARY", flush=True)
    print(f"  best exact match:       {result.get('best_exact_match', 'no')}", flush=True)
    if result.get("best_exact_match") == "yes":
        print(f"  best exact rank:        {result.get('best_exact_rank')}", flush=True)
    print(f"  best normalized match:  {result.get('best_normalized_match', 'no')}", flush=True)
    if result.get("best_normalized_match") == "yes":
        print(f"  best normalized rank:   {result.get('best_normalized_rank')}", flush=True)
        print(f"  matched output:         {result.get('best_normalized_output')}", flush=True)
        print(f"  matched reference:      {result.get('best_normalized_reference')}", flush=True)
    if result.get("sacrebleu_available") == "yes":
        print(f"  sacreBLEU BLEU:         {result.get('best_bleu')} (best-of-N rank {result.get('best_bleu_rank')})", flush=True)
        print(f"  sacreBLEU chrF:         {result.get('best_chrf')} (best-of-N rank {result.get('best_chrf_rank')})", flush=True)
    else:
        print("  sacreBLEU:              unavailable; run ./run setup", flush=True)

    if result["error"]:
        print("\nELVEX STDERR", flush=True)
        print(result["error"], flush=True)


def print_one(result: dict[str, str]) -> None:
    print_context(result)
    print_result_tail(result)


def write_report(results: list[dict[str, str]], path: Path) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    # Keep the batch reports compact and directly inspectable.
    # Machine-readable/debug values remain available in build/outputs/compare/*.all.tsv
    # and through `./run compare-one ...`.
    fields = [
        "ordinal",
        "n-triples",
        "n Elvex outputs",
        "n WebNLG outputs",
        "WebNLG triples",
        "WebNLG outputs",
        "Elvex outputs",
        "best exact match",
        "best formatted match",
        "best BLEU",
        "best CHRF",
    ]
    with path.open("w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fields, delimiter="\t")
        writer.writeheader()
        for r in results:
            writer.writerow({k: r.get(k, "") for k in fields})



def progress_bar(done: int, total: int, width: int = 28) -> str:
    if total <= 0:
        return f"[{done}]"
    done = max(0, min(done, total))
    filled = int(width * done / total)
    pct = int(100 * done / total)
    return "[" + "#" * filled + " " * (width - filled) + f"] {done}/{total} {pct:3d}%"


def print_progress(done: int, total: int, *, final: bool = False) -> None:
    # stderr keeps stdout usable for redirection, e.g. ./run score ... > log.txt
    end = "\n" if final else "\r"
    print(progress_bar(done, total), end=end, file=sys.stderr, flush=True)

def main() -> int:
    ap = argparse.ArgumentParser(description="Run Elvex on generated inputs and compare all outputs with WebNLG references")
    ap.add_argument("mode", choices=["one", "batch"])
    ap.add_argument("size", type=int, nargs="?", default=1, help="Number of triples per input set")
    ap.add_argument("selector", nargs="?", default="1", help="Ordinal or input filename for mode=one; limit for mode=batch")
    ap.add_argument("--index", default=None)
    ap.add_argument("--max-length", type=int, default=80)
    ap.add_argument("--max-items", type=int, default=int(os.environ.get("ELVEX_MAX_ITEMS", "200000")))
    ap.add_argument("--max-time", type=int, default=int(os.environ.get("ELVEX_MAX_TIME", "10")))
    ap.add_argument("--process-timeout", type=int, default=int(os.environ.get("ELVEX_PROCESS_TIMEOUT", "15")))
    ap.add_argument("--first-only", action="store_true", help="Pass --first to elvex. Default is to keep all generated outputs.")
    ap.add_argument("--report", default=None)
    ap.add_argument("--no-progress", action="store_true", help="Disable the batch progress bar on stderr")
    args = ap.parse_args()

    index_path = Path(args.index) if args.index else default_index(args.size)
    rows = read_index(index_path)
    if not rows:
        raise SystemExit(f"Index is empty: {index_path}")

    if args.mode == "one":
        row = find_row(rows, args.selector)
        ctx = row_context(row)
        print_context(ctx)
        print("\nRUNNING ELVEX", flush=True)
        mode = "first output only" if args.first_only else "all outputs"
        print(f"  mode={mode}; max_time={args.max_time}s; process_timeout={args.process_timeout}s; max_items={args.max_items}", flush=True)
        result = compare_one(row, args.max_length, args.max_items, args.max_time, args.process_timeout, first_only=args.first_only)
        print_result_tail(result)
        return 0 if result["status"] == "ok" else 1

    limit = int(args.selector or "20")
    selected = rows if limit == 0 else rows[:limit]
    results = []
    total = len(selected)
    if not args.no_progress:
        print_progress(0, total)
    for i, row in enumerate(selected, start=1):
        results.append(compare_one(row, args.max_length, args.max_items, args.max_time, args.process_timeout, first_only=args.first_only))
        if not args.no_progress:
            print_progress(i, total, final=(i == total))
    report = Path(args.report) if args.report else ROOT / f"build/reports/comparison_{args.size}_triples.tsv"
    write_report(results, report)
    ok = sum(1 for r in results if r["status"] == "ok")
    failed = len(results) - ok
    best_exact = sum(1 for r in results if r.get("best_exact_match") == "yes")
    best_norm = sum(1 for r in results if r.get("best_normalized_match") == "yes")
    bleu_values = [float(r["best_bleu"]) for r in results if r.get("best_bleu")]
    chrf_values = [float(r["best_chrf"]) for r in results if r.get("best_chrf")]
    print(f"Compared: {len(results)}; ok: {ok}; failed: {failed}")
    print(f"Best-of-N exact matches: {best_exact}")
    print(f"Best-of-N normalized matches: {best_norm}")
    if bleu_values and chrf_values:
        print(f"Mean best-of-N sacreBLEU BLEU: {sum(bleu_values) / len(bleu_values):.2f}")
        print(f"Mean best-of-N sacreBLEU chrF: {sum(chrf_values) / len(chrf_values):.2f}")
    else:
        print("sacreBLEU metrics unavailable; run ./run setup")
    print(f"Report: {report}")
    if results:
        print("\nFirst comparison:\n")
        print_one(results[0])
    return 0 if failed == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
