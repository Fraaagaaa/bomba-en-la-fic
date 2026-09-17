
# Simbólica
### 1. Búsqueda A* sobre Grafo

Dado el siguiente grafo, en donde (i) el nodo inicial es $A$ y el nodo meta es $G$, (ii) el valor numérico dentro de cada nodo indica el resultado de evaluar una función heurística $h$, y (iii) el valor numérico en cada arista indica el coste de transición entre los diferentes estados:

![[grafo2023.png]]

Aplicando el algoritmo A* basado en **grafo**, en algún paso, los nodos de la frontera vendrán dispuestos según la siguiente configuración (considerar precedencia izq a drch, que el número entre paréntesis representa el correspondiente valor $f$, $f=h+g$, y que en caso de empate en valor $f$, la precedencia de expansión vendrá dada por el orden alfabético de los nodos correspondientes):

- [ ] a) E(20), D(22)
    
- [ ] b) B(20), E(20), D(22)
    
- [ ] c) E(20), D(21)
    
- [ ] d) B(20), E(21), D(22)
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> En el algoritmo A* basado en **grafo**, se mantiene una lista de nodos "Cerrados" (Explorados). Si la heurística no es consistente (como ocurre aquí, ya que $h(A)=25 \not\le c(A,C)+h(C) = 2+20=22$), la versión estricta del algoritmo en grafo **no reabre nodos que ya han sido cerrados**, aunque encuentre un camino mejor hacia ellos (este es el motivo por el que en la pregunta 2 del examen se afirma que A* en este problema encuentra el óptimo "de casualidad").
> 
> Realizamos la traza paso a paso usando la ecuación $f(n) = g(n) + h(n)$:
> 
> 1. **Paso 1:** Se expande el inicial $A$.
>     
>     - Genera $B$ ($g=5, h=16 \rightarrow f=21$) y $C$ ($g=2, h=20 \rightarrow f=22$).
>         
>     - **Frontera:** `[B(21), C(22)]`. **Cerrados:** `{A}`.
>         
> 2. **Paso 2:** Se expande $B$ (por tener el menor valor $f$).
>     
>     - Genera $D$ ($g=5+7=12, h=10 \rightarrow f=22$).
>         
>     - **Frontera:** `[C(22), D(22)]` (por empate $f$, orden alfabético). **Cerrados:** `{A, B}`.
>         
> 3. **Paso 3:** Se expande $C$.
>     
>     - Genera $E$ ($g=2+10=12, h=8 \rightarrow f=20$).
>         
>     - También encuentra una nueva ruta hacia $B$ con menor coste ($g=2+2=4 \rightarrow f=20$).
>         
>     - **Punto clave:** Como estamos en búsqueda sobre _grafo_, el algoritmo comprueba si el nodo $B$ ya ha sido expandido. Como $B$ ya está en la lista de Cerrados `{A, B}`, la nueva ruta hacia él **se descarta** y el nodo no se reabre.
>         
>     - **Frontera resultante:** Tras añadir solo $E$, la frontera queda conformada por el nuevo nodo $E$ y el nodo $D$ que ya estaba esperando: **`[E(20), D(22)]`**.
>         
> 
> Esta configuración coincide exactamente con la opción **a**.
### 2. Optimalidad en el algoritmo A*

En el mismo problema de la pregunta 1, ¿obtiene el algoritmo A* una solución óptima?

- [ ] a) No, la heurística no es admisible.
    
- [ ] b) No, la heurística no es consistente.
    
- [ ] c) Si, ya que la heurística es admisible.
    
- [ ] d) Si, pero de casualidad, ya que la heurística no es consistente.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Para que el algoritmo A* garantice teóricamente una solución óptima al recorrer un grafo, su heurística debe ser consistente (monótona) y admisible. Una heurística es admisible si nunca sobreestima el coste real hacia la meta. Si observamos el grafo del ejercicio, desde el nodo $E$ hasta la meta $G$ el coste real es de $2$, pero su estimación heurística marca $h(E) = 8$. Como $8 > 2$, la heurística sobreestima flagrantemente el coste y **no es admisible** (y por consiguiente, tampoco es consistente). 
> 
> Prueba adicional de que no es consistente (de A a C):
> 
> Una heurística es consistente si el coste estimado desde un nodo a la meta no es mayor que el coste de dar un salto físico hacia su vecino más la estimación de dicho vecino. La inecuación matemática que debes aplicar siempre es: $h(n)≤c(n,n′)+h(n′)$.
> 
> Para saber si C cumple la regla, calculamos lo mismo de siempre
> 
>  - La estimación dentro del nodo A es h(A)=25.
>   - El coste de la flecha para viajar de A hacia C es c(A,C)=2.
>   - La estimación dentro del nodo C es h(C)=20.
>   
>- **El cálculo:** Sustituimos los números en la inecuación: ¿Es 25≤2+20? Es decir, **¿Es** 25≤22**?** No, la inecuación es falsa porque 25 es mayor que 22.
> 
> A pesar de esto, si ejecutamos el algoritmo paso a paso, A* acaba encontrando la ruta óptima de coste 14. Al lograrlo con una heurística que rompe las reglas teóricas, lo hace estrictamente **"de casualidad"**. _(Nota: Descarta plantillas libres que marquen la opción 'c', ya que matemáticamente la heurística es inadmisible)._

### 3. Ejecución de la Búsqueda Avara

En el mismo problema de la pregunta 1, indica la secuencia del camino devuelto utilizando, esta vez, la búsqueda avara:

- [ ] a) A $\rightarrow$ B $\rightarrow$ D $\rightarrow$ G
    
- [ ] b) A $\rightarrow$ C $\rightarrow$ B $\rightarrow$ D $\rightarrow$ G
    
- [ ] c) A $\rightarrow$ C $\rightarrow$ E $\rightarrow$ G
    
- [ ] d) Ninguno de los anteriores
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> A diferencia de A*, el algoritmo de Búsqueda Avara (_Greedy Best-First_) es corto de miras y toma sus decisiones guiándose exclusivamente por el menor valor de la heurística $h(n)$ en la frontera, ignorando por completo el coste real acumulado $g(n)$.
> 
> Ejecutando el recorrido:
> 
> 1. Desde $A$, se abren los caminos hacia $B$ ($h=16$) y $C$ ($h=20$). Como $16 < 20$, la búsqueda avara elige $B$.
>     
> 2. Desde $B$, se abre el camino a $D$ ($h=10$). Elige $D$.
>     
> 3. Desde $D$, se abren caminos a $E$ ($h=8$) y $G$ ($h=0$). Elige la meta $G$.
>   
> 
> El camino devuelto ciegamente es **A $\rightarrow$ B $\rightarrow$ D $\rightarrow$ G**. _(Nota: Las plantillas no oficiales de Wuolah indican la opción C, pero ese es el camino que devuelve A_, no la búsqueda avara).*

### 4. Búsqueda de Coste Uniforme (UCS)

En la búsqueda de coste uniforme:

- [ ] a) Cada operador aplicable siempre tendrá el mismo coste.
    
- [ ] b) Cualquier camino solución encontrado tendrá siempre el mismo coste.
    
- [ ] c) Cualquier camino solución encontrado tendrá siempre el mismo número de pasos.
    
