## Metodología
Los aspectos fundamentales que cada metodología de gestión de proyectos debe contemplar son los siguientes:
- Definición de proyectos.
- Modelo genérico del ciclo de vida de los proyectos.
- Metodologías específicas por cada tipo de proyecto.

### Definición de un proyecto
La definición de proyecto debe adaptarse a las necesidades de cada organización. Cada organización establecerá lo que para ella es un proyecto o no.
Generalmente un proyecto es un conjunto de:
- Unos recursos humanos, materiales, financieros, etc.
- Una organización: relación entre actividades y recursos
- Una planificación: relación entre actividades, recursos y tiempo
- Unos productos: específicos a obtener con los elementos anteriores.
- Unos objetivos a alcanzar con los productos anteriores.
- Un entorno de riesgo en el que se desenvuelvan dichos elementos.

Como características, un proyecto es:
- Discreto: Con inicio y fin definidos, y un producto final a obtener.
- Completo: Con un conjunto de diferentes tareas interrelacionadas.
- Único: En relación a su producto final y a su entorno de desarrollo.
- No es un proceso cotidiano o rutinario.

La gestión del proyecto buscará la entrega de sus productos finales.
- Cumpliendo las especificaciones.
- En plazo.
- Dentro del presupuesto.
- Con los niveles de calidad correspondientes  a los estándares profesionales y a las expectativas.

### Modelo de ciclo de vida de un proyecto
![[Modelo de ciclo de vida de un proyecto.png]]

Las fases de la figura anterior reflejan básicamente la aproximación Information Technology Project Managment de KPMG Consulting:
- Fases propias:
	- Evaluación y aprobación del proyecto.
	- Planificación y puesta en marcha del proyecto
		- Identificar el requisito de trabajo.
		- Cuantificar requisitos de trabajo.
		- Identificar requisitos de recursos.
	- Ejecución del proyecto.
		- Planificación detallada del trabajo.
		- Organización de la infraestructura.
		- Organización de los recursos humanos.
		- Seguimiento y control.
			- Realizar el seguimiento del proyecto con respecto al plan.
			- Realizar los ajustes necesarios.
			- Analizar el impacto.
	- Finalización del proyecto.
- Fases adyacentes:
	- Gestión de la calidad.
	- Gestión de cambios.
	- Gestión de riesgos.

### Metodologías específicas
![[Metodologías específicas.png]]

### Recomendaciones:
Una efectiva gestión del proyecto sucede si se produce:
- Una planificación disciplinada:
	- Primero a  papel
	- Después con herramientas de soporte a la planificación .
- Realización del trabajo de acuerdo con estándares preestablecidos, incluyendo 
	- Trabajo relativo al proyecto.
	- Trabajo relativo a la gestión del proyecto.
- Mediciones adecuadas y evaluación de resultados.
- Acciones correctivas adecuadas.
- Liderazgo en los equipos.

Máxima a respetar: En general, la planificación y su seguimiento no pueden consumir más esfuerzo que el propio proyecto.

## Conceptos de panificación y seguimiento de proyectos
### Definiciones
Tarea/actividad: Es la unidad más elemental del nivel de planificación. Puede ser identificada por su duración, consumo de recursos o ambas cosas. Cada actividad es una parte independiente y homogénea del proyecto que, una vez comenzada, se realiza de forma independiente del resto, que le preceden y le siguen. Cada actividad conduce a la obtención de un resultado tangible a utilizar para el desarrollo de otras actividades del proyecto.

Evento/suceso: También denominados "milestones" o hitos, es un tipo de actividad especial que no tiene duración y sirve para indicar un acontecimiento, un momento particular e importante del proyecto susceptible de ser modelado. No consume recursos. Normalmente se utiliza para describir puntos de control. Suelen ser base de seguimiento y control espacial, se suelen usar ante eventos de terceras partes o subcontratas.

Recurso: Un elemento se considera como recurso si va a estar sujeto a compartición, posiblemente originando conflictos de uso.
Clases de recursos:
- Clasificación 1:
	- Humanos.
	- Materiales.
	- Maquinaria.
- Clasificación 2:
	- Consumibles: Se emplean en la realización de la actividad y no se reutilizan.
	- Recurrentes: Tienen capacidad de reutilización.

