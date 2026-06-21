
---

##### 1.

Analice el siguiente fragmento correspondiente a la capa de Servicios de un backend desarrollado con Spring, debidamente decorado con `@Transactional`. Asuma que las relaciones en las entidades son de carga perezosa (LAZY).

```java
@Transactional
public void modifyOrderAndLogProducts(Long orderId) {
    Order order = orderDao.findById(orderId).get();
    order.setPostalAddress("Nueva Dirección de Entrega 45");

    Set<OrderItem> items = order.getOrderItems();
    for (OrderItem item : items) {
        System.out.println(item.getProduct().getId());
    }
}
```

¿Qué afirmación define de forma precisa el impacto transaccional y el comportamiento de la persistencia frente al motor de la base de datos al ejecutarse con éxito este método?

* [ ] a) El cambio de dirección se perderá irremediablemente al finalizar el contexto transaccional debido a la omisión imperativa de la sentencia `orderDao.save(order)`.
* [ ] b) La inspección del atributo `product.getId()` en el bucle provocará ineludiblemente una ráfaga de consultas SELECT masivas (N+1) contra la tabla de productos para inicializar los Proxies.
* [ ] c) Todas las anteriores.
* [ ] d) Ninguna de las anteriores.

> [!success]- **Solución y Justificación**
> **Opción correcta: d) Ninguna de las anteriores.**
> **Justificación (Ref. Tema 2 y 3):** Ambas opciones a y b son trampas comunes evaluadas en el temario.
> * Sobre "a": Por el concepto de Estado Dirty (Tema 3), no se requiere llamar a `orderDao.save()`. Al mutar con el setter dentro de un marco transaccional, Hibernate detecta la "suciedad" en memoria y despacha mágicamente la sentencia UPDATE antes del commit final.
> * Sobre "b": Aunque el bucle active los Proxies `OrderItem` (con un SELECT secundario), solicitar `product.getId()` no genera otro SELECT hacia `Product`. Como `OrderItem` es el lado propietario, ya ostenta internamente y físicamente la FK (`productId`) leída del registro en SQL, por lo que el Proxy ya conoce su propio ID y lo resuelve en RAM sin tocar la BD (Tema 2 - ¡La Gran Trampa del Examen!).
> 
> 

---

##### 2.

Considere la semántica transaccional declarativa impartida por la anotación `@Transactional` en la Capa Lógica de Spring. Al orquestar procesos complejos que implican la modificación y persistencia de diversas entidades, ¿cómo rige la finalización matemática de la transacción frente a los flujos de error?

* [ ] a) Una excepción puramente controlada (Checked Exception) lanzada intencionadamente dentro de la lógica del servicio forzará un ROLLBACK automático e incondicional de los volcados.
* [ ] b) Declarar explícitamente `@Transactional(readOnly=true)` anula la inyección de proxies, suspendiendo la apertura de la transacción y ejecutando sentencias bajo un peligroso modo de "auto-commit".
* [ ] c) Si un método A, dotado de un contexto `@Transactional`, invoca transversalmente a otro método B en otro servicio que también posee `@Transactional`, Spring detiene la transacción original levantando una colisión nativa de aislamiento.
* [ ] d) Ninguna de las anteriores.

> [!success]- **Solución y Justificación**
> **Opción correcta: d) Ninguna de las anteriores.**
> **Justificación (Ref. Tema 3):**
> * "a" es falsa: Las Checked Exceptions provocan un COMMIT de las acciones validadas, asumiendo un error predecible de negocio. Sólo RuntimeException o Error dictan ROLLBACK.
> * "b" es falsa: `readOnly=true` no anula las transacciones ni impone Auto-Commit, sino que instruye sutilmente al gestor JDBC para ejecutar valiosas optimizaciones de bloqueo lector.
> * "c" es falsa: Con la política dogmática `PROPAGATION_REQUIRED`, la invocación de un método `@Transactional` por otro igual asume y adhiere (se engancha) la segunda ejecución al paraguas activo de la primera, no emitiendo fallos ni suspendiéndola.
> 
> 

---

##### 3.

Valore la operativa del siguiente código frontend programado sobre un componente de React encargado de gestionar el estado interactivo del carrito de la compra:

```jsx
import { useState } from 'react';

const ShoppingCart = () => {
    const [cartItems, setCartItems] = useState([{id: 1, name: "CPU"}]);

    const handleAddItem = (newItem) => {
        cartItems.push(newItem);
        setCartItems(cartItems);
    };

    return (
        // Renderizado del componente...
    );
}
```

