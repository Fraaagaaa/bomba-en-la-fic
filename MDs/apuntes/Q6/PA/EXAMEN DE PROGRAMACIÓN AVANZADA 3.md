
---
##### 1.

El departamento de sistemas nos notifica que la infraestructura de PA-Shop migrará su base de datos de MySQL a un clúster corporativo de Oracle. Atendiendo a la especificación estricta de JPA, ¿qué modificación arquitectónica es obligatoria en el modelado de nuestras Entidades respecto a la generación de claves primarias?

- [ ] a) Ninguna. El paradigma ORM abstrae por completo el motor relacional subyacente, por lo que la directiva `GenerationType.IDENTITY` seguirá inyectando claves autoincrementales nativamente de forma transparente.
    
- [ ] b) Es imperativo permutar la configuración a `GenerationType.SEQUENCE`, dado que motores como Oracle repudian las columnas autoincrementales directas y exigen el uso de secuencias nativas de base de datos.
    
- [ ] c) Se debe desactivar `@GeneratedValue` temporalmente e inyectar el ID de forma asíncrona mediante un `PermissionChecker` en la capa de Servicios REST.
    
- [ ] d) Todas las anteriores son estrategias válidas bajo JPA 3.0.
    

> [!success]- **Soluciones y Justificaciones Analíticas**
> 
> **Opción correcta: b)**
> 
> **Justificación (Ref. Tema 2 - "2.3 Claves Primarias"):** MySQL facilita el soporte para columnas internamente auto-incrementales (`GenerationType.IDENTITY`). Sin embargo, en el ecosistema Oracle este mecanismo no es compatible; Oracle exige delegar la numeración a "secuencias" nativas de base de datos aisladas, lo que requiere incondicionalmente transformar el mapeo arquitectónico hacia `GenerationType.SEQUENCE`.

##### 2.

Estudie la siguiente implementación reactiva diseñada para capturar los datos de un formulario de alta de categorías en nuestro Frontend:


```JavaScript
const CategoryForm = ({ onAdd }) => {
    let input;
    return (
        <form onSubmit={(e) => {
            e.preventDefault();
            onAdd(input.value.trim());
        }}>
            <input type="text" ref={node => input = node} />
            <button type="submit">Guardar</button>
        </form>
    );
}
```

¿Cuál es el dictamen arquitectónico oficial aplicable a este fragmento según los estándares de React?

- [ ] a) Es un diseño óptimo denominado "Controlled Component" (Push), ya que el estado fluye sincronizadamente hacia el Virtual DOM en cada pulsación de tecla.
    
- [ ] b) Constituye un "Uncontrolled Component" (Pull). Los datos no se custodian en el estado local de React (no hay `useState`), sino que se extraen rudimentariamente del nodo físico del DOM real mediante la propiedad mágica `ref` en el último instante.
    
- [ ] c) Provocará una fuga de memoria ("memory leak") porque la promesa asíncrona `onSubmit` carece de una función clean-up en su ciclo de vida.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Soluciones y Justificaciones Analíticas**
> 
> **Opción correcta: b)**
> 
> **Justificación (Ref. Tema 7 - "7.2 Controlled vs Uncontrolled components"):** El fragmento carece por completo del uso del Hook de estado `useState`. Se vale de la propiedad de sonda `ref={node => input = node}` para atar una variable directamente a la etiqueta HTML biológica e interrogar su valor (Pull) rompiendo la sincronicidad central. Esto define académicamente a un "Uncontrolled Component", una estrategia no recomendada porque mantiene a React "ciego" sobre lo que teclea el usuario hasta que éste pulsa Submit.

##### 3.

Un desarrollador junior omite accidentalmente la anotación `@Transactional` en el siguiente servicio de actualización de perfil, pero conserva la inyección de dependencias intacta. El código compila sin errores:


```Java
@Service
public class UserServiceImpl implements UserService {
    @Autowired private UserDao userDao;

    @Override
    public User updateProfile(Long id, String firstName) throws InstanceNotFoundException {
        User user = userDao.findById(id).get();
        user.setFirstName(firstName);
        return user; // Omitió userDao.save(user)
    }
}
```

Atendiendo al comportamiento de la Caché de Primer Nivel (L1), ¿qué ocurrirá físicamente en la base de datos al ejecutarse este método?

- [ ] a) El framework detectará la alteración gracias al "Dirty State" y lanzará una sentencia UPDATE de forma automática, haciendo redundante la falta de la anotación global.
    
