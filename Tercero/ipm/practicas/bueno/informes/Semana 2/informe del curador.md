# 📝 Informe del Curador-Traductor - Xabier Guitian López

## Objetivos de aprendizaje de la semana 2

### 1. Manipulación Dinámica del DOM y Gestión de Estado

Este fue el objetivo principal para implementar la funcionalidad de edición en su lugar (*in-place editing*). Requiere cambiar la estructura del DOM de una celda de visualización de texto a una celda de formulario (`<input>`) y viceversa.

* **Recursos identificados para su estudio:**
    * Documentación MDN sobre la propiedad `innerHTML` y sus implicaciones de seguridad y rendimiento al reemplazar nodos.
    * Tutoriales sobre la gestión de *event listeners* en elementos generados dinámicamente.
    * Uso de propiedades personalizadas (`data-*` o temporales) en elementos del DOM para almacenar estados (`editing`) o contenido original.

### 2. Implementación del Ciclo de Vida CRUD (U) - "Update"

El objetivo fue dominar la lógica de los cuatro estados principales en una edición de interfaz: Leer (estado normal), Editar (cambio de UI), Guardar (validación y actualización) y Cancelar (reversión al estado original).

* **Recursos identificados para su estudio:**
    * Artículos sobre el patrón de diseño "Read/Write View" en el frontend.
    * Lógica de validación básica en JavaScript (ej. comprobar `isNaN` y campos vacíos) antes de la persistencia de datos.

## Recursos empleados en la semana 2

### 1. Uso de Propiedades Temporales del Elemento DOM (`row._originalHTML`)

* **Descripción del recurso:** Se utilizó una propiedad de JavaScript adjunta directamente al elemento `<li>` o `<div>` que representa la fila de gasto (`row._originalHTML`) antes de la edición.
* **Utilidad y aplicación a la práctica:** Esto permitió almacenar una **copia exacta** del HTML original de la fila en la función `enterEditMode`. Es esencial para la función **`cancelEdit`**, ya que permite revertir la fila a su estado inicial de manera instantánea si el usuario descarta los cambios, asegurando que no se pierdan los datos originales.

### 2. Delegación de Eventos con `e.target.closest()`

* **Descripción del recurso:** El evento `click` se sigue escuchando en el contenedor padre (`listContainer`), pero se utiliza `e.target.closest('.btn-edit')`, `.closest('.btn-save')` o `.closest('.btn-cancel')` para identificar el botón específico que fue presionado.
* **Utilidad y aplicación a la práctica:** Los botones "Editar" se transforman en "Guardar" y "Cancelar" dinámicamente. La delegación de eventos garantiza que no importa si el botón se creó en el HTML inicial o si se generó en tiempo de ejecución (modo de edición), la lógica de acción siempre funcionará sin necesidad de añadir y quitar *event listeners* continuamente.

### 3. Propiedades `dataset`

* **Descripción del recurso:** El atributo `data-` de HTML (accesible mediante JavaScript como `elemento.dataset`).
* **Utilidad y aplicación a la práctica:** Se usó para establecer una bandera en la fila, como `row.dataset.editing = 'true'`, para marcar claramente el estado actual de la interfaz de usuario. Esto evita que el usuario pueda hacer clic en "Editar" en una fila que ya está siendo editada, mejorando la usabilidad y la robustez del código.
