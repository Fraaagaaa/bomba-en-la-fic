## Definición de Concurrencia
La **concurrencia** es la capacidad de un sistema para gestionar múltiples flujos de interacción o tareas de procesamiento de forma simultánea. En el diseño de interfaces, no se refiere solo al hardware (multiprocesador), sino a la percepción del usuario de que el sistema puede hacer varias cosas a la vez sin bloquearse.<br>
## ¿Por qué es importante?
Un sistema sin concurrencia obliga al usuario a esperar a que termine una tarea para empezar otra. La concurrencia aporta:
* **Responsividad:** El sistema sigue reaccionando a los clics, movimientos de ratón o toques táctiles aunque esté realizando un cálculo pesado internamente.
* **Feedback en Tiempo Real:** Permite mostrar indicadores de progreso mientras la tarea principal sigue su curso.
* **Flexibilidad:** El usuario puede cancelar una operación en curso si se da cuenta de que ha cometido un error, en lugar de esperar a que esta finalice.
* **Aprovechamiento de Canales:** Permite el uso de interfaces **multimodales** (por ejemplo, dictar por voz mientras se mueve un deslizador con el ratón).
<br>
## Usos y Aplicaciones Comunes
En una interfaz moderna, la concurrencia se aplica en:
1.  **Separación de Hilos:** El uso de un hilo principal para la **UI** y hilos secundarios para **tareas de red o bases de datos**.
2.  **Monitorización de Sistemas:** En interfaces industriales (SCADA), permite visualizar datos de sensores en tiempo real mientras el operador configura parámetros en otra ventana.
3.  **Animaciones Fluidas:** Las transiciones visuales se ejecutan de forma independiente a la carga lógica para evitar saltos o "lag".
4.  **Entrada Multicanal:** Gestión de eventos provenientes de distintos periféricos (teclado, ratón, gestos) de manera asíncrona.
``` mermaid
sequenceDiagram
    autonumber
    actor Usuario
    participant Vista as Vista (UI Thread)
    participant Worker as Hilo Secundario (Background)
    participant Servidor as Servidor / BD

    Usuario->>Vista: Clic en botón "Cargar Datos"
    activate Vista
    Vista->>Vista: Mostrar Spinner de carga
    
    Note over Vista, Worker: Inicio de ejecución concurrente
    Vista-->>Worker: ejecutarTareaAsincrona()
    
    deactivate Vista
    Note right of Vista: La interfaz sigue fluida y responde
    
    activate Worker
    Worker->>Servidor: Petición de datos (Request)
    Servidor-->>Worker: Respuesta con datos (Response)
    
    Worker-->>Vista: Notificar finalización (Callback/Event)
    deactivate Worker
    
    activate Vista
    Vista->>Vista: Ocultar Spinner
    Vista->>Vista: Renderizar datos en pantalla
    Vista-->>Usuario: Muestra información actualizada
    deactivate Vista
```