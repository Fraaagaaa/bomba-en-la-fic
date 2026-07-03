# Simbólica

### Grafo de Búsqueda (Preguntas 1 - 3)

![[grafoMayo2026.png|400]]

### 1. Coste de la Solución A*

Dado el siguiente grafo, donde el nodo inicial es A, el valor numérico de cada nodo indica el resultado de evaluar una función heurística $h$, y el valor numérico de cada arista indica el coste de transición entre estados... ¿Cuál sería el coste de la solución devuelta por el algoritmo $A^*$?

- [ ] a) 22
    
- [ ] b) 26
    
- [ ] c) 35
    
- [ ] d) 39
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> - El algoritmo $A^*$ expande los nodos basándose en la función de evaluación $f(n) = g(n) + h(n)$, donde $g(n)$ es el coste acumulado desde el inicio hasta $n$, y $h(n)$ es el valor heurístico estimado hasta la meta.
> - **Inicialización:** Cola de prioridad = `[A(g=0, h=60, f=60)]`
> - **Paso 1:** Se extrae A y se expande:
>   - B: $g(B) = 5, h(B) = 50 \implies f(B) = 55$
>   - C: $g(C) = 6, h(C) = 10 \implies f(C) = 16$
>   - Cola = `[C(f=16), B(f=55)]`
> - **Paso 2:** Se extrae C y se expande:
>   - F: $g(F) = 6 + 5 = 11, h(F) = 5 \implies f(F) = 16$
>   - G: $g(G) = 6 + 10 = 16, h(G) = 1 \implies f(G) = 17$
>   - Cola = `[F(f=16), G(f=17), B(f=55)]`
> - **Paso 3:** Se extrae F y se expande:
>   - G: $g(G) = 11 + 1 = 12, h(G) = 1 \implies f(G) = 13$ (actualiza la entrada anterior de G al ser menor que $17$)
>   - Cola = `[G(f=13), B(f=55)]`
> - **Paso 4:** Se extrae G y se expande:
>   - I: $g(I) = 12 + 23 = 35, h(I) = 0 \implies f(I) = 35$
>   - Cola = `[I(f=35), B(f=55)]`
> - **Paso 5:** Se extrae I (meta). Como tiene el menor valor de la cola y es la meta, la búsqueda finaliza con coste **35**.

### 2. Búsqueda por Profundidad Iterativa

En el mismo grafo de la pregunta anterior, ¿cuál sería la solución de aplicar el algoritmo de búsqueda por profundidad iterativa, usando la precedencia lexicográfica como mecanismo de resolución de conflictos?

- [ ] a) $A \to C \to G \to I$
    
- [ ] b) $A \to B \to E \to H \to I$
    
- [ ] c) $A \to B \to A \to B \to E \to A \to B \to E \to H \to A \to B \to E \to H \to I$
    
- [ ] d) El algoritmo iterativo no encuentra una solución, pero sí lo haría una búsqueda en profundidad estándar
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> La búsqueda por profundidad iterativa (IDDFS) incrementa secuencialmente el límite de profundidad $L$ en cada iteración ($L = 0, 1, 2, 3, \dots$). Los sucesores de cada nodo se exploran en orden lexicográfico (alfabético):
> 
> - **Límite L=0:** Se explora A. No es meta.
> - **Límite L=1:** Se exploran A -> B y A -> C. Ninguno es meta.
> - **Límite L=2:** Se exploran A -> B -> D, A -> B -> E, A -> C -> F, A -> C -> G. Ninguno es meta.
> - **Límite L=3:** 
>   - Rama B: se explora A -> B -> D -> E y A -> B -> D -> H, y también A -> B -> E -> H.
>   - Rama C: se explora A -> C -> F -> G, y finalmente **A -> C -> G -> I**. Al ser I la meta a profundidad 3, se encuentra y se devuelve la solución **$A \to C \to G \to I$**.

### 3. Propiedades de la Heurística

En el mismo grafo, la heurística proporcionada...

- [ ] a) Es admisible y consistente
    
- [ ] b) No es admisible, pero sí consistente
    
- [ ] c) Es admisible, pero no consistente en algunos nodos
    
- [ ] d) No es admisible ni consistente
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> - **Admisibilidad:** Una heurística $h(n)$ es admisible si $h(n) \le h^*(n)$ (el coste real óptimo a la meta) para todo nodo $n$. 
>   - Desde el nodo H, el camino real óptimo a la meta es H -> I con coste $1$. Sin embargo, la heurística asignada es $h(H) = 3$. Como $3 > 1$, la heurística sobreestima el coste, por lo que **no es admisible**.
> - **Consistencia:** Exige que $h(n) \le c(n, a, n') + h(n')$. 
>   - Para la transición D -> H: $h(D) = 60$, $c(D,H) = 1$, $h(H) = 3$. Esto requeriría $60 \le 1 + 3 \implies 60 \le 4$, lo cual es falso. Por tanto, **no es consistente**.

### 4. Modelo de Representación del Conocimiento

Se nos pide realizar un modelo de representación del conocimiento para un sistema sobre un nuevo virus. Al ser de reciente descubrimiento, se dispone de muy poca información sobre este nuevo virus, pero se tiene mucha información sobre otros virus que se cree que funcionan de una manera similar. ¿Qué modelo de representación del conocimiento se debería utilizar?

- [ ] a) Orientación a objetos
    
- [ ] b) Redes semánticas
    
- [ ] c) Reglas de producción
    
- [ ] d) Frames
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> El modelo de **Frames** (Marcos) estructura la información en ranuras (slots) que heredan valores por defecto desde clases más generales (en este caso, otros virus similares). Esto permite que, ante una escasez de datos específicos del nuevo virus, se utilicen por defecto los conocimientos del virus prototípico y se vayan sobrescribiendo los detalles a medida que se descubran.

### 5. Diferencias entre IFANY e IFSOME

¿En qué se diferencian las reglas IFANY y IFSOME?

- [ ] a) IFANY investiga toda la premisa, mientras que IFSOME ejecuta la acción cuando encuentra una cláusula cierta
    
- [ ] b) IFSOME investiga toda la premisa, mientras que IFANY ejecuta la acción cuando encuentra una cláusula cierta
    
- [ ] c) IFANY requiere que una cláusula sea cierta para ejecutar una acción, mientras que IFSOME requiere más de una (al menos 2)
    
- [ ] d) IFSOME requiere que una cláusula sea cierta para ejecutar una acción, mientras que IFANY requiere más de una (al menos 2)
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)** 
> 
> - **Justificación**: En los motores de inferencia, la cláusula **IFANY** funciona como un OR de cortocircuito: evalúa la premisa y ejecuta la acción en cuanto encuentra la primera cláusula que sea cierta. Por el contrario, **IFSOME** investiga toda la premisa de forma exhaustiva para recopilar todas las que se cumplen antes de proceder.

### 6. Arquitecturas Básicas de Agentes

Las arquitecturas básicas de agentes son:

- [ ] a) Reactivo, reactivo con estado, basado en metas y basado en utilidades
    
