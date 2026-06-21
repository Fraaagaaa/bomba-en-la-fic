# Objetivos de la GCS
Dos son los objetivos fundamentales de la GCS:
- Facilitar la visibilidad:
	- Sobre el estado del producto: **estado**.
	- Sobre su historia: **evolución**.
- Mantener la integridad del producto:
	- Establecer y mantener la integridad de los productos generados durante un proyecto y a lo largo de todo su ciclo de vida.
	- ¿Qué significa la integridad de un producto software? Significa que el producto cumple con las siguientes condiciones:
		- Satisface las necesidades del usuario.
		- Cumple los requisitos de rendimiento.
		- Se puede trazar su evolución desde que se concibió y a través de todas las fases de su ciclo de vida.

![[Pasted image 20260117193206.png]]
# Conceptos básicos de la GCS
## Definicioens básicas
Configuración del software:
- Conjunto de toda la información y productos utilizados o generados en un proyecto como resultado del proceso de ingienería del software.
- Por tanto, es el término que designa al conjunto de todos los elementos de configuración del software de un proyecto.

Elemento de configuración del software:
- Cada uno de los componentes de la configuración del software.
- Es la unidad de trabajo para la GSC: Un ECS debe ser un elemento que se pueda definir y controlar de forma separada. Es decir, una unidad en sí mismo.
- En cuanto al software propiamente dicho, dependiendo de su tamaño, complejidad y necesidad de control y visibilidad sobre el mismo, puede requerir de su descomposición en varios ECS, aunque el sistema en su conjunto es a su vez un ECS.

## Línea base
Concepto introducido para facilitar el control de cambios:
- Permitir cambios rápidos e informales sobre un ECS **antes** de que pase a formar parte de una línea base.
- En el momento en que se establece una línea base, se debe aplicar un procedimiento formal para evaluar y verificar cada cambio.

Hay dos definiciones formales:
- Desde el punto de vista del proceso:
	- Es un **punto de referencia** en el proceso de desarrollo que queda marcado por la **aprobación** de uno o más ECS mediante una **revisión técnica formal**.
- Desde el punto de vista del producto:
	- Es un conjunto de **ECS revisados y aceptados** que sirven como base para el desarrollo posterior y que **sólo** se pueden cambiar a través de un **proceso formal de control de cambios**.

# Aspectos relacionados con la GCS
## Actividades relacionadas
Las herramientas CASE que automatizan la GCS suelen incluir funciones adicionales que llevan a ampliar la definición estándar con las siguientes actividades:
- Control de versiones:
	- Consiste en mantener un riesgo histórico de las diferentes versiones por las que pasan los componentes de un producto que permita la recuperación de cualquiera de ellas.
- Construcción:
	- Consiste en gestionar la complicación y enlazado de los distintos componentes del producto software de una forma lo más eficiente posible.
- Gestión de problemas:
	- Consiste en realizar un seguimiento de la evolución de los problemas que afectan al producto.
- Control del trabajo en equipo:
	- Consiste en controlar las interacciones que se producen entre los múltiples desarrolladores de un producto, sobre todo cuando deben compartir ciertos componentes del producto.

## Control de versiones
Facilita la GCS.
Permite saber para cada ECS:
- Cuál es la última versión.
- Relación entre distintas versiones.
- Dónde están

Esto facilita el control de cambios. ¿Sobre qué version/es hacer un cambio?

### Versiones y revisiones
Versión: Es una instancia de un ECS, en un momento dado del proceso de desarrollo, que es almacenada en un repositorio y que puede ser recuperada en cualquier momento para su uso o modificación.<br>
Revisión: A las distintas versiones que aparecen en el tiempo, según se va avanzando en el desarrollo de un ECS, se les suele llamar también versiones.

### Grafo de evolución de revisiones
Cada una de las revisiones de un ECS se debe poder identificar de manera única. Es común utilizar para ello un sistema de esquema numérico, donde cada nueva versión recibe un número sucesivo.<br>
La manera más fácil de crear una nueva revisión de un ECS es realizar una modificación sobre la revisión más reciente. Así, las revisiones van formando una cadena, a la que se suele llamar cadena de revisión.<br>
Cada revisión en la cadena de revisión es una actualización de, y viene a sustituir a, la revisión anterior. Normalmente se trabaja sobre la última revisión de la cadena, que es la más actual, aunque las anteriores también deben ser accesibles.<br>
Grafo de evolución o grafo de revisión: Una representación para las diferentes revisiones de un ECS y sus relaciones de sucesión temporal.

### Modelo de trabajo
El modelo de trabajo de la mayoría de las herramientas de gestión de revisiones es:
![[Pasted image 20260118132437.png]]

Las herramientas de gestión de revisiones o control de versiones ayudan a crear, identificar y almacenar nuevas versiones, al mismo tiempo que se mantienen las anteriores.