- [ ] d) Cualquier camino solución encontrado tendrá siempre el mínimo número de pasos.
    
- [ ] e) Ninguna de las anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> La Búsqueda de Coste Uniforme (UCS) es un algoritmo óptimo guiado exclusivamente por la función $g(n)$ (coste acumulado del camino). Su garantía teórica es que encuentra el camino de **mínimo coste absoluto** hacia la meta.
> 
> - La a) es falsa, los operadores pueden (y suelen) tener costes distintos.
>     
> - La b) es falsa/ambigua: el algoritmo devolverá el camino de coste mínimo, no significa que todos los caminos imaginables del grafo midan lo mismo.
>     
> - Las c) y d) son falsas porque la optimización por pasos (mínimo número de saltos) es característica exclusiva de la **Búsqueda en Amplitud (BFS)**, no de UCS. Por ello, la opción e) es la única lógicamente rigurosa.
>     

### 5. Algoritmo de Profundidad Iterativa

En el algoritmo de profundidad iterativa se cumple que la cantidad de nodos hoja en la iteración "$i$" es siempre mayor que la suma acumulada de todos los nodos generados previamente en las "$i-1$" iteraciones anteriores:

- [ ] a) Cierto.
    
- [ ] b) Dependerá del número de iteraciones "$i$".
    
- [ ] c) Dependerá del factor de ramificación.
    
- [ ] d) Falso.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Matemáticamente, en un árbol de búsqueda con un factor de ramificación constante $b$, el número de nodos hoja (frontera) en el nivel de profundidad $d$ (o iteración $i$) es $b^i$. La suma total de todos los nodos generados en las iteraciones previas es una progresión geométrica $\sum_{k=0}^{i-1} b^k = \frac{b^i - 1}{b - 1}$.
> 
> Para que la base actual $b^i$ sea mayor que todos los nodos anteriores combinados $\frac{b^i - 1}{b - 1}$, la inecuación exige estrictamente que el factor de ramificación $b$ sea mayor o igual a 2. Por ende, la afirmación no es un axioma absoluto, sino que depende matemáticamente del factor de ramificación.

### 6. Escalada (Hill-Climbing) y Árboles

En el contexto del algoritmo de escalada en búsqueda local, el siguiente árbol de búsqueda se corresponde con una situación de: 
![[arbolHillClimbing2023.png]]
- [ ] a) Mínimo local.
    
- [ ] b) Máximo local.
    
- [ ] c) Meseta.
    
- [ ] d) Cresta.
    
- [ ] e) Ninguna de las anteriores, ya que dicho desarrollo nunca podría darse aplicando la búsqueda de escalada.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Se trata de una "pregunta trampa" clásica. A diferencia de A* o Búsqueda en Anchura, el algoritmo de Escalada Simple (_Hill-Climbing_) pertenece a la familia de métodos de **Búsqueda Local**. La característica teórica definitoria de esta familia es que **no conservan ni generan un "árbol de búsqueda" en memoria** (operan sin historial). Solamente guardan el "estado actual" y evalúan a sus vecinos inmediatos para decidir el siguiente paso. Por lo tanto, es algorítmica y estructuralmente imposible que _Hill-Climbing_ produzca la representación de un árbol de exploración.

### 7. Representación del Conocimiento (Declarativo vs Procedimental)

Señala la respuesta correcta:

- [ ] a) Una de las ventajas fundamentales de los métodos declarativos de representación del conocimiento es que facilitan trabajar con información de carácter probabilístico.
    
- [ ] b) Los métodos procedimentales son más adecuados para la codificación de conocimiento fruto de la experiencia.
    
- [ ] c) En los métodos declarativos la incorporación de nuevo conocimiento suele implicar la recodificación del ya existente.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> En la representación del conocimiento, los métodos procedimentales (cuyo máximo exponente son los Sistemas de Producción basados en reglas _IF-THEN_) nacieron específicamente para capturar las heurísticas y atajos mentales de los expertos humanos (conocimiento fruto de la experiencia o empírico).
> 
> - La a) es falsa: los métodos declarativos puros (Lógica) son formales y frágiles ante la incertidumbre; esto se gestiona con otros paradigmas como Redes Bayesianas.
>     
> - La c) es falsa: la mayor virtud de los modelos declarativos y modulares (como la base de hechos/reglas) es que se puede incorporar nuevo conocimiento **añadiendo axiomas a la base** sin necesidad de alterar o recodificar todo el motor.
>     


### 8. Traza en Sistemas de Producción (Encadenamiento Progresivo)

En el contexto de un sistema de producción, se parte de la siguiente base de reglas y estado de la Memoria Activa inicial ($M_0$):

- **R1:** $A \land B \implies C$
    
- **R2:** $E \lor F \implies D$
    
- **R3:** $D \land C \implies X$
    
- **R4:** $B \land D \implies R$
    
- **R5:** $X \land R \implies H$
    
- **$M_0$** = $\{A, B, E\}$ _(Nota: $H$ es la meta buscada)_.
    

**Configuración del Motor:** Encadenamiento progresivo. Búsqueda en profundidad, con la ejecución de la regla cuya premisa contenga el elemento en orden alfabético mayor de las que hayan sido activadas más recientemente (asumiendo que $A > B > C \dots$). ¿Cuál es la secuencia de ejecución de las reglas?

- [ ] a) R2 $\rightarrow$ R1 $\rightarrow$ R3 $\rightarrow$ R4 $\rightarrow$ R5
    
- [ ] b) R1 $\rightarrow$ R2 $\rightarrow$ R3 $\rightarrow$ R4 $\rightarrow$ R5
    
- [ ] c) R2 $\rightarrow$ R1 $\rightarrow$ R4 $\rightarrow$ R3 $\rightarrow$ R5
    
- [ ] d) R1 $\rightarrow$ R2 $\rightarrow$ R4 $\rightarrow$ R3 $\rightarrow$ R5
    

