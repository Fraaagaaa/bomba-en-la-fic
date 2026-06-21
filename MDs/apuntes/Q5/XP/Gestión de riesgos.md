## Pilares fundamentales
Se puede obtener un desarrollo rápido, económico y de calidad basándose en los cuatro pilares que McConnell propone en su libro "Desarrollo y gestión de los proyectos informáticos"<br>
Cometer errores clásicos, no actuar según los buenos principios de desarrollo o no gestionar los riesgos provocará retrasos y costes asociados.<br>
Los proyectos de software incluyen un amplio rango de riesgos:
- Cambios en los requisitos de usuario.
- Falta de experiencia en la gestión.
- Mala estimación de la planificiación.
- Personal contratado poco fiable y efectivo.
- Problemas con la tecnología, con el desarrollo y/o con los proveedores.
- Etc.

Probabilidades en el mundo real:
- De finalizar un proyecto complejo en el tiempo estimado: **Tiende a 0**.
- De cancelar un proyecto completo: **Tiende a 0.5**.

La función de la gestión de riesgos es:
- Identificar, estudiar y eliminar las fuentes de riesgo antes de que empiecen a amenazar la finalización satisfactoria de un proyecto.

Según Pressman, se pueden controlar los riesgos a varios niveles. (si se está en los niveles 1, 2 o 3 se ha perdido la batalla de la planificación):
1. Control de crisis
	- Controlar los riesgos sólo cuando se han convertido ya en problemas: Actuar de bombero apagando el fuego.
2. Arreglar cada error.
	- Detectar y reaccionar rápidamente ante cualquier riesgo, pero sólo después de haberse producido.
3. Mitigación de riesgos.
	- Planificar con antelación el tiempo que se necesitaría para cubrir riesgos en el caso de que ocurran, pero no intentar eliminarlos incialmente.
4. Prevención.
	- Crear y llevar a cabo un plan como parte del proyecto software para identificar riesgos y evitar que se conviertan en problemas.
5. Eliminación de las causas principales.
	- Identificar y eliminar los factores que puedan hacer posible la presencia de algún tipo de riesgo.


Según Boehm, la gestión de riesgos se compone de:
- Estimación de riesgos:
	- Identificación de riesgos: Genera una lista de riesgos capaces de romper la planificación del proyecto.
	- Análisis de riesgos: Mide la probabilidad y el impacto de cada riesgo, y los niveles de riesgo de los métodos alternativos.
	- Priorización de riesgos: Genera una lista de riesgos ordenados por su impacto.
- Control de riesgos:
	- Planificación de la gestión de riesgos: Genera un plan para tratar cada riesgo significativo. También asegura que los planes para la gestión de riesgos de cada uno de ellos son consistentes entre sí y con el plan del proyecto.
	- Resolución de riesgos: Es la ejecución del plan para resolver cada uno de los reisgos significativos.
	- Monitorización de riesgos: Es la actividad del progreso de la monitorización dirigido a la resolución de cada elemento de riesgo.

Identificación de riesgos:
- Los riesgos se parecen mucho a los errores clásicos ya mencionados.
- La diferencia es:
	- Los errores clásicos se comenten con mayor frecuencia que los riesgos.
	- Los riesgos son menos comunes o pueden ser únicos para un proyecto determinado.
- Steve McConnell recopila en su libro "Desarrollo y gestión de proyectos informáticos" los riesgos más habituales en la planificación y los riesgos potenciales de la planificación.

Priorización de riesgos:
- Los proyectos suelen gastar el 80% de su presupuesto en arreglar el 20% de sus problemas.
- Conclusión:
	- Centrarse, fundamentalmente, en ese 20%
- Se pueden ordenar los riesgos por su ER y así saber cuáles controlar para compensar esfuerzo y reducción en tiempo de los riesgos.
- Steve McConnell presenta ejemplos de priorización de riesgos en su libro ya mencionado donde se aprecia:
	- Mayor utilidad al controlar unos riesgos que otros.
	- Necesidad de controlar riesgos especialmente "dolorosos".

