# Entregable 3: Tablas Hash

**Fecha de entrega:** 8 de julio a las 23:59  
**Puntaje total:** 6 puntos  
**Forma de entrega:** URL de página web o carga de archivo  
**Disponibilidad:** 9 de junio, 00:00 - 8 de julio, 23:59

> **Ayuda extra:** ver la siguiente página para aprender a realizar experimentos de manera adecuada.

## Descripción de la actividad

En este entregable compararemos el rendimiento de diferentes tablas hash usando tweets sobre las elecciones australianas del 2019. El dataset es un CSV disponible en un enlace indicado en el documento original (la URL no es visible en el PDF). Se trata de **180.000 tweets** publicados entre el **10 de mayo de 2019** y el **20 de mayo de 2019**, conformado por las siguientes columnas:

- `created_at`: fecha y hora de creación del tweet.
- `id`: ID único del tweet.
- `full_text`: texto completo del tweet.
- `retweet_count`: número de retweets.
- `favorite_count`: número de likes.
- `user_id`: ID del usuario creador del tweet; sirve como identificador único.
- `user_name`: nombre de usuario del creador del tweet.
- `user_screen_name`: screen name del creador del tweet; sirve como identificador único.
- `user_description`: descripción del perfil del creador del tweet.
- `user_location`: ubicación registrada en el perfil del creador del tweet.
- `user_created_at`: fecha en la que el creador del tweet creó su cuenta en la red social.

## Problema a resolver

Se solicita contar cuántos tweets publicó cada usuario utilizando diferentes tablas hash. Para ello, se deben considerar dos claves:

- `user_id`
- `user_screen_name`

En otras palabras, se pide diseñar e implementar estructuras de datos que utilicen `user_id` como clave, y un grupo similar que utilice `user_screen_name` como clave. El valor asociado a cada clave será un entero correspondiente a la cantidad de tweets que ese usuario publicó.

Por cada tweet que se analice (cada fila del dataset), se debe usar el siguiente esquema para contar los tweets:

```text
Dada la tabla hash H y dado el usuario con user_id k

if (k está en H) H[k] = H[k] + 1
else H[k] = 1
```

## Estructuras de datos mínimas

Se deben considerar, como mínimo, las siguientes estructuras:

1. Implementación propia (o del laboratorio) de **tabla hash con hashing abierto** (encadenamiento).
2. Implementación propia (o del laboratorio) de **tabla hash con hashing cerrado**. Para este caso, se deben evaluar las estrategias de manejo de colisiones:
   - *Linear probing*.
   - *Quadratic probing*.
   - *Double hashing*.
3. La implementación de **`unordered_map` de la STL de C++**.

## Funciones hash

Las funciones hash a utilizar quedan a criterio de los estudiantes. Se necesitarán, al menos, dos funciones hash:

- Una para `user_id`.
- Una para `user_screen_name`.

En el caso de *double hashing*, se necesitará una segunda función hash para ambos tipos de clave.

## Informe experimental

Se debe entregar un pequeño informe que reporte un estudio experimental de las estructuras, con una extensión máxima de **8 páginas**.

### 1. Introducción — máximo 1 página

Breve reseña de todo el trabajo realizado. Descripción de alto nivel del problema planteado y de las estructuras de datos utilizadas —implementadas y provistas por bibliotecas—, herramientas, fuentes de datos y conclusiones preliminares.

### 2. Descripción de las estructuras de datos comparadas — máximo 1 página

- Entregar todos los códigos como adjuntos al documento o enlaces a dónde encontrarlos en el mismo.
- El código debe estar documentado y seguir algún estándar de codificación adoptado por el estudiante.
- Para cada estructura de datos, entregar una descripción general, indicar los costos de inserción y búsqueda, y especificar los parámetros utilizados, tales como función hash, número inicial de *buckets*, etc.
- Se debe destinar, como máximo, un párrafo por cada estructura de datos descrita.
- En dicho párrafo se pueden incluir enlaces a sitios web y otras referencias bibliográficas.

### 3. Descripción del dataset y del ambiente de experimentación — máximo 1 página

Describir los métodos de lectura del dataset. Si fuese necesario realizar alguna modificación al dataset, especificar las modificaciones de manera justificada. Además, describir en detalle la máquina en la que se realizaron los experimentos:

- Modelo del procesador.
- Tamaño de la memoria RAM.
- Tamaño de las memorias caché.
- Otras características relevantes del equipo.

### 4. Resultados experimentales — máximo 4 páginas

Comparar el rendimiento de las estructuras de datos usando evidencia experimental. Como mínimo, se deben entregar gráficas y/o tablas con las siguientes comparaciones:

- **Tamaño de las estructuras de datos**, expresado en B, KB o MB.
- **Rendimiento en la creación de la estructura de datos** al contar tweets por usuario. Para cada estructura, medir experimentalmente su escalabilidad en función de la cantidad de usuarios almacenados.

Por ejemplo, medir el tiempo que toma contar los primeros:

```text
10.000, 20.000, 30.000, ..., 180.000 tweets
```

Cada medición experimental debe realizarse utilizando las claves `user_id` y `user_screen_name`. Se debe mostrar evidencia experimental de la clave más eficiente para cada estructura de datos.

### 5. Conclusiones — máximo 1 página

Describir los principales descubrimientos obtenidos. Hacer hincapié en:

- Las estructuras de datos más rápidas para cada tipo de experimento.
- La comparación entre los dos tipos de claves evaluadas.

## Modalidad de trabajo

El entregable se realizará en grupos de **3 estudiantes**. Se recomienda aprovechar los mismos grupos del proyecto semestral para distribuir mejor la carga de trabajo. Basta con que un integrante del grupo realice la entrega, siempre que indique el nombre de todos los integrantes.

No se aceptarán entregas individuales.

# Recomendaciones para realizar un estudio experimental

Para obtener resultados confiables en un estudio experimental, como el solicitado en este entregable, se deben considerar las siguientes recomendaciones:

1. **Usar siempre el mismo computador.** Al medir tiempo de ejecución, deben estar abiertos solo los programas estrictamente necesarios. Otros programas, como navegadores web, editores de texto, etc., deben estar cerrados.
2. **Repetir cada experimento varias veces.** Idealmente, repetirlo 20 veces y reportar luego su promedio y desviación estándar. Una desviación estándar muy alta hace que el promedio sea poco confiable.
3. **Preparar todos los experimentos para ejecutarlos de una sola vez.** Por ejemplo, pueden ejecutarse en horarios en que el computador se use poco, como durante la noche.
4. **Generar un archivo CSV para el análisis posterior.** Por cada experimento, se recomienda imprimir una línea como la siguiente:

```text
número_experimento;dataset;estructura_de_datos;cantidad_consultas;tiempo_ejecucion
```

De esa manera, todos los experimentos quedarán registrados como un archivo CSV con valores separados por `;`, facilitando la obtención de estadísticas como el promedio mediante hojas de cálculo o lenguajes como Python.

# Rúbrica tarea 3

**Puntaje total: 6 puntos**

## 1. Introducción — 0,5 puntos

**Criterio:** Se introduce de manera correcta y coherente el tema a tratar. Se menciona el objetivo general de la tarea y una breve descripción de las conclusiones obtenidas.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Introducción adecuada | La temática y las conclusiones se introducen de manera adecuada. | 0,5 pts |
| Introducción con errores | La introducción presenta falencias en su contenido. | 0,3 pts |
| Introducción incorrecta o sin introducción | La introducción no es adecuada para el trabajo o no se entrega conclusión. | 0 pts |

## 2. Descripción de las estructuras de datos — 0,8 puntos

**Criterio:** Se describen, como mínimo, las estructuras de datos comparadas: tabla hash con hashing abierto y tabla hash con hashing cerrado, además de las funciones hash utilizadas. Cada estructura debe ser descrita en un párrafo, incluyendo referencias bibliográficas de ser necesario.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Se describen 3 elementos correctamente | Se presenta de manera correcta la descripción de los 3 elementos solicitados: funciones hash, hashing cerrado y hashing abierto. | 0,8 pts |
| Descripción de 3 elementos, pero con errores | Se describen los 3 elementos solicitados, pero con errores leves en algunos de ellos. | 0,64 pts |
| Descripción de 2 elementos | Se describen correctamente 2 elementos. | 0,54 pts |
| Descripción de 2 elementos, pero con errores | Se describen 2 elementos, pero con errores leves. | 0,38 pts |
| Descripción de un elemento | Se describe de manera correcta solo un elemento. | 0,26 pts |
| Descripción de un elemento, pero con errores leves | Se describe solo un elemento, el cual presenta errores leves. | 0,1 pts |
| No presenta descripción | No se presenta una descripción de las estructuras, o la presentada tiene serios errores de correctitud y completitud. | 0 pts |