Muchos autores distinguen expresamente entre:
- Planificación -> establecimiento del plan.
- Programación -> planificación + asignación de recursos.

Calendarios: Algunas empresas pueden tener diferente calendario según los periodos. (p.e. bico de xeado en verano o invierno).

Duraciones: Dependiendo de la empresa y lo que planifique, las duraciones se establecerán en una determinada medida.

Esfuerzo: Medida de trabajo que hay que hacer por parte de los recursos.

Pool de recursos humanos y datos asociados: (p.e., id, nombre, OBS al que pertenece, coste por hora estándar, coste por hora extra y disponibilidad por unidad de duración).

### Técnicas más usuales
Técnicas de representación:
- Diagrama de Gantt
- Red de precedencia
- Histograma
  
Técnicas de estructuración:
- Work Breakdown Structure (WBS).
- Organisational Breakdown Structure (OBS).
  
Técnicas de programación:
- Program Evaluation and Review Technique (PERT)
- Critical Path Method (CPM).
  
Técnicas de seguimiento:
- Tiempo.
- Esfuerzo.
- Coste.

#### Diagrama de Gantt
Representa en una escala de tiempos cada una de las actividades mediante barras, que representan su duración en fechas de calendario. Es una representación simplificada de una red de procedencia.

#### Red de precedencia
Hasta los años 60 el diagrama de Gantt era prácticamente el único método  de planificación y control de proyectos. A finales de los años 50 aparecen técnicas basadas en grafos para la planificación de proyectos, estas técnicas permiten reflejar las relaciones que se dan entre las actividades de un proyecto: Relaciones de precedencia.
- El objetivo es establecer el las dependencias entre las distintas tareas del proyecto para saber de qué manera han de encadenarse dichas tareas en la planificación.
- Estas dependencias o prelaciones se establecen a partir de las actividades precedentes.
  
La red (grafo dirigido sin ciclos) obtenida por estas técnicas es un modelo gráfico que señala las relaciones de secuencia entre las actividades de un proyecto.
- Un análisis de esta red puede identificar el camino crítico de una planificación

Existen fundamentalmente dos técnicas para construir el diagrama de red o la red de de precedencia de un proyecto:
- PDM: Precedence diagramming method.
	- Utiliza nodos, para representar actividades, y vectores, que conectan los nodos representando las dependencias o relaciones lógicas.
	- Si una actividad A precede a otra B, existen 4 tipos de relaciones de precedencia: CC, CF, FC y FF
	- Es la técnica más empleada.
- ADM: Arrow diagramming method.
	- Utiliza vectores, para representar las actividades, y nodos, para indicar las dependencias entre actividades a través de manejo de hitos.
	- Hay tres tipos de relaciones de precedencia: lineales, de convergencia y de divergencia.
	- Es una técnica poco empleada.

#### Histograma
Es un diagrama de barras que muestra de forma visual la distribución de datos cuantitativos de una misma variable. Es típico el histograma de recursos para mostrar la asignación de recursos a lo largo del tiempo y ver sobre e infrautilizaciones.

#### WBS y OBS
Work Breakdown Structure:
- Técnica que consiste en estructurar las tareas de un proyector por tipos, por niveles de agregación, etc.
- Estructura de descomposición/desglose de un proyecto en actividades y con diferentes niveles de detalle.

Organisational Breakdown Structure:
- Técnica que consiste en estructurar la organización de un proyecto por las unidades organizativas, e incluso personas, que poseen responsabilidad sobre la realización del proyecto.
- Refleja cómo están organizadas las diferentes áreas de una organización en términos de responsabilidad funcional.

#### PERT y CPM
PERT se orienta a los eventos o sucesos mientras que CPM se orienta a las actividades. PERT permite considerar la probabilidad mientras que CPM no.
PERT:
- Permite estimar la duración de tiempo de un proyecto partiendo de la secuencia de actividades y de una estimación ponderada de la duración de cada actividad.
- La duración de cada actividad se calcula como una medida ponderada de tres valores $\frac{Optimista + 4 \times Más probable + Pesimista} {6}$, en lugar de sólo el valor más probable empleado en CPM.

