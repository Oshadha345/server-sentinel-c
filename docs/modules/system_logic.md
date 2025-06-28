# System Logic Module

## Purpose
The System Logic module is responsible for determining the system state based on sensor readings. It implements the core decision-making logic of the environmental controller, comparing temperature and humidity readings against thresholds and tracking critical conditions over time.

## Responsibilities

-   **Threshold Checking**
    -   Compare temperature readings against caution (45°C) and danger (60°C) thresholds.
    -   Compare humidity readings against caution (30% / 70%) and danger (20% / 80%) thresholds.
    -   Determine the appropriate system state based on these comparisons.
-   **State Management**
    -   Manage transitions between the four system states (`NORMAL`, `CAUTION`, `DANGER`, `SHUTDOWN`).
    -   Ensure state transitions follow the defined state diagram.
    -   Prevent erratic state changes during fluctuating conditions.
-   **Critical Condition Tracking**
    -   Track the duration of critical temperature conditions.
    -   Manage the 20-second countdown timer for system shutdown.
    -   Reset the timer when conditions return to safer levels.

## Data Structures

### SystemState Enumeration
```c
typedef enum {
    NORMAL,   // All parameters within safe range
    CAUTION,  // At least one parameter in caution range
    DANGER,   // At least one parameter in danger range
    SHUTDOWN  // Critical temperature sustained for required period
} SystemState;
```

### CriticalTimer Structure
```c
typedef struct {
    int seconds_at_critical;  // Time spent at critical temperature
    bool timer_active;        // Whether the shutdown timer is running
} CriticalTimer;
```

## Functions

### `checkTemperature()`
-   **Purpose**: Evaluates temperature reading against thresholds.
-   **Parameters**: `float` temperature value.
-   **Returns**: Appropriate state based on temperature.
-   **Behavior**:
    -   Returns `NORMAL` if temperature <= 45°C.
    -   Returns `CAUTION` if temperature > 45°C and <= 60°C.
    -   Returns `DANGER` if temperature > 60°C.

### `checkHumidity()`
-   **Purpose**: Evaluates humidity reading against thresholds.
-   **Parameters**: `float` humidity value.
-   **Returns**: Appropriate state based on humidity.
-   **Behavior**:
    -   Returns `NORMAL` if humidity is between 30% and 70%.
    -   Returns `CAUTION` if humidity is < 30% or > 70% but not in the danger range.
    -   Returns `DANGER` if humidity is < 20% or > 80%.

### `determineSystemState()`
-   **Purpose**: Determines the overall system state based on both temperature and humidity.
-   **Parameters**: `SensorReading` struct containing temperature and humidity.
-   **Returns**: The current `SystemState`.
-   **Behavior**: Takes the more severe state between the temperature and humidity evaluations.

### `updateCriticalTimer()`
-   **Purpose**: Manages the shutdown countdown timer.
-   **Parameters**: Current `SystemState`, time delta.
-   **Returns**: `bool` indicating whether a shutdown should occur.
-   **Behavior**:
    -   Increments the timer when in a `DANGER` state due to temperature.
    -   Resets the timer when not in a temperature-based `DANGER` state.
    -   Returns `true` when the timer exceeds 20 seconds.