## 3. Código y documentación — 0,8 puntos

**Criterio:** Se entrega el código fuente de las tres estructuras de datos y su documentación.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Código y documentación adecuados | Tanto el código como la documentación son adecuados al contexto de la tarea. Se entenderá como documentación adecuada aquella contenida dentro del mismo código o en un archivo adjunto. | 0,8 pts |
| Documentación y/o código incompletos | El código está incompleto o incorrecto, o la documentación es deficiente porque no aporta a explicar el código mismo. | 0,4 pts |
| Código y/o documentación con errores graves | No se entrega el código y/o documentación. También se considerará una falta grave el plagio del código o de la documentación sin las debidas referencias a las fuentes originales. | 0 pts |

## 4. Datasets y diseño experimental — 0,4 puntos

**Criterio:** Descripción del dataset, métodos de lectura/escritura y *setup* experimental.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Descripción adecuada | Se describe de manera adecuada y concisa el dataset utilizado en la evaluación experimental. Además, se describe el equipo computacional utilizado; como mínimo, incluye tipo de procesador, tamaño de memoria RAM y tamaño de memorias caché. | 0,4 pts |
| Descripción incompleta o con errores | La descripción entregada, tanto del dataset como del equipo computacional, contiene errores o está incompleta. | 0,2 pts |
| Sin descripción | No se entrega una descripción o la entregada contiene errores graves. | 0 pts |

## 5. Exposición de resultados experimentales — 3 puntos

**Criterio:** Incluye una sección describiendo los experimentos realizados, resumiendo de manera adecuada los resultados obtenidos mediante tablas y figuras.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Se presentan resultados de las 3 estructuras y los dos tipos de clave | Se entregan y explican adecuadamente resultados para hashing abierto, hashing cerrado y `unordered_map`, utilizando `user_id` y `user_screen_name`. Se incluyen resultados de tiempo de ejecución y espacio de las estructuras. | 3 pts |
| Se presentan resultados de 2 estructuras y los dos tipos de clave | Los resultados están bien explicados y resumidos, pero corresponden solo a dos estructuras de datos. Se incluyen tiempo, espacio y ambos tipos de clave. | 2 pts |
| Se presentan resultados de las 3 estructuras, pero solo un tipo de clave | Los resultados están bien explicados y resumidos. Se incluyen tiempo y espacio, pero solo se considera `user_id` o `user_screen_name`. | 1,5 pts |
| Se presentan resultados de 2 estructuras, pero solo un tipo de clave | Los resultados están bien explicados y resumidos, pero corresponden solo a dos estructuras y una clave: `user_id` o `user_screen_name`. | 1,01 pts |
| Se presentan resultados de una estructura y los dos tipos de clave | Los resultados están bien explicados y resumidos, pero solo se presenta una estructura de datos. Se incluyen tiempo, espacio y ambas claves. | 1,01 pts |
| Se presentan resultados de una estructura y un tipo de clave | Los resultados están bien explicados y resumidos, pero solo consideran una estructura y una clave: `user_id` o `user_screen_name`. | 0,5 pts |
| Resultados incorrectos | No se presentan resultados experimentales o los presentados tienen serios errores. | 0 pts |

## 6. Conclusiones — 0,5 puntos

**Criterio:** Incluye una sección con conclusiones y reflexiones generadas a partir del desarrollo del trabajo.

| Nivel | Descripción | Puntaje |
|---|---|---:|
| Conclusiones adecuadas | Las conclusiones son correctas y están respaldadas por los resultados mostrados en la sección de experimentos. | 0,5 pts |
| Conclusiones mayoritariamente adecuadas | Las conclusiones son correctas y están respaldadas por los resultados mostrados en la sección de experimentos; no obstante, presentan algunos errores leves y omisiones. | 0,35 pts |
| Conclusiones insuficientes | Las conclusiones presentan errores considerables, aunque contienen reflexiones rescatables. | 0,15 pts |
| Conclusiones incorrectas o sin conclusiones | No se entregan conclusiones o las entregadas contradicen los resultados experimentales. | 0 pts |
