# Patrón de diseño
Hemos optado por el patrón Model View ViewModel para la estructuración de la aplicación
# Diagramas
## Diagrama de clases
``` Mermaid
classDiagram
    direction LR

    %% --- ACTOR 1: MODEL (La capa de datos) ---
    namespace Model_Layer {
        class Friend {
            +Id isarId
            +String name
            +double totalCreditBalance
            +double totalDebitBalance
            +Friend(name, totalCreditBalance, totalDebitBalance)
        }

        class Expense {
            +Id isarId
            +String description
            +DateTime date
            +double amount
            +IsarLink~Friend~ payer
            +IsarLinks~Friend~ participants
            +Expense(description, date, amount)
        }

        class FriendRepository {
            <<Interface>>
            +fetchFriends() Future~Result~
            +addFriend(friend) Future~Result~
            +removeFriend(id) Future~Result~
        }
    }

    %% --- ACTOR 2: VIEWMODEL (El gestor de estado) ---
    namespace ViewModel_Layer {
        class FriendViewModel {
            -FriendRepository _friendRepository
            +List~Friend~ friends
            +String? errorMessage
            +Command0 load
            +Command1~void, String~ addFriend
            +Command1~void, int~ removeFriend
            +FriendViewModel(friendRepository)
            -_load() Future
            -_addFriend(name) Future
            -_removeFriend(id) Future
        }
        
        class Command {
            <<Utility>>
            +execute()
        }
    }

    %% --- ACTOR 3: VIEW (La interfaz gráfica) ---
    namespace View_Layer {
        class FriendsView {
            <<Widget>>
            +build(context) Widget
            -Muestra lista de amigos
            -Usa Provider para escuchar cambios
        }
    }

    %% RELACIONES
    %% Relación entre Modelos (Relaciones de base de datos)
    Expense "0..*" --> "1" Friend : payer (IsarLink)
    Expense "0..*" --> "1..*" Friend : participants (IsarLinks)

    %% Relación View -> ViewModel
    FriendsView ..> FriendViewModel : Observa (Provider/Consumer)
    FriendsView ..> Command : Ejecuta acciones

    %% Relación ViewModel -> Model
    FriendViewModel o-- Friend : Gestiona lista de
    FriendViewModel --> FriendRepository : Usa para obtener datos
    FriendViewModel ..> Command : Expone comandos

    %% Relación Repository -> Model
    FriendRepository ..> Friend : Devuelve/Guarda
```

## Diagrama de secuencia (Crear gasto)
``` Mermaid
sequenceDiagram
    participant U as Usuario
    participant App as Aplicación Móvil
    participant DB as Base de Datos
    
    U->>App: Clic en botón "Gastos"
    App->>App: Muestra lista de gastos
    
    U->>App: Clic en botón "+"
    App->>App: Navega a "crear gasto"
    
    U->>App: Ingresa Description, Fecha, Monto
    U->>App: Selecciona Participantes
    
    U->>App: Clic en "Confirmar"
    
    App->>DB: Guarda nuevo Expense
    DB-->>App: Confirma guardado
    
    alt Error al guardar
        DB-->>App: Envía código de Error
        App->>U: Muestra "ERROR!"
    else Éxito al guardar
        App->>U: Muestra pantalla de Carga
        App->>App: Regresa a "Gastos"
        App->>U: Muestra lista de Expenses actualizada
    end
```

## Diagrama de flujo
``` Mermaid
graph TD
    A["Pantalla Principal"] --> B{"Menú: Friends / Expenses"};
    
    B --> C["Amigos"];
    B --> G["Gastos"];
    
    C --> D{"Ver Amigo"};
    C --> E{"Añadir Amigo"};
    C --> F{"Ir a Gastos"};
    
    D --> C2["Ver gastos de amigo X"];
    
    G --> H{"Ver Gasto"};
    G --> I{"Crear Gasto"};
    G --> J{"Ir a Amigos"};
    
    H --> G2["Ver usuarios de Expense X"];
    
    I --> K["Crear gasto"];
    K --> L{"Carga / Resultado"};
    
    C2 --> M["Modificar gasto"];
    M -->  L;
    
    G2 --> M;
    
    L --> B;
    L --> N["Pantalla de error"];
```
## OAAAAA

