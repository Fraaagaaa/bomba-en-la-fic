### 1. Paginación y Optimización en DAOs

Considere un repositorio Spring Data JPA encargado de gestionar la entidad `Order`. Se desea añadir un método para buscar los pedidos de un usuario optimizando el rendimiento de la base de datos ante colecciones masivas de registros. Valore las siguientes afirmaciones respecto a la elección del tipo de retorno:

- [x] a) El uso de `Slice<Order>` optimiza la consulta pidiendo simplemente un elemento extra en el LIMIT de SQL, evitando la ejecución de una consulta oculta de tipo SELECT COUNT(*).
- [ ] b) El uso de `Page<Order>` es arquitectónicamente superior porque carga previamente todos los datos en la Caché de primer nivel (L1) antes de dividirlos.
- [ ] c) Ambos enfoques (`Slice` y `Page`) requieren cargar todos los registros asociados en la memoria RAM del servidor y delegan la paginación a la capa de Servicios.
- [ ] d) Las interfaces DAOs profesionales jamás deben extender de `PagingAndSortingRepository`, debiendo implementar la paginación manualmente mediante JDBC.

> [!success]- **Solución y Justificación**
> **Opción correcta: a)** Es un error arquitectónico común confundir la interfaz `Slice<T>` con `Page<T>`. El uso de `Page<T>` obliga a Spring Data a lanzar una segunda consulta SQL tipo COUNT(*) que degrada masivamente el rendimiento en tablas con millones de registros. `Slice<T>` previene este cuello de botella y optimiza la consulta, descubriendo si hay más páginas disponibles al pedir un elemento extra, protegiendo la red y la memoria RAM.

---

### 2. Relaciones Bidireccionales y Lado Propietario

Sean `Category` y `Product` dos entidades, y `Category-Product` una relación bidireccional Uno-a-Muchos. Una categoría engloba varios productos y un producto pertenece a una sola categoría. La tabla relacional en la que se mapea `Product` dispone de la columna `categoryId`, que actúa como clave foránea (FK). Teniendo en cuenta la estrategia de acceso por propiedad, valore de forma individual cada anotación e indique la opción que utiliza la sintaxis correcta:

- [ ] a) `@ManyToOne(mappedBy="category")` sobre el método `public Category getCategory()` en `Product`.
- [ ] b) `@OneToMany(mappedBy="category")` sobre el método `public Set<Product> getProducts()` en `Category`.
- [ ] c) `@JoinColumn(name="categoryId")` sobre el método `public Set<Product> getProducts()` en `Category`.
- [ ] d) La a) y la c).

> [!success]- **Solución y Justificación**
> **Opción correcta: b)** En una relación bidireccional 1:N, el lado propietario es siempre el lado N (el hijo, `Product`), el cual alberga la clave foránea y usa `@ManyToOne` junto a `@JoinColumn`. El lado inverso es el lado 1 (el padre, `Category`), el cual delega el control usando `@OneToMany` junto con el atributo obligatorio `mappedBy="category"`. Además, la anotación `@ManyToOne` nunca soporta el atributo `mappedBy`, lo que invalida automáticamente la opción a).

---

### 3. Estrategias de Carga y Mecánica de Proxies

Considere las entidades `Order` y `OrderItem` vinculadas mediante una relación bidireccional 1:N parametrizada con carga perezosa (LAZY). Analice el siguiente fragmento ejecutado secuencialmente dentro de una transacción válida:

```
Order order = orderDao.findById(id).get();       // Línea [A]
Set<OrderItem> items = order.getOrderItems();    // Línea [B]
for (OrderItem item : items) {                   // Línea [C]
    Product product = item.getProduct();         // Línea [D]
    System.out.println(product.getId());         // Línea [E]
    System.out.println(product.getName());       // Línea [F]
}
```

Indique qué líneas provocan el disparo de una consulta de selección REAL (SELECT) hacia el motor de la base de datos:

- [ ] a) Las líneas A, B y D.
- [ ] b) Las líneas B, C y E.
- [x] c) Las líneas A, C y F.
- [ ] d) Todas las líneas causan una consulta física.

>[!success]- **Solución y Justificación** 
**Opción correcta: c)** La línea A recupera la entidad `Order` obligando a lanzar una sentencia SELECT inmediata. La línea B no causa SELECT porque la relación es LAZY e inyecta una colección de proxies vacíos al instante. La línea C fuerza la iteración, obligando a activar la colección perezosa y disparar un SELECT a la tabla `OrderItem`. La línea D inyecta el proxy del producto de forma inmediata sin consultar a la base de datos. La línea E es la gran trampa de examen: inspeccionar el ID de un proxy no dispara consulta porque el proxy ya conoce internamente su ID, ya que residía en la clave foránea de la línea anterior. Finalmente, la línea F sí causa SELECT al solicitar un dato ordinario no cacheado (el nombre), obligando a rellenar la entidad desde la base de datos.

---

### 4. Domain Model y Reglas Sintácticas de Persistencia

A la hora de aplicar el patrón Domain Model para encapsular la lógica intrínseca, se ha incorporado el siguiente método dentro de la entidad Java `Order`, asumiendo una estrategia de acceso por propiedad:

```
public BigDecimal getTotalPrice() {
    BigDecimal total = BigDecimal.ZERO;
    for (OrderItem item : this.orderItems) {
        total = total.add(item.getSubtotal());
    }
    return total;
}
```

Para garantizar un correcto arranque del servidor y evitar la colisión de persistencia, ¿qué acción es imperativa?

- [ ] a) Anotar la clase con `@DynamicUpdate` para permitir atributos calculados al vuelo.
- [ ] b) Modificar el constructor para que reciba la variable `total` por inyección de dependencias.
- [ ] c) Anotar el método forzosamente con `@Column(updatable=false, insertable=false)`.
- [ ] d) Decorar la firma del método explícitamente con la anotación `@Transient`.

> [!success]- **Solución y Justificación** 
> **Opción correcta: d)** Con la estrategia de acceso por propiedad, JPA inspecciona automáticamente cualquier método que inicie con `get` o `is` y asume que corresponde a una columna en la tabla física de la base de datos. Al tratarse de una operación exclusiva de Lógica de Negocio y no de un campo físico de la tabla SQL, se debe utilizar forzosamente `@Transient` para ordenarle a JPA que ignore dicho método durante su escaneo y evitar una excepción catastrófica en tiempo de arranque.

---

### 5. Semántica Transaccional Declarativa (@Transactional)

Considere un método `public Long buy()` alojado en la capa de Servicios y debidamente anotado con `@Transactional`. Durante el flujo de la operación para procesar un pedido, ocurre una infracción de negocio (el carrito de la compra pertenece a otro usuario) que se aborta lanzando `PermissionException` (la cual hereda de `Exception`). Indique la afirmación correcta sobre el estado final de la transacción:

- [ ] a) El contenedor de Spring intercepta la excepción, destruye la Caché L1 y finaliza ejecutando un ROLLBACK automático.
- [ ] b) La transacción terminará en ROLLBACK siempre que el método haya modificado atributos marcados como dirty state.
- [x] c) Dado que constituye una excepción controlada (Checked Exception), la transacción finalizará efectuando un COMMIT y materializará en la base de datos todas las operaciones previas exitosas.
- [ ] d) El contenedor de Spring ignorará la anotación a menos que el servicio haya implementado el patrón Optimistic Locking.

> [!success]- **Solución y Justificación**
> **Opción correcta: c)** En Spring, la regla arquitectónica que gobierna la finalización de las transacciones asume que las excepciones controladas (`CheckedException`, aquellas que heredan de `Exception`) obedecen a casuísticas de negocio predecibles, obligando a ejecutar un COMMIT y consolidar los cambios parciales. Únicamente las excepciones no controladas (`RuntimeException` o `Error`) desencadenan un procedimiento automático de ROLLBACK para deshacer el volcado y proteger la integridad del sistema.

---

### 6. Diseño y Propagación Transaccional

Considere un servicio de la capa Lógica de Negocio implementado con Spring, donde un método `A` se encuentra anotado con `@Transactional`. Este método ejecuta diversas comprobaciones y, seguidamente, invoca a un método `B` perteneciente a otra clase de servicio que también ostenta la anotación `@Transactional`. Valore la siguiente afirmación respecto al hilo de ejecución:

- [ ] a) Spring rechaza la sintaxis provocando un error de compilación debido al solapamiento de proxies y contextos.
- [ ] b) El método B ignora su propia configuración e invoca internamente operaciones sobre JDBC en estado "auto-commit".
- [x] c) El método B detecta la existencia de una transacción viva subyacente y, por defecto, se fusiona (engancha) a la transacción de A.
- [ ] d) El framework obliga al desarrollador a cerrar manualmente la sesión de JPA antes del trasvase entre servicios.

> [!success]- **Solución y Justificación**
> **Opción correcta: c)** Esta es la casuística correspondiente a la propagación transaccional por defecto (denominada `PROPAGATION_REQUIRED`) que implementa Spring. El Contenedor verifica la cadena de mandos y, si constata que ya se ha abierto e iniciado un contexto transaccional en el método de origen (A), anexa directamente las ejecuciones del método secundario (B) a dicha transacción matriz para asegurar la máxima integridad global.

---

### 7. Pruebas Automatizadas y Rollbacks de Contexto

Analice el enfoque para implementar pruebas de integración automatizadas para nuestra capa de modelo, asumiendo la inyección de los atributos `@SpringBootTest`, `@ActiveProfiles("test")` y `@Transactional` sobre la propia clase de Test. Valore las siguientes aseveraciones e indique la respuesta correcta:

- [ ] a) El perfil de pruebas dictamina que los parámetros de `application.yml` deben anularse sin fusionar los credenciales originales de la base de datos principal.
- [ ] b) El programador está obligado a clausurar el Test mediante un fragmento `userDao.delete(user)` para garantizar la sanidad del almacén de datos de cara a la prueba posterior.
- [x] c) Por el mero hecho de utilizar la librería spring-test, la anotación transaccional transfigura su semántica exigiendo siempre un ROLLBACK incondicional al término del método, sin importar el éxito interno del test.
- [ ] d) Ninguna de las anteriores.

> [!success]- **Solución y Justificación**
> **Opción correcta: c)** En el marco de producción (Lógica de Negocio), la anotación `@Transactional` finaliza su ejecución realizando Commit de forma predeterminada. Sin embargo, la biblioteca de test de Spring subvierte intencionadamente esta funcionalidad y muta su comportamiento: al término de cualquier método de ensayo (decorado con `@Test`), inyecta invariablemente un Rollback, restituyendo el almacén a un escenario inmaculado para abolir la necesidad de borrar manualmente (mediante llamadas `delete()`) los registros creados temporalmente.

---

### 8. Transferencia de Entidades y el Patrón DTO

En el contexto del modelado de una arquitectura moderna basada en Servicios REST mediante Spring Boot, existe una estricta directiva de no devolver nunca los objetos `@Entity` (pertenecientes a JPA) directamente hacia la red exterior, siendo mandatorio aplicar el Patrón Data Transfer Object (DTO). ¿Cuál es la motivación técnica imperativa subyacente a esta regla?

- [ ] a) Impedir fallos en el proceso de des-serialización de atributos de tipo nativo como Enum u Optional que Jackson es incapaz de traducir a JSON.
- [ ] b) Encubrir el esquema estructural interno de la Base de Datos, evitar catástrofes de serialización por bucles bidireccionales y prevenir las excepciones originadas por una Caché L1 inactiva al ejecutar Proxies LAZY desvinculados de la Lógica.
- [ ] c) Cumplir con la sintaxis HTTP que restringe el paso exclusivo de cadenas de texto puras (String) a través del protocolo, forzando la compilación a DTO.
- [ ] d) La b) y la c) son correctas.

> [!success]- **Solución y Justificación**
> **Opción correcta: b)** Retornar y exponer una entidad directa compromete severamente la robustez del sistema: externaliza sin filtro la representación relacional del servidor de datos, desencadena bucles recursivos infinitos al volcar en JSON los vínculos bidireccionales cruzados (`Order` <-> `OrderItem`), e induce un fallo crítico y abrupto al requerir valores de Proxies de inicialización retardada (LAZY) cuando la sesión conectiva del Controlador se ha cerrado completamente al salir de la Capa de Lógica de Negocio.

---

### 9. Controladores REST: Parámetros del Cuerpo (@RequestBody)

Considere un servicio REST encargado de procesar la matriculación (alta) de un nuevo usuario en la aplicación. Sabiendo que los credenciales no encajan semánticamente en las variables de la ruta (URL), el desarrollador estipula una petición POST. Analice el código y escoja la opción correcta respecto a sus decoradores sintácticos:

```
@PostMapping("/users/signUp")
public AuthenticatedUserDto signUp(@Validated UserDto params) {
    // ...
}
```

- [ ] a) La firma es incorrecta. Spring inyectará un objeto vacío porque se omite la anotación forzosa `@RequestBody` imprescindible para que el analizador serialice el JSON incrustado.
- [ ] b) La firma es correcta. La inyección se resuelve exitosamente gracias a la anotación de delegación global `@RestController` dispuesta en el archivo matriz del Controlador.
- [ ] c) La firma es incorrecta. Debería reemplazarse la llamada por la anotación de extracción superficial `@RequestParam` ya que se trata de variables nativas inyectadas por cadena de consulta (query string).
- [ ] d) La anotación `@Validated` asume por polimorfismo que el mapeo procede de un JSON y efectúa la inyección directamente a la entidad de seguridad.

> [!success]- **Solución y Justificación**
> **Opción correcta: a)** Constituye una clásica "trampa" o falso amigo del código. Si bien el modelo establece que el flujo de alta recae en una operación POST y viaja oculto en el cuerpo de la misma, carecer del decorador semántico explícito `@RequestBody` aledañamente al parámetro anula las directrices de Jackson y le inhibe para descubrir y traducir el contenedor de texto JSON al respectivo objeto Java instanciado (DTO), desembocando en una referencia hueca que estrellará el proceso.

---

### 10. Seguridad JWT y Arquitectura Stateless

Se estipula que nuestro Backend opera en un ecosistema API REST puro desprovisto de estado en memoria (Stateless), y emplea exclusivamente identificadores "JSON Web Token" (JWT) firmados algorítmicamente para orquestar la autorización en secciones privadas. Indique la aseveración precisa:

- [ ] a) El JWT viaja como parámetro inyectado en el path de enrutamiento (ej. `/shopping/orders/14?jwt=token`).
- [ ] b) El backend memoriza e incrusta el token permanentemente en las sesiones del servidor Tomcat por motivos de redundancia antes de rebotarlo.
- [ ] c) Se implanta un filtro interceptor que valida la firma subyacente y dictamina si se inyecta programáticamente el `userId` en el parámetro del Controlador REST valiéndose de `@RequestAttribute`.
- [ ] d) El cuerpo interior (payload) de los tokens es codificado con encriptación bidireccional AES, imposibilitando la extracción de las caducidades a menos que se posea la clave privada de Spring Security.

> [!success]- **Solución y Justificación**
> **Opción correcta: c)** Por especificación estandarizada, las tramas de los JWT se diseminan mediante atributos estandarizados en las Cabeceras HTTP `Authorization: Bearer <token>` (eludiendo las URLs). Sus valores se empaquetan en tramas abiertas (Base64url), transparentes pero blindadas bajo firmas contra las modificaciones de terceros. Al recibirlas, el filtro de Spring intercepta la trama, audita su validez criptográfica con el secreto HS256 predefinido y empuja la identidad certificada internamente delegándola a la capa final de servicios usando la directiva `@RequestAttribute`.

---

### 11. Gestión de Errores Global (Controller Advice)

Suponga que una petición externa ingresa en el servidor adjuntando una carga JSON en el cuerpo cuyos valores repudian el catálogo de validaciones primitivas prescrito mediante anotaciones paramétricas de la familia Bean Validation (e.g. `@Size`, `@NotNull`). Teniendo presente un enfoque global de intercepción (`@ControllerAdvice`), ¿cuál es la operativa correcta para recolectar esos errores formales en el lado del servidor y rebotarlos traducidos?

- [ ] a) El sistema devuelve irremediablemente el texto apilado estándar (stacktrace) de la virtual machine, forzando a React a parsear el cuerpo del fallo 500 para extraer la sintaxis en crudo de la alerta.
- [ ] b) El propio servicio de Capa Lógica (`@Service`) escanea la inconsistencia instanciando un objeto interceptor que frena la carga usando excepciones transaccionales.
- [ ] c) La arquitectura detiene el hilo en el umbral, genera automáticamente una exepción `MethodArgumentNotValidException` interceptable por el radar global, desde donde se llama programáticamente a `exception.getBindingResult().getFieldErrors()` para acopiar un informe limpio de los fallos.
- [ ] d) Ninguna de las anteriores.

> [!success]- **Solución y Justificación**
> **Opción correcta: c)** Ante el naufragio de las evaluaciones impuestas por `@Validated`, la ejecución aborta sin traspasar la frontera de la Capa de Lógica e interpone un Código 400 (Bad Request). Dicha señal emite la interrupción nativa `MethodArgumentNotValidException`, siendo recolectada en el componente transversal `@ControllerAdvice` que aglutina la semántica de error pormenorizada a través de la interfaz de la cadena de errores `getBindingResult()` para construir respuestas inteligibles y traducibles mediante repositorios de idiomas `i18n`.

---

### 12. Componentes de React y Manejo de Clases en JSX

Usted diseña un componente en el frontend usando las librerías oficiales de la arquitectura de la asignatura para renderizar la etiqueta HTML que conforma la caja gráfica de búsqueda del catálogo. Al programar la variable visual de estilos, introduce: `<div class="header-container"> <h1>Búsqueda</h1> </div>` Evaluando las normas estrictas impuestas por el transpilador subyacente de JSX, seleccione la premisa veraz:

- [ ] a) La formulación de las llaves en los atributos sintácticos es inyectada nativamente valiéndose del arroba (e.g. `@class="..."`).
- [ ] b) La sintaxis JSX se somete inalterada y sin traducción a los navegadores modernos, que aplican el motor nativo ECMAScript 2020 para emular el renderizado.
- [ ] c) El código carece de validez debido a que la terminología `class` usurpa una palabra clave protegida y reservada por el lenguaje de JavaScript puro, haciendo forzoso el uso explícito del constructo sustitutivo `className`.
- [ ] d) La a) y la c) son correctas.

> [!success]- **Solución y Justificación**
> **Opción correcta: c)** Es una trampa fundamental del Examen Oficial subyacente a JSX: al no representar HTML genuino, sino una envoltura estética superior de JavaScript estricto, JSX prohibe taxativamente la escritura original de etiquetas con los sustantivos reservados propios de su gramática funcional, como ocurre con la palabra `class` para instanciar programación orientada a objetos. Como sustitución impuesta, la arquitectura condena a utilizar obligatoriamente el formato en notación camello `className`.

---

### 13. Conservación del Estado y Ciclo del Hook useState

Analice con detenimiento el siguiente componente reactivo orientado a mostrar el listado del contenido del carrito de un cliente simulando transacciones activas de volcado continuo:

```
const Cart = () => {
    const [items, setItems] = useState([]);
    const handleAddItem = article => setItems([article, ...items]);
    // renderizado...
}
```

Una vez finalizada la carga visual o montaje (mounting initial) del componente en pantalla y habiéndose producido tres llamadas interactivas concurrentes al despachador secundario `handleAddItem`, asuma un repintado inminente motivado por la herramienta reactiva central.

- [ ] a) Al inicio de cada ciclo inminente de ejecución de renderización de la función iterada principal, la directiva `useState([])` impone un reinicio catastrófico, castigando el puntero matriz y vaciando el listado en RAM irremediablemente.
- [ ] b) En las renderizaciones sucesivas que desencadenan actualizaciones asíncronas originadas por `setX()`, la maquinaria de React neutraliza y descarta la firma y el vector `[]` pasados originariamente al método constructor `useState()`, recordando mágicamente los fondos custodiados vigentes al momento del evento.
- [ ] c) React bloquea terminantemente que la declaración originaria de inicialización en crudo transite reasignaciones clónicas y arroja una excepción alertando de mutabilidad prohibida en la caché.
- [ ] d) Ninguna de las anteriores.

> [!success]- **Solución y Justificación**
> **Opción correcta: b)** Se ilustra un concepto vital y recurrente en simulaciones oficiales de la asignatura: La declaración asignativa inyectada durante la inicialización (`[]` ó `0`) en la invocación del Hook `useState(initialValue)` es consumida de forma única y aislada durante el encendido y montaje pionero de renderizado. Las ulteriores llamadas funcionales originadas por mutaciones en los eventos desprecian de facto ese inicializador devolviendo consistentemente la variable global remanente cacheada.

---

### 14. React: Virtual DOM e Interacciones de Renderizado

Indique la afirmación correcta y exacta que expone la arquitectura matricial sobre el flujo de actualización gráfica y cálculo topológico estudiado para el framework de presentación React:

- [ ] a) Al desencadenarse operaciones o acciones en los controladores directos, los componentes redibujan sus porciones asociadas enviando actualizaciones atómicas directas sin filtrado sobre las etiquetas primitivas localizadas en el árbol del DOM real del navegador.
- [ ] b) React es un entorno reactivo pasivo que se actualiza estrictamente reescribiendo la propiedad genérica universal `innerHTML`, emulando un recambio profundo y monolítico totalizador de las capas frontales.
- [ ] c) Los componentes reevalúan su algoritmo lógico procesando las variaciones exclusivas sobre una copia paralela abstracta albergada en memoria conocida como Virtual DOM, desde el que calculan, purgan, extraen un subconjunto de diferencias topológicas operando luego parches focalizados ultra-selectivos en el modelo físico del explorador web.
- [ ] d) Las opciones a) y b) son correctas.

> [!success]- **Solución y Justificación**
> **Opción correcta: c)** Uno de los pilares arquitectónicos que justifica la inmensa rapidez de la librería de React radica en la interposición transversal de un amortiguador ramificado subyacente estructurado en RAM de alta velocidad: El DOM Virtual. Cuando un componente emite alertas internas de inmutabilidad alterada (e.g. invoca sus Hook de reemplazo), React despliega un mapeo topológico (Algoritmo de Diffing), disecciona la discrepancia del Virtual DOM actual e inyecta la mínima fracción resolutiva imperativamente requerida en el explorador.

---

### 15. Redux: Reglas Obligatorias para un Reductor

Bajo los cánones técnicos más dogmáticos que sustentan a la cadena reactiva para el control de la información unificada central (Redux), un desarrollador decide implementar su `rootReducer`. Valore rigurosamente y exponga cuál de los comportamientos operativos se halla terminantemente vetado en la concepción arquitectural de un reductor:

- [ ] a) Inicializar las matrices o diccionarios base predeterminados empleando parámetros obligatorios por defecto en la firma si el argumento de entrada es nulo (e.g., `state = initialState`).
- [ ] b) Disparar interceptores asíncronos nativos para interactuar lateralmente con llamadas a la red usando operaciones tipo REST, interceptando y consolidando promesas de red.
- [ ] c) Desestimar interacciones o tramas si su identificador posicional `action.type` no halla compatibilidad devolviendo impertérrito y sin tocar los punteros nativos de `state` el estado inmaculado inyectado (cláusula `default`).
- [ ] d) Emplear directivas de clonado superficial, invocando a los operadores diseminadores (Spread `...`) como forma habitual de componer instancias análogas pero desvinculadas por inmutabilidad.

> [!success]- **Solución y Justificación**
> **Opción correcta: b)** Dentro de la estricta axiomatización computacional estipulada para Redux, el corazón funcional que implementa los algoritmos de síntesis central, esto es, un Reductor, se califica como una "Función Pura". Esta clasificación matemática estipula la imposibilidad para ejecutar colateralidades que desvirtúen los predecibles cálculos deterministas referenciales de las ejecuciones. Toda contaminación como promesas temporales asíncronas vinculadas a interacciones web (Side-Effects o llamadas API) debe consumarse y expurgarse de raíz antes de la canalización atómica final en el emisor de tareas `dispatch()`.

---

### 16. Redux: Inmutabilidad, Rendimiento y Estado Normalizado

El equipo de integración se halla reestructurando la memoria estática general manejada por Redux en PA-Shop. Un listado relacional de registros se proyecta transformando Arrays masivos del tipo elemental plano O(n) iterativo a conjuntos anidados catalogados del formato diccionario, mediante objetos segmentados e instanciados por Clave (`byId`) acompañados por un trazado lineal ordinal (`allIds`). El dictamen de diseño que obliga e induce el despliegue de esta modificación técnica tiene como motivación esencial:

- [ ] a) Sustituir el bucle lineal ineficiente requerido durante la modificación por la inyección posicional instantánea en RAM (complejidad algorítmica constante O(1)), preservando con destreza el orden semántico representacional nativo que espera react y la inmutabilidad intrínseca global de los identificadores.
- [ ] b) Evadir el rechazo subyacente a la manipulación nativa de funciones elementales del entorno de NodeJS que vetan la instanciación estructural de datos en bloque en sistemas con `combineReducers`.
- [ ] c) Mitigar el riesgo inmanente de que la función pura despachadora colisione, debido a la sobrecarga generada en la persistencia estanca almacenada de HTML5 localmente y protegida contra transiciones cruzadas.
- [ ] d) La a) y la c).

> [!success]- **Solución y Justificación**
> **Opción correcta: a)** En el marco arquitectónico exigido y estipulado en PA-Shop sobre configuraciones masivas y aplicaciones avanzadas, guardar las colecciones de estado dependientes en simples ordenaciones indexadas en Arrays degrada la iteración transaccional durante reescrituras obligando a usar barridos y clonaciones cíclicas extremas. Estructurar un diseño de bases relacionales de Estado Normalizado rompe y mitiga tal límite al encapsular el conjunto en diccionarios asociativos y de búsqueda logarítmicamente predecible e indexación fija de coste marginal O(1).

---

### 17. Uso de Formulario (Controlled Components) y Redux

Evalúe la siguiente operativa de diseño implementada en PA-Shop sobre una pestaña genérica de adquisición. El operador redacta y vuelca, presionado al tiempo un `onChange`, cadenas sobre un formulario (`BuyForm`) cuyas directrices internas estipulan interceptar la variable textual captada albergándola y refrescándola constantemente mediante un marco restrictivo `useState()`, de espaldas y oculto ante el gestor de memoria masiva de Redux. Indique la premisa acertada:

- [ ] a) Conlleva un antipatrón en escalabilidad: Todas las variables transitivas y reescrituras parciales del frontend deben imperiosamente residir en el núcleo de Redux para que la caché unificada las purgue.
- [ ] b) Al no disponer un atributo imperativo vinculante de acceso manual (estilo "Pull" invocando y amarrando `ref={node}`), el flujo se catalogará de forma irrevocable como descontrolado (Uncontrolled).
- [ ] c) Pertenece al canon universal estandarizado para campos definidos como Controlados (Controlled Components), permitiendo un encapsulamiento aislado e interceptaciones locales sintácticas puras sin infectar o sobrecargar los flujos iterativos de Redux.
- [ ] d) Provocará advertencias incesantes por colisiones con Vite, dado que React interceptará el teclado congelando al navegador ante falsas percepciones de re-renderizado totalizador.

> [!success]- **Solución y Justificación**
> **Opción correcta: c)** En el paradigma de Controlados ("Push"), la variable visual está vinculada al valor dictado nativamente desde el estado individual de su clase madre o del entorno local (vía `useState`), confiriéndole independencia y reacción automática ante cambios programáticos interceptados, sin corromper con micro-transacciones el registro de almacenamiento persistente macro de Redux ni la topología ajena.

---

### 18. Abstracción Transaccional del Gateway (appFetch)

Dentro de la capa interior del Frontend, encargada del trasiego hacia las rutas o controladores HTTP expuestos, la codificación recurre sistemáticamente al uso de un módulo envoltorio de comunicación parametrizado por una función particularizada bajo el identificador `appFetch`. Señale la premisa correcta:

- [ ] a) Constituye la herramienta estándar sustitutiva de Vite destinada a compilar en JS nativo transpilando los parámetros del lado servidor generados para JPA.
- [ ] b) Evita un acoplamiento tóxico suprimiendo del entorno el token firmado digitalmente.
- [ ] c) Su concepción arquitectónica recae en encapsular comodidades críticas para interactuar de red centralizada, como concatenar inteligentemente prefijos variables, anexar automáticamente certificados y cabeceras JWT en canales privados y empaquetar con limpieza la señal resultante.
- [ ] d) React prescindirá de `appFetch` a la hora de gestionar las rutas variables extraíbles con `useParams`, pero la llamará explícitamente para desactivar los selectores globales.

> [!success]- **Solución y Justificación**
> **Opción correcta: c)** Invocaciones masivas directas de librerías crudas JavaScript asíncronas del estilo `fetch()` empañarían la limpieza del código sembrando vulnerabilidades transversales. Configurar y delegar a `appFetch` representa un escudo que unifica la interceptación, formatea los objetos a JSON con precisión, unifica la absorción pasiva desde `sessionStorage` inyectando automáticamente la cabecera predeterminada obligatoria `Authorization: Bearer <token>` cuando corresponde y facilita el retorno lógico del control de validación `payload`.

---

### 19. El Ciclo Limpiador de Promesas y Hooks de Ciclo de Vida

El programador inspecciona minuciosamente la función asincrónica inyectada dentro del decorador referencial global `useEffect` de React asimilado en `ProductDetails`:

```
useEffect(() => {
    dispatch(actions.fetchProductDetails(id));
    return () => dispatch(actions.clearProductDetails());
}, [id]);
```

Indique qué dinámica y control del rastro en memoria experimentará este fragmento enmarcado en dependencias acotadas en matrices cerradas (e.g. `[id]`):

- [ ] a) Tras la fase exclusiva de purga inactiva, `useEffect` colapsa iterando cíclicamente, ejecutándose irremisiblemente detrás de cualquier transición reactiva paralela y no condicionada.
- [ ] b) La función interna final dictada por `return` no ejerce capacidad vinculante y se restringe a enviar trazas irrelevantes que el Garbage Collector nativo de ECMAScript elimina.
- [ ] c) Se trata del bloque resolutivo y paliativo (Clean-up), que en caso de existir transmutaciones sobre la dependencia (el ID extraído) se invocará forzosamente por orden restrictivo al inicio antes de montar un componente clónico u abandonarlo, mitigando la retención parasitaria (fugas de memoria) y blanqueando variables de Redux obsoletas.
- [ ] d) Ninguna de las anteriores.

> [!success]- **Solución y Justificación**
> **Opción correcta: c)** En el marco de actuación natural para componentes dinámicos de visualización singular o con peticiones remotas transitorias, los Hooks de anclaje iterativos exigen delegar acciones y limpieza por sobrecarga o rastros fantasmas; la directiva que la propia función inicial retorna transfiere a React una promesa y barrera funcional de clausura estricta para vaciar o purgar estados inservibles antes de montar variaciones relativas e inmediatamente al destruir la visualización.

---

### 20. Expansión Tecnológica y Microservicios Clímax

Teniendo en cuenta el diseño resolutivo y la mutación estratégica de los núcleos cerrados de desarrollo monolítico que ostenta la plataforma PA-Shop, se opta por disgregar todo este complejo macro en múltiples servidores o arquitecturas de microservicios segregadas que orquesten independientemente la persistencia alojada bajo Docker en Clouds distribuidos. Indique la premisa que defina el paradigma técnico veraz:

- [ ] a) Para la interconectividad entre las diferentes piezas aisladas desplegadas resulta imperativo eliminar APIs de tipo REST y transmutar la Capa de Controladores delegando las intercomunicaciones asincrónicas a los DAOs locales, compartiendo el acceso masivo a la misma Base de Datos relacional nativa central.
- [ ] b) Cada fracción o microservicio segregado del espectro (e.g., Catálogo o Compras) resulta ostentar dominio y titularidad absoluta sobre su base de datos privativa excluyente, extirpando caídas cascada en dominios relacionales pero trasladando un desafío a transacciones complejas para mantener consistencia subyacente asincrónica y resguardando un API Gateway que aísle al exterior de la topología distribuida.
- [ ] c) Spring prohíbe el uso de componentes de tipo Fat JAR preestablecidos obligando a delegar empaquetados pesados en formato WAR de carga que no logran inicializar un motor intermedio web o proxy si viajan segregados en los perfiles de despliegue virtuales y encapsulamientos modulares.
- [ ] d) Todas las afirmaciones son verdaderas y aplicables.

> [!success]- **Solución y Justificación**
> **Opción correcta: b)** Es la Regla de Oro Ineludible en el paradigma puro escalable arquitectónico: un ecosistema funcional de microservicios segmenta la centralidad, aislando bases autónomas de repositorios particulares (`BD Catalog`, `BD User`, etc.) bajo su responsabilidad estricta. Todo esto prevé cuellos de botellas, asegura una contención estanca al escalar procesos disímiles a través de contenedores virtuales dinámicos y centraliza peticiones del Frontend a través del nodo canalizador o fachada global `API Gateway`.

### 21. Requisitos Formales de Entidades JPA

Para que el motor de persistencia de Hibernate acepte y gestione satisfactoriamente una clase Java como una entidad válida bajo el paradigma ORM, se deben cumplir reglas estrictas preestablecidas por la especificación. Valore las siguientes opciones e indique cuál de estas configuraciones en una clase Java **violaría** los principios arquitectónicos impidiendo su despliegue:

- [ ] a) Estar decorada obligatoriamente a nivel de clase con la anotación `@Entity`.
- [ ] b) Contar imperativamente con un constructor vacío (sin argumentos), que ostente visibilidad `public` o `protected`.
- [ ] c) Declarar la clase explícitamente mediante la sintaxis `public final class Product`.
- [ ] d) Poseer obligatoriamente un atributo de identidad marcado explícitamente con la anotación `@Id`.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Según las reglas formales de la asignatura, la clase "no puede ser final (public final class), ya que JPA necesita heredar de ella para poder crear en tiempo de ejecución los objetos intermediarios conocidos como Proxies". Instanciarla como final bloquea la herencia y paraliza el sistema LAZY y la activación de Hibernate.

---

### 22. Naturaleza Estructural de JPQL vs SQL

Al emplear la anotación `@Query` para definir sentencias declarativas de búsqueda complejas en un repositorio Spring Data JPA, se exige la utilización estricta del lenguaje JPQL. ¿Cuál es el principio dogmático subyacente que diferencia a JPQL del SQL nativo convencional a la hora de redactar estas sentencias?

- [ ] a) JPQL ignora la inyección de parámetros nombrados, exigiendo concatenar variables Java directamente mediante el operador `+` para evitar la sobrecarga de tipos.
- [ ] b) JPQL interroga exclusivamente a las Clases Entidades de Java y a sus propiedades internas de objeto, ignorando por completo el nombre físico y real que ostentan las tablas y columnas en el motor relacional.
- [ ] c) JPQL es interpretado por el navegador en el lado del cliente y requiere obligatoriamente el retorno estructurado en un DTO.
- [ ] d) JPQL obliga a clausurar todas sus consultas con la sintaxis `LIMIT`, ya que carece de interoperabilidad con interfaces tipo `Pageable` o `Slice`.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** Constituye un principio fundamental y trampa clásica de examen. JPQL opera en un ecosistema puramente orientado a objetos. Si se redacta `FROM users_table`, el framework colapsará. Se debe referenciar a la clase (`FROM User u`) y Hibernate se encarga internamente de transcribirlo vía JDBC a los sustantivos físicos reales de las tablas.

---

### 23. Estado Dirty e Invocación de Persistencia

Analice detalladamente el siguiente método perteneciente a un servicio alojado en la Capa Lógica y decorado globalmente con la directiva `@Transactional`:

```
public User updateProfile(Long id, String name) {
    User user = userDao.findById(id).get();
    user.setFirstName(name);
    return user;
}
```

Indique la premisa correcta y técnica acerca del volcado de datos:

- [ ] a) El código omite un paso imperativo: al carecer de una instrucción de cierre `userDao.save(user)`, los valores de `name` colapsarán al clausurar el contexto en memoria.
- [ ] b) El código es arquitectónicamente perfecto. Al mutar el objeto en RAM, la entidad transita al estado _dirty_, y JPA lanzará automáticamente una sentencia UPDATE oculta al finalizar exitosamente la transacción.
- [ ] c) El método inducirá a un fallo crítico porque `@Transactional` impone internamente que todas las colecciones mutadas se definan como inmutables y de solo lectura.
- [ ] d) El contenedor Spring interceptará la alteración y generará de inmediato una `RuntimeException` alertando de violaciones en el patrón Optimistic Locking.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** Se ilustra el concepto maestro conocido como "Dirty State". Cuando se extrae una Entidad de la Base de Datos bajo un paraguas `@Transactional`, ésta se aloja en la Caché de primer nivel. Cualquier invocación posterior a sus métodos `setX()` muta la entidad. Al alcanzar la llave de cierre del método, Hibernate escanea la caché, detecta el "estado sucio" y despacha el `UPDATE` a MySQL, haciendo totalmente redundante y prescindible el uso manual del comando `save()`.

---

### 24. Optimistic Locking y Concurrencia Extrema