- [ ] b) La base de datos no sufrirá ninguna alteración. Al carecer de contexto `@Transactional`, la sesión de Hibernate y su Caché L1 nacen y mueren de forma efímera en la línea del `findById`. El cambio en el objeto queda huérfano en la RAM ordinaria y se pierde al finalizar el método.
    
- [ ] c) Spring Boot levantará una `OptimisticLockingFailureException` inmediata para proteger la integridad de lectura.
    
- [ ] d) Todas las anteriores.
    

> [!success]- **Soluciones y Justificaciones Analíticas**
> 
> **Opción correcta: b)**
> 
> **Justificación (Ref. Tema 3 - "2.4 Estado Dirty y Caché de Primer Nivel"):** Constituye un error crítico en programación Lógica. El mecanismo mágico del "Dirty State" (que lanza el UPDATE automático) y la propia Caché L1 requieren que exista el perímetro temporal de una transacción. Si la anotación `@Transactional` falta, Hibernate abre una sesión minúscula para resolver el `findById` y la cierra milisegundos después. La memoria RAM se corta, y cualquier uso posterior de un setter sobre la entidad es una mutación espectral que jamás tocará físicamente las tablas en MySQL.

##### 4.

Para anular y someter la validación de errores visuales nativos que imponen los navegadores web por defecto (los clásicos "globos" de advertencia) e integrar un diseño corporativo pulcro mediante React Bootstrap, ¿qué directriz estructural en el componente `<Form>` es innegociable?

- [ ] a) Incrustar orgánicamente el atributo semántico `noValidate` en la raíz del formulario para amordazar al explorador, y delegar la lógica programáticamente ejecutando `form.checkValidity()` en el evento de envío.
    
- [ ] b) Bloquear todos los eventos de renderizado envolviendo el formulario con un `useEffect` de array vacío `[]`.
    
- [ ] c) Capturar la excepción global `MethodArgumentNotValidException` directamente en el Reductor para mutar el estilo CSS.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Soluciones y Justificaciones Analíticas**
> 
> **Opción correcta: a)**
> 
> **Justificación (Ref. Tema 7 - "7.4 Validaciones del lado cliente"):** Para imponer el "look-and-feel" estético de Bootstrap y suprimir las alertas erráticas, intrusivas y de escasa personalización de HTML5 en los formularios, es preceptivo y obligatorio insertar la bandera pasiva `noValidate` en el origen del tag `<Form>`. Seguidamente, en el evento asíncrono `onSubmit`, el programador asume manualmente las riendas del chequeo estructural ejecutando la validación programática `form.checkValidity()`.

##### 5.

En la frontera de nuestra API REST, recibimos peticiones autenticadas para recursos privados (ej. comprar un carrito). Bajo una arquitectura verdaderamente Stateless, ¿cuál es la mecánica forense exacta mediante la que el Controlador obtiene de manera fidedigna y blindada el identificador del usuario (userId) sin requerir búsquedas en base de datos?

- [ ] a) El Frontend lo adjunta visiblemente como parámetro en la URL de la forma `?userId=5`, y el Controlador lo extrae mediante `@RequestParam`.
    
- [ ] b) El filtro interceptor `JwtFilter` de Spring Security audita la firma criptográfica del token (HS256) presente en la cabecera `Authorization: Bearer`. Si es válida, desempaqueta el payload, extrae el `userId` inyectado durante el login, y lo transfiere a la petición interna para que el Controlador lo recupere mediante la anotación `@RequestAttribute`.
    
- [ ] c) Se almacena permanentemente en una sesión `HttpSession` en la RAM del servidor Tomcat tras el primer inicio de sesión.
    
- [ ] d) Todas las anteriores son implementaciones válidas del paradigma REST.
    

> [!success]- **Soluciones y Justificaciones Analíticas**
> 
> **Opción correcta: b)**
> 
> **Justificación (Ref. Tema 4 - "6. Seguridad: Autenticación y Autorización JWT"):** Una API Stateless repudia las sesiones activas en Tomcat (falla C) y jamás debe viajar como variable en URL por vulnerabilidad de falsificación (falla A). La verdadera mecánica es delegar la validación a un Filtro de seguridad (`JwtFilter`) anterior al Controlador. Éste evalúa matemáticamente que nadie haya falsificado la firma HS256, extrae el identificador del usuario blindado del interior del payload, y lo inyecta como un tributo seguro en la invocación de Spring a través del decorador `@RequestAttribute`.

##### 6.

