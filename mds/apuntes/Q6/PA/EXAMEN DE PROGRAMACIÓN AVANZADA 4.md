
---
##### 1.

Analice detalladamente el ciclo de vida del siguiente código reactivo anidado en el componente `ProductDetails`, ejecutado bajo el escrutinio del modo de desarrollo local con Vite y `<React.StrictMode>`:


```JavaScript
useEffect(() => {
    dispatch(actions.findProduct(id));

    return () => dispatch(actions.clearProduct());
}, [id]);
```

Indique qué dinámica computacional y control del rastro en memoria experimentará este fragmento en la pestaña del explorador web al montarse:

- [ ] a) El recolector de basura nativo de ECMAScript aniquila la promesa asíncrona interpuesta por la orden `dispatch`, impidiendo su resolución y dejando el componente en un estado espectral irrecuperable.
    
- [ ] b) Se desencadena un bucle infinito de re-renderizado debido a que la matriz de dependencias `[id]` muta su puntero referencial matemático tras cada inserción pasiva efectuada en el Virtual DOM.
    
- [ ] c) El componente experimentará un ciclo forzado de montaje, desmontaje instantáneo ejecutando la función limpiadora (clean-up), y un nuevo montaje; provocando dos peticiones de red idénticas visibles en consola.
    
- [ ] d) La directiva de limpieza devuelta por el Hook carece de capacidad vinculante en este ámbito asíncrono, por lo que React ignorará la orden y provocará incondicionalmente una fuga de memoria letal.
    

> [!success]- **Soluciones y Justificaciones (Evaluación Forense)**
> 
> **Opción correcta: c) El componente experimentará un ciclo forzado de montaje, desmontaje instantáneo ejecutando la función limpiadora (clean-up), y un nuevo montaje; provocando dos peticiones de red idénticas visibles en consola.**
> 
> **Justificación (Ref. Tema 7 y "preguntas-examen.pdf", Pregunta 19 extra):** La opción "c" describe al milímetro el comportamiento del Strict Mode de React 18 en la fase de desarrollo. React inyecta intencionadamente esta "terapia de choque" doble (montar $\rightarrow$ limpiar $\rightarrow$ montar) para auditar con ferocidad si el programador ha diseñado una función de limpieza sin fallos ocultos. Las fugas de memoria o el colapso del Event Loop (opciones a, b y d) son inventos técnicos para despistar a quienes no han abierto la consola de su navegador durante las prácticas.

##### 2.

En el marco de la gestión del estado global mediante Redux (Tema 6), considere un componente visual `UnreadMessagesIcon` que utiliza un Hook de la siguiente forma: `const count = useSelector(selectors.getUnreadCount);`. Supongamos que una acción de red elimina permanentemente de la matriz global `messages` un mensaje que el usuario ya había leído previamente. Identifique la reacción gráfica del sistema:

- [ ] a) El reductor raíz intercepta la eliminación pero, al detectar una violación del patrón "Dirty State" en los punteros del array, aborta la mutación y congela la interfaz gráfica permanentemente en el explorador.
    
- [ ] b) La ejecución del `dispatch` procesa íntegramente el reductor raíz mutando el arreglo físico, pero el componente visual omitirá repintarse porque la comprobación referencial (`===`) corrobora que el valor numérico extraído (`count`) permanece idéntico.
    
- [ ] c) React forzará un repintado masivo y parasitario del icono en el Virtual DOM, ya que el tamaño estructural del arreglo global ha transmutado y la regla de inmutabilidad dictamina obligatoriamente una alteración referencial global.
    
- [ ] d) El componente levantará una advertencia paralizante de tipo `OptimisticLockingFailureException` al intentar acceder superficialmente a una propiedad extirpada temporalmente del diccionario centralizado `byId`.
    

