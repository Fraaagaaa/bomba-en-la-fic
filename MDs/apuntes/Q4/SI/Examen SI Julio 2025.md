# Simbólica
### 4. Representación del Conocimiento mediante Reglas de Producción

Como modelo de representación del conocimiento, las reglas de producción...

- [ ] a) No suelen almacenar conocimiento heurístico.
    
- [ ] b) Deben combinarse para poder formar unidades completas de razonamiento.
    
- [ ] c) Siempre involucran condiciones y acciones explícitas.
    
- [ ] d) Ninguna de las anteriores es correcta.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> - La característica definitoria y estructural de las reglas de producción (como modelo procedimental) es precisamente que se organizan siempre en una arquitectura explícita de tres partes: un **IF** (que representa la condición o premisa explícita), un **THEN** (que representa la acción o conclusión explícita) y, opcionalmente, un **ELSE** (alternativa). Por tanto, su diseño siempre requiere especificar explícitamente qué condición debe darse y qué acción o conclusión desencadena.
>- **Por qué la b) es FALSA:** La teoría establece como una de las grandes ventajas de las reglas de producción su alta modularidad, afirmando literalmente que **"Cada regla constituye una unidad completa de razonamiento"** por sí sola. Por lo tanto, es falso afirmar que _necesitan_ combinarse con otras para formar una unidad completa de razonamiento, ya que son piezas lógicas independientes.
>- **Por qué la a) es FALSA:** Es exactamente al revés. Entre las ventajas fundamentales de los métodos procedimentales y las reglas de producción se cita textualmente que **"incorporan de forma natural conocimiento heurístico"** y permiten almacenar saberes muy específicos derivados de la experiencia.

### 5. Ejecución de Reglas en un Sistema de Producción

Cuando una regla se activa, ¿de qué depende su ejecución?

- [ ] a) De la estrategia de resolución de conflictos.
    
- [ ] b) Del contenido de la memoria activa.
    
- [ ] c) De las metas establecidas como hipótesis de trabajo.
    
- [ ] d) De todas las anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> En el ciclo de funcionamiento de un sistema de producción, el "contenido de la memoria activa" determina qué reglas se activan (fase de emparejamiento o _matching_), ya que evalúa qué condiciones se cumplen en ese instante. Sin embargo, una vez que el sistema tiene un conjunto de reglas activadas (conjunto conflicto), la decisión final de cuál de ellas se ejecuta (fase de acción) depende en exclusiva de la estrategia de "resolución de conflictos" dictaminada por el motor de inferencias (por ejemplo, orden léxico, mayor especificidad o prioridad en el tiempo).

### 6. Arquitecturas de Agentes Basados en Metas

Los agentes basados en metas...

- [ ] a) Basan su comportamiento en reflejos al estado del mundo.
    
- [ ] b) Mantienen un conocimiento interno del mundo y las consecuencias de sus acciones.
    
- [ ] c) Consideran la bondad de los estados para alcanzar los estados finales.
    
- [ ] d) Todas son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Dentro de las arquitecturas clásicas de agentes inteligentes, los agentes basados en metas no solo operan respondiendo de forma refleja al entorno (eso es propio de agentes reactivos simples). Necesitan llevar un registro del estado interno actual del mundo, combinarlo con un modelo de cómo sus acciones cambian ese entorno (las consecuencias) y utilizar información sobre su "meta" u objetivo para planificar qué secuencias de acciones les permitirán llegar al estado deseado. No cuantifican la "bondad" comparativa de las metas (eso corresponde a los agentes basados en utilidad).

### 7. Cálculo de la Base Lógica Reducida (BLR)

Sea un dominio con tres manifestaciones posibles $\{M(1), M(2), M(3)\}$ y dos interpretaciones posibles $\{I(1), I(2)\}$. Desde una perspectiva categórica, y dadas las reglas del dominio:

> R1: $M(1) \lor M(2) \lor M(3) \implies I(1) \lor I(2)$
> 
> R2: $I(1) \implies \neg M(1) \land M(2)$
> 
> R3: $I(2) \land \neg I(1) \implies M(1) \land M(3)$

¿Cuántos posibles conjuntos manifestación-interpretación contiene la Base Lógica Reducida?

- [ ] a) 7
    
- [ ] b) 32
    
- [ ] c) 16
    
- [ ] d) 11
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> La Base Lógica Expandida (BLE) contiene todas las combinaciones posibles de variables, que son $2^5 = 32$ complejos. Para obtener la Base Lógica Reducida (BLR), aplicamos las restricciones que dictan las reglas, eliminando los complejos absurdos:
> 
> - **R2 exige que:** Si $I(1) = 1$, entonces obligatoriamente $M(1) = 0$ y $M(2) = 1$. Esto elimina cualquier combinación donde $I(1)=1$ y no se cumplan esos valores. De los 16 casos iniciales donde $I(1)=1$, nos quedamos solo con **4 casos válidos** (ya que solo varían $I(2)$ y $M(3)$, dando $2 \times 2 = 4$).
>     
> - **R3 exige que:** Si $I(2)=1$ e $I(1)=0$, entonces obligatoriamente $M(1)=1$ y $M(3)=1$. De los 8 casos iniciales con estas condiciones, nos quedamos solo con los **2 casos válidos** donde $M(2)$ vale 0 o 1.
>     
> - **R1 exige que:** Si existe alguna manifestación activa, debe existir alguna interpretación. Nos quedan por evaluar los casos donde $I(1)=0$ e $I(2)=0$. Si ambas interpretaciones son $0$, ninguna manifestación puede ser $1$. Esto nos deja con **1 único caso válido**: todos los valores a 0.
>     
> 
> Sumando los complejos válidos: $4 + 2 + 1 = 7$ conjuntos posibles en la BLR.

### 8. Inferencia a Partir de Manifestaciones Verdaderas

Asumiendo $M(1)$ verdadero, la solución será...

