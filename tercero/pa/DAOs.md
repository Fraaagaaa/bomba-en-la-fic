# Definición mediante interfaces

En este proyecto, los DAOs no son clases, sino **intefaces**. No es necesario escribir código para implementar los métodos de acceso a datos, ya que Spring lo hace automáticamente.

Un DAO típico en esta arquitectura (como `UserDao` o `MovieDao` extiende interfaces proporcionadas por Spring Data, principalmente:
- `ListCrudRepository<Entity, ID>`: Proporciona métodos básicos de CRUD (Crear, Leer, Actualizar, Borrar) que devuelven listas en lugar de iterables.
- `PagingAndSorting Repository<Entity, ID>`: Añade funcionalidades para recuperar datos de forma paginada y ordenada, algo vital para el rendimiento cuando se manejan catálogos de películas o historiales de compras.

# ¿Qué hace Spring?
Cuando la aplicación arranca, Spring detecta las interfaces que extienden los repositorios de Spring Data y, mediante una técnica llamada **Proxy Dinámico**, genera una implementación en tiempo de ejecución.
- **Sin Spring Data**: Tendría que crear una clase, inyectar un `Entity Manager`, abrir una transacción, escribir la consulta JPQL, ejecutarla y cerrar la sesión.
- **Con Spring Data**: Solo define la interfaz y Spring inyecta automáticamente una instacia que ya contiene toda esa lógica de infraestructura.

# Derivación de Consultas por Nombre (Query Methods)

Una de las características más potentes que utiliza este backend es la capacidad de generar consultas basadas en el nombre del método. Spring analiza el nombre del método definido en la interfaz y "deduce" la consulta SQL necesaria.

Por ejemplo, si en `UserDao` se define `Optional<User> findByLoginName(String loginName);`.
Spring interpreta automáticamente que debe realizar una consulta: `SELECT * FROM User WHERE loginName = ?`

# Consultas Personalizadas con `@Query`
En casos donde la lógica de búsqueda es más compleja y no se puede expresar solo con el nombre del método (por ejemplo, búsquedas con múltiples filtros o joins complejos), se utiliza la anotación `@Query`. Esto permite escribir **JPQL (Java Persistance Query Language)**, que es un lenguaje orientado a objetos que hace referencia a las entidades y no a las tablas físicas.

# Interacción en el sistema

Los DAOs interactúan exclusivamente con la capa de **Servicio** El flujo técnico es el siguiente:
1. El **Service** recibe una petición de lógica.
2. El **Service** invoca un método del **DAO** (ej. `userDao.existsByLoginName(loginName)`.
3. El **Proxy de Spring** traduce esa llamada a una sentencia SQL optimizada para el dialecto de la base de datos configurada (en este caso MySQL).
4. **Hibernate** (que es el motor bajo de JPQ) ejecuta el SQL, mapea el resultado (ResultSet) a una instacia de la **Entidad**(`User`, `Movie`, etc.) y la devuelve al servicio.

Esta separación garantiza que, si en el futuro se decidiera cambiar la base de datos de MySQL a PostgreSQL, el código de los DAOs y los Servicios permanecería prácticamente idéntico, ya que Spring se encarga de adaptar el lenguaje de persistencia.