CPM:
- Permite calcular la lista de actividades con menor flexibilidad en su ejecución: un retrato en una de ellas implica obligatoriamente un retraso en la duración del proyecto.
- Permite obtener las fechas mínimas esperadas y fechas máximas permitidas, de comienzo y finalización, de las tareas.
	- Se calculan a partir de las duraciones e interdependencias de las mismas.
- Camino crítico: conjunto de tareas que poseen holgura total mínima; esto es, 0 (diferencia entre las fechas más tardías y las fechas más tempranas).

##### PERT
Los pasos ordenados de la técnica PERT son los siguientes:
- Elaboración de la red de precedencia a partir de una WBS elaborada para el proyecto.
- Cálculo de los tiempos PERT:
	- Tiempo pesimista (Tp): tiempo máximo en el que se finalizará la actividad.
	- Tiempo optimista (To): tiempo mínimo si no surge ningún problema.
	- Tiempo más probable (Tmp): tiempo normal de duración de la actividad.
	- Cálculo del tiempo PERT para cada actividad; suponiendo una distribución de probabilidad beta, la duración esperada es: $\frac{To + 4xTmp + Tp}{6}$.
- Cálculo de los tiempos más tempranos posibles (early).
- Cálculo de los tiempos más tardíos posibles (late).
- Cálculo de las holguras.
- Determinación del camino crítico.
	- Pueden existir varios caminos críticos, desde el principio hasta el fin del proyecto.
	- Cualquier retrato en una actividad crítica afecta a todo el proyecto.
	- Si una actividad no crítica consume su holgura total se convierte en crítica, crea un nuevo camino crítico.
- Definición de fechas más tempranas y tardías de comienzo y finalización.

##### CPM
Los pasos ordenados de la técnica CPM son los siguientes:
- Elaboración de la red de precedencia a partir de una WBS elaborada para el proyecto.
- Identificar todos los posibles caminos dentro del grafo dirigido desde el principio al fin del proyecto.
- Calcular los tiempos totales de cada camino.
- Identificar el camino crítico: el que tenga mayor duración.
- El significado de camino crítico, fechas early, fechas late, etc. es completamente equivalente al expresado anteriormente al hablar de la técnica PERT.


# Faltan diapos


## Entorno Organizativo

Deben de ser parte de un procedimiento o manual dentro de cada organización. El contenido debiera contemplar al menos lo siguiente:
- Una estructura de órganos y responsabilidades.
- Unas normas y políticas de actuación.
- Un conjunto de procedimientos administrativos. Por ejemplo:
	- Una hoja de tiempos.
	- Distribución de informes.
- La o las técnicas, herramientas y estándares de planificación a emplear y la forma de operar con ellos.

![[Informes de seguimiento.png]]

## Planificación sí, pero ¿cómo?
Idealmente:
- Elaborar una estimación, empleando métodos de estimación.
- Elaborar una planificación, empleando la estimación anterior.
- Controlar y hacer seguimiento de la planificación elaborada.
	- Elaborar una planificación nueva si fuera necesario.

En la realidad:
- Jefes, clientes, situaciones, representantes de partes, etc. pueden exigir unos plazos (por ejemplo, aunque es lo más habitual) en la planificación que no se ajusten a los plazos elaborados en base a los pasos anteriores.

Por lo tanto:
- Necesitamos aprender cómo lograr que la planificación basada en métodos de estimación sea aceptada en lugar de fechas impuestas inalcanzables, excesivamente optimistas, poco realistas o viables.

## Planificación excesivamente optimista
Robert L. Glass: "Trabajar con planificaciones imposibles es el mayor problema en sistemas de información".
Sin embargo, este problema no es algo moderno.
Las planificaciones del software excesivamente optimistas son una tradición en el desarrollo de software:
- En 1970, Fred Brooks: "Hay más proyectos software que han salido mal por falta de tiempo que por todas las otras causas combinadas".
- En 1984, Scott Costello "La presión de la fecha límite es el principal enemigo de la Ingeniería del Software".
- En 1994, Capers Jones "Las planificaciones excesivas o irracionales representan probablemente la influencia más destructiva de todas las que afectan al software".