Planificación de la gestión de riesgos:
- El plan de gestión de riesgos puede ser tan sencillo como un párrafo para cada riesgo describiendo: Quién, Qué, Cuándo y Cómo.

Resolución de riesgos:
- Depende del riesgo específico que se esté tratando.
- Algunas posibles acciones son:
	- Evitar el riesgo: No realizar actividades arriesgadas.
	- Trasladar el riesgo de una parte del sistema a otra: Expertos en una materia supervisan a los noveles y que el riesgo no esté en el camino crítico de la planificación.
	- Informarse del riesgo: Conocerlo y ver si es o no posible.
	- Asumir el riesgo: Si las consecuencias son pequeñas y el esfuerzo grande.
	- Comunicar el posible impacto de un riesgo en caso de ocurrir.
	- Controlar el riesgo: Planificar acciones en caso de ocurrir.
	- Recordar el riesgo: Para proyectos futuros.

Monitorización de riesgos:
- Los riesgos aparecen y desaparecen en el desarrollo del proyecto.
- Por ello se necesita una monitorización de riesgos que permita:
	- Comprobar cómo aparecen los nuevos riesgos.
	- Identificar cómo aparecen los nuevos riesgos.


Para hacer gestión de riesgos teniendo en cuanta los aspectos aneriores, a continuación se verá una aproximación ligera.

Esta aproximación ligera considerará:
- Fases a abordar.
- Técnicas a emplear en cada fase.
- Puesta en operación práctica.


# Introducción
## Gestión de riesgos
- Surge debido al gran porcentaje de proyectos cancelados, entregados fuera de plazo, con presupuestos excedidos, con problemas operativos, etc.
- Se considera un factor importante en la gestión de un proyecto.
- Su objetivo es identificar, estudiar y eliminar las fuentes de riesgo antes de que empiecen a amenazar el cumplimiento satisfactorio del proyecto.
- Los riesgos son inherentes a los proyectos y siempre existirán en menos o mayor medida.
- Cualquier proyecto implica riesgos para las dos partes generalmente involucradas:
	- Organización contratante y organización contratista.
- Estos riesgos pueden ser:
	- Identificados.
	- Traducidos en términos cuantitativos; esto es, valorados.
	- Analizados.
	- Controlados y reducidos en la medida de lo posible.
	- Con algunos riesgos se podrá convivir sin problema y con otros se tendrán que ejercer acciones para controlarlos y/o evitarlos.

## Definición de riesgo
El Air Force Systems Command define riesgo como la forma de expresar la incertidumbre a lo largo del ciclo de vida: la probabilidad de que en un punto del ciclo de vida no se alcancen los objetivos propuestos con los recursos disponibles.<br>
Un riesgo es un evento que podría reducir la capacidad para lograr los objetivos definidos en el proyecto.<br>
Es decir:
- Evento o condición incierta que, en caso de ocurrir, tiene un efecto negativo sobre los objetivos de un proyecto.
- Cualquier elemento potencial que provoca resultados insatisfactorios en un proyecto.
- Lo previsto no se va a poder conseguir.

Un riesgo tiene una causa y, si ocurre, una consecuencia.<br>
## Clasificación de riesgos
Las áreas o clases típicas de riesgo que debe tratar un jefe de proyecto son las siguientes:
- Riesgos estratégicos:
	- Riesgos relacionados con la estrategia de la organización. Están relacionados con las pérdidas y los beneficios, las inversiones, la imagen, etc. (e.g. Pérdida de mercado)
- Riesgos comerciales:
	- Riesgos relacionados con la venta del proyecto, el seguimiento del cliente, el precio y las posibles actualizaciones, etc. (e.g. esfuerzo de venta desperdiciado, pérdida del cliente y vender a bajo precio)
- Riesgos contractuales y financieros:
	- Riesgos relacionados con los términos contractuales negociados antes de la firma del contrato: penalizaciones, niveles de calidad, control de las necesidades de evolución, calendarios de pagos, obligaciones, etc.
- Riesgos de proyecto:
	- Riesgos causados por los aspectos técnicos del software: especificación, diseño, desarrollo, integración y validación.