Para mitigar drásticamente la anomalía transaccional de "Second Lost Update" (Segunda Actualización Perdida) en ecosistemas web masivos, descartamos los cerrojos estáticos físicos de base de datos (Pessimistic Locking) a favor de un enfoque de **Optimistic Locking**. Valore cómo se materializa y controla formalmente esta estrategia técnica en JPA:

- [ ] a) Insertando la cláusula `isolation = Isolation.SERIALIZABLE` en todos los métodos de lectura, lo que forza a un bloqueo exclusivo de la fila de hardware.
- [ ] b) Empaquetando la actualización en un bucle `while(true)` que itera intentando volcar los DTOs hasta que el controlador web cierra el canal.
- [ ] c) Anotando un atributo numérico de la entidad con `@Version`. Si una transacción clónica muta la versión anticipadamente, el UPDATE de la segunda fracasa informando de '0 filas afectadas' e induciendo un Rollback automático.
- [ ] d) Desactivando la Caché de Primer Nivel para garantizar que la memoria RAM se re-alimente continuamente durante la concurrencia a través de Proxies forzados.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** El cerrojo optimista se inyecta declarando un contador interno (`@Version`) en la entidad. Al escribir en disco, Hibernate emite `UPDATE ... WHERE id=? AND version=?`. Si la Transacción B llega tarde, la versión original de la fila ya fue incrementada por la Transacción A. El motor no hallará correspondencia (0 filas afectadas) y el sistema entrará en pánico controlado emitiendo una `OptimisticLockingFailureException` y deshaciendo la colisión.

---

### 25. Perfiles de Configuración YAML en Testing

Durante el despliegue del entorno automatizado de integración de Spring Boot, el equipo inyecta la cabecera sintáctica `@ActiveProfiles("test")`. Asumiendo que conviven físicamente en el arquetipo de carpetas del proyecto los archivos configuradores `application.yml` (matriz) y `application-test.yml` (derivado), ¿cuál es el protocolo exacto del contenedor al iniciar los volcados de parámetros?

- [ ] a) Spring Boot asimila inicialmente el archivo matriz `application.yml` y, acto seguido, lo fusiona solapando `application-test.yml`, sobreescribiendo única y quirúrgicamente las propiedades que entran en colisión, conservando las demás.
- [ ] b) Spring aborta el análisis del archivo base original y carga en exclusiva y bajo formato monolítico los parámetros del archivo derivado, exigiendo reescribir manualmente cada credencial.
- [ ] c) Al pertenecer a la familia de `spring-test`, los archivos YAML se deniegan por seguridad, forzando la inyección de conexiones URL mediante parámetros en código puramente Java.
- [ ] d) El marco ignora `@ActiveProfiles` si la base de datos embebida carece del esquema físico previo, provocando un error de sintaxis en blanco.

> [!success]- **Solución y Justificación** 
> **Opción correcta: a)** Una confusión recurrente y trampa de examen consiste en asumir que activar el perfil "test" anula el fichero matriz general. La realidad funcional del framework radica en el patrón de "Fusionado". El `application.yml` actúa de cimientos; el `application-test.yml` aterriza por encima, aplastando únicamente los nodos solapados (como la cadena URL reorientada hacia la base aislada `patest`), protegiendo el resto de metadatos ambientales.

---

### 26. Empaquetado, Contenedores Web y Fat JAR

Sabiendo que Spring Boot ostenta y centraliza la orquestación global del servidor, analice el impacto arquitectónico que detenta la orden de empaquetamiento comercial `mvn package`, si partimos de la configuración oficial y estándar del esqueleto del proyecto:

- [ ] a) Compila las rutinas a lenguaje ensamblador, creando un bloque de sistema dependiente pero veloz.
- [ ] b) Fabrica exclusivamente un archivo tipo `.war` mutilado, inoperante por sí mismo a menos que el equipo devOps lo encruste en un Servidor Tomcat estanco clásico ya instalado y configurado manualmente.
- [ ] c) Materializa un artefacto unitario y monolítico denominado "Fat JAR", el cual subsume no solo las lógicas del programa y dependencias, sino que incrusta su propio servidor web Tomcat en su vientre, facilitando ejecuciones puras (`java -jar`).
- [ ] d) Inyecta el empaquetamiento directamente en el núcleo del navegador cliente forzándolo a utilizar el motor interno para resolver el volcado transaccional a SQLite.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Uno de los triunfos disruptivos de la plataforma Spring Boot radica en extirpar el tedioso proceso tradicional de administrar servidores (modelo WAR) delegándolo al formato "Fat JAR" (archivo jar 'gordo'). Este paquete es auto-suficiente: contiene la compilación compilada de nuestro software más un Tomcat interno alzado automáticamente al teclear la sentencia matriz en cualquier máquina host.

---

### 27. Servicios REST y Extracción Paramétrica

El operador Frontend tramita una solicitud HTTP en búsqueda de productos paginados orientándose hacia la ruta exterior: `GET /catalog/products?keywords=matrix&page=0`. En el núcleo del Controlador correspondiente, ¿qué decorador sintáctico resulta imperativo y dogmático para atrapar inyectar esos parámetros volátiles directamente hacia los argumentos elementales del método de la clase Java?

- [ ] a) `@PathVariable`
- [ ] b) `@RequestBody`
- [ ] c) `@RequestParam`
- [ ] d) `@RequestAttribute`

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** En semántica REST, los atributos concatenados tras el símbolo de interrogación (`?`) se tipifican como "Query String" o cadena de consulta. La anotación especializada provista por Spring Web para atrapar y decodificar estas asociaciones pares "clave-valor" es estrictamente `@RequestParam`. Si los valores hubiesen viajado incrustados en la propia arquitectura semántica de la barra (`/orders/14`), se exigiría usar `@PathVariable`.

---

### 28. Internacionalización (i18n) y Cabeceras Nativas HTTP

En la frontera perimetral del Controlador de Excepciones global, ¿bajo qué directriz mecánica dictamina el Backend dinámicamente el idioma particular con el que debe estructurar, traducir y enviar a la red exterior el texto legible de un error semántico (e.g. "El carrito está vacío" frente a "Shopping cart is empty")?

- [ ] a) El usuario parametriza forzosamente su idioma inyectando un token en la base de datos persistente al cual Spring Security acude en caso de desastre.
- [ ] b) El explorador del cliente inyecta nativamente la cabecera `Accept-Language` en la petición entrante, a partir de la cual el framework instancia e inyecta un objeto transparente `Locale` hacia nuestros métodos interceptores para interrogar al repositorio `MessageSource`.
- [ ] c) React traduce asincrónicamente el paquete nativo en crudo de la excepción instanciando un motor de renderizado sobre el archivo `application.yml`.
- [ ] d) Spring Web delega el mapeo idiomático basándose en el parámetro posicional incrustado en el cuerpo JSON originado en la capa de persistencia LAZY.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** La norma suprema de la internacionalización web moderna (i18n) transfiere la responsabilidad de las preferencias lingüísticas hacia las cabeceras predefinidas del protocolo (`Accept-Language`). Spring Web lee este vector pasivo, consolida su valor geográfico empaquetándolo en una instancia nativa `java.util.Locale`, y permite que nuestros componentes la inyecten de forma mágica en sus firmas para recuperar del `MessageSource` la cadena de texto coincidente con su sufijo local (e.g., `messages_es.properties`).

---

### 29. Transpilación Estática y el Comando de Producción de Vite

Habiendo alcanzado el clímax del desarrollo del Frontend con la herramienta Vite en React, el programador abate el servidor en caliente de desarrollo y despacha la instrucción oficial `npm run build`. ¿Cuál es el dictamen arquitectural sobre las mutaciones topológicas sufridas en los ficheros amparados en la nueva carpeta física matriz `dist`?

- [ ] a) Todos los ecosistemas híbridos JSX sufren una transpilación descendente a JavaScript puro; a su vez, la totalidad algorítmica y los CSS se minimizan agresivamente expurgando comentarios, dando luz a archivos inermes y estáticos ideales para empotrar sobre ecosistemas de red tradicionales.
- [ ] b) Se genera un servidor Tomcat embebido clónico al de Spring Boot, uniendo la lógica de los DAOs con el React Virtual DOM para saltar los cuellos de CORS.
- [ ] c) La sintaxis JSX se traslada en estado latente de preservación, induciendo a que cada explorador de escritorio active un micro-compilador Babel al inicio para interpretar las llaves inyectadas de React Native en tiempo real.
- [ ] d) Vite rehúsa comprimir los componentes que estén suscritos al entorno global de Redux por miedo a fragmentar el estado, aislando sólo los estáticos.

> [!success]- **Solución y Justificación** 
> **Opción correcta: a)** Vite es un aglutinador y transpilador. En su fase de compilación productiva (Build), neutraliza todo el azúcar sintáctico exclusivo de React (los ficheros `.jsx` que los navegadores ignoran) traduciéndolo de forma monolítica al idioma binario original que entiende la máquina web (ECMAScript "normal"). Adicionalmente, minimiza, concatena y tritura todo resquicio de espacios o comentarios, volcando una huella nítida, de altísima velocidad, servible por un modesto Nginx o Apache estático.

---

### 30. Mecánica Resolutiva del Algoritmo de Igualdad en el Virtual DOM

Para sostener un rendimiento de reacción ultrarrápido sin ahogar la CPU, las librerías matrices que orbitan sobre el Estado global de React (Selectores de Redux o Evaluadores de Hook) evitan renderizaciones paralizantes y redundantes. ¿Qué herramienta de análisis algorítmico utilizan internamente para sentenciar si una variable matricial ha transmutado y requiere parcheo gráfico?

- [ ] a) Una incursión profunda evaluando el estado de persistencia anidado, recorriendo con un bucle recursivo masivo cada celda interna del array comparando texto por texto.
- [ ] b) Evaluaciones semánticas basadas en la instanciación de un JSON estanco y un parseo reverso, comparando su longitud de caracteres absolutos.
- [ ] c) Un test de igualdad referencial incondicional y superficial (Shallow comparison) basado en las reglas lógicas matemáticas estrictas del triple igual (`===`), analizando solo las mutaciones del puntero en la caché RAM.
- [ ] d) El algoritmo ignora la evaluación condicional y siempre aplica los reemplazos mediante inyección indiscriminada vía propiedades de InnerHTML sobrecargando las ramas.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** El corazón del inmenso poder resolutivo subyacente al entorno reactivo dicta que la librería renuncia a destripar iterativamente y buscar cambios anidados en matrices mastodónticas ("Deep compare", que implicaría tiempo polinómico o peor). Por el contrario, se contenta con verificar trivialmente si la referencia original del objeto (el puntero a bloque RAM) es distinto. Esta justificación matemática hace imperativa y dogmática la norma de aplicar la "Inmutabilidad Absoluta": fabricar siempre clones completos desde el exterior para desvincular el referencial.

---

### 31. Trazabilidad de Listas y la Directiva JSX Obligatoria

Un componente requiere iterar funcionalmente mediante el paradigma declarativo `.map()` una matriz albergada de Objetos `Todo` para renderizar secuencialmente una cadena infinita de nodos repetitivos. Considerando los rigores topológicos y de advertencias expuestos por el motor del Virtual DOM, resulta imperativo:

- [ ] a) Clausurar el cierre de la expresión usando el atributo local de instancia `ref` asociándolo a un disparador interno nativo para amarrar la matriz persistente a SQL.
- [ ] b) Evitar las inyecciones funcionales de flecha asíncronas y canalizar todas las instancias iterables empaquetando cada hijo en un contexto aislado `@Context`.
- [ ] c) Adherir taxativamente y de forma unívoca a la etiqueta raíz de cada ítem dinámico la propiedad especial y reservada `key`, parametrizada preferiblemente con el ID sustantivo matriz de base de datos que garantice la trazabilidad de renderizado.
- [ ] d) Inicializar los componentes empleando invariablemente la palabra clave matricial `class` como herencia, para dotar al componente de un ciclo de vida atómico.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Constituye una pregunta vital: "La directiva mágica key". Cuando React inyecta de forma masiva fragmentos replicados derivados de una matriz, su algoritmo topológico ("Diffing") entra en riesgo de estrangulamiento computacional si se eliminan nodos intermedios. Añadir una marca visual individual mediante la inyección del parámetro especial `key={item.id}` sobre la envoltura dota al mapeador de radares inequívocos, restaurando el rendimiento, previniendo advertencias paralizantes en consola y logrando identificar mutaciones localizadas asombrosamente rápido.

---

### 32. Enrutamiento en Arquitecturas SPA y el Bloqueo de Etiquetas

