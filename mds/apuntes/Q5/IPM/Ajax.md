# ¿Qué es AJAX?

**AJAX** (acrónimo de **Asynchronous JavaScript And XML**) es una técnica de desarrollo web que permite que las páginas se actualicen de forma **asíncrona**.
En términos sencillos, esto significa que una página web puede intercambiar datos con un servidor y actualizar partes específicas del contenido **sin necesidad de recargar la página completa**.
## ¿Cómo funciona AJAX?

Tradicionalmente, para ver contenido nuevo en una web, el navegador debía solicitar una página completa al servidor. Con AJAX, el proceso cambia:

1.  **Evento:** Ocurre un evento en la página (como hacer clic en un botón).
2.  **Solicitud:** JavaScript crea un objeto (`XMLHttpRequest` o `Fetch API`) que envía una solicitud al servidor en segundo plano.
3.  **Procesamiento:** El servidor recibe la solicitud, busca los datos y envía una respuesta.
4.  **Actualización:** JavaScript recibe los datos y actualiza el HTML de la página en el lugar exacto.
## Componentes principales

Aunque el nombre menciona tecnologías específicas, hoy en día AJAX es más un concepto que un conjunto rígido:

* **HTML y CSS:** Para la estructura y el diseño visual.
* **DOM (Document Object Model):** Para interactuar y cambiar dinámicamente el contenido.
* **JavaScript:** El motor que gestiona la comunicación.
* **JSON:** Aunque la "X" es por XML, actualmente **JSON** es el formato más utilizado por ser más ligero y fácil de leer.
## Ejemplos comunes en la vida real

* **Google Maps:** Al arrastrar el mapa, las nuevas secciones se cargan sin refrescar la página.
* **Scroll Infinito:** En Instagram o X (Twitter), el contenido nuevo aparece automáticamente al bajar.
* **Buscadores:** Sugerencias automáticas mientras escribes en la barra de búsqueda.
## Ventajas principales

* **Mejor experiencia de usuario:** Navegación fluida y sin interrupciones.
* **Ahorro de ancho de banda:** Solo se transmiten los datos necesarios.
* **Interactividad:** Las webs se comportan como aplicaciones de escritorio.