> [!success]- **Soluciones y Justificaciones (Evaluación Forense)**
> 
> **Opción correcta: b) La ejecución del dispatch procesa íntegramente el reductor raíz mutando el arreglo físico, pero el componente visual omitirá repintarse porque la comprobación referencial (===) corrobora que el valor numérico extraído (count) permanece idéntico.**
> 
> **Justificación (Ref. Tema 6 y "preguntas-examen.pdf", Pregunta 7 y 50 extra):** Engaño clásico de rendimiento de Redux evaluado en exámenes. Aunque el array matriz gigante de mensajes cambie su longitud, el `useSelector` actúa como escudo protector. Solo extrae el entero (`count` de no leídos). Puesto que borramos un mensaje ya leído, el número de no leídos sigue siendo, por ejemplo, 5. La igualdad matemática estricta `5 === 5` en el Virtual DOM detiene en seco la propagación, salvando valiosa CPU y evadiendo repintados catastróficos.

##### 3.

Concluido el desarrollo del Frontend React, el programador abate el servidor en caliente de desarrollo y despacha la instrucción oficial `npm run build` gestionada por Vite. Atendiendo al dictamen arquitectural, indique las mutaciones topológicas sufridas en los ficheros amparados en la nueva carpeta física matriz `dist`:

- [ ] a) Se instanciará un servidor de aplicaciones Tomcat embebido, unificando orgánicamente la lógica estática con el Virtual DOM para mitigar y evadir eficazmente los bloqueos de seguridad originarios (Same-Origin Policy).
    
- [ ] b) La sintaxis JSX se transfiere en estado de latencia nativa, induciendo a que cada explorador cliente active el micro-compilador Babel al inicio para interpretar las inyecciones asíncronas en tiempo real.
    
- [ ] c) Todas las estructuras JSX sufren una transpilación descendente a JavaScript puro; paralelamente, el código se minimiza con suma agresividad eliminando comentarios, generando archivos inermes y estáticos.
    
- [ ] d) El empaquetador repudia compilar nativamente aquellos módulos que estén suscritos asincrónicamente a Redux, exigiendo que se disocien en archivos `.war` aptos para ecosistemas tradicionales corporativos.
    

> [!success]- **Soluciones y Justificaciones (Evaluación Forense)**
> 
> **Opción correcta: c) Todas las estructuras JSX sufren una transpilación descendente a JavaScript puro; paralelamente, el código se minimiza con suma agresividad eliminando comentarios, generando archivos inermes y estáticos.**
> 
> **Justificación (Ref. Tema 5 y "preguntas-examen.pdf", Pregunta 29 extra):** Vite es un transpilador despiadado. JSX no existe en los estándares de los navegadores; es "azúcar sintáctico". El comando `npm run build` extrae toda esa magia, la tritura a lenguaje primitivo (JavaScript normal) y extirpa blancos y comentarios, generando recursos estáticos óptimos para producción en la carpeta `dist`. Es falso que incorpore Tomcat o requiera compilar en Babel on-the-fly.

##### 4.

Durante el diseño de la Capa de Acceso a Datos (Spring Data JPA), usted modela una entidad `User` que contiene la propiedad privada `String userName`. Aplicando el patrón de consultas mediante convenciones de nombrado, redacta la siguiente firma en su interfaz DAO:


```Java
public interface UserDao extends CrudRepository<User, Long> {
    Optional<User> findByuserName(String userName);
}
```

Prevea el comportamiento del motor transaccional al levantar el ecosistema de persistencia:

- [ ] a) Spring Data generará dinámicamente un árbol SQL optimizado en tiempo de ejecución, mapeando ágilmente y sin error la consulta sobre la columna nativa `user_name` de la base de datos subyacente de MySQL.
    
- [ ] b) La interfaz carece de la inyección dogmática `@Repository` en su cabecera, lo que impedirá irrevocablemente que el contenedor IoC localice el componente, provocando una caída catastrófica en las dependencias.
    
- [ ] c) Todas las anteriores aplican para mitigar consultas redundantes tipo `SELECT COUNT(*)` en entornos de alta concurrencia o perfiles de despliegue automatizados amparados por `@ActiveProfiles("test")`.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Soluciones y Justificaciones (Evaluación Forense)**
> 
> **Opción correcta: d) Ninguna de las anteriores.**
> 
> **Justificación (Ref. Tema 2 - "Búsquedas mediante convenciones de nombrado"):** Un castigo por falta de agudeza visual. El atributo en Java es `userName`. La convención dogmática de Spring Data estipula que la propiedad anexada al verbo `findBy...` debe obligatoriamente comenzar en Mayúscula (CamelCase puro). Redactar `findByuserName` (con 'u' minúscula) corromperá irremediablemente el escáner de reflexión en tiempo de arranque, lanzando una excepción sistémica que impedirá inicializar todo el backend. La respuesta C es palabrería, y la A asume un funcionamiento inexistente ante este error sintáctico mortal.