Evalúe analíticamente el siguiente selector incrustado en un componente visual encargado de listar únicamente las tareas pendientes de un usuario:


```JavaScript
const ActiveTodos = () => {
    // Selector en línea extrayendo filtrado
    const activeTasks = useSelector(state => state.todos.filter(t => !t.completed));

    return (
        <ul>{activeTasks.map(t => <li key={t.id}>{t.text}</li>)}</ul>
    );
}
```

Determine la catastrófica consecuencia sobre el rendimiento que este código infligirá al Virtual DOM:

- [ ] a) Infringe frontalmente la igualdad referencial. Al ejecutar `.filter()`, el selector devuelve un array de nueva instanciación en memoria tras CADA mutación global. Como la comprobación matemática superficial (`===`) dictaminará diferencias sistemáticamente, el componente forzará re-renderizados inútiles aunque el estado de las tareas no haya variado.
    
- [ ] b) El selector es óptimo y asume un coste algorítmico logarítmico constante $O(1)$ al aprovechar la inmutabilidad intrínseca de los arrays.
    
- [ ] c) Carece de la anotación `@Validated`, provocando que el estado global de Redux degenere en una fuga de memoria (memory leak).
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Soluciones y Justificaciones Analíticas**
> 
> **Opción correcta: a)**
> 
> **Justificación (Ref. Tema 6 - "La Magia Matemática del Rendimiento ==="):** ¡Sacrilegio Arquitectónico de Rendimiento! El `useSelector` dictamina si debe forzar una re-renderización visual calculando exclusivamente si la nueva referencia en RAM es distinta (comprobación `===`). La función nativa de JavaScript `.filter()` jamás muta o aprovecha el arreglo previo; siempre construye un arreglo completamente nuevo en otra zona de memoria. Así, aunque los datos sean idénticos, la igualdad referencial falla y el árbol DOM se repinta parasitariamente ante cualquier evento cruzado de Redux.

##### 7.

Ante requisitos orgánicos altamente variables, se solicita desarrollar un buscador dinámico de productos en la Capa de Acceso a Datos donde los parámetros `categoryId` y `keywords` puedan ser nulos de forma arbitraria. ¿Por qué se repudia taxativamente la inclusión de una anotación estática `@Query("SELECT p FROM Product p WHERE ...")` para este caso?

- [ ] a) Porque la sintaxis JPQL restringe el uso de condicionales lógicos difusos, haciendo que las cláusulas se corrompan ante parámetros no presentes. Es forzoso delegar el diseño dinámico a una infraestructura de Herencia Múltiple acoplando una interfaz extra e implementándola manualmente con la API Criteria o `EntityManager` (Patrón CustomizedDao).
    
- [ ] b) Porque las consultas de catálogo vulneran la directiva transaccional `readOnly=true` exigiendo volcados de estado dirty.
    
- [ ] c) Porque Jackson es incapaz de traducir atributos opcionales devolviendo incondicionalmente un 400 Bad Request.
    
- [ ] d) Todas las anteriores.
    

> [!success]- **Soluciones y Justificaciones Analíticas**
> 
> **Opción correcta: a)**
> 
> **Justificación (Ref. Tema 2 - "6.3 Consultas Dinámicas y el Patrón CustomizedDao"):** Las directrices estáticas de `@Query` son compuestas en el pre-arranque; no soportan lógicas mutables condicionales ricas del tipo "si este String es nulo, omite este WHERE de la cláusula". Para construir SQL polimórfico al vuelo, debemos aislar la resolución inyectando una Interfaz adicional implementada programáticamente con la API Interna y anexarla al `Repository` original para que efectúe Herencia Múltiple, conformando el aclamado Patrón CustomizedDao.

##### 8.

En la capa de servicios web interceptamos un fallo semántico predecible del cliente (ej. intentar efectuar un pago sin saldo) originado en la capa de lógica. Al configurar los métodos `@ExceptionHandler` en nuestro `@ControllerAdvice`, se nos exige inyectar automáticamente la variable `Locale`. ¿Cuál es el sustrato arquitectónico de esta acción?

- [ ] a) Descifrar el JWT con llaves asimétricas para aislar perfiles de usuario geolocalizados.
    
- [ ] b) Materializar la Internacionalización (i18n). El framework intercepta silenciosamente la cabecera nativa `Accept-Language` enviada por el navegador del cliente y la consolida en el objeto `Locale`, permitiendo al `MessageSource` extraer y rebotar un JSON de error redactado dinámicamente en el idioma exacto del consumidor.
    
