# Laboratorio 3: Tablas hash

Repositorio del Entregable 3 para comparar estructuras de tablas hash contando tweets por usuario en el dataset `auspol2019.csv`.

## Decisiones técnicas base

- Lenguaje: C++17.
- Build system: CMake.
- Capacidad inicial: `101` casillas.
- Factor de carga maximo: `0.60`.
- Crecimiento: `next_prime(capacity * 2)`.
- Unidad de tiempo para benchmarks: microsegundos.
- Hash primario para `user_id`: mezcla SplitMix64.
- Hash primario para `user_screen_name`: FNV-1a de 64 bits.
- Hash secundario para double hashing: variante independiente, con salto calculado como `1 + (secondary_hash(key) % (capacity - 1))`.
- CSV de resultados separado por punto y coma (`;`).

## Estructuras comparadas

La experimentación principal evalúa las estructuras y estrategias solicitadas por el laboratorio:

- hashing abierto por encadenamiento (`chaining`);
- hashing cerrado con `linear_probing`;
- hashing cerrado con `quadratic_probing`;
- hashing cerrado con `double_hashing`;
- `std::unordered_map` de la STL de C++.

Cada configuracion se mide con las claves `user_id` y `user_screen_name`.

## Estructura del repositorio

```text
include/common/      Tipos, configuracion, hashes, lector CSV y contrato
include/chaining/    Tabla hash con hashing abierto
include/closed/      Tablas hash con hashing cerrado
include/stl/         Adaptador std::unordered_map
include/benchmark/   Ejecución experimental compartida
src/                 Implementaciones y ejecutables
tests/               Pruebas simples con assert
data/                Dataset pequeno de prueba
results/             CSV de resultados
docs/                Material de referencia para experimentación
scripts/             Scripts de experimentacion
```

El CSV grande `auspol2019.csv` debe estar en la raiz del repositorio para ejecutar benchmarks locales. **No se incluye en este repositorio** y debe descargarse manualmente desde Kaggle:

- https://www.kaggle.com/datasets/taniaj/australian-election-2019-tweets?select=auspol2019.csv

Una vez descargado, copiar `auspol2019.csv` a la raiz del proyecto.

## Compilación

```bash
cmake -S . -B build
cmake --build build
```

## Pruebas

```bash
ctest --test-dir build --output-on-failure
```

También se pueden ejecutar directamente los binarios de prueba generados en `build/`.

## Experimentación completa

Con `auspol2019.csv` en la raiz del repositorio:

```bash
./scripts/run_full_benchmark.sh
```

Equivalente indicando ruta explicita al dataset y archivo de salida:

```bash
./scripts/run_full_benchmark.sh ./auspol2019.csv results/benchmark_results.csv
```

El script compila `hash_benchmark`, ejecuta todas las configuraciones, respalda resultados previos y genera:

- `results/benchmark_results.csv`: mediciones crudas.
- `results/benchmark_summary.csv`: promedios y desviación estándar agrupados por estructura, estrategia, clave y tamaño.

Formato del CSV crudo:

```text
run;key_type;structure;strategy;n_tweets;unique_users;time_us;memory_bytes;capacity
```

## Ejecución directa del programa experimental

```bash
./build/hash_benchmark auspol2019.csv results/benchmark_results.csv
python3 scripts/summarize_benchmark.py results/benchmark_results.csv results/benchmark_summary.csv
```

## Interfaz común

Cada estructura expone, como mínimo:

```cpp
void increment(const Key& key);
std::size_t size() const;
std::size_t capacity() const;
std::size_t memory_bytes() const;
void clear();
```

Se pueden agregar métodos auxiliares como `contains` o `get(const Key&, TweetCount&)`; la comparación experimental utiliza la interfaz común anterior.
