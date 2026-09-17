# 📝 Informe del Analista - Miguel Fraga Pico

## Evaluación final de la semana 3

- **Miguel Fraga Pico** 10/10
- **Xabier Guitian López** 10/10
- **Pedro Gómez Osorio** 10/10

## Retrospectiva de la semana 3

### a) ¿Qué ha sido lo mejor de la práctica?

Lo más destacado ha sido ver cómo la aplicación se vuelve inclusiva. Implementar **WAI-ARIA** no solo cumple con los requisitos, sino que mejora la estructura semántica global. El uso de `aria-live` para anunciar cambios dinámicos (como "Gasto guardado") añade una capa de profesionalidad que muchas veces se pasa por alto.

### b) ¿Qué fue lo peor?

Lo más tedioso fue probar la navegación por teclado exhaustivamente. Asegurarse de que el foco no se pierda al eliminar un amigo o al guardar un gasto requirió afinar mucho el manejo del `focus()` en JavaScript, especialmente manejando los tiempos de ejecución para que el elemento existiera antes de intentar enfocarlo.

### c) ¿Cuál fue el mejor momento de cada semana durante el trabajo del equipo?

Cuando conseguimos que el lector de pantalla leyera correctamente la tabla de gastos gracias a los roles `rowgroup`, `row` y `columnheader`. Fue satisfactorio ver que la estructura visual compleja se traducía perfectamente a una estructura lógica accesible.

### d) ¿Cuál ha sido el peor?

Enfrentarnos a errores de validación de accesibilidad que no eran obvios a primera vista, como el contraste de colores en los estados `:hover` o `:focus` de los botones, lo que nos obligó a revisar el CSS más de lo esperado.

### e) ¿Qué has aprendido?

He profundizado en:
* **Roles ARIA:** La diferencia entre usar etiquetas semánticas nativas y forzar semántica con `role="..."` solo cuando es necesario.
* **Gestión del Foco:** La importancia de devolver el foco al elemento disparador (trigger) cuando se cierra un modal o se termina una acción, para no desorientar al usuario.
* **Alertas de Accesibilidad:** Cómo crear un sistema de notificaciones invisible visualmente pero audible para screen readers (`.sr-only` y `aria-live="polite"`).

### f) ¿Qué necesitáis conservar -como equipo- para las próximas semanas?

* **Testing Continuo:** La práctica de validar cada pequeña funcionalidad con el teclado antes de darla por cerrada nos ha ahorrado mucho tiempo de depuración final.
* **Comunicación:** Mantener la división clara de tareas (HTML, JS, Reportes) nos permite avanzar en paralelo sin pisarnos el trabajo.

### g) ¿Qué tenéis que mejorar -como equipo- para las próximas semanas?

* **Automatización:** Sería ideal integrar alguna herramienta de linting de accesibilidad (como `axe-core` o plugins de editor) para detectar fallos de ARIA mientras escribimos código, en lugar de esperar a la revisión manual.
* **Documentación en Código:** A veces los atributos ARIA hacen el HTML muy verboso; deberíamos comentar mejor *por qué* se añade cierto atributo para que no parezca ruido.

### h) ¿Cómo se relaciona ESTE contenido con otros del curso y con tu titulación?

* **Titulación:** Comprender la Accesibilidad Web es un requisito legal y ético en la ingeniería de software moderna. No se trata solo de programar, sino de diseñar para *todos*.
* **Curso:** Se cierran conceptos vistos en teoría sobre estándares web (W3C), usabilidad y diseño centrado en el usuario. La implementación práctica de las normas WCAG refuerza la teoría de interfaces hombre-máquina.