- [ ] b) Reactivo, basado en metas, basado en metas con estado y basado en utilidades
    
- [ ] c) Activo, reactivo, reactivo con estado y basado en metas
    
- [ ] d) Activo, reactivo, basado en metas con estado y basado en utilidades
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Según la clasificación clásica de Russell & Norvig, los agentes se estructuran en cuatro familias básicas:
> 1. **Reactivos simples** (sin memoria, asocian percepciones a acciones directamente).
> 2. **Reactivos basados en modelos** (mantienen un estado interno del mundo).
> 3. **Basados en objetivos / metas** (actúan para alcanzar metas deseadas).
> 4. **Basados en utilidad** (maximizan una función de preferencia o bienestar).

### 7. Cálculo de la Base Lógica Reducida (BLR)

Sea un dominio con tres manifestaciones posibles $\{M(1), M(2), M(3)\}$ y dos interpretaciones posibles $\{I(1), I(2)\}$. Desde una perspectiva categórica, y dadas las reglas del dominio:

> R1: $M(1) \lor M(2) \lor M(3) \implies I(1) \lor I(2)$
> 
> R2: $I(2) \implies \neg M(2) \land M(1)$
> 
> R3: $I(1) \lor \neg I(2) \implies M(2) \land M(3)$

¿Cuál de las siguientes combinaciones pertenece a la Base Lógica Reducida?

- [ ] a) $m_4 i_1$
    
- [ ] b) $m_4 i_2$
    
- [ ] c) $m_4 i_3$
    
- [ ] d) Ninguna es correcta
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Analizando la manifestación $m_4$, en la tabla dada sus valores son $M(1)=1, M(2)=0, M(3)=0$. Evaluemos cada opción:
> 
> - **Para a) $m_4 i_1$ (donde $I(1)=0, I(2)=0$):** 
>   - R1 establece que si hay manifestaciones activas (las hay porque $M(1)=1$), debe haber al menos una interpretación activa. Al ser ambas 0, **R1 se viola**. No pertenece a la BLR.
> - **Para b) $m_4 i_2$ (donde $I(1)=0, I(2)=1$):**
>   - R1: Antecedente Verdadero, Consecuente Verdadero ($I(2)=1$). (Se cumple)
>   - R2: Antecedente Verdadero ($I(2)=1$). Consecuente: $\neg M(2) \land M(1) = \neg 0 \land 1 = 1$. (Se cumple)
>   - R3: Antecedente: $I(1) \lor \neg I(2) = 0 \lor \neg 1 = 0$ (Falso). Al ser el antecedente falso, la implicación se cumple automáticamente. (Se cumple)
>   - Todas las reglas se satisfacen, por lo que **pertenece a la BLR**.
> - **Para c) $m_4 i_3$ (donde $I(1)=1, I(2)=0$):**
>   - R3: Antecedente: $I(1) \lor \neg I(2) = 1 \lor \neg 0 = 1$ (Verdadero). Consecuente: $M(2) \land M(3) = 0 \land 0 = 0$ (Falso). **R3 se viola** ($1 \implies 0$ es falso). No pertenece a la BLR.

### 8. Inferencia a Partir de Manifestaciones Verdaderas

Con las mismas reglas del ejercicio anterior, y sabiendo que tenemos la manifestación $M(1)$, ¿cuál es el conjunto de interpretaciones más probable? Ten en cuenta las siguientes probabilidades:

> $p(\neg I(1) \land \neg I(2)) = 0.2$
> 
> $p(\neg I(1) \land I(2)) = 0.08$
> 
> $p(I(1) \land \neg I(2)) = 0.34$
> 
> $p(I(1) \land I(2)) = 0.38$

- [ ] a) $I - I(1) \land \neg I(2)$
    
- [ ] b) $\neg I(1) \land I(2)$
    
- [ ] c) $I(1) \land \neg I(2)$
    
- [ ] d) $I(1) \land I(2)$
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Evaluemos la consistencia de las interpretaciones cuando $M(1)=1$:
> 1. $\neg I(1) \land \neg I(2)$ es inconsistente porque al estar activa $M(1)$, R1 obliga a que al menos una interpretación sea verdadera.
> 2. $I(1) \land I(2)$ es inconsistente porque R2 exige que si $I(2)=1 \implies M(2)=0$, mientras que R3 exige que si $I(1)=1 \implies M(2)=1$, provocando una contradicción.
> 3. Las únicas interpretaciones consistentes con $M(1)=1$ son:
>    - $\neg I(1) \land I(2)$ (Probabilidad: 0.08)
>    - $I(1) \land \neg I(2)$ (Probabilidad: 0.34)
> 
> Al comparar las probabilidades de los estados consistentes, la más probable es **$I(1) \land \neg I(2)$** con $0.34$.

### 9. Tamaño del Espacio de Estados en Planificación

En un problema de planificación clásica con $N$ variables booleanas, el tamaño máximo del espacio de estados:

- [ ] a) Crece de forma lineal ($2N$), ya que cada variable añade un nuevo estado posible
    
- [ ] b) Crece de forma cuadrática ($N^2$), debido a las relaciones entre precondiciones y efectos
    
- [ ] c) Crece de forma exponencial ($2^N$), porque cada variable puede tomar dos valores posibles
    
- [ ] d) Permanece constante, ya que el entorno es estático
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> En planificación clásica, si hay $N$ variables booleanas independientes, cada una de ellas puede encontrarse en uno de dos estados posibles ($\{\text{Verdadero}, \text{Falso}\}$). Por tanto, la combinatoria total de combinaciones de estados es $2 \times 2 \times \dots \times 2 = 2^N$.

### 10. Sistemas de Producción y Memoria Activa

Si hablamos de sistemas de producción...

- [ ] a) La base de conocimientos está formada por la base de reglas y el motor de inferencias
    
- [ ] b) Los sistemas dirigidos por los datos son más específicos, porque ejecutarán todas las reglas disponibles en función de la información introducida
    
- [ ] c) La memoria activa almacena todos los cambios de estado de nuestro sistema, de forma que representa siempre nuestro estado actual
    
- [ ] d) El motor de inferencias es el responsable de interactuar con el mundo exterior
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La memoria activa (o memoria de trabajo) almacena dinámicamente los hechos que representan el estado actual de la resolución del problema. Cada vez que una regla de producción se ejecuta, modifica el contenido de esta memoria activa, manteniendo una imagen actualizada del estado del sistema. El motor de inferencias es el software de control (separado de la base de conocimientos), y el mundo exterior se gestiona mediante interfaces.

### 11. Algoritmos de Búsqueda en Árboles

Sobre algoritmos de búsqueda en árboles:

- [ ] a) La búsqueda en anchura siempre es óptima y completa
    
- [ ] b) El profundizamiento iterativo en profundidad debería usarse en espacios de estado en los que se conoce la profundidad de la solución
    
- [ ] c) La búsqueda en profundidad es óptima, pero no completa
    
