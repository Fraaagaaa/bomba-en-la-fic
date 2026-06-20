# 📝 Informe del Analista - Miguel Fraga Pico

## Evaluación final de la semana 2

- **Xabier Guitian López** 10/10
- **Pedro Gómez Osorio** 10/10

## Retrospectiva de la semana 2

### a) ¿Qué ha sido lo mejor de la práctica?

Lo mejor ha sido la integración de la manipulación compleja del DOM para crear una experiencia de usuario interactiva y sin recarga de página. Implementar las funciones **`enterEditMode`** y **`saveChanges`**, que alternan completamente el contenido de un elemento de la lista por un conjunto de *inputs* y viceversa, es una demostración clara del poder de **JavaScript en el navegador** y la gestión del **DOM**.

### b) ¿Qué fue lo peor?

Lo más complejo ha sido asegurar la **integridad de los datos y el manejo de estados** durante la edición. Por ejemplo:

1.  **Capturar y conservar** elementos complejos (como el *span* de `participants-info`) mientras se modifican otros.
2.  Asegurar la **validación** de los nuevos campos antes de guardar (ej. que la fecha no esté vacía, que el importe sea un número).
3.  Implementar la lógica de **cancelación** de forma robusta, guardando el estado original (`_originalHTML`) y restaurándolo si el usuario se arrepiente.

### c) ¿Cuál fue el mejor momento de cada semana durante el trabajo del equipo?

El mejor momento fue ver la fila de gastos pasar del modo visual al modo de edición con todos los campos de *input* cargados correctamente con los datos preexistentes, y luego ver cómo se actualizaba la información tras guardar, respetando el formato de fecha y moneda. Esto valida el diseño de la interfaz y la lógica de JS.

### d) ¿Cuál ha sido el peor?

El peor momento fue probablemente depurar los pequeños errores de formateo o *parsing* de datos, como asegurar que `parseFloat` se maneje correctamente y que la conversión de la fecha (`toLocaleDateString`) se haga en el formato español esperado, sin afectar al valor *datetime* subyacente.

### e) ¿Qué has aprendido?

He aprendido o reforzado mis conocimientos sobre:

* **Manipulación Avanzada del DOM:** Cómo reemplazar y restaurar nodos complejos del DOM y gestionar sus estados mediante atributos (`dataset`).
* **Gestión de Formularios Dinámicos:** La lógica para convertir contenido de solo lectura en elementos de formulario (`<input>`) y viceversa, incluyendo la extracción correcta de datos (ej. valores de `time` o `input type="number"`).
* **Programación con Estado Temporal:** El uso de propiedades temporales (`row._originalHTML`, `row.dataset.editing`) para gestionar el ciclo de vida de una edición (entrar, modificar, guardar/cancelar).

### f) ¿Qué necesitáis conservar -como equipo- para las próximas semanas?

* **Estructura de Event Listeners:** La centralización de los *event listeners* en contenedores padres (`listContainer`, `friendsList`) usando `e.target.closest()`, lo que mantiene el código limpio y eficiente, especialmente para elementos generados dinámicamente.
* **Separación de Preocupaciones:** Mantener las funciones modulares (`enterEditMode`, `saveChanges`, `cancelEdit`), lo que facilita la lectura y el mantenimiento.

### g) ¿Qué tenéis que mejorar -como equipo- para las próximas semanas?

* **Persistencia de Datos:** La mayor debilidad es la falta de persistencia real. Para la próxima semana, es crucial implementar **`localStorage`** para que los cambios (ediciones de gastos, amigos añadidos) se conserven al recargar la página.
* **Experiencia de Usuario en Edición de Participantes:** Actualmente, la información de los participantes es estática. Se debe diseñar una forma interactiva (ej. *checkboxes* o un selector múltiple) para que el usuario pueda editar los participantes de un gasto.
* **Uso de Select en Pagador:** Reemplazar el `input type="text"` del pagador por un elemento `<select>` que liste los amigos disponibles.

### h) ¿Cómo se relaciona ESTE contenido con otros del curso y con tu titulación?

* **Titulación (Desarrollo Web/Ingeniería Informática):** Esta tarea es fundamental. Implementar funcionalidades de **CRUD (Crear, Leer, Actualizar, Borrar)** en el *frontend* usando el DOM sin *frameworks* enseña los principios básicos de cómo interactúan las aplicaciones web con el usuario. El manejo de estados y la **interfaz de usuario reactiva** son habilidades esenciales para cualquier desarrollador *frontend*.
* **Contenidos del Curso:**
    * **JavaScript en el Navegador y DOM:** Es el núcleo de la tarea. Se ha utilizado la API del DOM (`querySelector`, `innerHTML`, `createElement`, `addEventListener`) para modificar dinámicamente el contenido y la estructura de la página, cumpliendo directamente con los objetivos establecidos.
    * **Maquetación y Diseño (HTML/CSS):** El *frontend* requiere una extensión de la interfaz (`edit-input` y los nuevos botones de acción) que se integra con el diseño ya existente, asegurando que la experiencia de edición sea coherente con la maquetación responsiva.