- Riesgos de explotación:
	- Se refieren a fallos ocurridos durante la explotación, los cuales pueden causar daños significativos y, eventualmente, pueden ser peligrosos para la vida de las personas.

## ¿Por qué y cuándo gestionarlos?
Porque hay que gestionar los riesgos para lograr los objetivos marcados en el proyecto. Una buena planificación, organización y gestión del proyecto puede verse muy afectada por los riesgos que se van produciendo.<br>
Hay dos alternativas:
- Gestión de Problemas: Según apareen los problemas se van solventando
- Gestión de riesgos: Los posibles impactos de los riesgos se mitigan con planes. No exime de hacer gestión de problemas cuando sea necesario.

Sólo tiene sentido si se hace de forma sistemática. Típicamente vinculada a:
- Planificación.
- Seguimiento.
- Cierre.

## ¿Cómo?: Fases básicas
![[image-removebg-preview(1).png]]

Identificación: ¿Qué riesgos se pueden producir?:
- Explicitación de los riesgos para el proyecto.
- Opcional: Clasifciación y agrupación (e.g. por causas).

Valoración: Si un riesgo deja de ser riesgo y pasa a ser un problema, ¿Qué pasa?:
- Cuantificaciones de los riesgos.
- Priorización de los riesgos.
- Decisión del nivel aceptable de un riesgo.

Análisis: ¿Qué causas determinan ese riesgo y cómo se puede evitar o mitigar?
- Estudio de posibles alternativas.
- Actividades de contención y prevención.

Control y seguimiento: ¿Cómo se hace el seguimiento de los riesgos?:
- Implantación efectiva de las estrategias de mitigación consideradas.
- Seguimiento de los riesgos considerados más relevates.
- Actividades de contingencia.

# Identificación de riesgos
Consiste en elaborar una lista de riesgos que pueden afectar al proyecto, documentando así cada riesgo potencial.
Pero... ¿Cómo se identifican los riesgos?
Algunas posibilidades para dicha identificación son las siguientes:
- Examinar resultados insatisfactorios y sus causas origen.
- Usar el marco clasificatorio de los riesgos visto anteriormente.
- Usar las estructuras de tareas o productos para particionar el espacio del problema.
- Estudio de los posibles eventos de riesgo y sus resultados.
- Listas de comprobación.

## Resultado insatisfactorio y causas
El riesgo es frecuentemente definido como fuente de resultados insatisfactorios.
Pensar en estos términos es útil para ayudar a identificar riesgos potenciales.
Identificar resultados insatisfactorios permitirá pensar en las causas de origen de los mismos y, por lo tanto, identificar los riesgos asociados.
La mayoría de los resultados insatisfactorios tendrán una o más causas origen, por ejemplo:
- Falta de la definición de un ciclo de vida.
- Pobre planificación y seguimiento.
- Pobre gestión de requisitos.
- Malas relaciones entre el personal.
- Mala gestión en las compras.
- Tecnología inmadura y/o desconocida.

## Marco clasificatorio de riesgos
El proceso de identificación de riesgos puede considerar cada área o clase típica de riesgo presentada con anterioridad:
- Riesgos estratégicos.
- Riesgos comerciales.
- Riesgos contractuales y financieros.
- Riesgos de gestión.
- Riesgos de proyecto.
- Riesgos de explotación.

Existen otras clasificaciones o marcos, lo realmente importante es disponer de unas tipologías establecidas y que esta aproximación sea lo más metódica posible.

### Particionar el espacio del problema
Para proyectos que no sean muy pequeños, se puede aplicar la máxima de "divide y vencerás".
En este caso, esta máxima consiste en examinar individualmente:
- Cada tarea principal del plan de proyecto.
- Cada área de producto.

Por cada partición considerada, se trata de identificar aproximadamente 4-6 riesgos principales, evitando así la excesiva complejidad en el proceso. Así se va confeccionando una lista de riesgos identificativos, que no debería ser una enumeración exhaustiva de pesimismos (particularmente de esta aproximación)

## Evento de riesgo y efecto
La identificación de riesgos también se puede apoyar en el estudio de eventos y sus efectos:
![[Pasted image 20260116194405.png]]

