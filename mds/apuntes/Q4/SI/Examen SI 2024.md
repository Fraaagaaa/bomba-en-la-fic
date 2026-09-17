# Simbólica

### 1. Pregunta Omitida en el Original

### 2. Búsqueda Avara (Greedy Best-First Search) - Concepto

_(Enunciado reconstruido teóricamente debido a la ausencia del grafo original)_

En un problema que aplica la Búsqueda Avara sobre un grafo, la pregunta final exige calcular la "longitud del camino" de la solución obtenida. ¿Cómo se determina dicha longitud?

- [ ] a) Sumando los valores de la heurística $h(n)$ de los nodos visitados.
    
- [ ] b) Calculando la media entre $g(n)$ y $h(n)$.
    
- [ ] c) Sumando los costes reales $g(n)$ de la ruta obtenida.
    
- [ ] d) Contando simplemente el número de nodos visitados, asumiendo coste 1.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> En un ejercicio genérico de Búsqueda Avara, la respuesta final será la suma de los costes reales $g(n)$ de la ruta obtenida. El algoritmo evalúa los nodos de la frontera expandiendo siempre aquel que parece estar más cerca de la meta guiándose en exclusiva por el menor valor de la función heurística $h(n)$. Para resolver este tipo de preguntas visuales, se debe recorrer el grafo ciegamente hacia el nodo adyacente con menor $h(n)$ (ignorando el coste real $g(n)$ durante la toma de decisiones), pero, al llegar a la meta, se suman los costes de los arcos transitados ($g(n)$) para dar la longitud del camino real.

### 3. Optimalidad del algoritmo A*

Para el mismo grafo del ejercicio anterior: ¿el algoritmo A* obtiene una solución óptima?

- [ ] a) Sí, y es 12.
    
- [ ] b) No, la heurística no es admisible.
    
- [ ] c) No, la heurística no es consistente.
    
- [ ] d) Sí, pero la heurística no es consistente.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: Depende de los valores del grafo original**
> 
> Según la teoría clásica de resolución de problemas, el algoritmo A* ($f(n) = g(n) + h(n)$) garantiza matemáticamente la obtención de una ruta óptima siempre que se cumplan dos condiciones: si operamos sobre un árbol de búsqueda, la heurística debe ser admisible (nunca sobreestimar el coste real); pero al operar sobre un grafo (como especifica el bloque de esta pregunta), la heurística debe ser obligatoriamente **consistente** (o monótona), cumpliendo que la diferencia de las estimaciones heurísticas entre dos nodos no supere el coste real del paso entre ellos: $h(n) \le c(n,a,n') + h(n')$. Si un algoritmo A* sobre un grafo devuelve un camino subóptimo, la justificación teórica es que la heurística no es consistente (apuntando a la opción **c** o **d** según el caso específico).

### 4. Análisis de la Tabla de Exploración (Nodos Cerrados)

A partir de la siguiente tabla de nodos explorados, ¿qué tipo de búsqueda fue utilizada?

**Paso 1:** -

**Paso 2:** A

**Paso 3:** A, B

**Paso 4:** A, B, C

**Paso 5:** A, B, C, D

**Paso 6:** A, B, C, D, E

- [ ] a) Búsqueda de coste uniforme.
    
- [ ] b) Búsqueda en anchura.
    
- [ ] c) A*.
    
- [ ] d) Búsqueda en profundidad.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b) Búsqueda en anchura.**
> 
> Utiliza una cola **FIFO** (el primero que entra en la frontera, es el primero en salir y explorarse). Esto hace que explore el árbol "por capas 
> horizontales: primero el nivel 0, luego todo el nivel 1, luego todo el nivel 2.
>
>- **Paso 1:** `-` _(Frontera: [A])_
>- **Paso 2:** `A` _(Frontera: [B, C])_ -> Explora todo el nivel 0.
>- **Paso 3:** `A, B` _(Frontera: [C, D, E])_ -> Empieza el nivel 1. Saca a B porque entró antes que C.
>- **Paso 4:** `A, B, C` _(Frontera: [D, E, F, G])_ -> Termina el nivel 1.
>- **Paso 5:** `A, B, C, D` _(Frontera: [E, F, G, H, I])_ -> Empieza el nivel 2.
>- **Paso 6:** `A, B, C, D, E` _(Frontera: ...)_
>
>Como ves, **esta traza coincide exactamente al milímetro con la tabla de tu enunciado**. La búsqueda en anchura es la que genera una lista alfabética secuencial perfecta si el árbol está ordenado así.
>
>2. Búsqueda en Profundidad
>
>Utiliza una pila **LIFO** (el último que entra a la frontera, es el primero en salir). Esto obliga al algoritmo a ignorar a los hermanos y sumergirse ciegamente por una rama hasta chocar con el fondo.
>
>- **Paso 1:** `-` _(Frontera: [A])_
>- **Paso 2:** `A` _(Frontera: [B, C])_
>- **Paso 3:** `A, B` _(Frontera: [D, E, C])_ -> Al explorar B, descubre D y E. Al ser LIFO, estos se ponen "encima" de C.
>- **Paso 4:** `A, B, D` _(Frontera: [H, I, E, C])_ -> **¡Aquí se rompe la secuencia!** El algoritmo ignora a C y explora D (el hijo de B) porque está yendo hacia lo profundo.
>- **Paso 5:** `A, B, D, H` _(Frontera: ...)_
>
>En profundidad, jamás verías los explorados `A, B, C, D, E`, porque eso implicaría haber explorado a `B` y a su hermano `C` antes de bajar a los hijos, lo cual viola la regla de ir hacia abajo.
>
>3. Búsqueda de Coste Uniforme y A*
>
>En estos algoritmos, el orden de los nodos explorados no sigue un patrón alfabético ni de capas predecible a simple vista, ya que la frontera **se ordena por números** (por el coste más barato g(n) o por la fórmula f(n)).
>
>- Dependiendo de los costes de las flechas, la tabla de explorados daría saltos ilógicos como: `A`, luego `A, C`, luego `A, C, B`, luego `A, C, B, E`, etc., buscando siempre el camino más barato en cada momento.

### 5. Algoritmos de Búsqueda Local (Hill-Climbing)

En un problema en el que estamos utilizando búsqueda local, tenemos la siguiente función de coste, en la que estamos buscando el valor máximo:

![[funciónHillClimbing2024.png]]

Si estamos en el punto marcado, ¿qué deberíamos de hacer?

- [ ] a) Retroceder a un punto anterior y probar un sentido diferente.
    
- [ ] b) Devolver el punto marcado.
    
- [ ] c) Aplicar más de un operador antes de realizar el test de meta.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
>
>En los algoritmos de Búsqueda Local pura (como la Ascensión de Colinas o _Hill-Climbing_), la máquina **carece de memoria histórica** (opera en el nodo actual con una complejidad espacial constante $O(1)$). Su mecánica es simple: evalúa sus estados vecinos inmediatos y se mueve hacia el que tenga mayor valor.
>
>En la gráfica, el punto marcado es un **Máximo Local**. Al evaluar a sus vecinos, el algoritmo ve que si da un paso a la izquierda, el valor baja; si da un paso a la derecha, el valor también baja. Como _ningún_ vecino mejora su situación actual, la condición de parada algorítmica se dispara de inmediato: la máquina asume que ha llegado a la cima absoluta del problema, **se detiene y devuelve el punto marcado** como su solución final (quedando trágicamente atascada sin encontrar el máximo global que está más a la izquierda).
>
>**Por qué las demás son falsas:**
>
>- **La a) es falsa:** Para poder "retroceder" (_backtracking_), el algoritmo necesitaría tener memoria y guardar el camino que ha recorrido (como hace la Búsqueda en Profundidad). La Búsqueda Local está diseñada específicamente para no guardar caminos, por lo que es físicamente incapaz de retroceder.
 >   
