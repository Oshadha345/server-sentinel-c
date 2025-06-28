# 🏗️ Data Structures

This document defines all data structures used in the Server-Sentinel-C system.

---

## 🔢 Enumerations

### 🚦 `SystemState`
Defines the overall operational state of the system.
```c
typedef enum {
    NORMAL,   // All parameters within safe range
    CAUTION,  // At least one parameter in caution range
    DANGER,   // At least one parameter in danger range
    SHUTDOWN  // Critical temperature sustained for required period
} SystemState;
```

### 🎭 `MockDataState`
Represents the different simulation scenarios for generating mock sensor data.
```c
typedef enum {
    STABLE,               // Normal server room conditions
    HEATING_UP,           // Simulates cooling system failure
    COOLING_DOWN,         // Simulates successful repair
    HUMIDITY_SPIKE,       // Simulates humidity control failure
    INTERMITTENT_FAILURE  // Simulates unstable cooling system
} MockDataState;
```

### ⌨️ `CommandType`
Enumerates the commands a user can issue to the system.
```c
typedef enum {
    CMD_NONE,          // No command
    CMD_FAIL_COOLING,  // Trigger cooling failure scenario
    CMD_FIX,           // Trigger system recovery
    CMD_HUMIDITY_SPIKE, // Trigger humidity spike
    CMD_INTERMITTENT,  // Trigger intermittent failure
    CMD_EXIT,          // Exit the program
    CMD_HELP,          // Display help information
    CMD_SHOW_LOG       // Display the log
} CommandType;
```

---

## 🧱 Structures

### 🌡️ `SensorReading`
Holds a single reading of temperature and humidity.
```c
typedef struct {
    float temperature;  // Temperature in Celsius
    float humidity;     // Humidity in percentage
} SensorReading;
```

### 🧠 `SmartDataGenerator`
Manages the state and parameters for generating simulated sensor data.
```c
typedef struct {
    MockDataState state;      // Current simulation state
    float current_temp;       // Last generated temperature
    float current_humidity;   // Last generated humidity
    float temp_drift;         // Rate of temperature change per cycle
    float humidity_drift;     // Rate of humidity change per cycle
    int stable_cycles;        // Counter for tracking alternating states
} SmartDataGenerator;
```

### 📝 `LogEntry`
Represents a single entry in the system log.
```c
typedef struct {
    SensorReading reading;    // Temperature and humidity values
    time_t timestamp;         // When the reading was recorded
    SystemState state;        // System state at time of reading
} LogEntry;
```

### 📚 `LogBuffer`
A circular buffer to store recent log entries.
```c
typedef struct {
    LogEntry entries[LOG_SIZE]; // Fixed array of 120 entries
    int head;                  // Index of oldest entry
    int tail;                  // Index of newest entry
    int count;                 // Number of entries currently stored
} LogBuffer;
```

### ⏱️ `CriticalTimer`
Tracks the duration the system has been in a critical state.
```c
typedef struct {
    int seconds_at_critical;  // Time spent at critical temperature
    bool timer_active;        // Whether the shutdown timer is running
} CriticalTimer;
```

### 🧑‍💻 `UserCommand`
Stores a command received from the user.
```c
typedef struct {
    CommandType type;        // Type of command
    char raw_input[64];      // Raw input string
} UserCommand;
``` 

### 🖥️ `SystemStatus`
A snapshot of the system's current status.
```c
typedef struct {
    SystemState state;         // Current system state
    SensorReading last_reading; // Most recent sensor reading
    int critical_time;         // Time spent in critical state
} SystemStatus;
```

### 🕹️ `Controller`
The main structure that holds the entire state of the application.
```c
typedef struct {
    SystemStatus status;       // Current system status
    SmartDataGenerator data_gen; // Data generator
    LogBuffer log_buffer;      // System log
    bool running;              // Program execution flag
} Controller;
```

---

## ⚙️ Constants

Defines key configuration values and thresholds for the system.
```c
// Thresholds
#define TEMP_CAUTION_THRESHOLD 45.0f
#define TEMP_DANGER_THRESHOLD  60.0f
#define HUMID_LOW_CAUTION      30.0f
#define HUMID_HIGH_CAUTION     70.0f
#define HUMID_LOW_DANGER       20.0f
#define HUMID_HIGH_DANGER      80.0f

// Logger configuration
#define LOG_SIZE 120

// Critical timer
#define CRITICAL_SHUTDOWN_SECONDS 20
```
