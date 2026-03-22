#System Architecture Diagram

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