- [ ] d) Ninguna es correcta
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> - **La a) es falsa:** La búsqueda en anchura (BFS) solo es óptima si los costes de todas las aristas son idénticos o no-decrecientes con la profundidad.
> - **La b) es falsa:** Si se conoce la profundidad exacta de la solución, lo óptimo es usar búsqueda en profundidad limitada. IDDFS se emplea cuando la profundidad es desconocida.
> - **La c) es falsa:** La búsqueda en profundidad (DFS) puede caer en ramas infinitas (no es completa) y no garantiza encontrar la solución más barata (no es óptima).

### 12. Asunciones del Modelo Bayesiano

El modelo bayesiano...

- [ ] a) Hace una suposición de independencia para las manifestaciones e interpretaciones
    
- [ ] b) No asume relaciones causales
    
- [ ] c) La evidencia a favor de una hipótesis no cuenta en la negación de esta hipótesis
    
- [ ] d) Ninguna es correcta
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> - Por qué la **a** es falsa: El temario define textualmente que _"En la probabilidad condicional aparecen involucrados dos sucesos, en donde_ **la ocurrencia del segundo depende de la ocurrencia del primero**". El modelo bayesiano se basa precisamente en la **dependencia** probabilística entre una manifestación (evidencia) y una interpretación (hipótesis). Si asumiera que manifestaciones e interpretaciones son variables independientes, el modelo no podría actualizar la creencia ante nueva evidencia, invalidando la fórmula central de Bayes mostrada en el temario.
> - Por qué la **b** es falsa: La teoría establece literalmente que _"La probabilidad condicional se parece a la total, pero puede ser definida como la_ **probabilidad de las causas**". Además, al avanzar hacia las Redes Bayesianas como solución estructurada del mismo modelo, el temario confirma que sus capacidades fundamentales son _"_**Inferir causas** _a partir de síntomas"_ y _"_**Predecir efectos de una causa**". Por lo tanto, el modelo bayesiano sí asume y modela relaciones de causalidad.
> - Por qué la **c** es falsa: La diapositiva 35 del Tema 4, titulada expresamente _"Secuencialidad y_ **consistencia matemática**", formula las siguientes sentencias matemáticas:
>    - $P(A)+P(¬A)=1$
>   - $P(H∣o_1​∧o_2​∧o_3​)=x$
>   - $P(¬H∣o_1​∧o_2​∧o_3​)=1−x$
> Esta demostración del temario prueba que cualquier conjunto de evidencias ($o_1​∧o_2​∧o_3​$) que otorgue un valor probabilístico x a favor de una hipótesis ($H$), automáticamente y por definición, afecta e impacta a la negación de dicha hipótesis ($¬H$), restándole exactamente ese mismo valor ($1−x$).

### 13. Planificación en Entornos Complejos

Si un entorno es parcialmente observable y estocástico, la planificación clásica:

- [ ] a) Sigue siendo válida sin cambios, porque los algoritmos de búsqueda no dependen de la observabilidad
    
- [ ] b) No es directamente aplicable porque requiere observabilidad total y acciones deterministas
    
- [ ] c) Reduce el espacio de estados al no conocerse toda la información del entorno
    
- [ ] d) Requiere usar exclusivamente búsqueda voraz para estimar estados posibles
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> La planificación clásica (STRIPS / PDDL) opera bajo la hipótesis del mundo cerrado, asumiendo un entorno estático, totalmente observable y acciones con efectos deterministas. Si estas propiedades fallan (entorno estocástico y parcialmente observable), los planes lineales clásicos fallarán y se requerirán modelos como MDPs o POMDPs.

### 14. Componentes de los Sistemas de Producción

*(Nota: Pregunta idéntica a la 10)*

Si hablamos de sistemas de producción...

- [ ] a) La base de conocimientos está formada por la base de reglas y el motor de inferencias
    
- [ ] b) Los sistemas dirigidos por los datos son más específicos, porque ejecutarán todas las reglas disponibles en función de la información introducida
    
- [ ] c) La memoria activa almacena todos los cambios de estado de nuestro sistema, de forma que representa siempre nuestro estado actual
    
- [ ] d) El motor de inferencias es el responsable de interactuar con el mundo exterior
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La memoria activa (o de trabajo) guarda dinámicamente el estado actual del problema actualizándose tras cada disparo de regla.

### 15. Parámetros de Eficiencia en Búsqueda

La eficiencia de un algoritmo de búsqueda depende de dos parámetros, independientemente del dominio de aplicación:

- [ ] a) Profundidad y criterios de selección de estados
    
- [ ] b) Factor de ramificación y costo de expansión
    
- [ ] c) Factor de ramificación y profundidad
    
- [ ] d) El costo de expansión de los nodos y el tipo de representación de conocimiento usado
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La complejidad (temporal y espacial) de los algoritmos de búsqueda en árboles y grafos depende fundamentalmente del **factor de ramificación ($b$)** del árbol de búsqueda y de la **profundidad de la solución ($d$)**.

### 16. Explicabilidad en Redes Bayesianas

¿Por qué una red bayesiana es más explicable que un modelo bayesiano directo sobre datos?

- [ ] a) Porque las aristas del grafo representan dependencias entre variables, haciendo el razonamiento interpretable
    
- [ ] b) Porque transforma las probabilidades en reglas lógicas deterministas, eliminando la incertidumbre
    
- [ ] c) Porque los nodos representan únicamente todos los conceptos relevantes, facilitando la comprensión
    
- [ ] d) Porque solo admite variables booleanas y no variables continuas, eliminando la incertidumbre
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> En una Red Bayesiana, la topología del grafo acíclico dirigido (DAG) representa explícitamente las relaciones de dependencia condicional (e idealmente causales) entre las variables aleatorias. Esto permite al usuario comprender visualmente cómo fluye e influye la probabilidad a través del modelo.

# Subsimbólica

### 1. Diferencias entre las dos ramas clásicas de la Inteligencia Artificial

¿En qué se diferencian las dos ramas clásicas de la Inteligencia Artificial?

- [ ] a) La rama subsimbólica tiene menos capacidades
    
- [ ] b) Una tiene los sistemas expertos y la otra a las redes de neuronas artificiales como paradigmas
    
- [ ] c) Una se basa en la estimulación y la otra en la recursividad
    
- [ ] d) Ninguna de las anteriores es correcta
    
- [ ] e) Todas son correctas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> La Inteligencia Artificial se divide históricamente en dos grandes corrientes complementarias. La rama Simbólica se fundamenta en modelos que contienen conocimiento explícito (como reglas, hechos y ontologías), siendo su mayor exponente los Sistemas Expertos (ej. MYCIN). Por el contrario, la rama Subsimbólica o Conexionista se basa en la emulación biológica, extrayendo conocimiento implícito aprendido automáticamente a partir de los datos, siendo las Redes de Neuronas Artificiales su paradigma central.

### 2. Autores y trabajos sobre cibernética

¿Qué autores con sus trabajos sobre cibernética sientan las bases de la IA?

- [ ] a) Rosenblueth, Wiener y Bigelow.
    
