# Examen Sistemas Inteligentes - Mayo 2025

## Parte Simbólica

### Grafo del Espacio de Estados

![[grafoMayo2025.png|600]]
### 1. Búsqueda A* sobre espacio de estados

Sobre el grafo del espacio de estados, ¿qué solución encuentra el algoritmo A*?

- [ ] a) A → C → G → K
    
- [ ] b) A → C → F → J
    
- [ ] c) A → B → D → H → L → M
    
- [ ] d) A* no encuentra la solución
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> El algoritmo A* siempre expande el nodo con el menor valor $f(n) = g(n) + h(n)$. Si trazamos la ejecución desde A:
>     1. Expandimos A. Sus sucesores son B ($f=1+5=6$) y C ($f=1+3=4$).
>     2. El menor es C. Lo expandimos y obtenemos F ($f=2+6=8$) y G ($f=2+8=10$).
>     3. La frontera tiene a B(6), F(8) y G(10). El menor es B. Al expandir B obtenemos D(9) y E(11).
>     4. La frontera ahora es F(8), D(9), G(10), E(11). El menor es F. Lo expandimos y obtenemos I ($f=3+4=7$) y J ($f=3+2=5$).
>     5. La frontera es J(5), I(7), D(9), G(10), E(11). El menor es J. Expandimos J y llegamos a K ($f=4+0=4$).
>     El camino trazado por A* es indiscutiblemente `A → C → F → J → K`. La opción B es la única que marca este recorrido óptimo a través de F y J.

### 2. Búsqueda en profundidad iterativa (IDS)

Sobre el mismo espacio de estados, ¿qué solución encuentra el algoritmo de búsqueda en profundidad iterativa?

- [ ] a) A → C → G → K
    
- [ ] b) A → C → F → J
    
- [ ] c) A → B → D → H → L → M
    
- [ ] d) No encuentra la solución
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> La profundidad iterativa (IDS) explora el árbol nivel a nivel, pero dentro de cada nivel utiliza una estrategia de profundidad pura (normalmente guiada por orden alfabético de izquierda a derecha). 
>     * Límite 0 y 1: No llega a la meta.
>     * Límite 2: Explora las ramas hasta profundidad 2 (A-B-D, A-B-E, A-C-F, A-C-G). Ninguno es meta.
>     * Límite 3: Se sumerge a profundidad 3. Explora primero todo lo que cuelga de B, y luego lo que cuelga de C. Al bajar por C, explora `A → C → F → I` y `A → C → F → J` (ninguno es meta). Finalmente explora la siguiente rama: `A → C → G → K`. ¡K es un nodo meta ($h=0$) y lo acaba de encontrar a profundidad 3! Por tanto, este es el primer camino válido que el algoritmo devuelve.

### 3. Número de expansiones en IDS

Con el enunciado anterior, ¿cuántas veces se expandirá el nodo B?

- [ ] a) 0
    
- [ ] b) 1
    
- [ ] c) 2
    
- [ ] d) 3
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> El comportamiento de IDS se basa en reiniciar la búsqueda desde cero cada vez que aumenta el límite de profundidad.
>     * Límite 0: Se expande A.
>     * Límite 1: Se expande A. Se generan B y C, pero **no** se expanden porque hemos chocado con el límite.
>     * Límite 2: Se expande A. Luego se expande B (1ª vez) y C.
>     * Límite 3: Se expande A. Luego se expande B (2ª vez) para llegar a sus nietos.
>     Por lo tanto, a lo largo de toda la ejecución para llegar a la profundidad 3, el nodo B se ha llegado a expandir exactamente 2 veces.

### 4. Redes semánticas y razonamiento por rastreo

En las redes semánticas, el razonamiento por rastreo...

- [ ] a) No puede asegurar la validez de las inferencias obtenidas
    
- [ ] b) emplea exclusivamente las relaciones de jerarquía de la red.
    
- [ ] c) evita la ambigüedad propia del lenguaje natural, al contrario que el razonamiento por emparejamiento.
    
- [ ] d) Ninguna de las anteriores es correcta.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Según la teoría de los modelos declarativos estructurados, el mecanismo de inferencia fundamental de una red semántica es la "herencia de propiedades". Este proceso algorítmico, también llamado rastreo, consiste en que cualquier propiedad cierta para un nodo superior "cae por gravedad" hacia sus ejemplares. Para lograr esto, el algoritmo rastrea y navega exclusivamente a través de los arcos de jerarquía taxonómica (como `ES_UN` o `SUBCOJUNTO_DE`).

### 5. Diferencias entre reglas IFANY e IFSOME

¿En qué se diferencian las reglas IFANY e IFSOME

- [ ] a) IFANY investiga toda la premisa, mientras que IFSOME ejecuta la acción cuando encuentra una cláusula cierta
    
- [ ] b) IFSOME investiga toda la premisa, mientras que IFANY ejecuta la acción cuando encuentra una cláusula cierta
    
- [ ] c) IFANY requiere que una cláusula sea cierta para ejecutar una acción, mientras que IFSOME requiere más de una (al menos 2)
    
- [ ] d) IFSOME requiere que una cláusula sea cierta para ejecutar una acción, mientras que IFANY requiere más de una (al menos 2)
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Esta es una pregunta teórica clásica de los Sistemas de Producción. La regla IFANY funciona como un mecanismo de cortocircuito (no exhaustivo): en cuanto detecta que la primera condición es cierta, deja de leer y dispara la acción. Por el contrario, la regla IFSOME es de naturaleza exhaustiva; aunque encuentre rápidamente una cláusula cierta, está obligada por su arquitectura a investigar toda la premisa completa para recopilar todos los datos antes de ejecutar la acción.