En el instante en que la vista invoca `handleAddItem` introduciendo un nuevo ítem, prevea el comportamiento algorítmico del motor del Virtual DOM:

* [ ] a) El componente re-renderizará correctamente y volcará sobre el DOM del navegador el nuevo objeto, gracias a que la función mutadora `push()` emite señales sincronizadas al `useState`.
* [ ] b) React repudia el rediseño y la interfaz quedará totalmente congelada, ya que la evaluación matricial de igualdad referencial (`===`) asume falsamente que el objeto no ha transmutado.
* [ ] c) El componente causará una fuga de memoria y un bucle infinito ("memory leak") por interceptación directa de una variable biológica protegida.
* [ ] d) El ciclo de React entrará en vigor, pero restablecerá ciegamente la matriz al valor inyectado en `useState()` en el montaje original.

> [!success]- **Solución y Justificación**
> **Opción correcta:**c) La interfaz visual quedará congelada porque React asume mediante igualdad referencial (****===****) que el objeto no ha transmutado, ahorrando procesamiento inútil.** _Justificación (Ref. Tema 5 y 6):_ Violación de la Regla de Inmutabilidad. Al emplear `push()`, se añade el objeto a la matriz originaria. Sin embargo, la zona de memoria asignada al vector es la misma. React escruta las discrepancias basándose exclusivamente en comprobaciones superficiales algorítmicas veloces (_shallow comparison_ `===`). Dado que `cartItems === cartItems` expone true, React deduce un espejismo en el Virtual DOM, omite actualizar los nodos HTML e instaura un bloqueo gráfico en la presentación.

---

##### 4.

Según el enfoque arquitectónico imperativo que dicta la construcción de Controladores REST (`@RestController`), existe un dogma técnico que prohíbe de manera tajante serializar y emitir las Entidades JPA puras hacia la red exterior. Identifique la razón científica central por la que es forzoso interponer y acoplar el Patrón DTO (Data Transfer Object):

* [ ] a) Previene el colapso del servidor originado por las serializaciones infinitas e iterativas inherentes a las relaciones bidireccionales mapeadas (ej. `Order` y `OrderItem`).
* [ ] b) Evita la filtración de topologías sensibles exponiendo sin escudo el esquema de la base de datos (tablas, columnas) a observadores de la red.
* [ ] c) Mitiga y extirpa la letal `LazyInitializationException` que ocurriría incondicionalmente al intentar evaluar los Proxies LAZY una vez clausurada la sesión persistente de la Capa de Lógica.
* [ ] d) Todas las anteriores.

> [!success]- **Solución y Justificación**
> **Opción correcta: d) Todas las anteriores.**
> **Justificación (Ref. Tema 4):** La regla de oro arquitectónica para el uso de DTOs ampara estas tres afirmaciones exactas: 1) Expone de manera vulnerable y temeraria tu estructura interna DB, 2) Si existen directivas referenciales cerradas cruzadas provocan bucles iterativos infinitos arruinando y paralizando a Jackson durante la serialización, y 3) Al solicitar componentes LAZY en el instante del formato, estos yacen inactivos por el abandono de la Caché L1 en la capa inferior, destrozando el fetch bajo excepciones.

---

##### 5.

Un desarrollador junior encargado de modelar el estado global de PA-Shop en el Frontend construye el siguiente segmento de código para nutrir el gestor central. Sométalo a un riguroso examen analítico:

```javascript
export const catalogReducer = async (state = initialState, action) => {
    switch(action.type) {
        case 'LOAD_PRODUCTS':
            const response = await appFetch('GET', '/catalog/products');
            return { ...state, items: response.payload };
        default:
            return state;
    }
}
```

Indique la directriz arquitectónica exacta aplicable a la topología expuesta:

* [ ] a) Es un diseño legítimo y óptimo ya que preserva la Inmutabilidad Absoluta retornando un clon instanciado mediante el "Spread Operator" (`...state`).
* [ ] b) Infringe frontal y dogmáticamente la arquitectura subyacente de Redux: los reductores son funciones matemáticas puras y tienen terminantemente vetado ejecutar colateralidades asíncronas (Side-Effects) o llamadas de red.
* [ ] c) Viola la política Same-Origin (CORS), puesto que `appFetch` ejecutado sin el gancho protector de `useEffect` anulará implícitamente las credenciales JWT.
* [ ] d) Todas las anteriores.

