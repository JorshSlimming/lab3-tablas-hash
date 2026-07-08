# Rol C - Double hashing, unordered_map y runner experimental

## Responsable

Benjamin

## Estado

Completado. Benchmark final ejecutado y resultados guardados en `results/role_c_benchmark.csv`.

## Objetivo del rol

Completar la familia de hashing cerrado con double hashing, crear el adaptador
para `std::unordered_map` y generalizar el runner experimental para comparar
todas las estructuras con el mismo procedimiento.

## Archivos sugeridos

- `include/closed/double_hash_table.hpp`
- `include/stl/unordered_map_adapter.hpp`
- `include/benchmark/benchmark_runner.hpp`
- `src/benchmark_main.cpp`
- `tests/double_hash_tests.cpp`
- `tests/unordered_map_adapter_tests.cpp`
- `tests/benchmark_tests.cpp`

El archivo `src/benchmark_main.cpp` ya existe con una version base para
chaining; este rol debe generalizarlo sin romper el formato CSV acordado.

## Double hashing

La estrategia debe usar:

```cpp
position = (h1(key) + i * h2(key)) % capacity;
```

La segunda funcion hash debe evitar saltos de cero:

```cpp
h2 = 1 + (secondary_hash(key) % (capacity - 1));
```

Ya existe una funcion compartida:

```cpp
lab3::double_hash_step(key, capacity);
```

## Adaptador unordered_map

El adaptador debe permitir usar `std::unordered_map` bajo el mismo contrato:

```cpp
void increment(const Key& key);
std::size_t size() const;
std::size_t capacity() const;
std::size_t memory_bytes() const;
void clear();
```

`capacity()` puede reportar `bucket_count()`.

La memoria debe estimarse considerando al menos:

- objeto `std::unordered_map`;
- buckets internos;
- nodos o pares almacenados;
- memoria dinamica de strings cuando la clave sea `UserScreenName`.

No basta con usar solo `sizeof(std::unordered_map)`.

## Runner experimental

El runner final debe ejecutar todas las configuraciones:

- chaining;
- linear probing;
- quadratic probing;
- double hashing;
- `std::unordered_map`.

> Nota de integracion del equipo: por acuerdo operativo, este rol deja listo el
> runner comun y ejecuta directamente las estructuras bajo este ownership
> (`chaining`, `double hashing`, `unordered_map`). `linear probing` y
> `quadratic probing` quedaron en una carpeta e interfaz mantenidas por otro
> integrante, por lo que sus resultados deben correrse/guardarse por separado y
> luego unirse en el analisis final del grupo.

Y para ambos tipos de clave:

- `user_id`;
- `user_screen_name`.

Debe medir los tamanos:

```text
10000, 20000, 30000, ..., 180000
```

Por cada medicion debe registrar:

- numero de corrida;
- tipo de clave;
- estructura;
- estrategia;
- tweets procesados;
- usuarios unicos;
- tiempo en microsegundos;
- memoria estimada;
- capacidad final.

Formato obligatorio:

```text
run;key_type;structure;strategy;n_tweets;unique_users;time_us;memory_bytes;capacity
```

## Reglas experimentales

El runner debe mantener las reglas ya consideradas en el Rol A:

- leer el CSV antes de medir;
- medir solo el conteo con `increment`;
- repetir cada experimento, idealmente 20 veces;
- guardar observaciones crudas;
- usar el mismo computador para los benchmarks finales;
- no sobrescribir resultados finales sin respaldo.

## Pruebas minimas

El rol debe agregar pruebas para:

- double hashing con colisiones intencionales;
- incremento repetido;
- rehash preservando contadores;
- soporte para `user_id`;
- soporte para `user_screen_name`;
- adaptador `unordered_map`;
- formato CSV del runner;
- comparacion de conteos entre todas las estructuras y `unordered_map`.

## Criterios de completitud

El rol se considera terminado cuando:

- double hashing compila y pasa pruebas;
- el adaptador STL respeta el contrato comun;
- el runner ejecuta todas las estructuras y ambas claves;
- los resultados se guardan con el formato acordado;
- se puede usar el CSV final para generar tablas, promedios, desviacion
  estandar y graficos del informe.

## Listo para ejecutar

El codigo, las pruebas y el runner quedaron completos. El benchmark final ya se
ejecuto con `auspol2019.csv` y dejo el CSV en `results/role_c_benchmark.csv`.

Para repetir la corrida:

```bash
# Ejecutar benchmark completo
./scripts/run_role_c_benchmark.sh
```

El script:

- falla claramente si `auspol2019.csv` no existe;
- compila el benchmark si es necesario;
- respalda resultados previos antes de sobrescribir;
- escribe en `results/role_c_benchmark.csv`.

### Estructuras medidas

| Estructura | Estrategia | Archivo |
|---|---|---|
| ChainingHashTable | chaining | `include/chaining/chaining_hash_table.hpp` |
| DoubleHashTable | double_hashing | `include/closed/double_hash_table.hpp` |
| UnorderedMapAdapter | unordered_map | `include/stl/unordered_map_adapter.hpp` |

### Cobertura de pruebas

| Archivo | Pruebas |
|---|---|
| `tests/hash_tests.cpp` | Chaining, parser CSV, hashes |
| `tests/double_hash_tests.cpp` | Double hashing: colisiones, rehash, clear, memoria |
| `tests/unordered_map_adapter_tests.cpp` | Adaptador: incremento, clear, capacity, memoria |