- [ ] b) Cajal.
    
- [ ] c) Craik.
    
- [ ] d) Todos los anteriores.
    
- [ ] e) A y C son ciertas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> El nacimiento de la Inteligencia Artificial y los sistemas conexionistas es multidisciplinar. Las bases cibernéticas fundamentales se establecieron en la década de 1940 gracias a trabajos como la "propuesta cibernética sobre las máquinas teleológicas" desarrollada por Norbert Wiener (junto a Arturo Rosenblueth y Julian Bigelow en su publicación *Behavior, Purpose and Teleology*), así como la capacidad de los sistemas para utilizar modelos lógicos propuesta por Kenneth Craik (*The Nature of Explanation*).

### 3. Precursores biológicos

En la evolución histórica de los sistemas conexionistas, ¿cuáles son precursores biológicos?

- [ ] a) Minsky.
    
- [ ] b) McCulloch.
    
- [ ] c) Papert.
    
- [ ] d) Todos los anteriores.
    
- [ ] e) Ninguno de los anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Los precursores biológicos sentaron las bases orgánicas que luego se trasladarían a las matemáticas. Santiago Ramón y Cajal describió la estructura de la neurona, Donald Hebb postuló el aprendizaje sináptico, y fue el investigador Warren McCulloch (junto a Walter Pitts) quien logró trasladar esa biología a un modelo lógico-matemático fundacional en 1943, convirtiéndose en un precursor biológico innegable de las redes neuronales. Minsky y Papert, por el contrario, fueron críticos posteriores que frenaron el avance del perceptrón.

### 4. Sistemas Inteligentes Subsimbólicos

Causas del interés actual por los Sistemas Inteligentes Subsimbólicos

- [ ] a) El interés existente por la búsqueda de arquitecturas de computadoras que permitan el procesamiento en paralelo.
    
- [ ] b) La habilidad de estos sistemas para aprender automáticamente.
    
- [ ] c) La habilidad para poder funcionar de forma aceptable tanto en presencia de información inexacta como cuando se producen deterioros o fallos en sus componentes.
    
- [ ] d) Su similitud con los modelos neurofisiológicos del cerebro, pudiéndose de este modo intercambiar modelos e investigaciones entre los de RNA y Neurociencias, potenciándose ambas.
    
- [ ] e) Todas las anteriores son correctas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Los sistemas conexionistas (redes neuronales) han experimentado un inmenso resurgir ("tercera primavera de la IA") debido a cuatro factores técnicos decisivos: su habilidad intrínseca para aprender automáticamente a partir de datos (sin ser programados explícitamente), su notable tolerancia y robustez para funcionar frente a fallos de componentes o información inexacta (ruido), su capacidad para ser implementados en arquitecturas de hardware masivamente en paralelo, y su similitud con modelos neurofisiológicos que permiten intercambiar avances con las neurociencias.

### 5. Avances tecnológicos

¿Cuál de los siguientes avances tecnológicos no está relacionado con la IA?

- [ ] a) Impresoras 3D y fabricación aditiva.
    
- [ ] b) Realidades extendidas y "gemelos digitales"
    
- [ ] c) Tecnologías convergentes "NBIC".
    
- [ ] d) Todas las anteriores están relacionadas.
    
- [ ] e) Ninguna de las anteriores está relacionada.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Si observamos las tendencias tecnológicas que definirán la próxima década y que orbitan o están potenciadas directa o indirectamente por el núcleo de la Inteligencia Artificial, encontramos a las realidades virtuales extendidas (Metaverso y Gemelos Digitales), la impresión 3D/4D de fabricación aditiva masiva, y las nanotecnologías combinadas o tecnologías NBIC (Nanotecnología, Biotecnología, Tecnologías de la Información y Ciencias Cognitivas). Todas ellas están estrechamente interconectadas con los avances de la IA.

### 6. Mapas Autoorganizativos (SOM)

Los Mapas Autoorganizativos (SOM) vistos en clase tienen...

- [ ] a) Una única capa que es de entrada
    
- [ ] b) Una única capa recurrente
    
- [ ] c) Una capa de entrada y una capa de salida
    
- [ ] d) Dúas capas de neuronas recurrentes y autoorganizables
    
- [ ] e) Todas las anteriores son incorrectas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Esta es una pregunta teórica con "truco" semántico recurrente en estos exámenes. Aunque a simple vista un esquema SOM dibuja neuronas de entrada y neuronas de salida, la respuesta oficial validada por la UDC es "Todas las anteriores son incorrectas" (opción E). A nivel estrictamente computacional, la red SOM solo posee **1 única capa** de células que procesan y realizan cálculos de pesos (la capa competitiva topológica). La supuesta "capa de entrada" actúa únicamente como un bus pasivo o *buffer* que transfiere las señales hacia adelante, por lo que llamarla arquitectura "de dos capas (entrada y salida)" se considera un error teórico bajo el conexionismo estricto de Kohonen.

### 7. Ideas centrales de Kohonen

Las 2 ideas centrales en las que se basa Kohonen para desarrollar los SOM son...

- [ ] a) La ubicación espacial de las neuronas y su crecimiento dinámico
    
- [ ] b) La autoorganización y el concepto de simetría
    
- [ ] c) La autoorganización y el crecimiento dinámico del nº de neuronas
    
- [ ] d) El proceso de adaptación de pesos y el concepto de geometría topológica de elementos de proceso
    
- [ ] e) Todas las anteriores son incorrectas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> El fundamento primordial del mapa de Teuvo Kohonen radica en combinar el aprendizaje competitivo (donde las neuronas luchan y adaptan sus pesos para parecerse al vector de entrada) con una rigurosa restricción de vecindad espacial. Esto significa que la red mapea características abstrayendo una **geometría topológica**, logrando que neuronas físicamente cercanas en el mapa respondan a estímulos similares.

### 8. Patrones de entrada en SOM

Si los patrones de entrada de un problema tienen 4 características o atributos, una SOM que lo resuelva tendrá...

- [ ] a) 24 neuronas de entrada
    
- [ ] b) 8 neuronas de entrada
    
- [ ] c) 4 neuronas de entrada
    
- [ ] d) 16 neuronas de entrada
    
- [ ] e) Ninguna de las anteriores
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> En una red neuronal de este tipo, la interfaz receptora (las neuronas de entrada) debe acoplarse exactamente a la dimensionalidad matemática de los datos a tratar. Si el patrón cuenta con 4 atributos independientes, es obligatorio disponer de exactamente 4 terminales (o neuronas) en la entrada para recibir cada uno de esos parámetros de forma paralela.

### 9. Aprendizaje no supervisado

En el aprendizaje no supervisado...

- [ ] a) Se desconocen las clases, pero se consiguen grupos similares
    
- [ ] b) La autoorganización de la red permite hallar directamente las clases
    
- [ ] c) Se trabaja con patrones etiquetados
    
- [ ] d) La B y la C son correctas
    