### Almacenamiento de revisiones
Las herramientas de gestión de revisiones, por eficiencia, no almacenan físicamente todas las versiones. Almacenan sólo una de ellas, que puede ser la primera o la última.<br>
Sin embargo, nos permiten recuperar cualquier otra versión. Para ello guardan también todo el historial de cambios que han ocurrido sobre el elemento y que lo han hecho pasar de una versión a otra.<br>
Siendo r1 y r2 dos revisiones consecutivas en el grafo de evolución, se llama delta a: La secuencia de operaciones que aplicadas sobre la revisión r1 dan como resultado la revisión r2.<br>
Tipos de deltas:
- Según su dirección:
	- Deltas directos.
	- Deltas indirectos
- Según su locacilización:
	- Deltas separados.
	- Deltas mezclados.


### Variantes
Son versiones de un ECS que coexisten en un determinado momento y que se diferencian en ciertas características.
Representan la necesidad de que un objeto satisfaga distintos requisitos al mismo tiempo.
Puede haber varias sobre las que se esté trabajando simultáneamente, a diferencia de las revisiones.
Una variante no reemplaza a otra, como ocurre con las revisiones, sino que abre un nuevo camino de desarrollo. Se reconoce fácilmente en el grado de evolución como una ramificación de este
![[Pasted image 20260118133000.png]]

#### Tipos de variantes
Las variantes pueden ser:
- Temporales:
	- A veces es necesario que varias personas trabajen simultáneamente sobre la misma versión de un objeto y para que no ocurran conflictos entre ellas se crea una variante distinta para cada persona.
	- Una vez acabadas las modificaciones, es necesario mezclar todas las variantes para que la versión resultante contenga todos los cambios.
- De usar y tirar:
	- Para exponer diferentes soluciones alternativas en paralelo y quedarse con la mejor.
	- Variantes de pruebas: Sobre las que se introducen elementos especiales para facilitar la relación de pruebas.
- Permanentes, que se dividen en:
	- Variantes de requisitos de usuario: El caso más típico era el idioma en las aplicaciones.
	- Variantes de plataforma: Una variante para cada sistema operativo o plataforma hardware sobre la que se desee que funcione la aplicación

### Configuraciones alternativas
Al abrir ramificaciones en el grafo de evolución, en vez de una única configuración vamos a tener un conjunto de configuraciones alternativas.
- Cada una va a satisfacer las necesidades de un entorno particular o usuario.

Cada configuración alternativa se especifica mediante los ECS que la componen y la versión adecuada de cada uno de ellos.

Esto se puede conseguir de la siguiente forma:
- Se asocian atributos a cada versión de un ECS.
- Se crea una especificación de configuración que describa el conjunto de atributos deseado y se recuperan los ECS adecuados para construir la configuración.

Make: Herramienta que facilita la construcción automática de una configuración concreta: Recupera los ECS necesarios en la versión adecuada, los compila y los linka.

## Release
Se suele llamar release a una configuración del sistema que se va a comercializar o entregar al cliente. Debe identificarse y almacenarse para poder recuperarla en cualquier momento. La GCS también se encarga de controlar la gestión e instalación de releases.

### Construcción (building)
Esta actividad gestiona la compilación y el enlazada.
- Es una actividad facilitada por la GCS.
- Necesita saber:
	- Que componentes enlazar.
	- En qué versión.
	- Dónde están.
- Toma esta información de:
	- Identificación de la configuración.
	- Control de versiones.
- Una vez que se han especificado las diferentes configuraciones del producto, existen herramientas que facilitan la construcción automática de una configuración concreta, es decir, la recuperación de los ECS necesarios en la versión adecuada, su compilación y enlazado.

## Gestión de problemas
Es una actividad facilitada por la GCS y que se considera complementaria a la de control de cambios.
El cambio sobre un producto puede venir dado por:
- Cambios en los requisitos/necesidades.
- Problemas

Esta actividad gestiona la evolución de los problemas detectados sobre el software, tanto aquellos que se detectan en la fase de pruebas como los informes de problemas que llegan del usuario.
Las tareas a realizar en la gestión de problemas son:
- Admisión, registro y valoración de informes de incidencias.
- Asignación del problema a un responsable.
- Asociación de información al problema.
- Monitorización del estado del problema.
- Registro de actividades de corrección del problema.
- Información acerca de los problemas.

## Control del trabajo en equipo
Es una actividad facilitada por la GCS.

Al compartir elementos de trabajo existe un claro y evidente peligro, la sobreescritura de cambios.

Solución: Desarrollo en paralelo

Necesidad que se plantea ante esta solución: Integración del trabajo realizado en paralelo: operación merge.

## Otros aspectos relacionados
La GCS tiene también una gran influencia en otros aspectos del desarrollo de software:
- Las metodologías
	- Integración de las actividades de GCS son las metodológicas.
	- Las fases en que establezca la metodología, los productos que se generen, etc. son determinantes para establecer la GCS.
- El entorno de desarrollo:
	- Uso de herramientas de GCS.
	- Integración con las otras herramientas del entorno de desarrollo.
- La organización:
	- Aparecen nuevas políticas y procedimientos de GCS.
	- Aparecen nuevos roles y responsabilidades que deberán integrarse en la organización del proyecto.
- La calidad:
	- Se contribuye a mantener la integridad del producto