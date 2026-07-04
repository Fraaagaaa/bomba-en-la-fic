# Informe del Facilitador-Administrador - Semana 3

## Registro de tareas llevadas a cabo durante la semana 3

- **Auditoría de Accesibilidad (Tarea 3)**
  - **Descripción**: Revisión completa de la interfaz para detectar barreras de navegación y semántica.
  - **Responsables**: Miguel Fraga (Líder QA), Pedro Gómez, Xabier Guitian.
  - **Estado**: Completado.
  - **Notas**: Se identificaron puntos críticos en la navegación por teclado y falta de etiquetas en iconos.

- **Implementación de WAI-ARIA**
  - **Descripción**: Inyección de atributos ARIA en el HTML y gestión de anuncios de estado.
  - **Responsables**: Xabier Guitian, Pedro Gómez.
  - **Estado**: Completado.
  - **Detalles**: Se evitaron redundancias de etiquetas y se aseguró que el árbol de accesibilidad fuera coherente.

- **Gestión Avanzada de Foco**
  - **Descripción**: refactorización de `script.js` para asegurar un flujo de foco coherente al abrir/cerrar ediciones.
  - **Responsables**: Miguel Fraga, Pedro Gómez.
  - **Estado**: Completado.
  - **Notas**: Fue necesario crear referencias a los elementos editados para poder devolver el foco correctamente.

- **Documentación de Pruebas**
  - **Descripción**: Creación del `informe-accesibilidad.md` y actualización de documentación de proyecto.
  - **Responsables**: Pedro Gómez (Facilitador).
  - **Estado**: Completado.

## Estado del repositorio en la semana 3

El repositorio ha evolucionado hacia una versión robusta y accesible:

- **Estructura de Directorios**: Se organizó la entrega en `semana 3/`, separando claramente los entregables de documentación de cada fase.
- **Calidad de Código**: `index.html` pasa validaciones de accesibilidad estándar (Lighthouse/Axe). `script.js` maneja errores de usuario y feedback de forma no intrusiva.
- **Sin Conflictos**: El trabajo se ha integrado linealmente sin conflictos de ramas significativos.

No existen issues abiertos críticos que bloqueen la entrega de la práctica.