> [!success]- Solución y Justificación (Traza paso a paso)
> 
> **Opción correcta: d)**
> 
> Un motor de inferencia clásico ejecuta **solo una regla por ciclo**. La estrategia de desempate dictamina que gana la regla "más reciente" (las que acaban de activarse en ese ciclo). Si hay empate de novedad, gana la que tenga la letra con mayor prioridad en el abecedario en sus premisas.
> 
> **CICLO 1:**
> 
> - **Memoria Activa (MA):** $\{A, B, E\}$
>     
> - **Conjunto Conflicto (CC):** Se activan **R1** (cumple $A \land B$) y **R2** (cumple $E$).
>     
> - **Resolución:** Ambas son recientes. Empate. Miramos sus premisas: $R1$ tiene la **A**, $R2$ tiene la **E**. Gana la $R1$ por orden alfabético.
>     
> - **Ejecución:** Se dispara **R1**. Añadimos $C$ a la memoria.
>     
> 
> **CICLO 2:**
> 
> - **MA:** $\{A, B, E, C\}$
>     
> - **CC:** Revisamos si la nueva letra $C$ activa algo nuevo. $R3$ necesita la $D$, así que no. En el Conjunto Conflicto solo nos queda esperando la **R2**.
>     
> - **Ejecución:** Se dispara **R2**. Añadimos $D$ a la memoria.
>     
> 
> **CICLO 3:**
> 
> - **MA:** $\{A, B, E, C, D\}$
>     
> - **CC:** Al entrar la $D$, se activan de golpe dos reglas nuevas: **R3** (cumple $D \land C$) y **R4** (cumple $B \land D$).
>     
> - **Resolución:** Ambas son hiper-recientes. Empate. Miramos sus premisas: $R3$ tiene $\{C, D\}$ (gana la **C**). $R4$ tiene $\{B, D\}$ (gana la **B**). Como la B va antes en el abecedario, gana $R4$.
>     
> - **Ejecución:** Se dispara **R4**. Añadimos $R$ a la memoria.
>     
> 
> **CICLO 4:**
> 
> - **MA:** $\{A, B, E, C, D, R\}$
>     
> - **CC:** La nueva letra $R$ no activa $R5$ todavía (nos falta la $X$). En el Conjunto Conflicto nos queda esperando la **R3** desde el ciclo anterior.
>     
> - **Ejecución:** Se dispara **R3**. Añadimos $X$ a la memoria.
>     
> 
> **CICLO 5:**
> 
> - **MA:** $\{A, B, E, C, D, R, X\}$
>     
> - **CC:** Al entrar la $X$, se activa por fin la regla **R5** (cumple $X \land R$).
>     
> - **Ejecución:** Se dispara **R5**. Llegamos a la meta $H$.
>     
> 
> **Traza final:** $R1 \rightarrow R2 \rightarrow R4 \rightarrow R3 \rightarrow R5$.


### 9. Lógica Categórica (Base Lógica Reducida)

Dada la siguiente codificación de posibles Manifestaciones ($M$) e Interpretaciones ($I$) en un contexto de razonamiento categórico:

**Tabla de Manifestaciones (M):**

||**m1**|**m2**|**m3**|**m4**|**m5**|**m6**|**m7**|**m8**|
|---|---|---|---|---|---|---|---|---|
|**M(1)**|0|0|0|0|1|1|1|1|
|**M(2)**|0|0|1|1|0|0|1|1|
|**M(3)**|0|1|0|1|0|1|0|1|

**Tabla de Interpretaciones (I):**

||**i1**|**i2**|**i3**|**i4**|
|---|---|---|---|---|
|**I(1)**|0|0|1|1|
|**I(2)**|0|1|0|1|

Y sea el siguiente conjunto de reglas:

> R1: $M(1) \vee M(2) \vee M(3) \rightarrow I(1) \vee I(2)$
> 
> R2: $I(2) \rightarrow \neg M(2) \wedge M(1)$
> 
> R3: $I(1) \vee \neg I(2) \rightarrow M(2) \wedge M(3)$

Si en un momento dado se da la ocurrencia $f = M(1) \wedge \neg M(2) \wedge \neg M(3)$, entonces podríamos deducir que:

- [ ] a) La interpretación I(1) es falsa.
    
- [ ] b) La interpretación I(1) es verdadera.
    
- [ ] c) La interpretación I(2) es falsa.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Analizamos lógicamente la manifestación entregada. La evidencia $f$ nos dice categóricamente que $M(1)$ es Verdadera ($1$), $M(2)$ es Falsa ($0$), y $M(3)$ es Falsa ($0$).
> 
> Si evaluamos esto en la **Regla 3** ($I(1) \vee \neg I(2) \rightarrow M(2) \wedge M(3)$), observamos que el consecuente ($M(2) \wedge M(3)$) es forzosamente **Falso** (porque carecemos de ambas manifestaciones).
> 
> Por las reglas básicas de la implicación lógica (_Modus Tollens_), si el consecuente de una regla es falso, su antecedente no puede ser verdadero. Esto exige que el bloque $(I(1) \vee \neg I(2))$ sea obligatoriamente **Falso**.
> 
> Para que una disyunción ("O") sea falsa, ambas partes deben ser falsas: por tanto, **$I(1)$ es Falsa** y $\neg I(2)$ es Falsa (lo que significa que $I(2)$ es Verdadera). La deducción lógica ineludible coincide a la perfección con la opción a).

### 10. Lógica Bayesiana

Con la misma situación del ejercicio anterior y sabiendo que:

- $P(i1) = 0.3 \quad ; \quad P(i2) = 0.2 \quad ; \quad P(i3) = 0.1 \quad ; \quad P(i4) = 0.4$
    
- $P(m1|i1) = 1.0 \quad ; \quad P(m1|i3) = 0.5 \quad ; \quad P(m4|i3) = 0.2 \quad ; \quad P(m5|i2) = 0.8 \quad ; \quad P(m6|i4) = 0.3$
    

¿Qué conjunto de interpretaciones es más probable?

- [ ] a) $\neg I(1) \wedge \neg I(2)$
    
- [ ] b) $\neg I(1) \wedge I(2)$
    
- [ ] c) $I(1) \wedge \neg I(2)$
    
- [ ] d) $I(1) \wedge I(2)$
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> El "ejercicio anterior" fijaba como escenario empírico la ocurrencia $f = M(1) \wedge \neg M(2) \wedge \neg M(3)$. Si observamos la matriz de manifestaciones aportada en la pregunta 9, esta combinación booleana $(1, 0, 0)$ corresponde exactamente a la columna del vector **m5**.
> 
> Al aplicar el Teorema de Bayes para hallar la interpretación más probable dada la evidencia $m5$, buscamos maximizar la relación: $P(i_k | m5) \propto P(m5 | i_k) \cdot P(i_k)$.
> 
> Revisando los datos condicionales brindados, la única verosimilitud que existe en el conocimiento probabilístico sobre $m5$ apunta directamente a la interpretación $i_2$: **$P(m5 | i2) = 0.8$**. Las demás interpretaciones ($i1, i3, i4$) son lógicamente incompatibles con el vector $m5$ debido a la Base de Reglas (por ejemplo, vimos en la pregunta 9 que si $m5$ ocurre, $I(1)$ tiene que ser Falsa e $I(2)$ Verdadera, lo cual anula de base a $i1, i3$ e $i4$).
> 
> Por tanto, la interpretación dominante absoluta es $i_2$, que, leyendo la tabla de interpretaciones de la pregunta anterior, corresponde a los valores booleanos $I(1)=0$ e $I(2)=1$, cuya representación lógica es **$\neg I(1) \wedge I(2)$**.
> 
> _(Nota: Evita las plantillas libres que asignen la opción 'C'. Si fuera $i_3$, forzaría a que $I(1)$ fuera cierta, lo cual dispararía la Regla 3 obligando a que existieran M(2) y M(3), lo que sabemos que es falso porque nuestra evidencia base es m5)._

# Subsimbólica

### 1. Etapas en la Neurona Artificial

Al recibir las entradas una neurona artificial, estas se combinan en primer lugar mediante una:

- [ ] a) Función de activación
    
- [ ] b) Regla Delta
    
- [ ] c) Regla de propagación
    
- [ ] d) Función de transferencia
    
