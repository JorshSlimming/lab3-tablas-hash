#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
DATASET="${1:-$REPO_DIR/auspol2019.csv}"
OUTPUT_DIR="$REPO_DIR/results"
OUTPUT_FILE="${2:-$OUTPUT_DIR/benchmark_results.csv}"
SUMMARY_FILE="$OUTPUT_DIR/benchmark_summary.csv"
BENCHMARK="$REPO_DIR/build/hash_benchmark"

if [ ! -f "$DATASET" ]; then
    echo "ERROR: no se encontro el dataset auspol2019.csv."
    echo ""
    echo "Coloca el archivo en la raiz del repositorio o entrega su ruta como primer argumento:"
    echo "  ./scripts/run_full_benchmark.sh /ruta/a/auspol2019.csv"
    exit 1
fi

cd "$REPO_DIR"
cmake -S . -B build
cmake --build build --target hash_benchmark

mkdir -p "$OUTPUT_DIR"
if [ -f "$OUTPUT_FILE" ]; then
    BACKUP="${OUTPUT_FILE}.bak.$(date +%Y%m%d%H%M%S)"
    cp "$OUTPUT_FILE" "$BACKUP"
    echo "Respaldo creado: $BACKUP"
fi

"$BENCHMARK" "$DATASET" "$OUTPUT_FILE"
python3 "$SCRIPT_DIR/summarize_benchmark.py" "$OUTPUT_FILE" "$SUMMARY_FILE"

LINE_COUNT="$(wc -l < "$OUTPUT_FILE")"
SUMMARY_COUNT="$(wc -l < "$SUMMARY_FILE")"

echo ""
echo "Experimentacion completa finalizada."
echo "CSV crudo:    $OUTPUT_FILE ($LINE_COUNT lineas, incluyendo cabecera)"
echo "CSV resumen:  $SUMMARY_FILE ($SUMMARY_COUNT lineas, incluyendo cabecera)"
echo ""
echo "Configuraciones esperadas: 5 estructuras/estrategias x 2 tipos de clave."