>- **La c) es falsa:** La búsqueda local clásica evalúa iterativamente paso a paso aplicando un solo operador para mirar al vecino inmediato. No puede saltarse la ceguera encadenando operadores de golpe.

### 6. Evaluación de heurísticas y funciones

La búsqueda $A*$...

- [ ] a) Evalúa cada nodo combinando las funciones $g(n)$ y $h(n)$, e.g. el coste real del mejor camino para alcanzar cada nodo $n$ y el coste estimado del camino menos costoso desde el nodo $n$ a meta.
    
- [ ] b) La búsqueda A* basada en grafo es óptima si la heurística es admisible.
    
- [ ] c) Se comporta como búsqueda en profundidad si $g$ es incrementada por 1, $h = 0$, y los nodos con la misma $f$ son ordenados de menos a más recientes.
    
- [ ] d) Todas son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> La opción a) es la definición exacta de la función de evaluación algorítmica de la Búsqueda A* ($f(n) = g(n) + h(n)$). Las demás opciones son falsas por principios teóricos de IA:
> 
> - La opción b) es falsa porque para que A* sea óptima en búsqueda sobre grafos, la heurística no solo debe ser admisible, sino **consistente**.
>     
> - La opción c) es falsa porque si $h=0$ y $g$ se incrementa iterativamente, estamos implementando una estructura equivalente a una cola FIFO, lo cual define una Búsqueda en Anchura o Coste Uniforme, no una búsqueda en profundidad.
>     

### 7. Conceptos sobre heurísticas

Las funciones heurísticas...

- [ ] a) Cuantas más restricciones tengamos en cuenta para su diseño, menos precisas serán.
    
- [ ] b) Son consideradas admisibles si nunca sobreestiman el coste actual de alcanzar la meta.
    
- [ ] c) Si $n$ es el nodo inicial, entonces $h(n) = 0$.
    
- [ ] d) Si una heurística domina otra ($h_2 \ge h_1$), A* usando $h_2$ expandirá más nodos que usando $h_1$.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> La opción b) describe de manera clásica la definición central de una heurística admisible: es de naturaleza optimista y asume que el objetivo está más cerca de lo que realmente está, por lo que **nunca sobreestima** el coste real ($h(n) \le c^*$).
> 
> Las demás opciones contienen errores:
> 
> - La a) es falsa: crear heurísticas mediante el método de "relajación de problemas" implica que cuantas _menos_ restricciones tenga el problema abstracto, menos precisa será la heurística; cuantas más contemple (más realista sea), más informada se volverá.
>     
> - La c) es falsa: la regla estricta es que la función vale 0 en la meta, no en el nodo inicial ($h(meta) = 0$).
>     
> - La d) es falsa: describe erróneamente el concepto de dominación. Si $h_2$ domina a $h_1$ (es decir, $h_2 \ge h_1$ para todo nodo), $h_2$ guiará mejor la búsqueda por estar más informada y, por tanto, expandirá **menos** nodos que $h_1$, no más.
>     

### 8. Estrategias ciegas de búsqueda en árboles

Si hablamos de algoritmos de búsqueda en árbol...

- [ ] a) Búsqueda en amplitud siempre es óptima y completa.
    
- [ ] b) La búsqueda de profundidad iterativa debe de ser usada en espacios de búsqueda donde la profundidad de la solución sea conocida.
    
- [ ] c) La búsqueda de profundidad limitada es óptima, pero no completa.
    
- [ ] d) Ninguna es correcta.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Se descartan todas las afirmaciones clásicas por sus trampas teóricas:
> 
> - La a) es falsa: la Búsqueda en Amplitud solo es óptima si todos los operadores tienen **exactamente el mismo coste** de transición. Si los pasos cuestan distinto, devolverá el camino con menos arcos, pero no el más barato.
>     
> - La b) es falsa: la Búsqueda de Profundidad Iterativa fue diseñada algorítmicamente justo para el escenario opuesto; es útil cuando el espacio de búsqueda es infinito o inmenso y **no se conoce a priori** la profundidad de la solución.
>     
> - La c) es falsa: la Profundidad Limitada jamás garantiza optimalidad y perderá su completitud intrínsecamente si la meta resulta estar más profunda que el límite ($d > l$) preconfigurado por el usuario.
>     

### 9. Selección del Modelo de Representación del Conocimiento

Se nos pide crear un modelo de representación del conocimiento para un sistema sobre un nuevo virus. Al haber sido descubierto recientemente, hay muy poca información disponible sobre este nuevo virus, pero hay mucha información sobre otros virus que se cree que funcionan de manera similar. ¿Qué modelo de representación del conocimiento debería de ser utilizado?

- [ ] a) Orientada a objetos.
    
- [ ] b) Redes semánticas.
    
- [ ] c) Reglas de producción.
    
- [ ] d) Marcos (Frames).
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Los **Marcos** (o _Frames_, desarrollados por Marvin Minsky) son la estructura de representación ideal cuando nos enfrentamos a dominios con información incompleta, ya que su núcleo conceptual es el uso de **valores por defecto** (_default values_). Al enfrentarnos a un virus nuevo del que sabemos poco, pero que pertenece a una categoría conocida ("virus similares"), podemos instanciar un "Marco de Virus" general. El sistema rellenará automáticamente los "huecos" (_slots_) desconocidos del nuevo virus heredando las características típicas (valores por defecto) de la clase padre, permitiéndonos razonar sobre él aunque nuestra información inicial sea escasa.

### 10. Algoritmo de Model Checking (Verificación de Modelos)

El algoritmo de _model checking_...

- [ ] a) Tiene una complejidad que se vuelve inmanejable para sistemas con muchos símbolos.
    
- [ ] b) Permite verificar si $KB \models \alpha$.
    
- [ ] c) Puede ser implementado como una exploración de un árbol binario.
    
- [ ] d) Todas son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> El _Model Checking_ (Comprobación de Modelos) evalúa exhaustivamente todas las interpretaciones (modelos) posibles para dictaminar el entrañamiento lógico. Se cumplen las tres premisas:
> 
> - **a es correcta:** Su complejidad espacial/temporal es $O(2^n)$ donde $n$ es el número de símbolos proposicionales. Para dominios grandes, la explosión combinatoria lo hace computacionalmente intratable.
>     
> - **b es correcta:** Su finalidad fundacional es comprobar algorítmicamente el entrañamiento: si para todos los modelos donde la Base de Conocimiento ($KB$) es cierta, la sentencia $\alpha$ también lo es ($KB \models \alpha$).
>     
> - **c es correcta:** Para enumerar sistemáticamente los modelos, los algoritmos (como TT-Entails) construyen implícitamente un árbol de búsqueda binario de profundidad $n$, donde cada nivel asigna `True` o `False` a un símbolo.
>     

### 11. Modificación del Motor de Inferencias

Hay un sistema de producción en un problema dado. En un punto, el cliente se da cuenta de que la información es incompleta y necesita añadir dos reglas a mayores para cubrir casos específicos que no habían sido considerados previamente. ¿Qué deberíamos de cambiar en el motor de inferencias?

- [ ] a) Las nuevas reglas deben ser insertadas.
    
- [ ] b) Las nuevas reglas y los hechos resultantes de dichas reglas deben ser insertados.
    
- [ ] c) El sistema de reglas tendrá que ser reconstruido completamente para adaptarlo al problema actual.
    
- [ ] d) Nada.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> La esencia arquitectónica de un sistema de producción (y de los Sistemas Basados en Conocimiento en general) radica en la estricta **separación entre el conocimiento y el control**. El Motor de Inferencias es un programa de control genérico (el "intérprete") que no almacena información específica del dominio. Toda nueva heurística o lógica experta (como añadir dos nuevas reglas) se inserta exclusivamente en la **Base de Conocimiento (Base de Reglas)**. Por consiguiente, el código del Motor de Inferencias permanece inalterado.