- [ ] a) $I(1) \land I(2)$
    
- [ ] b) $I(1) \land \neg I(2)$
    
- [ ] c) Ambas las anteriores
    
- [ ] d) Ninguna de las anteriores
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Del cálculo anterior, sabemos que si $I(1)$ es verdadero, $M(1)$ es forzosamente falso (por la regla R2). Es decir, en la BLR no existe ningún caso válido en el que $I(1)$ y $M(1)$ sean verdaderos al mismo tiempo.
> 
> Si observamos los 7 casos de la BLR elaborados en la pregunta anterior, los únicos donde $M(1)$ es verdadero son aquellos 2 casos derivados de la regla R3, y en ambos escenarios las interpretaciones toman el valor de $I(1)=0$ e $I(2)=1$. Por tanto, la solución que se inferiría al ser cierta $M(1)$ es estrictamente $\neg I(1) \land I(2)$. Al no aparecer esta expresión exacta en las opciones a) y b), la correcta es la d).

### 9. Análisis Probabilístico en Lógica Categórica

Partiendo del problema original, ¿qué manifestación es más probable cuando ambas interpretaciones son verdaderas?

- [ ] a) $M(1)$
    
- [ ] b) $M(2)$
    
- [ ] c) $M(3)$
    
- [ ] d) Son equiprobables
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Si asumimos que ambas interpretaciones son verdaderas, es decir, ocurre el caso $I(1)=1$ e $I(2)=1$, estaremos circunscritos a los casos derivados de que $I(1)$ es cierto. Según la regla R2 ($I(1) \implies \neg M(1) \land M(2)$), siempre que $I(1)$ se cumple, $M(2)$ debe darse inexcusablemente (probabilidad 1.0) y $M(1)$ jamás puede darse (probabilidad 0). $M(3)$ no está restringida por ninguna regla en este subescenario, por lo que su aparición es aleatoria. Por tanto, la manifestación absolutamente segura (y por ende más probable) bajo estas condiciones es $M(2)$.

### 10. Fase de Acción en el Ciclo de Inferencia

La ejecución de las reglas seleccionadas, en la fase de acción, concluye con...

- [ ] a) El proceso inferencial
    
- [ ] b) La verificación de si continuar o no el proceso cíclico
    
- [ ] c) La actualización de la memoria activa y el motor de inferencias
    
- [ ] d) Ambas b) y c) son correctas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> En los sistemas basados en reglas (sistemas de producción), la arquitectura establece un ciclo que incluye emparejamiento, resolución de conflictos y ejecución de acciones. Esta fase final de ejecución concluye procesando el consecuente de la regla, lo que modifica irrevocablemente los hechos del sistema, es decir, produce la actualización de la Memoria Activa introduciendo nuevo conocimiento (hipótesis) o alterando el actual.

### 11. Análisis de Algoritmos de Búsqueda en Profundidad

Los procedimientos de búsqueda en profundidad...

- [ ] a) Demandan más recursos computacionales (en términos espaciales) que los basados en anchura
    
- [ ] b) No son completos en espacios de estados finitos si están basados en grafos
    
- [ ] c) Están limitados computacionalmente por el tamaño del espacio de estados si están basados en árboles
    
- [ ] d) Ninguna de las anteriores es correcta
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Se descartan una a una:
> 
> - **a) es falsa:** La búsqueda en profundidad se caracteriza por ser mucho más eficiente en el consumo de memoria espacial $O(b \cdot m)$ frente a la tremenda explosión de memoria de la búsqueda en anchura $O(b^d)$.
>     
> - **b) es falsa:** La versión de grafos (que lleva un registro de nodos visitados o cerrados) sí es completa en espacios de estados finitos porque asegura que el algoritmo no quedará atrapado en bucles de redundancia.
>     
> - **c) es falsa:** En su versión de árbol, si existen ciclos en el espacio del problema, la profundidad explorada se vuelve infinita. Por lo tanto, no se encuentra computacionalmente limitada por el tamaño del espacio, sino por la máxima ramificación cíclica (pudiendo ser infinita y quedarse atrapado).
>     

### 12. El Espacio de Complejos Manifestación-Interpretación

El conjunto de complejos manifestación-interpretación...

- [ ] a) Representa el conjunto total de situaciones posibles en el problema
    
- [ ] b) No es completo si el conocimiento no es categórico
    
- [ ] c) Presenta elementos mutuamente excluyentes
    
- [ ] d) Ninguna de las anteriores es correcta
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> En el razonamiento categórico, el conjunto de complejos manifestación-interpretación ($M \times I$) compone la Base Lógica Expandida (BLE). Este conjunto se formula construyendo y emparejando la exhaustividad completa de los vectores de síntomas (manifestaciones) y etiologías (interpretaciones). Por su mera definición, su construcción captura todas y cada una de las situaciones, escenarios o estados potenciales posibles para un problema antes de aplicar la función de conocimiento $E$ que filtra los complejos incompatibles.

### 13. Modularidad y Mantenimiento en Sistemas de Producción

Se dispone de un sistema de producción sobre un problema dado. En cierto punto, el cliente se da cuenta que la información está incompleta, y necesita añadir dos reglas más que cubren unos casos específicos que no había contemplado anteriormente. ¿Qué se debería de cambiar en el motor de inferencias?

- [ ] a) Se deben insertar las nuevas reglas
    
- [ ] b) Se deben insertar las nuevas reglas y los hechos que sean resultado de dichas reglas
    
- [ ] c) Se debe rehacer completamente el sistema de reglas, para adecuarlo a la problemática actual
    
- [ ] d) Nada
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Una de las ventajas de los sistemas de producción es su extrema modularidad e independencia. El "Motor de Inferencias" es un componente fijo, encargado puramente del sistema de control y evaluación cíclica. Todo el conocimiento concreto (como las dos reglas nuevas) se almacena y añade de manera exclusiva a la Base de Reglas (Conocimiento). Por tanto, ante un requerimiento de adición de nueva información sobre el dominio, el motor de inferencias no experimenta ningún cambio estructural ni lógico.

