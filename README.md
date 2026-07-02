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
ejecutar benchmarks locales. No se versiona por su tamano.

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

## Ejecutar benchmark base

El ejecutable actual mide la tabla con hashing abierto (`chaining`) para las
dos claves. Los roles siguientes deben conectar las demas estructuras al mismo
formato de salida.

```powershell
.\build\Debug\hash_benchmark.exe auspol2019.csv results\chaining_results.csv
```

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