### 12. Traza de Encadenamiento Progresivo

Dado la siguiente base de reglas:

> R1: `IF (X AND Y) THEN Z`
> 
> R2: `IF (C OR D) THEN G`
> 
> R3: `IF (E AND V) THEN H`
> 
> R4: `IF (A AND B) THEN C`
> 
> R5: `IF (F OR G) THEN X`
> 
> R6: `IF (Z AND B) THEN V`
> 
> R7: `IF (E AND C) THEN F`

Queremos inferir `H` mediante encadenamiento progresivo, y sabiendo que: la primera de las reglas activadas será ejecutada (si R3 y R4 son activadas, se ejecutará primero R3); y en la memoria activa tenemos `A`, `B`, `D` y `Y`. _(Nota: la digitalización indica `?, D y Y`, pero el apunte a mano `ABDY(H)` confirma que la memoria inicial es `{A, B, D, Y}`)._ Entonces:

- [ ] a) H puede ser inferida, y el número de reglas ejecutadas es 4.
    
- [ ] b) H puede ser inferida, y el número de reglas ejecutadas es 5.
    
- [ ] c) H no puede ser inferida, y el número de reglas ejecutadas es 4.
    
- [ ] d) H no puede ser inferida, y el número de reglas ejecutadas es 5.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Traza algorítmica del encadenamiento progresivo partiendo de la Memoria inicial = `{A, B, D, Y}`:
> 
> 1. **Ciclo 1:** > * Reglas emparejadas (Conjunto Conflicto): R2 (condición `D` cumple el `OR`) y R4 (cumple `A AND B`).
>     
>     - Resolución de conflictos: Por orden léxico (se asume de arriba abajo según la pista del enunciado "la primera activada"), se dispara **R2**.
>         
>     - Nuevo hecho: `G`. Memoria actual: `{A, B, D, Y, G}`.
>         
> 2. **Ciclo 2:**
>     
>     - Conjunto Conflicto: R4 y R5 (cumple `G` en el `OR`).
>         
>     - Dispara: **R4**.
>         
>     - Nuevo hecho: `C`. Memoria actual: `{A, B, D, Y, G, C}`.
>         
> 3. **Ciclo 3:**
>     
>     - Conjunto Conflicto: R5 (Nota: R7 requiere `E` que no tenemos).
>         
>     - Dispara: **R5**.
>         
>     - Nuevo hecho: `X`. Memoria actual: `{A, B, D, Y, G, C, X}`.
>         
> 4. **Ciclo 4:**
>     
>     - Conjunto Conflicto: R1 (cumple `X AND Y`).
>         
>     - Dispara: **R1**.
>         
>     - Nuevo hecho: `Z`. Memoria actual: `{A, B, D, Y, G, C, X, Z}`.
>         
> 5. **Ciclo 5:**
>     
>     - Conjunto Conflicto: R6 (cumple `Z AND B`).
>         
>     - Dispara: **R6**.
>         
>     - Nuevo hecho: `V`. Memoria actual: `{A, B, D, Y, G, C, X, Z, V}`.
>         
> 6. **Ciclo 6:**
>     
>     - Llegados a este punto, la regla objetivo es R3, que requiere `E AND V`. Tenemos `V`, pero el hecho `E` no está en la memoria ni existe ninguna regla capaz de inferirlo en todo el sistema. El conjunto conflicto queda vacío.
>         
>     - **Resultado final:** El algoritmo se detiene tras ejecutar **5 reglas** (R2, R4, R5, R1, R6) sin haber logrado inferir la meta `H`.
>

### 14. Función de la Memoria Activa

Si hablamos de sistemas de producción...

- [ ] a) La base de conocimientos está formada por la base de reglas y el motor de inferencias.
    
- [ ] b) Los sistemas dirigidos por los datos son más específicos, porque ejecutarán todas las reglas disponibles en función de la información introducida.
    
- [ ] c) La memoria activa almacena todos los cambios de estado de nuestro sistema, de forma que representa siempre nuestro estado actual.
    
- [ ] d) El motor de inferencias es el responsable de interaccionar con el mundo exterior.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La memoria activa o "pizarra" tiene como objetivo estructural recoger todo el set de condiciones iniciales (hechos base) y memorizar la modificación inmediata producida en la fase de acción del ciclo. Al registrar rigurosamente qué hechos se crean, cambian o borran, provee al sistema en todo momento de la "fotografía" exacta de la realidad con la que emparejar las siguientes reglas.

### 15. Evaluación en Búsqueda A*

La búsqueda A*...

- [ ] a) Evalúa los nodos combinando las funciones $g(n)$ y $h(n)$.
    
- [ ] b) Basada en grafo es óptima si la heurística es admisible.
    
- [ ] c) Se comporta como anchura si $g$ se incrementa en 1, $h=0$ y los nodos con igual $f$ se ordenan de menos a más reciente.
    
- [ ] d) Todas son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> La piedra angular que constituye la búsqueda A* frente a las ciegas y avaras es su ecuación de evaluación unificada $f(n) = g(n) + h(n)$, sumando el pasado certero y el futuro optimista. La opción b) se descarta de lleno porque un A* sobre un "grafo" precisa obligatoriamente heurísticas _consistentes_ para ser óptima; la simple admisibilidad aislada en grafos puede generar errores de ruta.

### 16. Inferencia Híbrida Categórica-Bayesiana

Con las reglas categóricas genéricas del dominio ($R1: M(1) \lor M(2) \lor M(3) \implies I(1) \lor I(2)$, $R2: I(1) \implies \neg M(1) \land M(2)$, y $R3$) y sabiendo que tenemos la **manifestación ineludible $M(1)$**, ¿cuál es el conjunto de interpretaciones más probables? Ten en cuenta las siguientes probabilidades:

- $p(\neg I(1) \land \neg I(2)) = 0.2$
    
- $p(\neg I(1) \land I(2)) = 0.08$
    
- $p(I(1) \land \neg I(2)) = 0.34$
    
- $p(I(1) \land I(2)) = 0.38$
    

- [ ] a) $\neg I(1) \land \neg I(2)$
    
- [ ] b) $\neg I(1) \land I(2)$ 
    
- [ ] c) $I(1) \land \neg I(2)$
    
- [ ] d) $I(1) \land I(2)$
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Es una pregunta trampa en la que la estadística insertada es irrelevante gracias a las restricciones inquebrantables del modelo categórico (Base Lógica Reducida). Si M(1) es estrictamente cierto, sabemos por regla (R2:I(1)⟹¬M(1)∧M(2)) que la interpretación I(1) jamás puede ser cierta, pues nos obligaría a tener ¬M(1), lo cual contradice el enunciado. Por lo tanto, I(1) es forzosamente **falsa**. En el dominio categórico, para manifestaciones presentes, alguna interpretación ha de cumplirse (por R1); descartada la 1, la única que queda activa obligatoriamente es I(2). Esto nos arroja categóricamente a la respuesta ¬I(1)∧I(2) sin necesidad de apoyarse en la probabilidad bayesiana proporcionada.

# Subsimbólica

### 1. Representación del Conocimiento en RNA

En una RNA, el conocimiento está en...

- [ ] a) La función de transferencia.
    
- [ ] b) Los pesos y bias.
    
- [ ] c) Los valores dados por las salidas.
    
- [ ] d) El algoritmo de entrenamiento.
    