##### 5.

En el enrutador matricial principal de nuestra SPA (`Body.jsx`), se configuran diversas rutas de navegación descendente de la siguiente manera secuencial:


```JavaScript
<Routes>
    <Route path="/*" element={<Home/>}/>
    <Route path="/catalog/product-details/:id" element={<ProductDetails/>}/>
</Routes>
```

Asumiendo que el usuario introduce en su navegador la URL explícita `/catalog/product-details/14`, seleccione el veredicto arquitectónico del sistema:

- [ ] a) React Router acata incondicionalmente la primera directriz topológica por estricto orden de aparición en el fichero, interceptando la URL y renderizando erróneamente `<Home>` debido a la voracidad del comodín.
    
- [ ] b) Se desencadenará una superposición de componentes clónicos en el Virtual DOM, forzando pasivamente a React a dibujar `<Home>` y `<ProductDetails>` simultáneamente, destruyendo la maquetación de React Bootstrap.
    
- [ ] c) La sintaxis JSX repudiará frontalmente la inyección de los dos puntos paramétricos (`:id`) en un entorno estricto de compilación, exigiendo codificar la variable previamente mediante la función `encodeURIComponent()`.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Soluciones y Justificaciones (Evaluación Forense)**
> 
> **Opción correcta: d) Ninguna de las anteriores.**
> 
> **Justificación (Ref. Tema 7 - "Layout y enrutamiento - Cambios de pantalla" y "preguntas-examen.pdf", Pregunta 59 extra):** Esta es la gran trampa de enrutamiento del Aula Virtual. Si usted cree la "a", no entiende las SPAs. React Router NO evalúa secuencialmente por orden posicional descendente de líneas. El componente de React Router escanea todo el árbol de rutas e impone inteligencia deductiva: ejecuta invariablemente la ruta que posea la correspondencia léxica más específica (Exact Match), relegando el comodín `/*` para rutas residuales o caídas. Puesto que ninguna de las afirmaciones A, B o C describe la verdad absoluta sobre la especificidad de rutas, la respuesta es Ninguna.

##### 6.

En el desarrollo de la Capa de Servicios REST fronteriza, los casos de uso "Iniciar Sesión" (`/users/login`) y "Registrarse" (`/users/signUp`) se modelan invariablemente bajo el decorador `@PostMapping`. Dado que conceptualmente no son operaciones transaccionales CRUD convencionales de inserción, ¿cuál es el motivo imperativo para usar POST?

- [ ] a) El estándar del protocolo HTTP 1.1 prohíbe de forma imperativa y absoluta la transferencia de cualquier parámetro simple a través de la URL de enrutamiento, obligando a emplear incondicionalmente el cuerpo de la petición.
    
- [ ] b) Sirve para sortear la intervención pasiva de la Caché L1 de Hibernate, permitiendo que las entidades de seguridad transitorias se alojen temporalmente en el `sessionStorage` sin ensuciar la RAM.
    
- [ ] c) Todas las anteriores fundamentan el uso extendido del patrón "Overloaded POST" implementado unívocamente por Spring.
    
- [ ] d) Es una táctica estricta de seguridad: las operaciones que transportan credenciales altamente sensibles deben viajar codificadas y ocultas en el Body, eludiendo la exposición temeraria que sufrirían insertadas en un Query String usando GET.
    

> [!success]- **Soluciones y Justificaciones (Evaluación Forense)**
> 
> **Opción correcta: d) Es una táctica estricta de seguridad: las operaciones que transportan credenciales altamente sensibles deben viajar codificadas y ocultas en el Body, eludiendo la exposición temeraria que sufrirían insertadas en un Query String usando GET.**
> 
> **Justificación (Ref. Tema 4 - "Mapeo de Rutas y Parámetros"):** Aunque tradicionalmente un Login solo consulta datos y se adecuaría teóricamente a un GET, la arquitectura REST impone el uso del patrón "Overloaded POST". Los datos incrustados en URL (GET) terminan irremediablemente cacheados en historiales de proxys, logs del sistema o pestañas de navegación. Insertarlos asincrónicamente mediante POST blinda dichas propiedades alojándolas en las profundidades del Payload binario.