### 6. Arquitecturas básicas de agentes

Las arquitecturas básicas de agentes son:

- [ ] a) Reactivo, reactivo con estado, basado en metas y basado en utilidades
    
- [ ] b) Reactivo, basado en metas, basado en metas con estado y basado en utilidades
    
- [ ] c) Activo, reactivo, reactivo con estado y basado en metas
    
- [ ] d) Activo, reactivo, basado en metas con estado y basado en utilidades
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Según la clasificación teórica clásica establecida por los autores Russell & Norvig, los agentes solucionadores de problemas se estructuran y dividen en cuatro familias o arquitecturas básicas. En primer lugar, los agentes reactivos simples, que seleccionan sus acciones guiándose únicamente por las percepciones actuales, sin memoria. En segundo lugar, los agentes reactivos basados en modelos (o con estado), que mantienen un estado interno que les permite rastrear cómo evoluciona el mundo. En tercer lugar, los agentes basados en metas u objetivos, que utilizan la planificación para encontrar la secuencia de acciones que les permite alcanzar sus propósitos. Y, finalmente, los agentes basados en utilidad, que buscan siempre maximizar una medida de rendimiento, asociada a un valor numérico que representa la "bondad" o preferencia de un estado.

### 7. Cálculo de la Base Lógica Reducida (BLR)

Sea un dominio con tres manifestaciones posibles [M(1), M(2), M(3)] y dos interpretaciones [I(1), I(2)]. Desde una perspectiva categórica, y asumiendo el siguiente criterio:

#### Tabla de Manifestaciones:
| | **a** | **b** | **c** | **d** | **e** | **f** | **g** | **h** |
|---|---|---|---|---|---|---|---|---|
| **M(1)** | 0 | 0 | 0 | 1 | 0 | 1 | 1 | 1 |
| **M(2)** | 0 | 0 | 1 | 0 | 1 | 0 | 1 | 1 |
| **M(3)** | 0 | 1 | 0 | 0 | 1 | 1 | 0 | 1 |

#### Tabla de Interpretaciones:
| | **x** | **y** | **z** | **t** |
|---|---|---|---|---|
| **I(1)** | 0 | 0 | 1 | 1 |
| **I(2)** | 0 | 1 | 0 | 1 |

#### Regla del Dominio:
`R1: M(1) V M(2) V M(3) ⇒ I(1) V I(2)`

- [ ] a) $m_4 i_1$
    
- [ ] b) $m_4 i_2$
    
- [ ] c) $m_4 i_3$
    
- [ ] d) Ninguna de las opciones propuestas pertenece a la BLR
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Evaluemos si alguna de las interpretaciones para la manifestación $m_4$ logra sobrevivir a las reglas del dominio (es decir, si pertenece a la BLR).
>     * Las reglas dadas en 2025 son: `R1: M(1) v M(2) v M(3) => I(1) v I(2) | R2: I(1) => ~M(1) AND M(2) | R3: I(2) AND ~I(1) => M(1) AND M(3)`
>     * En $m_4$, tenemos $M(1)=1$, mientras que el resto de las manifestaciones son $0$.
>     * Si probamos la opción A ($m_4 i_1$): Aquí $I(1)=0$ e $I(2)=0$. La regla R1 exige que si hay manifestaciones activas (tenemos un 1), debe haber al menos una interpretación activa. Al ser ambas cero, R1 se rompe. Descartada.
>     * Si probamos la opción B ($m_4 i_2$): Aquí $I(1)=0$ e $I(2)=1$. Evaluamos R3: Su antecedente es cierto ($1$ y $\neg 0$). Pero su consecuente exige $M(1) \land M(3)$. Como $M(3)=0$, el consecuente es falso. Implicar algo falso desde un antecedente verdadero rompe la regla R3. Descartada.
>     * Si probamos la opción C ($m_4 i_3$): Aquí $I(1)=1$. Evaluamos R2: Su antecedente es cierto ($1$). Su consecuente exige $\neg M(1) \land M(2)$. Como $M(1)=1$, $\neg 1$ es $0$. El consecuente es falso. Se rompe R2. Descartada.
>     Como todas las combinaciones con $m_4$ violan alguna regla, este complejo manifestación es un escenario absurdo o imposible, y ninguna de las opciones propuestas pertenece a la BLR.

## Parte Subsimbólica

### 2. Diferencias entre las dos ramas clásicas de la IA

¿En qué se diferencian las dos ramas clásicas de la IA?

- [ ] a) La rama subsimbólica tiene menos capacidad para explicar sus resultados
    
- [ ] b) Los sistemas expertos y las redes de neuronas artificiales son sus paradigmas
    
- [ ] c) Una se basa en la estimulación y la otra en la emulación
    
- [ ] d) Ninguna de las anteriores es correcta
    
- [ ] e) A y B son correctas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Según los fundamentos introductorios, la IA Simbólica tiene una alta explicabilidad (es transparente), mientras que la Subsimbólica es una "caja negra" con menor capacidad para explicar cómo ha llegado a sus resultados (opción A correcta). Además, se diferencian en sus paradigmas fundacionales: la simbólica orbita en torno a los Sistemas Expertos y la lógica, mientras que la subsimbólica tiene a las Redes de Neuronas Articiales como su estandarte absoluto (opción B correcta).

