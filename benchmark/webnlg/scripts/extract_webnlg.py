#!/usr/bin/env python3
from __future__ import annotations

import argparse, json, re, xml.etree.ElementTree as ET
from pathlib import Path
import sys
from typing import Any

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from lib.webnlg_utils import parse_triple_text, write_jsonl, iter_text_values

ROOT = Path(__file__).resolve().parents[1]


def relpath(path: Path) -> str:
    try:
        return str(path.relative_to(ROOT))
    except ValueError:
        return str(path)

def local_name(tag: str) -> str:
    return tag.split("}", 1)[-1].lower()

def text_of(el) -> str:
    return "".join(el.itertext()).strip()

def parse_xml(path: Path) -> list[dict[str, Any]]:
    rows = []
    try:
        tree = ET.parse(path)
    except ET.ParseError as e:
        print(f"[xml skip] {path}: {e}")
        return rows
    root = tree.getroot()
    for entry in root.iter():
        if local_name(entry.tag) != "entry":
            continue
        triples = []
        lexs = []
        category = entry.attrib.get("category")
        eid = entry.attrib.get("eid") or entry.attrib.get("id") or f"{path.stem}:{len(rows)}"
        size = entry.attrib.get("size")
        for node in entry.iter():
            ln = local_name(node.tag)
            if ln in {"mtriple", "otriple", "triple"}:
                parsed = parse_triple_text(text_of(node))
                if parsed:
                    triples.append({"subject": parsed[0], "predicate": parsed[1], "object": parsed[2]})
            elif ln in {"lex", "text", "reference"}:
                val = text_of(node)
                if val:
                    lexs.append(val)
        if triples:
            rows.append({
                "id": eid,
                "source_file": relpath(path),
                "category": category,
                "split": infer_split(path),
                "size": int(size) if str(size).isdigit() else len(triples),
                "triples": triples,
                "lexicalizations": sorted(set(lexs)),
            })
    return rows

def infer_split(path: Path) -> str:
    low = str(path).lower()
    for split in ("train", "dev", "test", "validation"):
        if re.search(rf"(^|[/_.-]){split}($|[/_.-])", low):
            return "dev" if split == "validation" else split
    return "unknown"

def triples_from_json_obj(obj: Any) -> list[dict[str, str]]:
    triples = []
    if isinstance(obj, dict):
        if {"subject", "predicate", "object"} <= set(obj):
            triples.append({"subject": str(obj["subject"]), "predicate": str(obj["predicate"]), "object": str(obj["object"])})
        for key in ("modifiedtripleset", "originaltripleset", "triples", "triple_set", "input"):
            val = obj.get(key)
            if isinstance(val, list):
                for item in val:
                    if isinstance(item, str):
                        parsed = parse_triple_text(item)
                        if parsed:
                            triples.append({"subject": parsed[0], "predicate": parsed[1], "object": parsed[2]})
                    elif isinstance(item, dict):
                        triples.extend(triples_from_json_obj(item))
        for v in obj.values():
            if isinstance(v, (dict, list)):
                triples.extend(triples_from_json_obj(v))
    elif isinstance(obj, list):
        for item in obj:
            triples.extend(triples_from_json_obj(item))
    return triples

def parse_json(path: Path) -> list[dict[str, Any]]:
    try:
        obj = json.loads(path.read_text(encoding="utf-8"))
    except Exception as e:
        print(f"[json skip] {path}: {e}")
        return []
    candidates = obj if isinstance(obj, list) else obj.get("entries") if isinstance(obj, dict) and isinstance(obj.get("entries"), list) else [obj]
    rows = []
    for i, item in enumerate(candidates):
        triples = triples_from_json_obj(item)
        if not triples:
            continue
        lexs = sorted(set(t for t in iter_text_values(item) if isinstance(t, str) and len(t.split()) > 2))
        rows.append({
            "id": str(item.get("eid") or item.get("id") or f"{path.stem}:{i}") if isinstance(item, dict) else f"{path.stem}:{i}",
            "source_file": relpath(path),
            "category": item.get("category") if isinstance(item, dict) else None,
            "split": infer_split(path),
            "size": len(triples),
            "triples": triples,
            "lexicalizations": lexs[:20],
        })
    return rows

def main() -> int:
    ap = argparse.ArgumentParser(description="Extract all WEBNLG XML/JSON triples to JSONL")
    ap.add_argument("--raw", default=str(ROOT / "data/raw"))
    ap.add_argument("--out", default=str(ROOT / "data/processed/triples.jsonl"))
    args = ap.parse_args()
    raw = Path(args.raw)
    files = [p for p in raw.rglob("*") if p.suffix.lower() in {".xml", ".json"} and "__MACOSX" not in p.parts]
    rows = []
    for p in files:
        rows.extend(parse_xml(p) if p.suffix.lower() == ".xml" else parse_json(p))
    rows.sort(key=lambda r: (r["source_file"], r["id"]))
    n = write_jsonl(Path(args.out), rows)
    print(f"{n} entries written to {args.out}")
    return 0 if n else 1

if __name__ == "__main__":
    raise SystemExit(main())
