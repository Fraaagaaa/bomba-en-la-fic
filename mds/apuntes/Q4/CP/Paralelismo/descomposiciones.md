# Descomposiciones
> Note
> Esto cae por lo menos 2 veces en el examen
# Descomposición de dominio
En la parte de implementar del examen, si la función depende de reparto, no lo hagamos por columnas, la memoria no es contigua, mejor hacerlo por filas


Regla del propietario: *La tarea a la que se le asigna un determinado dato es responsable de realizar todos los cálculos asociados al mismo*

# Descomposición funcional
Descomponer el cálculo en tareas atendiendo a las partes diferenciadas del mismo.

**PIPELINE** es siempre funcional

Pasos:
1. Identificar las fases funcionales del cálculo a paralelizar
2. Asignar una tarea para la realización de cadad fase

Es habitual que el grafo de tareas resultante de este tipo de descomposiciones pueda organizarse como un *pipeline*

# Descomposición recursiva
También conocido como *divide-y-vencerás*.

Pasos:
1. Si un subproblema ha alcanzado el tamaño crítico, obtener su solución parcial.
2. De lo contrario, descomponerlo en subproblemas.
3. Combinar los resultados de los subproblemas para obtener la solución al problema original.

# Descomposición especuativa
En ocasiones un problema no puede dividirse en tareas independientes. No obstante, sí puede dividirse funcionalmente en fases que se ejecutan condicionalmente dependiendo de los resultados de fases anteriores.

La descomposición especulativa consiste en comnezar la ejecución de tareas condicionales excluyentes entre sí sin esperar a la finalización de las tareas de las que depende la seleción de una de ellas.

Una vez la tarea de selecci´on haya finalizado, es posible seleccionar el resultado correcto de entre los obtenidos por las tareas ejecutadas de forma especulativa

# Factores a considerar

Creacón estática: todas las tareas que participan en el algoritmo se crean al inicio de su ejecución.

Creación dinámica: las tareas se crean durante la ejecución del alcoritmo. Útil cuando no se conoce la estructura del grafo de dependencias de forma estácica. Sí se define la política de creación de nuevas tareas.

# Balanceo de la carga
Es deseable que las tareas obtenidas tengan un coste similar, para facilitar la etapa de asignaci´on de tareas.

Es deseable que las tareas obtenidas tengan un coste similar, para facilitar la etapa de asignaci´on de tareas

La descomposici´on de dominio habitualmente lleva a algoritmos equilibrados. En la descomposici´on funcional, recursiva y especulativa depender´a del an´alisis realizado.