- [ ] e) Ninguna de las anteriores es correcta
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> El paradigma de aprendizaje no supervisado se caracteriza por operar a ciegas en cuanto a objetivos: carece de etiquetas externas, clases predefinidas o un tutor que dicte el resultado deseado. La misión algorítmica de la red es autoorganizarse analizando directamente los datos y descubriendo estructuras ocultas, lo que le permite agrupar los patrones (clustering) basándose exclusivamente en su similitud o distancia matemática.

### 10. El ADALINE

El ADALINE fue creado

- [ ] a) Después del perceptrón
    
- [ ] b) No llegó a ser creado
    
- [ ] c) Antes del perceptrón
    
- [ ] d) La B y la C son correctas
    
- [ ] e) Ninguna de las anteriores es correcta
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Desde una perspectiva cronológica, el Perceptrón simple fue presentado por Frank Rosenblatt en 1958. Muy poco después, entre los años 1959 y 1960, los investigadores Bernard Widrow y Marcian Hoff desarrollaron el modelo ADALINE (ADAptive LInear NEuron), que utilizaba una regla de corrección de error más refinada (Regla Delta).

### 11. Conjunto de entrenamiento

El conjunto de datos que se utiliza para calcular los valores de los pesos de las conexiones de una RNA se denomina:

- [ ] a) Conjunto de prueba
    
- [ ] b) Conjunto de validación
    
- [ ] c) Conjunto de test
    
- [ ] d) Conjunto de entrenamiento
    
- [ ] e) Conjunto de normalización
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> En el particionado de datos, el "conjunto de entrenamiento" (Training set) es el volumen masivo de datos que fluye operativamente por el algoritmo de aprendizaje (como el backpropagation). Es el único conjunto matemático que interviene directamente en la actualización iterativa e interna del valor de los pesos sinápticos de las conexiones de la red.

### 12. Entrenamiento de un perceptrón multicapa

Durante el entrenamiento de un perceptrón multicapa se busca...

- [ ] a) Llegar al error cero siempre.
    
- [ ] b) Estar muy cerca de un mínimo error, pero nunca en él.
    
- [ ] c) Conseguir un mínimo local siempre.
    
- [ ] d) Estar lejos de un mínimo global.
    
- [ ] e) Todas son incorrectas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> El objetivo del entrenamiento de una Red Neuronal Artificial no es lograr un error matemáticamente igual a cero, ya que esto implicaría un "sobreentrenamiento" (memorización de los datos y del ruido), perdiendo la capacidad de generalizar frente a nuevos patrones,,. Tampoco se busca "estar lejos de un mínimo global" ni "conseguir un mínimo local siempre" (al contrario, quedarse atascado en un mínimo local es un problema que algoritmos como el descenso del gradiente con momento intentan evitar),. Por tanto, al no haber ninguna afirmación cierta, la opción E es la correcta.

### 13. Limitaciones del perceptrón

Un perceptrón (sin capas ocultas) no puede implementar una puerta lógica con la función

- [ ] a) AND
    
- [ ] b) OR
    
- [ ] c) EXOR
    
- [ ] d) NOT
    
- [ ] e) Puede hacer cualquiera de las anteriores
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Minsky y Papert demostraron en 1969 las limitaciones matemáticas del perceptrón simple o monocapa: es incapaz de resolver problemas cuyas clases no sean linealmente separables mediante un hiperplano o línea recta. La función lógica EXOR (XOR u OR exclusivo) es el ejemplo clásico de un problema no linealmente separable, por lo que un perceptrón sin capas ocultas jamás podrá implementarla,.

### 14. Neuronas de entrada de un perceptrón

El número de neuronas de entrada de un perceptrón multicapa

- [ ] a) Lo puede fijar el usuario como quiera
    
- [ ] b) Depende del problema a resolver
    
- [ ] c) Debe ser igual al número de neuronas de salida
    
- [ ] d) Debe ser igual al número de neuronas ocultas
    
- [ ] e) Debe ser distinto al número de neuronas de salida
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> En cualquier red neuronal, la interfaz receptora (la capa de entrada) debe acoplarse estrictamente a la dimensionalidad de los datos que se van a tratar,. Si los patrones de entrada cuentan con N características o atributos independientes, la arquitectura exige obligatoriamente tener exactamente N neuronas en la capa de entrada. Por tanto, no se fija aleatoriamente, sino que depende de las variables del problema.

### 15. Función de transferencia

La función de transferencia de las neuronas de un perceptrón multicapa

- [ ] a) Son solamente lineales
    
- [ ] b) Son solamente umbrales
    
- [ ] c) Son solamente de tipo sigmoidal
    
- [ ] d) Son solamente de tipo logarítmico
    
- [ ] e) Todas son falsas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Para que un perceptrón multicapa adquiera su propiedad de "aproximador universal" y pueda resolver problemas no lineales, sus capas ocultas deben utilizar funciones de transferencia o activación no lineales (como las de tipo sigmoidal o tangente hiperbólica),. Sin embargo, restringir la respuesta a que son solamente lineales, umbrales, sigmoidales o logarítmicas (opciones A, B, C y D) es falso, ya que una misma red puede combinar distintas funciones (por ejemplo, sigmoidal en las capas ocultas y lineal en la de salida para problemas de regresión),.

### 16. La Regla Delta

La Regla Delta...

- [ ] a) Es un algoritmo de aprendizaje no supervisado
    
- [ ] b) Maximiza el error cuadrático medio
    
- [ ] c) Es un algoritmo de aprendizaje supervisado
    
- [ ] d) Fija los valores de los pesos y bias
    
- [ ] e) La C y D son correctas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> La Regla Delta es el fundamento del entrenamiento en redes como el ADALINE. Se trata de un algoritmo de aprendizaje supervisado (opción C), ya que opera calculando la diferencia (error) entre la salida obtenida y una salida deseada o "supervisada", modificando los pesos en sentido opuesto a la pendiente del error para minimizarlo,. Además, su función algorítmica es "fijar" o establecer iterativamente los valores de los pesos y el bias (opción D) hasta alcanzar el ajuste óptimo. Al ser ciertas la C y la D, la opción E es la correcta.

### 17. Conocimiento de la red

En un perceptrón multicapa el conocimiento de la red está en ...

- [ ] a) Los datos de salida de las neuronas
    
- [ ] b) En las funciones de transferencia
    
- [ ] c) En los datos de entrada
    
- [ ] d) En las conexiones
    
- [ ] e) Todas son incorrectas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> A diferencia de la IA simbólica clásica que almacena el conocimiento en forma de reglas o sentencias lógicas explícitas, el paradigma conexionista distribuye todo el aprendizaje de forma subsimbólica. El conocimiento y la memoria de una Red Neuronal Artificial residen única y exclusivamente en las intensidades numéricas de sus conexiones sinápticas, es decir, en los pesos de las conexiones,.

### 18. Arquitectura de RNA

Para decidir cuál arquitectura de RNA funciona mejor para un dataset, es necesario mirar el error

- [ ] a) De entrenamiento
    
- [ ] b) De validación
    