- [ ] c) Neutralizar ataques CORS validando que la IP de origen se encuentre en los entornos autorizados del `application.yml`.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Soluciones y Justificaciones Analíticas**
> 
> **Opción correcta: b)**
> 
> **Justificación (Ref. Tema 4 - "5. Internacionalización - i18n"):** Las arquitecturas fronterizas de red no obligan al backend a leer atributos de base de datos para deducir el lenguaje. Es el protocolo HTTP quien remite en sus entrañas la etiqueta estandarizada `Accept-Language` originada en el explorador del usuario. Spring procesa inteligentemente esta directriz en crudo y la empaqueta nativamente bajo el objeto paramétrico de inyección `Locale`, vital para interrogar con éxito nuestros ficheros `messages_es.properties`.

##### 9.

En la fase de consolidación del ciclo de vida asíncrono de un componente encargado de montar los datos de un catálogo maestro, se redacta el siguiente Hook limitador:


```JavaScript
const Catalog = () => {
    const dispatch = useDispatch();

    useEffect(() => {
        dispatch(actions.fetchMasterCatalog());
    });

    // ... renderizado ...
}
```

Atendiendo a la matriz de dependencias proporcionada a la firma de la función nativa, pronostique el desenlace de la carga visual:

- [ ] a) El sistema se ahogará en un Bucle Infinito. Al omitir completamente el array de dependencias opcional `[]`, React ejecutará el efecto tras cada renderizado. Como `dispatch` muta el estado global Redux y obliga a repintar, el ciclo de repeticiones colapsará la RAM de la pestaña.
    
- [ ] b) La consulta de red se ejecutará de forma quirúrgica una única vez al montar el componente, siendo el diseño idóneo para búsquedas primarias.
    
- [ ] c) React suspenderá la invocación asíncrona porque exige imperativamente que la llamada se decore con el método envoltorio `form.checkValidity()`.
    
- [ ] d) Ninguna de las anteriores.
    

> [!success]- **Soluciones y Justificaciones Analíticas**
> 
> **Opción correcta: a)**
> 
> **Justificación (Ref. Tema 7 - "7.3 Hook useEffect - dependencias"):** Esta trampa mortífera expone la ignorancia de las firmas nativas. Si el `useEffect` se configura prescindiendo enteramente de su segundo parámetro (omitiendo hasta el vector vacío `[]`), su ciclo vital degenera provocando que ejecute su envoltorio asíncrono posterior a cada evento de montaje en el Virtual DOM. Dado que despacha una acción de red a Redux que obligará al árbol de React a redibujarse, este redibujo volverá a disparar el efecto de red... induciendo un colapso en cadena (Bucle Infinito).

##### 10.

La gerencia nos informa de que el Backend ya no se desplegará mediante la ejecución de una máquina virtual directa, sino que se instalará de forma corporativa sobre un Servidor de Aplicaciones externo y preexistente de la compañía (Tomcat Standalone clásico). A nivel de empaquetado de Spring Boot, ¿qué dictamen procede?

- [ ] a) Resulta irrelevante. Spring Boot es polimórfico, por lo que su comando `mvn package` generará un Fat JAR universal que el servidor externo transmutará mágicamente a RAM.
    
- [ ] b) El enfoque Fat JAR provisto por defecto queda inhabilitado. El proyecto requerirá una refactorización de configuración en Maven para expurgar el Tomcat embebido y generar forzosamente un artefacto comprimido de tipo `.war` apto para despliegues empresariales tradicionales.
    
- [ ] c) Es forzoso implementar la interfaz `PagingAndSortingRepository` para adecuar los repositorios relacionales al ancho de banda del nuevo servidor externo.
    
- [ ] d) Todas las anteriores.
    

> [!success]- **Soluciones y Justificaciones Analíticas**
> 
> **Opción correcta: b)**
> 
> **Justificación (Ref. Tema 4 - "1.1 Concepto de Examen: Fat JAR vs WAR"):** El paradigma estrella "Fat JAR" compila e incrusta el código de la tienda asimilando un servidor virtual Apache Tomcat en el interior, posibilitando el despliegue automático autónomo vía consola. Si las políticas operativas nos fuerzan a hospedar la aplicación en un Servidor de Aplicaciones externo gestionado separadamente, el Fat JAR nativo resulta inservible. Deberá extraerse la auto-dependencia y reconfigurar la transpilación a un archivo modular `.war`.