- [ ] e) La topología de la red.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> A diferencia de los modelos de Inteligencia Artificial Simbólica (como los sistemas expertos o los árboles de búsqueda), que basan su inferencia en el almacenamiento de reglas o estados de conocimiento explícitos, el paradigma conexionista distribuye todo lo aprendido de forma puramente matemática. En las Redes Neuronales Artificiales (RNA), la huella del aprendizaje —la retención de la generalización del problema— reside intrínseca y exclusivamente en el valor paramétrico de la intensidad de sus conexiones sinápticas (los pesos) y en el de los niveles de activación base de la célula (los bias).

### 2. Conjuntos de Datos en el Aprendizaje

El conjunto de datos utilizado para establecer el valor de los pesos de una RNA es conocido como...

- [ ] a) Conjunto de prueba.
    
- [ ] b) Conjunto de validación.
    
- [ ] c) Conjunto de test.
    
- [ ] d) Conjunto de entrenamiento.
    
- [ ] e) Conjunto de normalización.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Durante el proceso de aprendizaje de una red neuronal, el volumen total de datos empíricos se divide. El "conjunto de entrenamiento" (_Training set_) es el único lote de datos que interactúa de manera directa con el algoritmo (por ejemplo, retropropagación) calculando los gradientes de error para actualizar y asentar matemáticamente las matrices de pesos y bias de la red.

### 3. Descenso del Gradiente

Cuando el gradiente descendente es utilizado para modificar los pesos de las conexiones de una RNA...

- [ ] a) Si está cerca de 0, el mínimo estará lejos y serán necesarios más saltos para encontrarlo.
    
- [ ] b) Si toma un valor alto, se realizará un pequeño salto dentro del espacio de búsqueda para encontrar el mínimo.
    
- [ ] c) Si toma un valor bajo, se realizará un salto grande en el espacio de búsqueda para encontrar el mínimo.
    
- [ ] d) Es necesario modificar los pesos en la dirección del gradiente.
    
- [ ] e) Es necesario modificar los pesos en la dirección contraria del gradiente.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Matemáticamente, el vector gradiente apunta siempre hacia la dirección de mayor o máximo crecimiento de una función (en este caso, la función de error). Dado que el objetivo del aprendizaje es buscar el fondo del valle (el error mínimo), la regla Delta especifica que la actualización o salto de los pesos debe realizarse indefectiblemente restando esa pendiente, es decir, moviéndose en la dirección o sentido opuesto al gradiente.

### 4. Limitaciones del Perceptrón Simple

Un Perceptrón (sin capas ocultas) puede resolver problemas de clasificación con una precisión del 100% cuando las muestras...

- [ ] a) Son clasificadas en sólo dos clases y no están entremezcladas.
    
- [ ] b) Son clasificadas en sólo dos clases y son linealmente separables.
    
- [ ] c) Son clasificadas en sólo dos clases, aunque estén mezcladas, no sean linealmente separables o tengan ruido.
    
- [ ] d) Son clasificadas en sólo dos clases y no tengan ruido.
    
- [ ] e) Son clasificadas en sólo dos clases y sigan una distribución normal.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> El teorema fundamental del Perceptrón simple (Rosenblatt) establece que una red sin capas ocultas solo es capaz de trazar un único hiperplano (una línea recta en 2D) en el espacio de decisión. Por lo tanto, solo puede alcanzar una convergencia total (100% de precisión) si el problema geométrico subyacente es **linealmente separable** (es decir, que una línea recta baste para separar la Clase A de la Clase B).

### 5. El Problema EXOR (XOR)

Para utilizar un perceptrón multicapa para resolver el problema EXOR...

- [ ] a) No es necesario utilizar capas ocultas.
    
- [ ] b) Es necesario utilizar una capa oculta (con el número suficiente de neuronas), y no hacen falta más capas.
    
- [ ] c) Es necesario utilizar dos capas ocultas (con el número suficiente de neuronas), y no hacen falta más capas.
    
- [ ] d) Es necesario utilizar tres capas ocultas (con el número suficiente de neuronas), y no hacen falta más capas.
    
- [ ] e) Es necesario utilizar más de tres capas ocultas (con el número suficiente de neuronas).
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> El problema de la disyunción exclusiva (XOR o EXOR) es el ejemplo clásico de un problema **no linealmente separable**. Un perceptrón simple fracasa al intentar resolverlo porque se requieren al menos dos rectas para aislar las respuestas verdaderas de las falsas en el plano lógico. Al añadir **una única capa oculta** (con al menos dos neuronas ocultas), la red gana la capacidad de combinar dos hiperplanos, resolviendo el problema a la perfección sin requerir arquitecturas más profundas.

### 6. Funciones de Transferencia

La función de transferencia de las neuronas artificiales...

- [ ] a) Puede ser hiperbólica.
    
- [ ] b) Puede ser treshold / hard limiter.
    
- [ ] c) Puede ser sigmoidal.
    
- [ ] d) Puede ser logarítmica.
    
- [ ] e) Todas son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Las Redes Neuronales Artificiales admiten un abanico inmenso de funciones matemáticas para procesar el potencial postsináptico. Dependiendo de la topología y el problema, se usan funciones de umbral/escalón (_hard limiter_ para el Perceptrón simple), sigmoides logarítmicas o tangentes hiperbólicas (para capas ocultas o clasificación probabilística), y funciones lineales puras (para salida en regresión). Todas las mencionadas son válidas.

### 7. Extrapolación en Redes Neuronales

Si un perceptrón multicapa entrenado es alimentado con una instancia en un área donde no había muestras de entrenamiento...

- [ ] a) Siempre devolverá un error.
    
- [ ] b) Siempre devolverá 0 como salida.
    
- [ ] c) Siempre devolverá -1 como salida.
    
- [ ] d) Siempre devolverá 1 como salida.
    
- [ ] e) Devolverá una salida arbitraria e impredecible.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Las Redes Neuronales Artificiales son excelentes "interpoladores" (pueden generalizar muy bien dentro del dominio envuelto por sus datos de entrenamiento). Sin embargo, son pésimos "extrapoladores". Si se les inyecta un patrón de entrada de un área del hiperespacio que jamás han explorado (fuera de su rango de entrenamiento), la red no dará un error de software, sino que escupirá un valor matemático calculado a través de sus pesos actuales, el cual será totalmente **arbitrario, sesgado e impredecible** desde la lógica humana.

### 8. Problemas del Descenso del Gradiente

Entrenar una RNA utilizando un algoritmo de entrenamiento basado en el algoritmo de descenso de gradiente tiene el siguiente problema...

- [ ] a) Nunca encontrará el mínimo global.
    
- [ ] b) Al alcanzar un mínimo, oscilará de un lado a otro, incapaz de permanecer en él.
    
- [ ] c) Alcanzará un mínimo con incrementos muy pequeños.
    
- [ ] d) Es posible que se quede atrapado en algún mínimo local.
    
- [ ] e) Requerirá un número muy alto de épocas para lograr un error aceptable.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> El descenso del gradiente clásico (empleado en _Backpropagation_) es un algoritmo analítico determinista y miope. Su única regla es "descender por la pendiente más pronunciada". Si la topología de la función de coste es rugosa y presenta "valles falsos", el algoritmo descenderá hasta el fondo de ese valle y el gradiente se hará cero. Al carecer de momento inercial o visión panorámica, se quedará irremediablemente **atrapado en ese mínimo local**, asumiendo erróneamente que ha llegado al fondo absoluto (mínimo global).

### 9. Evaluación de la Capacidad de Generalización

Para evaluar qué tan bien entrenada está una red y qué tan bien generaliza, es necesario evaluar el error...

- [ ] a) en el conjunto de entrenamiento.
    
- [ ] b) en el conjunto de validación.
    
- [ ] c) en el conjunto de prueba (Test).
    
- [ ] d) en la época de entrenamiento con el gradiente más pequeño.
    