### 3. Sistemas subsimbólicos y la emulación de la IA

¿Qué significa que los sistemas subsimbólicos pertenecen a la rama de la emulación de la IA?

- [ ] a) Que la red aprenderá muy rápido las diferencias entre ellos.
    
- [ ] b) Que es necesario poner más capas intermedias en la Red para representar mejor su conocimiento.
    
- [ ] c) Que pretendemos reproducir la función del sistema biológico inteligente.
    
- [ ] d) Que pretendemos reproducir la estructura del sistema biológico inteligente.
    
- [ ] e) Que pretendemos reproducir tanto la estructura como la función del sistema biológico inteligente.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> La simulación (propia de la IA simbólica) busca replicar el comportamiento exterior o la función sin importar cómo esté construido el programa por dentro. La emulación, por el contrario, va un paso más allá y a un nivel más profundo: intenta reproducir de manera fidedigna la "arquitectura o estructura" subyacente (creando neuronas y sinapsis artificiales) para que, de esa estructura biomimética, nazca orgánicamente la "función" inteligente.

### 4. Definición y concepto de sinapsis

¿Qué es una sinapsis?

- [ ] a) El intercambio de energía entre neuronas.
    
- [ ] b) Procedimiento fisiológico por el cual mueren las neuronas.
    
- [ ] c) Intercambio de energía entre neuronas y astrocitos.
    
- [ ] d) Intercambio de información entre los elementos del sistema nervioso.
    
- [ ] e) Todas las anteriores son correctas.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> A nivel neurobiológico básico y trasladado a los sistemas conexionistas, las sinapsis son los enlaces funcionales unidireccionales que permiten la comunicación y el trasvase de señales o información entre las distintas células del sistema nervioso, alterando el potencial de la neurona receptora.

### 5. Precursores computacionales de los sistemas conexionistas

En la evolución histórica de los sistemas conexionistas, ¿cuáles son precursores computacionales?

- [ ] a) Rosenblueth, Wiener y Bigelow.
    
- [ ] b) McCulloch y Pitts.
    
- [ ] c) Craik.
    
- [ ] d) Todos los anteriores.
    
- [ ] e) Ninguno de los anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> El nacimiento de la Inteligencia Artificial reúne a pioneros de diversas disciplinas. Por un lado, científicos como Santiago Ramón y Cajal, Donald Hebb o Warren McCulloch y Walter Pitts (estos dos últimos al trasladar la biología a modelos lógico-matemáticos en 1943) son considerados estrictamente precursores biológicos de las redes neuronales. Por otro lado, investigadores como Wiener, Rosenblueth, Bigelow y Craik, responsables de trabajos publicados también en 1943, sentaron las bases de la IA moderna desde el campo de la Cibernética. Los verdaderos precursores computacionales, catalogados como los "padres indiscutibles de las ciencias de la computación", son figuras como Alan Turing, John Von Neumann o Zuse y Sreyers, quienes sentaron las bases de la arquitectura secuencial y la computación necesaria para implementar la IA. Al no aparecer ninguno de estos precursores computacionales en las opciones A, B y C, la única respuesta válida es la E.

### 6. Precursores biológicos de los sistemas conexionistas

En la evolución histórica de los sistemas conexionistas, ¿cuáles son precursores biológicos?

- [ ] a) Minsky.
    
- [ ] b) Cajal.
    
- [ ] c) Papert.
    
- [ ] d) Todos los anteriores.
    
- [ ] e) Ninguno de los anteriores.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Los precursores biológicos son aquellos investigadores procedentes de la fisiología o la neurociencia que sentaron las bases orgánicas que más tarde la IA intentaría emular computacionalmente. A finales del siglo XIX, Santiago Ramón y Cajal describió la estructura fundamental de la neurona, proponiendo las teorías esenciales sobre las que se asientan hoy en día todos los desarrollos de los sistemas adaptativos de emulación. Por el contrario, autores como Marvin Minsky y Seymour Papert no fueron precursores biológicos, sino que en 1969 publicaron el libro "Perceptrons", en el cual demostraron las limitaciones matemáticas del perceptrón, desautorizando el modelo conexionista y provocando el conocido como "invierno de la IA".

### 7. Causas del interés actual por los sistemas subsimbólicos

¿Causas del interés actual por los Sistemas Inteligentes Subsimbólicos?

- [ ] a) El interés existente por la búsqueda de arquitecturas de computadoras que permitan el procesamiento en paralelo.
    
- [ ] b) La habilidad de estos sistemas para aprender automáticamente.
    
- [ ] c) La habilidad para poder funcionar de forma aceptable tanto en presencia de información inexacta como cuando se producen deterioros o fallos en sus componentes.
    
- [ ] d) Su similitud con los modelos neurofisiológicos del cerebro, pudiéndose de este modo intercambiar modelos e investigaciones entre los de RNA y Neurociencias, potenciándose ambas.
    
- [ ] e) Todas las anteriores son correctas
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Los sistemas conexionistas (rama subsimbólica) han experimentado un inmenso resurgir en las últimas décadas gracias a sus innegables ventajas. Estas redes neuronales destacan por su capacidad intrínseca para aprender y extraer patrones automáticamente de grandes volúmenes de datos (sin necesidad de reglas explícitas programadas). Además, a diferencia de la IA simbólica clásica, su conocimiento se distribuye en los pesos de las conexiones, otorgándoles una gran robustez y tolerancia a fallos, permitiéndoles operar eficazmente frente a ruido o componentes dañados. Asimismo, el auge del procesamiento paralelo encaja perfectamente con su arquitectura. Finalmente, la retroalimentación y similitud con la fisiología humana permite grandes sinergias científicas con las Neurociencias.