Consecuencias:
- A nivel local:
	- Anima la toma de atajos y soluciones rápidas, poco pensadas y, a la larga, costosas en proyectos específicos.
	- Perjudica a estos proyectos específicos en: costes, calidad e integridad del producto.
- A nivel global:
	- Contribuye a una mentalidad paradójica sobre la presión en la planificación: los recursos ven esta presión como un problema exclusivo de su proyecto actual, aunque la han sufrido en todos los proyectos en los que han estado y ha sido una característica del desarrollo de software desde sus inicios.

Steve McConnell: hay tres factores que conllevan al núcleo de los problemas asociados a las planificaciones excesivamente optimistas:
- Ilusiones: Clientes, responsables y usuarios finales desean natural y lógicamente obtener el máximo partido a su inversión y lo antes posible. La mayoría de las planificaciones de los proyectos software son ambiciosas, no de tipo medio.
	- Lo anteriormente indicado debería bastar para abandonar las ilusiones sobre las planificaciones excesivamente optimistas del software.
- Pocos conocimientos de estimación, su historia o de los efectos de no emplearla correctamente: Es imposible lógicamente poder estimar correctamente el software en sus estados iniciales. Aún encima, no podemos permitir que nos fuercen a estimaciones poco realistas.
	- Los datos de la historia de la estimación sirven de ayuda para este problema.
- Poca habilidad para negocias: En 1981, Philip Metzger observó que los desarrolladores eran bastante buenos  en las estimaciones, pero eran malos defendiéndolas.
	- Vamos a intentar poner remedio a este problema en este apartado.

## Negociación
Los desarrolladores tienden a ser malos negociadores por una serie de razones:
- Suelen ser introvertidos:
	- 3/4 partes de los desarrolladores son introvertidos, pero sólo 1/3 de la población en general se puede considerar como tal.
	- La mayoría de los desarrolladores se llevan bien con las demás personas, pero las relaciones sociales y la comunicación interpersonal no son su fuerte.
- Suelen ser jóvenes y sin experiencia en negociaciones:
	- Las planificaciones del software normalmente se establecen mediante negociaciones entre desarrollo y gestión/marketing. En 1994 Gerald Weinberg analizó que el personal de gestión/marketing suele ser 10 años mayor y su misión fundamental es negociar: negociadores maduros y profesionales.
- Los desarrolladores tienden a oponerse enérgicamente a los trucos de negociación por sus convicciones de calidad y claridad técnica:
	- No ofrecen estimaciones iniciales desproporcionadas incluso sabiendo que los clientes, vendedores o responsables comenzarán a regatear.
### Negociación conveniente
Método de negociación descrito en el libro "Getting to yes", de Roger Fisher y William Ury (1981) <br>
No trata sobre el software, pero es muy buen punto de partida. El libro surge del trabajo y se centra en la negociación ventajosa para todos, frente a otros libros de negociación que contienen principalmente trucos para anular al otro bando. No confía en trucos de negociación, pero explica cómo responder a ellos cuando otros los utilizan.<br>
Se basa en:
- Crear alternativas satisfactorias para todas las partes.
- No intenta derrotar a la persona con la que se negocia.
- Intenta cooperar de forma que ambas partes de la negociación puedan ganar.
- Es una estrategia abierta.
- No tiene miedo a que la otra parte conozca este método. De hecho, funciona mejor cuando ambas partes lo conocen y emplean.

La estrategia de negociación conveniente consta de 4 partes que tratan sobre PERSONAS, INTERESES, OPCIONES y CRITERIOS:
- Separar las **personas** del problema.
- Centrarse en los **intereses**, no en las posiciones.
- Inventar **opciones** para beneficios mutuos.
- Insistir en la utilización de **criterios** objetivos.

A continuación se describen cada una de estas cuatro partes...

### Separar las personas del problema
Todas las negociaciones involucran personas y luego intereses y posiciones:
- Si las personalidades de los negociadores son diferentes, las negociaciones pueden estar condicionadas por las diferencias de personalidad.
- Hay que comprender la posición y postura del lado contrario.
- Hay que intentar no personalizar las posiciones y posturas.
- La mayoría de las personas no son estúpidas o irracionales cuando insisten en una postura (e.g una fecha de entrega imposible).
	- La postura puede deberse a que no conocen suficientemente el trabajo para saber que es imposible su postura o que ellos a su vez tengan presiones.
