# Rol A - Repositorio, arquitectura y hashing abierto

## Responsable

Jorge

## Estado

Completado como base funcional inicial.

## Objetivo del rol

Dejar listo el repositorio base para que los demas integrantes puedan trabajar
en paralelo, y desarrollar la implementacion propia de tabla hash con hashing
abierto mediante encadenamiento separado.

## Decisiones tecnicas fijadas

- Lenguaje: C++17.
- Sistema de compilacion: CMake.
- Capacidad inicial: `101`.
- Factor de carga maximo: `0.60`.
- Crecimiento de capacidad: `next_prime(capacity * 2)`.
- Unidad de medicion de tiempo: microsegundos.
- Hash para `user_id`: mezcla SplitMix64.
- Hash para `user_screen_name`: FNV-1a de 64 bits.
- Hash secundario disponible para double hashing.
- Formato CSV:

```text
run;key_type;structure;strategy;n_tweets;unique_users;time_us;memory_bytes;capacity
```

## Archivos entregados

- `CMakeLists.txt`: configuracion del proyecto.
- `.gitignore`: ignora `build/`, ejecutables, resultados CSV y `auspol2019.csv`.
- `README.md`: instrucciones de compilacion, pruebas, benchmark y decisiones base.
- `include/common/dataset_types.hpp`: tipos compartidos.
- `include/common/experiment_config.hpp`: parametros experimentales.
- `include/common/hash_functions.hpp`: funciones hash primarias y secundarias.
- `include/common/prime_utils.hpp`: utilidades para numeros primos.
- `include/common/memory_utils.hpp`: apoyo para estimacion de memoria.
- `include/common/hash_table_contract.md`: contrato comun de las estructuras.
- `include/common/dataset_reader.hpp`: interfaz del lector CSV.
- `src/dataset_reader.cpp`: lector CSV robusto.
- `include/chaining/chaining_hash_table.hpp`: tabla hash abierta con chaining.
- `src/benchmark_main.cpp`: benchmark base para chaining.
- `tests/hash_tests.cpp`: pruebas minimas.
- `data/sample_tweets.csv`: dataset pequeno de prueba.
- `data/README.md` y `results/README.md`: convenciones de datos/resultados.

## Trabajo realizado

### Configuracion del repositorio

Se dejo una estructura base con carpetas para codigo comun, hashing abierto,
hashing cerrado, adaptador STL, benchmark, pruebas, datos, resultados y
documentacion.

### Contrato comun

Todas las estructuras deben exponer como minimo:

```cpp
void increment(const Key& key);
std::size_t size() const;
std::size_t capacity() const;
std::size_t memory_bytes() const;
void clear();
```

Tambien se permite agregar auxiliares como:

```cpp
bool contains(const Key& key) const;
bool get(const Key& key, TweetCount& count) const;
```

### Lector CSV

El lector extrae solo:

- `user_id`
- `user_screen_name`

Considera:

- comas dentro de campos entre comillas;
- comillas escapadas como `""`;
- registros con saltos de linea dentro de campos citados;
- preservacion del orden original del dataset;
- carga opcional limitada a los primeros `n` tweets.

### Hashing abierto

La tabla `ChainingHashTable<Key>` implementa:

- vector de buckets;
- cada bucket almacena pares `{key, count}`;
- insercion de claves nuevas;
- incremento de claves repetidas;
- manejo de colisiones por encadenamiento separado;
- rehash al superar el factor de carga;
- preservacion de contadores durante rehash;
- estimacion de memoria.

### Benchmark base

El benchmark actual mide la tabla de chaining para:

- `user_id`;
- `user_screen_name`.

La lectura del dataset se realiza antes de medir. El tiempo registrado considera
solo las llamadas a `increment`.

## Verificacion realizada

Como `cmake` no estaba disponible en PATH, se verifico con `g++` directamente:

```powershell
g++ -std=c++1z -I include src/dataset_reader.cpp tests/hash_tests.cpp -o build\hash_tests.exe
.\build\hash_tests.exe

g++ -std=c++1z -I include src/dataset_reader.cpp src/benchmark_main.cpp -o build\hash_benchmark.exe
.\build\hash_benchmark.exe auspol2019.csv results\chaining_results.csv
```

Resultado:

- las pruebas pasaron correctamente;
- el benchmark cargo `183370` tweets desde `auspol2019.csv`;
- se genero `results/chaining_results.csv`.

## Pendiente para integracion

- Validar tambien con CMake cuando este instalado o disponible en PATH.
- Integrar el runner final con las estructuras de los roles B y C.
- Comparar los conteos finales contra `std::unordered_map` cuando este el
  adaptador.