La ingeniería de las aplicaciones SPA (Single Page Application) impone rigores severos sobre el diseño del esquema de navegación inter-componentes. Indique por qué está vetado funcionalmente programar saltos internos mediante el constructo elemental primitivo HTML `<a href="/catalog">`:

- [ ] a) Porque invocar al ancla original precipitará irrevocablemente una recarga física desde cero al servidor Web aniquilando en el acto todo rastro del Estado RAM vigente, obligando en su lugar a usar el componente envoltorio `<Link>` propio de React Router para simular trayectos por el Virtual DOM.
- [ ] b) Porque los sistemas modernos carecen de soporte nativo interpretativo para cadenas href, desencadenando que Vite repudie la compilación.
- [ ] c) Las etiquetas de ancla no soportan propiedades en notación camello, lo que corrompe la sintaxis estricta del JSX paralizando el volcado de Bootstrap.
- [ ] d) Al no permitir encapsular tokens en sus rutas transitorias, los componentes SPA rechazan la cabecera `Accept-Language` degradando el i18n al idioma base preestablecido.

> [!success]- **Solución y Justificación** 
> **Opción correcta: a)** Una SPA genuina aspira a una interacción ininterrumpida y libre de pantalla blanca. Ejecutar la llamada de un anclaje tradicional del estándar HTML subyacente dispara la señal global de refresco impuesta a nivel explorador, estrellando todas las variables matriciales puras y destrozando el `Store` de Redux guardado en caché. La biblioteca React Router mitiga esto dotándonos del componente subversivo `<Link>`, quien apresa el evento de Click y altera la URL cosméticamente engañando a la vista del Virtual DOM.

---

### 33. Validación Programática en Formularios HTML5

Evaluando la dinámica interior del caso de uso transaccional "Comprar" (Componente `BuyForm`), se requiere apagar y deponer la intervención brusca y la renderización estética impositiva por defecto de los globos nativos que los exploradores dibujan sobre errores sintácticos de entrada. ¿Bajo qué estrategia técnica y estructural logramos subyugar este comportamiento a nuestro control absoluto en React?

- [ ] a) Se impone usar exclusivamente componentes "no-controlados", suprimiendo el rastreador `onChange` de los campos e invocando asincrónicamente selectores crudos.
- [ ] b) Configurar un Hook paralizante de retención asincrónica `useEffect` apuntando sus dependencias referenciales únicamente a `backendErrors`.
- [ ] c) Inyectar orgánicamente el atributo semántico `noValidate` en la raíz del objeto matriz `<Form>` para amordazar el motor ajeno, y ejecutar programática y manualmente la señal nativa resolutiva `form.checkValidity()` tras abatir el comportamiento clásico interceptando `onSubmit`.
- [ ] d) Migrar de la librería oficial hacia React Native para extirpar las validaciones CSS del DOM.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** En el canon del curso de arquitecturas escalables, para adueñarse estética y programáticamente de las alertas interponiendo el estilo corporativo de React Bootstrap, es preceptivo anular el radar intrínseco del HTML inyectando `noValidate={true}` en el formulario, para inmediatamente capturar la promesa reactiva y domar el suceso mediante la pulsación delegando evaluaciones sintácticas bajo el paraguas de `checkValidity()`.

---

### 34. Resiliencia de la Autenticación ante Recargas Hostiles (F5)

Un cliente correctamente registrado transita por las profundidades del listado del catálogo en el Frontend. En ese instante, pulsa involuntariamente la tecla "F5" desencadenando un recambio masivo y abrupto del entorno ECMAScript activo. Frente a esta purga totalizadora en la Caché, ¿cómo reconstruye de manera ininterrumpida e invisible el componente matriz `App` el rastro funcional de JWT para no degradar la experiencia de usuario?

- [ ] a) React Router inyecta preventivamente copias fragmentadas del Estado de forma periódica en un servidor de caché Redis anidado.
- [ ] b) React detiene e invierte la acción de la tecla solicitando permisos a través de un diálogo pasivo que aborta la instrucción nativa preestablecida de Windows.
- [ ] c) Dado que el componente amparó previamente el certificado JWT en un depósito ajeno resiliente del explorador (denominado `sessionStorage`), el sistema lee, rescata la cadena y reinyecta un Login Silencioso forzando al Endpoint subyacente `/users/loginFromServiceToken` a devolver la radiografía integra de las colecciones de usuario.
- [ ] d) Ninguna de las anteriores. Las recargas implican la pérdida inexorable y total del carrito y de la identidad ineludiblemente bajo entornos React asíncronos.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Constituye una pregunta de evaluación arquitectónica crítica. Las recargas F5 destruyen todo el estado RAM de Javascript, pero respetan y conmutan al depósito nativo del navegador denominado `sessionStorage`. El Frontend extrae hábilmente el JWT alojado en este almacén paralelo, y aprovechando su subsistencia lanza de forma invisible una petición remota con las cabeceras blindadas, despertando a los reductores del letargo transaccional al nutrirse velozmente con los saldos devueltos por Spring Boot.

---

### 35. Entornos Cruzados y la Directriz Originaria (CORS)

En modo desarrollo, el motor Vite orquesta sus respuestas desde la URL canónica portuaria HTTP (puerto 5173). Simultáneamente, el robusto contenedor Java expone el canal transaccional (puerto 8080). El explorador cliente web aborta incesantemente los intercambios emitidos por la abstracción `appFetch`. Señale con absoluta precisión técnica el veredicto arquitectónico:

- [ ] a) Vite enmascara internamente el formato de cabecera JWT obligando a los módulos Jackson a decodificar usando llaves públicas no emparejables.
- [ ] b) Los exploradores web custodian feroz y estrictamente la "Política del Mismo Origen" (Same-Origin Policy), requiriendo de forma ineludible que el Backend remoto (Spring Boot) instancie y expulse directrices explícitas incrustadas de compartición "CORS" pre-autorizando el tráfico forastero.
- [ ] c) Spring intercede en el tráfico con un `JwtFilter` restrictivo prohibiendo explícitamente y bajo sanción todo el contenido emitido desde transpiladores ECMAScript.
- [ ] d) El puerto transaccional 8080 en modo desarrollo entra por defecto en cuarentena (Pessimistic Isolation), neutralizando iteraciones asíncronas no cifradas con AES256.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** Resulta ser el muro primigenio y habitual de cualquier ecosistema web distribuido ("Cross-Origin Resource Sharing"). Al radicar el Frontend (5173) en un domicilio digital discordante respecto al dominio backend (8080), todo explorador bloquea la carga activa AJAX por motivos de inmunidad ante inyecciones ("XSS"). El Backend mitiga este muro emitiendo encabezados formales que le avisan al explorador: "Reconozco el puerto 5173, autorizo el acceso a mis recursos".

---

### 36. Fragmentación en el Árbol Central Redux

Teniendo en cuenta el incremento descomunal y abismal que asume PA-Shop en funciones orgánicas y módulos heterogéneos dispares de Lógica asincrónica, mantener y anidar todo en un único fichero resolutivo (Reductor Raíz) conlleva fatigas insostenibles de acoplamiento. Valore qué técnica de la biblioteca propicia el desbroce eficiente de este componente:

- [ ] a) Utilizar el método matricial nativo `Promise.all()` diseminando promesas puras y abstractas a distintos archivos interconectables.
- [ ] b) Consolidar el patrón estructural de ensamblaje dividiéndolos en reductores diminutos y parciales estancos que se encapsulan con ayuda transversal de la matriz orquestadora `combineReducers`.
- [ ] c) Redux impone estrictamente un diseño monolítico integral, vetando la disgregación en bloques modulares para conservar la igualdad referencial subyacente intacta de sus variables.
- [ ] d) Empotrar lógicas resolutivas directamente mediante mutación sucia (Dirty State) inyectadas asincrónicamente mediante Contextos transaccionales locales en la carpeta Components.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** Abordar el control central de datos en escalabilidad demanda inexorablemente desintegrar el algoritmo en funciones puras especializadas en recovecos limitados de responsabilidad única. La librería asume esta directriz exportando `combineReducers`, una utilidad arquitectónica magistral encargada de amalgamar "mini-reductores" (uno que dirija "usuarios", otro "pedidos"), empaquetándolos transparentemente en un macro-diccionario sinérgico y coherente de altísima tolerancia e integridad global.

---

### 37. Anomalías Temporales del Modo Estricto de React 18

Al operar la ejecución del código funcional tras una recarga exitosa y navegar hasta la ventana "Detalles de Producto" orientada a extraer descripciones asíncronamente en el Frontend, el programador fiscaliza asustado a través de su consola de inspección que el navegador web ha emitido un doble latido idéntico al Backend mediante dos peticiones duplicadas. Identifique la exégesis de ingeniería exacta que solventa este dilema:

- [ ] a) Redux transfiere cíclicamente una iteración superflua e infinita, indicando que el Hook falló forzando un loop destructivo inminente en RAM.
- [ ] b) React Bootstrap interceptó erróneamente un foco no validado provocando un envío doble a causa del atributo nativo de etiqueta `autoFocus`.
- [ ] c) Se trata de un espejismo inofensivo inducido intencionalmente en exclusiva durante fase de desarrollo por `<React.StrictMode>`. Esta capa evaluativa monta, desmonta vertiginosamente y vuelve a montar cada vista de forma artificial, forzando y auditando brutalmente la pulcritud imperativa de las funciones de limpieza (Clean-Up).
- [ ] d) El patrón de acceso por propiedad incurrió en inconsistencias provocando transiciones Dirty State dobles en las transacciones perezosas del Controlador REST.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Bajo la lupa inclemente del modo de audición `StrictMode`, el framework React aplica "Terapia de choque". Su objetivo es desenmascarar si nos hemos olvidado de abatir promesas pendientes, suscripciones asíncronas perennes o temporizadores fantasma, ejecutando un montaje y desmontaje súbito forzado e instantáneo de prueba inicial, lo que conlleva la invocación reiterada del bloque funcional `useEffect` simulando este rebote doble temporal inexistente en producción.

---

### 38. Búsquedas Dinámicas, Interfaces Nulas y Herencia Múltiple

La anotación mágica inyectora `@Query` se vuelve inoperante o insuficientemente ágil para gestionar filtrados web mutables donde parámetros opcionales pueden omitirse o acumularse dinámicamente bajo demanda asincrónica (ej: búsquedas interactivas del Catálogo de la asignatura). Según la arquitectura imperante del modelo, analice el mecanismo sintáctico para solucionar esta incapacidad algorítmica y señale el veredicto:

- [ ] a) Resulta ineludible segregar la lógica mediante la creación de una interfaz hija lateral acoplada a una clase manual (CustomizedDaoImpl) utilizando la API de bajo nivel de Criteria y enlazarla obligando a la interfaz originaria base `ProductDao` a heredar e importar en bloque de ambas.
- [ ] b) JPA nos permite solventar este atasco técnico mediante el decorador avanzado transaccional estático `@DynamicUpdate`, alterando la consulta precompilada del pool subyacente en caliente.
- [ ] c) La sintaxis JPQL suple este atasco permitiendo condicionales puros dentro del texto `IF-THEN-ELSE` de forma matricial esquivando la implementación y aislando los recursos nulos.
- [ ] d) Se delega invariablemente la tarea forzando a cargar absolutamente todas las colecciones pasivamente en formato matricial a la RAM (fetch completo a L1) y filtrando el remanente posterior en los Servicios Lógicos mediante la función nativa `.stream()`.

> [!success]- **Solución y Justificación** 
> **Opción correcta: a)** Este es el patrón oficial de inyección y extensión para Consultas Dinámicas (CustomizedDao Pattern). Las anotaciones fijas son dogmas ciegos y compilados, inflexibles a mutaciones orgánicas (criterios nulos opcionales múltiples). Para construir un árbol decisional adaptable en tiempo de ejecución (Criteria API o EntityManager), segregamos estas tareas dinámicas complejas a una interfaz a medida e integramos las fuerzas polimórficamente exigiendo Herencia Múltiple transparente en nuestro componente repositorio final.

---

### 39. Caché de Primer Nivel L1 y Rendimiento

Asuma que el programador codifica un método acordonado bajo la anotación matriz `@Transactional` para reajustar los perfiles de facturación. En la línea inicial extrae un pedido usando `findById(99)`. Más adelante, tras interponer verificaciones lógicas de permisos extensas y sin abandonar la misma función asincrónica en ejecución, instiga un segundo llamado idéntico de rastreo transaccional invocando nuevamente `findById(99)`. Prevea exactamente la repercusión física en la infraestructura de hardware:

- [ ] a) El Driver JDBC cursará obligatoriamente dos sentencias de selección `SELECT` reales e íntegras, castigando inútilmente a MySQL en aras de mitigar lecturas fantasmas de alta concurrencia.
- [ ] b) El framework lanza una `OptimisticLockingFailureException` inmediata vetando recargas cruzadas sin un Commit subyacente confirmatorio intermedio.
- [ ] c) Se materializará exclusivamente una única y pionera extracción `SELECT`. La segunda incursión será amortiguada y servida mágica e instantáneamente en rama mediante el repositorio temporal volátil en RAM, denominado Caché de Primer Nivel, asociado umbilicalmente a la transacción vigente.
- [ ] d) Ninguna de las anteriores.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Uno de los pilares de la tremenda eficiencia asincrónica inmanente al motor de JPA reside en la interceptación inteligente. Mientras el cauce transaccional mantenga las fronteras de su sesión abiertas, almacena un subconjunto orgánico de todos los elementos consultados. La reincidencia iterativa sobre la base exigiendo registros recién inspeccionados es mitigada, nutriéndose pasiva y velozmente a través de las cachés internas para aplacar el castigo excesivo en las redes I/O.

---

### 40. Extracción de Lógica, POJOs y Traducción al Cliente Red

Cuando el flujo transaccional y resolutorio llega a su colofón y transfiere la custodia de los objetos primitivos purificados (POJOs empaquetados bajo los patrones DTO) de vuelta a los nodos exteriores a través del decorador global `@RestController`, ¿quién se subroga nativamente el papel fundamental y oscuro de desentrañar, traducir sintácticamente y emitir al protocolo externo el ensamblado final de estas variables para su lectura asíncrona?

- [ ] a) Vite y su componente emisor transpilado `appFetch`.
- [ ] b) Bean Validation dictaminando e inyectando las directrices inmanentes pasivas del arroba `@Validated`.
- [ ] c) El motor de renderizado asíncrono pasivo implementado puramente mediante JSX a través de `MessageSource`.
- [ ] d) La librería encriptada subsidiaria e imperceptible Jackson de Spring, que interviene la salida, mapea reflexivamente las colecciones anidadas y expide instantáneamente su flujo representacional textual riguroso bajo formato binario JSON abierto.

> [!success]- **Solución y Justificación** 
> **Opción correcta: d)** En el corazón orgánico de la capa limítrofe y perimetral de Servicios, cuando declaramos métodos sin plantillas gráficas (`@RestController` o `@ResponseBody`), el contenedor Spring no remite objetos crudos nativos de Java a través del éter del protocolo HTTP. Se fundamenta y apoya intrínsecamente en el serializador oficial enmascarado "Jackson", el cual disecciona reflexivamente los DTOs rellenando un texto legible y estandarizado sin interrupciones transaccionales denominado JSON, ideal para el consorcio React.

---

### 41. Generación de Claves Primarias (JPA)

A la hora de modelar la clave primaria de una entidad bajo la especificación estricta de JPA, la anotación `@GeneratedValue` delega la instanciación al motor de la base de datos subyacente. Si nuestro ecosistema empresarial transita de un gestor tradicional MySQL hacia un entorno corporativo basado en Oracle, ¿qué alteración técnica se vuelve preceptiva en el mapeo Java?

- [ ] a) Mantener inalterada la estrategia predeterminada `GenerationType.IDENTITY`, ya que la especificación JPA efectúa una abstracción total y transparente del motor relacional instalado.
- [ ] b) Migrar forzosamente la configuración paramétrica hacia `GenerationType.SEQUENCE`, dado que los sistemas como Oracle repudian las columnas autoincrementales, requiriendo el uso de secuencias nativas acompañadas de `@SequenceGenerator`.
- [ ] c) Desactivar la directriz `@GeneratedValue` en su totalidad, forzando a la capa de Lógica de Negocio a instanciar la inyección manual asincrónica empleando Proxies UUID.
- [ ] d) Spring Data inyecta automáticamente perfiles `@ActiveProfiles` que resuelven esta colisión estructural prescindiendo por completo de la intervención del desarrollador.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** La asignatura distingue taxativamente el comportamiento de los SGDb frente a la inyección de llaves. En MySQL, la directiva `GenerationType.IDENTITY` concuerda con las columnas nativas autoincrementales. Por el contrario, Oracle impone el paradigma computacional de secuencias de base de datos separadas. Para orquestar esta inyección, la anotación JPA requiere permutar irrevocablemente hacia `GenerationType.SEQUENCE`.

---

### 42. Relaciones y Mapeo Sintáctico (@ManyToOne)

Considere una relación bidireccional entre la entidad matriz `Company` (Lado 1) y `Employee` (Lado N). Un programador inexperto decora el método `getCompany()` alojado en la entidad hija `Employee` (que custodia la clave foránea) introduciendo la siguiente cabecera sintáctica en Java: `@ManyToOne(mappedBy="company", fetch=FetchType.LAZY)`. ¿Cuál es el dictamen arquitectónico oficial aplicable sobre esta línea?

- [ ] a) Es estrictamente correcta y estipula que la inicialización perezosa (LAZY) se gobierna interceptando la caché de la propiedad "company".
- [ ] b) Constituye una trampa mortal sintáctica de examen y un error de compilación ineludible, puesto que la directiva relacional `@ManyToOne` jamás soporta o acepta el atributo `mappedBy`.
- [ ] c) Viola las reglas declarativas dado que la carga LAZY está prohibida en el lado propietario, forzando invariablemente a una inyección en modo EAGER.
- [ ] d) Su redacción es válida únicamente si se acompaña de una anotación complementaria de intercepción `@Transient` para ocultar la referencia subyacente.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** Es catalogada expresamente en la Guía Antifallo (Tema 2) como "TRAMPA MORTAL DE EXAMEN". El atributo `mappedBy` es un privilegio de uso exclusivo e intransferible reservado para las entidades delegadas o "lado inverso" (usualmente `@OneToMany` o `@OneToOne`). Inyectar este vocablo paramétrico dentro de `@ManyToOne` invalida la compilación automática de Hibernate en el acto.

---

### 43. Pruebas Automatizadas y Caché L1

Durante la concepción y estructuración de pruebas automatizadas con el marco híbrido `spring-test`, se recupera exactamente la misma entidad en memoria mediante dos llamadas continuadas a `findById()` dentro de un bloque funcional de prueba decorado con `@Transactional`. Evaluando la aserción posterior, la comparativa `assertEquals(user1, user2)` reporta éxito incondicional a pesar de no haberse sobrescrito jamás los métodos puristas de herencia `equals()` y `hashCode()`. Identifique el fenómeno que ampara este hecho:

- [ ] a) El entorno de `spring-test` muta polimórficamente por reflexión las clases del `application.yml` introduciendo un clonado superficial subyacente.
- [ ] b) Se materializa gracias a la Caché de Primer Nivel (L1); al operar bajo el paraguas de una única transacción, el contenedor Hibernate provee exactamente el mismo puntero y objeto instanciado en la memoria RAM, validando matemáticamente la igualdad referencial estricta de Java (`==`).
- [ ] c) El módulo `spring-boot-starter-test` paraliza las validaciones internas de JUnit forzando afirmaciones positivas en ausencia de un Rollback manual previo.
- [ ] d) La anotación interceptora suprime las consultas físicas, reasignando variables a proxies genéricos universales vacíos cuyo contenido matemático equivale siempre al nulo subyacente.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** Cuando un bloque de código se envuelve bajo `@Transactional`, el motor inyecta transitoriamente un repositorio en caché L1. Cualquier búsqueda iterada sobre un registro primario previamente cargado no lanza consultas nuevas, sino que el sistema nos devuelve irremediablemente el puntero vivo almacenado. Así, los objetos en RAM resultan ser referencial y molecularmente el mismo, haciendo redundante el cálculo del método equals().

---

### 44. Componentes Transaccionales de Solo Lectura

Sabiendo que el decorador semántico global `@Transactional` centraliza y agrupa atómicamente un bloque transaccional del servicio, un ingeniero decide optimizar una rutina analítica decorándola específicamente como `@Transactional(readOnly=true)`. Ante esta sintaxis restrictiva, seleccione la afirmación dogmática exacta que gobierna la topología de la base de datos:

- [ ] a) Se trata de un espejismo semántico. El marco Spring anula y expulsa la apertura transaccional operando en un arriesgado modo "Auto-Commit".
- [ ] b) Sigue abriéndose e instanciándose activamente un contexto de transacción subyacente, pero instruye taxativamente al Driver JDBC de que su propósito es la mera recuperación pasiva, permitiendo suprimir bloqueos físicos perjudiciales y volcados de datos redundantes.
- [ ] c) Resulta letal si se acompaña de consultas paginadas, ya que repudia las sentencias ocultas tipo LIMIT colapsando la pila en ejecuciones asincrónicas.
- [ ] d) Inyectará excepciones silenciadas si el controlador devuelve un DTO sin deserializar, corrompiendo la caché transaccional principal.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** Afirmar que `readOnly=true` elude transacciones es un error conceptual crítico. La transacción sí se materializa y ampara al bloque en su totalidad; no obstante, actúa como un banderín de información dirigida al sistema transaccional del driver (y al motor físico) confiriéndole prerrogativas puras de optimización frente al bloqueo concurrido y suprimiendo el escaneo interno de comprobación del estado Dirty.

---

### 45. Empaquetado y Artefactos de Despliegue

Concluido íntegramente el diseño de la arquitectura Backend apoyado en Spring Boot, los equipos de integración y despliegue (DevOps) tramitan la instrucción de compilación oficial `mvn package`. Evaluando la configuración dogmática y estándar de los cimientos del ecosistema de la asignatura, dictamine la anatomía y topología computacional del artefacto consolidado:

- [ ] a) Se compila irrevocablemente una librería mutilada de formato `.war` que exige incrustarse manualmente mediante la intervención del administrador dentro de un Servidor Tomcat exterior ya parametrizado.
- [ ] b) Empaqueta exclusivamente las rutas controladoras, desvinculando la lógica JDBC para ser interceptada asincrónicamente por la abstracción de Redux en memoria transitoria.
- [ ] c) Se materializa y forja de forma inmutable un contenedor monolítico e independiente denominado "Fat JAR", cuyo interior aloja la compilación funcional unida intrínsecamente a su propio servidor web Tomcat incrustado, permitiendo ejecuciones prístinas autónomas.
- [ ] d) Genera una colección pasiva de ficheros XML configurativos dependientes, incapaces de arrancar salvo mediando la inyección activa del entorno Node.js.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Uno de los triunfos resolutivos más profundos de Spring Boot se sustenta en su poder de autocontención. Al lanzar `mvn package`, evade el suplicio de generar el antiguo y frágil ecosistema WAR e infunde al artefacto un formato "Fat JAR" (Jar gordo), el cual engulle y aprisiona en su núcleo un servidor web, empoderándolo para cobrar vida instantáneamente en cualquier servidor virgen mediante un simple `java -jar`.

---

### 46. Seguridad JWT: Criptografía y Cabeceras

Bajo el canon de diseño establecido en la plataforma PA-Shop, los pases VIP perimetrales circulan empacados en un JSON Web Token (JWT). Analizando los rigores criptográficos inherentes a la constitución pública de esta credencial (RFC 7519) que viaja hacia el Frontend, escoja la premisa matemática veraz:

- [ ] a) El cuerpo de la carga interior (payload) que alberga el rol se halla herméticamente encriptado con protocolos simétricos ultraseguros AES-256, siendo imposible descifrarlo si se desconoce la contraseña alojada en Spring.
- [ ] b) El token se camufla como parámetro enmascarado viajando incrustado en el "Query String" (ej. `/checkout?authorization=jwt`), evadiendo intercepciones maliciosas de cabeceras pasivas.
- [ ] c) El token transpira mediante la Cabecera `Authorization: Bearer <token>`; su anatomía interior viaja en formato base64url visualmente decodificable por cualquiera, descansando su inviolabilidad en la blindada e inalterable Firma matemática anidada validada por el servidor con HS256.
- [ ] d) Carece intrínsecamente de controles biológicos temporales (exp), obligando a que la base de datos implemente cerrojos pesimistas recurrentes para abolir su ciclo de existencia.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Es una "pregunta trampa" común creer que el contenido del JWT (roles o IDs) viaja encriptado. Un JWT base es transparente y descifrable visualmente (base64url); su seguridad no recae en ocultar el contenido, sino en blindarlo algorítmicamente mediante una firma infranqueable (`alg: HS256`) acoplada a un secreto custodiado celosamente en el servidor que veta e impide cualquier manipulación parasitaria del certificado.

---

