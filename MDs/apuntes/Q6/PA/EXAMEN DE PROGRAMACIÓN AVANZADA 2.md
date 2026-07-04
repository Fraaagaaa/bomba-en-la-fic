
---
##### 1.

Usted diseña la entidad `OrderItem` aplicando el Patrón Domain Model para encapsular la lógica de negocio intrínseca. Sabiendo que el acceso a datos está configurado por "propiedad" (anotaciones en los getters), implementa el siguiente bloque de código:


```Java
@Entity
public class OrderItem {
    // ... otros atributos y mapeos ...

    public BigDecimal getSubtotal() {
        return this.productPrice.multiply(new BigDecimal(this.quantity));
    }
}
```

¿Cuál será el veredicto del framework al intentar levantar el contenedor de Spring Boot?

- [ ] a) El sistema arrancará a la perfección, ya que JPA abstrae y omite de forma inteligente cualquier método que no posea una anotación directa tipo `@Column`.
    
- [ ] b) El sistema colapsará catastróficamente durante el arranque. JPA asume que todo método con el prefijo `get` corresponde a una columna física en la tabla SQL. Al no encontrar la columna `subtotal`, lanzará una excepción.
    
- [ ] c) El código provocará un bucle infinito en el motor de Hibernate al intentar sincronizar el cálculo matemático con la Caché de Primer Nivel (L1).
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Solución y Justificación**
> 
> **Opción correcta: b) El sistema colapsará catastróficamente durante el arranque.**
> 
> **Justificación (Ref. Tema 2 - "Métodos de negocio en entidades"):** En el enfoque de acceso por propiedad, JPA escanea mediante reflexión todos los métodos precedidos por `get` o `is` para delinear el esquema SQL. Asumirá ciegamente que `getSubtotal()` es un campo e intentará buscar en base de datos la columna `subtotal`. Para incorporar métodos matemáticos de negocio (patrón Domain Model) sin corromper el modelo relacional, debe decorarse la cabecera obligatoriamente con la anotación `@Transient`.

##### 2.

Para orquestar la concurrencia masiva en la tienda durante el Black Friday, descartamos los cerrojos físicos de base de datos en favor del patrón "Optimistic Locking". Cuando dos transacciones simultáneas (T1 y T2) intentan actualizar el mismo registro (problema del "Second Lost Update"), ¿cuál es la mecánica exacta impuesta por JPA para proteger los datos?

- [ ] a) Empaqueta la actualización en un bucle `while(true)` que itera intentando volcar los datos hasta que el hilo de concurrencia quede liberado.
    
- [ ] b) Emite un comando `UPDATE ... WHERE id=? AND version=?`. Si T2 llega tarde, el motor detecta que la versión ha cambiado, afectando a 0 filas y desencadenando una `OptimisticLockingFailureException` que aborta la transacción con ROLLBACK.
    
- [ ] c) Transfiere el nivel de aislamiento a `TRANSACTION_SERIALIZABLE` temporalmente, forzando un bloqueo de hardware exclusivo en la tabla.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Solución y Justificación**
> 
> **Opción correcta: b) Emite un comando UPDATE ... WHERE id=? AND version=?. Si T2 llega tarde, el motor detecta que la versión ha cambiado, afectando a 0 filas y desencadenando una OptimisticLockingFailureException...**
> 
> **Justificación (Ref. Tema 3 - "Optimistic Locking"):** Para salvaguardar la escalabilidad y no asfixiar el tráfico web mediante candados de nivel `SERIALIZABLE` (opción C), incrustamos el atributo `@Version`. Hibernate, de forma silenciada, adjunta un chequeo numérico en la cláusula `WHERE`. Si la actualización devuelve "0 filas afectadas", significa que un intruso ya mutó el registro, orquestando JPA un control de pánico (rollback controlado).

##### 3.

Un desarrollador inexperto que no comprende el flujo de una Single Page Application (SPA), construye el siguiente enlace en JSX para navegar hacia los detalles de un producto en el catálogo:


```javascript
const ProductLink = ({ id, name }) => {
    return (
        <div className="product-link">
            <a href={`/catalog/product-details/${id}`}>
                {name}
            </a>
        </div>
    );
}
```

¿Qué letal consecuencia arquitectónica provocará que un usuario haga clic en este enlace nativo de HTML?