### 8. IA y su relación con otros avances tecnológicos

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
> La Inteligencia Artificial actúa en la actualidad como la principal fuerza impulsora que subyace y potencia al resto de las grandes tendencias tecnológicas. Las impresoras 3D/4D y la fabricación aditiva están siendo transformadas radicalmente gracias a la co-creatividad impulsada por máquinas. Las realidades virtuales extendidas (como el Metaverso o los Gemelos Digitales) dependen de la IA para generar simulaciones inmersivas y modelar comportamientos predictivos en objetos físicos. Igualmente, las tecnologías convergentes NBIC (Nanotecnología, Biotecnología, Tecnologías de la Información y Ciencias Cognitivas) aplican algoritmos inteligentes, como la bioinformática y las redes neuronales, para resolver retos complejos como el análisis de procesos patológicos o interfaces cerebro-máquina (ej. Neuralink).

### 9. El núcleo de la mayoría de los avances tecnológicos

¿Qué está en el "Core" de la mayoría de los avances tecnológicos?

- [ ] a) Las potentes infraestructuras de cómputo.
    
- [ ] b) Las dos ramas de la IA: simbólica y subsimbólica
    
- [ ] c) Los humanos proponiendo nuevos avances
    
- [ ] d) Todas las anteriores son correctas
    
- [ ] e) Ninguna de las anteriores es correcta
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> Aunque a simple vista podríamos pensar que es la Inteligencia Artificial en general (lo que daría por buena la opción B), el temario y los exámenes de la UDC son muy tajantes en este matiz: el resurgir masivo que ha provocado la actual "Tercera Primavera de la IA" y que sustenta el núcleo ("core") de las disrupciones tecnológicas (como Deep Learning o Big Data) pertenece de forma única y exclusiva al paradigma de la **IA Subsimbólica** o Conexionista. Como la opción B mezcla ambas ramas por igual y la rama subsimbólica pura no aparece aislada en ninguna opción, la respuesta oficial dictada por la lógica de la materia es la E.

### 10. El Régimen de Lovelace y el origen de las ideas

¿Quién establece que: "las máquinas sólo pueden hacer todo aquello que sepamos cómo ordenarle que haga"?

- [ ] a) Ramón Llull.
    
- [ ] b) Ada Lovelace.
    
- [ ] c) Newell y Simon.
    
- [ ] d) Leibniz.
    
- [ ] e) Turing.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> Este célebre axioma histórico se conoce académicamente como el "Régimen de Lovelace". Ada Lovelace, pionera de la computación, argumentaba que las máquinas analíticas carecían de iniciativa propia o creatividad, limitándose a ejecutar mecánicamente las rutinas matemáticas explícitas que el humano les hubiera programado.

### 11. El conjunto de entrenamiento en una RNA

El conjunto de datos que se utiliza para establecer los valores de los pesos de las conexiones de una RNA se denomina:

- [ ] a) Conjunto de prueba
    
- [ ] b) Conjunto de validación
    
- [ ] c) Conjunto de test
    
- [ ] d) Conjunto de entrenamiento
    
- [ ] e) Conjunto de normalización
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> El "Training Set" o conjunto de entrenamiento es la porción de datos sobre la que iteran los algoritmos de corrección (como el descenso del gradiente). Es el único bloque de datos autorizado matemáticamente para interactuar con la red y modificar/ajustar de forma directa las intensidades de sus pesos sinápticos.

### 12. Significado de un gradiente de cero en el entrenamiento

Si durante el entrenamiento de una RNA, en un ciclo se obtiene un gradiente de 0, esto quiere decir...

- [ ] a) Se está muy lejos de un mínimo.
    
- [ ] b) Se está muy cerca de un mínimo, pero no en él.
    
- [ ] c) Se está en un mínimo, y es el global.
    
- [ ] d) Se está en un mínimo, pero no se sabe si es el global o uno local.
    
- [ ] e) El error es 0.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Durante el proceso de entrenamiento de una RNA (por ejemplo, mediante descenso de gradiente), el algoritmo evalúa la superficie de la función de error e itera modificando los pesos para descender por ella. Cuando se alcanza un punto donde la pendiente de la tangente (el gradiente) es exactamente igual a 0, el algoritmo determina que se encuentra posicionado en un mínimo de la función y cesa de actualizar los pesos. No obstante, debido a la topología y no linealidad de la superficie del error en redes complejas (y dado que la inicialización de los pesos es puramente aleatoria), el algoritmo es susceptible a quedarse atrapado y no puede garantizar matemáticamente si dicho valle corresponde al mínimo absoluto y óptimo (global) o simplemente a un valle secundario (mínimo local) en el cual el error sigue siendo alto. Es erróneo afirmar que el error sea cero, puesto que llegar a un error de cero suele ser sinónimo de sobreentrenamiento y de que la red ha memorizado el ruido.

### 13. Limitaciones lógicas del perceptrón simple

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
> A pesar del gran interés generado por el perceptrón simple en sus inicios en los años 60, los investigadores Minsky y Papert demostraron matemáticamente que las redes compuestas por una única capa de pesos adaptativos adolecen de una severa limitación computacional: únicamente son capaces de clasificar y aprender ejemplos que sean estrictamente separables de forma lineal mediante una línea recta o un hiperplano en el espacio. El problema lógico de la puerta EXOR (OR Exclusivo) es el paradigma por excelencia de un conjunto de datos que se cruza espacialmente y, por tanto, no es linealmente separable; lo que hace completamente imposible que un perceptrón sin capas ocultas pueda resolverlo.

