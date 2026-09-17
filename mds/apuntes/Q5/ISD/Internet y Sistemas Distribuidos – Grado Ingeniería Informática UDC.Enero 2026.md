
### Pregunta 1

Suponga una aplicación instalada siguiendo una arquitectura en 4 capas (capa 1: máquina con el navegador; capa 2: máquina con un servidor en el que está instalada una aplicación web, internamente estructurada en una capa Interfaz Web de Usuario y una capa Acceso a Servicios, implementadas ambas con tecnologías .NET; capa 3: máquina con un servidor de aplicaciones en el que está instalado un servicio web, internamente estructurado en una capa Servicios y una capa Modelo, implementadas ambas con tecnologías Java; capa 4: máquina con la base de datos). Indicar cuál de las siguientes afirmaciones es correcta:

- [ ] a) No es posible que el software instalado en las capas 2 y 3 esté implementado con diferentes tecnologías, por tanto, la arquitectura descrita no es válida.
    
- [ ] b) Para optimizar la arquitectura, se podría instalar y ejecutar la capa Interfaz Web de Usuario en el servidor de aplicaciones de la capa 3, donde se ejecuta la capa Modelo, haciendo innecesarias las capas Servicios y Acceso a Servicios.
    
- [ ] c) Si se cambia la base de datos instalada en la capa 4, habría que realizar las modificaciones pertinentes en el código y reinstalar el software de las capas 2 y 3.
    
- [x] d) Ninguna de las anteriores.

### Pregunta 2

Indique qué APIs o frameworks se han empleado en la asignatura para el desarrollo de la capa Servicios:

- [x] a) Servlets y Apache Thrift.
    
- [ ] b) JDBC y HTTPClient.
    
- [ ] c) JDBC y Servlets.
    
- [ ] d) Apache Thrift y HTTPClient.

### Pregunta 3

Indique qué afirmación relativa a la capa Modelo de los ejemplos de la asignatura y de su práctica es correcta:

- [x] a) Para su compilación requiere un driver JDBC específico a MySQL.
    
- [ ] b) Para su ejecución requiere un driver JDBC específico a MySQL.
    
- [ ] c) Todas las anteriores.
    
- [ ] d) Ninguna de las anteriores.

### Pregunta 4

Considere las dos siguientes estrategias de implementación con respecto a los métodos de los servicios de la capa Modelo. La capa Modelo está instalada dentro de un servidor de aplicaciones y es invocada por una capa Servicios REST. En la estrategia 2, la variable `dataSource` hace referencia a una instancia de una clase proporcionada por el servidor de aplicaciones que implementa la interfaz `DataSource` y utiliza la estrategia pool de conexiones. Indique la respuesta correcta.

**Estrategia 1**
```java
public void <<método>> () {
    try (Connection connection = DriverManager.getConnection(url, user, password)) {
        << Implementar lógica de negocio usando "connection". >>
    } catch (SQLException e) {
        throw new RuntimeException(e);
    }
}
```

**Estrategia 2**
```java
public void <<método>> () {
    try (Connection connection = dataSource.getConnection()) {
        << Implementar lógica de negocio usando "connection". >>
    } catch (SQLException e) {
        throw new RuntimeException(e);
    }
}
```

- [ ] a) La estrategia 1 conduce a un tiempo menor de ejecución.
    
- [x] b) La estrategia 2 conduce a un tiempo menor de ejecución.
    
- [ ] c) El método `getConnection` del `dataSource` (estrategia 2) lanzará siempre una excepción si no queda ninguna conexión libre en el pool.
    
- [ ] d) La b) y la c) son correctas.

### Pregunta 5

Analice el siguiente fragmento de código e indique la afirmación correcta:
```java
try {
    connection = dataSource.getConnection();
    connection.setAutoCommit(false); // (1)
    
    Product product = productDao.find(connection, productId);
    product.setStock(product.getStock() + increment);
    productDao.update(connection, product);
    
    connection.commit();
} catch (Exception e) {
    connection.rollback(); // (2)
}
```

- [ ] a) La línea (1) evita problemas de concurrencia con otras transacciones.
    
- [ ] b) La línea (2) garantiza que todas las sentencias SQL se ejecutarán dentro de la misma transacción.
    
- [ ] c) Todas las anteriores.
    
- [x] d) Ninguna de las anteriores.

### Pregunta 6

Indique la afirmación correcta de acuerdo al enfoque de desarrollo estudiado en la asignatura:

- [ ] a) Las operaciones de los DAOs de su práctica reciben la conexión para poder agrupar de manera sencilla varias operaciones de un mismo o distintos DAOs en una única transacción.
    
- [ ] b) El uso de DAOs simplifica la implementación de los métodos de los servicios de la capa Modelo.
    
- [x] c) Todas las anteriores.
    
- [ ] d) Ninguna de las anteriores.

### Pregunta 7

Se está diseñando una aplicación bancaria que incluye, entre otros, un caso de uso para realizar una transferencia entre dos cuentas (no se permite la transferencia si la cuenta origen no tiene suficiente saldo). La interfaz gráfica incluye un formulario en el que el usuario tiene que introducir el identificador de la cuenta origen (Long), el identificador de la cuenta destino (Long) y la cantidad de dinero a transferir (BigDecimal). Analice el DAO de la entidad Account (cuenta) que figura a continuación e indique la respuesta correcta en base al enfoque de desarrollo estudiado en la asignatura:

```java
public interface SqlAccountDao {
    public Account find(Connection connection, Long accountId)
        throws InstanceNotFoundException;
    public void update(Connection connection, Account account)
        throws InstanceNotFoundException;
    public void transfer(Long sourceAccountId, Long targetAccountId,
        BigDecimal amount);
}
```

- [ ] a) La operación `transfer` del DAO debe implementarse en términos de `find` (para recuperar la cuenta origen y la cuenta destino) y `update` (para minorar el balance de la cuenta origen y aumentar el balance de la cuenta destino).
    
- [ ] b) En la operación `transfer` del DAO falta el parámetro `Connection`, así como especificar excepciones para el caso en el que la cuenta origen no tenga suficiente saldo o que alguna cuenta no exista.
    
- [ ] c) Todas las anteriores.
    
- [x] d) Ninguna de las anteriores.

### Pregunta 8

¿Qué puede decir con respecto a este código?
```java
public ... buyMovie(Long movieId, ...) throws ... {
    ...
    try (Connection connection = ...) {
        ...
        Movie movie = movieDao.find(connection, movieId);
        Sale sale = saleDao.create(connection, new Sale(...));
        ...
    } catch (...) {
        ...
    }
}
```

- [x] a) Corresponde a la capa Lógica de Negocio.
    
- [ ] b) Corresponde a la capa Acceso a Datos.
    
- [ ] c) Corresponde a la capa Servicios Thrift.
    
- [ ] d) Corresponde a la capa Acceso a Servicios.

### Pregunta 9

En base al enfoque aconsejado en la asignatura para la realización de pruebas de integración, indique la afirmación correcta:

- [ ] a) Durante la ejecución de las pruebas se utiliza el `DataSource` proporcionado por Jetty, al que se accede por JNDI.
    
- [ ] b) Durante la ejecución de las pruebas se utiliza el `DataSource` proporcionado por Tomcat, al que se accede por JNDI.
    
- [ ] c) Durante la ejecución de las pruebas es posible utilizar el `DataSource` proporcionado por Jetty o por Tomcat, a los que se accede por JNDI, dependiendo del valor de una propiedad del fichero de configuración `ConfigurationParameters.properties` presente en `src/test/resources`.
    
- [x] d) Ninguna de las anteriores.

### Pregunta 10

Dado el siguiente fragmento de código correspondiente a un método de una clase de pruebas de integración de la capa Modelo, implementada con JUnit 5, indique qué afirmación es correcta:
```java
@Test
public void testRemoveElement() throws InputValidationException, InstanceNotFoundException {
    // Fragmento de código 1
    ...
    assertThrows(ElementNotRemovableException.class, () -> {
        // Fragmento de código 2
        ...
    });
    // Fragmento de código 3
    ...
}
```

- [x] a) Se corresponde con un test que se ejecutará correctamente si durante la ejecución del fragmento de código 2 se lanza la excepción `ElementNotRemovableException` y NO es capturada por el código de ese fragmento.
    
- [ ] b) Se corresponde con un test que se ejecutará correctamente si durante su ejecución se lanza cualquiera de las excepciones declaradas en su cláusula `throws` y NO es capturada por el código del método.
    
- [ ] c) Todas las anteriores.
    
- [ ] d) Ninguna de las anteriores.

### Pregunta 13

