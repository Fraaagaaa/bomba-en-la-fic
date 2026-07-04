# Núcleo y Configuración Global
- Punto de entrada (`src/main.jsc`): Es el archivo principal que arranca la aplicación React y renderiza el componente raíz dentro del DOM.
- Almacén de estado (`src/store/`): Aquí se configura el **Redux Store** en `index.js`, cambiando todos los reductores de la aplicación mendiante `rootReducer.js`.
- Internacionalización (`src/i18n/`): Gestiona los mensajes en diferentes idiomas (español, inglés, gallego) para permitir que la interfaz cambie de idioma dinámicamente.

# Capa de Servicios y Comunicación (src/backend)

Esta capa actúa como el punete con la API del backend explicada anteriormente.
- `appFetch.js`: Centraliza las peticiones HTTP (utilizando `fetch`), gestionando aspectos comunes como la inclusión del token JWT en las cabeceras y el manejo de errores de red.
- Serivicos específicos: Archivos como `userService.js`, `catalogService.js` y `shoppingService.js` definen funciones que realizan llamadas a los endpoints específicos del servidor, abstrayendo la complejidad de la comunicación.

# Organización por Módulos
La aplicaicón divide su lógica en módulos independientes. Cada módulo suele contener:
- Componentes: Vistas de React (archivos `.jsx` que definen la interfaz de usuario.
- Acciones (`actions.js`) y Tipos (`actionTypes.js`): Definen los eventos que pueden ocurrir
- Reducor (`reducer.js`): Determina cómo cambia el estado del módulo en respuesta a las acciones.
- Selectores (`selectors.js`): Funciones para extraer datos específicos del estado de Redux de forma eficiente.

# Interacción entre Archivos

El flujo típico de una operación es el siguiente:
1. Componente: Un componente del módulo catálogo (`src/modules/catalog/components/Billboard.jsx`) solicita datos al montarse.
2. Acción: Se dispara una acción asíncrona definida en `src/modules/catalog/actions.js`.
3. Servicio: Dicha acción llama a una función en `src/backend/catalogService.js`, que realiza la petición HTTP al backend
4. Reductor: Una vez recibida la respuesta, se lanza una acción de "éxite" que el reductor (`src/modules/catalog/reducer.js`) caputra para actualizar el estado con la nueva información.
5. Actualización de UI: El componente, suscrito a esa parte del estado mediante un selector (`src/modules/catalog/selectors.js`) se vuelve a renderizar automáticamente con los datos acumulados.

# Componentes comunes y Estructura Base

- Módulo `app`: Define la estructura de la página (cabecera, cuerpo, pie de página) y las rutas de navegación en `App.jsx`.
- Módulo `common`: Contiene componentes reutilizables en toda la aplicación, como el paginador (`Pager.jsx`), cuadros de dialogo de error (`ErrorDialog.jsx`) o enlaces de retroceso (`BackLink.jsx`).
- Estilos `src/styles.css`: Define la apariencia global de la aplicación mediante reglas CSS tradicionales