### 14. Arquitectura y Componentes de los Sistemas de Producción

Si hablamos de sistemas de producción...

- [ ] a) La base de conocimientos está formada por la base de reglas y el motor de inferencias
    
- [ ] b) Los sistemas dirigidos por los datos son más específicos, porque ejecutarán todas las reglas disponibles en función de la información introducida
    
- [ ] c) La memoria activa almacena todos los cambios de estado de nuestro sistema, de forma que representa siempre nuestro estado actual
    
- [ ] d) El motor de inferencias es el responsable de interaccionar con el mundo exterior
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> En un sistema de producción clásico, la Memoria Activa actúa como la "pizarra" del sistema; su trabajo es albergar puramente los "hechos" instantáneos e ir almacenando cada variación y nuevo estado detectado tras la fase de acción de las reglas. Esta característica garantiza que la Memoria Activa mantenga con exactitud una instantánea continua y fidedigna del estado actual de ejecución en todo momento. Se descartan las otras opciones porque el motor de inferencias NO forma parte de la Base de Conocimientos (que es la conjunción de Base de Hechos y Base de Reglas), y porque las interfaces (no el motor) se encargan de la comunicación con el exterior.

# Subsimbólica

### 5. Núcleo de los Avances Tecnológicos

¿Qué se encuentra en el "core" de los principales avances tecnológicos actuales y de los próximos años?

- [ ] a) La rama de la inteligencia artificial subsimbólica.
    
- [ ] b) La rama de la inteligencia artificial simbólica.
    
- [ ] c) La computación cuántica.
    
- [ ] d) Todas las anteriores.
    
- [ ] e) Ninguna de las anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Nos encontramos en la denominada "tercera primavera de la IA". Este resurgir masivo y el núcleo tecnológico actual (como el _Deep Learning_, ChatGPT, Visión por Computador, etc.) está impulsado única y exclusivamente por el paradigma conexionista o IA subsimbólica, alimentado por el fenómeno del _Big Data_ y la capacidad de computación en paralelo.

### 6. Precursores Biológicos

En la evolución histórica de los sistemas conexionistas, ¿cuáles son precursores biológicos?

- [ ] a) Donald Hebb.
    
- [ ] b) Santiago Ramón y Cajal.
    
- [ ] c) Warren McCulloch.
    
- [ ] d) Todos los anteriores.
    
- [ ] e) Ninguno de los anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Ramón y Cajal descubrió la estructura fundamental del sistema nervioso (la Doctrina de la Neurona); Donald Hebb postuló la regla del aprendizaje sináptico ("una vía que se usa, se refuerza"); y Warren McCulloch (junto a Walter Pitts) fue el encargado de trasladar esa biología a un modelo lógico-matemático en 1943. Los tres conforman los cimientos biológicos de las redes neuronales.

### 7. Objetivos de la IA

¿Qué pretende la IA como ciencia y como ingeniería?

- [ ] a) Conocer cómo funcionan los seres inteligentes y qué pueden hacer con la ayuda de computadores.
    
- [ ] b) Cómo hacer que los computadores hagan las cosas que hacen las personas inteligentes.
    
- [ ] c) Cómo superar el Régimen de Lovelace.
    
- [ ] d) Construir o implementar "Sistemas Inteligentes": SCX, SS.EE, ...
    
- [ ] e) Todas las anteriores son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> La IA se articula sobre un doble objetivo: como "Ciencia" persigue el entendimiento empírico de la mente y la superación del Régimen de Lovelace (lograr que una máquina origine ideas, no solo que repita código); y como "Ingeniería" busca la automatización práctica y construcción física de dichos sistemas (Sistemas Conexionistas, Sistemas Expertos, etc.).

### 8. Características de los Sistemas Inteligentes

¿Características específicas de los sistemas inteligentes?

- [ ] a) Intencionalidad: comportamiento guiado por metas.
    
- [ ] b) Incapacidad de conocer y proyectar el "hoy sostenido".
    
- [ ] c) Ser metódico, no innovador.
    
- [ ] d) Tener efecto serendipico.
    
- [ ] e) Ninguna de las anteriores está relacionada.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> A diferencia de los programas informáticos tradicionales que siguen una serie de algoritmos fijos, los sistemas inteligentes (típicamente formulados como Agentes) se caracterizan fundamentalmente por su intencionalidad. Esto significa que perciben su entorno, evalúan un estado interno y toman decisiones ponderando acciones con el objetivo final de lograr y maximizar la satisfacción de una serie de metas u objetivos concretos.

### 9. Trabajo Científico Fundacional

¿Cuál es el principal trabajo científico en el que se basa la IA?

- [ ] a) "The Nature of Explanation" (W. Craik).
    
- [ ] b) "Behaviour, purpose and teleology" (Wiener, Rosenblueth y Bigelow).
    
- [ ] c) "A logical calculus of the ideas immanent in nervous activity" (McCulloch y Pitts).
    
- [ ] d) Todas las anteriores son correctas.
    
- [ ] e) Ninguna de las anteriores es correcta.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> El nacimiento formal de la inteligencia artificial y de los sistemas conexionistas como disciplina científica no bebe de una única fuente, sino de tres pilares multidisciplinares fundamentales de 1943: la propuesta cibernética sobre las máquinas teleológicas de Wiener, la capacidad de los sistemas para usar modelos lógicos de Craik, y la representación matemática-booleana de la neurona humana planteada por McCulloch y Pitts.

### 10. Origen del Término IA

¿Quién acuña por primera vez y tal como se entiende hoy la expresión "Artificial Intelligence"?

- [ ] a) John McCarthy.
    
- [ ] b) Ada Lovelace.
    
- [ ] c) Alan Newell y Herbert Simon.
    