- [ ] e) en la época de entrenamiento con el momento más pequeño.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Existe una jerarquía estricta en el uso de los datos. El conjunto de _entrenamiento_ ajusta los pesos. El conjunto de _validación_ se usa como monitor durante el entrenamiento para tunear hiperparámetros o aplicar parada temprana (early stopping). Sin embargo, la auténtica prueba de fuego (la métrica final de rendimiento para saber si la red ha generalizado correctamente el problema hacia el mundo real y no solo ha memorizado) se mide obligatoriamente evaluando su error en un **conjunto de prueba (_test set_)**, un lote de datos absolutamente virgen e independiente que el modelo jamás ha visto durante su diseño.

### 10. Función del Conjunto de Validación

En una RNA, el conjunto de validación...

- [ ] a) se usa para evaluar la capacidad de generalización de la red.
    
- [ ] b) debe ser linealmente separable.
    
- [ ] c) realiza la modificación de los pesos con el algoritmo correspondiente.
    
- [ ] d) no realiza la modificación de los pesos, pero controla el proceso de entrenamiento y lo detiene cuando es necesario.
    
- [ ] e) Todas las respuestas anteriores son incorrectas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> El conjunto de validación actúa como un monitor o árbitro externo. Los datos que lo componen jamás pasan por el algoritmo de actualización de pesos (descartando la opción c). Su función es evaluar cómo se comporta la red ante datos que no ha "visto" durante el entrenamiento para aplicar la estrategia de regularización denominada "parada temprana" (_early stopping_): detiene el entrenamiento justo cuando el error de entrenamiento sigue bajando pero el de validación empieza a subir (inicio del sobreentrenamiento).

### 11. Detención Temprana (Early Stopping)

Durante el proceso de entrenamiento de una RNA utilizando la técnica de detención temprana, los valores más bajos de error en los conjuntos de entrenamiento, validación y prueba se alcanzan en épocas diferentes. ¿Qué pesos se toman para la red que se devuelve?

- [ ] a) Los de la época con el error de validación más bajo.
    
- [ ] b) Los de la época con el error de prueba más bajo.
    
- [ ] c) Los de la última época de entrenamiento.
    
- [ ] d) Los de la época con el gradiente más bajo.
    
- [ ] e) Los de la época con el error de entrenamiento más bajo.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Al utilizar la técnica de detención temprana, el programa de diseño evalúa la pérdida en el conjunto ciego de validación. La orden algorítmica es retroceder en el tiempo y devolver a nivel productivo "la copia estructural de la red guardada en la **época matemática exacta donde el error del conjunto de validación registró su marca histórica más baja**", pues es ahí donde se demuestra la mayor capacidad de generalización teórica de la red.

### 12. Topología de la Capa de Salida (Clasificación Binaria)

Para utilizar una RNA para resolver un problema de clasificación con dos clases, sin la posibilidad de que una instancia no pertenezca a ninguna de ellas, el número de neuronas que se debe usar en la capa de salida es...

- [ ] a) 1.
    
- [ ] b) 2.
    
- [ ] c) 3.
    
- [ ] d) 4.
    
- [ ] e) 5.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> En un problema de clasificación estrictamente dicotómica (o binaria) donde todos los elementos del mundo pertenecen imperativamente a la Clase A o a la Clase B, basta con usar **una única neurona de salida** equipada con una función de transferencia como la sigmoide o limitador duro. Si la neurona emite un 0, se asigna a la primera clase; si emite un 1, a la segunda. Añadir una segunda neurona sería redundante e ineficiente topológicamente.

### 13. Codificación de Salidas Categóricas (One-Hot)

¿Cómo codificarías una salida categórica de una RNA, cuyos valores pueden ser "coche/motocicleta/bicicleta/avión"?

- [ ] a) Como 2 valores booleanos, codificando cada una de las 4 categorías como "01/01/10/11".
    
- [ ] b) No es necesario codificarlo, la RNA puede generar esa salida categórica.
    
- [ ] c) Como 4 valores booleanos, codificando cada una de las 4 categorías como "1000/0100/0010/0001".
    
- [ ] d) Como un valor real, que toma 4 valores equiespaciados diferentes.
    
- [ ] e) Las respuestas c) y d) son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Las redes neuronales solo entienden vectores numéricos. Para variables categóricas nominales sin un orden jerárquico inherente (un coche no vale matemáticamente el doble que una bicicleta), se emplea la técnica de codificación **One-Hot Encoding**. Consiste en crear un vector del mismo tamaño que el número de clases (4 clases = 4 neuronas de salida booleanas) donde solo se enciende (valor 1) la neurona correspondiente a la clase correcta, manteniendo el resto apagadas (valor 0).

### 14. Funciones de Transferencia en Regresión

La función de transferencia de las neuronas de salida de una Red Neuronal Artificial...

- [ ] a) Será lineal si es un problema de clasificación con solo dos clases.
    
- [ ] b) Será sigmoide logarítmica si es un problema de clasificación con más de dos clases.
    
- [ ] c) Será sigmoide logarítmica si es un problema de regresión.
    
- [ ] d) Será tangente hiperbólica sigmoide si es un problema de regresión.
    
- [ ] e) Será lineal si es un problema de regresión.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Para problemas de regresión, donde se busca predecir un valor continuo en el espacio real (como una temperatura o un precio), la capa de salida debe usar una **función de transferencia estrictamente lineal** o de identidad (como _purelin_). Esto permite a la red escupir el valor en bruto sin recortar su escala numérica natural. Las funciones limitadoras (sigmoides) estrujarían los resultados impidiendo dar valores mayores a 1 o menores a 0/-1.

### 15. Autoorganización en Sistemas Conexionistas

La autoorganización en los Sistemas Conexionistas...

- [ ] a) Permite la existencia de un jefe que determina el comportamiento de los patrones.
    
- [ ] b) Evita el comportamiento emergente del sistema.
    
- [ ] c) Facilita el almacenamiento de información en las neuronas (células) de entrada.
    
- [ ] d) Permite obtener redundancia en los datos.
    
- [ ] e) Todas las anteriores son incorrectas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> La autoorganización es puramente **no supervisada** (carece de "jefe" o tutor, descartando la a); se fundamenta precisamente en permitir el **comportamiento emergente** (descartando la b); el conocimiento no se almacena en la capa de entrada, sino en la matriz topológica de pesos (descartando la c); y, finalmente, la redundancia en los datos de entrada es un _requisito previo_ para que la red descubra características estadísticas, no un resultado que "se obtenga" (descartando la d). Todas son falsas.

### 16. Adaptación Topológica Dinámica

¿Qué modelo se ajusta mejor a datos de diferentes dimensionalidades?

- [ ] a) GNG.
    
- [ ] b) SOM.
    
- [ ] c) GNS.
    
- [ ] d) SGM.
    
- [ ] e) SVM.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> El modelo **GNG (_Growing Neural Gas_)** supera a los SOM clásicos porque no utiliza una cuadrícula o malla rígida 2D predefinida. Al ser un "gas" neuronal, su arquitectura constructiva le permite crear y destruir nodos (y aristas) de forma dinámica, adaptándose orgánicamente a cualquier geometría, discontinuidad o cambio de dimensionalidad en el espacio de los datos de entrada.

### 17. Propiedad Clave de una Red SOM

En una red SOM, es importante...

- [ ] a) La ubicación espacial de las neuronas.
    
- [ ] b) La interacción de una neurona con las demás en la capa de salida.
    
- [ ] c) El número de capas ocultas.
    
- [ ] d) Que el número de neuronas en la capa de entrada sea mayor que en la capa de salida.
    
- [ ] e) Todas son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> A diferencia del perceptrón multicapa, en los Mapas de Kohonen (SOM) la **ubicación espacial y topológica** de las neuronas en la cuadrícula de salida es crítica. El algoritmo de entrenamiento (competitivo y de vecindad) está diseñado matemáticamente para que las neuronas que están físicamente cerca en el mapa terminen respondiendo a patrones de entrada que también son similares en el mundo real, preservando la topología de los datos originales.