- [ ] e) Función de validación
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La asimilación matemática en una célula artificial opera en dos etapas secuenciales. La "Regla de propagación" constituye siempre el primer paso algorítmico, encargándose de recopilar y combinar las señales del entorno exterior (generalmente mediante un sumatorio lineal ponderado por los pesos y sumando el _bias_). Posteriormente, ese potencial bruto pasará por la función de transferencia/activación.

### 2. Limitaciones del Modelo ADALINE

El ADALINE...

- [ ] a) No tiene capas ocultas
    
- [ ] b) Tiene una función de transferencia de tipo sigmoidal
    
- [ ] c) No puede ser entrenado con la Regla Delta
    
- [ ] d) Puede realizar aproximaciones no lineales
    
- [ ] e) Es capaz de aprender cualquier relación entrada/salida
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> El modelo ADALINE (_Adaptive Linear Neuron_) es una arquitectura de red neuronal estrictamente monocapa. Al carecer de capas ocultas y utilizar una función de activación puramente lineal, no puede trazar fronteras de decisión curvas ni resolver problemas no lineales (como el operador XOR).

### 3. Dinámica de la Regla Delta

La Regla Delta...

- [ ] a) Modifica los pesos en el sentido (signo) del cambio realizado en el ciclo anterior
    
- [ ] b) Modifica los pesos en el sentido (signo) opuesto del cambio realizado en el ciclo anterior
    
- [ ] c) Modifica los pesos en el sentido (signo) de la pendiente del error
    
- [ ] d) Modifica los pesos en el sentido (signo) opuesto de la pendiente del error
    
- [ ] e) Todas son falsas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> La Regla Delta se fundamenta en el descenso por el gradiente. Para minimizar el margen de error entre la salida obtenida y la deseada, los pesos deben ajustarse restando el valor del gradiente. Es decir, los pesos se desplazan espacialmente de manera rigurosa en la dirección diametralmente contraria u "opuesta" a la pendiente calculada de la función de error.

### 4. Hiperparámetros de Entrenamiento

Al entrenar una RNA, el algoritmo de entrenamiento dice que la modificación de los pesos se debe de multiplicar por una constante llamada...

- [ ] a) Momento
    
- [ ] b) Gradiente
    
- [ ] c) Delta
    
- [ ] d) Tasa de aprendizaje
    
- [ ] e) Bias
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> En la ecuación de retropropagación del error, la magnitud del cambio que dictamina la derivada parcial se modula a través de un escalar constante crucial llamado "Tasa de aprendizaje" ($\alpha$ o $\eta$). Este escalar determina "el tamaño del paso" que da el algoritmo, regulando la velocidad a la que la red converge.

### 5. Estancamiento del Gradiente

Si durante el entrenamiento de una RNA, en un ciclo se obtiene un gradiente de 0, esto quiere decir...

- [ ] a) Se está muy lejos de un mínimo
    
- [ ] b) Se está muy cerca de un mínimo, pero no en él
    
- [ ] c) Se está en un mínimo, y es el global
    
- [ ] d) Se está en un mínimo, pero no se sabe si es el global o uno local
    
- [ ] e) El error es 0
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Cuando la pendiente (gradiente) de la superficie del error alcanza 0, la recta tangente es paralela, indicando que el algoritmo ha aterrizado en el fondo de un "valle". El problema crítico del descenso del gradiente ciego es que, sin examinar todo el hiperespacio, la red neuronal no tiene forma matemática de discernir si está en el fondo absoluto (mínimo global) o simplemente atrapada en una depresión subóptima (mínimo local).

### 6. Capacidades del Perceptrón Simple

Atendiendo a las capacidades funcionales de un Perceptrón clásico monocapa:

- [ ] a) Puede resolver problemas no linealmente separables.
    
- [ ] b) Utiliza funciones de base radial.
    
- [ ] c) Es capaz de aprender la función XOR sin capas adicionales.
    
- [ ] d) Tiene propiedades bayesianas innatas para la incertidumbre.
    
- [ ] e) Todas son falsas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Minsky y Papert demostraron matemáticamente en 1969 las limitaciones fundamentales de los perceptrones simples (monocapa): no pueden trazar fronteras complejas y son incapaces de operar si las clases de datos de entrada no son estricta y rígidamente separables mediante una única línea recta (hiperplano).

### 7. Dimensión de Capas Ocultas

El número óptimo de neuronas que se debe incluir en las capas ocultas de un Perceptrón Multicapa:

- [ ] a) Se calcula siempre como la suma de nodos de la capa de entrada y salida
    
- [ ] b) Depende del problema a resolver
    
- [ ] c) Debe ser igual a 2N+1 por el Teorema de Kolmogorov
    
- [ ] d) Debe elegirse de forma estocástica e inmutable
    
- [ ] e) Ninguna es correcta
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> En la arquitectura conexionista no existe un postulado analítico cerrado universal que determine cuántas neuronas ocultas son la cifra perfecta. La cantidad de nodos ocultos constituye un hiperparámetro empírico que depende directamente de la complejidad y no-linealidad específica de los datos del problema a resolver.

### 8. Teorema de Aproximación Universal

¿Es factible emplear un perceptrón multicapa para mapear relaciones no separables linealmente que presentan un alto grado de no-linealidad geométrica?

- [ ] a) Sí, pero sólo si el algoritmo emplea regularización estocástica
    
- [ ] b) No, ninguna red neuronal logra superar la barrera del XOR en dominios complejos
    
- [ ] c) No, se debe usar obligatoriamente computación evolutiva o lógica borrosa
    
- [ ] d) Sí, siempre y cuando la red devuelva resultados discretizados con escalones
    
- [ ] e) En cualquier caso, si la red tiene la complejidad suficiente
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> El Teorema de Aproximación Universal demuestra formalmente que cualquier red conexionista _Feed-forward_ equipada con funciones de activación no lineales es capaz de modelar o aproximar funciones continuas arbitrarias (relaciones extremadamente no-lineales), siempre y cuando posea el número de capas ocultas o la complejidad interna adecuada.

### 9. Extrapolación en Espacios Desconocidos

¿Cuál será el comportamiento del sistema si, tras entrenar con éxito una RNA, se le suministran patrones novedosos ubicados muy fuera de las fronteras topológicas del espacio de generalización aprendido?

- [ ] a) Avisará algorítmicamente mediante una excepción matemática
    
- [ ] b) Aplicará autoorganización dinámica en caliente para asimilar la nueva entrada
    
- [ ] c) Se adaptará automáticamente basándose en los bias
    
- [ ] d) Devolverá el último patrón correcto almacenado en la memoria
    
- [ ] e) Dará una salida arbitraria e imprevisible
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Las Redes Neuronales son excelentes interpolando, pero pésimas extrapolando. Si se inyecta un patrón "alienígena" fuera de la distribución estadística vista en el entrenamiento, la arquitectura inyectará ciegamente el valor a través de la matriz de pesos congelados, provocando una respuesta computada totalmente espuria e imprevisible.

### 10. Tasa de Aprendizaje Excesiva

¿Qué efecto fenomenológico ocurre al someter a la red de un proceso iterativo en donde la Tasa de Aprendizaje se ha configurado con un escalar demasiado elevado?

- [ ] a) Se convergerá matemáticamente al mínimo global de manera ultrarrápida
    
- [ ] b) Se correrá el riesgo de oscilar en torno al mínimo
    
