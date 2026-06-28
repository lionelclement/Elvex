#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import subprocess
import time
from pathlib import Path
from typing import Any

def read_jsonl(path: Path) -> list[dict[str, Any]]:
    rows = []
    with path.open("r", encoding="utf-8") as f:
        for line in f:
            if line.strip():
                rows.append(json.loads(line))
    return rows

def parse_elvex_stdout(stdout: str) -> list[str]:
    outputs = []
    for line in stdout.splitlines():
        line = line.strip()
        if not line:
            continue
        low = line.lower()
        if low.startswith("trace") or low.startswith("[trace") or low.startswith("stage"):
            continue
        outputs.append(line)
    return outputs

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--manifest", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--prefix", default="grammar/e2e/e2e")
    ap.add_argument("--elvex-bin", default="elvex")
    ap.add_argument("--strategy", default="exhaustive", choices=["exhaustive", "sample", "beam"])
    ap.add_argument("--max-length", default="80")
    ap.add_argument("--max-time", default=None)
    ap.add_argument("--max-items", default=None)
    ap.add_argument("--all-outputs", action="store_true",
                    help="Do not pass --first; collect all outputs printed by Elvex.")
    ap.add_argument("--random", action="store_true")
    ap.add_argument("--seed", default=None)
    args = ap.parse_args()

    rows = read_jsonl(Path(args.manifest))
    out_path = Path(args.out)
    out_path.parent.mkdir(parents=True, exist_ok=True)

    with out_path.open("w", encoding="utf-8") as out:
        for idx, row in enumerate(rows, 1):
            cmd = [
                args.elvex_bin,
                "--rules-file", f"{args.prefix}.rules",
                "--lexicon-file", f"{args.prefix}.lexicon",
                "--input-file", row["input_file"],
                "--strategy", args.strategy,
                "--max-length", str(args.max_length),
            ]
            if not args.all_outputs and not args.random:
                cmd.append("--first")
            if args.random:
                cmd.append("--random")
            if args.seed is not None:
                cmd += ["--seed", str(args.seed)]
            if args.max_time is not None:
                cmd += ["--max-time", str(args.max_time)]
            if args.max_items is not None:
                cmd += ["--max-items", str(args.max_items)]

            t0 = time.perf_counter()
            proc = subprocess.run(cmd, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            runtime_ms = (time.perf_counter() - t0) * 1000.0
            outputs = parse_elvex_stdout(proc.stdout) if proc.returncode == 0 else []

            record = {
                "id": row.get("id"),
                "source_id": row.get("source_id"),
                "ok": proc.returncode == 0,
                "returncode": proc.returncode,
                "outputs": outputs,
                "stdout": proc.stdout,
                "stderr": proc.stderr,
                "runtime_ms": runtime_ms,
                "expected_slots": row.get("expected_slots", {}),
                "references": row.get("references", []),
                "mr": row.get("mr"),
                "n_slots": row.get("n_slots"),
                "cmd": cmd,
            }
            out.write(json.dumps(record, ensure_ascii=False) + "\n")
            print(f"[{idx}/{len(rows)}] {row.get('id')}: ok={record['ok']} outputs={len(outputs)} time={runtime_ms:.1f}ms")

if __name__ == "__main__":
    main()