### 47. Extracción Paramétrica en Rutas REST

En el tejido arquitectónico exterior perimetral de un Controlador expuesto mediante el decorador `@RestController`, la vía de extracción dinámica avanza de forma asincrónica. Suponga la intersección combinada donde ingresan atributos desde la URL `GET /shopping/orders/14` por un lado, y desde consultas adyacentes `GET /shopping/orders?page=2` por el otro. Seleccione la nomenclatura sintáctica exacta que absorbe ambos canales:

- [ ] a) Utilizar `@RequestBody` para capturar asincrónicamente el 14, y delegar el `page` incrustado en variables `@RequestAttribute`.
- [ ] b) Inyectar orgánicamente `@PathVariable` para sustraer la variable incrustada fundacional (el 14 de la ruta) y emparejar `@RequestParam` destinado a captar el modificador colateral alojado en la Query String (`page=2`).
- [ ] c) Implementar el módulo pasivo y unificado `@Validated` el cual extrapola y transfiere mágicamente cualquier sufijo textual traduciéndolo al DTO respectivo alojado en RAM.
- [ ] d) Carece de soporte nativo para múltiples inyecciones discordantes obligando siempre al uso de `appFetch` condicional emulando parámetros formales por `noValidate`.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** La asignatura estipula nítidamente las normativas de inyección aledaña. Cualquier variable numérica o conceptual alojada y vertebrada sintácticamente en la barra principal del directorio de ruta (ej. `/orders/{id}`) se succiona invocando incondicionalmente a `@PathVariable`. A su vez, los sub-elementos anexos a la cola e instigados por interrogantes (el clásico Query String de búsquedas) se absorben y recuperan ordenando una invocación a `@RequestParam`.

---

### 48. Gestión de Excepciones e Internacionalización (i18n)

Cuando el radar centralizador unificado del sistema `@ControllerAdvice` interviene como salvavidas abortivo atajando catástrofes controladas (`InstanceNotFoundException`), asume la potestad resolutiva para retornar fallos legibles y coherentes. ¿Cuál es el proceso invisible, orgánico e inherente a Spring Web para acatar estrictamente el idioma deseado y mapearlo en `MessageSource`?

- [ ] a) Exige que el JWT adjunte permanentemente un token `i18n-flag` evaluado transaccionalmente por filtros Hibernate y derivado hacia un Proxy interceptor pasivo.
- [ ] b) Extrae automáticamente el formato priorizado por la cabecera preestablecida `Accept-Language` dictada por el navegador exterior web, consolidándola pasivamente en una variable autoinyectada del núcleo de Java denominada `Locale`.
- [ ] c) React Vite compila e incrusta una clave global forzada `default_language` durante el `npm run build`, eclipsando para siempre la petición idiomática de la arquitectura servidor.
- [ ] d) Ninguna de las opciones define el ecosistema, ya que la orquestación recae imperativamente en bucles asíncronos programáticos situados en React Router.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** El estándar de Internacionalización y traducción semántica moderna reniega de obligar al programa a memorizar identidades de usuarios nativos. Por el contrario, delega toda la inteligencia geográfica escuchando reverencialmente y extrayendo la sintaxis pasiva universal del protocolo, esto es, la cabecera inyectada `Accept-Language`. Spring Web orquesta este flujo traduciéndolo internamente en RAM e inyectando un parámetro tipo `Locale` aledaño a nuestros gestores de excepciones.

---

### 49. Funciones Puras en Redux (Reducer)

Ciñéndonos a la exigencia analítica del paradigma reactivo unidireccional y matricial forjado en el Store de Redux, evalúe el código interno insertado programáticamente por un desarrollador dentro del corazón del bloque evaluador condicional de un reductor (`case ADD_TODO:`). Exponga y sancione cuál representa la operativa dogmáticamente legítima exigible:

- [ ] a) `state.todos.push(action.todo); return state;`
- [ ] b) `const resp = await appFetch('POST', '/todos', action.todo); state = resp.payload; return state;`
- [ ] c) `return { ...state, todos: [action.todo, ...state.todos] };`
- [ ] d) Inyectar asincrónicamente una llamada a `setTodos()` amarrando nativamente el Virtual DOM saltándose la cadena algorítmica para evitar renderizaciones pesadas.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Existen Leyes de Oro inviolables castigadas severamente en examen que tutelan los "Reductores". En primera instancia: repudian visceralmente las inyecciones API y asincronías colaterales (opción B descartada al instante por promesa await). En segunda y letal instancia: la "Inmutabilidad Absoluta" paraliza la mutación destructiva física sobre arrays matriz tipo `push()`. La única ruta dogmática de compilación limpia implica generar clonaciones íntegras propagando el rastro antiguo y anidando la nueva traza valiéndose de los operadores esparcidores esotéricos (Spread Operator `...`).

---

### 50. Rendimiento y Mecánica del Hook useSelector

El componente estético superior denominado `ShoppingCartIcon` ostenta la misión pasiva y cosmética de renderizar simplemente el número cardinal de productos guardados, anclándose a las profundidades globales vía extracción simple mediante `const count = useSelector(state => state.cart.items.length);`. Si un componente filial orquesta una mutación subyacente reordenando iterativamente y clonando todas las celdas y punteros de productos en la matriz `items` guardando intacto el tamaño en elementos, deduzca la reacción computacional subyacente inminente:

- [ ] a) React induce inevitable y recursivamente una sobrecarga destructiva al evaluar que el array matriz en sí es un objeto nuevo (`!==`), arrastrando el icono a un repintado obligatorio.
- [ ] b) Redux entra en colisión de sincronía, emitiendo alertas fatales de fragmentación anidada, colapsando el DOM hasta que interceda el `rootReducer`.
- [ ] c) La arquitectura inteligente pasiva paraliza incondicionalmente las fases de repintado del icono, escudándose en que la función comparativa del Hook constata la igualdad matemática referencial (`===`) entre el valor numérico devuelto original y el nuevo.
- [ ] d) La c) es incierta, pues la librería exige estrictamente encapsular estados estáticos valiéndose de la directriz pasiva `<React.StrictMode>`.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Constituye el baluarte de eficiencia del entorno React-Redux. La suscripción de selectores puros no escanea iteraciones pesadas sobre colecciones lejanas para provocar parches inútiles. Como el `useSelector` dictaminado extrae explícita y focalizadamente el atributo estanco de longitud (un número primitivo de Java/JS), aunque el universo del vector cambie molecularmente, si el valor resultante numérico subyacente no muta (e.g. 5 `===` 5), React repudia el rediseño ahogando la propagación parasitaria y blindando la CPU de tu explorador.

---

### 51. Arquitectura de Navegación Inter-componente SPA

Afrontando los severos rigores estructurales impuestos por un entorno de renderizado continuo libre de interrupciones puramente orquestado como Single Page Application (SPA), identifique el fallo dogmático subyacente introducido al aplicar el botón elemental HTML `<a href="/catalog/product-details/1">Ver Detalles</a>`:

- [ ] a) Quebranta los pilares de la retención del estado en RAM; el ancla original HTML desencadena invariablemente una recarga física catastrófica contra el Host del protocolo, destruyendo todo el marco algorítmico Redux cacheado y colapsando variables volátiles, en detrimento del imperativo uso estanco de la herramienta abstracta `<Link>`.
- [ ] b) Las anclas nativas HTML no admiten polimorfismo hacia direcciones paramétricas incrustando el ID `/1`, forzando al navegador a inyectar falsos bucles sin sentido interpretativo.
- [ ] c) Incurre en un conflicto de seguridad lateral denominado CORS, ya que las anclas prohíben adjuntar las cabeceras subyacentes con firmas JWT para accesos privados.
- [ ] d) Ninguna es acertada, puesto que `appFetch` captura y mitiga internamente toda acción nativa y la envuelve por defecto en una promesa interceptada.

> [!success]- **Solución y Justificación** 
> **Opción correcta: a)** Una SPA (React Router) persigue con avidez emular y engañar al ojo dictando una navegación ininterrumpida que simula pantallas sin jamás requerir llamadas pesadas completas al servidor remoto de inicio. Emplear un vínculo arcaico de etiqueta cruda `<a>` es una injerencia fatal: fuerza al navegador a emitir señales de recarga limpias que arrasan la RAM (memoria de estado, Hooks, y Redux), por lo que siempre debe sustituirse empleando componentes mitigadores encapsulados subyacentes como `<Link to="...">`.

---

### 52. Ciclo de Vida del Efecto Limpiador (Clean-up)

Asuma un componente de inspección transaccional (ej: Detalles de Pedido) donde un programador incrusta asincrónicamente el anclaje imperativo de la librería React, dictando lo siguiente en su umbral: `useEffect(() => { dispatch(findOrder(id)); return () => dispatch(clearOrder()); }, [id]);`. Frente al inminente cese o interrupción visual del marco gráfico (el componente procede a desmontarse al regresar a la matriz del catálogo), pronostique su comportamiento nativo y dictamine su fin:

- [ ] a) El Hook repudia la salida de la orden, invocando cíclicamente y sin parar `findOrder` incurriendo en sobrecarga destructiva al transmutar una id inactiva.
- [ ] b) Redux clona en caché inactiva el vestigio del pedido en modo pasivo hasta que un nuevo componente es asignado.
- [ ] c) Se acatará e invocará inexorablemente la directriz dictada por la función remanente `return` (limpiadora / clean-up) vaciando deliberadamente los restos volátiles paramétricos antes del desguace del contenedor gráfico, conjurando el riesgo inminente de retenciones parasitarias o apariciones de información espectral ("fugas de memoria") en renderizados venideros.
- [ ] d) La respuesta B) y C) coexisten si `appFetch` devuelve código familia 2xx.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** En transacciones de carga puntual y transitoria bajo la batuta del marco React, abandonar un nodo sin sanear su basurero lógico en el Store produce los infames efectos de "interferencias fantasma" de datos obsoletos persistiendo temporalmente y fugas computacionales letales para recursos de navegador limitados. La función de cierre o "clean-up" dictaminada por el retorno del propio Hook ataja estas incidencias garantizando una destrucción elegante extirpando la memoria al instante del desensamblaje del DOM.

---

### 53. Componentes Formularios: Entornos "Uncontrolled"

Analice la codificación pasiva en la matriz de la interfaz `AddTodo`, implementado primitivamente como un componente denominado "Uncontrolled" (no controlado), donde la extracción del valor redactado esquiva y desdeña la mediación del Estado (Hook local `useState`) apartándose del diseño natural y fluido de React. Identifique cómo logra anclar su puntero a los datos nativos:

- [ ] a) Vinculando el atributo de evento polimórfico imperativo `onChange` hacia un Reductor matricial global de Redux, el cual extrae por filtrado pasivo al Virtual DOM el texto de la caja nativa.
- [ ] b) Recurriendo a amarrar y apresar un enlace directo y pasivo a la etiqueta real biológica del DOM web interponiendo la directriz paramétrica y mágica de JSX denominada `ref={node => input = node}`.
- [ ] c) Anulando la herencia mediante el uso inyectivo asíncrono de un `appFetch` que rastrea de forma lateral la etiqueta `<form>` en estado letárgico antes de volcar al servidor.
- [ ] d) La B) y la C) describen partes obligatorias de esta técnica marginal reactiva.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** Se ilustra y destripa el mecanismo secundario opuesto al paradigma puro, denominado No Controlado ("Pull"), desaconsejado en sistemas profundos pero existente. En este estilo elusivo, la librería no guarda custodia sincrónica del dato de la celda. El desarrollador inserta una sonda manual (`ref`) sobre la entidad física cruda dictada por el lenguaje HTML base, para recuperar robóticamente la variable del bloque cuando ocurra el salto del evento de Click ("submit"), contraviniendo el flujo armónico natural continuo del Store central o memoria de la clase.

---

### 54. Topología Asincrónica en Entornos de Desarrollo (CORS)

Nuestra topología impone operar asincrónicamente el transpilador Vite empujando su servidor caliente en `http://localhost:5173` y desvinculándolo del robusto ecosistema analítico Spring en `http://localhost:8080`. Ante cualquier señal cruzada de `appFetch`, el mecanismo de barrera de los exploradores contemporáneos estrella incondicionalmente el intento aduciendo un colapso en nombre de la protección originaria "Same-Origin Policy". Señale la afirmación veraz referida a su atajo curativo:

