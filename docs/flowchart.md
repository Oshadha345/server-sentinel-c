# System Flowchart

The following flowchart represents the core logic of the Server-Sentinel-C system:

```mermaid
graph TD
    A[Start] --> B{Initialize Controller<br>State = NORMAL<br>Log Size = 120};
    B --> C[Enter Main Loop];
    C --> D{Get User Command<br>(e.g., "fail_cooling", "fix")};
    D --> E[Update Smart Data Generator State];
    E --> F[Get Simulated Sensor Reading<br>(Temp & Humidity)];
    F --> G[Log the Reading];
    G --> H{Check Reading Against Thresholds};
    
    subgraph StateLogic
        H -- Temp > 60C OR Hum >80%/<20% --> I[State = DANGER];
        H -- Temp > 45C OR Hum >70%/<30% --> J[State = CAUTION];
        H -- Otherwise --> K[State = NORMAL];
    end

    I --> L{Is Temp > 60C for > 20s?};
    L -- Yes --> M[State = SHUTDOWN<br>Print Final Msg<br>Exit];
    L -- No --> N[Print DANGER Alert];
    
    J --> O[Print CAUTION Alert];
    K --> P[Print NORMAL Status];

    N --> C;
    O --> C;
    P --> C;

    A[Get Command] --> B{Command Type?};
    B -- "fail_cooling" --> C[Set State to HEATING_UP];
    B -- "fix" --> D[Set State to COOLING_DOWN];
    B -- "humidity_spike" --> E[Set State to HUMIDITY_SPIKE];
    B -- "intermittent" --> F[Set State to INTERMITTENT_FAILURE];
    
    C --> G[Positive Temp Drift<br>Negative Humidity Drift];
    D --> H[Negative Temp Drift<br>Positive Humidity Drift];
    E --> I[Zero Temp Drift<br>Positive Humidity Drift];
    F --> J[Alternating Drift Patterns];
    
    G --> K[Generate Reading];
    H --> K;
    I --> K;
    J --> K;
    
    K --> L[Return Sensor Reading];

    A[Receive New Reading] --> B{Is Log Full?};
    B -- Yes --> C[Overwrite Oldest Entry];
    B -- No --> D[Add to Next Position];
    
    C --> E[Update Log Pointers];
    D --> E;
    
    E --> F[Return];
```