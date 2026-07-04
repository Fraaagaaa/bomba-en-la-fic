# Informe del Curador-Traductor - Semana 3

**Autor:** Xabier Guitián Lopez
**Grupo:** Guns N' Roses

---

## 1. Objetivos de aprendizaje (Traductor)

Esta semana, el equipo abordó la **Tarea 3: Internacionalización (i18n)**. Los objetivos de aprendizaje clave, tal como los definimos, fueron:

* **Comprender la Internacionalización (i18n) vs. Localización (l10n):**
    * **Concepto:** Diferenciar entre la internacionalización (diseñar la aplicación para que *pueda* ser adaptada) y la localización (la *adaptación* real a un idioma y región específicos).
    * **Objetivo:** Preparar la aplicación para que funcione globalmente, no solo en español.

* **Implementar un Sistema de Traducción de Cadenas:**
    * **Concepto:** Crear un mecanismo centralizado para gestionar las traducciones de todo el texto visible en la interfaz.
    * **Objetivo:** Implementar el módulo `app/i18n.py`, que detecta el idioma del sistema (`detect_locale()`) y proporciona una función (`_()`) para obtener la cadena de texto correcta (español o inglés).

* **Refactorizar la Interfaz de Usuario (Vistas):**
    * **Concepto:** Modificar todos los componentes de la vista (GTK) para que no usen texto "duro" (hardcoded), sino que llamen al sistema de traducción.
    * **Objetivo:** Asegurar que cada `Gtk.Label`, `Gtk.Button` y título de ventana obtenga su texto a través de la función `_()`. Esto se completó en `expenses_view.py` (ej. `_("Add Expense")`, `_("Currency")`), `friends_view.py` (ej. `_("Split - Friends")`) y `main_window.py` (ej. `_("View Friends")`).

* **Internacionalizar Formatos (Unidades):**
    * **Concepto:** Adaptar la visualización de datos que no son solo texto, como las unidades monetarias.
    * **Objetivo:** Implementar la traducción de "Currency" para que muestre "€" en la localización española y "$" en la inglesa, como se define en `i18n.py` y se usa en las vistas.

---

## 2. Recursos Empleados (Curador)

Para alcanzar los objetivos de la Tarea 3, el equipo se basó en los siguientes recursos, complementando los de las semanas 1 y 2:

### 1. Guía de Internacionalización (i18n) en Python
* **Descripción del recurso:** Artículos y guías (como las de Real Python) que explican los conceptos de i18n y l10n en Python, y las diferentes estrategias para manejar traducciones de cadenas (desde simples diccionarios hasta el módulo `gettext`).
* **Utilidad y aplicación a la práctica:** Fue **conceptual y fundamental** para el diseño. Nos ayudó a tomar la decisión de implementar nuestra propia solución ligera en `app/i18n.py` usando un diccionario de Python. Esto fue más rápido de implementar que configurar `gettext` para nuestro caso de uso, aunque también generamos los archivos `.po` y `.mo` como parte del proceso de aprendizaje.

### 2. Documentación del Módulo `locale` de Python
* **Descripción del recurso:** La documentación oficial de la biblioteca estándar de Python para el módulo `locale`.
* **Utilidad y aplicación a la práctica:** Fue un recurso **técnico directo**. Se utilizó para implementar la función clave `detect_locale()` en `app/i18n.py`. Específicamente, la llamada a `locale.getdefaultlocale()[0]` nos permite identificar el código de idioma del sistema operativo del usuario (ej. "es_ES" o "en_US") y así seleccionar la traducción correcta al inicio.

### 3. Hilos de GTK 4 y GLib (revisión de la Tarea 2)
* **Descripción del recurso:** Documentación de PyGObject sobre cómo actualizar la interfaz de usuario de forma segura desde hilos secundarios (`threading`).
* **Utilidad y aplicación a la práctica:** Aunque este recurso fue clave en la Tarea 2, el informe del analista de esta semana menciona que Xabier realizó correcciones vitales a la **concurrencia**. Este recurso fue **revisado y esencial** para finalizar esa tarea. La solución implementada (`GLib.idle_add()`) fue el mecanismo que usamos para que los hilos de red (ej. `_slow_load_friends`) pudieran enviar datos (o errores) de vuelta al hilo principal de GTK sin bloquear o corromper la interfaz.