El mismo evento de riesgo y la misma causa pueden tener a veces efectos muy distintos:
- Algunos descartes puede resultar peligrosos si no se consideran con cuidado.
<br>
### Listas de comprobación
Las listas de comprobación se construyen a partir de información histórica, conteniendo los riesgos más habituales en los proyectos de una organización.
- La lista proporcionada por Steve McConnell podría ser un buen punto de partida.

Su principal ventaja es que permiten una identificación de riesgos muy rápida y relativamente sencilla, máxime si se emplea algún tipo de agrupación (e.g. por tipos de riesgos).

Su principal inconveniente es que es prácticamente imposible tener una lista que incluya todos los posibles riesgos en un proyecto software.

Consejo de uso como consecuencia de lo anterior: Utilizar una lista de comprobación como punto de partida, pero permitiendo después incluir nuevos riesgos específicos del proyecto (identificación de riesgos según opciones anteriores).

### Agrupación por causas
Una vez identificados a través de alguna de las estrategias anteriores, de cualquier otra o de varias de ellas, los riesgos podrían clasificarse atendiendo a las causas origen que los provocan. <br>
Esto suele ayudar en la planificación de la gestión de riesgos para determinar las causas a las que prestar mayor atención.<br>
La agrupación ayuda principalmente a saber sobre qué poner especial atención.<br>
No es un paso obligatorio, per sí recomendable por la información que se puede llegar a sacar del análisis de esta agrupación.
<br>
# Valoración o cuantificación de riegos
## Valoración de riesgos
Una vez identificados los riesgos en la fase anterior, es fundamental su priorización.
- Hay que atender a los que más puedan afectar al proyecto.
- Con muchos riesgos se podrá convivir sin mayores inconvenientes.
- Por tanto, debe decidirse el nivel aceptable de un riesgo (umbrales de atención)

Para su priorización es imprescindible un método de cuantifiación o valoración, que es lo que se explicará a continuación.
Una vez cuantificado un riesgo, éste ya es comparable con otros para estudiar la prioridad que posee dentro de todo el proyecto.
## Conceptos para la cuantificación
En la introducción se definió riesgo como la probabilidad de obtener un resultado no satisfactorio.
De dicha definición se deriva directamente la medida de la exposición a riesgo, que se define como el producto de:
- La probabilidad de ocurrencia del riesgo.
- La magnitud de pérdida del riesgo (impacto que puede producir el riesgo en el proyecto si se convierte en problema).
- Por ejemplo: si existe un 25% de probabilidad de que ocurra un riesgo que retrasaría el proyecto en 4 semanas, entonces la exposición a este riesgo es de $0.25\times4 = 1 semana$ 

La probabilidad y el impacto de un riesgo puede valorarse como:
- Medida numérica (e.g. probabilidad = 7.9 e impacto = 20 días)
- Meida subjetiva (e.g. Alta, media, baja...)

### Cuantificación de la probabilidad
La probabilidad del riesgo puede expresarse como un valor númerico (e.g. 0.79). Normalmente se necesitan datos históricos para asignar un valor numérico a la probabilidad de ocurrencia. La probabilidad numérica se expresa en un rango entre 0 y el 1, el 0 representa un riesgo imposible y el 1 un riesgo seguro.

### Cuantificación del impacto
Si el resigo afecta al presupuesto, el impacto puede ser la pérdida expresada en unidades monetarias.
Si el riesgo afecta a la planificación, puede expresarse en unidades temporales.
Si el riesgo afecta a la vida, se expresa la gravedad de la incapacidad y el número de personas afectadas.
La mayoría de los riesgos, si no todos, podrían ser expresados en su impacto como pérdida económica.

#### Subjetividad
Técnicas para ayudar a acotar la subjetividad al establecer medidas numéricas:
- Solicitar la estimación de la persona más familiarizada con el sistema o con más experiencia en proyectos parecidos.
- Utilizar el método Delphi: varios miembros de un grupo identifican riesgos y les asignan una probabilidad de ocurrencia y una magnitud de pérdida. Estas estimaciones son discutidas por el grupo y refinidas.
- Usar aproximaciones subjetivas empleando adjetivos (e.g. muy improbable, bastante improbable, improbable, probable, bastante probable, muy probable) y asignando un valor numérico a cada uno de esos adjetivos.