### 14. Capa de entrada en un perceptrón multicapa

El número de neuronas de entrada de un perceptrón multicapa

- [ ] a) Lo puede fijar el usuario como quiera
    
- [ ] b) Depende del problema a resolver
    
- [ ] c) Debe ser igual al número de neuronas de salida, y lo puede fijar el usuario como quiera
    
- [ ] d) Debe ser igual al número de neuronas de salida, pero depende del problema a resolver
    
- [ ] e) Debe ser distinto al número de neuronas de salida
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: b)**
> 
> En la arquitectura funcional de un perceptrón multicapa, la capa de entrada es un mero canal pasivo cuya función exclusiva es la de recibir e introducir los estímulos externos al sistema. Por lo tanto, el número de células que conformarán esta capa de entrada no se escoge por capricho ni tiene por qué coincidir con las dimensiones de salida, sino que está estricta e inexorablemente determinado por el número de variables, características (features) o dimensiones de los patrones del problema específico que se pretende resolver o clasificar.

### 15. Función de transferencia en redes multicapa

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
> Para que un perceptrón multicapa sea capaz de superar las deficiencias del perceptrón simple, extraiga características complejas y actúe verdaderamente como un "aproximador universal", es matemáticamente indispensable que las funciones de transferencia que operen en sus capas ocultas incorporen no linealidad (tales como funciones de tipo sigmoidal o tangente hiperbólica). Sin embargo, afirmar que "solamente" pueden ser de un tipo específico es falso, debido a que la arquitectura permite combinar de manera muy flexible diferentes funciones de activación dentro del mismo sistema. Por ejemplo, en los problemas de regresión continua es una práctica estándar y óptima incorporar funciones no lineales en las capas ocultas y una función puramente lineal en la capa de salida.

### 16. Comportamiento ante patrones en zonas sin entrenamiento

Si a un perceptrón multicapa entrenado se le presenta un patrón en una zona donde no había patrones de entrenamiento...

- [ ] a) Dará error en su funcionamiento
    
- [ ] b) Dará una salida de 0 siempre
    
- [ ] c) Dará una salida de -1 siempre
    
- [ ] d) Dará una salida de 1 siempre
    
- [ ] e) Dará una salida arbitraria e imprevisible
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: e)**
> 
> El objetivo supremo del aprendizaje en una Red Neuronal no es memorizar, sino adquirir la capacidad de generalizar de forma robusta ante patrones que jamás ha "visto". Cuando al perceptrón se le introduce un patrón de entrada que recae en un área del espacio de características que permanecía vacía y carente por completo de instancias durante la fase de entrenamiento, la red no cuenta con referencias, topología ni información estadística para trazar sus hiperplanos de decisión en esa zona ciega. En consecuencia, el sistema intentará extrapolar la respuesta de forma espuria basándose en fronteras lejanas aprendidas para otros datos, lo que irremediablemente desembocará en que se comporte mal y devuelva una salida completamente arbitraria e imprevisible.

### 17. Problema de los mínimos locales en descenso de gradiente

Entrenar una RNA mediante un algoritmo de entrenamiento basado en el gradiente descendente tiene el problema de que

- [ ] a) Nunca va a encontrar el mínimo global.
    
- [ ] b) Al acercarse a un mínimo, se va a oscilar de un lado a otro, sin lograr pararse en él.
    
- [ ] c) Se va a acercar a un mínimo con incrementos muy pequeños.
    
- [ ] d) Es posible que se quede parado en algún mínimo local.
    
- [ ] e) Va a necesitar un número muy alto de ciclos para alcanzar un error aceptable.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> En las técnicas de entrenamiento supervisado fundamentadas en el descenso de gradiente (como el backpropagation clásico), el algoritmo busca minimizar la función de error partiendo de un punto aleatorio y "resbalando" por la superficie matemática guiándose por la pendiente de la tangente. Sin embargo, el gran inconveniente intrínseco a este método analítico es su susceptibilidad topológica: una vez que la red alcanza un punto de la superficie donde el gradiente es 0 (un mínimo), el aprendizaje cesa de inmediato, sin que el modelo disponga de la visión global necesaria para discernir si realmente ha encontrado la solución óptima absoluta (mínimo global) o si ha quedado fatalmente atrapado en un pozo secundario (mínimo local) donde la tasa de error sigue siendo inaceptablemente alta.

### 18. Valoración de la generalización en una RNA

Para valorar cómo de bien está entrenada una RNA (y lo bien que generaliza), es necesario mirar el error

- [ ] a) En el conjunto de entrenamiento
    
- [ ] b) En el conjunto de validación
    
- [ ] c) En el conjunto de test
    
- [ ] d) En el ciclo de entrenamiento con menor gradiente
    
- [ ] e) En el ciclo de entrenamiento con menor error de entrenamiento
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Para garantizar el rigor científico y evitar que la Red Neuronal Artificial haya memorizado espuriamente los datos o su ruido (sobreentrenamiento), el proceso debe dividirse en tres conjuntos de patrones. El conjunto de entrenamiento guía los pesos y el conjunto de validación supervisa y detiene el aprendizaje; no obstante, como ambos "intervienen" o influyen en las decisiones arquitectónicas, no son objetivos. La verdadera y única manera de comprobar cómo de bien entrenada está la máquina y medir fielmente su capacidad de generalización (es decir, cómo se comporta frente a la incertidumbre del mundo real) consiste en procesar y analizar el nivel de error sobre un conjunto de test estricta y absolutamente virgen, que bajo ninguna circunstancia ha intervenido ni en el ajuste de pesos ni en la parada temprana del algoritmo.

