### Project Overview
This project implements a smart thermostat firmware running on STM32.  
It enables remote temperature control via UART using an HTTP-like protocol.

Key capabilities include:

- Remote command execution using structured requests
- Secure communication using encryption and authentication
- Time-based scheduling using RTC
- Adaptive energy optimization based on usage patterns
- Modular embedded architecture for scalability

## System Architecture

```mermaid
    flowchart TD

    User[User / UART Terminal]
    
    User --> UART
    
    UART --> WebServer
    
    WebServer --> RequestQueue
    
    RequestQueue --> CommandProcessor
    
    CommandProcessor --> JSONParser
    
    JSONParser --> Authenticator
    
    Authenticator --> Scheduler
    Authenticator --> ThermostatController
    
    Scheduler --> ThermostatController
    
    ThermostatController --> HVAC[HVAC Control]
    
    EnergyOptimizer --> ThermostatController
```

### Firmware Layer Architecture

```mermaid
    flowchart TB
    
    subgraph Application Layer
    ThermostatController
    Scheduler
    EnergyOptimizer
    end
    
    subgraph Middleware Layer
    WebServer
    RequestQueue
    CommandProcessor
    JSONParser
    end
    
    subgraph Security Layer
    CryptoEngine
    Authenticator
    end
    
    subgraph Platform Layer
    PlatformUART
    PlatformRTC
    PlatformSensor
    PlatformHVAC
    end
    
    PlatformUART --> WebServer
    WebServer --> RequestQueue
    RequestQueue --> CommandProcessor
    CommandProcessor --> JSONParser
    JSONParser --> Authenticator
    
    Scheduler --> ThermostatController
    EnergyOptimizer --> ThermostatController
    ThermostatController --> PlatformHVAC
```

### Command Processing Flow

```mermaid
    sequenceDiagram
    
    participant User
    participant UART
    participant WebServer
    participant Queue
    participant CommandProcessor
    participant JSONParser
    participant Auth
    participant Thermostat
    
    User->>UART: Send Command
    UART->>WebServer: Receive Data
    WebServer->>Queue: Push Request
    Queue->>CommandProcessor: Pop Request
    CommandProcessor->>JSONParser: Parse JSON
    JSONParser->>Auth: Verify Token
    Auth->>Thermostat: Execute Command
    Thermostat-->>User: Send Response
```

### Scheduler Runtime Logic

```mermaid
    flowchart TD
    
    RTC[RTC Time]
    
    RTC --> Scheduler
    
    Scheduler --> CheckSchedule{Schedule Match?}
    
    CheckSchedule -- Yes --> UpdateTemp[Update Target Temperature]
    
    UpdateTemp --> ThermostatController
    
    CheckSchedule -- No --> Continue
    
    Continue --> NextLoop
```

### Thermostat Control Logic

```mermaid
    flowchart TD

    TempSensor[Read Temperature]
    
    TempSensor --> Compare{Compare with Target}
    
    Compare -- Below Target --> HeatingON[Turn Heating ON]
    
    Compare -- Above Target --> HVACOFF[Turn HVAC OFF]
    
    HeatingON --> HVAC
    
    HVACOFF --> HVAC
```

### Full System Data Flow

```mermaid
    flowchart LR

    UART --> Parser
    Parser --> Queue
    Queue --> Processor
    Processor --> Security
    Security --> Scheduler
    Scheduler --> Controller
    Controller --> HVAC
    Controller --> Optimizer
```

### Folder Structure Diagram

```mermaid
    flowchart TB
    
    Project[Smart Thermostat]
    
    Project --> App
    Project --> Middleware
    Project --> Security
    Project --> Platform
    Project --> ThirdParty
    
    App --> ThermostatController
    App --> Scheduler
    App --> EnergyOptimizer
    
    Middleware --> WebServer
    Middleware --> RequestQueue
    Middleware --> CommandProcessor
    
    Security --> CryptoEngine
    Security --> Authenticator
    
    Platform --> UART
    Platform --> RTC
    Platform --> Sensor
    Platform --> HVAC
    
    ThirdParty --> JSMN
```
