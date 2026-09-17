# Controladores REST
En la arquitectura del proyecto, los **Controladores REST** actúan como la "frontera" del sistema. Son los encargados de recibir las peticiones del frontend (React), interpretar qué desea hacer y devolver una respuesta adecuada.

# ¿Qué hace exactamente un controlador?
El controlador tiene una responsabilidad muy específica: **gestionar el protocolo HTTP**. Sus tareas principales son:
- Escuchar peticiones: Identifica si llega un `GET`, `POST`, `PUT` o `DELETE`.
- Deserializar datos: Convierte el JSON que envía el cliente en objetos Java (DTOs).
- Validar la entrada: Comprueba que los datos recibidos cumplen los requisitos.
- Delegar: Llama al servicio de negocio correspondiente.
- Responder: Devuelve un código de estado (200 OK, 400 Bad Request, etc.) y los datos finales en formato JSON.

# ¿Cómo maneja Spring los Controladores?

Spring utiliza un componente llamado **DispatcherServlet**. Cuando su aplicación arranca:
1. Spring escanea las clases anotadas con `@RestController`.
2. Registra todas las rutas (URLs) definidas en ellas en una tabla de rutas interna.
3. Cuando llega una petición, el `DispatcherServlet` consulta esa tabla, instancia el controlador necesario y ejecuta el modo correspondiente.
4. Al estar anotado con `@RestController`, Spring asume automáticamente que la respuesta debe ser convertida a JSON (usado la librería Jackson).

# Las anotaciones clave

**`@RequestMapping` (El enrutador)**

Se utiliza para definir la dirección URL que atenderá el controlador o un método específico
- A nivel de clase: Define un prefijo común. Por ejemplo, en su `UserController`, verá `@RequestMapping("/users")`. Todas als rutas de ese archivo empezarán por esa dirección.
- A nivel de método: Se suele usar mediante sus variantes más específicas: `@GetMapping`, `@PostMapping`, `@PutMapping`, etc.
<br>
**`@PatchVariable` (Variables en la URL)**

Se utiliza cuando la información vieja en la propia estructura de la URL, normalmente para identificar un recurso concreto.
- Ejemplo en `MovieController`:
``` Java
@GetMapping("/movies/{id}")
public MovieDto findById(@PathVariable Long id {...}
```
Si el frontend solicita `/api/movies/5`, Spring extrae el `5` y lo asigna automáticamente al parámetro `id`.
<br>
**`@Autowired` (Inyección de Dependencias)**
Esta es una de las anotaciones más importantes de Spring. Le indica al frameworkd que el controlador **necesita** otro componente para funcionar (generalmente un servicio).

- Funcionamiento: En lugar de que usted cree el objeto manualmente con `new MovieServiceImpl()`, Spring busca en su contenedor de objetos un "Bean" que encjae con ese tipo y lo "inyecta" automáticamente.
- Uso común: Verá que sus controladores tienen atributos privados de tipo `UserService` o `MovieService` marcados con esta anotación (o inyectados mediante el constructor).

# Resumen de Interacción en un método típico
Imagine que un usuario quiere ver los detalles de una película:
1. Entrada: Llega un un `GET /api/catalog/movies/12`.
2. Mapping: El constructor de catálogo captura la petición gracias a `@GetMapping("/movies/{id}")`.
3. Extracción: `@PathVariable` extrae el `12`.
4. Colaboración: El controlador usa el servicio inyectado vía `@Autowired` para buscar la película: `movieService.findById(12)`.
5. Salida: El controlador recibe la entidad, la convierte a DTO y la devuelve, finalizando el ciclo.