##### 7.

Un componente reactivo encargado de pintar el bloque descriptivo de un artículo (`ProductDetails`) intercepta en su estado local que la información solicitada aún no ha retornado desde el Backend (la variable `product` es matemática y estrictamente `null`). Consecuentemente, el desarrollador aplica el patrón de guarda y programa: `if (!product) { return null; }`. Identifique la consecuencia gráfica:

- [ ] a) El componente suspende su aportación visual de forma orgánica y legítima, no generando ningún nodo HTML perjudicial en la vista mientras aguarda pasivamente la resolución del Event Loop.
    
- [ ] b) React levantará una excepción nativa letal en la consola, ya que la arquitectura impone dogmáticamente devolver al menos un fragmento vacío (`<></>`) para preservar inalterada la topología del árbol de renderizado.
    
- [ ] c) Se induce una fuga de memoria (memory leak) de altísima severidad: al no renderizar la vista, el Hook `useEffect` pierde su anclaje referencial en RAM y omite eternamente la invocación de su limpieza (clean-up).
    
- [ ] d) El enrutador React Router intercepta el volcado nulo y, deduciendo de facto un Error HTTP 404 Not Found, redirige pasivamente al usuario desautenticado a la página perimetral comodín `PageNotFound`.
    

> [!success]- **Soluciones y Justificaciones (Evaluación Forense)**
> 
> **Opción correcta: a) El componente suspende su aportación visual de forma orgánica y legítima, no generando ningún nodo HTML perjudicial en la vista mientras aguarda pasivamente la resolución del Event Loop.**
> 
> **Justificación (Ref. Tema 7 - "Caso de Uso Ver Detalles de un Producto"):** El uso del retorno pasivo `null` (`return null;`) constituye el paradigma recomendado y canónico para bloquear el renderizado mientras se interroga por red al Backend para extraer los atributos de un estado local nulo (como el `product` recién ensamblado por el `useParams`). No revienta ningún Hook ni corrompe el Clean-up; sencillamente dictamina la ausencia de dibujo en pantalla en ese fotograma de renderizado sin ocasionar catástrofes en Vite.

##### 8.

Cuando el interceptor global `@ControllerAdvice` interviene como dique de contención para atajar anomalías semánticas o validaciones rotas, ostenta la responsabilidad arquitectónica de redactar el JSON del fallo en el idioma nativo del consumidor (Internacionalización o i18n). ¿Cómo instiga Spring este mapeo lingüístico para interrogar a su `MessageSource`?

- [ ] a) El desarrollador extrae programáticamente la variable de zona de la firma encriptada del JWT mediante `@RequestAttribute`, pasándosela a los repositorios idiomáticos para evadir las políticas restrictivas de orígenes.
    
- [ ] b) El contenedor intercepta silenciosamente la cabecera preestablecida `Accept-Language` originada por el navegador del cliente, instanciando y delegando un objeto pasivo `Locale` directamente en las firmas de captura locales.
    
- [ ] c) Todas las anteriores.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Soluciones y Justificaciones (Evaluación Forense)**
> 
> **Opción correcta: b) El contenedor intercepta silenciosamente la cabecera preestablecida Accept-Language originada por el navegador del cliente, instanciando y delegando un objeto pasivo Locale directamente en las firmas de captura locales.**
> 
> **Justificación (Ref. Tema 4 y "preguntas-examen.pdf", Pregunta 28 extra):** Los sistemas verdaderamente Stateless desprecian vincular preferencias a la base de datos para no degradar cachés innecesariamente. Delegan la geolocalización lingüística confiando plenamente en la propiedad estándar HTTP provista por el protocolo `Accept-Language`. Spring Web orquesta este proceso transmutando la cabecera hacia su homónimo en ecosistema Java (la clase pasiva `java.util.Locale`), que los decoradores de Controladores inyectan hábilmente para traducir diccionarios (`messages_es.properties`).