- [ ] c) De test
    
- [ ] d) En el ciclo de entrenamiento con menor gradiente
    
- [ ] e) Todas las anteriores son incorrectas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> A la hora de comparar distintas topologías y evitar sesgos de sobreentrenamiento, el error de entrenamiento no es fiable porque la red podría estar simplemente memorizando. El conjunto verdaderamente útil para tomar decisiones sobre los hiperparámetros y determinar qué arquitectura generaliza mejor los datos es el conjunto de validación, el cual actúa como un árbitro externo durante la fase de diseño,,.

### 19. Parada temprana

En la técnica de parada temprana, una vez finalizado el proceso de entrenamiento, la RNA que se devuelve tiene unos pesos que son

- [ ] a) siempre los del último ciclo de entrenamiento realizado.
    
- [ ] b) siempre correspondientes al ciclo con menor error de entrenamiento.
    
- [ ] c) correspondientes al ciclo con menor error de validación.
    
- [ ] d) correspondientes al ciclo con menor error de test.
    
- [ ] e) correspondientes al ciclo con menor gradiente.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La parada temprana (Early Stopping) es un método de regularización. Monitoriza el error en el conjunto de validación a lo largo de las épocas; la orden algorítmica consiste en retroceder en el tiempo y "devolver" la red en la época matemática exacta donde el error de validación registró su valor histórico más bajo, ya que es ahí donde se demuestra la mayor capacidad de generalización antes de que comience el sobreentrenamiento,,.

### 20. Conjunto de patrones de test

El conjunto de patrones de test...

- [ ] a) No interviene en nada en el entrenamiento
    
- [ ] b) Dictamina cuando parar de entrenar
    
- [ ] c) Guía todo el proceso de entrenamiento
    
- [ ] d) Es siempre el conjunto con mayor cantidad de patrones del dataset
    
- [ ] e) Todas las anteriores son falsas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Para que la evaluación final del rendimiento de una RNA tenga rigor científico, el conjunto de prueba o "Test Set" debe mantenerse estricta y absolutamente virgen. Esto significa que sus datos jamás cruzan la red durante la fase de optimización de pesos ni interactúan con las métricas de detención temprana, sirviendo en exclusiva para medir la capacidad real de generalización del modelo frente a lo desconocido.

### 21. Capa de competición en SOM

En una red SOM, la capa de competición está compuesta por:

- [ ] a) Neuronas que generan la salida supervisada.
    
- [ ] b) Neuronas conectadas entre sí por enlaces recursivos.
    
- [ ] c) Neuronas que compiten por representar el patrón de entrada.
    
- [ ] d) Neuronas que codifican el error de la red.
    
- [ ] e) Todas son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Las redes de mapas autoorganizativos operan bajo un paradigma de aprendizaje "competitivo". Cuando la red recibe un vector numérico de estímulo, todas las neuronas de la capa de salida realizan un cálculo de distancia y compiten entre sí. Aquella cuyo vector de pesos se asemeje más al patrón de entrada se corona como ganadora (Best Matching Unit), obteniendo el privilegio exclusivo de actualizar sus propios pesos y los de su vecindario físico más próximo.

### 22. Error de cuantización medio

¿Qué mide el error de cuantización medio en una red SOM?

- [ ] a) La distancia media entre los vectores de entrada y sus neuronas ganadoras (BMU).
    
- [ ] b) El número de patrones correctamente clasificados.
    
- [ ] c) El número de neuronas entrenadas.
    
- [ ] d) La diferencia entre la salida deseada y la obtenida.
    
- [ ] e) El grado de vecindad entre neuronas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Al no existir una salida "deseada" (las redes SOM son no supervisadas), herramientas clásicas como el cálculo del Error Cuadrático Medio no son aplicables. Para saber si el mapa se ha adaptado y amoldado correctamente a la nube de datos, se usa el *Error de Cuantización*, una métrica que calcula el promedio de las distancias matemáticas resultantes entre todos los vectores de entrenamiento y sus respectivas unidades ganadoras (BMU).

### 23. Neurona ganadora en SOM

En una red SOM, la neurona ganadora es aquella que:

- [ ] a) Tiene el peso con mayor valor.
    
- [ ] b) Tiene la mayor activación en la capa de entrada.
    
- [ ] c) Es más cercana al patrón de entrada según una medida de distancia.
    
- [ ] d) Ha sido activada más veces durante el entrenamiento.
    
- [ ] e) Tiene mayor número de conexiones sinápticas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La neurona ganadora o BMU no se elige por mayor nivel de activación absoluto o preselección histórica. La selección se realiza estrictamente en cada ciclo de la red computando y evaluando cuál de todas las celdas tiene el vector de pesos que se encuentra a menor distancia del vector de entrada proporcionado, revelando así la similitud.

### 24. Función de similitud en SOM

¿Qué función se utiliza habitualmente para determinar la similitud entre una neurona y un patrón de entrada en una SOM?

- [ ] a) Distancia de Manhattan
    
- [ ] b) Producto escalar
    
- [ ] c) Distancia Euclídea
    
- [ ] d) Entropía cruzada
    
- [ ] e) Función sigmoidal
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> En los modelos SOM canónicos, la fórmula de similitud matemática principal que permite medir la dispersión entre las dimensiones del peso de una neurona y las del vector ambiental es la métrica de distancia euclídea ordinaria.

### 25. Problemas comunes de las redes SOM

¿Cuál de los siguientes es un problema común de las redes SOM?

- [ ] a) No permiten reducción de dimensionalidad.
    
- [ ] b) Siempre requieren entrenamiento supervisado.
    
- [ ] c) Algunas neuronas pueden no ser entrenadas si están alejadas del espacio de entrada.
    
- [ ] d) No pueden representar relaciones topológicas.
    
- [ ] e) No necesitan inicialización de pesos.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Debido a que el SOM tiene una topología geométrica predefinida y rígida (una cuadrícula fija), si algunos nodos del mapa se inicializan de forma aleatoria en coordenadas muy remotas de donde realmente se halla la concentración de datos de entrada, y la función de vecindario se reduce rápidamente, estas neuronas podrían no llegar a ganar jamás frente a ningún estímulo. Estas "neuronas muertas" son un defecto arquitectónico de los SOM, problema que más adelante fue solventado en redes dinámicas de crecimiento libre como las GNG.

### 26. Tamaño del vecindario en SOM

En una red SOM, ¿qué ocurre con el tamaño del vecindario a lo largo del entrenamiento?

- [ ] a) Permanece constante.
    
- [ ] b) Aumenta progresivamente.
    
- [ ] c) Disminuye con el tiempo.
    
- [ ] d) Se elimina tras la fase de aprendizaje.
    
- [ ] e) Se calcula de forma aleatoria.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> El aprendizaje en mapas de Kohonen se divide en dos fases bien diferenciadas que permiten la estabilidad. Primero, una "fase de ordenación", donde el vecindario es extremadamente amplio para forzar una macro-organización topológica gruesa de toda la red. Posteriormente, se transita a la "fase de convergencia", durante la cual tanto la tasa de aprendizaje como el radio topológico de vecindad disminuyen de forma asintótica y progresiva para efectuar el ajuste y estabilización fina de los centroides.

