## ¿Qué es WAI-ARIA?
El Web Accessibility Initiative - Accessible Rich Internet Applications (WAI-ARIA) es una iniciativa del World Wide Web Consortium (W3C) que proporciona especificaciones para mejorar la accesibilidad de las aplicaciones web interactivas y dinámicas. ARIA proporciona una serie de atributos y roles adicionales que pueden ser añadidos al código HTML, especialmente cuando se utilizan tecnologías como AJAX, JavaScript y otras técnicas de desarrollo web avanzadas.

Se suele utilizar en:
+ Controles interactivos, como menús, sliders, pop-ups...
+ Regiones dinámicas.
+ Páginas con estructura no estándar o de generación dinámica.

## Roles

### Abstract roles
No tienen una representación directa en la interfaz de usuario, pero sirven como roles base o "plantillas" para otros roles más concretos. Estos son:
+ **command:** objeto que puede ser activado por el usuario para realizar una acción.
	+ Roles relacionados: button, menuitem, menuitemcheckbox, menuitemradio.
+ **composite:** widget que contiene varios objetos secundarios que, cuando se combinan, forman un único objeto interactivo.
	+ Roles relacionados: grid, tree, select, scrollbar.
+ **input:** objeto que permite al usuario ingresar información, como texto o valores numéricos.
	+ Roles relacionados: textbox, checkbox, radio, spinbutton.
+ **range:** widget que permite al usuario seleccionar un valor dentro de un rango.
	+ Roles relacionados: progressbar, slider, spinbutton.
+ **roletype:** rol abstracto que sirve como base para todos los roles en WAI-ARIA.
	+ Roles relacionados: Todos los roles de WAI-ARIA.
+ **section:** sección de contenido que forma parte de una estructura más grande.
	+ Roles relacionados: alert, log, status, tabpanel.

### Landmark roles
Son roles específicos que se utilizan para identificar y etiquetar secciones clave de una página web.

|**Rol WAI-ARIA**|**Etiqueta HTML5**|
|---|---|
|banner|header|
|navigation|nav|
|main|main|
|complementary|aside|
|contentinfo|footer|
### Document structure roles
Proporcionan una manera de describir la organización y la estructura de las páginas web, especialmente cuando la estructura no se puede expresar de manera adecuada mediante las etiquetas HTML estándar.

### Widget roles
Se utilizan para describir objetos de la interfaz de usuario con los que los usuarios pueden interactuar.

+ Widgets Compuestos:
	- **combobox**
	- **grid**
	- **listbox**
	- **menu, menubar**
	- **tablist** 
	- **tree, treegrid**
+ Widgets Simples:
	- **alert**
	- **button**
	- **checkbox:**
	- **dialog:**
	- **gridcell**
	- **link**
	- **progressbar**
	- **radio**
	- **scrollbar**
	- **tab, tabpanel**
	- **textbox**
	- **tooltip**
## Estados y propiedades

### Atributos de widgets
Los atributos de widgets son propiedades y estados que se utilizan para mejorar la accesibilidad de los elementos interactivos en una página web. Estos atributos proporcionan información adicional sobre la función, comportamiento y estado actual de un widget.
### Atributos de relación
Los atributos de relación son atributos que describen asociaciones entre elementos que no pueden ser directamente deducidas solo por la estructura del documento. Estos son:
### Live regions
Los Live Regions son utilizados para indicar que el contenido de una región puede cambiar de forma dinámica sin que el usuario interactúe directamente con ella. Notifica cambios o actualizaciones importantes en tiempo real. 