- [ ] d) Gottfried Leibniz.
    
- [ ] e) Alan Turing.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Fue el informático John McCarthy quien acuñó oficialmente el término "Inteligencia Artificial" para bautizar la célebre conferencia "Proyecto de Investigación de Verano en Dartmouth sobre Inteligencia Artificial" de 1956. Esta conferencia unió a las mentes más brillantes del momento (Minsky, Newell, Simon, etc.) y se considera el hito fundacional de la IA moderna.

### 11. Descenso del Gradiente

Al aplicar el gradiente descendente para modificar los pesos de las conexiones de una RNA...

- [ ] a) Si este es cero, indica que el mínimo está lejos y es necesario realizar más saltos.
    
- [ ] b) Si es alto, se realiza un salto pequeño en el espacio de búsqueda.
    
- [ ] c) Si es bajo, se realiza un salto grande en el espacio de búsqueda.
    
- [ ] d) Es necesario modificar los pesos en sentido (signo) dictado por el gradiente.
    
- [ ] e) Es necesario modificar los pesos en sentido (signo) contrario al dictado por el gradiente.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> El algoritmo del descenso del gradiente (basado en la Regla Delta) busca sistemáticamente el punto más bajo (el mínimo) de la función de error. Por definición matemática, el gradiente apunta en la dirección de máximo crecimiento de una función. Por tanto, para reducir el error de la RNA, los pesos siempre deben ajustarse desplazándose en el sentido u opuesto (restándolo) al vector gradiente.

### 12. Arquitectura del Perceptrón Simple

La RNA formada por una única neurona, sin capas ocultas, con una función de transferencia umbral, pensada para resolver problemas de clasificación, se llama...

- [ ] a) ADALINE.
    
- [ ] b) Backpropagation.
    
- [ ] c) Perceptrón.
    
- [ ] d) Perceptrón multicapa.
    
- [ ] e) La b) y la d) son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> El Perceptrón simple es el modelo conexionista de clasificación más elemental introducido por Rosenblatt. Dispone únicamente de capa de entrada y salida (sin ocultas) y utiliza específicamente una función de transferencia de tipo escalón o umbral (_hard limiter_). El ADALINE es muy similar, pero se diferencia arquitectónicamente en que calcula su regla de aprendizaje basándose en una función de transferencia estrictamente lineal, no de umbral.

### 13. Problemas Linealmente Separables (AND)

Para utilizar un perceptrón multicapa para resolver el problema AND...

- [ ] a) No es necesario utilizar capas ocultas.
    
- [ ] b) Es necesario utilizar una capa oculta (con el número suficiente de neuronas), y no hacen falta más.
    
- [ ] c) Es necesario utilizar dos capas ocultas...
    
- [ ] d) Es necesario utilizar tres capas ocultas...
    
- [ ] e) Es necesario utilizar más de tres capas ocultas...
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> El operador lógico AND (y también el OR) constituye un problema que es linealmente separable. Esto significa geométricamente que un hiperplano o línea recta es capaz de dividir el espacio de soluciones correctas e incorrectas. Cualquier problema linealmente separable puede ser resuelto por una red de una sola capa (como un Perceptrón simple) sin necesidad de requerir arquitecturas multicapa.

### 14. Número de Neuronas Ocultas

El número de neuronas ocultas de un perceptrón multicapa...

- [ ] a) Lo puede fijar el usuario como quiera.
    
- [ ] b) Depende del número de entradas y salidas del problema a resolver.
    
- [ ] c) Debe ser igual al número de neuronas de entrada...
    
- [ ] d) Debe ser igual al número de neuronas de entrada, pero depende del problema...
    
- [ ] e) Debe ser igual al número de neuronas de salida...
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)** _(Nota: Su valor óptimo empírico depende directamente de la complejidad del problema a resolver)._
> 
> El número de capas y de neuronas en las capas ocultas no está dictaminado matemáticamente por las entradas y salidas de la RNA. Constituye un hiperparámetro arquitectónico que el diseñador de la red configura a voluntad. Sin embargo, en la práctica el usuario debe ajustar ese tamaño mediante prueba y error en base a la no-linealidad y complejidad del problema, evitando el sobreentrenamiento (si pone demasiadas) o la incapacidad de aprender (si pone demasiadas pocas).

### 15. Tasa de Aprendizaje Alta

Si al entrenar una RNA se utiliza una tasa de aprendizaje muy alta...

- [ ] a) Se acercará al mínimo con cambios muy pequeños.
    
- [ ] b) Se correrá el riesgo de oscilar en torno al mínimo.
    
- [ ] c) El entrenamiento se parará siempre en un mínimo local.
    
- [ ] d) El entrenamiento se parará siempre en un mínimo global.
    
- [ ] e) Se sobreentrenará la red.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> La tasa de aprendizaje ($\alpha$ o $\eta$) es el multiplicador escalar que define la longitud o tamaño del "paso" que da el algoritmo de entrenamiento a lo largo del espacio de pesos. Una tasa sumamente pequeña ralentizará drásticamente el entrenamiento; por el contrario, si es muy alta, la red generará saltos enormes, cruzando de un lado al otro del valle del error repetidamente, lo que provoca oscilaciones caóticas y le impide aterrizar y converger en el fondo del mínimo de la función.

### 16. Función de la Capa de Entrada

Las neuronas de la capa de entrada de un perceptrón multicapa...

- [ ] a) Aplican la función de transferencia a las entradas que reciben.
    
- [ ] b) Emiten su salida como la suma de las entradas multiplicadas por los pesos.
    
- [ ] c) Emiten su salida como el resultado de aplicar la función de transferencia a la suma de las entradas.
    
- [ ] d) Emiten su salida como el resultado de aplicar la función de transferencia a la suma del bias...
    
