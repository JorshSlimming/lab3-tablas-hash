# Results

Los CSV crudos y resumidos de benchmarks se guardan aqui.

Formato base:

```text
run;key_type;structure;strategy;n_tweets;unique_users;time_us;memory_bytes;capacity
```

## Regla: no sobrescribir sin respaldo

Antes de regenerar un CSV final, el runner debe respaldar el archivo existente.
El script `scripts/run_role_c_benchmark.sh` sigue esta regla automaticamente,
creando copias con sufijo `.bak.YYYYMMDDHHMMSS`.

## Archivos generados por Rol C

| Archivo | Contenido |
|---|---|
| `role_c_benchmark.csv` | Benchmark combinado de chaining, double hashing y unordered_map para ambos tipos de clave |

Estado actual del repositorio:

- `role_c_benchmark.csv` ya fue generado con el dataset `auspol2019.csv`.
- `auspol2019.csv` permanece fuera de versionado y debe descargarse localmente.

Para regenerarlo:

```bash
./scripts/run_role_c_benchmark.sh
```

Requiere `auspol2019.csv` en la raiz del repositorio (no versionado).
