#!/usr/bin/env bash
# Role C — Ejecuta el benchmark completo de:
#   - ChainingHashTable
#   - DoubleHashTable
#   - UnorderedMapAdapter
# para ambos tipos de clave (user_id, user_screen_name).
#
# Requiere: auspol2019.csv en la raiz del repositorio.
# Respeta: no sobrescribir resultados finales sin respaldo.
set -euo pipefail

ROLE="rol_c"
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
DATASET="$REPO_DIR/auspol2019.csv"
BENCHMARK="$REPO_DIR/build/hash_benchmark"
OUTPUT_DIR="$REPO_DIR/results"
OUTPUT_FILE="$OUTPUT_DIR/role_c_benchmark.csv"

echo "=== Rol C — Benchmark: Double Hashing + STL Adapter ==="
echo ""

# 1. Verificar dataset
if [ ! -f "$DATASET" ]; then
    echo "ERROR: No se encuentra el dataset 'auspol2019.csv' en la raiz."
    echo ""
    echo "Debes copiarlo manualmente (no se versiona por su tamano):"
    echo ""
    echo "  cp /ruta/a/auspol2019.csv $REPO_DIR/"
    echo ""
    exit 1
fi
echo "  Dataset: $DATASET"

# 2. Verificar / compilar ejecutable
if [ ! -x "$BENCHMARK" ]; then
    echo "  Compilando hash_benchmark..."
    cd "$REPO_DIR"
    cmake -S . -B build
    cmake --build build --target hash_benchmark 2>&1
    if [ ! -x "$BENCHMARK" ]; then
        echo "ERROR: No se pudo compilar hash_benchmark."
        exit 1
    fi
    echo "  Compilacion exitosa."
fi
echo "  Ejecutable: $BENCHMARK"

# 3. Respadar resultado previo si existe
mkdir -p "$OUTPUT_DIR"
if [ -f "$OUTPUT_FILE" ]; then
    BACKUP="${OUTPUT_FILE}.bak.$(date +%Y%m%d%H%M%S)"
    cp "$OUTPUT_FILE" "$BACKUP"
    echo "  Respaldo creado: $BACKUP"
fi

# 4. Ejecutar benchmark
echo ""
echo "  Ejecutando benchmark (puede tomar varios minutos)..."
cd "$REPO_DIR"
"$BENCHMARK" "$DATASET" "$OUTPUT_FILE"

# 5. Verificar que se generaron datos
if [ ! -f "$OUTPUT_FILE" ]; then
    echo "ERROR: No se genero el archivo de salida."
    exit 1
fi

LINE_COUNT="$(wc -l < "$OUTPUT_FILE")"
if [ "$LINE_COUNT" -le 1 ]; then
    echo "ERROR: El archivo de salida solo contiene la cabecera."
    echo "  Verifica que auspol2019.csv tenga al menos ${kBenchmarkStep:-10000} tweets."
    exit 1
fi

echo ""
echo "=== Benchmark completado ==="
echo "  Archivo: $OUTPUT_FILE"
echo "  Lineas:  $LINE_COUNT (cabecera + datos)"
echo ""
echo "Estructuras medidas:"
echo "  - chaining"
echo "  - double hashing"
echo "  - unordered_map"
echo "Claves: user_id, user_screen_name"
echo ""