### 19. La técnica de parada temprana (Early Stopping)

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
> El método de parada temprana surge como la solución técnica más robusta para evitar el sobreajuste (over-fitting) cuando un modelo es excesivamente complejo o se somete a demasiados ciclos de computación. Durante este proceso, a la vez que la red entrena y disminuye su error interno, un monitor evalúa el desempeño paralelo con un subconjunto de datos disjunto (validación). La estrategia consiste en dejar que la red entrene exhaustivamente pero memorizando su mejor estado histórico; de modo que, si el error en validación comienza a divergir (empeorar) por causa de que el sistema empieza a memorizar el ruido, el algoritmo retrocederá en el tiempo y se forzará al sistema a devolver única y exclusivamente la topología congelada y los pesos exactos de aquel ciclo que arrojó el menor error de validación, y no los de su iteración final o última.

### 20. Clasificación dicotómica y neuronas de salida

Para usar una RNA para resolver un problema de clasificación con dos clases, sin posibilidad de que un patrón no pertenezca a alguna de las dos clases, el número de neuronas de salida que hay que usar, según lo visto en las clases de teoría, es:

- [ ] a) 1
    
- [ ] b) 2
    
- [ ] c) 3
    
- [ ] d) 4
    
- [ ] e) 5
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> En una clasificación estrictamente binaria o dicotómica (o eres de la clase A, o eres de la clase B, sin espacio para ambigüedades), basta con colocar una única neurona en la capa de salida. Si su función de transferencia (ej. escalón o sigmoide) devuelve un valor bajo (0), representa a la primera clase; si devuelve un valor alto (1), representa a la segunda.

### 21. Capa de competición en mapas autoorganizativos

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
> Como su propio paradigma indica, el aprendizaje en los mapas autoorganizativos es no supervisado y competitivo. Cuando un vector de datos entra en la red, las neuronas de la capa de salida calculan su distancia euclídea hacia ese dato y libran una competición matemática. La más cercana se proclama vencedora (BMU) y gana el derecho exclusivo de actualizar sus pesos y los de sus vecinas.

### 22. El error de cuantización medio en redes SOM

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
> Dado que los Mapas Autoorganizativos (SOM) operan en el campo del aprendizaje automático "no supervisado", carecen por completo de etiquetas de salida deseada para el vector, lo que imposibilita matemáticamente el uso del clásico Error Cuadrático Medio. Como alternativa de validación en este paradigma, se utiliza el Error de Cuantización. Este parámetro funciona como una medida de adaptación geométrica que evalúa cuán fiel es el mapa resultante analizando todos los patrones y sumando la distancia matemática existente entre cada uno de los vectores reales de entrada procesados y sus respectivos prototipos seleccionados por similitud en la matriz, esto es, sus correspondientes unidades ganadoras o BMUs (Best Matching Units).

### 23. La neurona ganadora (BMU) en redes SOM

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
> La esencia del modelado espacial de Teuvo Kohonen es el aprendizaje competitivo puro. En la fase de entrenamiento, cada vez que la capa de entrada estimula al sistema con un vector u objeto analítico nuevo, la totalidad de las neuronas que componen la capa de competición paralela o malla SOM ejecutan simultáneamente cálculos de distancia (típicamente Euclídea). Tras este cálculo de similitud, la neurona de salida que alcance la menor distancia geométrica o matemática con los valores dimensionales del citado patrón de entrada será coronada unívocamente como la célula ganadora o BMU. Esta condición de victoria es la que le otorgará el derecho exclusivo a actualizar sus pesos analíticos y arrastrar topológicamente a las células adyacentes de su vecindario local.

### 24. Similitud matemática en mapas de Kohonen

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
> La métrica estándar implementada en el motor geométrico de las redes SOM para medir cuán alejado o similar es el vector de pesos de una neurona frente al vector ambiental de entrada, es la fórmula de la distancia euclídea clásica.

### 25. Problemas y limitaciones de las redes SOM

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
> Dado que un mapa SOM despliega una cuadrícula de tamaño y topología fijos desde el inicio, si los pesos aleatorios iniciales de algunas neuronas caen en un lugar muy remoto respecto a donde se agrupan los datos reales, y el radio de vecindad se encoge rápidamente, dichas neuronas nunca llegarán a ganar la competición. Quedan como "neuronas muertas" o desperdiciadas, un defecto que arquitecturas posteriores como las GNG solucionaron.

### 26. Tamaño del vecindario durante el aprendizaje SOM

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
> Para garantizar la estabilidad del mapa, el entrenamiento se divide en fases. En la fase inicial de ordenación, el radio de vecindad es muy amplio para organizar la topología globalmente. Sin embargo, conforme avanza el tiempo (fase de convergencia), el tamaño de este vecindario se encoge de manera progresiva y asintótica, permitiendo así que la red realice ajustes finos y precisos en sus prototipos sin desestabilizar a todo el grupo.

### 27. Fase de operación de una red SOM

En la fase de operación de una red SOM:

- [ ] a) Se modifican los pesos de las neuronas.
    
- [ ] b) Se entrena la red con nuevos datos.
    
- [ ] c) Se categoriza un patrón según la neurona más similar.
    