- ¿Qué hacer?
	- Trabajar para mejorar la relación con otra parte y entender el motivo de su postura.
	- Trabajar para establecer expectativas realistas y evitar meterse en la piel de la otra parte.
	- Sugerir cambios que permitan acercar ambas posturas, pero no simplemente acercando la postura de uno a la postura de otro.
### Centrarse en los intereses, no en las posiciones
- Las posiciones son premisas de negociación que son tan estrictas que para que una gente gane la otra tiene que perder.
- Nunca negociar centrándose en las posiciones, sino en los intereses que hay detrás de las posiciones:
- Los intereses subyacentes a las posiciones son más amplios que dichas posiciones de negociación y si se centra la negociación en ellos se pueden abrir muchas posibilidades de negociación.
- En planificación, muchas veces se exige una fecha de entrega para todo el producto cuando no es necesario.

### Inventar opciones para beneficios mutuos
La negociación NO es un juego donde una parte gana a expensas de otra, que pierde.
Una negociación inteligente consiste en un ejercicio creativo para resolver un problema: Un negociador realmente bueno e inteligente encontrará la forma en que ambas partes ganen.
Para un técnico, esta parte es muy importante, pues tiene la capacidad de generar opciones creativas que la otra parte no puede por su falta de conocimientos.
- Esto es una ventaja, pero también es una responsabilidad, explicar el rango completo de posibilidades y compromisos.

Aplicando esta parte a la planificación de proyectos software, posibles opciones técnicas serían:
- Entrega del producto incremental priorizando las prestaciones: ciclos de desarrollo evolutivos.
- Eliminación de prestaciones considerando integraciones con otros sistemas.
- Reducción de prestaciones, implementándola sólo hasta cierto punto.
- Empleo de componentes comerciales preconstruidos, aunque no se ajusten ahora exactamente a lo solicitado.
- Etc.


Estas directrices buscan una atmósfera creativo y cooperativa por ambas partes. En esta dinámica, muchas veces sucede que:
- Se accede y acuerda una solución que parece una buena idea en el momento, pero cuando se analiza con cuidado no es buena, no es fácil, etc...

**Las partes no deben comprometerse firmemente con las nuevas opciones hasta que se hayan podido analizar tranquilamente de forma individual.**
**En todo el proceso debe centrarse uno en lo que puede hacer, evitando bloquearse en lo que no puede hacer.**
### Insistir en la utilización de criterios objetivos
Para eliminar los bloqueos en negociaciones convenientes, es clave uso de criterios objetivos que se puedan utilizar para dicha eliminación.
Esto supone:
- Presentar criterios objetivos.
- Mantener la mente abierta a criterios que sean sugeridos.
- Discutir con la otra parte qué criterios son los más adecuados.
- No ceder a la presión sino sólo a los principios

En desarrollo software suele suceder que cuando una estimación cuidadosa en base a métodos de estimación objetivos produce estimaciones no deseadas, el cliente/gerente simplemente la obvia.
- Cuestionar una estimación es una actitud válida y útil. Obviarla y sustituirla por ilusiones, no.
- Directrices para centrar las negociaciones de planificaciones de software en los principios y no sólo en los deseos:
	- No negociar la propia estimación, aunque sí los que se emplean para estimar, no se puede modificar la salida del proceso sin cambiar las entradas.
	- Insistir en que la estimación sea preparada por alguien cualificado.
	- Insistir en seguir un procedimiento de estimación racional
		1. Comprometerse con los requisitos antes que con la estimación.
		2. Proporcionar estimaciones cada vez más ajustadas conforme avance el proyecto.
		3. Volver a estimar si se cambian los requisitos.
#### ¿Qué más?
Ya sabemos cómo negociar, pero ¿hace falta algo más para negociar?
Sí: **Comunicarse correctamente**.
La comunicación es fundamental y no sólo para negociar, sino también para comunicarse y relacionarse con:
- Compañeros de trabajo.
- Compañeros de equipo de proyecto.
- Clientes.
- Jefes.
- Etc.