- [ ] c) Se provocará un sub-ajuste o underfitting automático en los bias
    
- [ ] d) Se bloqueará la capacidad de generalización estocástica
    
- [ ] e) La red entrará irreversiblemente en un efecto de parada temprana
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Si la tasa de aprendizaje es demasiado alta, el incremento del vector de ajuste será gigantesco, provocando que la red efectúe saltos ciegos que errarán el fondo del valle. En consecuencia, el error rebotará sistemáticamente de una ladera a otra, generando oscilaciones caóticas y divagaciones sin estabilizarse jamás.

### 11. Tasa de Aprendizaje Diminuta

El hecho de entrenar una RNA mediante un algoritmo de entrenamiento basado en el gradiente descendente (con pasos ínfimos) tiene el problema de que...

- [ ] a) Nunca va a encontrar el mínimo global
    
- [ ] b) Al acercarse a un mínimo, se va a oscilar de un lado a otro, sin lograr pararse en él
    
- [ ] c) Se va a acercar a un mínimo de incrementos muy pequeños
    
- [ ] d) Es posible que se quede parado en algún mínimo local
    
- [ ] e) Va a necesitar un número muy alto de ciclos para alcanzar un error aceptable
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)** _(Nota: La 'E' también es un problema temporal, pero la 'D' es la falla catastrófica del modelo)_
> 
> Debido a que los pasos que efectúa el vector iterativo son pequeños, si en la superficie de coste encuentra cualquier leve protuberancia o bache de "mínimo local", el gradiente morirá. Al carecer de inercia suficiente para saltar y franquear la cresta, el entrenamiento quedará estancado de forma permanente en un estado subóptimo.

### 12. Conjunto de Prueba (Test)

En una RNA, el conjunto de test...

- [ ] a) Se utiliza para evaluar la capacidad de generalización de la red
    
- [ ] b) Debe de ser linealmente separable
    
- [ ] c) Produce la modificación de los pesos mediante el algoritmo correspondiente
    
- [ ] d) No produce la modificación de los pesos, pero controla el proceso de entrenamiento, y lo para si es necesario
    
- [ ] e) Todas son falsas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> La métrica final e indiscutible de rendimiento para saber si la red ha generalizado correctamente el problema hacia el mundo real (y no solo ha memorizado) se mide obligatoriamente evaluando su error en el conjunto de prueba (_Test Set_), un lote de datos absolutamente virgen que la red no ha visto ni en la fase de entrenamiento ni en la de validación/tuneo.

### 13. Prevención del Sobreentrenamiento

Las técnicas de regularización permiten...

- [ ] a) Entrenar una RNA hasta alcanzar un error de 0
    
- [ ] b) Saltar mínimos locales al entrenar una RNA
    
- [ ] c) Eliminar el ruido del conjunto de entrenamiento
    
- [ ] d) Resolver problemas de clasificación no linealmente separables
    
- [ ] e) Evitar el sobreentrenamiento al entrenar una RNA
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Las técnicas de regularización (como el _Early Stopping_, _Dropout_, o las penalizaciones L1/L2) tienen una única misión fundamental: penalizar la memorización excesiva. Fuerzan a la red a mantener modelos simples o a abortar a tiempo, garantizando que el modelo prevenga el temido "sobreentrenamiento" (_overfitting_) provocado por absorber el ruido de los datos.

### 14. Capa de Salida Dicotómica

Para usar una RNA para resolver un problema de clasificación con dos clases, sin posibilidad de que un patrón no pertenezca a ninguna de las dos clases, el número de neuronas de salidas que hay que usar es...

- [ ] a) 1
    
- [ ] b) 2
    
- [ ] c) 3
    
- [ ] d) 4
    
- [ ] e) 5
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> En un escenario predictivo estrictamente binario y mutuamente excluyente, disponer de dos neuronas de salida sobreparametriza el modelo de manera ineficiente. El problema se resuelve empleando **1 sola neurona** provista de una función sigmoidal: si su salida es $< 0.5$ se infiere la clase A, y si es $\ge 0.5$ se infiere ineludiblemente la clase B.

### 15. Autoorganización en el Conexionismo

La autoorganización en Sistemas Conexionistas...

- [ ] a) Permite que exista un jefe que determine el comportamiento de los patrones
    
- [ ] b) Impide un comportamiento emergente del sistema
    
- [ ] c) Facilita que la información se guarde en las neuronas de entrada
    
- [ ] d) Permite que se obtenga redundancia en los datos
    
- [ ] e) Todas las anteriores son incorrectas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> La autoorganización es un aprendizaje **no supervisado** (carece de "jefe", descartando a). Se fundamenta en originar comportamiento emergente (descartando b). El conocimiento no reside algorítmicamente en las celdas receptoras, sino proyectado en la matriz de pesos sinápticos (descartando c). Finalmente, la redundancia de datos es un requisito de entrada necesario para que la red descubra correlaciones, no un subproducto obtenido (descartando d).

### 16. Inspiración Fisiológica en SOM

En la corteza cerebral (y en su emulación mediante redes SOM)...

- [ ] a) La ubicación espacial de las neuronas constituye un mapa organizado
    
- [ ] b) Todas las neuronas idénticas realizan la misma función
    
- [ ] c) La ubicación de las neuronas no es significativa
    
- [ ] d) Todas las anteriores son correctas
    
- [ ] e) Todas las anteriores son incorrectas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> A diferencia de los perceptrones clásicos, en los Mapas de Kohonen (SOM) la topología espacial es fundamental. Modelando de manera fiel la corteza somatosensorial del cerebro mamífero, la red se ve forzada a organizar las unidades competitivas espacialmente; las neuronas ubicadas geométricamente adyacentes se especializan en excitarse ante estímulos del entorno que también son similares entre sí.

### 17. Dimensionalidad Isomórfica (GCS)

Si los patrones de entrada de un problema tienen dos características o atributos, una Growing Cell Structure (GCS) que lo resuelva tendrá...

- [ ] a) 1 neurona de entrada
    
- [ ] b) 4 neuronas de entrada
    
- [ ] c) 6 neuronas de entrada
    
- [ ] d) 8 neuronas de entrada
    
- [ ] e) Todas las anteriores son incorrectas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Las redes no supervisadas exigen un mapeo isomórfico directo con su entorno. La cardinalidad de la capa de entrada debe coincidir rigurosamente en formato 1 a 1 con la dimensionalidad de las magnitudes vectoriales a percibir. Por tanto, si el patrón cuenta con 2 atributos de entrada, la arquitectura exigirá obligatoriamente **2 neuronas base receptoras**. Como el número 2 no aparece entre las alternativas listadas, todas son incorrectas.

### 18. Evolución Geométrica: SOM vs GCS

Diferencias entre SOM y GCS son:

- [ ] a) La GCS no consideran neuronas vecinas a la ganadora
    
- [ ] b) Un SOM considera un radio de vecindad de diferentes niveles
    
- [ ] c) Las GCS consideran solamente vecinas directas a la ganadora
    
- [ ] d) No hay diferencia en cuestión de vecindario, la diferencia está en la variación dinámica del numero de neuronas de la capa competitiva
    
