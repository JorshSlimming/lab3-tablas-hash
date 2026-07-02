# Rol B - Hashing cerrado: linear y quadratic probing

## Responsable

Sebastian

## Estado

Pendiente.

## Objetivo del rol

Implementar una tabla hash con direccionamiento abierto que permita evaluar dos
estrategias de resolucion de colisiones:

- linear probing;
- quadratic probing.

La implementacion debe reutilizar las decisiones tecnicas ya fijadas por el Rol
A.

## Archivos sugeridos

- `include/closed/closed_hash_table.hpp`
- `tests/closed_hash_tests.cpp`

Tambien se pueden agregar archivos auxiliares dentro de `include/closed/` si la
implementacion lo requiere.

## Interfaz esperada

La tabla debe respetar el contrato comun:

```cpp
void increment(const Key& key);
std::size_t size() const;
std::size_t capacity() const;
std::size_t memory_bytes() const;
void clear();
```

Se recomienda permitir seleccionar la estrategia con:

```cpp
enum class ProbeStrategy {
    Linear,
    Quadratic
};
```

Ejemplo de uso esperado:

```cpp
ClosedHashTable<lab3::UserId> table_ids(ProbeStrategy::Linear);
ClosedHashTable<lab3::UserScreenName> table_names(ProbeStrategy::Quadratic);
```

## Comportamiento requerido

La estructura debe implementar:

- arreglo/vector de slots;
- estado de cada slot: vacio u ocupado;
- insercion de claves nuevas;
- busqueda de claves existentes;
- incremento del contador asociado a una clave existente;
- deteccion y resolucion de colisiones;
- rehash cuando se supere el factor de carga;
- reinsercion correcta de elementos durante rehash;
- estimacion documentada de memoria;
- soporte para `lab3::UserId`;
- soporte para `lab3::UserScreenName`;
- uso de las funciones hash compartidas en `include/common/hash_functions.hpp`.

## Formulas de probing

### Linear probing

```cpp
position = (hash(key) + i) % capacity;
```

### Quadratic probing

```cpp
position = (hash(key) + c1 * i + c2 * i * i) % capacity;
```

Se recomienda usar parametros simples y documentados, por ejemplo:

```cpp
c1 = 1;
c2 = 1;
```

La capacidad debe seguir siendo prima usando `next_prime`.

## Pruebas minimas

El rol debe agregar pruebas para:

- insercion de clave nueva;
- incremento repetido;
- colisiones intencionales con linear probing;
- colisiones intencionales con quadratic probing;
- rehash preservando contadores;
- funcionamiento con `user_id`;
- funcionamiento con `user_screen_name`;
- comparacion contra conteos esperados en `data/sample_tweets.csv`.

## Criterios de completitud

El rol se considera terminado cuando:

- compila junto al proyecto base;
- sus pruebas pasan;
- ambas estrategias respetan el contrato comun;
- ambas estrategias entregan los mismos conteos que una referencia;
- queda documentada la estimacion de memoria usada.
