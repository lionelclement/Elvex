#!/usr/bin/env python3
import csv
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
MAX_N = int(sys.argv[1]) if len(sys.argv) > 1 else 7

def read_status(mode, n):
    p = HERE / f"{mode}_N{n}.status"
    return p.read_text(encoding="utf-8", errors="replace").strip() if p.exists() else "unknown"

def output_lines(path):
    p = Path(path)
    if not p.exists():
        return []
    return [x.strip() for x in p.read_text(encoding="utf-8", errors="replace").splitlines() if x.strip()]

def valid_output(line):
    s = " ".join(line.lower().split())
    return ("pays notice" not in s) and ("takes attention" not in s)

def read_metrics(path):
    p = Path(path)
    if not p.exists():
        return {}
    header = values = None
    for raw in p.read_text(encoding="utf-8", errors="replace").splitlines():
        parts = raw.rstrip("\n").split("\t")
        if parts and parts[0] == "ELVEX_METRICS_HEADER":
            header = parts[1:]
        elif parts and parts[0] == "ELVEX_METRICS":
            values = parts[1:]
    if header and values and len(header) == len(values):
        return dict(zip(header, values))
    return {}

def read_time(path):
    result = {"real_s": 0.0, "user_s": 0.0, "sys_s": 0.0}
    p = Path(path)
    if not p.exists():
        return result
    for raw in p.read_text(encoding="utf-8", errors="replace").splitlines():
        parts = raw.split()
        if len(parts) >= 2:
            key = parts[0]
            try:
                value = float(parts[1])
            except ValueError:
                continue
            if key == "real":
                result["real_s"] = value
            elif key == "user":
                result["user_s"] = value
            elif key == "sys":
                result["sys_s"] = value
    return result

def gf(d, key):
    try: return float(d.get(key, 0))
    except (TypeError, ValueError): return 0.0

def gi(d, key):
    try: return int(float(d.get(key, 0)))
    except (TypeError, ValueError): return 0

rows = []
for mode in ("full", "no_context"):
    for n in range(1, MAX_N + 1):
        lines = output_lines(HERE / f"{mode}_N{n}.out")
        generated = len(lines)
        valid = sum(valid_output(x) for x in lines)
        m = read_metrics(HERE / f"{mode}_N{n}.metrics")
        t = read_time(HERE / f"{mode}_N{n}.time")

        rows.append({
            "mode": mode,
            "N": n,
            "status": read_status(mode, n),
            "generated": generated,
            "expected": 2**n if mode == "full" else 4**n,
            "valid": valid,
            "expected_valid": 2**n,
            "valid_pct": 100.0 * valid / generated if generated else 0.0,
            "os_real_s": t["real_s"],
            "os_user_s": t["user_s"],
            "os_sys_s": t["sys_s"],
            "chart_forest_ms": gf(m, "chart_forest_wall_ms"),
            "linearization_ms": gf(m, "linearization_wall_ms"),
            "internal_total_ms": gf(m, "total_wall_ms"),
            "chart_items": gi(m, "chart_items_inserted"),
            "packed_nodes": gi(m, "packed_nodes"),
            "forest_edges": gi(m, "forest_edges"),
            "sat_passes": gi(m, "saturation_passes"),
            "max_sat_passes": gi(m, "max_passes_per_saturate"),
            "rss_kb": gi(m, "process_hwm_rss_kb"),
        })

fields = [
    "mode","N","status","generated","expected","valid","expected_valid","valid_pct",
    "os_real_s","os_user_s","os_sys_s",
    "chart_forest_ms","linearization_ms","internal_total_ms",
    "chart_items","packed_nodes","forest_edges","sat_passes","max_sat_passes","rss_kb"
]

with (HERE/"results.tsv").open("w", encoding="utf-8", newline="") as f:
    w = csv.DictWriter(f, fieldnames=fields, delimiter="\t")
    w.writeheader()
    for r in rows:
        rr = dict(r)
        for k in ("valid_pct","os_real_s","os_user_s","os_sys_s"):
            rr[k] = f"{rr[k]:.6f}"
        for k in ("chart_forest_ms","linearization_ms","internal_total_ms"):
            rr[k] = f"{rr[k]:.3f}"
        w.writerow(rr)

print(
    "mode\tN\tstatus\tgenerated\tvalid\tvalid_pct\t"
    "OS-real(s)\tOS-user(s)\tOS-sys(s)\t"
    "chart(ms)\tlinear(ms)\tinternal(ms)\t"
    "chart_items\tpacked_nodes\tforest_edges\tsat_passes\tmax_sat_passes\trss_kb"
)
for r in rows:
    print(
        f"{r['mode']}\t{r['N']}\t{r['status']}\t"
        f"{r['generated']}/{r['expected']}\t"
        f"{r['valid']}/{r['expected_valid']}\t"
        f"{r['valid_pct']:.6f}\t"
        f"{r['os_real_s']:.6f}\t{r['os_user_s']:.6f}\t{r['os_sys_s']:.6f}\t"
        f"{r['chart_forest_ms']:.3f}\t{r['linearization_ms']:.3f}\t"
        f"{r['internal_total_ms']:.3f}\t"
        f"{r['chart_items']}\t{r['packed_nodes']}\t{r['forest_edges']}\t"
        f"{r['sat_passes']}\t{r['max_sat_passes']}\t{r['rss_kb']}"
    )