- [ ] e) B y C son correctas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> El algoritmo SOM clásico aplica su atenuación gaussiana a todo un parche extenso o vecindario (afectando de manera degradada a neuronas a "diferentes niveles" de proximidad). Por el contrario, la topología de la _Growing Cell Structure_ (GCS) es mucho más puntual y agresiva, limitándose algorítmicamente y de forma exclusiva a actualizar solamente a los nodos vecinos colindantes unidos a la BMU mediante un enlace topológico ("vecinas directas").

### 19. Capacidades Estructurales del GCS

Una GCS...

- [ ] a) Está siempre orientada a clasificación
    
- [ ] b) Permite añadir neuronas en regiones con menos patrones de entrenamiento
    
- [ ] c) Tiene una capa de salida formada por diferentes estructuras k-dimensionales básicas a la vez
    
- [ ] d) No se entrena, sus pesos se construyen a partir de los patrones de entrada
    
- [ ] e) Todas las anteriores son incorrectas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Se rechazan las opciones porque: A es falsa (es de clustering no supervisado, no de clasificación _per se_). B es diametralmente falsa, ya que su gran innovación es añadir dinámicamente neuronas justo en las regiones con _mayor error_ y densidad de patrones, no en las de menos. C es falsa porque se apoya en una estructura dimensional única mediante símplices o k-dimensionalidades discretas en su crecimiento. D es falsa porque evidentemente la red exige someterse a múltiples fases de entrenamiento.

### 20. Estructura Tradicional de Capas en SOM

Los Mapas Autoorganizativos (SOM) tienen normalmente...

- [ ] a) Una capa de entrada, tres o cuatro capas ocultas y una capa de salida
    
- [ ] b) Una única capa que es de entrada y salida
    
- [ ] c) Una capa de entrada y una capa de salida
    
- [ ] d) Una capa de neuronas recurrentes y autoorganizables
    
- [ ] e) Todas las anteriores son incorrectas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)** _(O la opción "c" si el docente la considera formal. Nota explicativa: En las plantillas oficiales de la UDC, la respuesta oficial validada es la "e")._
> 
> Esta pregunta puede tener "truco" semántico, razón por la cual la plantilla oficial dictaminó la 'e'. A nivel estrictamente computacional, la red SOM solo posee **1 única capa** de células que procesan pesos (la capa competitiva topológica). La capa de "entrada" es un mero bus transparente que transmite las señales, no cuenta como capa de cálculo, por lo que llamarle arquitectura "de dos capas (entrada y salida)" es un error teórico en el conexionismo estricto de Kohonen.
### 21. Aprendizaje No Supervisado

En el aprendizaje no supervisado...

- [ ] a) Se consiguen grupos con elementos similares dentro del mismo grupo.
    
- [ ] b) La autoorganización de la red permite hallar las clases supervisadas.
    
- [ ] c) Se trabaja con patrones etiquetados con tipo o clase.
    
- [ ] d) Si un patrón de entrada no pertenece a ningún grupo reconocido previamente, se descarta siempre.
    
- [ ] e) La B y la C son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> El objetivo principal del aprendizaje no supervisado (como el clustering o las redes SOM) es descubrir estructuras ocultas en datos no etiquetados. El sistema agrupa los patrones basándose exclusivamente en su similitud matemática (distancia euclídea), logrando que los elementos dentro de un mismo grupo (clúster) sean muy similares entre sí, y muy dispares respecto a los de otros grupos. (Las opciones B y C son falsas por definición al referirse a etiquetas/supervisión).

### 22. Representación en la Capa Competitiva (SOM)

En un SOM...

- [ ] a) Cada neurona de la capa competitiva representa siempre a un solo patrón de entrada.
    
- [ ] b) Cada neurona de la capa competitiva puede representar a un grupo de patrones de entrada.
    
- [ ] c) Cada neurona de la capa de entrada representa a un prototipo.
    
- [ ] d) Cada neurona de la capa de entrada se conecta con x neuronas y estas x conexiones constituyen un prototipo.
    
- [ ] e) La A y la C son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> En los Mapas Auto-Organizativos de Kohonen, la matriz de pesos de cada neurona de la capa competitiva (salida) actúa como un centroide o prototipo. Dado que el número de neuronas del mapa suele ser muchísimo menor que el número total de datos del mundo real, múltiples patrones de entrada que sean topológicamente similares activarán (tendrán como BMU) a la misma neurona, haciendo que esta represente a todo ese clúster o "grupo" de patrones.

### 23. Dimensionalidad en Redes Neuronales

Si los patrones de entrada tienen diferentes dimensiones, la red más aconsejable para agruparlos es...

- [ ] a) Un SOM.
    
- [ ] b) Una GNG.
    
- [ ] c) Un ADALINE.
    
- [ ] d) Una GCS.
    
- [ ] e) Ninguna de las anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Un axioma arquitectónico estricto de las Redes Neuronales Artificiales clásicas (incluyendo SOM, GNG, GCS y perceptrones) es que requieren tensores de entrada de tamaño fijo. La capa de entrada debe poseer exactamente un nodo por cada dimensión del patrón. Si los patrones del problema tienen "diferentes dimensiones" (vectores de tamaño variable), ninguna de estas redes puede procesarlos crudamente; requerirían algoritmos de preprocesamiento (como _padding_) o arquitecturas recurrentes (RNN) no contempladas en las opciones.

### 24. Tasas de Aprendizaje en Redes GCS

Las tasas de aprendizaje para redes GCS son...

- [ ] a) Las mismas que para redes SOM.
    
- [ ] b) Dos tasas diferenciadas.
    
- [ ] c) Una única de aprendizaje en todos los casos.
    
- [ ] d) La A y la B son correctas.
    
- [ ] e) Ninguna de las anteriores es correcta.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> En el algoritmo de _Growing Cell Structures_ (GCS), la regla de adaptación de pesos es mucho más focalizada que en el SOM clásico (el cual usa una función de vecindario gaussiana decreciente). GCS emplea estrictamente **dos tasas de aprendizaje diferenciadas e invariantes en el tiempo**: una tasa mayor ($\epsilon_b$) que se aplica de forma exclusiva a la neurona ganadora (BMU), y una tasa mucho menor ($\epsilon_n$) que se aplica únicamente a las neuronas topológicamente conectadas a ella de forma directa (sus vecinas en el grafo).

### 25. Fundamento Biológico del Aprendizaje No Supervisado

Las redes de neuronas con entrenamiento no supervisado...

- [ ] a) Tienen un fundamento biológico, se basan en la corteza cerebral.
    
- [ ] b) Se llaman así porque el supervisor no sabe supervisarlas.
    
- [ ] c) No son de utilidad actualmente.
    
- [ ] d) La B y la C son correctas.
    
- [ ] e) Ninguna de las anteriores es correcta.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Redes como el SOM de Teuvo Kohonen se inspiraron directamente en la neurofisiología, específicamente en los **mapas topográficos de la corteza cerebral** de los mamíferos (como el córtex visual o somatosensorial). En el cerebro, neuronas físicamente cercanas responden a estímulos sensoriales similares (por ejemplo, frecuencias de sonido continuas), organizándose de manera autónoma y no supervisada mediante excitación lateral, exactamente igual que las redes competitivas artificiales.