### 27. Fase de operación de una red SOM

En la fase de operación de una red SOM:

- [ ] a) Se modifican los pesos de las neuronas.
    
- [ ] b) Se entrena la red con nuevos datos.
    
- [ ] c) Se categoriza un patrón según la neurona más similar.
    
- [ ] d) Se actualiza la topología de la red.
    
- [ ] e) Ninguna de las anteriores es correcta.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> El ciclo de vida de un SOM consta de la fase de aprendizaje (donde los pesos son fluidos) y el "modo de operación" (fase productiva). Una vez alcanzado este último, la estructura del modelo se congela de manera inmutable; los pesos ya no se alteran y el sistema solo se utiliza para recibir vectores y proyectarlos o abstraerlos hacia la neurona que resulte más cercana (clasificación o mapeo pasivo).

### 28. Vector de pesos de una neurona

¿Qué representa el vector de pesos de una neurona en la capa de competición de una SOM?

- [ ] a) La tasa de aprendizaje local.
    
- [ ] b) El error de representación de dicha neurona.
    
- [ ] c) El patrón de entrada más común que ha activado esa neurona.
    
- [ ] d) Un prototipo o centroide que representa un grupo de patrones.
    
- [ ] e) El número de veces que ha sido ganadora.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> El aprendizaje competitivo empuja orgánicamente a cada vector de pesos de la capa competitiva a moverse hacia las densidades del conjunto de datos. Como resultado final de la autoorganización, cada neurona actúa fenomenológicamente como un "prototipo" o centroide matemático que representa eficientemente a todo un grupo (clúster) de patrones que comparten características próximas en el entorno real.

### 29. Tareas adecuadas para una red SOM

¿Cuál de las siguientes tareas es especialmente adecuada para una red SOM?

- [ ] a) Predicción de valores numéricos.
    
- [ ] b) Agrupamiento y visualización de datos de alta dimensión.
    
- [ ] c) Traducción automática de lenguas.
    
- [ ] d) Detección de anomalías supervisada.
    
- [ ] e) Reconocimiento de voz con salida categórica.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Las redes de mapas autoorganizativos son herramientas conexionistas inigualables en técnicas de *clustering* no supervisado y de extracción de conocimiento. Su ventaja crítica radica en mapear conjuntos de datos enrevesados formados por alta dimensionalidad para "aplastarlos" visualmente sobre una malla bi o tridimensional discreta y fácilmente interpretable por humanos, salvaguardando las relaciones espaciales y lógicas originales.

### 30. Diferencia de GCS frente a SOM

¿Qué diferencia clave tienen los modelos GCS frente a SOM?

- [ ] a) No utilizan aprendizaje no supervisado.
    
- [ ] b) Ajustan dinámicamente la arquitectura durante el entrenamiento.
    
- [ ] c) No permiten visualización de datos.
    
- [ ] d) Solo funcionan con entradas binarias.
    
- [ ] e) No usan distancia euclídea para calcular similitud.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Las redes SOM (Mapas de Kohonen) clásicas poseen una topología y un número de neuronas fijo y rígido predefinido desde antes de comenzar a entrenar (por ejemplo, una malla de 10x10). La gran innovación de la arquitectura GCS (Growing Cell Structures) es su naturaleza constructiva y evolutiva: añaden y eliminan neuronas de forma dinámica durante el propio entrenamiento para adaptarse orgánicamente a las regiones con mayor error o densidad de datos,,,.

### 31. El término Fitness

El término "Fitness" en un Algoritmo Genético se refiere a...

- [ ] a) Una forma de intercambiar material genético entre varios individuos de la población.
    
- [ ] b) Una forma o función para construir individuos y obtener la población inicial.
    
- [ ] c) Una operación genética que cambia la composición de los descendientes.
    
- [ ] d) El valor que permite evaluar lo bien adaptado que está cada individuo de la población para obtener la solución al problema que se pretende resolver.
    
- [ ] e) Una estrategia que consiste en mantener al mejor individuo y copiarlo directamente a la siguiente generación para evitar perder la mejor solución obtenida.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> En la Computación Evolutiva, la función de aptitud o Fitness es el criterio métrico fundamental que dictamina la supervivencia,. Consiste en una fórmula matemática que evalúa a cada individuo (cromosoma) del enjambre y le asigna una puntuación que representa cuán bien resuelve o se adapta a la problemática planteada, determinando sus posibilidades probabilísticas de reproducirse o ser descartado en la fase de selección,.

### 32. Técnicas de mutación

¿Cuál de las siguientes es una técnica de mutación en los Algoritmos Genéticos?

- [ ] a) Uniforme
    
- [ ] b) Máscara
    
- [ ] c) Intercambio
    
- [ ] d) Génesis
    
- [ ] e) Punto flotante
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> En los Algoritmos Genéticos, el operador de mutación es fundamental para la "exploración" del espacio de búsqueda, ya que su objetivo es inyectar variabilidad (ruido estocástico) en la población alterando posiciones aleatorias de los cromosomas. Esta variabilidad es indispensable para evitar la pérdida irreversible de información genética (alelos) y permitir que el algoritmo escape de máximos o mínimos locales, previniendo la convergencia prematura. Dentro de las técnicas estándar utilizadas para aplicar la mutación, se documentan explícitamente las siguientes: mutación de bit, mutación multibit, mutación de gen, mutación multigen, mutación de barajado y la mutación de intercambio. Por lo tanto, el "intercambio" es una técnica tipificada y válida, descartando opciones inventadas o ajenas a este operador como el punto flotante o la máscara.

### 33. Programación Genética

En Programación Genética...

- [ ] a) El cromosoma nunca representa una posible solución para las variables del problema.
    
- [ ] b) Los operadores de cruce y mutación se aplican para invertir la población de cromosomas.
    
- [ ] c) Los individuos se representan mediante árboles, lo cual es una de las principales diferencias con los Algoritmos Genéticos.
    
- [ ] d) La forma de codificar los individuos es la misma que en los Algoritmos Genéticos; solo cambia la forma de aplicar el cruce y la mutación.
    
- [ ] e) No existe ninguna técnica en Computación Evolutiva denominada Programación Genética.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La Programación Genética (desarrollada por John Koza) comparte el mismo motor evolutivo y principio de selección natural que los Algoritmos Genéticos. Sin embargo, la mayor diferencia arquitectónica entre ambas disciplinas es la forma en la que se codifica la solución al problema. Mientras que en los Algoritmos Genéticos las posibles soluciones o individuos se estructuran mediante vectores planos (como cadenas de bits, caracteres o números reales), en la Programación Genética la codificación se realiza computacionalmente en forma de árbol sintáctico. Para elaborar más sobre esto, en estas representaciones arbóreas, la estructura imita cómo los compiladores leen los programas informáticos. El genotipo se divide en dos tipos de componentes: los nodos internos (no terminales), que albergan forzosamente a los operadores lógicos o aritméticos (como +, -, AND, OR, IF), y las hojas (nodos terminales), que se ubican en los extremos y corresponden a los valores primitivos o variables de entrada y constantes del problema. Por consiguiente, la representación mediante árboles es el rasgo definitorio y diferencial de la Programación Genética.