A continuación veremos algunos aspectos de la comunicación:
- Habilidades de comunicación: comunicación eficaz.
- Comunicación asertiva, que lo que busca es precisamente una comunicación eficaz.

### Comunicación eficaz
Premisa: La comunicación eficaz entre dos personas se produce cuando el **receptor interpreta el mensaje en el sentido que pretende el emisor**.
Para lograrlo hay que cuidar:
- Comunicación verbal
	- Se refiere a las palabras empleadas y a las inflexiones de la voz (tono y variaciones de voz).
- Comunicación no verbal:
	- Se refiere a un gran número de canales:
		- Contacto visual.
		- Gestos faciales.
		- Movimientos de brazos y manos.
		- Postura y distancia corporal.
		
La comunicación verbal es realmente importante, pero entre un 65% y un 80% del total de nuestra comunicación con los demás la realizamos a través de canales no verbales. Para comunicarse eficazmente, los mensajes verbales y no verbales deben coincidir: las palabras no pueden contradecirse con nuestra conducta no verbal.<br>
Técnicas de comunicación eficaz básicas:
- Escucha activa:
	- Hay que saber escuchar: no se escucha de forma automática (oír vs escuchar).
	- Las escucha activa significa escuchar y entender la comunicación desde el punto de vista del emisor. Es decir:
		- Entender, comprender o dar sentido a lo que se oye.
		-  Es la habilidad de escuchar no sólo lo que la persona está expresando directamente, sino también los sentimientos, ideas o pensamientos que subyacen a lo que se está diciendo.
	- Conviene mostrar que se está escuchando activamente:
		- Con comunicación verbal: "Ya veo", "Entonces...", "No me digas", parafrasear lo que se acaba de escuchar, etc.
		- Con comunicación no verbal: contacto visual (frecuente pero no exagerado), gestos, etc.
	- No conviene:
		- Mostrase distante: al contrario, se debe mostrar empatía.
		- No distraerse.
		- No interrumpir al emisor.
		- No ofrecer soluciones prematuramente.
		- No rechazar la actitud, sensación o sentimientos del emisor.
- No criticar al receptor: hablar de lo que se hace, no de lo que es.
- Discutir los temas uno a uno: no aprovechar para sacar otros.
- No acumular sensaciones: evitar explotar sacando todo de golpe.
- Rememorar el pasado sólo constructivamente: cosas que funcionaron/buenas/etc.
- Ser específico y concreto: evitar vaguedades y circunloquios y hacer propuestas concretas.
- Evitar generalizar: evitar los términos "todos", "nadie", "siempre", "nunca", etc.
- Ser breve: evitar alargarse, repetirse.
- Elegir el lugar y el momento correcto: críticas o reproches requieren estar a solas, elogios mejor delante del grupo del emisor o sus personas relevantes y saber emplazar para esa conversación en otro momento/lugar.

## Comunicación asertiva
La asertividad es una conducta humana altamente deseada que consiste en que al interactuar con los demás se debe ser:
- Directo.
- Honesto.
- Respetuoso.

Sin embargo, en el trabajo, en casa, con los amigos, etc., existen situaciones "incómodas", molestas, de tensión, etc. que hacen que normalmente la gente no tenga esa conducta.
Por ejemplo:
- Un compañero es muy injusto con tu trabajo.
- Un compañero "te traiciona" ante tu jefe.
- Un compañero no coopera en el proyecto.
- Un compañero te pide cosas poco razonables y quieres decir que no.
- Un compañero expresa opiniones completamente contrarias a las tuyas.

Las respuestas de la gente ante las situaciones y sensaciones anteriores pueden clasificar en tres tipos:
- Comunicación pasiva/sumisa:
	- "Soy inferior y mis derechos no cuentan".
	- No se expresan opiniones, intereses o deseos para evitar conflictos.
	- Es una conducta permisiva con la violación de los derechos de uno que puede acabar afectando al sujeto sumiso.
- Comunicación agresiva:
	- "Soy superior, más importante e impongo mis ideas sobre las de los demás".
	- Tiene una conducta de combatir que conlleva acusaciones, insultos, amenazas y/o peleas.
	- Es una conducta de control a los demás y conseguir lo que se quiere, aunque se ganen enemigos y se descontrole a menudo.