### 18. Significado de la Capa de Salida en SOM

¿Qué representa la ubicación en la capa de salida de una neurona (célula) en una red SOM?

- [ ] a) El número de atributos de los patrones.
    
- [ ] b) El orden de presentación de cada patrón durante el proceso de entrenamiento.
    
- [ ] c) Una proyección bidimensional de los datos de entrada.
    
- [ ] d) Indica su relación con las neuronas de entrada.
    
- [ ] e) Ninguna de las anteriores es correcta.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La utilidad primordial de un SOM es la reducción de dimensionalidad espacial. Al entrenarse, la red abstrae un espacio de datos de altísima complejidad ($n$-dimensional) y lo proyecta sobre un mapa discreto, creando una **proyección topológica bidimensional (2D)**. De este modo, la ubicación en el mapa permite a los humanos visualizar e interpretar de un vistazo los clústeres y relaciones originales.

### 19. Capas Computacionales en SOM

¿Cuántas capas, que realizan cálculos, tiene una red SOM?

- [ ] a) Tantas como especifique el usuario.
    
- [ ] b) Depende del tipo de problema.
    
- [ ] c) 1.
    
- [ ] d) 2.
    
- [ ] e) Tantas como patrones de entrada.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Una arquitectura SOM estándar se compone de dos capas: una de entrada y una de salida (competitiva). Sin embargo, la capa de entrada actúa únicamente como un "buffer" pasivo que recibe los vectores del entorno sin alterar sus valores ni realizar cálculos. Por tanto, la única capa que realiza procesamiento, cálculo de distancias euclídeas y ajuste de pesos sinápticos es **1 sola capa** (la capa competitiva de salida).

### 20. Parámetros de la Ecuación de Actualización SOM

En una red SOM, ¿qué representa el parámetro _(omitido en texto/OCR, referido habitualmente a $\alpha$)_ en la fórmula de actualización de pesos?

- [ ] a) El tamaño del vecindario.
    
- [ ] b) La topología del vecindario.
    
- [ ] c) La distancia a la Unidad de Mejor Coincidencia (BMU).
    
- [ ] d) La tasa de aprendizaje.
    
- [ ] e) El parámetro no existe en la ecuación de la SOM.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)** _(Asumiendo $\alpha$ en los cuestionarios típicos)_
> 
> En la fórmula clásica de Kohonen $W_i(t+1) = W_i(t) + \alpha(t) \cdot h_{ci}(t) \cdot [x(t) - W_i(t)]$, el parámetro $\alpha(t)$ representa la **tasa de aprendizaje** (que decrece progresivamente con el tiempo). Si el símbolo omitido en el examen por fallo de escaneo se refería a $h_{ci}(t)$ o $\sigma(t)$, la respuesta sería "el tamaño del vecindario" (opción a). Ante preguntas truncadas donde las opciones de respuesta no contienen ambas, se asume típicamente la tasa de aprendizaje.

### 21. Tipo de Aprendizaje SOM

¿Qué tipo de aprendizaje ocurre en las SOM?

- [ ] a) Competitivo.
    
- [ ] b) Exhaustivo.
    
- [ ] c) Por necesidad.
    
- [ ] d) Reforzamiento.
    
- [ ] e) Las opciones c y d son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Las redes SOM utilizan un paradigma de aprendizaje puramente **no supervisado y competitivo**. Ante la presentación de un vector de entrada, todas las neuronas de la red calculan su similitud geométrica y "compiten" entre sí. Solo existe una ganadora absoluta (BMU) que se lleva el derecho principal de actualizar sus pesos de acuerdo con la información de entrada.

### 22. La Neurona Ganadora (BMU)

¿Qué es la neurona (célula) ganadora en una red SOM?

- [ ] a) La que está más cerca del patrón de entrada.
    
- [ ] b) La neurona que representa el patrón dentro de su clúster.
    
- [ ] c) La neurona que aprende más rápido.
    
- [ ] d) La neurona que converge primero.
    
- [ ] e) La neurona en el top 5 de la red en el proceso de aprendizaje.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> La neurona ganadora, conocida técnicamente como BMU (_Best Matching Unit_), se define exclusivamente como la célula de la malla cuyo vector interno de pesos presenta la menor distancia matemática (usualmente euclidiana) respecto al vector de datos de entrada. En términos topológicos, es **la neurona que está más cerca** de ese patrón.

### 23. Significado de los Pesos en SOM

¿Qué representan los pesos de las neuronas en la red SOM?

- [ ] a) Clústeres.
    
- [ ] b) Conocidos como bias.
    
- [ ] c) Número de patrones aprendidos.
    
- [ ] d) Prototipos, centros o centroides de clústeres.
    
- [ ] e) Grupos.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> A diferencia del Perceptrón (donde los pesos son simples ponderadores), en las redes SOM las unidades operan con matrices de pesos que funcionan estructuralmente como un conjunto de coordenadas matemáticas (un vector). Estos vectores actúan como **prototipos, centros o centroides**. A medida que la red se entrena, dichos vectores migran por el espacio hasta anclarse justo en el centro de gravedad de las nubes de datos o clústeres.

### 24. Dinámica del Vecindario SOM

En una red SOM...

- [ ] a) El vecindario determina el número de neuronas contra las que uno compite por un patrón.
    
- [ ] b) El vecindario de una neurona ganadora determina cuáles se modifican parcialmente.
    
- [ ] c) El tamaño del vecindario permanece sin cambios durante todo el proceso de entrenamiento.
    
- [ ] d) La topología cambia durante el entrenamiento.
    
- [ ] e) El número de vecinos se adapta a las dimensiones del espacio de búsqueda.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> En el algoritmo de aprendizaje competitivo de un SOM, la neurona ganadora (BMU) no es la única en verse beneficiada. Se define un radio topológico alrededor de ella llamado "vecindad" (usualmente con forma de campana de Gauss). Su rol es **determinar qué neuronas adyacentes a la ganadora van a modificar parcialmente sus pesos**, forzando un comportamiento topológico continuo en toda la manta neuronal. (La 'C' es falsa porque este radio decrece con el tiempo).

### 25. Conectividad en la Arquitectura SOM

¿A cuántas neuronas se conecta cada neurona en la capa de entrada?

- [ ] a) A todas las neuronas en la capa de competencia.
    
- [ ] b) Consigo misma recursivamente.
    
- [ ] c) Solo con neuronas que alguna vez han sido ganadoras.
    
- [ ] d) Se conecta con todas y cada una de las neuronas presentes en el modelo.
    
- [ ] e) Todas son falsas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Un mapa SOM clásico se basa en una arquitectura _Feed-forward_ (hacia adelante) totalmente conectada o densa. Esto significa que **todas y cada una de las neuronas receptoras** de la capa de entrada se bifurcan y trazan conexiones sinápticas físicas hacia **todas las neuronas del mapa de salida** (la capa de competencia).

### 26. Ciclo de Vida de un Modelo SOM

¿Qué fases presenta el funcionamiento del modelo SOM?

- [ ] a) Fase de aprendizaje y modo operativo.
    
- [ ] b) Fase de aprendizaje y fase de validación.
    
- [ ] c) Fase de generalización y fase de validación.
    
- [ ] d) Fase inicial y modo de operación.
    
- [ ] e) Modo rápido y modo robusto.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> La vida de una red SOM se divide secuencialmente en dos estados. Primero la **Fase de Aprendizaje**, donde el mapa está "blando", compite de forma no supervisada, y sus pesos y la campana de vecindad se actualizan y adaptan topológicamente. Una vez el mapa converge y sus prototipos se asientan, se congelan los pesos pasando al **Modo Operativo** (o fase de mapeo), donde ante la llegada de nuevos vectores, la red simplemente identifica a la neurona ganadora para clasificarla sin alterar ya su estructura.

