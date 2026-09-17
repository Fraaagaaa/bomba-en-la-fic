## Introducción
La memoria es uno de los bloques funcionales básicos, junto con la unidad de control, la unidad de procesamiento y la de entrada/salida.
En la memoria se almacenan tanto datos como instrucciones.
Existe un continuo movimiento de información entre la memoria y el procesador. El rendimiento depende en gran medida de ambos elementos.
La estructura de la memoria es un conjunto de posiciones, cada una de las cuales contiene un número determinado de bits.
- La información se almacena en forma de bits, los bits de agrupan para formar bytes y palabras. Una palabra es una unidad de organización de la memoria. Su tamaño suele coincidir con el número de bits utilizados para representar números con la longitud de las instrucciones.

Debemos distinguir entre la dirección de un dato y su contenido. Una dirección de memoria puede indicarlos la ubicación de un solo bit,  de un byte o de una palabra completa. Con n bits podemos direccionar m = 2^n datos diferentes.
Asimismo, el número de bits necesarios para direrccionar m datos diferentes es n = log2(m).
<br>
Características deseables de la memoria: Rapidez (bajo tiempo de acceso), Alta capacidad y Coste bajo (coste por bit).
Problema para conjugar estas 3 virtudes: A mayor rapidez, mayor coste por bit; A mayor capacidad, menor rapidez; y a mayor capacidad menor coste por bit.
En general, si tenemos 2 de las 3 características, la otra se disparará.

## Jerarquía de la memoria
La diferencia entre el rendimiento del procesador y de la memoria aumenta en cada generación debido a la Ley de Moore.
- El rendimiento del procesador se degrada debido a las continuas paradas que tiene para hacer esperar por la carga de datos.

La jerarquía de memoria es una organización del subsistema de memoria que trata de mitigar este problema.
- El subsistema de memoria está compuesto por varios dispositivos de memoria que se organizan jarárquicamente.
- Memorias rápidas y pequeñas en los niveles superiores de la jerarquía se combinan con otras más lentas y grandes en los niveles inferiores.

El objetivo es crear la ilusión de que toda la memoria es tan rápida como la del nivel superior y tan grande como la del nivel inferior.
<br>
A medida que descendemos en la jerarquía de memoria: la memoria se hace más lenta, se disminuye el coste por bit y aumenta la capacidad.
Los niveles de la jerarquía de memoria son de acceso aleatorio. La latencia es, aproximadamente, la misma para acceder a cualquier posición de la memoria.
**SRAM** (Static Random Access Memory): Acceso muy rápido, no necesita refresco, mayor coste y preferible para registros y cachés.
**DRAM** (Dynamic Random Access Memory): Mucha más capacidad, menor coste y preferible para chips independientes.
**SDRAM** (Synchronous DRAM): Coordinada oir una señal de reloj externa y utilizada actualmente para memoria principal.
### Jerarquía de memoria: Funcionamiento
Cuando se enciende solo los niveles inferiores, los no volátiles, contienen la información. A medida que el procesador opera van emitiendo de las direcciones de memoria donde se encuentran tanto las instrucciones como los datos que necesita. A medida que se van referenciando datos desde el procesador estos, a parte de ser proporcionados al procesador, se van cargando en los niveles superiores de la jerarquía. La carga de los datos se produce en bloques, es decir, se carga el dato pedido y una cierta cantidad de datos adyacentes.
1. Cuando un datos es referenciado, primero se comprueba si está en el nivel superior de la jerarquía.
2. Si se encuentra se le proporciona al procesador y sino se va a buscar al nivel inmediatamente inferior de la jerarquía
3. El proceso desciende de forma recursiva en la jerarquía hasta hallar el dato buscado.
- Cada vez que se referencia un dato, una vez encontrado se carga en todos los niveles de la jerarquía.
La jerarquía de memoria funciona bien cuando casi todos los bloques de memoria referenciados se encuentran en los niveles superiores de la jerarquía
- La clave del éxito de la jerarquía se basa en el principio de localidad.
#### Principio de Localidad
Un programa suele acceder a una parte reducida del espacio de direcciones. Las referencias a memoria generadas por un programa suelen estar agrupadas.
- Localidad espacial: Si un dato es referenciado, los datos próximos a él es probable que sean referenciados pronto.
- Localidad temporal: Si un dato es referenciado, es probable que ese mismo dato vuelva a ser referenciado pronto.
#### Jerarquía de memoria: Definiciones
Bloque: es la unidad mínima de transferencia de datos entre los distintos niveles de la jerarquía.
Acierto: Cuando un dato se encuentra en un determinado nivel de la jerarquía decimos que su búsqueda terminó en un acierto en ese nivel de jerarquía.
- Tasa de aciertos: es la fracción de accesos a un nivel de la jerarquía que resultó en un acierto