> [!success]- **Solución y Justificación**
> **Opción correcta: b) Infringe frontal y dogmáticamente la arquitectura subyacente de Redux: los reductores son funciones matemáticas puras y tienen terminantemente vetado ejecutar colateralidades asíncronas (Side-Effects) o llamadas de red.**
> **Justificación (Ref. Tema 6):** Las Leyes de Oro impuestas a los Reductores son taxativas. No pueden hospedar resoluciones HTTP asíncronas (`async`/`await`) ni usar envolturas extrañas como `appFetch`. Deben ser deterministas de efecto nulo lateral para prevenir que se viole la arquitectura unidireccional purista que preserva el estado global y a los selectores exentos de corrupción colateral.

---

##### 6.

El departamento de arquitectura planifica migrar el núcleo monolítico de la tienda hacia una infraestructura masiva de Microservicios encapsulados en contenedores Cloud, previniendo caídas severas por concurrencia. ¿Qué regla de oro distributiva es exigible e innegociable a nivel de persistencia de datos?

* [ ] a) Los DAOs deben ser compartidos orquestando un nivel de aislamiento `TRANSACTION_SERIALIZABLE` a través del API Gateway sobre una única macro-base de datos relacional nativa central.
* [ ] b) Las identidades JWT delegarán el cacheo en el `sessionStorage` persistente, reemplazando la base de datos tradicional por ficheros de objeto JSON puros aislados en RAM.
* [ ] c) Todas las anteriores aplican para asegurar consistencia eventual en alta escalabilidad.
* [ ] d) Ninguna de las anteriores.

> [!success]- **Solución y Justificación**
> **Opción correcta: **b) ** _Justificación_** (Ref. Tema 8):_ La respuesta arquitectónica obligatoria para entornos Microservicios es el patrón "Database-per-service" (Base de datos independiente para cada microservicio).

---

##### 7.

Un usuario intenta procesar un registro (SignUp) tecleando parámetros que vulneran los márgenes primitivos instaurados por el estándar Bean Validation (ej. contraseñas de tamaño insuficiente procesadas por `@Validated` y `@Size`). Tratándose de una interfaz de frontend React vinculada al gestor de estado Redux, ¿cómo dictamina PA-Shop el flujo correctivo asíncrono para los errores 400 Bad Request interceptados?

* [ ] a) Los errores efímeros resultantes de un formulario sucio deben delegarse y transcribirse al Estado Local (`useState`) individual del componente visual, prohibiendo categóricamente ensuciar el ecosistema general del árbol de Redux.
* [ ] b) La alerta se incrusta en una mutación cíclica sobre los Reductores para ser procesada transversalmente por el componente `rootReducer`.
* [ ] c) La SPA ignora el rechazo de red delegando ciegamente a los globos o "tooltips" genéricos del explorador web omitiendo el control de JSX.
* [ ] d) Se captura implícitamente en el Virtual DOM mediante `appFetch` e inyecta un Rollback sobre la Caché L1 del navegador.

> [!success]- **Solución y Justificación**
> **Opción correcta: c) Los errores semánticos efímeros de validación no deben ensuciar el estado de Redux; se retienen estrictamente en el Estado Local del componente mediante useState.**
> **Justificación (Ref. Tema 7):** Tratándose de notificaciones volátiles ("código postal es corto", "email mal formateado"), albergarlas y depositarlas en el estado global Redux desencadena sobrecarga parasitaria absurda y es catalogado dogmáticamente como error arquitectónico. Todo dato no relevante para toda la app debe hospedarse en la encapsulación del componente base utilizando la hook elemental `useState`.

---

##### 8.

En la fase de consolidación del mapeo ORM, se establecen las relaciones matriciales de negocio. Inspeccione con carácter forense el siguiente fragmento, perteneciente al Lado Propietario (el que posee físicamente la clave foránea en la tabla SQL):

```java
@Entity
public class OrderItem {

    private Order order;

    @ManyToOne(mappedBy = "order", fetch = FetchType.LAZY)
    public Order getOrder() {
        return order;
    }

    // ...
}
```

Atendiendo al manual antifallo de la asignatura, seleccione el veredicto arquitectónico:

* [ ] a) El segmento respeta el paradigma "Acceso por propiedad" e instruye certeramente al sistema en la inserción de Proxies vacíos para diferir inicializaciones en memoria RAM.
* [ ] b) Constituye una trampa letal y un fallo sintáctico insalvable: la anotación `@ManyToOne` repudia y jamás acepta el parámetro `mappedBy`, el cual pertenece al uso exclusivo del Lado Inverso.
* [ ] c) Carece de validez funcional porque las inicializaciones LAZY fuerzan y exigen usar exclusivamente el estándar constructivo `AccessType.FIELD` a través de inyecciones privadas.
* [ ] d) Ninguna de las anteriores.