Asumiendo las convenciones de nombrado utilizadas en la asignatura, ¿qué puede decir con respecto al método `toClientMovieDto`?
```java
private static ClientMovieDto toClientMovieDto(JsonNode movieNode)
    throws ParsingException {
    if (movieNode.getNodeType() != JsonNodeType.OBJECT) {
        throw new ParsingException("Unrecognized JSON (object expected)");
    } else {
        ObjectNode movieObject = (ObjectNode) movieNode;
        JsonNode movieIdNode = movieObject.get("movieId");
        Long movieId = (movieIdNode != null) ? movieIdNode.longValue() : null;
        ...
        return new ClientMovieDto(movieId, ...);
    }
}
```

- [ ] a) Convierte un DTO (Data Transfer Object) utilizado en la capa Servicios, a un objeto de la capa Modelo.
    
- [x] b) Convierte un árbol Jackson (recibe su nodo raíz) a un DTO utilizado en la capa Acceso a Servicios.
    
- [ ] c) Convierte un DTO (Data Transfer Object) utilizado en la capa Acceso a Servicios, a un árbol Jackson (devuelve el nodo raíz del árbol).
    
- [ ] d) Convierte un árbol Jackson (recibe su nodo raíz) a un DTO utilizado en la capa Modelo.

### Pregunta 14

Suponga que está diseñando un Servicio Web según el enfoque REST estudiado en la asignatura y ya existe una funcionalidad que permite dar de alta un libro en un repositorio. Suponga que ahora desea modelar una funcionalidad que permite reemplazar la representación de un libro en el repositorio. ¿Qué opción escogería?

- [ ] a) El servicio permitirá reemplazar la representación de un libro invocando el URL del recurso individual libro (e.g. `http://www.servicename.com/books/123`) con el método POST e incluyendo los nuevos datos del libro en un documento JSON incluido en el cuerpo de la petición.
    
- [ ] b) El servicio permitirá reemplazar la representación de un libro invocando el URL del recurso colección libros (e.g. `http://www.servicename.com/books/`) con el método POST e incluyendo el identificador y los nuevos datos del libro en un documento JSON incluido en el cuerpo de la petición.
    
- [x] c) El servicio permitirá reemplazar la representación de un libro invocando el URL del recurso individual libro (e.g. `http://www.servicename.com/books/123`) con el método PUT e incluyendo los nuevos datos del libro en un documento JSON incluido en el cuerpo de la petición.
    
- [ ] d) El servicio permitirá reemplazar la representación de un libro invocando el URL del recurso colección libros (e.g. `http://www.servicename.com/books/`) con el método PUT e incluyendo el identificador y los nuevos datos del libro en un documento JSON incluido en el cuerpo de la petición.

### Pregunta 15

Suponga que está diseñando un Servicio Web según el enfoque REST. Teniendo en cuenta las convenciones seguidas en la asignatura, ¿qué opción le parece más adecuada para la respuesta a una petición que falle debido a que la base de datos no está accesible en ese momento?

- [ ] a) En la respuesta HTTP se indicará el código de respuesta `200 OK` para indicar que el servidor entendió correctamente la petición y que el fallo es por causas ajenas a él.
    
- [ ] b) En la respuesta HTTP se indicará el código de respuesta `400 Bad Request` para indicar que la petición es incorrecta.
    
- [x] c) En la respuesta HTTP se indicará el código de respuesta `500 Internal Error` para indicar que la petición falló debido a un error interno.
    
- [ ] d) En la respuesta HTTP se indicará el código `404 Not Found` para indicar que no se encontró la base de datos.

### Pregunta 16

En el contexto de Servicios Web REST, suponga un intermediario genérico capaz de reintentar peticiones a servicios web REST que han devuelto códigos de respuesta de error. Considerando las convenciones vistas en la asignatura y que 500 es un error temporal, diga qué afirmación es correcta:

- [x] a) El intermediario NO reintentará una petición `POST http://www.servicename.com/books/1234` que ha devuelto el código de respuesta `500 Internal Error`.
    
- [ ] b) El intermediario NO reintentará una petición `GET http://www.servicename.com/books/1234` que ha devuelto el código de respuesta `500 Internal Error`.
    
- [ ] c) El intermediario NO reintentará una petición `PUT http://www.servicename.com/books/1234` que ha devuelto el código de respuesta `500 Internal Error`.
    
- [ ] d) El intermediario NO reintentará una petición `DELETE http://www.servicename.com/books/1234` que ha devuelto el código de respuesta `500 Internal Error`.