- Comunicación aservita:
	- "Soy igual a todos y todos somos igualmente importantes".
	- Expresión de opiniones, intereses o deseos al emisor respetando al mismo tiempo sus sentimientos.
	- **Es una conducta de cooperación y negociación** con la que se logra satisfacción propia y relaciones interpersonales satisfactorias.

Una persona con conducta asertiva:
- Manifiesta su propia postura ante un tema, petición o demanda, incluso diciendo NO.
- Expresa su razonamiento para explicar o justificar sus creencias, sentimientos, peticiones o accioens.
- Puede cambiar de opinión ante razonamientos que se le presenten.
- Expresa comprensión.
- Pide lo que necesita.
- Pide aclaraciones.
- Expresa gratitud, afecto, admiración, insatisfacción, dolor, desconcierto o sensaciones similares.

Puede emplear alguna de estas técnicas:
- "Mensajes YO".
- "Disco rayado".
- "Banco de niebla".
- Aplazamiento asertivo.
- Ignorar.
- Pregunta asertiva.

### Mensajes YO
Objetvios:
- Describir el comportamiento de la otra persona sin condenarlo.
- Describir el propio sentimienot que uno tiene.
- Describir objetivamente las consecuencias del comportamiento.
- Expresar lo que se quiere de la otra persona.

> [!example]
> "Cuando tú \[indicar comportamiento], yo me siento \[establecer sentimiento] porque \[establecer consecuencia]; por lo que por favor te pido \[establecer petición]."

### Disco rayado
Objetivos:
- Reiterar de forma persistente el mensaje central de lo que se quiere manifestar.
- Repetir de forma tranquila.
- Centrar la atención en el mensaje central sin permitir que otros elementos distraigan para conseguir otros objetivos.


> [!example]
> Ciudadano: "Quería entregar esta solicitud con la documentación anexa que se solicita".
> Funcionario de registro: "Necesito los originales de las fotocopias para poder cotejarlas".
> Ciudadano: "Nadie me dijo nada y ahora no los tengo".
> Funcionario: "En este tipo de convocatorias es imprescindible el original para poder cotejar la fotocopia".
> Ciudadano: "¡Pero si son fotocopias nítidas! Si es que la Administración siempre dando la lata".
> Funcionario: "Una fotocopia siempre debe acompañarse del original para cotejarla".
> \[...]

### Banco de niebla
Objetivos:
- Reconocer total o parcialmente que la otra parte puede tener razón.
- Simultáneamente, negarse a mantener la discusión.
- Dejar claro que no se va a cambiar de postura.

> [!example]
> Novia: "Carió, ¿Podrías bajar la basura?. Yo aún tengo trabajo que hacer para mañana".
> Novio: "Acabo de sentarme a ver el partido y estoy cansado del trabajo. Ve tú anda".
> Novia: "Sé que estás muy cansado porque tu jefe te encarga muchas cosas, y lo entiendo, pero por favor baja tú la basura, que yo aún tengo que hacer este trabajo para mañana y luego ya descansaremos los dos".

### Aplazamiento asertivo
Objetivo:
- Aplazar la respuesta a dar a la persona que nos ha criticado hasta que estemos más tranquilos y nos sintamos capaces de responder correctamente

> [!example]
> Uno: "Eso que has hecho es vergonzoso y demuestra que eres un ignorante. ¡¿Cómo se te ha ocurrido?!".
> Otro: "Si te parece bien, lo miramos mañana con calma y te explico todo lo que quieras".

### Ignorar
Objetivo:
- No prestar atención cuando la otra persona está enfadada y percibimos que todo puede acabar mal.
- Cuidarse de las críticas y palabras de la otra parte y alejarse.

### Pregunta asertiva
Objetivos:
- No pensar mal de la persona que nos critica.
- Asumir que las críticas son bienintencionadas.
- Pedir aclaraciones y justificaciones que soporten la crítica expresada.

> [!example]
> "¿Porqué te molesta mi forma de actuar?"
> "¿Qué defecto encuentras en esta solución?"
> "¿Qué problema tendremos en tu opinión si optamos por esta estrategia?"

