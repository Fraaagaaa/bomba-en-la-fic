# Beans
En el ecosistema de Spring Framework, un **Bean** es el componente fundamental sobre el cual se construye toda la aplicación. Aunque el término puede parecer genérico, en este contexto tiene un significado técnico muy preciso y relacionado con la gestión de esos elementos:

# Definición Técnica

Un **Spring Bean** es simplemente un objeto que es instaciado, ensamblado y gestionado por el contenedor de **Inversión de control (IoC)** de Spring. A diferencia de un objeto normal que se crea manualmente usando la palabra clave `new`, un Bean es un objeto cuya vida y dependencias son controladas por el framework.

# El Contenedor de Inversión de Control (IoC)
El contenedor de IoC (representado habitualmente por la interfaz `ApplicationContext`) es el "cerebro" que gestiona los Beans. Su funcionamiento se basa en dos conceptos clave:
- Inversión de Control (IoC): El control sobre la creación de objetos se translada del programador al framework.
- Inyección de Dependencia (DI): El contenedor suministra a cada Bean los otros objetos que necesita para funcionar, conectándolos automáticamente.

# ¿Cómo se define un Bean?
Existen varias formas de indicarle a Spring que una clase debe ser tratada como un Bean:
- Anotaciones de Estereotipos: Se colocan sobre la clase para qeu Spring la detecte automáticamente durante el escaneo de paquetes.
    - `@Component`: El tipo más genérico.
    - `@Service`: Indica que la clase contiene lógica de negocio.
    - `@Repository`: Indica que la clase gestiona el acceso a datos (DAOs)
- Anotación `@Bean`: Se utiliza dentro de clases de configuración (anotadas con `@Configuration`). Es útil cuando se desea registrar como Bean una clase que pertenece a una librería externa y cuyo código fuente no se puede modificar para añadirle `@Component`.

# Ámbitos de un Bean (Scopes)
Spring permite definir cuántas instancias de un Bean deben existir mediante el "Scope". Los más comunes son:
1. Sigleton (por defecto): El componente crea una única instancia de ese Bean para toda la aplicación. Siempre que se solicite, se devolverá el mismo objeto.
2. Prototype: Se crea una instancia nueva cada vez que el Bean es solicitado.
3. Request / Session: (Específicos de aplicaciones web) La instancia vive únicamente durante la duración de una petición HTTP o de una sesión de usuario, respectivamente.

# Ciclo de vida del Bean
Un Bean pasa por varias etapas desde que la aplicación arranca hasta que se detiene:
1. Instalación: Spring crea el objeto (equivalente al `new`).
2. Inyección de propiedades: Spring inyecta las dependencias necesarias (objetos marcados con `@Autowired`).
3. Post-procedimiento: Se ejecutan métodos de inicialización si han sido definidos (usando la anotación `@PostConstruct`).
4. Uso: El Bean está listo y disponible para ser utilizado por otra aplicación.
5. Destrucción: Cuando el contenedor se cierra, se ejecutan métodos de liempieza (anotados con `@PreDestroy`).

# Importancia de los Beans
La arquitectura basada en Beans permite que el código sea extremadamente modular y fácil de probar. Dado que los objetos no se crean entre sí de forma "dura" (hard-coded), es posible sustituir un Bean real por un "mock" o simulacro durante las pruebas unitarias sin cambiar ni una sola línea de la lógica de negocio.