- [ ] a) React Router interceptará el evento pasivamente, optimizando la ruta sin perturbar el Virtual DOM mediante un enganche CORS.
    
- [ ] b) Destruirá por completo el estado de la aplicación. Al forzar una petición física real al servidor HTTP, la memoria RAM se vacía, aniquilando el Store de Redux, el carrito y la sesión de usuario activa.
    
- [ ] c) Vite repudiará la sintaxis en tiempo de compilación, ya que JSX prohíbe taxativamente la inyección de plantillas de texto `${id}` en propiedades de navegación.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Solución y Justificación**
> 
> **Opción correcta: b) Destruirá por completo el estado de la aplicación. Al forzar una petición física real al servidor HTTP, la memoria RAM se vacía, aniquilando el Store de Redux, el carrito y la sesión de usuario activa.**
> 
> **Justificación (Ref. Tema 7 - "Layout y enrutamiento"):** Este es el "pecado capital" en ecosistemas Single Page Application (SPA). El uso de la etiqueta originaria HTML `<a>` insta al navegador a purgar y sustituir enteramente el DOM pidiendo el nuevo archivo `index.html`. Debemos delegar invariablemente la navegación intra-vista al componente `<Link to="...">` de React Router, quien engaña al visualizador mutando la URL y repintando componentes virtuales eludiendo peticiones masivas al servidor.

##### 4.

A medida que el catálogo de PA-Shop escala a decenas de miles de productos, almacenar el listado en Redux mediante una matriz secuencial plana (Array) degrada el rendimiento de la CPU al buscar o actualizar elementos. ¿Cuál es el dictamen arquitectónico exigido (Estado Normalizado) para alcanzar una eficiencia matemática perfecta de $O(1)$?

- [ ] a) Transmutar la matriz plana por un diccionario asociativo indexado por claves (objeto `byId`), donde el acceso y modificación de un producto específico se resuelve de forma directa y constante sin iterar.
    
- [ ] b) Desvincular Redux y delegar toda la carga iterativa al Virtual DOM mediante el hook nativo `useSelector`, aprovechando el recolector de basura del navegador.
    
- [ ] c) Implementar llamadas recurrentes a `appFetch` para que el Backend filtre activamente los Array empleando memoria de sesión.
    
- [ ] d) Todas las anteriores.
    

> [!success]- **Solución y Justificación**
> 
> **Opción correcta: a) Transmutar la matriz plana por un diccionario asociativo indexado por claves (objeto byId), donde el acceso y modificación de un producto específico se resuelve de forma directa y constante sin iterar.**
> 
> **Justificación (Ref. Tema 6 - "Estado Normalizado"):** Navegar arrays mediante `find()` o reescribir con `map()` arrastra un coste lineal $O(n)$ degradando sistemas masivos. La "Normalización de Estado" soluciona esto hospedando la estructura en diccionarios. Consultar o mutar `state.byId` cuesta $O(1)$ (tiempo constante y predecible).

##### 5.

En la configuración de nuestro entorno para pruebas automatizadas (`spring-test`), empleamos la anotación `@ActiveProfiles("test")` para aislar las operaciones en la base de datos `patest`. Atendiendo a la jerarquía YAML, ¿cómo orquesta Spring Boot la resolución de parámetros cuando conviven `application.yml` y `application-test.yml`?

- [ ] a) Spring Boot ignora y repudia por completo el fichero base `application.yml`, obligando al desarrollador a reescribir desde cero todas las propiedades monolíticas en el archivo derivado.
    
- [ ] b) El framework desactiva temporalmente el control transaccional de JDBC, permitiendo operar en la RAM interna sin afectar a los esquemas físicos.
    
- [ ] c) Todas las anteriores.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Solución y Justificación**
> 
> **Opción correcta: d) Ninguna de las anteriores.**
> 
> **Justificación (Ref. Tema 3 - "Pruebas Automatizadas - Configuración"):** Ambas opciones a y b son falsas. La trampa habitual es pensar que los perfiles actúan con exclusión total. La realidad es que el `application.yml` matriz sigue siendo la zapata fundacional. El fichero `application-test.yml` únicamente fusiona (solapando o sobreescribiendo) aquellas llaves explícitamente declaradas (como la redirección URL o credenciales aisladas), protegiendo la herencia del resto del esquema base.

##### 6.

