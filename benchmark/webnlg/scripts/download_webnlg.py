#!/usr/bin/env python3
from __future__ import annotations

import argparse, json, shutil, subprocess, sys, urllib.request, zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

def run(cmd: list[str]) -> None:
    print("+", " ".join(cmd))
    subprocess.run(cmd, check=True)

def git_clone_or_pull(url: str, dest: Path) -> None:
    if dest.exists() and (dest / ".git").exists():
        run(["git", "-C", str(dest), "pull", "--ff-only"])
    elif dest.exists() and any(dest.iterdir()):
        print(f"[skip] {dest} already exists and is not a git repository")
    else:
        dest.parent.mkdir(parents=True, exist_ok=True)
        run(["git", "clone", "--depth", "1", url, str(dest)])

def download_zip(url: str, dest: Path) -> None:
    dest.parent.mkdir(parents=True, exist_ok=True)
    archive = dest.with_suffix(".zip")
    print(f"download {url} -> {archive}")
    urllib.request.urlretrieve(url, archive)
    with zipfile.ZipFile(archive) as zf:
        zf.extractall(dest)

def main() -> int:
    ap = argparse.ArgumentParser(description="Download configured WebNLG sources")
    ap.add_argument("--config", default=str(ROOT / "user/sources.json"))
    ap.add_argument("--only", help="Exact name of one source to download")
    args = ap.parse_args()
    cfg = json.loads(Path(args.config).read_text(encoding="utf-8"))
    ok = 0
    for source in cfg.get("sources", []):
        if args.only and source.get("name") != args.only:
            continue
        dest = ROOT / source["path"]
        try:
            typ = source.get("type", "git")
            if typ == "git":
                if not shutil.which("git"):
                    raise RuntimeError("git est requis pour cette source")
                git_clone_or_pull(source["url"], dest)
            elif typ == "zip":
                download_zip(source["url"], dest)
            else:
                raise RuntimeError(f"type de source inconnu: {typ}")
            ok += 1
        except Exception as e:
            if source.get("optional"):
                print(f"[optional failed] {source.get('name')}: {e}", file=sys.stderr)
            else:
                raise
    print(f"Sources retrieved: {ok}")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