##### 9.

En la composición de formularios con reactividad pura (Paradigma "Controlled Component", como el `BuyForm`), se rechaza vincular los datos visuales al almacén central de Redux, optando por interceptar el tecleo (evento `onChange`) refrescando incondicionalmente un Hook `useState` local de componente. Dictamine el sustrato científico de esta decisión:

- [ ] a) Constituye un mecanismo de eficiencia suprema: depositar pulsaciones de teclado efímeras y volátiles en el macro-estado global de Redux forzaría repintados globales inútiles y asfixiaría parasíticamente a todos los selectores suscritos.
    
- [ ] b) Almacenar variables mutables a nivel de componente es un requisito imperativo que impone a la fuerza la directiva de anulación HTML `noValidate` para acoplar orgánicamente la API evaluadora interna `checkValidity()`.
    
- [ ] c) El uso indiscriminado de Redux en componentes puramente visuales está terminantemente vetado por el compilador, obligando por arquitectura a aislar toda invocación de `useDispatch` de manera exclusiva en la capa abstracta HTTP.
    
- [ ] d) Todas las anteriores sustentan el repudio documentado a la mezcla de variables sueltas incontroladas.
    

> [!success]- **Soluciones y Justificaciones (Evaluación Forense)**
> 
> **Opción correcta: a) Constituye un mecanismo de eficiencia suprema: depositar pulsaciones de teclado efímeras y volátiles en el macro-estado global de Redux forzaría repintados globales inútiles y asfixiaría parasíticamente a todos los selectores suscritos.**
> 
> **Justificación (Ref. Tema 7 - "Controlled Components" y Tema 6):** En nuestra disciplina no se acopla el teclado a Redux. Enviar una Acción a Redux (`dispatch`) por cada micro-evento al teclear obligaría incesantemente a React a procesar el Reductor Raíz completo y lanzar notificaciones evaluativas a la inmensa telaraña general de componentes suscritos, provocando un cuello de botella letal ("ahogo del Virtual DOM"). El Estado Local (`useState`) es vital para amortiguar este ruido limitando el coste computacional.

##### 10.

En el componente de abstracción transaccional frontend (`catalogService.js`), el programador redacta la llamada de red inyectando las variables tecleadas por el usuario hacia el `appFetch` de esta forma perimetral: `&keywords=${encodeURIComponent(keywords)}`. Desvele el fundamento por el que se exige el uso obligatorio de esta función envoltorio nativa de JavaScript:

- [ ] a) Para inyectar simétricamente la firma criptográfica asimétrica exigida por el token JWT, garantizando matemáticamente que los espacios en blanco no invaliden la cabecera HTTP estándar `Authorization: Bearer`.
    
- [ ] b) Resulta ser el eslabón fundamental exigido para desactivar el bloqueo estanco "Same-Origin Policy" (CORS), permitiendo que el servidor hostigado en el puerto 8080 acate pasivamente el tráfico proveniente del puerto cliente 5173.
    
- [ ] c) Sirve como herramienta crucial de saneamiento para blindar la sintaxis del motor HTTP frente a espacios o caracteres hostiles en el Query String, eludiendo así la corrupción semántica en la petición asíncrona hacia el Backend.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Soluciones y Justificaciones (Evaluación Forense)**
> 
> **Opción correcta: c) Sirve como herramienta crucial de saneamiento para blindar la sintaxis del motor HTTP frente a espacios o caracteres hostiles en el Query String, eludiendo así la corrupción semántica en la petición asíncrona hacia el Backend.**
> 
> **Justificación (Ref. Tema 7 - "La Abstracción Crítica appFetch"):** Omitir `encodeURIComponent` al mandar cadenas de texto extraídas de casillas de búsqueda ("Matrix Reloaded") provocaría que los espacios desnudos (" ") u otros caracteres prohibidos rompan literalmente la validación de formato sintáctico inherente del paquete de petición de red. No obedece en nada a vulnerabilidades directas de CORS (respuesta B), ni a des-serialización Jackson asimétrica (respuestas A y D).