Fallo: Cuando un dato no se encuentra en un determinado nivel de la jerarquía.
- Tasa de fallos: fracción de accesos a un nivel de la jerarquía que resultó en un fallo (1 - tasa de aciertos).

Tiempo de acierto: tiempo de acceso al nivel superior de jerarquía.
Penalización por fallo: tiempo adicional requerido ante un fallo caché, para ir a buscar el dato en los niveles inferiores de la jerarquía e intercambiar un bloque del nivel superior por el bloque buscado y luego proporcionar el dato al procesador.
## Memoria princial: Conceptos básicos
Es el nivel de jerarquía de memoria ubicado entre la caché y el almacenamiento secundario. También sirve como interfaz con el subsistema de E/S.
Tecnología que se utiliza: generalmente usa SDRAM, memoria volátil, cuando se apaga el ordenador se pierde información; y memoria basada en tecnología semiconductora, cada celda de esta memoria está compuesta habitualmente de un transistor y un elemento de almacenamiento que contiene un bit de información.
### Memoria princial: Conceptos sobre la SDRAM
DIMM, Dual In-line Memory Module
- Es un módulo de RAM tal como lo conocemos hoy en día.
- Contiene 2 rangos, uno por cada cara, de 8 chips.

DDR (Double Data Rate):
- Capáz de transferir datos en ambos flancos de reloj.
- Cada generación soporta mayor frecuencia de reloj, mejora el ancho de banda, la tasa de transferencia, es más eficiente, etc.
### Memoria princial: Descomposición SDRAM
Un DIMM contiene 2 rangos, no necesariamente uno por cada lado.
Cada rango contiene 8 chips, cada chip se compone de 8 bancos de memoria apilados. El término banco referencia también al conjunto de 8 bancos análogos, con mismo ID, de un mismo rango, cada banco contiene 8 matrices de celdas. Cada celda almacena un único bit de información, podemos buscar la misma celda en el mismo banco en varios chips a la vez.
SDRAM permite acceder de forma simultánea a los bits que conforman una palabra. Si accedemos a los 8 bancos en los 8 chips, obtendremos 64 bits, para acceder de este modo, la información se almacena de forma cíclica: a nivel de bit entre chip y a nivel de byte entre bancos.
### Memoria principal: Canal
Por encima del acceso paralelo anterior, la placa madre puede tener varios canales para la memoria. Podemos transferir datos de módulos de diferentes canales simultáneamente:
- Dual-Chanel -> x2 Ancho de Banda
- Triple-Chanel -> x3 Ancho de Banda
El acceso a módulos de un mismo canal puede hacerse simultáneamente, pero no la transferencia. Sin embargo, el doble de ancho de banda no se traduce en el doble de velocidad de nuestro ordenador.
Empíricamente observamos un incremento de velocidad de 15 - 30%.
Los datos se transfieren en bloques, la latencia sigue siendo alta comparada con niveles superiores de la jerarquía y a pesar de la localidad, no todos los datos transferidos son utilizados.
### Memoria principal: Rendimiento
El rendimiento de la memoria principal determina el tiempo que tarda en resolverse un fallo caché. Parámetros que determinan el rendimiento de la memoria principal:
- Latencia: o tiempo en acceder al primer datos, depende de la tecnología empleada.
- Tiempo de transferencia: tiempo necesario para transferir el resto de la información requerida, depende del ancho de banda entre la caché y la memoria principal.
Formas de aumentar el ancho de banda entre la caché y la memoria principal:
- Aumentar el ancho de la memoria. El bus y la memoria pasan a tener varias palabras de ancho y se utiliza un multiplexor para seleccionar qué palabra se le proporciona a la caché en cada momento.
- Utilizar blancos de memoria independientes. La opción más sencilla pero también la más costosa.
- Utilizar memoria entrelazada
## Memorias entrelazadas
La información está repartida entre varios módulos de memoria. Así se pueden atender varias peticiones de forma solapada/simultánea.
Se sigue pagando el coste de transmitir cada palabra secuencialmente dentro de un mismo canal, pero se evita pagar más de una vez la latencia de acceso. Se hacen más rápidas las escrituras -> importante en escritura directa. Funcionan al mismo tiempo todos los módulos -> más consumo.
Esquemas de entrelazado: Entrelazado de orden superior, consecutivo, o Entrelazado de orden inferior
![[Pasted image 20251113174327.png]]

Con cualquiera de los dos esquemas se pueden obtener M palabras en paralelo por cada acceso a memoria.
Conflicto de memoria: varias direcciones requieren simultáneamente el acceso a un mismo módulo.
Los conflictos de memoria son mayores en orden superior debido a la secuencialidad. En sistemas multiprocesador es a veces mejor el entrelazado de orden superior cuando las tareas son disjuntas o interaccionan poco entre sí.
Se suele utilizar el entrelazado de orden inferior.
Ventajas del superior: expansibilidad y fiabilidad pues un fallo se restringe a un área localizada del espacio de direcciones.