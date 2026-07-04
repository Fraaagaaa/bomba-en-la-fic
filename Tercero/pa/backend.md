Todo el código está en `es.udc.paproject.backend`

# Capa modelo

- `entities`: Contiene las clases que representan las tablas de la base de datos (mapeadas con JPA), como `User`, `Movie`, `Session` y `Purchase`.
- `DAOs`: Interfaces que heredan de Spring Data para gestionar la persistencia de las entidades sin escribir SQL manualmente.
- `services`: Contiene la lógica de negocia. Se divide en interfaces e implementaciones.
- `excepciones`: Define excepciones personalizadas para errores de negocio, como `InstanceNotFoundException` o `SessionAlreadyStartedException`.

# Capa REST

- `controllers`: Reciben las peticiones HTTP y delegan el trabajo a los servicios. (`UserController`, `MovieController` y `PurchaseController`.
- `dtos`: Objetos de Transferencia de Datos. Son clases sencillas utilizadas para recibir datos del cliente o enviarlos en las respuestas, evitando exponer directamente las entidades de la base de datos.
- `conversores`: Clases con métodos estáticos que transforman **Entidades en DTOs** y viceversa.
- `common`: Incluye la configuración de seguridad (`SecurityConfig`), filtros para la autenticación por tokens (`JwtFilter`) y la gestión global de errores (`CommonControllerAdvice`).

# Flujo de interacción 

Cuando se realiza una petición al backend, los archivos interactuan siguiendo este flujo:

1. Entrada: La petición HTTP llega a un **Controller**.
2. Validación y conversión: Si el cliente envía datos, el controlador recibe un **DTO**. Spring valida los datos **según las anotaciones del DTO** (como `@NotNull` o `@Size`)
3. Lógica de Negocio: El controlador llama a un método del **Service** correspondiente.
4. Persistencia: El servicio aplica las reglas de nogocio y utiliza los **DAOs** para consultar o guardar datos en la base de datos.
5. Respuesta
    - El servico devuelve una **Entidad** al controlador.
    - El contolador usa un **Conversor** para transformar esa entidad en un **DTO**
    - El DTO se devuelve al cliente en formato JSON.

# Componentes Trasversales

- Seguridad: El `JwtFilter` intercepta cada petición para validar el token de usuario contenido en la cabecera "Authorization". Utiliza el `JwtGenerator` para extraer la información del usuario y configurar el contexto de seguridad de Spring.
- Gestión de errores: Si ocurre una excepción en cualquier capa, el `CommonControllerAdvice` la captura y la traduce en un respuesta JSON estructurada con un mensaje de error localizado mediante los archivos `messages_XX.properties`
- Configuración: El archivo `application.yml` define parámetros como la conexión a la base de datos MySQL y la clave secreta para firmar los tokens JWT
- Base de Datos: Los scripts SQL en `src/sql` se utilizan para crear las tablas e insertar datos inicales.

# Tecnologías utilizadas (pom.xml)

El archivo `pom.xml` gestiona todas las dependencias necesarias, incluyendo:
- **Spring Boot Starter Data JPA**: Para el acceso a datos
- **Spring Boot Starter Security**: Para la protección de rutas.
- **io.jsonwebtoken (jjwt)**: Para la generación y validación de tokens JWT.
- **MySQL Connector**: Para la conexión con el servidor de base de datos.

