# Resultados experimentales

Los CSV crudos y resumidos de la experimentación se guardan en este directorio.

Formato del CSV crudo:

```text
run;key_type;structure;strategy;n_tweets;unique_users;time_us;memory_bytes;capacity
```

Formato del CSV resumen:

```text
key_type;structure;strategy;n_tweets;runs;unique_users;time_us_mean;time_us_stdev;memory_bytes_mean;capacity_mean
```

## Archivos esperados

| Archivo | Contenido |
|---|---|
| `benchmark_results.csv` | Mediciones crudas de encadenamiento, exploración lineal, exploración cuadrática, doble hashing y `unordered_map` para `user_id` y `user_screen_name` |
| `benchmark_summary.csv` | Promedios y desviaciones estándar derivados del CSV crudo |

## Regla: no sobrescribir sin respaldo

Antes de regenerar un CSV final, el script `scripts/run_full_benchmark.sh` respalda el archivo existente con sufijo `.bak.YYYYMMDDHHMMSS`.

## Regenerar resultados

Con `auspol2019.csv` en la raiz del repositorio:

```bash
./scripts/run_full_benchmark.sh
```

También se puede especificar la ruta del dataset:

```bash
./scripts/run_full_benchmark.sh /ruta/a/auspol2019.csv results/benchmark_results.csv
```
