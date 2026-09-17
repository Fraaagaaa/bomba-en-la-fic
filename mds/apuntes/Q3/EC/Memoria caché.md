## Introducción
La memoria caché es una memoria pequeña y rápida que se sitúa entre la CPU y la memoria principal. Almacena la información actualmente en uso de la memoria principal. En los computadores actuales está implementada dentro del chip del procesador (tecnología semiconductores).
Es una memoria volátil y una memoria asociativa: los datos se referencian a través de su contenido, buscamos un dato determinado dentro de una memoria sin saber si está o no y tampoco necesariamente en qué posición de la memoria se encuentra.
## Estructura del caché
La información de la caché se divide en bloques llamados líneas. Llamamos tamaño de línea al número de bytes que contiene una línea de la caché, 1 o maś palabras.
La línea es la unidad indivisible dentro de una caché: no es posible ni cargar ni eliminar porciones de una línea, cuando se carga una palabra en la caché, se carga toda la línea que la contiene esto permite aprovechar la localidad espacial.
Zona de almacenamiento: contiene la copia de algunas líneas de memoria principal.
Directorio: contiene información sobre las líneas, bloques, de la zona de almacenamiento.
- Los bits de control que contienen información de control relacionada con cada línea caché. El bit de validez permite conocer si un bloque de la caché no tiene información válida.
- La etiqueta para identificar si una palabra es caché se corresponde con la palabra buscada.
<br>
En la caché se almacenan datos, por lo que cada línea dispone de espacio para ellos. Los datos almacenados en una línea pueden provenir de cualquier dirección de memoria a la que esté asignada esa línea. Por tanto, no está claro el origen de un dato almacenado en la caché.
Para resolver este problema, cada línea almacena también una etiqueta, que indica la dirección en memoria del dato que contiene.
<br>
En un principio la caché está vacía. Cada línea tiene un bit de validez que indica si la línea contiene datos válidos o no y a medida que se llena la caché se van activando los bits de validez. Cuando no hay posiciones libres donde poder ubicar una línea es necesario reemplazar una de las que hay cargadas.

## Organización de un sistema caché
Existen tres categorías de organización dependiendo de la función de correspondencia (algoritmo que hace corresponder bloques de memoria principal a líneas caché):
Correspondencia directa: hace corresponder cada bloque de memoria principal a sólo una línea posible de caché. Asociativa, o totalmente asociativas): permite que el bloque de memoria pueda recargarse en cualquier línea de la caché.
Asociativa por conjuntos: solución de compromiso que recoge lo positivo de las dos soluciones anteriores.
<br>
Las cachés asociativas o asociativas por conjuntos permiten que cada bloque de memoria pueda ser alojado en más posiciones diferentes de la caché lo que reduce la tasa de fallos, pero complica el diseño ya que genera mayor consumo de energía, son más costosas y provoca un mayor tiempo de acceso.

## Cachés de correspondencia directa
Físicamente, una cachés de correspondencia directa es una memoria estática de acceso aleatorio pequeña y rápida. Su principal característica es que cada dato tiene asignada una posición fija en la caché.
Dada una caché de correspondencia directa con *p* posiciones, un dato almacenado en la dirección *d* sólo podrá alojarse en la posición *d* módulo *p* (d%p) de la caché.

En este tipo de caché puede haber fallos forzosos, de capacidad si el programa usa más bloques de los que caben en la caché y de conflicto porque varios bloques distintos pueden mapear a la misma línea y reemplazarse mutuamente.
## Caché totalmente asociativa
Permite que un bloque de memoria principal se cargue en cualquier línea de la memoria caché. Mientras la caché no está llena la asignación de línea no está fijada. Cuando está llena se necesita un algoritmo de reemplazo. Técnicamente, una caché asociativa es una memoria direccionable por contenido. En lugar de utilizar una dirección, se utiliza una etiqueta, y la memoria la buscará en su directorio y devolverá el dato asociado. Esto es muy complejo y costoso porque todas todas las comparaciones se realizan en paralelo.
En este tipo de caché puede haber fallos forzosos, que ocurren la primera vez que se accede a un bloque, y fallos de capacidad si el conjunto de bloques que utiliza  el programa supera el tamaño total de la caché. Sin embargo, no hay fallos de conflicto, ya que cualquier bloque de memoria puede almacenarse en cualquier línea de la caché.