La otra alternativa es directamente trabajar con la subjetividad: usar aproximaciones completamente subjetivas... Un ejemplo podría ser
![[Pasted image 20260117190656.png]]
<br>
#### Nivel de riesgo aceptable
La exposición a riesgo permite priorizar los riesgos identificados y destacar un conjunto de riesgos clave de entre todos ellos. Se pueden definir niveles de aceptabilidad de los riesgos para dirigir las medidas a poner en práctica. Así se proporciona una actuación dirigida a los riesgos más importantes.<br>
No sólo se debe centrar uno en la ordenación estricta de la lista de riesgos identificativos atendiendo a su exposición a riesgo. Algunos riesgos puede priorizarse independientemente del lugar que ocupen en la lista: riesgos que producirían pérdidas considerables con una baja probabilidad.<br>
#### Umbrales de actuación
Con un método subjetivo, como el anteriormente presentado, se puede definir los umbrales de forma sencilla.
Por ejemplo, aquellos riesgos cuya exposición sea:
- Baja: Se vive con ellos.
- Media: Se define un plan de contingencia por si se da el riesgo
- Alta: Se definen acciones de prevención, alternativas y plan de contingencia.

# Análisis de riesgos
## Clasificación de riesgos
Riesgos gestionables y dentro de alcance: Las acciones necesarias para gestionar el riesgo tienen un coste que está dentro de lo asumible para el proyecto considerado.
Riesgos gestionables y fuera de alcance: Las acciones necesarias para gestionar el riesgo tienen un impacto muy importante y poco asumible en el coste que está dentro de lo asumible para el proyecto.
Inevitable: Gestionar este tipo de riesgos conlleva cambiar la concepción del proyecto de forma completa.<br>
## Estrategias de gestión de riesgos
Las estrategias más relevantes para gestionar riesgos son las siguientes:
- Transferir:
	- Sacar el riesgo del proyecto a través de subcontratas
- Prevenir:
	- Desarrollar el proyecto de forma que el riesgo no pueda convertirse en problema.
	- Considerar caminos alternativos que eviten el riesgo
- Controlar:
	- Aceptar la posibilidad de que se dé el riesgo.
	- Establecer medidas para reducir la exposición a riesgo.
	- Planificar acciones de contención.
	- Hacer seguimiento frecuente del riesgo.
	
### Planificación de gestión de riesgos
Para cada riesgo destacado se debería desarrollar un plan que lo considere. Para cada uno de dichos planes se debería seguir un estándar, que debería considerar básicamente:
- Objetivos.
- Acciones concretas/entregables/hitos
- Resposabilidades.
- Estimación de plazos, recursos necesarios y costes.

Posteriormente, todos los planes individuales deben ser integrados para asegurar un empleo adecuado de los recursos.

# Control y seguimiento de riesgos
Las actividades de control y seguimiento se centran en:
- Asegurar que los planes de gestión de riesgos establecidos en la fase anterior se llevan a cabo como estaba previsto.
- Vigilar las modificaciones de los valores de los parámetros identificativos de los riesgos.
	- Revaloración de los riesgos.
	- Reanalizar los riesgos.
- Efectuar el seguimiento del riesgo del proyecto.
	- ¿Hay nuevos riesgos?
	- ¿Es todavía un riesgo?
## ¿Cuando?
No hay un estándar previamente establecido.
Los riesgos serán revisados y controlados conforme se establezca a nivel organizativo.
- Necesidad de establecer los momentos en que se procederá a la actividad de control y seguimiento de los riesgos.

Estos momentos dependen en gran medida del ciclo de vida establecido y de los tiempos que éste marque.
- El modelo en espiral ya los establece intrínsecamente.

Regla general vinculada a la gestión de proyectos:
- Cada vez que se haga el informe de seguimiento de un proyecto tal y como se indicó en su plan de proyecto.