- [ ] e) Todas son falsas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Por convención estructural, la capa de entrada de un Perceptrón Multicapa no realiza ningún tipo de computación, cálculo del potencial postsináptico, suma ponderada de pesos o aplicación de una función de activación. Las células de entrada operan exclusivamente como meros receptores y transmisores transparentes del patrón de entrada del entorno hacia la primera capa oculta.

### 17. Cálculo del Error en Capas Ocultas (Backpropagation)

¿Cómo calcula el algoritmo de backpropagation el error en cada capa oculta?

- [ ] a) Comparando la salida obtenida y la salida deseada para esa capa oculta.
    
- [ ] b) Poniéndolo en función del error calculado en la siguiente capa.
    
- [ ] c) No lo calcula, puesto que no es necesario modificar los pesos de las capas ocultas.
    
- [ ] d) Comparando el valor de los pesos de esa capa con los de la capa siguiente.
    
- [ ] e) Comparando el valor de la tasa de aprendizaje con el gradiente.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)** 
> 
> Dado que las capas ocultas no disponen de una "salida deseada" o patrón objetivo que se les pueda comparar (como sí tiene la capa de salida), el algoritmo _Backpropagation_ (Propagación hacia atrás) resuelve este escollo calculando el gradiente en las neuronas ocultas de forma recursiva a partir del error de la capa inmediatamente posterior, ponderado por el valor de los pesos de conexión entre ellas.

### 18. Detención Temprana (Early Stopping)

En la técnica de parada temprana, para evitar el sobreentrenamiento, es necesario controlar el proceso de entrenamiento mediante un conjunto de...

- [ ] a) test.
    
- [ ] b) entrenamiento.
    
- [ ] c) prueba.
    
- [ ] d) validación.
    
- [ ] e) aprendizaje.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> La "parada temprana" (_early stopping_) es un mecanismo de regularización que divide el corpus de datos empíricos introduciendo un conjunto de validación. Este set no se usa para ajustar los pesos con el gradiente, sino exclusivamente para monitorear el error al final de cada época. Cuando el error de entrenamiento sigue descendiendo pero el de validación empieza a crecer, la red está comenzando a "memorizar" (sobreentrenamiento) y el entrenamiento debe ser abortado.

### 19. Codificación One-Hot

¿Cómo codificarías una salida de una RNA categórica, cuyos valores pueden ser "coche/moto/bicicleta/avión"?

- [ ] a) Como 2 valores booleanos, codificando las 4 categorías como "00/01/10/11".
    
- [ ] b) No hace falta codificarla, la RNA puede generar esa salida categórica.
    
- [ ] c) Como 4 valores booleanos, codificando las 4 categorías como "1000/0100/0010/0001".
    
- [ ] d) Como un valor real, que toma 4 valores distintos equiespaciados.
    
- [ ] e) La c) y la d) son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La representación de clases categóricas independientes requiere de un modelo de salida llamado codificación _One-Hot_. Obligar a la red a responder con un único valor real continuo equiespaciado para variables sin un orden de magnitud natural (un avión no "vale" matemáticamente más que un coche) introduciría un sesgo espurio de orden, obstaculizando gravemente la capacidad de la RNA para clasificar adecuadamente.

### 20. Funciones de Transferencia Ocultas

La función de transferencia de las neuronas de una Red de Neuronas Artificiales...

- [ ] a) Nunca debe ser lineal en la capa de salida.
    
- [ ] b) Nunca debe ser logarítmica sigmoidal en las capas ocultas (si hay).
    
- [ ] c) Nunca debe ser tangente sigmoidal hiperbólica en las capas ocultas (si hay).
    
- [ ] d) Nunca debe ser lineal en las capas ocultas (si hay).
    
- [ ] e) Nunca debe ser logarítmica sigmoidal en la capa de salida.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Si las capas ocultas operan bajo funciones de transferencia estrictamente lineales, toda la arquitectura multicapa perderá sus beneficios, ya que algebraicamente, una cascada de transformaciones lineales puede simplificarse siempre a una sola matriz de transformación equivalente (una sola capa). Esto destruiría la cualidad de aproximador universal de la red e imposibilitaría resolver problemas no lineales (como el XOR).

### 21. Objetivo de las Redes SOM

¿Cuál es el objetivo principal de las redes SOM en el contexto del aprendizaje no supervisado?

- [ ] a) Predecir valores futuros a partir de datos históricos.
    
- [ ] b) Clasificar datos con base en etiquetas conocidas.
    
- [ ] c) Encontrar estructuras o patrones en los datos sin conocer su categoría.
    
- [ ] d) Corregir errores de clasificación.
    
- [ ] e) Generar nuevas muestras sintéticas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Los _Self-Organizing Maps_ (SOM) o Mapas de Kohonen operan bajo un paradigma estrictamente no supervisado. Carecen de un tutor o etiquetas objetivo (_targets_) a reproducir; en su lugar, se alimentan de los datos y ajustan libremente su topología para descubrir distribuciones ocultas, realizar agrupamientos (_clusters_) y abstraer mapas topológicos basándose puramente en la similitud de las entradas.

### 22. Parámetro de Vecindad en SOM

¿Qué función tiene el parámetro de vecindad en una red SOM?

- [ ] a) Controlar el número de entradas.
    
- [ ] b) Medir el error de cuantización.
    
- [ ] c) Actualizar también las neuronas cercanas a la ganadora.
    
- [ ] d) Determinar el número de capas de la red.
    
- [ ] e) Ajustar la tasa de aprendizaje.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> El núcleo del funcionamiento del aprendizaje competitivo de los SOM es preservar la topología local. Cuando una neurona concreta (_Best Matching Unit_) gana frente a un estímulo por ser la más cercana matemáticamente a él, la regla de aprendizaje somete no solo a la ganadora, sino también a todas las neuronas que se encuentran en su "radio de vecindad" a una adaptación en sus pesos, garantizando que celdas próximas codificarán características similares.

### 23. Tasa de Aprendizaje en SOM ($\alpha$)