### Algoritmos de reemplazo
Su función es decidir qué línea sale de la caché cuando es necesario un reemplazo. Son algoritmos sencillos que se implementan en hardware:
- FIFO
- LRU (Least recently used).
- LFU (Least frequently used)
- Aleatorio.
### Asociatividad por conjuntos
Consiste en dividir la caché en conjuntos de varias líneas. Dentro de cada conjunto la asociatividad es total. Al número de líneas por conjunto le llamamos número de vías. Cada dirección de memoria tiene asignado un conjunto de forma directa, pero dentro de ese conjunto puede ir a cualquiera línea. Es una solución intermedia entre la asociatividad total y la correspondencia directa. Consigue resultados próximos a la asociatividad total con un coste razonable.
## Escritura en la caché
Cuando un programa escribe en memoria y el dato antiguo ya está en la caché, hay dos opciones:
- Post-escritura o write-back: Se escribe sólo en la caché y se indica que esa línea ha sido modificada de forma que sólo se actualizan los niveles inferiores cuando la línea se expulsa de la caché.
- Escritura directa o write-through: Se escribe en la caché y en los niveles inferiores de la jerarquía de la memoria.
- Caché de post-escritura:
	- Varias escrituras consecutivas en la misma línea implican una única escritura en memoria principal.
	- Un fallo caché puede requerir una escritura y una lectura en memoria principal.
- Caché de escritura directa:
	- Siempre habrá una copia del dato actualizado en la memoria principal.
	- En memoria sólo se escribe el dato afectado, y no la línea completa.
	- Una escritura siempre implica actualizar tanto la caché como la memoria principal.
<br>

Al resolver un fallo de escritura caché hay dos opciones:
- Ubicar en escritura o write-allocate: La línea se carga y siguen las acciones de abierto de escritura.
	- Las escrituras subsiguientes en la línea no provocarán fallos.
- No ubicar en escritura o No-write-allocate: Se escriben directamente en otro nivel y la línea nunca viene a la caché
	- Las escrituras subsiguientes en la línea seguirán provocando fallos en la caché
	- Este modo existe como un modo avanzado en procesadores ARM que requiere intervención del programador. Se utiliza en programas que generan gran cantidad de resultados y en  los que la localidad temporal no se cumple de forma satisfactoria, p.e. muchos programas multimedia.
## Eficiencia de la caché
La principal medida de la eficiencia de una caché es la relación entre aciertos y fallos. Mejor en cachés asociativas o totalmente asociativas.
Existen otras medidas de eficiencia: el consumo de energía, más bajo en cachés de correspondencia directa, y el tiempo de acceso, más bajo en cachés de correspondencia directa.

### Tipos de fallos
Forzosos: Se producen la primera vez que se referencia un bloque de memoria. Se pueden reducir aumentando el tamaño de línea.
De capacidad: Cuando es referencia un dato que fue reemplazado porque la caché estaba llena. Se pueden reducir aumentando el tamaño del caché.
De conflicto: En correspondencia directa o asociativas por conjuntos cuando dos líneas compiten por la misma posición en la caché. Se reducen aumentando la asociatividad de la caché.

### Reducción de fallos
Incrementar el tamaño de línea, a mayor tamaño de línea:
- Mayores oportunidades de aprovechar la localidad espacial, secuencial, y reduce los fallos forzosos.
- A igual tamaño de caché, menor número de líneas y aumenta el número de reemplazos y puede incrementar los fallos de conflicto y los de capacidad.
- Incrementa la penalización por fallo: mayor coste temporal de transferir una línea.
<br>
Incrementar la asociatividad, a mayor asociatividad:
- Menor número de fallos de conflicto.
- Caché más lenta, mayor tiempo de acierto.
- Mayor coste
En la práctica, una caché asociativa por conjuntos de 8 vías es casi tan efectiva como una caché totalmente asociativa. Una caché de correspondencia directa tiene aproximadamente la misma tasa de fallos que una caché víctima, busca reducir principalmente los fallos de conflicto, y caché pseudo-asociativa, busca también reducir los fallos de conflicto.
El amento de asociatividad en el segundo nivel tiene poco impacto en el tiempo de acierto en este nivel, pero el aumento de la capacidad disminuye también los fallos de conflicto y por tanto los beneficios de la asociatividad.
Grandes tamaños llevan a incrementar el tamaño de la línea:
- Distintos niveles de caché pueden tener distinto tamaño de línea.
Propiedad de inclusión multinivel:
- Todos los datos de la caché de primer nivel están en la del segundo nivel.
- Deseable para mantener la consistencia.
- Algunos sistemas la cumplen y otros no.
Se pueden mantener con distintos tamaños de línea en las cachés, mediante invalidación de líneas de primer nivel. En las cachés del segundo nivel, el énfasis se hace en la reducción de fallos, usando cachés grandes, alta asociatividad y líneas grandes.
