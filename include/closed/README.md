# Hashing cerrado

Implementaciones de hashing cerrado incluidas en la experimentación principal:

- `ProbingHashTable<Key, ProbeStrategy::Linear>` para exploración lineal.
- `ProbingHashTable<Key, ProbeStrategy::Quadratic>` para exploración cuadrática.
- `DoubleHashTable<Key>` para doble hashing.

Todas respetan el contrato documentado en `include/common/hash_table_contract.md`.