¿Qué ocurre con la tasa de aprendizaje ($\alpha$) durante el entrenamiento de una SOM?

- [ ] a) Aumenta con cada iteración.
    
- [ ] b) Se mantiene constante.
    
- [ ] c) Disminuye progresivamente.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Para que un mapa SOM se estabilice progresivamente y no quede en un estado de fluctuación perpetua, el algoritmo transita tradicionalmente por una fase inicial de "ordenación general topológica" (con una tasa de aprendizaje y un radio de vecindad grandes) hacia una fase de "convergencia fina", donde la tasa de aprendizaje debe decaer y disminuir paulatinamente hasta volverse prácticamente nula.
¡Tienes toda la razón! Al ir pasándome los textos por bloques en los mensajes anteriores, la franja de las preguntas 24 a la 30 se quedó en el tintero sin procesar. Disculpa el despiste.

### 24. El Error de Cuantización

¿Qué mide el error de cuantización en una SOM?

- [ ] a) La tasa de aprendizaje óptima.
    
- [ ] b) La distancia entre los pesos de la BMU y la entrada.
    
- [ ] c) El número de conexiones no utilizadas.
    
- [ ] d) El tiempo de entrenamiento.
    
- [ ] e) La salida binaria del clasificador.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> El Error de Cuantización (QE) es la medida de calidad estándar en los Mapas Autoorganizativos. Se calcula hallando la distancia media (normalmente la distancia euclídea) entre cada vector de datos de entrada y el vector de pesos de su neurona ganadora o BMU (_Best Matching Unit_). Cuanto menor es esta distancia en el conjunto, de forma más precisa estará representando el mapa a los datos originales.

### 25. Paradigma de Aprendizaje SOM

¿Cuál es el tipo de aprendizaje que utilizan las redes SOM?

- [ ] a) Supervisado.
    
- [ ] b) No supervisado y competitivo.
    
- [ ] c) Por refuerzo.
    
- [ ] d) Hebbiano supervisado.
    
- [ ] e) Supervisado jerárquico.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Las redes SOM (Mapas de Kohonen) aprenden sin necesidad de un tutor ni etiquetas de salida objetivo, por lo que su exploración es puramente **no supervisada**. Además, utilizan un paradigma **competitivo**: ante cada estímulo de entrada, las neuronas de la capa de salida "compiten" entre sí para ver cuál es la más parecida al dato. Solo la ganadora (y las vecinas dentro de su radio topológico) adquieren el derecho a actualizar sus pesos.

### 26. Utilidad de los Mapas de Kohonen

¿Cuál es la principal utilidad de una red SOM?

- [ ] a) Traducir idiomas en tiempo real.
    
- [ ] b) Clasificación de imágenes con etiquetas.
    
- [ ] c) Proyección de datos de alta dimensión a un espacio 2D para visualización.
    
- [ ] d) Generación de lenguaje natural.
    
- [ ] e) Detección de intrusos en redes.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La principal aplicación práctica de una red SOM es la reducción de dimensionalidad y el descubrimiento de agrupamientos (clústeres). Actúan como una herramienta de visualización topológica que permite mapear un conjunto de datos de enorme complejidad (vectores con muchas variables o n-dimensiones) y "aplastarlo" o proyectarlo sobre un mapa discreto bidimensional (2D) comprensible para el ojo humano, preservando las relaciones topológicas y vecindades originales de los datos.

### 27. Arquitecturas Dinámicas: GNG vs SOM

¿Qué ventaja presenta GNG sobre SOM?

- [ ] a) Usa aprendizaje supervisado.
    
- [ ] b) Su estructura se adapta dinámicamente y puede eliminar nodos.
    
- [ ] c) Solo necesita una capa de entrada.
    
- [ ] d) Funciona mejor con datos lineales.
    
- [ ] e) Utiliza funciones de activación sigmoide.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> A diferencia de los SOM, donde la topología y el número exacto de neuronas conforman una cuadrícula o malla rígida establecida desde antes de iniciar el entrenamiento, las redes GNG (_Growing Neural Gas_) poseen una arquitectura constructiva y dinámica. Pueden hacer crecer el mapa añadiendo nodos en las áreas de mayor error y, crucialmente, pueden desconectar y **eliminar nodos** (o aristas "viejas") que se quedan aislados o resultan inútiles, actuando como un "gas" que se adapta de forma flexible a la forma del espacio de datos.

### 28. Evolución de Modelos: GNG vs GCS

¿Qué problema resuelve GNG respecto a GCS?

- [ ] a) La dificultad para eliminar neuronas innecesarias.
    
- [ ] b) El uso de etiquetas incorrectas.
    
- [ ] c) La falta de paralelismo en la ejecución.
    
- [ ] d) El exceso de supervisión.
    
- [ ] e) La lentitud en el cálculo de distancias.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> El algoritmo GCS (_Growing Cell Structures_) introdujo el crecimiento dinámico en los mapas topológicos, pero lo hizo forzando a que las neuronas estuvieran conectadas rígidamente formando estructuras de triángulos perfectos (símplices 2D). Esta restricción geométrica provocaba enormes dificultades algorítmicas a la hora de tener que eliminar neuronas obsoletas, ya que al borrar un nodo se rompía la red de triángulos. GNG resolvió este escollo eliminando la restricción de los triángulos, permitiendo generar o destruir enlaces libremente.

### 29. Detección de Cambios Topológicos

¿Qué modelo de red es más adecuado para detectar cambios topológicos en los datos?

- [ ] a) Red SOM.
    
- [ ] b) Perceptrón multicapa.
    
- [ ] c) Red GNG.
    
- [ ] d) Red convolucional simple.
    
