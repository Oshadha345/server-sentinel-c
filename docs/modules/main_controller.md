# 🎮 Main Controller Module

## 🎯 Purpose

> The Main Controller serves as the central coordinator for the Server-Sentinel-C system. It initializes all subsystems, manages the main application loop, and facilitates communication between modules.

## 📝 Responsibilities

### 🚀 System Initialization
- ✅ Initialize all modules in the correct order
- 🚦 Set up the initial system state (`NORMAL`)
- 💾 Configure the logger with the specified buffer size (120 entries)

### 🔄 Main Loop Management
- 🔁 Maintain the core program execution loop
- 🧭 Manage the program's execution flow
- 🛑 Handle graceful program termination

### 🤝 Module Coordination
- ⌨️ Obtain user commands from the User Interface module
- ➡️ Pass commands to the Smart Data module to affect environmental conditions
- 📈 Get simulated sensor readings from the Smart Data module
- ✍️ Send readings to the Logger module for recording
- 🧠 Pass readings to the System Logic module for state determination
- 🖥️ Update the User Interface with the current system state and alerts

## 🏗️ Data Structures

#### **`Controller`**
```c
typedef struct {
    SystemStatus status;       // Current system status
    SmartDataGenerator data_gen; // Data generator
    LogBuffer log_buffer;      // System log
    bool running;              // Program execution flag
} Controller;
```

#### **`SystemStatus`**
```c
typedef struct {
    SystemState state;         // Current system state
    SensorReading last_reading; // Most recent sensor reading
    int critical_time;         // Time spent in critical state
} SystemStatus;
```

## ⚙️ Functions

### `initializeSystem()`
- **🎯 Purpose:** Set up all system components.
- **📥 Parameters:** None.
- **📤 Returns:** An initialized `Controller` struct.
- **🔧 Behavior:**
    - Initializes the Smart Data generator.
    - Creates an empty log buffer.
    - Sets the initial system state to `NORMAL`.
    - Sets the `running` flag to `true`.

### `mainLoop()`
- **🎯 Purpose:** Runs the main program loop.
- **📥 Parameters:** A pointer to the `Controller`.
- **📤 Returns:** None.
- **🔧 Behavior:**
    - Continues execution until the `running` flag is `false`.
    - Processes user commands.
    - Generates and logs sensor readings.
    - Updates the system state.
    - Displays appropriate alerts.
    - Manages the shutdown condition.

### `processCommand()`
- **🎯 Purpose:** Handles user commands.
- **📥 Parameters:** A pointer to the `Controller`, a `UserCommand`.
- **📤 Returns:** None.
- **🔧 Behavior:**
    - Updates the Smart Data generator state based on the command.
    - Handles special commands like "exit" or "help".

### `updateSystemState()`
- **🎯 Purpose:** Updates the system state based on current readings.
- **📥 Parameters:** A pointer to the `Controller`, a `SensorReading`.
- **📤 Returns:** None.
- **🔧 Behavior:**
    - Passes the reading to the System Logic module.
    - Updates the system state based on the result.
    - Triggers a shutdown if conditions warrant.

### `shutdown()`
- **🎯 Purpose:** Handles the system shutdown sequence.
- **📥 Parameters:** A pointer to the `Controller`.
- **📤 Returns:** None.
- **🔧 Behavior:**
    - Logs a final shutdown message.
    - Sets the `running` flag to `false` to terminate the main loop.
    - Displays a final status report.
