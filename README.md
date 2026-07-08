# Lab 3 - Tablas Hash

Base del Entregable 3 para comparar tablas hash contando tweets por usuario
en el dataset `auspol2019.csv`.

## Decisiones tecnicas base

- Lenguaje: C++17.
- Build system: CMake.
- Capacidad inicial: `101` buckets/slots.
- Factor de carga maximo: `0.60`.
- Crecimiento: `next_prime(capacity * 2)`.
- Unidad de tiempo para benchmarks: microsegundos.
- Hash primario para `user_id`: mezcla SplitMix64.
- Hash primario para `user_screen_name`: FNV-1a de 64 bits.
- Hash secundario para double hashing: variante independiente, con salto
  calculado como `1 + (secondary_hash(key) % (capacity - 1))`.
- CSV de resultados separado por `;`.

## Estructura

```text
include/common/      Tipos, configuracion, hashes, lector CSV y contrato
include/chaining/    Tabla hash con hashing abierto
include/closed/      Espacio para hashing cerrado
include/stl/         Espacio para adaptador std::unordered_map
include/benchmark/   Espacio para runner experimental compartido
src/                 Implementaciones y ejecutables
tests/               Pruebas simples con assert
data/                Dataset pequeno de prueba
results/             CSV de resultados
docs/                Enunciado y organizacion
```

El CSV grande `auspol2019.csv` debe estar en la raiz del repositorio para
ejecutar benchmarks locales. **No se incluye en este repositorio** y debe
descargarse manualmente desde Kaggle:

- https://www.kaggle.com/datasets/taniaj/australian-election-2019-tweets?select=auspol2019.csv

Una vez descargado, copiar `auspol2019.csv` a la raiz del proyecto.

## Compilar

```powershell
cmake -S . -B build
cmake --build build
```

## Ejecutar pruebas

```powershell
ctest --test-dir build --output-on-failure
```

Tambien se puede ejecutar directamente:

```powershell
.\build\Debug\hash_tests.exe
```

## Ejecutar benchmark directo

El ejecutable `hash_benchmark` actual mide las tres estructuras implementadas
en este repositorio para ambas claves:

- `chaining`
- `double_hashing`
- `unordered_map`

```powershell
.\build\Debug\hash_benchmark.exe auspol2019.csv results\benchmark_results.csv
```

## Ejecutar benchmark completo (Rol C)

El Rol C agrega double hashing, el adaptador `std::unordered_map`, y un runner
que mide las tres estructuras en un solo CSV.

```bash
./scripts/run_role_c_benchmark.sh
```

Requiere `auspol2019.csv` en la raiz del repositorio (no versionado).
El script respalda resultados previos y falla claramente si falta el dataset.

Formato del CSV:

```text
run;key_type;structure;strategy;n_tweets;unique_users;time_us;memory_bytes;capacity
```

## Contrato comun

Cada estructura debe exponer, como minimo:

```cpp
void increment(const Key& key);
std::size_t size() const;
std::size_t capacity() const;
std::size_t memory_bytes() const;
void clear();
```

Puede agregar metodos auxiliares como `contains` o `get(const Key&, TweetCount&)`,
pero el runner debe poder usar todas las estructuras con la interfaz comun
anterior.