### 26. Resolución del Problema del Viajante (TSP)

El problema del viajante con una SOM...

- [ ] a) Se resuelve considerando una vecindad lineal.
    
- [ ] b) Se resuelve sin vecindad.
    
- [ ] c) Nunca se puede resolver.
    
- [ ] d) La B y la C son correctas.
    
- [ ] e) Ninguna de las anteriores es correcta.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> El clásico Problema del Viajante de Comercio (TSP) busca el camino más corto que conecte múltiples ciudades (puntos 2D) formando un circuito cerrado. Para resolverlo con una red SOM, se altera su estructura: en lugar de una malla 2D, se inicializa la red como una **cadena unidimensional cerrada (un anillo o vecindad lineal elástica)**. Al entrenar, este anillo se estira y se retuerce auto-organizándose hasta pasar por todas las "ciudades" de entrada, generando el recorrido óptimo.

### 27. Inspiración Biológica Descartada

Los trabajos de uno de los siguientes investigadores NO forman parte de la inspiración biológica que se utilizó como base para conformar el cómo funcionan los algoritmos genéticos. ¿Cuál?

- [ ] a) Gregor Mendel.
    
- [ ] b) Alfred Wallace.
    
- [ ] c) Jean-Batiste Lamark.
    
- [ ] d) Charles Darwin.
    
- [ ] e) John H. Holland.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Los Algoritmos Genéticos estándar (formalizados por John Holland) se basan estrictamente en la teoría de la Selección Natural (Darwin y Wallace) y en la genética clásica de la herencia cromosómica (Mendel). **Jean-Baptiste Lamarck** propuso la teoría de la "herencia de los caracteres adquiridos" (ej. las jirafas estiran el cuello y sus hijos nacen con cuello largo), un concepto que se descarta en la genética clásica y en los Algoritmos Genéticos puros (aunque sí inspira modelos híbridos complejos como los _Algoritmos Meméticos_).

### 28. Casos de Uso de los Algoritmos Genéticos

Se recomienda y está más justificado el uso de los Algoritmos Genéticos...

- [ ] a) En aquellos problemas cuya complejidad permita una solución directa.
    
- [ ] b) En aquellos problemas cuya complejidad no permita una solución directa.
    
- [ ] c) En los problemas resolubles polinomialmente.
    
- [ ] d) Cuando existe un único mínimo local y el espacio de búsqueda es muy pequeño.
    
- [ ] e) Siempre es recomendado su uso.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Los Algoritmos Genéticos son metaheurísticas de gran coste computacional. Aplicarlos a problemas sencillos, derivables o con solución directa (opciones A y C) es "matar moscas a cañonazos". Su uso está estrictamente justificado en dominios NP-Hard: problemas de altísima complejidad, hiperespacios de búsqueda inmensos, con múltiples mínimos locales o topologías discontinuas donde los métodos analíticos directos fracasan irremediablemente.

### 29. El Operador de Explotación

¿Cuál de los siguientes operadores genéticos es el responsable de explotar la información presente en la población?

- [ ] a) Clonación.
    
- [ ] b) Cruce.
    
- [ ] c) Mutación.
    
- [ ] d) Remplazo.
    
- [ ] e) Selección.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> En computación evolutiva, la **Explotación** consiste en aprovechar y combinar el "buen material" ya descubierto. El operador de **Cruce (Recombinación)** es el encargado de esta tarea: toma fracciones valiosas (_Building Blocks_) del genoma de dos padres exitosos y las entrelaza, asumiendo que al juntar características genéticas ganadoras, se obtendrá una solución hija teóricamente superior.

### 30. El Operador de Exploración

El objetivo del operador de mutación es...

- [ ] a) Reducir la diversidad de la población.
    
- [ ] b) Explorar en el espacio de búsqueda.
    
- [ ] c) Explotar la información que está en la población.
    
- [ ] d) Seleccionar aquellos individuos que son mejores, en función de su función de ajuste.
    
- [ ] e) En un esquema steady-state, decir qué individuos deben de deshacerse para hacer sitio a los nuevos.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Contrario al cruce, la Mutación es el motor de la **Exploración**. Inyecta pequeñas disrupciones ciegamente aleatorias (ruido) en los cromosomas para garantizar que la población explore y salte a nuevas coordenadas del hiperespacio. Esto previene la pérdida irreversible de alelos y evita que el sistema converja prematuramente estancándose en un mínimo local.

### 31. Requisitos Arquitectónicos Universales (AG)

¿Cuál de las siguientes afirmaciones es cierta en relación a los algoritmos genéticos?

- [ ] a) Las soluciones deben de ser codificadas en forma de árbol.
    
- [ ] b) Las poblaciones grandes favorecen una evolución más rápida.
    
- [ ] c) El esquema de remplazo generacional utiliza menos memoria.
    
- [ ] d) Las funciones de ajuste deben de poder evaluarse en cada individuo de la población.
    
- [ ] e) El criterio de parada debe de ser único.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> El motor base del darwinismo computacional es la criba de selección. Para que esto opere, es una condición _sine qua non_ que el sistema disponga de una **función de ajuste (_Fitness_)** capaz de evaluar, medir y puntuar matemáticamente la aptitud de **todos y cada uno** de los cromosomas vivos en el pool poblacional en cada ciclo evolutivo. (La opción A es falsa, los AG usan vectores/cadenas; la B es falsa, a mayor población mayor lentitud computacional).

### 32. Concepto de Elitismo

Elitismo en algoritmos genéticos...

- [ ] a) No existe este concepto.
    
- [ ] b) Sólo es aplicable a la Programación Genética.
    
- [ ] c) Es la estrategia de mantener los mejores individuos de la población.
    
- [ ] d) Se encarga de buscar los mejores individuos y con ellos generar una nueva población.
    
- [ ] e) La nueva población es generada a partir exclusivamente del mejor individuo (élite).
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> El **elitismo** es una póliza de seguro algorítmica. Dado que el cruce y la mutación son probabilísticos, podrían "destruir" por azar a un cromosoma maravillosamente apto hallado en la generación $T$. El elitismo obliga al motor de reemplazo a clonar y **mantener intactos al mejor individuo (o grupo élite)** y pasarlo directamente a la generación $T+1$, garantizando que el estado del arte del algoritmo nunca involucione.

### 33. Técnicas de Selección

En algoritmos genéticos existen las técnicas de selección denominadas:

- [ ] a) Profundidad y anchura.
    
- [ ] b) Recombinación puntual y uniforme.
    
- [ ] c) Ruleta y torneo.
    
- [ ] d) Cruce y mutación.
    
- [ ] e) Combinatoria múltiple y estocástica uniforme.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Las técnicas que escogen quién obtiene el derecho a reproducirse conforman los Operadores de Selección. La **Ruleta** (selección proporcional donde se asigna a cada individuo una porción del disco según su _fitness_) y el **Torneo** (donde se extraen subconjuntos aleatorios compitiendo localmente) son las dos estrategias estocásticas de selección más canónicas e implementadas en computación evolutiva.

### 34. Definición de Generación

En un Algoritmo Genético el término "Generación"...

- [ ] a) Representa cada ciclo de funcionamiento del Algoritmo.
    