- [ ] e) Red Hebbiana clásica.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La red GNG (_Growing Neural Gas_) es el modelo más adecuado porque su diseño de aristas flexibles le permite mapear cualquier geometría, por compleja, ramificada o discontinua que sea. Si la nube de datos cambia su forma topológica con el tiempo, los SOM o GCS sufren intentando doblar sus mallas rígidas; por el contrario, la red GNG simplemente dejará de actualizar los enlaces viejos (eliminándolos por "edad") y generará nodos nuevos en las áreas activas, rastreando los cambios dinámicos a la perfección.

### 30. Innovación del GCS

¿Qué característica distingue al algoritmo GCS frente al SOM clásico?

- [ ] a) No puede eliminar nodos durante el entrenamiento.
    
- [ ] b) Permite añadir neuronas según el error acumulado.
    
- [ ] c) Funciona únicamente con etiquetas conocidas.
    
- [ ] d) Solo se usa para clasificación binaria.
    
- [ ] e) No necesita una capa de entrada.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> La característica fundacional del GCS (_Growing Cell Structures_) frente al SOM clásico de Kohonen es su naturaleza evolutiva. Mientras que el SOM exige predefinir de antemano cuántas neuronas (ej. $10 \times 10$) compondrán el mapa y ese número permanece inmutable, el GCS comienza con una estructura mínima (un solo triángulo) y permite **añadir progresivamente nuevas neuronas** insertándolas justo en aquellas regiones topológicas concretas donde la red está acumulando un mayor error de representación.
### 31. Sustitución de Individuos (Steady-State)

El concepto de "sustitución de individuos" en Algoritmos Genéticos...

- [ ] a) Se aplica en la estrategia de gestión de población denominada "Steady-state".
    
- [ ] b) Se aplica siempre combinada con la estrategia elitista.
    
- [ ] c) Es una estrategia para sustituir los parecidos en error en la población.
    
- [ ] d) Es una estrategia para sustituir los peores individuos de la población.
    
- [ ] e) No existe este concepto en Algoritmos Genéticos.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> En el enfoque clásico generacional de la computación evolutiva, toda la población desaparece en bloque al final del ciclo y es reemplazada íntegramente. El concepto explícito de "sustitución de individuos" individuales asume importancia central únicamente en los Algoritmos Genéticos de Estado Estacionario (_Steady-State_), donde en cada ciclo poblacional apenas nacen uno o dos descendientes y el sistema debe elegir matemáticamente a qué individuos antiguos eliminar para cederles su espacio vital.

### 32. Concepto de Generación

En un Algoritmo Genético, el término "Generación"...

- [ ] a) Representa cada ciclo de funcionamiento del Algoritmo.
    
- [ ] b) En el mecanismo de gestión de población "Steady-State", representa el cambio de todos los individuos...
    
- [ ] c) Representa seleccionar al mejor individuo de cada población...
    
- [ ] d) Es el mecanismo de generación de la población inicial...
    
- [ ] e) No existe este concepto en Algoritmos Genéticos.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Inspirado directamente por las dinámicas del neodarwinismo biológico, una "generación" define una iteración o bucle completo del motor del algoritmo evolutivo. En este ciclo suceden ordenadamente la evaluación del _fitness_ en la población vigente, la fase competitiva de selección, la recombinación genética (cruce), la perturbación aleatoria (mutación) y finalmente el reemplazo para iniciar un ciclo nuevo con material de un orden de aptitud superior.

### 33. Nodos Terminales en Programación Genética

En los individuos de un sistema de Programación Genética...

- [ ] a) Los terminales son operadores.
    
- [ ] b) No puede haber nunca operadores aritméticos como nodos del árbol.
    
- [ ] c) Los terminales pueden contener otros nodos e incluso subárboles.
    
- [ ] d) La raíz nunca puede ser un operador.
    
- [ ] e) Los terminales pueden ser constantes o variables.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> A diferencia de los Algoritmos Genéticos que usan vectores planos (cadenas de bits o reales), la Programación Genética estructura computacionalmente a cada individuo como un árbol sintáctico (lógico/aritmético). En esta topología, los nodos internos representan las funciones operadoras (`+`, `-`, `IF`, `AND`) mientras que las hojas finales o terminales corresponden forzosamente a los valores primitivos de parada: datos variables del problema o constantes escalares.

### 34. Operadores Genéticos (Cruce y Mutación)

Los operadores genéticos en Computación Evolutiva...

- [ ] a) Son: selección, cruce, mutación y generación.
    
- [ ] b) De cruce y mutación sirven para evolucionar los individuos de la población.
    
- [ ] c) Son operaciones que simulan la recombinación natural... a cada individuo...
    
- [ ] d) Sólo son aplicables sobre individuos de una población que sea siempre homogénea.
    
- [ ] e) Sólo son aplicables sobre individuos de una población que sea siempre heterogénea.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> El objetivo funcional primario del cruce (entrelazar el material cromosómico valioso de dos padres fuertes) y la mutación (añadir pequeños estímulos de ruido estocástico para asegurar la exploración espacial) es generar variación fenotípica artificial e inyectar nuevo material útil. Estas variaciones son el motor del cambio para que la especie (la población) alcance zonas óptimas del espacio de búsqueda evolutivo.

### 35. Múltiples Mínimos Locales en AG

La técnica de Algoritmos Genéticos...

- [ ] a) No funciona bien cuando existen múltiples mínimos locales en el espacio de búsqueda.
    
- [ ] b) Permite resolver problemas en espacios de búsqueda donde existen múltiples mínimos locales.
    
- [ ] c) Es una técnica de búsqueda exhaustiva de soluciones denominada "técnica determinística".
    
- [ ] d) Sólo permite realizar regresión simbólica y búsqueda de máximos o mínimos en funciones...
    
- [ ] e) No es conveniente utilizarla para resolver problemas no resolubles polinomialmente...
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Las técnicas clásicas de inferencia basada en derivadas numéricas sufren del problema inherente de quedar atrapadas inexorablemente en el primer mínimo local que encuentran. Los Algoritmos Genéticos (A.G.), al poseer un comportamiento estocástico y manipular un enorme enjambre o población de soluciones simultáneas (búsqueda multipunto o en paralelo), tienen altísimas probabilidades de saltar topológicamente y escapar de dichos sub-óptimos para dar con soluciones cuasi-óptimas globales a un problema altamente complejo (NP-Hard).

