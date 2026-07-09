#!/usr/bin/env python3
from __future__ import annotations

import csv
import statistics
import sys
from collections import defaultdict
from pathlib import Path


def main() -> int:
    if len(sys.argv) != 3:
        print("Uso: summarize_benchmark.py <benchmark_results.csv> <benchmark_summary.csv>")
        return 2

    input_path = Path(sys.argv[1])
    output_path = Path(sys.argv[2])

    if not input_path.exists():
        print(f"ERROR: no existe el archivo de entrada: {input_path}")
        return 1

    groups: dict[tuple[str, str, str, int], list[dict[str, str]]] = defaultdict(list)
    with input_path.open(newline="", encoding="utf-8") as handle:
        reader = csv.DictReader(handle, delimiter=";")
        required = {
            "run",
            "key_type",
            "structure",
            "strategy",
            "n_tweets",
            "unique_users",
            "time_us",
            "memory_bytes",
            "capacity",
        }
        missing = required.difference(reader.fieldnames or [])
        if missing:
            print(f"ERROR: faltan columnas en CSV: {sorted(missing)}")
            return 1

        for row in reader:
            key = (
                row["key_type"],
                row["structure"],
                row["strategy"],
                int(row["n_tweets"]),
            )
            groups[key].append(row)

    output_path.parent.mkdir(parents=True, exist_ok=True)
    with output_path.open("w", newline="", encoding="utf-8") as handle:
        fieldnames = [
            "key_type",
            "structure",
            "strategy",
            "n_tweets",
            "runs",
            "unique_users",
            "time_us_mean",
            "time_us_stdev",
            "memory_bytes_mean",
            "capacity_mean",
        ]
        writer = csv.DictWriter(handle, fieldnames=fieldnames, delimiter=";")
        writer.writeheader()

        for (key_type, structure, strategy, n_tweets), rows in sorted(groups.items()):
            times = [int(row["time_us"]) for row in rows]
            memories = [int(row["memory_bytes"]) for row in rows]
            capacities = [int(row["capacity"]) for row in rows]
            unique_users = [int(row["unique_users"]) for row in rows]
            writer.writerow(
                {
                    "key_type": key_type,
                    "structure": structure,
                    "strategy": strategy,
                    "n_tweets": n_tweets,
                    "runs": len(rows),
                    "unique_users": round(statistics.mean(unique_users), 2),
                    "time_us_mean": round(statistics.mean(times), 2),
                    "time_us_stdev": round(statistics.stdev(times), 2) if len(times) > 1 else 0,
                    "memory_bytes_mean": round(statistics.mean(memories), 2),
                    "capacity_mean": round(statistics.mean(capacities), 2),
                }
            )

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