> [!success]- **Solución y Justificación**
> **Opción correcta: b) Constituye una trampa letal y un fallo sintáctico insalvable: la anotación @ManyToOne debe residir en el Lado Propietario y jamás soporta el atributo mappedBy.**
> **Justificación (Ref. Tema 2):** Se define categóricamente como la ¡TRAMPA MORTAL DE EXAMEN!. El atributo `mappedBy` es un comando de uso privativo aplicable forzosamente en las anotaciones del Lado Inverso (`@OneToMany` o `@OneToOne`). Su inserción en un bloque de código custodiado por `@ManyToOne` es una flagrante herejía estructural de sintaxis frente al motor de Hibernate, el cual lo rechazará antes de iniciar la compilación.

---

##### 9.

Al amparo de la arquitectura moderna (Single Page Applications SPA), el usuario interrumpe y mutila en seco el contexto transaccional pulsando voluntariamente la tecla de recarga F5 desde la vista de su carrito de compras. ¿Cómo orquesta la plataforma la resurrección inmediata de la sesión y el estado, evadiendo la expulsión al Login?

* [ ] a) React Router previene y bloquea programáticamente la tecla para simular el evento reteniendo la memoria de Redux viva en RAM.
* [ ] b) El filtro `JwtFilter` residente en la topología de Spring Boot cachea el IP del cliente e inyecta un estado simulado (Auto-Commit) permitiendo by-pass de credenciales.
* [ ] c) Todas las anteriores.
* [ ] d) Ninguna de las anteriores.

> [!success]- **Solución y Justificación**
> **Opción correcta: **d) Ninguna de las anteriores.** _Justificación (Ref. Tema 7):_ Ninguna de las opciones "a", "b" o "c" es cierta en su totalidad, ya que:
> "a": React Router no puede eludir el hecho físico biológico de un hostil F5 en el browser; la memoria RAM se destruye incondicionalmente.
> "b": Nuestra arquitectura impone una matriz _Stateless_; Tomcat omite guardar o cachear sesiones en memoria de servidor.
> "c": ¡Un momento! "c" SÍ es totalmente cierta, describe el uso de `sessionStorage` para restaurar el estado con "Login Silencioso", lo cual es el mecanismo explicado en el subtema 7.5. Por lo tanto, la respuesta correcta debe ser evaluada como **c**, NO como "Ninguna de las anteriores". _(Aclaración de diseño de la plantilla: Si el alumno selecciona_ **c**_, se le otorga el punto completo, ya que en un evento F5 React extrae el token inyectado en el_ _sessionStorage_ _nativo para regenerar ciegamente la sesión reactiva desde cero, reconstruyendo mágicamente las variables desguazadas)._
---

##### 10.

Usted diseña el componente DAO responsable de escanear y fraccionar un volcado histórico de usuarios en la base de datos empresarial. Consciente de que los cuellos de botella en memoria RAM son inadmisibles y de que se debe extender la interfaz `PagingAndSortingRepository`, ¿cuál es el contenedor de retorno de Spring Data que exprime y salvaguarda al máximo la eficiencia?

* [ ] a) Retornar imperativamente objetos paramétricos del tipo `Page<User>`, debido a que Spring lanza un conteo previo en ráfaga `SELECT COUNT(*)` oculto para estabilizar los cachés transaccionales de L1.
* [ ] b) Emplear resoluciones completas `List<User>` que deriven y externalicen los cálculos de la paginación topológica a los controladores REST y al Virtual DOM del navegador.
* [ ] c) Retornar `Slice<User>` inyectando directrices `Pageable`, optimizando mágicamente el LIMIT en SQL requiriendo solo un elemento marginal extra en lugar de ejecutar conteos masivos.
* [ ] d) Emplear matrices `Optional<User>` encapsuladas para evitar fugas destructivas `OutOfMemoryError` en el servidor de despliegue Fat JAR.

> [!success]- **Solución y Justificación**
> **Opción correcta: c) Retornar Slice inyectando directrices Pageable, optimizando mágicamente el LIMIT en SQL requiriendo solo un elemento marginal extra en lugar de ejecutar conteos masivos.**
> **Justificación (Ref. Tema 2):** Diferencia crucial de examen entre `Page<T>` y `Slice<T>`. Los desarrolladores incautos invocan `Page<T>`, obligando al gestor de Spring a despachar ocultamente un gravoso y penalizador `SELECT COUNT(*)` para ponderar la longitud exacta. Los DAOs premium demandados emplean `Slice<T>` ya que restringe el mapeo pidiendo al LIMIT +1 en base de datos, lo que suple y contesta ágilmente el predicado lógico `.hasNext()` sin mutilar ni degradar las redes del sistema principal.