### 27. Métricas de Validación No Supervisada

¿Cuáles son las métricas para validar una red SOM?

- [ ] a) Error de cuantización medio y medida de preservación de topología.
    
- [ ] b) Precisión y medida de preservación de topología.
    
- [ ] c) Error de cuantización medio y medida de dispersión de topología.
    
- [ ] d) Tasa de precisión media y medida de dispersión de topología.
    
- [ ] e) Medida de preservación del conocimiento.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Dado que una red SOM opera bajo un paradigma puramente "No Supervisado", las métricas estadísticas clásicas como la "Tasa de precisión" (_Accuracy_) resultan inútiles porque carecemos de salidas esperadas o etiquetas objetivo con las que comparar. Para auditar si la red se estructuró de forma correcta se utiliza:
> 
> 1. **Error de cuantización (QE):** Mide la distancia media de todos los datos de entrada a sus respectivas BMUs.
>     
> 2. **Error topográfico (TE):** Verifica que se haya preservado correctamente la topología original, confirmando que los datos se mapean hacia neuronas estrictamente contiguas.
>     

### 28. Origen Biológico de la Computación Evolutiva

¿Cuál de las siguientes opciones describe correctamente los orígenes de los Algoritmos Genéticos y la Programación Genética?

- [ ] a) Fueron desarrollados por John von Neumann en la década de 1950.
    
- [ ] b) Son el resultado de avances en inteligencia artificial en la década de 1980.
    
- [ ] c) Tienen sus raíces en los trabajos de Charles Darwin y Alfred Wallace sobre evolución y selección natural.
    
- [ ] d) Fueron propuestos por Charles Babbage durante la Segunda Guerra Mundial.
    
- [ ] e) El principal precursor es Mendel con su trabajo sobre la deriva genética.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Los algoritmos evolutivos (introducidos por John Holland) son una rama heurística bio-inspirada de la IA. Toda su arquitectura algorítmica y su terminología (individuos, población, cruce, mutación, aptitud) están fuertemente inspiradas en la **Teoría de la Evolución de las Especies** y la mecánica de la **Selección Natural** formulada empíricamente por Charles Darwin (junto a los trabajos de Alfred Wallace).

### 29. Teoría Evolutiva y Fitness

A la luz de las diferentes teorías evolutivas presentes en los Algoritmos Genéticos, ¿cuál de las siguientes inspira la operación de aptitud (Fitness)?

- [ ] a) Aprendizaje Hebbiano.
    
- [ ] b) Teoría de la Conservación de Lamarck.
    
- [ ] c) Teoría de la Evolución de Darwin.
    
- [ ] d) Leyes de Mendel.
    
- [ ] e) Deriva genética.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La función de "Aptitud" (_Fitness_) implementada en código representa al juez de supervivencia del Algoritmo Genético. Evalúa qué individuo está mejor preparado para el entorno, decidiendo quién se reproduce y quién es descartado (selección). Esta doctrina de "la supervivencia del más fuerte o más apto" es la base doctrinal directa de la **Teoría de la Evolución por Selección Natural de Darwin**.

### 30. Exploración vs Explotación

En el contexto de los algoritmos evolutivos, ¿qué técnica se utiliza para explotar la información presente en la población y mejorar las soluciones?

- [ ] a) Cruce (Recombinación).
    
- [ ] b) Mutación.
    
- [ ] c) Selección.
    
- [ ] d) Reemplazo.
    
- [ ] e) Clonación.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> En los metaheurísticos evolutivos existe un dilema constante entre explorar nuevas áreas (búsqueda ciega) o mejorar las actuales (perfeccionamiento). La Mutación es el operador de "Exploración". Por el contrario, el operador de Recombinación o **Cruce** es el encargado de la **Explotación**: mezcla y aprovecha la información (bloques genéticos valiosos) ya presente en las partes exitosas del genoma de padres fuertes para generar hijos teóricamente superiores.

### 31. Ajuste Local y Lamarckismo (Algoritmos Meméticos)

En un algoritmo genético, ¿cuál es el nombre dado al proceso por el cual el mejor individuo en la población pasa por una fase de ajuste local y así se inserta en la población?

- [ ] a) Siembra.
    
- [ ] b) Elitismo.
    
- [ ] c) Aprendizaje Lamarckiano.
    
- [ ] d) Estado Estable.
    
- [ ] e) Ascenso de Colinas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Cuando un individuo de un AG explora topológicamente su entorno local durante su "vida" (ej. mediante _hill-climbing_) para mejorar su aptitud y, tras esa fase de ajuste, sobreescribe sus propios genes para heredar de forma directa esa mejora a su descendencia, estamos implementando explícitamente el concepto biológico de la **Evolución Lamarckiana** (la herencia de los caracteres o habilidades adquiridos en vida).

### 32. Cálculo de Tasas en AG

Supongamos que se ejecuta un algoritmo genético en una población de 1000 individuos. Si en la segunda generación se obtienen 100 individuos mutados, ¿qué combinación de tasa de cruce y probabilidad de mutación es más probable que se haya utilizado?

- [ ] a) Tasa de cruce de 0.9 y ratio de mutación de 0.01
    
- [ ] b) Tasa de cruce de 0.9 y ratio de mutación de 0.001
    
- [ ] c) Tasa de cruce de 1.0 y ratio de mutación de 0.01
    
- [ ] d) Tasa de cruce de 1.0 y ratio de mutación de 0.001
    
- [ ] e) Tasa de cruce de 0.7 y ratio de mutación de 0.1
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Es un cálculo de probabilidad matemático directo. Si partimos de un censo total de 1000 individuos y el algoritmo devuelve que estadísticamente 100 de ellos sufrieron el operador de mutación en sus genes, la ratio efectiva que está operando en el sistema es de $100 / 1000 = 0.1$. La única opción que contempla correctamente esta **tasa de mutación de 0.1** es la opción e.

### 33. Efecto del Tamaño Poblacional

En algoritmos genéticos, ¿cómo puede afectar el tamaño de la población la eficiencia y efectividad del proceso de optimización?

- [ ] a) Con un tamaño de población más grande, se requiere más tiempo para converger hacia una solución óptima.
    
- [ ] b) Con un tamaño de población más pequeño, la diversidad genética y la exploración del espacio de búsqueda aumentan.
    
- [ ] c) Con un tamaño de población más grande, la probabilidad de encontrar soluciones óptimas globales disminuye.
    
- [ ] d) Con un tamaño de población más pequeño, se reducen los costos computacionales y se acelera la convergencia.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)** _(Nota: La 'A' también presenta una premisa cierta, pero la 'D' suele ser la definición buscada para la justificación de optimización de código)._
> 
> El tamaño de la población regula el balance computacional. Una población muy grande asegura alta diversidad genética, pero consume recursos extremos de CPU ralentizando el programa por el número de evaluaciones del _fitness_. Al revés, un **tamaño de población pequeño reduce drásticamente el coste computacional y acelera enormemente la convergencia** (aunque aumenta el riesgo teórico de estancarse en mínimos locales por baja diversidad).

### 34. Análisis de Dinámica Mutación/Cruce

En un Algoritmo Genético...

- [ ] a) Si la tasa de mutación es cero, el algoritmo funciona porque el cruce lleva a la evolución.
    
- [ ] b) Si la tasa de cruce es cero, la mutación causa que todos los individuos acumulen demasiados cambios.
    
- [ ] c) Si la tasa de cruce es cero, la mutación genera variabilidad y el algoritmo de selección lleva a la evolución.
    