- [ ] b) En el mecanismo de gestión de población "Steady-State" representa el cambio de todos los individuos por los hijos.
    
- [ ] c) Representa seleccionar al mejor individuo de cada población para copiarlo a la siguiente población.
    
- [ ] d) No existe este concepto en Algoritmos Genéticos.
    
- [ ] e) Ninguna de las anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Al igual que en la biología, una generación computacional se define de manera estructural como **un ciclo completo (o iteración temporal) de funcionamiento** del bucle principal del algoritmo: se evalúa la aptitud de la población actual, se selecciona, se cruza, se muta y se somete a reemplazo, marcando el inicio formal de una nueva generación genética en la simulación.

### 35. Algoritmos Steady-State (Estado Estacionario)

La denominación "Steady-state" en términos de un Algoritmo Genético es...

- [ ] a) El mecanismo mediante el cual se mantiene a los mejores individuos en una población.
    
- [ ] b) Un tipo de gestión de la población de individuos. En este tipo también hay que especificar el tipo de sustitución de individuos.
    
- [ ] c) Una forma de crear la población de descendientes antes de eliminar la población de los padres y pasar a la siguiente generación.
    
- [ ] d) Una forma de combinar los Algoritmos Genéticos con técnicas de optimización local.
    
- [ ] e) No existe esta palabra en estos sistemas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Frente al modelo "Generacional" (donde muere el $100\%$ de los padres de golpe), el modelo **Steady-State** es un tipo de **gestión poblacional** donde solo nacen uno o dos descendientes por cada ciclo. Esto obliga arquitectónicamente al ingeniero a diseñar e incluir un **algoritmo de sustitución** adicional para dictaminar qué integrante concreto y aislado de la vieja población debe "morir" para ceder su puesto vital al recién llegado (ej: sustituir al peor, al más viejo, o al más parecido).

### 36. Motor Evolutivo en Programación Genética

_(Enunciado reconstruido en base a la solución oficial)_

En la Programación Genética...

- [ ] a) Las soluciones son vectores de números reales o cadenas de bits.
    
- [ ] b) No interviene el operador de mutación por su fragilidad.
    
- [ ] c) Se emplean mecánicas de descenso de gradiente.
    
- [ ] d) El algoritmo de evolución de la población de individuos es igual al de los Algoritmos Genéticos.
    
- [ ] e) Ninguna de las anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Aunque la Programación Genética difiere radicalmente de los Algoritmos Genéticos en su forma de representar los cromosomas (utilizando complejos árboles sintácticos en lugar de simples cadenas o vectores planos), **su motor de evolución subyacente es exactamente el mismo**. Ambos se rigen por idéntico flujo de control biológico: inicializar población, evaluar _fitness_, seleccionar, realizar cruce y mutación (adaptados a árboles) y reemplazar.

### 37. Hibridación: Algoritmos Meméticos

_(Enunciado reconstruido en base a la solución oficial)_

La inyección de una técnica de búsqueda local (como Hill-Climbing) acoplada a un individuo dentro de un algoritmo genético (Algoritmo Memético):

- [ ] a) Mejora los individuos para acelerar que se encuentre un óptimo local.
    
- [ ] b) Impide cualquier comportamiento basado en herencia Lamarckiana.
    
- [ ] c) Asegura la convergencia en el mínimo global en el 100% de los casos.
    
- [ ] d) Ralentiza la convergencia debido al enorme coste de memoria de red.
    
- [ ] e) Desactiva los operadores de cruce.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Un algoritmo memético fusiona la exploración global dispersa (del algoritmo genético) con la **explotación local intensiva**. Al permitir que cada individuo recién cruzado descienda algorítmicamente por la colina de su propio nicho topológico, se perfeccionan ("mejoran") sus atributos individuales antes de reproducirse de nuevo, **acelerando dramáticamente la convergencia** hacia un óptimo en los entornos del espacio que el AG global ha preseleccionado.

### 38. Propósito de la Función de Aptitud

_(Enunciado reconstruido en base a la solución oficial)_

La función de aptitud (Fitness) en un algoritmo evolutivo...

- [ ] a) La programación genética no utiliza este elemento que está solo presente en los AG.
    
- [ ] b) Se evalúa sobre el mejor individuo de la población exclusivamente.
    
- [ ] c) Sirve para determinar cuáles son los mejores individuos de la población.
    
- [ ] d) Se ejecuta sobre la población como un todo para hacer competir a las soluciones entre sí.
    
- [ ] e) Es la función que marca cuándo se cambia de una generación a la siguiente.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La función _Fitness_ o de ajuste es el corazón ciego que modela el entorno de la supervivencia natural informáticamente. Retorna un escalar numérico por cada cromosoma que **sirve estrictamente para ranquear y determinar** cuán buena o mala es la solución que propone ese individuo frente al problema. Este valor es consumido posteriormente por la ruleta o torneo para sesgar la supervivencia favoreciendo a los "mejores".

### 39. Dinámicas de Sustitución Steady-State

_(Enunciado reconstruido en base a la solución oficial)_

En los algoritmos de sustitución para insertar nuevos individuos en un entorno Steady-State:

- [ ] a) La sustitución de peores es la más rápida y, por tanto, la mejor sin discusión.
    
- [ ] b) La sustitución de padres es la mejor porque no se pierde variabilidad.
    
- [ ] c) Lo mejor es no sustituir y que la población crezca indefinidamente.
    
- [ ] d) La sustitución de parecidos hace que la evolución avance muy despacio porque todos se van a parecer.
    
- [ ] e) La mejor opción es utilizar las tres técnicas a la vez.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> La técnica del _Crowding_ o "Sustitución de Parecidos" está diseñada para forzar la inserción de hijos eliminando únicamente al individuo de la población antigua que más se le asemeje cromosómicamente. Su gran virtud es que mantiene una inmensa diversidad genética (evita que la población colapse en un clon gigante), pero su peor contrapartida dinámica es precisamente que **ralentiza de forma severa el avance y la convergencia** de la evolución.

### 40. Ausencia de Cruce en el AG

En un Algoritmo Genético...

- [ ] a) Si la tasa de mutación es 0, el algoritmo funciona porque el cruce hace que haya evolución.
    
- [ ] b) Si la tasa de cruce es 0, la mutación hace que todos los individuos acumulen demasiados cambios.
    
- [ ] c) Si la tasa de cruce es 0, la mutación genera variabilidad y el algoritmo de selección hace que haya evolución.
    
- [ ] d) Si la tasa de cruce y evolución son 0, el algoritmo de selección prevalece y hace que haya evolución.
    
- [ ] e) Es imposible que el cruce y/o la mutación sean 0.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Si alteramos la arquitectura del AG anulando el cruce (tasa = 0%), la recombinación genética desaparece por completo. Sin embargo, la mutación continuará inyectando ruido aleatorio (variabilidad fenotípica) de manera autónoma, y el mecanismo darwiniano de "Selección" operará cribando y quedándose con las mutaciones favorables. El sistema seguirá iterando y evolucionando guiado por estos fallos genéticos positivos, operando eficazmente bajo un paradigma idéntico al de las llamadas **"Estrategias Evolutivas"**.