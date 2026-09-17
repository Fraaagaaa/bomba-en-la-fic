## WCAG
Las Web Content Accessibility Guidelines son un conjunto de pautas desarrolladas por el World Wide Web Consortium (W3C) con el objetivo de hacer que el contenido web sea más accesible para personas con discapacidades. El estándar actual es el WCAG 2.2, pero ya se está trabajando en el 3. Se divide en niveles:
+ A: Esencial
+ AA: Soporte ideal (recomendado)
+ AAA: Casos especializados

Los contenidos web deben ser:
+ **Perceptibles:** consiste en proporcionar alternativas de texto para vídeos, imágenes, etc; proporcionar alternativas a medios dependientes del tiempo como vídeos o audios, presentar contenidos en diferentes formas y facilitar la visualización de estos.
+ **Operables:** crear webs accesibles sin ratón, proporcionar tiempo suficiente para leer, diseñar contenidos que eviten por ejemplo epilepsia, proporcionar ayudas como volver atrás, o facilitar entradas a través de métodos que no sean teclado, como gestos.
+ **Entendibles:** consiste en hacer contenidos legibles y entendibles, hacer que la apariencia sea predecible, es decir, similares a páginas que ya existen y ayudar a los usuarios a corregir errores.
+ **Robustos:** maximizar la compatibilidad con los navegadores.

## Sección 508
Son una serie de disposiciones mantenidas o utilizadas por el gobierno federal de los Estados Unidos que establecen estándares y pautas para garantizar que las personas con discapacidades tengan acceso y utilidad equivalentes a la información y datos que proporciona el gobierno federal a través de tecnologías de la información.<br>
### Requisitos Técnicos Clave (Checklist para el examen)
Para que un sistema sea "508 Compliant", debe cumplir con:
* **Texto Alternativo:** Todas las imágenes no decorativas deben tener una descripción textual.
* **Navegación por Teclado:** Todas las funciones deben ser operables sin usar un ratón.
* **Contraste:** El texto debe tener un contraste suficiente con el fondo (mínimo 4.5:1 para texto normal).
* **Uso del Color:** No se puede usar el color como **único** medio para transmitir información.
* **Multimedia:** Los vídeos deben tener subtítulos sincronizados y, en algunos casos, audiodescripción.
* **Formularios:** Las etiquetas (`<label>`) deben estar correctamente vinculadas a sus campos.
* **Live Regions:** Uso de ARIA para anunciar cambios dinámicos a lectores de pantalla.

### Requisitos
+ **Técnicos:** la codificación de la página web debe ser compatible con tecnologías asistidas.
+ **Funcionales:** el sistema tiene que ser usable por personas con discapacidad.
+ **Soporte:** la documentación tiene soporte e información alternativa.

### Imágenes y tablas
No se deben incluir imágenes relevantes como background-images. Todo contenido no textual debe tener una alternativa. Por ejemplo:
``` html
<img src="imagen.jpg" alt="Descripción de la imagen">
```


En HTML el atributo "alt" se utiliza para proporcionar un texto alternativo que describe el contenido de la imagen. La etiqueta "caption" se utiliza para proporcionar un título o una descripción breve de la tabla.
``` html
<img src="logo.png" alt="Logo empresa" />
<table>
<caption>Titulo de la tabla</caption>
...
</table>
```

Se puede usar WAI-ARIA con el rol "presentation" para descripciones más largas y para marcar imágenes decorativas (aquellas que no aportan información significativa al contenido).
``` html
<img src="decorative-image.png" alt="" role="presentation" />
```

### Contenidos repetitivos
El contenido principal sea fácilmente accesible sin tener que atravesar secciones repetitivas en cada página del sitio web.
### Colores
La información no puede depender del color. Hay que usar colores que contrasten bien entre el fondo y el primer plano. Por tanto, no debemos, entre muchas otras cosas:
+ Usar colores para marcar acciones.
+ Indicar errores marcando bordes en rojo.
+ Marcar campos obligatorios en un formulario pintándolos de un color.