- [ ] d) Se actualiza la topología de la red.
    
- [ ] e) No intervienen las neuronas de entrada.
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> Una vez finalizada la fase de entrenamiento, la arquitectura de pesos de la red se "congela" y entra en su fase operativa o productiva. En este estado ya no hay aprendizaje ni actualización topológica; la red actúa como un sistema de mapeo pasivo, limitándose a recibir nuevos datos de entrada y proyectarlos o categorizarlos en la neurona vencedora que resulte estadísticamente más cercana.

### 28. Significado del vector de pesos de una neurona SOM

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
> Gracias al empuje del aprendizaje competitivo, las neuronas del mapa acaban desplazándose hacia los núcleos de densidad de la nube de datos. Como resultado, cada vector de pesos encapsula las características medias de esa región, convirtiéndose matemáticamente en un centroide o "prototipo representativo" que agrupa a todos los patrones similares de su entorno.

### 29. Aplicaciones adecuadas para mapas autoorganizativos

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
> Las redes Mapas Autoorganizativos, inspiradas en los mapas espaciales de la corteza fisiológica, ostentan como máxima utilidad técnica la reducción de dimensionalidad de datasets indescifrables. Siendo modelos que categorizan datos sin intervención de reglas supervisadas externas, son la opción superlativa y especializada para el análisis de componentes principales, clustering y segmentación (agrupamiento) de conjuntos vectoriales donde subyacen enormes volúmenes de características dimensionales, ya que pueden aplanar estas distribuciones abstractas sobre topologías gráficas bi o tridimensionales preservando la similitud, haciendo posible la visualización de los prototipos generados para el analista humano.

### 30. Diferencia de los modelos GCS frente a las SOM

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
> El talón de Aquiles de los modelos originarios de Kohonen (SOM) siempre ha sido su necesidad de establecer predefinidamente un tamaño y matriz fija y estática de neuronas (su topología rígida) antes de inyectarle los primeros datos, lo que en entornos vacíos da lugar a "neuronas muertas" desconectadas de las regiones de utilidad. Como profunda respuesta adaptativa frente a este fallo, surgieron las redes Growing Cell Structures (GCS) y el Gas Neuronal Creciente. Su diferencia crucial y paradigma vertebrador estriba en su asombrosa plasticidad o crecimiento orgánico, que les confiere el poder para insertar (agregar) o eliminar progresiva y dinámicamente neuronas operativas en los hiperplanos durante las fases mismas del entrenamiento, concentrando siempre sus recursos modulares en los nodos que presentan mayor índice de error topológico o cuantizado.

### 31. El término Fitness en Algoritmos Genéticos

La palabra "Fitness" en términos de un Algoritmo Genético es ...

- [ ] a) Es una forma de intercambiar material genético entre varios individuos de la población
    
- [ ] b) Una forma o función de construcción de los individuos para obtener la población
    
- [ ] c) Una operación genética que cambia la composición de los descendientes
    
- [ ] d) El valor que permite evaluar lo adaptado que está cada individuo de la población para obtener la solución del problema que pretende resolver
    
- [ ] e) Es una estrategia de mantener al mejor individuo y copiarlo directamente a la siguiente generación para evitar perder la mejor solución obtenida
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Dentro del paradigma evolutivo o de selección natural, la función de *Fitness* (aptitud) es el corazón métrico del algoritmo. Consiste en la fórmula matemática que examina a cada cromosoma (individuo) y le asigna una puntuación numérica que refleja directamente la bondad o calidad de su solución frente al problema planteado, dictaminando así sus probabilidades de sobrevivir y reproducirse en la siguiente iteración.

### 32. Técnicas de mutación en Computación Evolutiva

¿Cuál de las siguientes es una técnica de mutación en los Algoritmos Genéticos?

- [ ] a) Uniforme
    
- [ ] b) Máscara
    
- [ ] c) Intercambio
    
- [ ] d) Génesis
    
- [ ] e) Punto Flotante
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> En los cimientos de la Computación Evolutiva, las operaciones inspiradas en el darwinismo actúan manipulando los cromosomas (variables) para evadir óptimos locales. Opciones como "Uniforme" y "Máscara" hacen referencia de manual a los tipos clásicos de operadores de cruce (crossover), que combinan o barajan elementos entre dos progenitores para engendrar individuos en la descendencia. Asimismo, términos como "Punto Flotante" definen formas de representación semántica y tipados numéricos (codificación de individuos), mientras que la génesis no es un operador. La mutación por Intercambio (o Swap Mutation) es por consiguiente una técnica formal y validada en esta rama, de gran uso particular en problemas de optimización estocástica y enumeración, que garantiza el aporte brusco de variabilidad permutiendo o cambiando aleatoriamente la ordenación interna genotípica en el alelo de un solo individuo aislado.

### 33. Representación mediante árboles en Programación Genética

En Programación Genética,

- [ ] a) El cromosoma nunca representa la posible solución a las variables del problema
    
- [ ] b) Se aplican los operadores de cruce y mutación para invertir la población de cromosomas
    
- [ ] c) La forma de representar los individuos es mediante un árbol, siendo la principal diferencia con los Algoritmos Genéticos
    
- [ ] d) La forma de codificar los individuos es igual a los Algoritmos Genéticos, cambia la forma de aplicar el cruce y la mutación
    
