# Informe de Accesibilidad - SplitWithMe (Redo)

Este documento recoge las pruebas exploratorias planificadas y realizadas para asegurar que la aplicación cumple con las normas WAI-ARIA y es accesible.

## 1. Plan de Pruebas Exploratorias

### 1.1 Navegación y Estructura Semántica

| ID | Prueba | Resultado Esperado | Estado | Notas |
|----|--------|--------------------|--------|-------|
| T1 | Navegación por Teclado (Tab) | El foco debe moverse de forma lógica por todos los elementos interactivos. | ✅ Pasa | Verificado. |
| T2 | Jerarquía de Encabezados | La estructura `h1` -> `h2` -> `h3` debe ser coherente. La sección de Deudas (`h3`) debe integrarse correctamente. | ✅ Pasa | Integración de Deudas correcta. |
| T3 | Regiones (Landmarks) | Las regiones principales (`header`, `main`) deben estar identificadas. | ✅ Pasa | Semántica HTML correcta. |

### 1.2 Interacción y Foco

| ID | Prueba | Resultado Esperado | Estado | Notas |
|----|--------|--------------------|--------|-------|
| T4 | Cambio de Pestañas | Al cambiar a "Amigos", la lista de deudas se renderiza y es accesible. | ✅ Pasa | El foco no se atrapa. Lectura correcta. |
| T5 | Edición de Gasto (Entrada) | El foco debe moverse al primer input al pulsar "Editar". | ✅ Pasa | Implementado. |
| T6 | Edición de Gasto (Salida) | El foco debe volver al botón "Editar" tras guardar/cancelar. | ✅ Pasa | Implementado. |

### 1.3 Feedback y Live Regions

| ID | Prueba | Resultado Esperado | Estado | Notas |
|----|--------|--------------------|--------|-------|
| T7 | Feedback General | Acciones importantes (Guardar, Añadir Amigo) deben ser anunciadas por el lector de pantalla. | ✅ Pasa | `announce()` implementado. |

## 2. Conclusiones

La accesibilidad ha sido restaurada completamente. La nueva funcionalidad de Deudas se integra correctamente en la estructura semántica y no interfiere con la navegación por teclado.