### 36. Elitismo en Computación Evolutiva

En un Algoritmo Genético, ¿qué significa el término "elitismo"?

- [ ] a) No existe este concepto.
    
- [ ] b) Solo es aplicable a la programación genética.
    
- [ ] c) Es la estrategia de mantener los mejores individuos en la población.
    
- [ ] d) Se encarga de buscar los mejores individuos y generar una nueva población con ellos.
    
- [ ] e) La nueva población es generada a partir exclusivamente del mejor individuo (élite).
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> El elitismo es un concepto introducido como red de seguridad teórica en los algoritmos evolutivos. Dado que las operaciones de cruce y mutación operan en base a probabilidades destructivas (es decir, hijos mediocres generados por padres brillantes), el elitismo garantiza mecánicamente clonar sin modificaciones al mejor individuo (o individuos) de la generación $T$ pasándolo directamente a la generación $T+1$, asegurando que el máximo progreso jamás retroceda.

### 37. Dinámica de Operadores y Mutación

En un algoritmo genético:

- [ ] a) Si la tasa de mutación es cero, el algoritmo funciona porque el cruce hace que haya evolución.
    
- [ ] b) Si la tasa de cruce es cero, la mutación hace que todos los individuos acumulen demasiados cambios.
    
- [ ] c) Si la tasa de cruce es cero, la mutación genera variabilidad y el algoritmo de selección hace que haya evolución.
    
- [ ] d) Si la tasa de cruce y la evolución son cero, el algoritmo...
    
- [ ] e) Es imposible que el cruce y/o mutación sean cero.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> A pesar de que los Algoritmos Genéticos operan de manera óptima fusionando cruce y mutación, en el hipotético caso arquitectónico en el que el operador de recombinación o cruce se desactivase (tasa de 0%), la mutación continuaría de forma residual introduciendo material genético de experimentación (variabilidad) y el sistema de selección se ocuparía de salvaguardar los hallazgos valiosos. Seguiría progresando y resolviendo el problema, operando prácticamente como una "Búsqueda Aleatoria Guiada" (Estrategia Evolutiva).


### 38. Representación en Programación Genética

Atendiendo al siguiente árbol que representa a un individuo de programación genética, ¿cuál de las siguientes afirmaciones es cierta? 
![[PropagaciónGeneticaJulio2025.png|400]]

- [ ] a) El conjunto de componentes terminales es sólo `[1, 14]`.
    
- [ ] b) Los componentes no terminales son $X$, $Y$, $+$, $-$.
    
- [ ] c) La profundidad máxima del árbol es 3.
    
- [ ] d) Se trata de un árbol invertido.
    
- [ ] e) No puede representar a un individuo porque tiene que ser un vector de variables.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)** _(Asumiendo el gráfico de los exámenes típicos de la asignatura)._
> 
> En la Programación Genética, las soluciones se codifican en forma de árbol sintáctico, por lo que la afirmación e) es rotundamente falsa. Las afirmaciones a) y b) son falsas por definición teórica: las variables de entrada del problema ($X$, $Y$) siempre son nodos hoja o "terminales", al igual que las constantes numéricas ($1$, $14$); mientras que los operadores aritméticos (`+`, `-`, `*`, `/`) y lógicos ocupan inexcusablemente los nodos internos o "no terminales". Por eliminación estructural, la aserción sobre la profundidad máxima del árbol es la única propiedad que describe una característica válida y cierta de este tipo de genotipo.

### 39. Modelos de Vida Artificial

¿Cuál de los siguientes elementos se utiliza habitualmente para simular organismos en vida artificial?

- [ ] a) Programación Genética.
    
- [ ] b) Autómatas celulares.
    
- [ ] c) Neuronas.
    
- [ ] d) Cromosomas.
    
- [ ] e) Genes.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Dentro de las técnicas de Vida Artificial (VA) orientadas a crear sistemas computacionales que imitan las propiedades de la biología, los **Autómatas Celulares** son la herramienta y modelo clásico por excelencia. El ejemplo más célebre es el _Juego de la Vida_ de John Conway: un autómata celular bidimensional donde cada "célula" representa a un organismo, cuyo ciclo de vida (nacimiento, supervivencia o muerte por soledad/sobrepoblación) evoluciona matemáticamente dependiendo exclusivamente del estado de sus vecinas inmediatas.

### 40. Ventajas de la Vida Artificial

Una de las principales ventajas de utilizar técnicas de vida artificial para resolver un problema complejo es:

- [ ] a) Garantizar siempre la consecución de la mejor solución.
    
- [ ] b) Reducir el número de datos necesarios para resolver el problema.
    
- [ ] c) Permitir explorar soluciones alternativas a través de la evolución.
    
- [ ] d) Usar reglas determinísticas para la resolución del problema.
    
- [ ] e) Eliminar por completo la intervención humana en el diseño de algoritmos que resuelvan el problema.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Las técnicas de vida artificial y computación evolutiva se enmarcan dentro de los métodos heurísticos o subsimbólicos. Por su naturaleza empírica, **no garantizan** hallar matemáticamente el óptimo global (descartando la a) y se fundamentan fuertemente en procesos estocásticos o probabilísticos (descartando la d). Su mayor ventaja competitiva reside en aprovechar el comportamiento emergente y los mecanismos de selección natural para rastrear grandes espacios de búsqueda. Esto permite a la población evolucionar y descubrir de forma dinámica **soluciones alternativas** y topologías altamente creativas para problemas intratables o de enorme complejidad, allí donde los enfoques analíticos clásicos fracasarían por quedarse atrapados en mínimos locales.