- [ ] e) No existe ninguna técnica en Computación Evolutiva denominada Programación Genética
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> La Programación Genética es una subdisciplina de la Computación Evolutiva que surge como una evolución de los propios algoritmos genéticos clásicos, compartiendo con estos el mismo principio biológico de selección natural. Sin embargo, la mayor y principal diferencia arquitectónica entre ambas radica en la forma de codificación de la solución al problema. Mientras que en los Algoritmos Genéticos convencionales los individuos o posibles soluciones se estructuran mediante vectores o cadenas planas de variables, en la Programación Genética la representación se realiza unívocamente en forma de árbol sintáctico. Esta topología arbórea es análoga a la manera en que los compiladores analizan los lenguajes, situando funciones/operadores en los nodos internos y los terminales (variables o constantes) en las hojas.

### 34. Hibridación de Algoritmos Genéticos y búsqueda local

El procedimiento de combinar el "Ascenso de colinas" o "hill-climbing" con los Algoritmos Genéticos

- [ ] a) Es una técnica de búsqueda donde su principal problema es la convergencia prematura
    
- [ ] b) Es una técnica de búsqueda aplicada en los algoritmos genéticos donde su principal problema es que no garantiza la obtención del óptimo global
    
- [ ] c) Sólo se puede aplicar en programación genética.
    
- [ ] d) Está inspirada en los principios de evolución de Lamark para mejorar la convergencia del proceso evolutivo.
    
- [ ] e) Es una técnica que realiza una búsqueda aleatoria en el espacio de soluciones hasta encontrar el máximo o mínimo global
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: d)**
> 
> Los Algoritmos Genéticos son excelentes explorando de forma global el espacio de soluciones, pero tienen deficiencias a la hora de realizar la convergencia final y fina (explotación) hacia el punto óptimo absoluto. Para solventar esta carencia, se suele dotar a los individuos del algoritmo de una técnica de búsqueda u optimización local como el "escalado o ascenso de colinas" (hill-climbing). Cuando un individuo "aprende" o mejora sus características gracias a esta búsqueda local durante su evaluación, y transmite este nuevo material biológico mejorado a su descendencia en la población, se está emulando directamente la teoría de la evolución de Lamarck, basada históricamente en la "herencia de los caracteres adquiridos". Esta hibridación (conocida como aprendizaje lamarckiano o algoritmos meméticos) mejora dramáticamente la velocidad y convergencia del proceso evolutivo.

### 35. Aprendizaje Lamarckiano en Algoritmos Genéticos

En un algoritmo genético, ¿qué nombre recibe el proceso por el cual el mejor individuo de la población recibe una fase de ajuste local y es insertado de esa manera en la población?

- [ ] a) Seeding
    
- [ ] b) Elitismo
    
- [ ] c) Aprendizaje lamarckiano
    
- [ ] d) Steady-state
    
- [ ] e) Hill-climbing
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: c)**
> 
> En directa correlación con los principios expuestos en la pregunta anterior, el darwinismo estricto postula que las experiencias o mejoras locales que sufre un individuo durante su vida (fenotipo) no alteran sus genes y, por lo tanto, no se heredan. Sin embargo, en Computación Evolutiva, si decidimos aplicar un ajuste local u optimización (por ejemplo, hill-climbing) a un individuo particular (típicamente el mejor o los mejores) para perfeccionarlo, y a continuación alteramos explícitamente su genotipo y es insertado de esa manera mejorada en la población para que transmita dichas virtudes, estamos aplicando formalmente el Aprendizaje Lamarckiano. Si este aprendizaje no se codificara de vuelta en el genoma, se denominaría efecto Baldwin, pero al ser insertado tal cual, se cataloga rigurosamente como lamarckiano.

### 36. Cálculo de transiciones de poblaciones en AG

En una población de 40 individuos, se aplica una tasa de cruce del 50 %, una tasa de mutación del 10 %, y se conserva un 20 % de los mejores individuos mediante elitismo. ¿Cuál de las siguientes combinaciones es correcta para cada generación?

- [ ] a) 20 individuos por cruce, 4 por mutación, 8 copiados sin cambios
    
- [ ] b) 20 individuos por cruce, 2 por mutación, 6 copiados sin cambios
    
- [ ] c) 18 individuos por cruce, 4 por mutación, 8 copiados sin cambios
    
- [ ] d) 16 individuos por cruce, 4 por mutación, 10 copiados sin cambios
    
- [ ] e) 20 individuos por cruce, 6 por mutación, 6 copiados sin cambios
    

> [!success]- Solución y Justificación
> 
> **Opción correcta: a)**
> 
> Para configurar adecuadamente la transición de las poblaciones en un Algoritmo Genético, los operadores de cruce, mutación y elitismo se manejan a nivel paramétrico indicando fracciones estadísticas. En este escenario con una población (N) de 40 individuos, los cálculos matemáticos para deducir el número de cromosomas involucrados en cada fase son los siguientes:
> Cruce (recombinación): Una tasa del 50 % implica que la mitad exacta de la población se someterá al cruce. 40×0.50=20 individuos formarán la descendencia por este método.
> Mutación: Una tasa o probabilidad del 10 % estipula que la décima parte de la población se verá afectada por modificaciones en sus genes (introducción de variabilidad). 40×0.10=4 individuos.
> Elitismo: Finalmente, al establecer que se conserva un 20 % de los mejores, estamos obligando al algoritmo a garantizar la preservación inalterada de la élite de la generación anterior (para no perder la mejor solución). 40×0.20=8 individuos que serán copiados directamente sin cambios a la siguiente generación. Por tanto, las cifras 20, 4 y 8 corresponden unívocamente a los postulados matemáticos de la opción A.