### Formularios
Los formularios deben:
+ Evitar cambios de contexto inesperados en una aplicación o sitio web cuando un usuario selecciona o introduce información, especialmente al interactuar con botones o enlaces.
+ Incluir etiquetas descriptivas o instrucciones claras junto a los campos de entrada en formularios.
+ Cuando se produce un error, proporcionar a los usuarios información clara sobre la naturaleza del error, así como sugerencias para corregirlo.

### Enlaces y botones
Es esencial que el texto del enlace o botón proporcione una indicación clara del destino o la acción que se llevará a cabo al interactuar con él. Para ello debemos:
+ Evitar enlaces y botones de pulsa aquí y ver más. La forma correcta sería:
+ No usar el mismo texto para varios enlaces o botones. La forma correcta sería:
+ El destino de cada enlace o botón se debe indicar. La forma correcta sería:

### Teclado y focus
Todas las funcionalidades deben ser operables mediante un teclado. Los elementos HTML nativos, como botones y enlaces, generalmente tienen características de accesibilidad integradas. No debes eliminar estas características al personalizar o estilizar los elementos. Cuando se crean elementos personalizados que no son nativos de HTML, como botones personalizados o componentes interactivos, es crucial utilizar WAI-ARIA y JavaScript para proporcionar información adicional sobre la accesibilidad y replicar el comportamiento esperado.<br>
Cuando un usuario navega utilizando el teclado, es necesario que haya un indicador visual que destaque el elemento que tiene el foco. Cuando hay un orden lógico en la navegación, como en formularios o en componentes interactivos, los elementos que reciben el foco mediante la navegación con el teclado deben seguir ese orden. La propiedad "tabindex" se utiliza para determinar el orden en el que los elementos reciben el foco cuando se navega utilizando la tecla Tab. Asignar "tabindex=0" a un elemento específico lo incluye en el flujo natural de tabulación, asegurándote de que sea accesible mediante el teclado. Esto es útil para elementos que no son botones o enlaces, pero que aún deben ser interactivos.<br>
### Hoja de estilos
La información, estructura y relaciones entre los elementos de la página deben ser determinadas programáticamente, es decir, la estructura y la información en la página deben ser definidas de manera que las tecnologías de asistencia puedan interpretar y presentar la información de manera significativa. Esto se hace con HTML semántico.<br>
Para ello debemos evitar usar "before" y "after" en CSS, ya que esto da cierta información y esta siempre debe estar en el HTML. <br>
Además hay que evitar los posicionamientos absolutos en CSS. Es una técnica en CSS que se utiliza para colocar un elemento en relación con su contenedor más cercano que puede desvincular los elementos de su flujo natural en el documento.<br>
### Títulos y cabeceras
Toda página web debe tener un título descriptivo.
``` html
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Ejemplo de Título HTML</title>
</head>
```

Para estructurar los contenidos se utilizan las cabeceras (h1, h2, ...h6). Es importante no saltarse ningún nivel. Si se desea otro tamaño de cabecera se modifica en el CSS.

### Elementos multimedia
Para contenidos de audio, es importante proporcionar una transcripción textual del contenido hablado. Cuando un vídeo no incluye sonido o tiene un contenido relevante solo en audio, es crucial proporcionar una transcripción textual o una pista de sonido alternativa. Si contienen diálogo o información audible, se deben proporcionar subtítulos.

Cuando el contenido multimedia, como audio o vídeo, se inicia automáticamente al cargar una página, es esencial proporcionar un mecanismo para que los usuarios puedan detener o pausar ese contenido. Cuando se incluyen subtítulos o descripciones de audio, es importante proporcionar mecanismos para que los usuarios controlen su visibilidad o audición.

