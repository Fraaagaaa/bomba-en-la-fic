# DTOs
Los **DTOs (Data Transfer Objects)** son, en esencia, "sobres" de datos. En este proyecto, su función es transportar información desde el cliente (frontend) hasta el servidor y viceversa, sin exponer la estructura interna de la base de datos.

# DTO vs Entidad
Es vital no confundirlos
- Entidad (`User`, `Movie`): Es un reflejo de la base de datos. Tiene anotaciones de JPA (`@Entity`, `@Id`), puede tener relaciones complejas y campos sensibles.
- DTO (`UserDto`, `MovieDto`): Es una clase Java simple (POJO). Solo contiene los campos que el frontend necesita ver o enviar.

## ¿Por qué no usar solo entidades?
1. Seguridad: Evita el "Mass Assignment Attack". Si usaras las entidad `User` para registrarse, un atacante podría enviar un JSON con el campo `role: 'ADMIN'` y, si no tienes cuidado, Spring lo guardaría en la base de datos.
2. Eficiencia: Una entidad de película puede tener una lista de 50 sesiones. Si el frontend solo quiere el título, el DTO solo llevará el título, ahorrando ancho de banda.
3. Desacoplamiento: Puedes cambiar el nombre de una columna en la base de datos sin romper el frontend, ya que el DTO permanece igual.

# Validación de Datos
Los DTOs en su proyecto son el primer filtro de seguridad gracias a las anotaciones de la especificación **JSR 380**. En clases como `LoginParamsDto` o `UserDto`, verá anotaciones como:
- `@NotNull` / `@NotEmpty`: El campo no puede llegar vacío.
- `@Size(min=1, max=60)`: Controla la longitud de los strings.
- `@Email`: Valida que el formato sea de correo electrónico.

## ¿Quién dispara esta validación?
En el controlador, verá que el parámetro del método tiene la anotación `@Valid`. Spring intercepta la petición, comprueba las reglas del DTO y, si algo falla, detiene la ejecución y devuelve el error `400 Bad Request` antes siquiera de llegar al Servicio.

# El patrón "Conservador"
Dado que los Servicios trabajan con Entidas y los Controladores con DTOs, necesitamos "traductores". Aquí entran los **Conversores** (`UserConversor`, `MovieConversor`):
- Métodos estçaticos: Suelen ser clases con métodos como `toUserDto(User user)` o `toUser(UserDto userDto)`.
- Transformación: Se encargan de la lógica tediosa de copiar valores de un objeto a otro:
``` Java
public static UserDto toUserDto(User user) {
    return new UserDto(user.getId(), user.getLoginName(), user.getFirstName() ...)
}
```

# Tipos de DTOs en su arquitectura
En su carpeta `dtos`, verá que hay una distinción sutil pero importante:
1. DTOs de Respuestas: (Ej. `UserDto`, `MovieDto`) Devuelven información al cliente.
2. DTOs de Parámetros (`ParamsDto`): (Ej. `LoginParamsDto`, `PurchaseParamsDto`, `ChangePasswordParamsDto`) Se usan exclusivamente para recibir datos de formularios o acciones específicas. No tienen ID, porque son datos "en tránsito" que aún no existen en la BD.

# Resumen del Ciclo de Vida de un DTO
1. Frontend: Envía un JSON con datos de compra.
2. Spring: Recibe el JSON y crea un objeto `PurchaseParamsDto`.
3. Validación: Spring comprueba si el número de entradas es mayor a 0 (vía `@Min(1)`).
4. Controlador: Recibe el DTO ya váido y lo pasa al Servicio.
5. Servicio: Realiza la compra y devuelve una entidad `Purchase` ( con ID, fecha, etc.).
6. Conversor: El controlador toma esa entidad y la convierte en un `PurchaseDto`.
7. Salida: El cliente recibe el JSON final.

Esta estructura hace que el código sea **robusto** (no entrega datos basura), **seguro** (no se filtran datos internos) y **fácil de mantener**.