- [ ] d) Si tanto la tasa de cruce como la tasa de mutación son cero, el algoritmo de selección prevalece y lleva a la evolución.
    
- [ ] e) Es imposible que las tasas de cruce y/o mutación sean cero.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Si alteramos la arquitectura del AG anulando el cruce (tasa = 0%), la recombinación genética desaparece. Sin embargo, la mutación continuará inyectando ruido aleatorio constante (variabilidad fenotípica) sobre los individuos aislados, y el mecanismo darwiniano de "Selección" se encargará de salvaguardar aquellas mutaciones que presenten mejoras en la aptitud. El sistema seguirá evolucionando, comportándose como una simple técnica de **Búsqueda Aleatoria Guiada** (Estrategia Evolutiva).

### 35. Evaluación Genérica de la Población

¿Cuál de las siguientes afirmaciones es verdadera con respecto a todas las técnicas de Computación Evolutiva?

- [ ] a) Las soluciones deben codificarse en forma de árbol.
    
- [ ] b) Las poblaciones más grandes favorecen una evolución más rápida.
    
- [ ] c) El esquema de reemplazo generacional usa menos memoria.
    
- [ ] d) Las funciones de aptitud deben ser evaluables para cada individuo en la población.
    
- [ ] e) El criterio de terminación debe ser único.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Para que los mecanismos estocásticos de torneo y selección de Darwin funcionen, el algoritmo informático debe ser capaz de determinar quién sobrevive y quién no. Esto convierte en un requisito tecnológico universal que la función **Fitness** (la evaluación de aptitud del problema) pueda calcularse sin excepciones para todos y cada uno de los cromosomas (individuos) generados en la población.

### 36. Naturaleza Geométrica en Programación Genética

Con respecto al siguiente árbol que representa un individuo en la programación genética, ¿cuál de las siguientes afirmaciones es verdadera? _(Asumiendo operadores como nodos y variables/constantes como hojas)._

- [ ] a) Los componentes terminales son `[1, 14]`.
    
- [ ] b) Los componentes no terminales son $X$, $Y$, $+$, $-$.
    
- [ ] c) La profundidad máxima del árbol es 3.
    
- [ ] d) Es un árbol desequilibrado.
    
- [ ] e) No puede representar un individuo porque tiene que ser un vector de variables.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> En base a la teoría genotípica en Programación Genética (GP), la opción C evalúa la profundidad estructural de los niveles de llamadas recursivas en el árbol de código. Las opciones A y B son completamente falsas por definición semántica: los nodos "terminales" u hojas alojan siempre las constantes (`1`, `14`) **junto con** las variables ($X$, $Y$); y los nodos "no terminales" o funcionales son única y exclusivamente los operadores algebraicos/lógicos (`+`, `-`, `*`). La E es falsa porque GP usa explícitamente árboles, no vectores planos.

### 37. Impacto y Equilibrio de la Tasa de Mutación

¿Cuál es el efecto de ajustar la tasa de mutación en la programación genética y cómo puede influir en la convergencia del algoritmo?

- [ ] a) Aumentar la tasa de mutación acelera la convergencia del algoritmo...
    
- [ ] b) Reducir la tasa de mutación en poblaciones grandes puede mejorar la convergencia...
    
- [ ] c) La tasa de mutación no tiene impacto en la convergencia del algoritmo...
    
- [ ] d) Ajustar óptimamente la tasa de mutación puede equilibrar la exploración y la explotación en la programación genética, facilitando la convergencia hacia soluciones de alta calidad.
    
- [ ] e) La tasa de mutación solo afecta la velocidad de convergencia del algoritmo...
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> La tasa de mutación es el hiperparámetro que regula el "caos" del sistema. Si es muy baja, el modelo sufre convergencia prematura (se atasca en mínimos locales por baja exploración). Si es muy alta, degenera en una búsqueda puramente aleatoria (destruyendo los bloques buenos obtenidos por explotación en el cruce). Su **ajuste óptimo es la clave heurística para equilibrar** este "Trade-off" (exploración vs explotación) garantizando llegar a un óptimo global de alta fidelidad.

### 38. Propósito Específico del Cruce (Crossover)

¿Cuál es el objetivo principal del operador de cruce en las técnicas de computación evolutiva?

- [ ] a) Reducir la diversidad en la población.
    
- [ ] b) Expandir el espacio de búsqueda.
    
- [ ] c) Explotar la información presente en la población.
    
- [ ] d) Seleccionar los mejores individuos en función de su función de aptitud.
    
- [ ] e) Introducir aleatoriedad en la población.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> En las metaheurísticas evolutivas, el rol de "Expandir" o investigar zonas nuevas (aleatoriedad) recae enteramente sobre el operador de Mutación. El operador de Recombinación o **Cruce** asume la labor de **Explotación**: cruzar, enlazar y aprovechar eficientemente la información valiosa (los buenos alelos o "Building Blocks") ya descubierta en los individuos fuertes de la generación actual para engendrar hijos que retengan y mejoren esos rasgos.

### 39. Híbridos Evolutivos

La combinación de "Hill-climbing" y algoritmos genéticos:

- [ ] a) Es una técnica de búsqueda donde su principal problema es la convergencia temprana.
    
- [ ] b) Es una técnica de búsqueda aplicada en algoritmos genéticos donde su principal problema es que no garantiza obtener el óptimo global.
    
- [ ] c) Solo se puede aplicar en la programación genética.
    
- [ ] d) Está inspirada en los principios de la evolución Lamarckiana para mejorar la convergencia del proceso evolutivo.
    
- [ ] e) Es una técnica que realiza una búsqueda aleatoria en el espacio de soluciones...
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Este tipo de combinaciones (un algoritmo global genético híbrido con una técnica de ajuste de búsqueda local como _Hill-climbing_ por cada individuo) recibe el nombre técnico de "Algoritmo Memético". Si los fenotipos mejorados mediante la búsqueda local son codificados de vuelta (inyectados como genotipo) al cromosoma del agente para heredárselo a sus hijos de manera ventajosa, se está replicando a nivel informático la base de la **Evolución Lamarckiana** (la herencia biológica de los caracteres adquiridos).

### 40. Mecanismos de Selección y Prevención de Endogamia

¿Cuál de las siguientes estrategias describe con mayor precisión el mecanismo de selección utilizado en algoritmos evolutivos para promover la diversidad genética y evitar la convergencia prematura?

- [ ] a) Selección por ruleta, donde los individuos se asignan a sectores de una ruleta ponderada...
    
- [ ] b) Selección por ruleta, donde los individuos se asignan a sectores de una ruleta con igual probabilidad...
    
- [ ] c) Selección por torneo, donde los individuos se agrupan en subconjuntos y el individuo con el mejor valor de aptitud es seleccionado para cada grupo.
    
- [ ] d) Selección por torneo, donde los individuos compiten en pares y el ganador se selecciona con una probabilidad proporcional a su aptitud.
    
- [ ] e) Selección por torneo, donde los individuos se agrupan en subconjuntos y los dos individuos con menor aptitud de cada subconjunto son seleccionados para la reproducción.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La estrategia tradicional de "Ruleta" es muy propensa a provocar la "convergencia prematura": los individuos excesivamente sobresalientes al inicio del programa copan el 90% de los giros de la ruleta, devorando a los demás y destruyendo la diversidad por endogamia (clonación masiva). La **Selección por Torneo** soluciona esto aislando ciegamente pequeños _subconjuntos_ o agrupaciones aleatorias y haciendo que compitan localmente entre ellos, **seleccionando siempre al que posea mejor valor de aptitud dentro de su pequeña arena**. Esto da oportunidades reales de supervivencia y reproducción a individuos modestos pero genéticamente valiosos, promoviendo de forma óptima la diversidad global de la especie a largo plazo.