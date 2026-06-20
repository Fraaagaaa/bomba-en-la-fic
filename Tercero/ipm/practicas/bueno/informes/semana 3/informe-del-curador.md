# 📝 Informe del Curador-Traductor - Xabier Guitian López

## Objetivos de aprendizaje de la semana 3

### 1. WAI-ARIA (Web Accessibility Initiative - Accessible Rich Internet Applications)

El objetivo central fue comprender que HTML5 a veces no es suficiente para describir interfaces complejas a las tecnologías de asistencia. ARIA actúa como un puente semántico.

* **Recursos identificados para su estudio:**
    * Especificación **WAI-ARIA 1.2** del W3C.
    * Guías de autoría ARIA para patrones de diseño comunes (tablas, alertas, botones toggle).
    * Diferencias entre `aria-label`, `aria-labelledby` y `aria-describedby` y cuándo usar cada uno.

### 2. Accesibilidad Cognitiva y Navegación

Más allá de los lectores de pantalla, aprendimos sobre la importancia de la consistencia en el foco.

* **Recursos identificados para su estudio:**
    * Pautas WCAG 2.1 criterio 2.4.3 (Focus Order).
    * Técnicas para gestionar el foco, en aplicaciones de una sola página (SPA).

## Recursos empleados en la semana 3

### 1. Atributos de "Live Regions" (`aria-live`)

* **Descripción del recurso:** Atributos que indican a los lectores de pantalla que un contenido ha cambiado y debe ser anunciado.
* **Utilidad y aplicación a la práctica:** Se implementó una región oculta (`#a11y-status-message`) con `aria-live="polite"`. Creamos una función auxiliar `announce(message)` en JavaScript que inyecta texto en este contenedor. Esto permite que cuando un usuario añade un amigo o guarda un gasto, reciba confirmación auditiva inmediata sin necesitar alertas invasivas (`window.alert`).

### 2. Roles ARIA de Estructura (`role="table"`, `role="row"`)

* **Descripción del recurso:** Roles que sobreescriben o explicitan la semántica de un elemento.
* **Utilidad y aplicación a la práctica:** Dado que usábamos `div`s con clases CSS flexbox para la maquetación responsiva de la lista de gastos (para permitir el comportamiento adaptativo en móvil), la semántica de tabla nativa (`<table>`, `<tr>`) se perdía o era difícil de estilizar. Aplicar `role="table"`, `role="rowgroup"`, `role="row"` y `role="cell"` a nuestros `div`s permitió mantener el diseño flexible visualmente mientras se presentaba como una tabla de datos estructurada para los usuarios de lectores de pantalla.

### 3. Propiedades de Estado (`aria-current`, `aria-hidden`)

* **Descripción del recurso:** Atributos que comunican el estado actual de un elemento UI.
* **Utilidad y aplicación a la práctica:**
    * Usamos `aria-current="page"` en la navegación para indicar visual y semánticamente en qué sección se encuentra el usuario.
    * Usamos `aria-hidden="true"` en los iconos decorativos (como 🗑️ o ✏️) dentro de los botones, asegurando que los lectores de pantalla ignoren el emoji y lean solo el `aria-label` descriptivo del botón ("Editar gasto"), evitando redundancia o confusión.
