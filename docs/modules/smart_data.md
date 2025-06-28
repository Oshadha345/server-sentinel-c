# 🧠 Smart Data Module

## 🎯 Purpose
> The Smart Data module is responsible for simulating realistic environmental conditions in a server room. It generates temperature and humidity readings based on different scenarios to test the system's response to normal and emergency conditions.

## 📊 States

### ✅ `STABLE`
- **Description**: Normal server room conditions.
- **Behavior**: 
  - Temperature: `21-25°C` with minor fluctuations.
  - Humidity: `45-55%` with minor fluctuations.
  - Temperature and humidity drift are near zero.

### 🔥 `HEATING_UP`
- **Description**: Simulates a cooling system failure.
- **Behavior**:
  - Temperature increases steadily (`+2.0°C` per cycle).
  - Humidity decreases slowly (`-0.5%` per cycle).
  - Simulates a worst-case scenario leading to `SHUTDOWN`.

### ❄️ `COOLING_DOWN`
- **Description**: Simulates system recovery after intervention.
- **Behavior**:
  - Temperature decreases rapidly (`-3.0°C` per cycle).
  - Humidity normalizes (`+1.0%` per cycle).
  - Returns to `STABLE` when temperature reaches the normal range.

### 💧 `HUMIDITY_SPIKE`
- **Description**: Simulates humidity control failure.
- **Behavior**:
  - Temperature remains stable.
  - Humidity increases rapidly (`+4.0%` per cycle).
  - Tests humidity-specific alerts.

### ⚡ `INTERMITTENT_FAILURE`
- **Description**: Simulates an unstable, flickering cooling system.
- **Behavior**:
  - Alternates between heating and cooling behaviors.
  - `10` cycles of heating followed by `5` cycles of cooling.
  - Tests the system's ability to handle fluctuating conditions.

## 🏗️ Data Structure
The module uses a `SmartDataGenerator` struct to maintain its state:

```c
typedef struct {
    MockDataState state;        // Current simulation state
    float current_temp;         // Last generated temperature
    float current_humidity;     // Last generated humidity
    float temp_drift;           // Rate of temperature change per cycle
    float humidity_drift;       // Rate of humidity change per cycle
    int stable_cycles;          // Counter for tracking alternating states
} SmartDataGenerator;
```

## ⚙️ Functions

| Function | Purpose | Parameters | Returns |
| :--- | :--- | :--- | :--- |
| **`init_generator()`** | Initialize the generator to stable starting conditions. | `SmartDataGenerator*` | `void` |
| **`set_generator_state()`** | Change the simulation scenario. | `SmartDataGenerator*`, `MockDataState` | `void` |
| **`generate_reading()`** | Produce the next simulated sensor reading. | `SmartDataGenerator*` | `SensorReading` |
