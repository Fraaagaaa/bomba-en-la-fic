# Capa Servicio
El código sigue una arquitectura multicapa basada en **Spring Boot**, diseñada para separar las responsabilidades de persistencia, lógica de negocio y comunicación externa. A continuación se detalla la distribución del código y la interacción entre sus componentes:

# Estructura de Capas
El código se organiza principalmente bajo el paquete `es.udc.paproject.backend`:
- Capa de Modelo (`model`): Es el núcleo del sistema.
    - `entities`: Contiene las clases que representan las tablas de la base de datos (mapeadas con JPA), como `User`, `Movie`, `Session` y `Purchase`.
    - `entities (DAOs)`: Interfaces que heredan de Spring Data (como `ListCrudRepository` o `JpaRepository`) para gestionar la persistencia de las entidades sin escribir SQL manualmente.
    - `services`: Contiene la lógica de negocio. Se divide en interfaces (ej. `MovieService`) e implementaciones (ej. `MovieServiceImpl`).
    - `exceptions`: Define excepciones personalizadas para errores de negocio, como `InstanceNotFoundException` o `SessionAlreadyStartedException`.
- Capa Rest (`rest`): Gestiona la comunicación con el exterior (el frontend u otros cliente).
    - `controllers`: Reciben las peticiones HTTP y delegan el trabajo a los servicios. Ejemplos: `UserController`, `MovieController` y `PurchaseController`.
    - `dtos`: Objetos de Transferencia de Datos. Son clases sencillas utilizadas para escribir datos del cliente o enviarlos en las respuestas, evitando exponer directamente las entidades de la base de datos.
    - `dtos` (Conversores): Clases con métodos estáticos que transforman **Entidades en DTOs** y viceversa (ej. `MovieConversor`).
    - `common`: Incluye la configuración de seguridad (`SecurityConfig`), filtros para la autentificación por tokens (`JwkFilter`) y la gestión global de errores (`CommonControllerAdvise`).

# Flujo de Interacción
Cuando se realiza una petición al backend, los archivos interactúan siguiendo este flujo:
1. Entrada: La petición HTTP llega a un **Controller** (ej. `MovieController.viewMovieDetails`).
2. Validación y conversión: Si el cliente envía datos (ej. al comprar entradas), el controlador recibe un **DTO** (`PurchaseParamsDto`). Spring valdia los datos según las anotaciones del DTO (como `@NotNull` o `@Size`).
3. Lógica de negocio: El controlador llama a un método del **Service** correspondiente (`purchaseService.purchase`).
4. Persistencia: El servicio aplica las reglas de negocio (ej. comprobar si hay asientos libres) y utiliza los **DAOs** (`SessionDao`, `PurchaseDao`) para consultar o guardar datos en la base de datos.
5. Respuesta:
    - El servicio devuelve una **Entidad** al controlador.
    - El controlador usa un **Conversor** (`PurchsaeConversor`) para transformar esa entidad en un **DTO** (`pruchaseDto`).
    - El DTO se devuelve al cliente en formato JSON.

# Componentes Transversales
- Seguridad: El `JwtFilter` intercapta cada petición para validar el token de usuario contenido en la cabecera "Authorization". Utiliza el `JwtGenerator` para extraer la información del usuario y configurar el contexto de seguridad de Spring.
- Gestión de errores: Si ocurre una excepción en cualquier capa (ej. no se encuentra una película), el `CommonControllerAdvice` la captura y la traduce en una respuesta JSON estructurada con un mensaje de error localizado mediante los archivos `messages_XX.properties`.
- Configuración: El archivo `application.yml` define parámetros como la conexión a la base de datos MySQL y la clave secreta para firmar los tokens JWT.
- Base de Datos: Los scripts SQL en `src/sql` se utilizan para crear las tablas (`1-MySQLCreateTables.sql`) e insertar datos iniciales (`2-MySQLCreateData.sql`).

# Tecnologías usadas (pom.xml)
El archivo `pom.xml` gestiona todas las dependencias necesarias, incluyendo:
- Spring Boot Strater Data JPA: Para acceso a datos.
- Spring Boot Starter Security: Para la protección de rutas.
- io.jsonwebtoken (jjwt): Para la configuración de tokens JWT.
- MySQL Connector: Para la conexión con el servidor de base de datos.