### Otros
Se deben evitar elementos en la página que tengan movimientos, desplazamientos, parpadeos o destellos excesivos es esencial para reducir el riesgo de provocar molestias o problemas de accesibilidad, especialmente para personas con sensibilidades visuales.<br>
Los CAPTCHAs basados solo en imágenes pueden ser inaccesibles para lectores de pantalla. Se deben utilizar alternativas como CAPTCHAs auditivos o basados en texto.<br>
Para mejorar la accesibilidad y la experiencia del usuario, es importante indicar el idioma general de la página y, si hay secciones específicas que cambian de idioma, proporcionar información sobre el idioma de esas secciones.<br>
### Validación del HTML
+ Toolbars.
+ Pruebas en navegador sin CSS y JS.
+ Pruebas en navegador de solo texto.
+ Navegar sin ratón.
+ Tecnologías asistivas, como lectores de pantalla.
<br>
# Resumen
## Estándares Principales

### WCAG (Web Content Accessibility Guidelines)
Desarrolladas por el W3C. La versión actual es la **2.2**. Se dividen en tres niveles de conformidad:
* **A (Esencial):** El nivel mínimo de accesibilidad.
* **AA (Soporte ideal):** El estándar recomendado para la mayoría de los sitios web.
* **AAA (Especializado):** Casos muy específicos y estrictos.

### Sección 508
Normativa del gobierno federal de EE. UU. que exige que la tecnología sea accesible para empleados y ciudadanos con discapacidad. Se divide en requisitos:
* **Técnicos:** Compatibilidad con lectores de pantalla.
* **Funcionales:** Usabilidad real.
* **Soporte:** Documentación accesible.
## Los 4 Principios Fundamentales (POUR)

Para que una web sea accesible, debe cumplir con estos pilares:

1.  **Perceptible:** El contenido debe presentarse de forma que los usuarios puedan detectarlo (alternativas de texto, subtítulos, buen contraste).
2.  **Operable:** La interfaz debe ser fácil de usar (navegación por teclado, evitar destellos, tiempo suficiente para leer).
3.  **Entendible:** La información y el manejo deben ser comprensibles (lenguaje claro, errores fáciles de corregir).
4.  **Robusto:** El contenido debe ser compatible con diversas aplicaciones de usuario, incluyendo tecnologías asistivas.
## Guía Práctica de Implementación
### Contenido Visual
* **Atributo `alt`:** Obligatorio para imágenes informativas.
* **Decoración:** Usar `role="presentation"` o `alt=""` para imágenes que no aportan información.
* **Tablas:** Usar la etiqueta `<caption>` para dar un título descriptivo.

### Navegación y Estructura
* **HTML Semántico:** Usar etiquetas correctas (`<nav>`, `<main>`, `<header>`) en lugar de abusar de `<div>`.
* **Jerarquía:** No saltar niveles de encabezados (ej. pasar de `<h1>` a `<h3>`).
* **Skip Links:** Enlaces internos para saltar menús repetitivos y llegar al contenido principal.

### Formularios
* **Etiquetas:** Uso de `<label>` vinculado mediante el atributo `for`.
* **Agrupación:** Uso de `<fieldset>` y `<legend>` para grupos de campos relacionados.
* **Instrucciones:** Uso de `aria-describedby` para asociar textos de ayuda con los campos.

### Interacción (Teclado y Foco)
* **Operabilidad:** Todo debe poder usarse sin ratón.
* **Foco Visual:** Nunca eliminar el indicador visual de selección (el borde que aparece al tabular).
* **Orden Lógico:** Seguir el flujo natural de lectura al tabular.

### Diseño y Estilo (CSS)
* **Color:** No debe ser el único medio para transmitir información (ej. no marcar un error solo con color rojo).
* **Contraste:** Asegurar que el texto sea legible sobre el fondo.
* **Flujo:** Evitar el posicionamiento absoluto que desordene el contenido para los lectores de pantalla.

### Multimedia
* **Transcripciones:** Necesarias para audios.
* **Subtítulos:** Necesarios para vídeos con diálogo.
* **Control:** El usuario siempre debe poder pausar o detener contenidos automáticos.

## Validación y Pruebas
Para confirmar el cumplimiento, se recomienda:
1.  **Pruebas manuales:** Navegar solo con el teclado.
2.  **Lectores de pantalla:** Escuchar cómo se interpreta la web.
3.  **Pruebas sin estilo:** Desactivar CSS y JS para verificar que el contenido sigue siendo legible y lógico.