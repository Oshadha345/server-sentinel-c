# 📊 System Flowchart

---

## 🚀 Main System Flow

> The following flowchart represents the core logic of the **Server-Sentinel-C** system:

```mermaid
graph TD
    A1[Start] --> B1{Initialize Controller<br>State = NORMAL<br>Log Size = 120}
    B1 --> C1[Enter Main Loop]
    C1 --> D1{Get User Command<br>e.g., fail_cooling, fix}
    D1 --> E1[Update Smart Data<br>Generator State]
    E1 --> F1[Get Simulated Sensor Reading<br>Temp & Humidity]
    F1 --> G1[Log the Reading]
    G1 --> H1{Check Reading<br>Against Thresholds}
    
    subgraph StateLogic
        H1 -- "Temp > 60C OR<br> Hum >80% / <20% " --> I1[State = DANGER]
        H1 -- "Temp > 45C OR<br> Hum >70% / <30% " --> J1[State = CAUTION]
        H1 -- Otherwise --> K1[State = NORMAL]
    end

    I1 --> L1{Is Temp > 60C<br>for > 20s?}
    L1 -- Yes --> M1[State = SHUTDOWN<br>Print Final Msg<br>Exit]
    L1 -- No --> N1[Print DANGER Alert]
    
    J1 --> O1[Print CAUTION Alert]
    K1 --> P1[Print NORMAL Status]

    N1 --> C1
    O1 --> C1
    P1 --> C1
```

---

## 🧠 Smart Data Module Flow

> The following flowchart shows how the **Smart Data** module processes commands and generates sensor readings:

```mermaid
graph TD
    A2[Get Command] --> B2{Command Type?}
    B2 -- fail_cooling --> C2[Set State to<br>HEATING_UP]
    B2 -- fix --> D2[Set State to<br>COOLING_DOWN]
    B2 -- humidity_spike --> E2[Set State to<br>HUMIDITY_SPIKE]
    B2 -- intermittent --> F2[Set State to<br>INTERMITTENT_FAILURE]
    
    C2 --> G2[Positive Temp Drift<br>Negative Humidity Drift]
    D2 --> H2[Negative Temp Drift<br>Positive Humidity Drift]
    E2 --> I2[Zero Temp Drift<br>Positive Humidity Drift]
    F2 --> J2[Alternating<br>Drift Patterns]
    
    G2 --> K2[Generate Reading]
    H2 --> K2
    I2 --> K2
    J2 --> K2
    
    K2 --> L2[Return Sensor Reading]
```

---

## 📝 Logger Module Flow

> The following flowchart illustrates the circular buffer mechanism of the **Logger** module:

```mermaid
graph TD
    A3[Receive New Reading] --> B3{Is Log Full?}
    B3 -- Yes --> C3[Overwrite<br>Oldest Entry]
    B3 -- No --> D3[Add to<br>Next Position]
    
    C3 --> E3[Update Log Pointers]
    D3 --> E3
    
    E3 --> F3[Return]
```

---

## 💡 System Logic Module Flow

```mermaid
graph TD
    A4[Receive Sensor Reading] --> B4{Check Temperature}
    B4 -- " 60°C < " --> C4[Temp State = DANGER]
    B4 -- " 45°C < " --> D4[Temp State = CAUTION]
    B4 -- " 45°C >= " --> E4[Temp State = NORMAL]

    A4 --> F4{Check Humidity}
    F4 -- " < 20% or > 80% " --> G4[Humidity State = DANGER]
    F4 -- " < 30% or > 70% " --> H4[Humidity State = CAUTION]
    F4 -- " 30% to 70% " --> I4[Humidity State = NORMAL]
    
    C4 --> J4{Determine<br>Overall State}
    D4 --> J4
    E4 --> J4
    G4 --> J4
    H4 --> J4
    I4 --> J4
    
    J4 --> K4[Set System State<br>to Most Severe]
    
    K4 --> L4{Is State DANGER<br>due to Temperature?}
    L4 -- Yes --> M4[Increment<br>Critical Timer]
    L4 -- No --> N4[Reset<br>Critical Timer]
    
    M4 --> M4a[Store Timer Value<br>in System Status]
    M4a --> O4{Timer > 20s?}
    O4 -- Yes --> P4[State = SHUTDOWN]
    O4 -- No --> Q4[Keep State = DANGER]
    
    N4 --> N4a[Reset Timer Value<br>in System Status]
    N4a --> R4[Return Current State]
    P4 --> R4
    Q4 --> R4
```

---

<p align="center">
    <img src="https://img.shields.io/badge/Diagram-Mermaid-blue?logo=mermaid" alt="Mermaid Diagram Badge">
</p>