- [ ] a) Requiere la desactivación del protocolo asíncrono de intercepciones y su degradación forzada al uso imperativo excluyente de "Fat JAR" para aglomerarlos localmente sobre Tomcat.
- [ ] b) Precisa indispensablemente de la habilitación tecnológica de permisos y delegación asincrónica en el puerto del receptor (el contenedor de Spring Backend), el cual en su filtro inyectará cabeceras preaprobatorias subyacentes conocidas formalmente como "CORS" (Cross-Origin Resource Sharing).
- [ ] c) La directriz es insalvable y abortiva en todo momento, obligando irremediablemente al desarrollador a reorientar la IP estipulada empujando el proyecto mediante parámetros `encodeURIComponent()` para sortear la seguridad inmanente.
- [ ] d) Resulta un escollo subsanado exclusivamente por `noValidate` para el entorno Web.

> [!success]- **Solución y Justificación** 
> **Opción correcta: b)** Es el tropiezo por antonomasia de la programación distribuida moderna. Las librerías subyacentes de los navegadores actúan como aduaneros implacables (Política de Mismo Origen), aniquilando tráfico bidireccional entre domicilios o dominios inconexos con el objetivo férreo de impedir intrusiones indeseadas de inyecciones de script lateral (XSS). La exención técnica oficial ("CORS") recae ineludiblemente en que el componente "invitado" (Servidor Spring en puerto 8080) conceda un salvoconducto explícito mediante envío de cabeceras HTTP que legitiman a Vite y rebajan el muro.

---

### 55. Sintaxis de Validaciones Nativas Suprimidas

Dentro de las celdas pasivas en un formulario reactivo controlado (`BuyForm`) destinado a efectuar transferencias complejas, subyace el imperativo arquitectónico de acallar e interceptar las feas burbujas preventivas con las que los navegadores web modernos castigan los campos inválidos de manera rudimentaria. Escoja mediante qué herramienta estructural el componente recaba todo el dominio y depone este comportamiento visual originario:

- [ ] a) Expurga las dependencias HTML5 reemplazándolas nativamente instigando atributos polimórficos tipo `@Validated` en cada `<Form.Control>`.
- [ ] b) Impide los eventos al clausurar en bloque todos los métodos interceptores invocando en bucle ciego `e.preventDefault()`, anulando inclusive a React Router subyacente.
- [ ] c) Anula la injerencia visual foránea mediante la incrustación biológica del atributo paramétrico orgánico `noValidate` posicionado centralizadamente en la raíz `<Form>`, acaparando el juicio final invocando asincrónicamente de forma lógica el comando `checkValidity()`.
- [ ] d) Las opciones B) y C) juntas conforman la regla estricta unívoca de esta supresión gráfica.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** En pos de usurpar la estética intrusiva natural (y comúnmente arcaica) del explorador subyacente, delegando una armónica consistencia corporativa de CSS superior al framework React Bootstrap, el código nos impone desensamblar el radar pasivo del DOM de navegador insertando `noValidate` en su envoltura, y forzar de forma lógica, pura y calculada en el umbral de disparo el filtro asíncrono con el objeto interceptivo `form.checkValidity()`.

---

### 56. Rendimiento y Concordancias en Iteración de Listas

A la hora de codificar un componente matricial encargado de expandir y mapear la memoria del estado (`todos.map(todo => ...)`), el flujo de ejecución arroja un castigo severo contra la RAM advirtiendo la omisión de un vocablo estructural insalvable por parte del alumno. Dictamine cuál representa la base científica irrefutable por la que la biblioteca madre impone el uso de un parámetro especial asociado a iteradores continuados:

- [ ] a) Omite la parametrización pasiva `class` que debe insertarse como clave para generar una renderización nativa exenta de Hooks.
- [ ] b) Carece de la anotación `index={i}` de uso vital para que las promesas no alteren la igualdad relacional subyacente impuesta por el motor asíncrono del compilador Vite en desarrollo local.
- [ ] c) El ecosistema del Virtual DOM asume como dogmático incrustar una marca distintiva singular conocida como propiedad `key` adherida indisolublemente a la raíz de cada clon descendente; esto inyecta radades inconfundibles al algoritmo de cálculo topológico y evaluación gráfica "Diffing" mitigando estrangulamientos ciegos por escaneos destructivos al reordenar o mutilar.
- [ ] d) Ignorar dependencias referenciales expulsa fallos en consolas porque desata una transpilación errónea entre Redux y Jackson.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Inmenso en importancia y calado es el mandato para mapeos. Sin inyectar llaves fijas posicionales paramétricas unívocas (`key={item.id}`), el engranaje profundo matricial del Virtual DOM enloquece y naufraga ("Diffing Algorithm") tratando de deducir, celdilla a celdilla de manera redundante, si ha existido una transmutación o si el bloque es idéntico a su clónico precedente. Adjuntando un rastreador fijo de base de datos se disuelve de facto el ahogo del repintado masivo y se restituye un rendimiento soberbio instantáneo.

---

### 57. Estructuras Avanzadas de Microservicios (Dominio Distribuido)

Afrontando las directrices inmanentes del último peldaño de la asignatura asumiendo el paradigma superior enfocado en escalabilidad monstruosa horizontal distribuida, procedemos a decapitar a PA-Shop y segregarlo biológicamente en bloques autónomos segregados. A nivel dogmático transaccional, ¿cómo gestionamos el impacto y las repercusiones a la hora de ubicar la base persistente de almacenamiento de este mosaico y salvaguardar los dominios de la alta concurrencia asincrónica de rebajas?

- [ ] a) Exigiendo perpetuar por motivos de control estricto de concurrencia la inyección de una hiper-base persistente unitaria de formato monolítico, compartida transversalmente y sin barreras a lo largo de todos los ecosistemas fragmentados por Docker y amparada bajo Optimistic Locking extremo en capa común.
- [ ] b) Transmutando la persistencia y forzando a que las colecciones se transformen en ficheros JSON independientes de acceso por Redux almacenados en los depósitos de RAM distribuidos en Redis.
- [ ] c) Otorgando independencia soberana dictaminando taxativamente que a cada Microservicio o dominio de responsabilidad estanca y fraccionada le corresponda una base de datos propia separada biológica y físicamente como baluarte contra caídas sistémicas en cadena (cuellos de botella globales).
- [ ] d) Invocando asincrónicamente un proxy central delegativo ("Fat WAR") que acorrala e impide cualquier incursión transaccional descontrolada proveniente de ecosistemas ajenos y los encapsula en Tomcat.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** En el canon del salto tecnológico supremo orquestado en los esquemas distribuidos modernos de gran empresa y expuesto en el Tema 8, la disgregación en bloques modulares carece de sentido si el engranaje tropieza en la capa de datos. Resulta dogmático y vital emancipar y mutilar las raíces interdependientes, delegando bases unívocas ("Database-per-service pattern") para que la caída, bloqueo asincrónico o saturación extrema de una celda ("Usuarios") jamás asfixie ni corrompa el acceso al ecosistema contiguo transaccional del resto ("Catálogo").

---

### 58. El Patrón DTO en Fronteras Perimetrales

La doctrina arquitectónica de transacciones limítrofes implementada en el Controlador de Operaciones (`@RestController`) repudia y sentencia enérgicamente cualquier volcado exterior ingenuo y temerario de los entes primitivos matrices (Nuestras Clases `@Entity` como `Order` o `User`). Determine con precisión dogmática cuál de estos motivos sustenta y ampara científicamente dicha clausura arquitectural irrebatible:

- [ ] a) Al no constar con propiedades autoincrementales UUID externas asíncronas de Jackson impiden de facto que el explorador de cliente logre traducir cabeceras HTTP preestablecidas al entorno purista JavaScript.
- [ ] b) JPA sufre inyecciones cruzadas de inmutabilidad estanca que obligan a usar `appFetch` a través de colecciones unidireccionales en memoria si viajan desde la red en formato crudo.
- [ ] c) De hacerlo, colapsaríamos irrevocablemente el JSON por las referencias anidadas circulares cruzadas al entrar en bucles letales, desnudaríamos vulnerabilidades exhibiendo el esqueleto de persistencia SQL de la base de datos íntima y arrojaríamos catástrofes silenciadas por inicializaciones tardías (LAZY Proxies) que exigirían peticiones asincrónicas de base habiéndose roto ya la transacción lógica transitoria.
- [ ] d) Transitar atributos de base corrompe `GenerationType.SEQUENCE` alterando los diccionarios por polimorfismos residuales de los ecosistemas distribuidos en red.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Retornar y escupir por la red un objeto original "Entidad" aglutina un tridente catastrófico expuesto formalmente como error de principiante en producción: Muestra al mundo cómo has organizado y estructurado tus columnas base SQL. Si tienes relaciones entrelazadas 1:N cruzadas el mapeador de texto cae en bucle de repeticiones sin fin rompiendo memoria. Y al poseer atributos retardados estipulados pasivos ("Proxies" perezosos), su intento de carga estallaría violentamente, pues al rebasar la barrera de tu Servicio el cordón umbilical de Hibernate ya yace finiquitado y sin respuesta.

---

### 59. Sintaxis de Enrutamiento Condicional en SPA (React Router)

Bajo los rigores del esquema evaluativo matriz que gobierna y dicta el enrutador virtual de la aplicación, el componente base distribuye transiciones por defecto. Analice y dictamine el comportamiento algorítmico interno al declarar un camino `path="/*"` en coexistencia paramétrica concurrente con transiciones explícitamente delimitadas de la forma `path="/catalog/find-products-result"` para dirimir colisiones:

- [ ] a) React se cuelga emitiendo alertas incesantes y rehusando la carga del DOM en cascada ante ambigüedades insalvables sin `encodeURIComponent()`.
- [ ] b) Evalúa y acata incondicionalmente la primera directriz impuesta topológicamente en la matriz léxica del documento por orden estricto de aparición nativo ignorando todo lo demás.
- [ ] c) El componente de enrutamiento orgánico evaluador disecciona el árbol, priorizando con un escrutinio astuto la regla de ruta específica que concuerde de modo más exhaustivo o minucioso ("exact match"), reservando y delegando el anclaje asterisco expansivo ("/*") como un muro de red de seguridad subsidiario para URLs extraviadas.
- [ ] d) Omite la declaración transaccional hasta que `appFetch` arroje excepciones familia 4xx.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** Configura el andamiaje protector subversivo de la topología SPA asíncrona. La librería React Router goza de un enrutador inteligente y deductivo asombroso. No se ahoga en colisiones ciegas, sino que escanea la ruta del usuario, halla la correspondencia léxica más precisa existente en tu matriz y aparta el componente genérico atrapalotodo (asterisco "/*") confiriéndole funcionalidad de paracaídas final (Páginas NotFound 404 o Home predeterminada) eludiendo errores garrafales.

---

### 60. Estado Normalizado en Redux y Big Data (Complejidad O(1))

A medida que el ecosistema subyacente y transaccional masivo de nuestra infraestructura de tienda sufre gigantismo computacional, la memoria central Redux abomina y abandona el alojamiento de las matrices elementales convencionales (`[ ... ]`) por matrices fraccionadas en un esquema avanzado conocido y parametrizado formalmente en el temario como "Estado Normalizado". Desvele la naturaleza íntima purista que dictamina su eficacia:

- [ ] a) Implica aislar y anidar bucles asincrónicos `await` y promesas mediante Contextos Reactivos que liberen al CPU nativa ECMAScript para evadir las recargas F5 impuestas pasivamente.
- [ ] b) Impide los bucles en la función pura porque transita de un modo de escritura pasivo a un bucle infinito que destroza selectores no controlados si coexisten variables anidadas.
- [ ] c) Transfigura matrices lentas y costosas de recorrer computacionalmente O(n) por un complejo e ingenioso Diccionario asociativo indexado por claves inmutables puras de persistencia (`byId`), instaurando un repintado de búsquedas y mutaciones pasmosamente eficiente de coste algorítmico marginal instantáneo predecible logarítmico O(1).
- [ ] d) Inyecta la sintaxis de base relacional emulando a un motor de base de datos interconectado en la memoria transitoria mediante el módulo auxiliar de caché externa `sessionStorage`.

> [!success]- **Solución y Justificación** 
> **Opción correcta: c)** En arquitecturas abrumadoramente grandes que custodian miles de variables estancadas interconectadas en el navegador cliente por Redux, las actualizaciones en vectores elementales O(n) condenan y asfixian al procesador obligándolo a ciclar infinitamente sobre barridos. El "Estado Normalizado" rompe estas cadenas estructurando colecciones masivas mediante objetos en formato diccionario (`{ "402" : {...} }`). Al contar con índice directo nativo se efectúan escrituras matemáticas con complejidad logarítmica constante O(1), preservando intacta la sagrada inmutabilidad reactiva y blindando su respuesta en escalas masivas.