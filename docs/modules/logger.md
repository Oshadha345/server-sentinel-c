# 📝 Logger Module

## 🎯 Purpose
> The Logger module is responsible for recording and storing sensor readings in a circular buffer. It maintains a historical record of environmental conditions and provides access to this data for analysis and display.

## 🛠️ Responsibilities

### **💾 Data Recording**
- ✅ Record each sensor reading with a timestamp.
- ✅ Maintain a fixed-size circular buffer (120 entries).
- ✅ Manage the oldest/newest entry pointers.

### **🔍 Data Access**
- ✅ Provide access to the complete log history.
- ✅ Support retrieval of the most recent entries.
- ✅ Enable filtering or searching of log entries (optional feature).

## 🏗️ Data Structures

### `LogEntry`
```c
typedef struct {
    SensorReading reading;    // Temperature and humidity values
    time_t timestamp;         // When the reading was recorded
    SystemState state;        // System state at time of reading
} LogEntry;
```
### `LogBuffer`
```c
typedef struct {
    LogEntry entries[LOG_SIZE]; // Fixed array of 120 entries
    int head;                  // Index of oldest entry
    int tail;                  // Index of newest entry
    int count;                 // Number of entries currently stored
} LogBuffer;
```

## 🚀 Functions

### `initializeLogger()`
- **Purpose:** Create an empty log buffer.
- **Parameters:** None.
- **Returns:** Initialized `LogBuffer`.
- **Behavior:** Sets `head`, `tail`, and `count` to 0.

### `logReading()`
- **Purpose:** Add a new reading to the log.
- **Parameters:**
    - `LogBuffer` pointer
    - `SensorReading`
    - `SystemState`
- **Returns:** None.
- **Behavior:**
    - Creates a `LogEntry` with the current time.
    - If the buffer is full, overwrites the oldest entry.
    - If the buffer is not full, adds the entry at the tail.
    - Updates `head`/`tail` pointers appropriately.

### `getLogEntries()`
- **Purpose:** Retrieve all entries in the log.
- **Parameters:** `LogBuffer` pointer.
- **Returns:** An array of `LogEntry` structures and the count.
- **Behavior:** Returns entries from oldest to newest.

### `getLatestEntries()`
- **Purpose:** Retrieve the most recent entries.
- **Parameters:**
    - `LogBuffer` pointer
    - Number of entries to retrieve
- **Returns:** An array of the most recent `LogEntry` structures.
- **Behavior:**
    - Returns up to the specified number of entries.
    - Returns entries from newest to oldest.
    - Returns fewer entries if the buffer contains less than requested.