Analice con visión forense el siguiente fragmento reactivo diseñado para montar la pantalla de Detalles del Pedido:


```javascript
const OrderDetails = () => {
    const { id } = useParams();
    const dispatch = useDispatch();

    useEffect(() => {
        dispatch(actions.findOrder(id));

        return () => dispatch(actions.clearOrder());
    }, [id]);

    // ... renderizado ...
}
```

Atendiendo al ciclo de vida del componente, determine la verdadera finalidad de la función devuelta (`return () => ...`) dentro del Hook:

- [ ] a) Es una cláusula pasiva inútil; el recolector de basura nativo (Garbage Collector) ignora los retornos de `useEffect`.
    
- [ ] b) Constituye la función de limpieza (Clean-up). Se ejecuta forzosamente justo antes de desmontar el componente para purgar el pedido del estado global, conjurando fugas de memoria y evitando que usuarios posteriores visualicen datos espectrales.
    
- [ ] c) Desencadena de forma asíncrona un bucle infinito al intentar modificar el `id` cuando el componente ya está cerrado.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Solución y Justificación**
> 
> **Opción correcta: b) Constituye la función de limpieza (Clean-up). Se ejecuta forzosamente justo antes de desmontar el componente para purgar el pedido del estado global, conjurando fugas de memoria y evitando que usuarios posteriores visualicen datos espectrales.**
> 
> **Justificación (Ref. Tema 7 - "Clean-up"):** Sin la acción expurgadora devuelta por el interior del `useEffect`, abandonar una vista dinámica deja "rastros fantasmas" en el estado. Si un usuario inspeccionase otro elemento o cerrase sesión, la vista retendría la basura anterior colapsando visualmente y desperdiciando recursos locales.

##### 7.

Cuando un controlador expuesto como `@RestController` recibe un JSON que incumple las normativas paramétricas (por ejemplo, un código postal de 50 caracteres interceptado por `@Validated`), la capa Lógica se protege abortando la inyección. ¿Cómo se orquesta globalmente la captura de este rechazo sintáctico para rebotar al Frontend un informe inteligible?

- [ ] a) Se invoca programáticamente a `exception.getBindingResult().getFieldErrors()` dentro de la clase transversal `@ControllerAdvice` para extraer un listado limpio de los fallos, permitiendo su internacionalización (i18n).
    
- [ ] b) El Backend inyecta el stacktrace completo dentro de la cabecera `Accept-Language` y fuerza un recargo F5 pasivo.
    
- [ ] c) Spring delega mecánicamente el error al estado global Redux del usuario sin transpilación previa.
    
- [ ] d) Todas las anteriores.
    

> [!success]- **Solución y Justificación**
> 
> **Opción correcta: a) Se invoca programáticamente a exception.getBindingResult().getFieldErrors() dentro de la clase transversal @ControllerAdvice para extraer un listado limpio de los fallos, permitiendo su internacionalización (i18n).**
> 
> **Justificación (Ref. Tema 4 - "Gestión de excepciones - Ejemplo 2"):** Cuando un DTO viola parámetros como `@Size`, arroja nativamente `MethodArgumentNotValidException`. No queremos devolverle a React un "stacktrace" ilegible. Mediante la centralización `@ControllerAdvice`, atrapamos el fallo, ejecutamos la API de `BindingResult` para listar los atributos profanados y los devolvemos transmutados vía `MessageSource` usando la bandera idiomática del explorador.

##### 8.

En su intento de optimizar la persistencia, un programador redacta la siguiente firma dentro del componente `UserDao` utilizando el lenguaje declarativo JPQL:

```java
public interface UserDao extends CrudRepository<User, Long> {

    @Query("SELECT u FROM users_table u WHERE u.first_name = ?1")
    Optional<User> findByFirstName(String firstName);

}
```

Bajo los cánones dogmáticos que rigen la especificación JPA, pronostique la viabilidad de este código:

- [ ] a) El segmento funcionará espléndidamente, ya que JPQL permite mapear directamente tablas físicas en arquitecturas de alto rendimiento.
    
- [ ] b) Provocará un fallo sistémico irreparable: JPQL interroga exclusivamente a las Clases Java y sus atributos (objetos). Referenciar directamente al nombre de la tabla SQL (`users_table`) o columnas nativas (`first_name`) es un error estructural puro.
    
