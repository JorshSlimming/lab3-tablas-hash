# Interfaz común de tablas hash

Todas las tablas hash del proyecto deben implementar una interfaz pública
equivalente a:

```cpp
template <typename Key>
class HashTable {
public:
    void increment(const Key& key);
    std::size_t size() const;
    std::size_t capacity() const;
    std::size_t memory_bytes() const;
    void clear();
};
```

No es obligatorio usar herencia. El contrato es estructural: si una clase
implementa esos métodos, el programa experimental debe poder utilizarla.

Métodos auxiliares permitidos:

- `bool contains(const Key& key) const`
- `bool get(const Key& key, TweetCount& count) const`

## Convenciones

- `size()` representa la cantidad de usuarios unicos almacenados.
- `capacity()` representa casillas disponibles, según la estructura.
- `memory_bytes()` es una estimación documentada y consistente, no una medición
  exacta del heap.
- `increment(key)` inserta `key` con contador `1` si no existe, o incrementa su
  contador si ya existe.
