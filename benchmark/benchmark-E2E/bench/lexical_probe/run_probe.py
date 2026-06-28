#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import subprocess
import time
from pathlib import Path

def parse_outputs(stdout: str) -> list[str]:
    outs = []
    for line in stdout.splitlines():
        line = line.strip()
        if not line:
            continue
        low = line.lower()
        if low.startswith("trace") or low.startswith("[trace") or low.startswith("stage"):
            continue
        outs.append(line)
    return outs

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--manifest", default="bench/lexical_probe/manifest.jsonl")
    ap.add_argument("--out", default="bench/results/lexical_probe_outputs.jsonl")
    ap.add_argument("--prefix", default="grammar/lexical_probe/lexical_probe")
    ap.add_argument("--elvex-bin", default="/usr/local/bin/elvex")
    ap.add_argument("--strategy", default="exhaustive")
    ap.add_argument("--max-length", default="80")
    ap.add_argument("--first", action="store_true")
    args = ap.parse_args()

    rows = [json.loads(line) for line in Path(args.manifest).open(encoding="utf-8") if line.strip()]
    Path(args.out).parent.mkdir(parents=True, exist_ok=True)

    with Path(args.out).open("w", encoding="utf-8") as out:
        for i, row in enumerate(rows, 1):
            cmd = [
                args.elvex_bin,
                "--macros-file", f"{args.prefix}.macros",
                "--rules-file", f"{args.prefix}.rules",
                "--lexicon-file", f"{args.prefix}.lexicon",
                "--input-file", row["input_file"],
                "--compacted-lexicon-file", args.prefix,
                "--strategy", args.strategy,
                "--max-length", str(args.max_length),
            ]
            if args.first:
                cmd.append("--first")
            t0 = time.perf_counter()
            proc = subprocess.run(cmd, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            runtime_ms = (time.perf_counter() - t0) * 1000.0
            rec = dict(row)
            rec.update({
                "ok": proc.returncode == 0,
                "returncode": proc.returncode,
                "outputs": parse_outputs(proc.stdout) if proc.returncode == 0 else [],
                "stdout": proc.stdout,
                "stderr": proc.stderr,
                "runtime_ms": runtime_ms,
                "cmd": cmd,
            })
            out.write(json.dumps(rec, ensure_ascii=False) + "\n")
            print(f"[{i}/{len(rows)}] {row['id']}: ok={rec['ok']} outputs={len(rec['outputs'])} time={runtime_ms:.1f}ms")
    print(f"wrote {args.out}")

if __name__ == "__main__":
    main()