- [ ] c) Fallará porque se omitió la inyección paramétrica de `Pageable` para fraccionar los resultados, colapsando la RAM del servidor Fat JAR.
    
- [ ] d) Todas las anteriores.
    

> [!success]- **Solución y Justificación**
> 
> **Opción correcta: b) Provocará un fallo sistémico irreparable: JPQL interroga exclusivamente a las Clases Java y sus atributos (objetos). Referenciar directamente al nombre de la tabla SQL (users_table) o columnas nativas (first_name) es un error estructural puro.**
> 
> **Justificación (Ref. Tema 2 - "Desarrollo de DAOs - JPQL"):** Como se indica en los apuntes técnicos, JPQL NO es SQL, a pesar de su mimetismo sintáctico. JPQL está atado y enraizado estrictamente al modelo orientado a objetos. Debes seleccionar sobre las Clases (ej. `FROM User u`) y Hibernate asume la labor criptográfica de traducirlo al dialecto y tablas físicas instaladas bajo el driver JDBC.

##### 9.

En la representación gráfica mediante componentes React, cuando precisamos volcar secuencialmente y de forma iterativa el contenido de un Array mediante la función nativa `.map()`, la arquitectura nos impone adherir dogmáticamente el atributo `key={...}` al elemento raíz de cada iteración. ¿Cuál es el sustrato científico que justifica esta obligación?

- [ ] a) Dota al algoritmo de cálculo topológico ("Diffing") de identificadores fijos inequívocos.
    
- [ ] b) Previene que el motor se ahogue y penalice la CPU teniendo que deducir o recrear celdilla a celdilla toda la lista al insertar o mutilar un registro intermedio.
    
- [ ] c) Mitiga y neutraliza las advertencias paralizantes emitidas en la consola de depuración del navegador.
    
- [ ] d) Todas las anteriores.
    

> [!success]- **Solución y Justificación**
> 
> **Opción correcta: d) Todas las anteriores.**
> 
> **Justificación (Ref. Tema 5 - "Propiedad key" y apuntes extra):** La directriz `key` constituye la argamasa que sostiene la velocidad de React en iteraciones. Omitirla induce a que el motor "Diffing" no sepa discriminar qué parte de la matriz ha cambiado, obligándole estúpidamente a destruir y repintar la franja completa para evitar desincronizaciones ("ahogo computacional"), lo cual deriva en múltiples notificaciones coloradas de advertencia por la consola.

##### 10.

Usted codifica una prueba automatizada usando `spring-test` (`@SpringBootTest` y `@Transactional`). En la misma función de prueba, guarda un usuario `User` e inmediatamente después lo recupera de la base de datos para compararlos utilizando la aserción canónica `assertEquals(user1, user2)`. Teniendo en cuenta que jamás se han sobrescrito los métodos `equals()` ni `hashCode()` en la entidad, ¿por qué el test supera la prueba con un rotundo éxito?

- [ ] a) Porque el entorno inyecta polimorfismo superficial anulando las firmas de la entidad original durante los perfiles activos.
    
- [ ] b) Porque al transitar bajo una única transacción viva, el motor ORM consulta su Caché de Primer Nivel (L1) y sirve la réplica exacta. Ambos objetos convergen en el mismo puntero físico de la memoria RAM, haciendo que el comparador biológico estricto de Java (`==`) dictamine una coincidencia perfecta.
    
- [ ] c) Porque JUnit 5 evade las comparaciones de atributos relacionales en entidades LAZY.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Solución y Justificación**
> 
> **Opción correcta: b) Porque al transitar bajo una única transacción viva, el motor ORM consulta su Caché de Primer Nivel (L1) y sirve la réplica exacta. Ambos objetos convergen en el mismo puntero físico...**
> 
> **Justificación (Ref. Tema 3 - "Pruebas automatizadas - equals/hashCode"):** En la metodología de pruebas inyectamos `@Transactional`. Durante ese ciclo estanco y aislado, Hibernate hospeda los datos volcados en un búfer o "Caché de Primer Nivel". Al invocar subsiguientemente la búsqueda mediante `DAO.findById`, no se dispara la lectura a MySQL; la caché escupe de vuelta la instancia idéntica, la mismísima zona en memoria RAM. Es por ello que igualdades superficiales `==` y aserciones directas otorgan validez rotunda sin recurrir a sobrescribir la arquitectura con `equals()`.