### 34. Problemas para Algoritmos Genéticos

¿Cuál de los siguientes problemas es más adecuado para ser resuelto mediante un Algoritmo Genético?

- [ ] a) Encontrar el mínimo de una función cuadrática convexa y suave.
    
- [ ] b) Encontrar el óptimo de una función diferenciable de una sola variable.
    
- [ ] c) Enumerar todas las posibles soluciones en un espacio de búsqueda muy pequeño.
    
- [ ] d) Encontrar una ruta para el Problema del Viajante con muchas ciudades.
    
- [ ] e) Encontrar el óptimo global exacto cuando debe garantizarse matemáticamente la mejor solución.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Los Algoritmos Genéticos son metaheurísticas estocásticas de alto coste computacional; su uso se justifica exclusivamente en dominios de altísima complejidad o NP-Hard donde las soluciones directas o analíticas fracasan. El Problema del Viajante de Comercio (TSP) con un volumen masivo de ciudades genera una explosión combinatoria inmanejable para las matemáticas tradicionales, constituyendo el escenario idóneo para utilizar Computación Evolutiva,.

### 35. Elitismo

En un Algoritmo Genético, ¿qué nombre recibe el proceso en el que el mejor individuo de la población se conserva para la siguiente generación?

- [ ] a) Seeding
    
- [ ] b) Elitismo
    
- [ ] c) Aprendizaje lamarckiano
    
- [ ] d) Steady-state
    
- [ ] e) Hill Climbing
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Como se detalló previamente, el proceso que salva intacto al individuo con el fitness supremo, esquivando las fases destructivas de la recombinación para perpetuarlo en la siguiente iteración (generación T+1), recibe académicamente el nombre de estrategia elitista o Elitismo,,.

### 36. Métodos de selección

¿Cuál de los siguientes no es un método de selección utilizado en los Algoritmos Genéticos?

- [ ] a) Torneo
    
- [ ] b) Sobrante estocástico
    
- [ ] c) Universal estocástica
    
- [ ] d) Ruleta
    
- [ ] e) Sobrante determinístico
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Las técnicas algorítmicas canónicas incorporadas en los diseños genéticos se fundamentan en introducir variabilidad estocástica, contando con opciones ampliamente reconocidas como el Torneo, la Ruleta, la selección Universal Estocástica o el Sobrante Estocástico. El concepto de "sobrante determinístico" no forma parte del abanico estándar de operadores de selección en el temario.

### 37. Mecanismos de selección

¿Qué mecanismo de selección tiende a distribuir la búsqueda de forma más amplia en el espacio de estados?

- [ ] a) Selección por ruleta, donde los individuos se asignan a sectores ponderados por su fitness y los sectores con mayor peso tienen mayor probabilidad de no ser seleccionados.
    
- [ ] b) Selección por ruleta, donde todos los individuos tienen exactamente la misma probabilidad de ser seleccionados.
    
- [ ] c) Selección por torneo, donde se elige un subconjunto de individuos de forma aleatoria y se selecciona el individuo con mejor valor de fitness.
    
- [ ] d) Selección por torneo, donde los individuos compiten por parejas y el ganador se selecciona con una probabilidad proporcional a su fitness.
    
- [ ] e) Selección por torneo, donde los individuos se agrupan en subconjuntos y se seleccionan los dos individuos con menor fitness para la reproducción.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La selección por Torneo selecciona un "ring" aleatorio de individuos (un subconjunto del censo total) y hace que compitan, logrando que el de mejor fitness de ese grupo sobreviva. Este método posee una gran ventaja sobre la Ruleta pura, pues su presión selectiva se puede modular controlando el tamaño del subconjunto. Al dar oportunidad a individuos medianos de ganar en sus torneos locales, distribuye y explora el espacio de búsqueda de manera mucho más amplia, evitando la endogamia o convergencia prematura en un mínimo local.

### 38. El cruce en Algoritmos Genéticos

¿Cuál de las siguientes afirmaciones describe mejor el cruce en los Algoritmos Genéticos?

- [ ] a) El cruce selecciona los mejores individuos de la población y elimina los más débiles.
    
- [ ] b) El cruce combina material genético de dos individuos progenitores para crear nuevos descendientes.
    
- [ ] c) El cruce cambia aleatoriamente genes individuales para introducir valores completamente nuevos en la población.
    
- [ ] d) El cruce evalúa la calidad de cada individuo mediante la función de fitness.
    
- [ ] e) El cruce garantiza que los descendientes siempre serán mejores que ambos progenitores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> El Cruce (o Crossover) representa el operador principal de "Explotación" dentro del motor evolutivo. Su objetivo fundamental y excluyente es entrelazar y combinar de manera eficiente el material cromosómico valioso (los "Building Blocks" o bloques de genes exitosos) pertenecientes a dos padres distintos, engendrando hijos fenotípicamente novedosos que hereden las mejores características conjuntas para progresar en la resolución del problema,.

### 39. Vida artificial

¿Cuál de las siguientes simulaciones es un ejemplo clásico de vida artificial?

- [ ] a) El juego del laberinto
    
- [ ] b) El Juego de la Vida de Conway
    
- [ ] c) Hill Climbing
    
- [ ] d) La estrategia elitista
    
- [ ] e) Ninguna de las anteriores
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Dentro de los enfoques experimentales inspirados biológicamente, los autómatas celulares son el máximo exponente matemático de la Vida Artificial (VA). Entre ellos, la obra magna más clásica es el "Juego de la Vida" formulado por el matemático John Conway: una malla bidimensional sin estado central donde "organismos" celulares simples subsisten, se reproducen o perecen guiados por reglas locales estrictas dependientes de sus vecinos.

### 40. Entrelazamiento cuántico

¿Qué afirmación describe mejor el entrelazamiento cuántico?

- [ ] a) Dos qubits comparten un estado vinculado, por lo que medir uno proporciona información sobre el otro.
    
- [ ] b) Dos qubits alternan sus estados en direcciones opuestas hasta que se realiza una medición.
    
- [ ] c) Dos qubits almacenan el mismo valor clásico en dos ubicaciones físicas diferentes.
    
- [ ] d) Un qubit se copia en otro qubit para evitar la pérdida de información.
    
- [ ] e) Un qubit controla a otro enviando información más rápido que la luz.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> En los preceptos incorporados por la computación cuántica al temario (Tema 10), el entrelazamiento cuántico supone un fenómeno fundacional de la mecánica subatómica, mediante el cual dos Qubits quedan íntimamente entrelazados; colapsar o medir el estado analítico de uno de los Qubits define instantáneamente y a cualquier distancia la información de su pareja complementaria.