### Pregunta 17

Considere el siguiente fragmento de código e indique la respuesta correcta (asuma que `validateStatusCode` es el método que se utiliza en los ejemplos de la asignatura con el mismo nombre):
```java
ClassicHttpResponse response = (ClassicHttpResponse)
    Request.delete(getEndpointAddress() + "resources/" + resourceId).
        execute().returnResponse();

validateStatusCode(HttpStatus.SC_NO_CONTENT, response);
```

- [ ] a) Es un fragmento de un método de la capa Acceso a Servicios de una aplicación cliente que realiza una petición HTTP DELETE incluyendo el identificador del recurso a eliminar en el cuerpo de la petición y espera recibir una respuesta HTTP que no devuelva ningún código de estado (`HttpStatus.SC_NO_CONTENT`).
    
- [x] b) Es un fragmento de un método de la capa Acceso a Servicios de una aplicación cliente que realiza una petición HTTP DELETE que no incluye nada en su cuerpo y espera recibir una respuesta HTTP que tampoco incluya nada en su cuerpo (`HttpStatus.SC_NO_CONTENT`).
    
- [ ] c) Es un fragmento de un Servlet de la capa Servicios REST que procesa una petición DELETE y envía un código de respuesta 204 (`HttpStatus.SC_NO_CONTENT`) para indicar que no devuelve nada en el cuerpo de la respuesta.
    
- [ ] d) Es un fragmento de un Servlet de la capa Servicios REST que procesa una petición DELETE cuyo cuerpo debe estar vacío (`HttpStatus.SC_NO_CONTENT`) para que se procese correctamente.

### Pregunta 18

Asumiendo que utilizamos la clase `es.udc.ws.util.servlet.RestHttpServletTemplate` del subproyecto de utilidades de los ejemplos de la asignatura (`ws-util`), indique la afirmación INCORRECTA:

- [ ] a) Si queremos implementar un servlet que responda a peticiones GET y POST, tendremos que crear una clase que herede de `RestHttpServletTemplate` y redefinir los métodos `processGet` y `processPost`.
    
- [ ] b) Los servlets que heredan de `RestHttpServletTemplate` no tienen que preocuparse de tratar las excepciones del módulo `ws-util` (`InstanceNotFoundException`, `InputValidationException` y `ParsingException`) al procesar cualquier petición.
    
- [x] c) No hay que declarar en el fichero `web.xml` los servlets que heredan de `RestHttpServletTemplate`, puesto que ya está declarada su superclase.
    
- [ ] d) Si un servlet hereda de `RestHttpServletTemplate` y no se desea que procese peticiones DELETE, no es necesario redefinir el método `processDelete`, puesto que la implementación por defecto de `processDelete` en `RestHttpServletTemplate` devuelve un código de respuesta indicando que esa operación no está implementada.

### Pregunta 19

En el modelo de programación RPC (Remote Procedure Call), indique cuál de las siguientes afirmaciones es correcta:

- [ ] a) El programador de la aplicación servidora modela su funcionalidad a través de un conjunto de operaciones estándar (operaciones que no son ad hoc).
    
- [ ] b) Las aplicaciones cliente y servidora tienen que escribirse en el mismo lenguaje de programación.
    
- [ ] c) En cuanto a rendimiento, la invocación de una operación remota es similar a la invocación de un método de una librería local.
    
- [x] d) Cambios en la implementación del servidor no obligan a regenerar el stub si no cambia nada en la interfaz del servicio.

### Pregunta 20

Considere el siguiente fichero de definición de Apache Thrift, en el que se pretende declarar un servicio con una operación, e indique la afirmación correcta:
```thrift
namespace java es.udc.ws.movies.thrift

struct ThriftMovieDto {
    1: i64 movieId
    2: string title
}

struct ThriftInputValidationException {
    1: string message
}

ThriftMovieDto addMovie(1: ThriftMovieDto movieDto)
    throws (1: ThriftInputValidationException e)
```

- [ ] a) La operación `addMovie` debe definirse dentro de un servicio (usando la palabra reservada `service`).
    
- [ ] b) El parámetro de la operación `addMovie` no puede ser de tipo `ThriftMovieDto`.
    
- [ ] c) El tipo `ThriftInputValidationException` debe definirse con la palabra reservada `exception` (en lugar de `struct`).
    
- [x] d) La a) y la c) son correctas.
